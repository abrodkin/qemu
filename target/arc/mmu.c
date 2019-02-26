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
  CPUState *cs = CPU(arc_env_get_cpu(env));
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
	qemu_log_mask (CPU_LOG_MMU,
		       "[MMU] Writing PID_ASID with value 0x%08x at 0x%08x\n",
			val, env->pc);
        mmu->enabled = (val >> 31);
        mmu->pid_asid = val & 0xff;
	tlb_flush(cs);
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

// vaddr can't have top bit
#define VPN(addr) ((addr) & (PAGE_MASK & (~0x80000000)))
#define PFN(addr) ((addr) & PAGE_MASK)

void
arc_mmu_debug_tlb(CPUARCState *env)
{
  int i;

  for(i = 0; i < N_SETS; i++)
    {
      bool set_printed = false;
      int j;

      for(j = 0; j < N_WAYS; j++)
	{
	  struct arc_tlb_e *tlb = &env->mmu.nTLB[i][j];

	  if((tlb->pd0 & PD0_V) != 0)
	    {
	      if(set_printed == false)
	        {
		  printf("set %d\n", i);
		  set_printed = true;
		}
	  printf("  tlppd0: %08x: vaddr=\t%08x %s %s%s asid=%02x\n",
		 (unsigned int) tlb->pd0, (unsigned int) VPN(tlb->pd0),
		 (char *) ((tlb->pd0 & PD0_SZ) != 0 ? "sz1" : "sz0"),
		 (char *) ((tlb->pd0 & PD0_V) != 0 ? "V" : ""),
		 (char *) ((tlb->pd0 & PD0_G) != 0 ? "g" : ""),
		 tlb->pd0 & PD0_ASID);

	  printf("  tlppd1: %08x: paddr=\t%08x k:%s%s%s u:%s%s%s f:%s\n",
		 (unsigned int) tlb->pd1, (unsigned int) PFN(tlb->pd1),
		 (char *) ((tlb->pd1 & PD1_RK) != 0 ? "R" : "r"),
		 (char *) ((tlb->pd1 & PD1_WK) != 0 ? "W" : "w"),
		 (char *) ((tlb->pd1 & PD1_XK) != 0 ? "X" : "x"),
		 (char *) ((tlb->pd1 & PD1_RU) != 0 ? "R" : "r"),
		 (char *) ((tlb->pd1 & PD1_WU) != 0 ? "W" : "w"),
		 (char *) ((tlb->pd1 & PD1_XU) != 0 ? "X" : "x"),
		 (char *) ((tlb->pd1 & PD1_FC) != 0 ? "C" : "c"));
	    }
	}
    }
}

static struct arc_tlb_e *
arc_mmu_get_tlb_at_index(uint32_t index, struct arc_mmu *mmu)
{
  uint32_t set = index / 4;
  uint32_t bank = index % 4;
  return &mmu->nTLB[set][bank];
}

static struct arc_tlb_e *
arc_mmu_lookup_tlb(uint32_t vaddr, uint32_t compare_mask, struct arc_mmu *mmu, int *num_finds, uint32_t *index)
{
  struct arc_tlb_e *ret = NULL;
  uint32_t set = (vaddr >> PAGE_SHIFT) & (N_SETS - 1);
  struct arc_tlb_e *tlb = &mmu->nTLB[set][0];
  int w;

  if(num_finds != NULL)
    *num_finds = 0;

  bool general_match = true;
  for (w = 0; w < N_WAYS; w++, tlb++)
    {
      uint32_t match = vaddr & compare_mask;

      if((tlb->pd0 & PD0_G) == 0)
      {
	if((tlb->pd0 & PD0_S) != 0)
	  {
	    /* Match to a shared library. */
	    uint8_t position = tlb->pd0 & PD0_ASID_MATCH;
            uint32_t m1 = mmu->sasid0 & (1 << (position & (32-1)));
            uint32_t m2 = mmu->sasid1 & (1 << ((position-32) & (32-1)));
	    if(m1 == 0 && m2 == 0)
	      general_match = false;
	  } else {
	    /* Match to a process. */
	    match |= mmu->pid_asid & PD0_PID_MATCH;
	    compare_mask |= PD0_PID_MATCH;
	  }
      }

      if(match == (tlb->pd0 & compare_mask) && general_match)
      {
	ret = tlb;
	if(num_finds != NULL)
	  *num_finds += 1;
	if(index != NULL)
	  *index = (set << 2) + w;
      }
    }

  if(ret == NULL)
    {
      uint32_t way = mmu->way_sel[set];
      ret = &mmu->nTLB[set][way];

      // TODO: Replace by something more significant.
      if(index != NULL)
        *index = (set << 2) + way;

      mmu->way_sel[set] = (mmu->way_sel[set] + 1) & (N_WAYS - 1);
    }

  return ret;
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
  int num_finds = 4;
  uint32_t index;
  struct arc_tlb_e *tlb;

  mmu->tlbcmd = val;
  uint32_t matching_mask = (PD0_VPN | PD0_SZ | PD0_G | PD0_S | PD0_ASID);

  if((pd0 & PD0_G) != 0)
    matching_mask &= ~(PD0_S | PD0_ASID); /* When Global do not check for asid match */

  if (val == TLB_CMD_WRITE)
    {
      // TODO: Include index verification. We are always clearing the index as
      // we assume it is always valid.

      tlb = arc_mmu_get_tlb_at_index(mmu->tlbindex & TLBINDEX_INDEX, mmu);
      tlb->pd0 = mmu->tlbpd0;
      tlb->pd1 = mmu->tlbpd1;
    }
  if (val == TLB_CMD_READ)
    {
      // TODO: Include index verification. We are always clearing the index as
      // we assume it is always valid.

      tlb = arc_mmu_get_tlb_at_index(mmu->tlbindex & TLBINDEX_INDEX, mmu);
      mmu->tlbpd0 = tlb->pd0;
      mmu->tlbpd1 = tlb->pd1;

      mmu->tlbindex &= ~(TLBINDEX_E || TLBINDEX_RC);
    }
  if (val == TLB_CMD_DELETE || val == TLB_CMD_INSERT)
    {

      if((pd0 & PD0_G) != 0)
	matching_mask &= ~(PD0_S | PD0_ASID); /* When Global do not check for asid match */

      matching_mask &= (VPN(PD0_VPN) | (~PD0_VPN)) ;
      tlb = arc_mmu_lookup_tlb(pd0,
			       matching_mask | PD0_V,
			       &env->mmu, &num_finds, &index);

      if(num_finds == 0)
        {
          mmu->tlbindex = 0x80000000; /* No entry to delete */
        }
      else if(num_finds == 1)
        {
          mmu->tlbindex = index; /* Entry is deleted set index */
	  tlb->pd0 &= ~PD0_V;
	  num_finds--;
	  qemu_log_mask (CPU_LOG_MMU,
			 "[MMU] Delete at 0x%08x, pd0 = 0x%08x, pd1 = 0x%08x\n",
			  env->pc, pd0, pd1);
        }
      else
	{
          while(num_finds > 0)
	    {
	      tlb->pd0 &= ~PD0_V;
	      qemu_log_mask (CPU_LOG_MMU,
			     "[MMU] Delete at 0x%08x, pd0 = 0x%08x, pd1 = 0x%08x\n",
			     env->pc, pd0, pd1);
	      tlb = arc_mmu_lookup_tlb(pd0,
				       (VPN(PD0_VPN) | PD0_V | PD0_SZ | PD0_G | PD0_S),
				       mmu, &num_finds, NULL);
	    }
	}
    }

  if (val == TLB_CMD_INSERT)
    {
      if((pd0 & PD0_V) == 0)
	mmu->tlbindex = 0x80000000;
      else
	{
	  tlb->pd0 = pd0;
	  tlb->pd1 = pd1;

	  /* Set index for latest inserted element. */
	  mmu->tlbindex |= index;

	  /* TODO: More verifications needed. */

	   qemu_log_mask (CPU_LOG_MMU,
			  "[MMU] Insert at 0x%08x, PID = %d, VPN = 0x%08x, "
			  "PFN = 0x%08x, pd0 = 0x%08x, pd1 = 0x%08x\n",
			  env->pc,
			  pd0 & 0xff,
			  VPN(pd0), PFN(pd1),
			  pd0, pd1);
	}
  }

  assert(val == TLB_CMD_INSERT
	 || val == TLB_CMD_DELETE
	 || val == TLB_CMD_WRITE
	 || val == TLB_CMD_READ
	 );
}

/* Function to verify if we have permission to use MMU TLB entry. */
static bool
arc_mmu_have_permission(CPUARCState *env,
			struct arc_tlb_e *tlb,
			enum mmu_access_type type)
{
  bool ret = false;
  bool in_kernel_mode = !env->stat.Uf; /* Read status for user mode. */
  switch(type) {
      // TODO: Verify if this is correct
    case MMU_MEM_READ:
      ret = in_kernel_mode ? tlb->pd1 & PD1_RK : tlb->pd1 & PD1_RU;
      break;
    case MMU_MEM_WRITE:
      ret = in_kernel_mode ? tlb->pd1 & PD1_WK : tlb->pd1 & PD1_WU;
      //ret = in_kernel_mode ? true : tlb->pd1 & PD1_WU;
      break;
    case MMU_MEM_FETCH:
      ret = in_kernel_mode ? tlb->pd1 & PD1_XK : tlb->pd1 & PD1_XU;
      break;
    case MMU_MEM_ATTOMIC:
      ret = in_kernel_mode ? tlb->pd1 & PD1_RK : tlb->pd1 & PD1_RU;
      ret = ret & (in_kernel_mode ? tlb->pd1 & PD1_WK : tlb->pd1 & PD1_WU);
      break;
    case MMU_MEM_IRRELEVANT_TYPE:
      ret = true;
      break;
  }

  return ret;
}

#define SET_MMU_EXCEPTION(ENV, N, C, P) { \
  ENV->mmu.exception.number = N; \
  ENV->mmu.exception.causecode = C; \
  ENV->mmu.exception.parameter = P; \
}

/* Translation function to get physical address from virtual address. */
uint32_t
arc_mmu_translate(struct CPUARCState *env,
		  uint32_t vaddr, enum mmu_access_type rwe,
		  uint32_t *index)
{
  struct arc_mmu *mmu = &(env->mmu);
  int num_matching_tlb = 0;

  SET_MMU_EXCEPTION(env, EXCP_NO_EXCEPTION, 0, 0);

  if(env->stat.Uf == true && vaddr >= 0x80000000)
    goto protv_exception;

  /* Check that we are not addressing an address above 0x80000000.
   * Return the same address in that case. */
  if((vaddr >= 0x80000000) || mmu->enabled == false)
    return vaddr;

  if(rwe != MMU_MEM_IRRELEVANT_TYPE)
    qemu_log_mask (CPU_LOG_MMU, "[MMU] Translate at 0x%08x, vaddr 0x%08x, pid %d, rwe = %s\n",
		   env->pc, vaddr, mmu->pid_asid, RWE_STRING(rwe));

  uint32_t match_pd0 = (VPN(vaddr) | PD0_V);
  struct arc_tlb_e *tlb = arc_mmu_lookup_tlb(match_pd0,
					     (VPN(PD0_VPN) | PD0_V),
					     mmu,
					     &num_matching_tlb, index);

  /* Check for multiple matches in nTLB, and return machine check exception. */
  if(num_matching_tlb > 1)
  {
    qemu_log_mask (CPU_LOG_MMU, "[MMU] Machine Check exception. num_matching_tlb = %d\n",
		   num_matching_tlb);
    SET_MMU_EXCEPTION(env, EXCP_MACHINE_CHECK, 0x01, 0x00);
    return 0;
  }


  bool match = true;

  if(tlb == NULL)
    {
      goto tlb_miss_exception;
    }

  /* Check if entry if related to this address */
  if(VPN(vaddr) != VPN(tlb->pd0) || (tlb->pd0 & PD0_V) == 0)
    {
      /* Call the interrupt. */
      match = false;
    }

  /* In case entry is not global.
   * Logic from PRM, in TLBPD0 description, more precisely ASID one. */
  //if((tlb->pd0 & PD0_G) == 0 && rwe != MMU_MEM_IRRELEVANT_TYPE)
  //  {
  //    /* ASID check against library.  */
  //    if((tlb->pd0 & PD0_S) != 0
  //       && (tlb->pd0 & PD0_ASID_MATCH) != (mmu->sasid0 & PD0_ASID_MATCH))
  //    {
  //      match = false;
  //    } else {
  //      /* Check if ASID matches with PID. */
  //      if(mmu->pid_asid != (tlb->pd0 & PD0_PID_MATCH))
  //        {
  //          match = false;
  //        }
  //    }
  //  }

  if(match == true && !arc_mmu_have_permission(env, tlb, rwe))
    {
protv_exception:
      qemu_log_mask (CPU_LOG_MMU, "[MMU] ProtV exception at 0x%08x. rwe = %s, "
		     "tlb->pd0 = %08x, tlb->pd1 = %08x\n",
		     env->pc,
		     RWE_STRING(rwe),
		     tlb->pd0, tlb->pd1);
      SET_MMU_EXCEPTION(env, EXCP_PROTV, CAUSE_CODE(rwe), 0x08);
      return 0;
    }

  if(match == true) {
    if(rwe != MMU_MEM_IRRELEVANT_TYPE)
      qemu_log_mask (CPU_LOG_MMU, "[MMU] Translated to 0x%08x\n",
		     (tlb->pd1 & PAGE_MASK) | (vaddr & (~PAGE_MASK)));
//    assert(((tlb->pd1 & PAGE_MASK) | (vaddr & (~PAGE_MASK))) >= 0x80000000);
    return (tlb->pd1 & PAGE_MASK) | (vaddr & (~PAGE_MASK));
  }
  else
    {
tlb_miss_exception:
      if(rwe != MMU_MEM_IRRELEVANT_TYPE)
	{
	  if(mmu->sasid0 != 0 || mmu->sasid1 != 0)
	    assert(0);
	  else
	    mmu->tlbpd0 = (vaddr & (VPN(PD0_VPN))) | (mmu->pid_asid & PD0_ASID);
          if(rwe == MMU_MEM_FETCH)
	    {
              qemu_log_mask (CPU_LOG_MMU, "[MMU] TLB_MissI exception at 0x%08x. rwe = %s, "
			 "vaddr = %08x, tlb->pd0 = %08x, tlb->pd1 = %08x\n",
			 env->pc,
			 RWE_STRING(rwe),
			 vaddr, tlb->pd0, tlb->pd1);
	      SET_MMU_EXCEPTION(env, EXCP_TLB_MISS_I, 0x00, 0x00);
	    }
          else
	    {
              qemu_log_mask (CPU_LOG_MMU, "[MMU] TLB_MissD exception at 0x%08x. rwe = %s, "
			 "vaddr = %08x, tlb->pd0 = %08x, tlb->pd1 = %08x\n",
			 env->pc,
			 RWE_STRING(rwe),
			 vaddr, tlb->pd0, tlb->pd1);
	      SET_MMU_EXCEPTION(env, EXCP_TLB_MISS_D, CAUSE_CODE(rwe), 0x00);
	    }
	}
      else
	if(rwe != MMU_MEM_IRRELEVANT_TYPE)
	  qemu_log_mask (CPU_LOG_MMU, "[MMU] Failed to translate to 0x%08x\n",
			 vaddr);
      return 0;
    }
}

uint32_t arc_mmu_page_address_for(uint32_t vaddr)
{
  uint32_t ret = VPN(vaddr);
  if(vaddr >= 0x80000000)
    ret |= 0x80000000;
  return ret;
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

  memset(mmu->nTLB, 0, sizeof(mmu->nTLB));
}

static int
arc_mmu_get_prot_for_index(uint32_t index, CPUARCState *env)
{
  struct arc_tlb_e *tlb;
  int ret = 0;
  bool in_kernel_mode = !env->stat.Uf; /* Read status for user mode. */

  tlb = arc_mmu_get_tlb_at_index(
	  index,
	  &env->mmu);

  if((in_kernel_mode && (tlb->pd1 & PD1_RK) != 0)
     || (!in_kernel_mode && (tlb->pd1 & PD1_RU) != 0))
    ret |= PAGE_READ;

  if((in_kernel_mode && (tlb->pd1 & PD1_WK) != 0)
     || (!in_kernel_mode && (tlb->pd1 & PD1_WU) != 0))
    ret |= PAGE_WRITE;

  if((in_kernel_mode && (tlb->pd1 & PD1_XK) != 0)
     || (!in_kernel_mode && (tlb->pd1 & PD1_XU) != 0))
    ret |= PAGE_EXEC;

  return ret;
}

/* Softmmu support function for MMU. */
void tlb_fill(CPUState *cs, target_ulong vaddr, int size,
	      MMUAccessType access_type,
	      int mmu_idx, uintptr_t retaddr)
{
  int prot = 0;
  MemTxAttrs attrs = {};
  target_ulong page_size = TARGET_PAGE_SIZE;

  ARCCPU *cpu = ARC_CPU(cs);
  CPUARCState *env = &cpu->env;
  enum mmu_access_type rwe = (char) access_type;

  uint32_t paddr = vaddr;
  if(vaddr < 0x80000000 && env->mmu.enabled)
    {
      uint32_t index;
      paddr = arc_mmu_translate (env, vaddr, rwe, &index);
      if((enum exception_code_list) env->mmu.exception.number != EXCP_NO_EXCEPTION)
        {
          cpu_restore_state(cs, retaddr, true);
          env->efa = vaddr;
          env->eret = env->pc;
          env->erbta = env->npc_helper;

          cs->exception_index = env->mmu.exception.number;
          env->causecode = env->mmu.exception.causecode;
          env->param = env->mmu.exception.parameter;
          cpu_loop_exit (cs);
      }
      else
	prot = arc_mmu_get_prot_for_index(index, env);
    }
  else
    {
      if(env->stat.Uf != 1)
	prot = PAGE_READ | PAGE_WRITE | PAGE_EXEC;
      else
	{
          cpu_restore_state(cs, retaddr, true);
          env->efa = arc_mmu_page_address_for(vaddr);
          env->eret = env->pc;
          env->erbta = env->npc_helper;

          qemu_log_mask (CPU_LOG_MMU, "[MMU_TLB_FILL] ProtV "
			 "exception at 0x%08x. rwe = %s\n",
			 env->pc,
			 RWE_STRING(rwe));

          cs->exception_index = EXCP_PROTV;
          env->causecode = CAUSE_CODE(rwe);
          env->param = 0x08;
          cpu_loop_exit (cs);

      SET_MMU_EXCEPTION(env, EXCP_PROTV, CAUSE_CODE(rwe), 0x08);
	}

    }

  vaddr = arc_mmu_page_address_for(vaddr);
  paddr = (paddr & PAGE_MASK);
  tlb_set_page_with_attrs(cs, vaddr, paddr, attrs, prot, mmu_idx, page_size);
}
