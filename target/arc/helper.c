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

#include "cpu.h"
#include "hw/irq.h"
#include "include/hw/sysbus.h"
#include "include/sysemu/sysemu.h"
#include "exec/exec-all.h"
#include "exec/cpu_ldst.h"
#include "qemu/host-utils.h"
#include "exec/helper-proto.h"

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

void tlb_fill(CPUState *cs, target_ulong vaddr, MMUAccessType access_type,
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

void arc_cpu_do_interrupt(CPUState *cs)
{
  cs->exception_index = -1;
}

bool arc_cpu_exec_interrupt(CPUState *cs, int interrupt_request)
{
  return false;
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
