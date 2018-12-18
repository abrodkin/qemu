/*
 * QEMU ARC CPU
 *
 * Copyright (c) 2019
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, see
 * http://www.gnu.org/licenses/lgpl-2.1.html
 */

#include "qemu/osdep.h"

#include "cpu.h"
#include "hw/irq.h"
#include "include/hw/sysbus.h"
#include "include/sysemu/sysemu.h"
#include "exec/exec-all.h"
#include "exec/cpu_ldst.h"
#include "qemu/host-utils.h"
#include "exec/helper-proto.h"

#if defined (CONFIG_USER_ONLY)

void arc_cpu_do_interrupt (CPUState *cs)
{
  ARCCPU *cpu = ARC_CPU (cs);
  CPUARCState *env = &cpu->env;

  cs->exception_index = -1;
  CPU_ILINK (env) = env->pc;
}

#else /* !CONFIG_USER_ONLY */

void arc_cpu_do_interrupt (CPUState *cs)
{
  ARCCPU *cpu = ARC_CPU (cs);
  CPUARCState *env = &cpu->env;
  uint32_t offset = 0;
  uint32_t vectno;
  int i, j;

  /* FIXME! we cannot do interrupts in delay slots.  */

  /* Generic computation for exceptions.  */
  switch (cs->exception_index)
    {
    case EXCP_RESET:
    case EXCP_MEMORY_ERROR:
    case EXCP_INST_ERROR:
    case EXCP_MACHINE_CHECK:
    case EXCP_TLB_MISS_I:
    case EXCP_TLB_MISS_D:
    case EXCP_PROTV:
    case EXCP_PRIVILRGEV:
    case EXCP_SWI:
    case EXCP_TRAP:
    case EXCP_EXTENSION:
    case EXCP_DIVZERO:
    case EXCP_DCERROR:
    case EXCP_MALIGNED:
      qemu_log_mask (CPU_LOG_INT, "exception %d at pc=0x%08x\n",
		     cs->exception_index, env->pc);

      env->stat_er = env->stat;
      /* If we take an exception within an exception => fatal Machine
	 Check.  */
      if (env->stat.AEf == 1)
	{
	  cs->exception_index = EXCP_MACHINE_CHECK;
	  env->causecode = 0;
	  env->param = 0;
	}
      vectno = cs->exception_index & 0x0F;
      offset = vectno << 2;

      /* 3. exception status register is loaded with the contents of
	 STATUS32.  */
      env->stat_er = env->stat;

      /* 4. exception return branch target address register.  */
      env->erbta = env->bta;

      /* 5. eception cause register is loaded with a code to indicate
	 the cause of the exception.  */
      env->ecr = (vectno & 0xFF) << 16;
      env->ecr |= (env->causecode & 0xFF) << 8;
      env->ecr |= (env->param & 0xFF);

      /* 7. CPU is switched to kernel mode.  */
      env->stat.Uf = 0;

      /* 8. Interrupts are disabled.  */
      env->stat.IEf = 0;

      /* 9. The active exception flag is set.  */
      env->stat.AEf = 1;
      break;
    case EXCP_FIRQ:
    case EXCP_IRQ:
      {
	bool found = false;
	qemu_log_mask (CPU_LOG_INT, "interrupt at pc=0x%08x\n", env->pc);
	CPU_ILINK (env) = env->pc;
	env->stat_l1 = env->stat;

	/* Find the first IRQ to serve.  */
	for (j = 0; j < cpu->cfg.number_of_levels && !found; j++)
	  for (i = 0; i < cpu->cfg.number_of_interrupts; i++)
	    if (env->irq_bank[16 + i].priority == j
		&& env->irq_bank[16 + i].pending)
	      {
		found = true;
		break;
	      }
	offset = (i + 16) << 2;

	/* Set the AUX_IRQ_ACT.  */
	if ((env->aux_irq_act & 0xff) == 0)
	  env->aux_irq_act = env->stat.Uf << 31;
	env->aux_irq_act |= 1 << (--j);

	/* Set ICAUSE register.  */
	env->icause[j] = i;

	/* Switch SP with AUX_SP.  */
	if (env->stat.Uf)
	{
	    uint32_t tmp = env->aux_user_sp;
	    env->aux_user_sp = env->r[28];
	    env->r[28] = tmp;
	}

	/* CPU is switched to kernel mode.  */
	env->stat.Uf = 0;
      }
      break;
    default:
      cpu_abort(cs, "unhandled exception/irq type=%d\n",
		cs->exception_index);
      break;
    }

  /* XX. The PC is set with the appropriate exception vector. */
  env->pc = cpu_ldl_code (env, env->intvec + offset);
  CPU_PCL (env) = env->pc & 0xfffffffe;

  qemu_log_mask(CPU_LOG_INT, "%s isr=%x vec=%x ecr=0x%08x\n",
		__func__, env->pc, offset, env->ecr);
}

#endif

//void arc_cpu_register_gdb_regs_for_features(ARCCPU *cpu)
//{
//    CPUState *cs = CPU(cpu);
//    CPUARMState *env = &cpu->env;
//
//    gdb_register_coprocessor(cs, aarch64_fpu_gdb_get_reg,
//                             aarch64_fpu_gdb_set_reg,
//                             34, "arc-aux-minimal.xml", 0);
//}
static gint arc_cpu_list_compare (gconstpointer a, gconstpointer b)
{
  ObjectClass *class_a = (ObjectClass *)a;
  ObjectClass *class_b = (ObjectClass *)b;
  const char *name_a;
  const char *name_b;

  name_a = object_class_get_name (class_a);
  name_b = object_class_get_name (class_b);
  if (strcmp (name_a, "any-" TYPE_ARC_CPU) == 0)
    {
      return 1;
    } else if (strcmp (name_b, "any-" TYPE_ARC_CPU) == 0) {
    return -1;
  } else {
    return strcmp (name_a, name_b);
  }
}

static void arc_cpu_list_entry (gpointer data, gpointer user_data)
{
  ObjectClass *oc = data;
  CPUListState *s = user_data;
  const char *typename;
  char *name;

  typename = object_class_get_name (oc);
  name = g_strndup (typename, strlen (typename) - strlen ("-" TYPE_ARC_CPU));
  (*s->cpu_fprintf)(s->file, "  %s\n", name);
  g_free (name);
}

void arc_cpu_list (FILE *f, fprintf_function cpu_fprintf)
{
  CPUListState s = {
    .file = f,
    .cpu_fprintf = cpu_fprintf,
  };
  GSList *list;

  list = object_class_get_list (TYPE_ARC_CPU, false);
  list = g_slist_sort (list, arc_cpu_list_compare);
  (*cpu_fprintf)(f, "Available CPUs:\n");
  g_slist_foreach (list, arc_cpu_list_entry, &s);
  g_slist_free (list);
}

void tlb_fill(CPUState *cs, target_ulong vaddr, int size,
	      MMUAccessType access_type,
	      int mmu_idx, uintptr_t retaddr)
{
  target_ulong page_size = TARGET_PAGE_SIZE;
  int prot = 0;
  MemTxAttrs attrs = {};
  uint32_t paddr;

  vaddr &= TARGET_PAGE_MASK;
  paddr = PHYS_BASE_RAM + vaddr - VIRT_BASE_RAM;
  prot = PAGE_READ | PAGE_WRITE | PAGE_EXEC;

  tlb_set_page_with_attrs(cs, vaddr, paddr, attrs, prot, mmu_idx, page_size);
}

int arc_cpu_memory_rw_debug(CPUState *cs, vaddr addr, uint8_t *buf,
			    int len, bool is_write)
{
  return  cpu_memory_rw_debug(cs, addr, buf, len, is_write);
}

hwaddr arc_cpu_get_phys_page_debug(CPUState *cs, vaddr addr)
{
  return  addr;   /*  I assume 1:1 address correspondance */
}

void helper_debug(CPUARCState *env)
{
  CPUState *cs = CPU(arc_env_get_cpu(env));

  cs->exception_index = EXCP_DEBUG;
  cpu_loop_exit(cs);
}

/* Local variables:
   eval: (c-set-style "gnu")
   indent-tabs-mode: t
   End:  */
