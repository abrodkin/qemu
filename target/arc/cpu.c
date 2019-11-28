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
 * <<a  rel="nofollow" href="http://www.gnu.org/licenses/lgpl-2.1.html">http://www.gnu.org/licenses/lgpl-2.1.html</a>>
 */

#include "qemu/osdep.h"
#include "qapi/error.h"
#include "cpu.h"
#include "qemu-common.h"
#include "migration/vmstate.h"
#include "machine.h"
#include "exec/log.h"

static void arc_cpu_set_pc(CPUState *cs, vaddr value)
{
    ARCCPU   *cpu = ARC_CPU (cs);

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
    ARCCPUClass *mcc = ARC_CPU_GET_CLASS(cpu);
    CPUARCState *env = &cpu->env;

    if (qemu_loglevel_mask(CPU_LOG_RESET)) {
        qemu_log("CPU Reset (CPU)\n");
        log_cpu_state(s, 0);
    }

    mcc->parent_reset(s);

    memset(env->r, 0, sizeof(env->r));
    env->pc = 0x100;   /* TODO: this is just for testing */
    CPU_PCL(env) = 0x100;   /* TODO: this is just for testing */

    tlb_flush(s);
}

static void arc_cpu_disas_set_info(CPUState *cpu, disassemble_info *info)
{
    info->mach = bfd_arch_arc;
    info->print_insn = NULL;
}

static void arc_cpu_realizefn(DeviceState *dev, Error **errp)
{
    CPUState *cs = CPU(dev);
    ARCCPUClass *mcc = ARC_CPU_GET_CLASS(dev);
    Error *local_err = NULL;

    cpu_exec_realizefn(cs, &local_err);
    if (local_err != NULL) {
        error_propagate(errp, local_err);
        return;
    }

    qemu_init_vcpu(cs);
    cpu_reset(cs);

    mcc->parent_realize(dev, errp);
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
        ||  !object_class_dynamic_cast(oc, TYPE_ARC_CPU)
        ||  object_class_is_abstract(oc)) {
        return NULL;
    }

    return oc;
}

static void arc_cpu_class_init(ObjectClass *oc, void *data)
{
    DeviceClass *dc = DEVICE_CLASS(oc);
    CPUClass *cc = CPU_CLASS(oc);
    ARCCPUClass *mcc = ARC_CPU_CLASS(oc);

    mcc->parent_realize = dc->realize;
    dc->realize = arc_cpu_realizefn;

    mcc->parent_reset = cc->reset;
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

static void arc_any_initfn(Object *obj)
{
    /* Set cpu feature flags */
}

typedef struct ARCCPUInfo {
    const char     *name;
    void (*initfn)(Object *obj);
} ARCCPUInfo;

static const ARCCPUInfo arc_cpus[] = {
    {   .name = "any", .initfn = arc_any_initfn },
};

static gint arc_cpu_list_compare(gconstpointer a, gconstpointer b)
{
    ObjectClass *class_a = (ObjectClass *)a;
    ObjectClass *class_b = (ObjectClass *)b;
    const char *name_a;
    const char *name_b;

    name_a = object_class_get_name(class_a);
    name_b = object_class_get_name(class_b);
    if (strcmp(name_a, "any-" TYPE_ARC_CPU) == 0) {
        return 1;
    } else if (strcmp(name_b, "any-" TYPE_ARC_CPU) == 0) {
        return -1;
    } else {
        return strcmp(name_a, name_b);
    }
}

static void arc_cpu_list_entry(gpointer data, gpointer user_data)
{
    ObjectClass *oc = data;
    CPUListState *s = user_data;
    const char *typename;
    char *name;

    typename = object_class_get_name(oc);
    name = g_strndup(typename, strlen(typename) - strlen("-" TYPE_ARC_CPU));
    (*s->cpu_fprintf)(s->file, "  %s\n", name);
    g_free(name);
}

void arc_cpu_list(FILE *f, fprintf_function cpu_fprintf)
{
    CPUListState s = {
        .file = f,
        .cpu_fprintf = cpu_fprintf,
    };
    GSList *list;

    list = object_class_get_list(TYPE_ARC_CPU, false);
    list = g_slist_sort(list, arc_cpu_list_compare);
    (*cpu_fprintf)(f, "Available CPUs:\n");
    g_slist_foreach(list, arc_cpu_list_entry, &s);
    g_slist_free(list);
}
ARCCPU *cpu_arc_init(const char *cpu_model)
{
    ARCCPU *cpu = ARC_CPU (cpu_generic_init (TYPE_ARC_CPU, cpu_model));

    object_property_set_bool (OBJECT (cpu), true, "realized", NULL);

    return cpu;
}

static void cpu_register(const ARCCPUInfo *info)
{
    TypeInfo type_info = {
        .parent = TYPE_ARC_CPU,
        .instance_size = sizeof(ARCCPU),
        .instance_init = info->initfn,
        .class_size = sizeof(ARCCPUClass),
    };

    type_info.name = g_strdup_printf("%s-" TYPE_ARC_CPU, info->name);
    type_register(&type_info);
    g_free((void *)type_info.name);
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
