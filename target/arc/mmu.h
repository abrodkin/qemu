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

/* PD0 flags */
#define TLB_G   0x00000100      /* Global */
#define TLB_V   0x00000200      /* Valid */
#define TLB_SZ  0x00000400      /* Size: Normal or Super Page */
#define TLB_L   0x00000800      /* Lock */

/* PD1 permission bits */
#define TLB_FC  0x00000001      /* Cached */
#define TLB_XU  0x00000002      /* User Execute */
#define TLB_WU  0x00000004      /* User Write */
#define TLB_RU  0x00000008      /* User Read */
#define TLB_XK  0x00000010      /* Kernel Execute */
#define TLB_WK  0x00000020      /* Kernel Write */
#define TLB_RK  0x00000040      /* Kernel Read */

#define TLB_ENTRIES     1024


struct arc_mmu {
  bool enabled;

  /* nTLB is actually {PD0,PD1} tuples, better keep it "unpacked" for speed */
#define TLB_FLG     0    // includes both PD1 permissions and PD0 flags
#define TLB_ASID    1
#define TLB_PFN     2
  uint32_t nTLB[3][TLB_ENTRIES];

  /* Current Address Space ID (in whose context mmu lookups done)
   * Note that it is actually present in AUX PID reg, which we don't
   * explicitly maintain, but {re,de}construct as needed by LR/SR insns
   * respectively.
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
