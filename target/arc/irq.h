/*
 * QEMU ARC CPU
 *
 * Copyright (c) 2019
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License) any later version.
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

#ifndef __IRQ_H__
#define __IRQ_H__

#include "arc-regs.h"
#include "cpu.h"

uint32_t aux_irq_get (struct arc_aux_reg_detail *, void *);
void aux_irq_set (struct arc_aux_reg_detail *, uint32_t, void *);
bool arc_cpu_exec_interrupt (CPUState *, int);
bool arc_rtie_interrupts (CPUARCState *);

#endif
