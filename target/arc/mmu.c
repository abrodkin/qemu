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

uint32_t
arc_mmu_aux_get(struct arc_aux_reg_detail *aux_reg_detail, void *data)
{
  CPUARCState *env = (CPUARCState *) data;
  struct arc_mmu *mmu = &env->mmu;
  uint32_t reg = 0;

  switch (aux_reg_detail->id) {
      case AUX_ID_mmu_build:
        // For now hardcode the TLB geometry and canonical page sizes
        // MMUv4: 2M Super Page, 8k Page, 4 way set associative, 1K entries (256x4), 4 uITLB, 8 uDTLB
        reg = 0x04e21a4a;
        break;
      case AUX_ID_tlbindex:
        reg = mmu->tlbindex;
        break;
      case AUX_ID_tlbpd0:
        reg = mmu->tlbpd0;
        break;
      case AUX_ID_tlbpd1:
        reg = mmu->tlbpd1;
        break;
      case AUX_ID_tlbpd1_hi:
        reg = mmu->tlbpd1_hi;
        break;
      case AUX_ID_scratch_data0:
        reg = mmu->scratch_data0;
        break;
      case AUX_ID_tlbcommand:
        reg = mmu->tlbcmd;
        break;
      case AUX_ID_pid:
        reg = (mmu->enabled << 31) | mmu->pid_asid;
	break;
      case AUX_ID_sasid0:
        reg = mmu->sasid0;
	break;
      case AUX_ID_sasid1:
        reg = mmu->sasid1;
	break;
      default:
        break;
  }

  return reg;
}

void
arc_mmu_aux_set(struct arc_aux_reg_detail *aux_reg_detail,
		uint32_t val, void *data)
{
  CPUARCState *env = (CPUARCState *) data;
  struct arc_mmu *mmu = &env->mmu;

  switch (aux_reg_detail->id) {
      /* AUX_ID_tlbcommand is more involved and handled seperately */
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
      case AUX_ID_pid:
        mmu->enabled = (val >> 31);
        mmu->pid_asid = val & 0xff;
        break;
      case AUX_ID_sasid0:
        mmu->sasid0 = val;
        break;
      case AUX_ID_sasid1:
        mmu->sasid1 = val;
        break;
      default:
        break;
  }
}

#define VPN(addr) ((addr & PAGE_MASK) & ~0x10000000)
#define PFN(addr) (addr & PAGE_MASK)

static struct arc_tlb_e *
arc_mmu_create_tlb_entry()
{
  struct arc_tlb_e *ret = (struct arc_tlb_e *) malloc(sizeof(struct arc_tlb_e));
  ret->next = NULL;
  return ret;
}

static struct arc_tlb_e *
arc_mmu_lookup_tlb(uint32_t vaddr, struct arc_mmu *mmu)
{
  uint32_t set = (vaddr >> PAGE_SHIFT) & (N_SETS - 1);
  struct arc_tlb_e *tlb = mmu->nTLB[set];
  while(tlb)
    {
      if(VPN(vaddr) == VPN(tlb->vpn))
	return tlb;
      tlb = tlb->next;
    }
  return NULL;
}

/*
 * TLB Insert/Delete triggered by writing the cmd to TLBCommand Aux
 *  - Requires PD0 and PD1 be setup apriori
 */
void
arc_mmu_aux_set_tlbcmd(struct arc_aux_reg_detail *aux_reg_detail,
		       uint32_t val, void *data)
{
  CPUARCState *env = (CPUARCState *) data;
  struct arc_mmu *mmu = &env->mmu;
  uint32_t pd0 = mmu->tlbpd0;
  uint32_t pd1 = mmu->tlbpd1;

  mmu->tlbcmd = val;

  if (val == TLB_CMD_INSERT) {
	struct arc_tlb_e *tlb = arc_mmu_create_tlb_entry();


        tlb->flags = (pd0 & PD0_FLG) | (pd1 & PD1_FLG);
        tlb->asid = (pd0 & 0xff);
        tlb->vpn = VPN(pd0);   // vaddr can't have top bit
        tlb->pfn = PFN(pd1);

	/* Find the SET for this tlb entry and add it. */
	uint32_t set = (pd0 >> PAGE_SHIFT) & (N_SETS - 1);
	tlb->next = mmu->nTLB[set];
	mmu->nTLB[set] = tlb;
  }
}

/* Function to verify if we have permission to use MMU TLB entry. */
static bool
arc_mmu_have_permission(CPUARCState *env,
			struct arc_tlb_e *tlb,
			enum access_type type)
{
  bool ret = false;
  bool in_kernel_mode = !env->stat.Uf; /* Read status for user mode. */
  switch(type) {
    case MMU_MEM_READ:
      ret = in_kernel_mode ? tlb->flags & PD1_RK : tlb->flags & PD1_RU;
      break;
    case MMU_MEM_WRITE:
      ret = in_kernel_mode ? tlb->flags & PD1_WK : tlb->flags & PD1_WU;
      break;
    case MMU_MEM_FETCH:
      ret = in_kernel_mode ? tlb->flags & PD1_XK : tlb->flags & PD1_XU;
      break;
  }
  return ret;
}

/* Translation function to get physical address from virtual address. */
target_ulong
arc_mmu_translate(CPUARCState *env,
		  target_ulong vaddr, enum access_type rwe)
{
  struct arc_mmu *mmu = &env->mmu;
  struct arc_tlb_e *tlb = arc_mmu_lookup_tlb(vaddr, mmu);
  /* TODO: HW validation. Check for multiple matches in nTLB. */

  bool match = true;

  /* Check that we are not addressing an address above 0x80000000.
   * Return the same address in that case. */
  if((vaddr & 0x80000000) != 0 || mmu->enabled != true)
    return vaddr;

  if(tlb == NULL)
    {
      /* TODO: TLB Miss exception */
      return 0;
    }

  /* Check if entry if related to this address */
  if(VPN(vaddr) != tlb->vpn || (tlb->flags & PD0_V) != 0)
    {
      /* Call the interrupt. */
      match = false;
    }

  /* In case entry is not global.
   * Logic from PRM, in TLBPD0 description, more precisely ASID one. */
  if((tlb->flags & PD0_G) == 0)
    {
      /* ASID check against library.  */
      if((tlb->flags & PD0_S) != 0
	 && (tlb->asid & 0x1f) != (mmu->pid_asid & 0x1f))
      {
        match = false;
      } else {
        /* Check if ASID matches with PID. */
        if(mmu->pid_asid != tlb->asid)
          {
            match = false;
          }
      }
    }

  if(!arc_mmu_have_permission(env, tlb, rwe))
    {
      /* TODO: Protection Violation exception. */
      return 0;
    }

  if(match == true)
    return tlb->pfn | (vaddr & (~PAGE_MASK));
  else
    {
      /* TODO: TLB Miss Exception. */
      return 0;
    }
}

void arc_mmu_init(struct arc_mmu *mmu)
{
  mmu->enabled = 0;
  mmu->pid_asid = 0;
  mmu->sasid0 = 0;
  mmu->sasid1 = 0;

  mmu->tlbpd0 = 0;
  mmu->tlbpd1 = 0;
  mmu->tlbpd1_hi = 0;
  mmu->tlbindex = 0;
  mmu->tlbcmd = 0;
  mmu->scratch_data0 = 0;

  for(int i = 0; i < N_SETS; i++)
    mmu->nTLB[i] = NULL;
}

