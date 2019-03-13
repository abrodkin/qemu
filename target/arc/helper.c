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
#include "irq.h"

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
  const char *name;

  /* FIXME! we cannot do interrupts in delay slots.  */

  /* Generic computation for exceptions.  */
  switch (cs->exception_index)
    {
    case EXCP_RESET:
      name = "Reset";
      break;
    case EXCP_MEMORY_ERROR:
      name = "Memory Error";
      break;
    case EXCP_INST_ERROR:
      name = "Instruction Error";
      break;
    case EXCP_MACHINE_CHECK:
      name = "Machine Check";
      break;
    case EXCP_TLB_MISS_I:
      name = "TLB Miss Instruction";
      break;
    case EXCP_TLB_MISS_D:
      name = "TLB Miss Data";
      break;
    case EXCP_PROTV:
      name = "Protection Violation";
      break;
    case EXCP_PRIVILRGEV:
      name = "Privilege Violation";
      break;
    case EXCP_SWI:
      name = "SWI";
      break;
    case EXCP_TRAP:
      name = "Trap";
      break;
    case EXCP_EXTENSION:
      name = "Extension";
      break;
    case EXCP_DIVZERO:
      name = "DIV by Zero";
      break;
    case EXCP_DCERROR:
      name = "DCError";
      break;
    case EXCP_MALIGNED:
      name = "Maligned";
      break;
    case EXCP_IRQ:
    default:
      cpu_abort(cs, "unhandled exception/irq type=%d\n",
		cs->exception_index);
      break;
    }

  qemu_log_mask (CPU_LOG_INT, "[EXCP] exception %d (%s) at pc=0x%08x\n",
                 cs->exception_index, name, env->pc);

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
  env->stat.Uf = 0; /* FIXME! do switch to kernel mode.  */
  //tlb_flush(cpu);
  if (env->stat_er.Uf)
    switchSP (env);

  /* 8. Interrupts are disabled.  */
  env->stat.IEf = 0;

  /* 9. The active exception flag is set.  */
  env->stat.AEf = 1;

  /* 10-14. Other flags sets.  */
  env->stat.Lf  = 1;
  env->stat.DEf  = 0;
  env->stat.ESf = 0;
  env->stat.DZf = 0;
  env->stat.SCf = 0;

  /* 15. The PC is set with the appropriate exception vector. */
  env->pc = cpu_ldl_code (env, env->intvec + offset);
  CPU_PCL (env) = env->pc & 0xfffffffe;

  qemu_log_mask(CPU_LOG_INT, "[EXCP] isr=%x vec=%x ecr=0x%08x\n",
		env->pc, offset, env->ecr);

  cs->exception_index = -1;
}

#endif


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

int arc_cpu_memory_rw_debug(CPUState *cs, vaddr addr, uint8_t *buf,
			    int len, bool is_write)
{
  return  cpu_memory_rw_debug(cs, addr, buf, len, is_write);
}

hwaddr arc_cpu_get_phys_page_debug(CPUState *cs, vaddr addr)
{
  ARCCPU *cpu = ARC_CPU (cs);
  CPUARCState *env = &cpu->env;

  return arc_mmu_translate(env, addr, MMU_MEM_IRRELEVANT_TYPE, NULL /*index*/);
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
