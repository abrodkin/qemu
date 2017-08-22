/*
 * QEMU ARC CPU
 *
 * Copyright (c) 2016 Michael Rolnik
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
#include "qapi/error.h"
#include "cpu.h"
#include "qemu-common.h"
#include "migration/vmstate.h"
#include "exec/log.h"

static const VMStateDescription vms_arc_cpu = {
  .name               = "cpu",
  .version_id         = 0,
  .minimum_version_id = 0,
  .fields = (VMStateField[]) {
    VMSTATE_END_OF_LIST()
  }
};

static void arc_cpu_set_pc(CPUState *cs, vaddr value)
{
  ARCCPU *cpu = ARC_CPU (cs);

  CPU_PCL (&cpu->env) = value & 0xfffffffc;
  cpu->env.pc = value;
}

static bool arc_cpu_has_work(CPUState *cs)
{
  return false;
}

static void arc_cpu_synchronize_from_tb(CPUState *cs, TranslationBlock *tb)
{
  ARCCPU      *cpu = ARC_CPU(cs);
  CPUARCState *env = &cpu->env;

  env->pc = tb->pc;
}

static void arc_cpu_reset(CPUState *s)
{
  ARCCPU *cpu = ARC_CPU(s);
  ARCCPUClass *arcc = ARC_CPU_GET_CLASS(cpu);
  CPUARCState *env = &cpu->env;

  if (qemu_loglevel_mask(CPU_LOG_RESET)) {
    qemu_log("CPU Reset (CPU)\n");
    log_cpu_state(s, 0);
  }

  arcc->parent_reset(s);

  memset(env->r, 0, sizeof(env->r));
  // memset(env, 0, offsetof(CPUARCState, end_reset_fields));
//  env->pc = 0x100;   /* TODO: this is just for testing */
//  CPU_PCL(env) = 0x100;   /* TODO: this is just for testing */

  tlb_flush(s);
}

static void arc_cpu_disas_set_info(CPUState *cs, disassemble_info *info)
{
  ARCCPU *cpu = ARC_CPU (cs);
  CPUARCState *env = &cpu->env;

  switch (env->family)
    {
    case ARC_OPCODE_ARC700:
      info->mach = bfd_mach_arc_arc700;
      break;
    case ARC_OPCODE_ARC600:
      info->mach = bfd_mach_arc_arc600;
      break;
    case ARC_OPCODE_ARCv2EM:
      info->mach = bfd_mach_arc_arcv2em;
      break;
    case ARC_OPCODE_ARCv2HS:
      info->mach = bfd_mach_arc_arcv2hs;
      break;
    default:
      info->mach = bfd_mach_arc_arcv2;
      break;
    }

  info->print_insn = print_insn_arc;
  info->endian = BFD_ENDIAN_LITTLE;
}

static void arc_cpu_realizefn(DeviceState *dev, Error **errp)
{
  CPUState *cs = CPU (dev);
  ARCCPUClass *arcc = ARC_CPU_GET_CLASS (dev);
  Error *local_err = NULL;

  cpu_exec_realizefn (cs, &local_err);
  if (local_err != NULL) {
    error_propagate (errp, local_err);
    return;
  }

  qemu_init_vcpu(cs);
  cpu_reset(cs);

  arcc->parent_realize(dev, errp);
}

static void arc_cpu_set_int(void *opaque, int irq, int level)
{
}

static void arc_cpu_initfn(Object *obj)
{
  CPUState *cs = CPU(obj);
  ARCCPU *cpu = ARC_CPU(obj);
  static bool inited;

  cs->env_ptr = &cpu->env;

#ifndef CONFIG_USER_ONLY
  qdev_init_gpio_in(DEVICE(cpu), arc_cpu_set_int, 37);
#endif

  if (tcg_enabled() && !inited) {
    inited = true;
    arc_translate_init();
  }
}

static ObjectClass *arc_cpu_class_by_name(const char *cpu_model)
{
  ObjectClass *oc;
  char *typename;
  char **cpuname;

  if (!cpu_model) {
    return NULL;
  }

  cpuname = g_strsplit(cpu_model, ",", 1);
  typename = g_strdup_printf("%s-" TYPE_ARC_CPU, cpuname[0]);
  oc = object_class_by_name(typename);

  g_strfreev(cpuname);
  g_free(typename);

  if (!oc
      || !object_class_dynamic_cast(oc, TYPE_ARC_CPU)
      || object_class_is_abstract(oc)) {
    return NULL;
  }

  return oc;
}

static void arc_cpu_class_init(ObjectClass *oc, void *data)
{
  DeviceClass *dc = DEVICE_CLASS(oc);
  CPUClass *cc = CPU_CLASS(oc);
  ARCCPUClass *arcc = ARC_CPU_CLASS(oc);

  arcc->parent_realize = dc->realize;
  dc->realize = arc_cpu_realizefn;

  arcc->parent_reset = cc->reset;
  cc->reset = arc_cpu_reset;

  cc->class_by_name = arc_cpu_class_by_name;

  cc->has_work = arc_cpu_has_work;
  cc->do_interrupt = arc_cpu_do_interrupt;
  cc->cpu_exec_interrupt = arc_cpu_exec_interrupt;
  cc->dump_state = arc_cpu_dump_state;
  cc->set_pc = arc_cpu_set_pc;
#if !defined(CONFIG_USER_ONLY)
  cc->memory_rw_debug = arc_cpu_memory_rw_debug;
  cc->get_phys_page_debug = arc_cpu_get_phys_page_debug;
  cc->vmsd = &vms_arc_cpu;
#else
  cc->handle_mmu_fault = arc_cpu_handle_mmu_fault;
#endif
  cc->disas_set_info = arc_cpu_disas_set_info;
  cc->synchronize_from_tb = arc_cpu_synchronize_from_tb;
  cc->gdb_read_register = arc_cpu_gdb_read_register;
  cc->gdb_write_register = arc_cpu_gdb_write_register;
  cc->gdb_num_core_regs = 68;

}

static void arc_any_initfn (Object *obj)
{
  /* Set cpu feature flags */
  ARCCPU *cpu = ARC_CPU(obj);
  cpu->env.family = ARC_OPCODE_ARC700;
}

static void arc600_initfn (Object *obj)
{
  ARCCPU *cpu = ARC_CPU(obj);
  cpu->env.family = ARC_OPCODE_ARC600;
}

static void arc700_initfn (Object *obj)
{
  ARCCPU *cpu = ARC_CPU(obj);
  cpu->env.family = ARC_OPCODE_ARC700;
}

static void arcem_initfn (Object *obj)
{
  ARCCPU *cpu = ARC_CPU(obj);
  cpu->env.family = ARC_OPCODE_ARCv2EM;
}

static void archs_initfn (Object *obj)
{
  ARCCPU *cpu = ARC_CPU(obj);
  cpu->env.family = ARC_OPCODE_ARCv2HS;
}

typedef struct ARCCPUInfo {
  const char     *name;
  void (*initfn)(Object *obj);
} ARCCPUInfo;

static const ARCCPUInfo arc_cpus[] = {
  { .name = "arc600", .initfn = arc600_initfn },
  { .name = "arc700", .initfn = arc700_initfn },
  { .name = "arcem", .initfn = arcem_initfn },
  { .name = "archs", .initfn = archs_initfn },
  { .name = "any", .initfn = arc_any_initfn },
};

ARCCPU *cpu_arc_init (const char *cpu_model)
{
  ARCCPU *cpu = ARC_CPU (cpu_generic_init (TYPE_ARC_CPU, cpu_model));

  object_property_set_bool (OBJECT (cpu), true, "realized", NULL);

  return cpu;
}

static void cpu_register(const ARCCPUInfo *info)
{
  TypeInfo type_info =
    {
      .parent = TYPE_ARC_CPU,
      .instance_size = sizeof (ARCCPU),
      .instance_init = info->initfn,
      .class_size = sizeof (ARCCPUClass),
    };

  type_info.name = g_strdup_printf ("%s-" TYPE_ARC_CPU, info->name);
  type_register (&type_info);
  g_free ((void *)type_info.name);
}

static const TypeInfo arc_cpu_type_info = {
  .name = TYPE_ARC_CPU,
  .parent = TYPE_CPU,
  .instance_size = sizeof(ARCCPU),
  .instance_init = arc_cpu_initfn,
  .class_size = sizeof(ARCCPUClass),
  .class_init = arc_cpu_class_init,
  .abstract = true,
};

static void arc_cpu_register_types(void)
{
  int i;
  type_register_static(&arc_cpu_type_info);

  for (i = 0; i < ARRAY_SIZE(arc_cpus); i++) {
    cpu_register(&arc_cpus[i]);
  }
}

type_init(arc_cpu_register_types)
