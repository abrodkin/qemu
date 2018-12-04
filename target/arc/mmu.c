/*
 * QEMU ARC CPU
 *
 * Copyright (c) 2018 Cupertino Miranda (cmiranda@synopsys.com)
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

#include "mmu.h"
#include "arc-regs.h"
#include "qemu/osdep.h"

/*
void arc_aux_reg_set_func(struct arc_aux_reg_detail *aux_reg, uint32_t val, void *data);
uint32_t aux_reg_get_func(struct arc_aux_reg_detail *aux_reg, void *data);
*/
void
arc_aux_reg_set_tlbcommand(struct arc_aux_reg_detail *aux_reg,
			   uint32_t val, void *data)
{
  return;
}
