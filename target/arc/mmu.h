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

#ifndef ARC_MMU_H
#define ARC_MMU_H

#include "arc-regs.h"

#define TLB_ENTRIES     1024

#define PD0     0
#define PD1     1

struct arc_mmu {
  bool enabled;

  /* nTLB is organized as {PD0,PD1} tuple */
  uint32_t nTLB[2][TLB_ENTRIES];

  /* 8-bit Address Space ID is actually present in AUX PID
   * we {re,de}construct the PID reg as needed by LR/SR respectively
   */
  uint32_t asid;

  uint32_t tlbpd0;
  uint32_t tlbpd1;
  uint32_t tlbpd1_hi;
  uint32_t tlbindex;
  uint32_t tlbcmd;
  uint32_t scratch_data0;
};


extern void
arc_aux_reg_set_tlbcommand(struct arc_aux_reg_detail *aux_reg,
			   uint32_t val, void *data);

#endif /* ARC_MMU_H */
