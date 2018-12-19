/*
 * ARC Programmable Interrupt Controller support.
 *
 * Copyright (c) 2019
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, see <http://www.gnu.org/licenses/>.
 */

#include "qemu/osdep.h"
#include "hw/hw.h"
#include "cpu.h"
#include "hw/arc/cpudevs.h"

/* ARC pic handler.  */
static void arc_pic_cpu_handler (void* opaque, int irq, int level)
{
  ARCCPU *cpu = (ARCCPU *)opaque;
  CPUState *cs = CPU(cpu);
  CPUARCState *env = &cpu->env;

  if (!cpu->cfg.has_interrupts)
    return;

  if (irq < 16 || irq >= (cpu->cfg.number_of_interrupts + 15))
    return;

  env->irq_bank[irq].pending = 0;

  if ((env->irq_bank[irq].priority <= env->stat.Ef)
      && env->irq_bank[irq].enable
      && level)
    {
      cpu_interrupt (cs, CPU_INTERRUPT_HARD);
      env->irq_bank[irq].pending = 1;
      env->irq_priority_pending |= 1 << env->irq_bank[irq].priority;
    }
  else
    {
      cpu_reset_interrupt (cs, CPU_INTERRUPT_HARD);
      env->irq_priority_pending &= ~(1 << env->irq_bank[irq].priority);
    }
}

/* ARC PIC initialization helper.  */
void cpu_arc_pic_init (ARCCPU *cpu)
{
  CPUARCState *env = &cpu->env;
  int i;
  qemu_irq *qi;

  qi = qemu_allocate_irqs (arc_pic_cpu_handler,
                           cpu, 16 + cpu->cfg.number_of_interrupts);

  for (i = 0; i < cpu->cfg.number_of_interrupts; i++)
    {
      env->irq[16 + i] = qi[16 + i];
    }
}
