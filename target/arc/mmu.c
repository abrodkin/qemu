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
#include "cpu.h"

void arc_aux_reg_mmu_set(struct arc_aux_reg_detail *aux_reg_detail, struct CPUARCState *env, uint32_t val)
{
  struct arc_mmu *mmu = &env->mmu;

  switch (aux_reg_detail->id) {
      case AUX_ID_tlbcommand:
        break;
      case AUX_ID_tlbindex:
        mmu->tlbindex = val;
        break;
      case AUX_ID_tlbpd0:
        mmu->tlbpd0 = val;
        break;
      case AUX_ID_tlbpd1:
        mmu->tlbpd1 = val;
        break;
      case AUX_ID_tlbpd1_hi:
        mmu->tlbpd1_hi = val;
        break;
      case AUX_ID_scratch_data0:
        mmu->scratch_data0 = val;
        break;
      default:
        break;
  }
}

void
arc_aux_reg_set_tlbcommand(struct arc_aux_reg_detail *aux_reg,
			   uint32_t val, void *data)
{
  return;
}


static void mmu_flush_idx(CPUARCState *env, unsigned int idx)
{
  /*
    CPUState *cs = CPU(mb_env_get_cpu(env));
    struct arc_mmy *mmu = &env->mmu;
    unsigned int tlb_size;
    uint32_t tlb_tag, end, t;

    t = mmu->rams[RAM_TAG][idx];
    if (!(t & TLB_VALID))
        return;

    tlb_tag = t & TLB_EPN_MASK;
    tlb_size = tlb_decode_size((t & TLB_PAGESZ_MASK) >> 7);
    end = tlb_tag + tlb_size;

    while (tlb_tag < end) {
        tlb_flush_page(cs, tlb_tag);
        tlb_tag += TARGET_PAGE_SIZE;
    }
  */
}

void arc_mmu_init(struct arc_mmu *mmu)
{
  mmu->enabled = false;
  mmu->tlbpd0 = 0;
  mmu->tlbpd1 = 0;
  mmu->tlbpd1_hi = 0;
  mmu->tlbindex = 0;
  mmu->scratch_data0 = 0;
}
