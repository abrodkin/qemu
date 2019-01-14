/*
 * QEMU ARC CPU
 *
 * Copyright (c) 2018 Cupertino Miranda
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
#include "qemu/error-report.h"
#include "cpu.h"
#include "exec/helper-proto.h"
#include "exec/ioport.h"
#include "translate-all.h"
#include "arc-regs.h"
#include "mmu.h"
#include "hw/arc/cpudevs.h"
#include "qemu/main-loop.h"
#include "irq.h"

static uint32_t get_status32_internal (status_t *status_r)
{
  uint32_t res = 0x00000000;

  res |= (status_r->IEf & 0x1) << 31;
  res |= (status_r->USf & 0x1) << 20;
  res |= (status_r->ADf & 0x1) << 19;
  res |= (status_r->RBf & 0x7) << 16;
  res |= (status_r->ESf & 0x1) << 15;
  res |= (status_r->SCf & 0x1) << 14;
  res |= (status_r->DZf & 0x1) << 13;
  res |= (status_r->Lf  & 0x1) << 12;
  res |= (status_r->Zf  & 0x1) << 11;
  res |= (status_r->Nf  & 0x1) << 10;
  res |= (status_r->Cf  & 0x1) << 9;
  res |= (status_r->Vf  & 0x1) << 8;
  res |= (status_r->Uf  & 0x1) << 7;
  res |= (status_r->DEf & 0x1) << 6;
  res |= (status_r->AEf & 0x1) << 5;
  res |= (status_r->Ef  & 0xf) << 1;

  return res;
}

static uint32_t get_status32 (CPUARCState *env)
{
  uint32_t res = 0x00000000;

  res = get_status32_internal (&env->stat);

  if (env->stopped)
    res |= BIT(0);

  return res;
}

void helper_print_value(CPUARCState *env, target_ulong value)
{
  //printf("        Argument is %08x at address %08x\n", value, env->pc);
}

static void set_status32(CPUARCState *env, target_ulong value)
{
  //printf("        Status 32 was and set at %08x (%08x => ", env->pc, get_status32_internal(&(env->stat)));

  env->stat.IEf = ((value >> 31) & 0x1);
  env->stat.USf = ((value >> 20) & 0x1);
  env->stat.ADf = ((value >> 19) & 0x1);
  env->stat.RBf = ((value >> 16) & 0x7);
  env->stat.ESf = ((value >> 15) & 0x1);
  env->stat.SCf = ((value >> 14) & 0x1);
  env->stat.DZf = ((value >> 13) & 0x1);
  env->stat.Lf  = ((value >> 12) & 0x1);
  env->stat.Zf  = ((value >> 11) & 0x1);
  env->stat.Nf  = ((value >> 10) & 0x1);
  env->stat.Cf  = ((value >> 9)  & 0x1);
  env->stat.Vf  = ((value >> 8)  & 0x1);
  env->stat.Uf  = ((value >> 7)  & 0x1);
  env->stat.DEf = ((value >> 6)  & 0x1);
  env->stat.AEf = ((value >> 5)  & 0x1);
  env->stat.Ef  = ((value >> 1)  & 0xf);
  //env->stat.Hf  = ((value >> 0)  & 0x1);

  //printf("%08x) register was (%08x)\n", get_status32_internal(&(env->stat)), value);
}


static uint32_t get_status32_l1 (CPUARCState *env)
{
  return get_status32_internal (&env->stat_l1);
}

static void
do_exception_no_delayslot (CPUARCState *env, uint32_t index, uint32_t causecode, uint32_t param)
{
  env->eret = env->pc;
  env->erbta = env->npc_helper;

  helper_raise_exception (env, index, causecode, param);
}

uint32_t helper_mmu_translate_read(CPUARCState *env, uint32_t vaddr)
{
  uint32_t ret = arc_mmu_translate(env, vaddr, MMU_MEM_READ);
  if((enum exception_code_list) env->mmu.exception.number != EXCP_NO_EXCEPTION)
  {
    env->efa = arc_mmu_page_address_for(vaddr);
    RAISE_MMU_EXCEPTION(env);
  }
  return ret;
}

uint32_t helper_mmu_translate_write(CPUARCState *env, uint32_t vaddr)
{
  uint32_t ret = arc_mmu_translate(env, vaddr, MMU_MEM_WRITE);
  if((enum exception_code_list) env->mmu.exception.number != EXCP_NO_EXCEPTION)
  {
    env->efa = arc_mmu_page_address_for(vaddr);
    RAISE_MMU_EXCEPTION(env);
  }
  return ret;
}

target_ulong helper_norm(CPUARCState *env, uint32_t src1)
{
  int i;
  int32_t tmp = (int32_t) src1;
  if(tmp == 0 || tmp == -1)
    return 0;
  for(i = 0; i <= 31; i++)
  {
    if((tmp >> i) == 0) break;
    if((tmp >> i) == -1) break;
  }
  return i;
}

target_ulong helper_normh(CPUARCState *env, uint32_t src1)
{
  int i;
  for(i = 0; i <= 15; i++)
  {
    if(src1 >> i == 0) break;
    if(src1 >> i == -1) break;
  }
  return i;
}

target_ulong helper_ffs(CPUARCState *env, uint32_t src)
{
  int i;
  if(src == 0)
    return 31;
  for(i = 0; i <= 31; i++)
    if(((src >> i) & 1) != 0)
      break;
  return i;
}

target_ulong helper_fls(CPUARCState *env, uint32_t src)
{
  int i;
  if(src == 0)
    return 0;

  for(i = 31; i >= 0; i--)
    if(((src >> i) & 1) != 0)
      break;
  return i;
}

static void
report_aux_reg_error(uint32_t aux)
{
  if (((aux >= ARC_BCR1_START) && (aux <= ARC_BCR1_END)) ||
      ((aux >= ARC_BCR2_START) && (aux <= ARC_BCR2_END)))
    {
      qemu_log_mask(LOG_UNIMP, "Undefined BCR 0x%03x\n", aux);
    }

  error_report("Undefined AUX register 0x%03x, aborting", aux);
  exit(EXIT_FAILURE);
}

void helper_sr(CPUARCState *env, uint32_t val, uint32_t aux)
{
  struct arc_aux_reg_detail *aux_reg_detail =
    arc_aux_reg_struct_for_address(aux, ARC_OPCODE_ARCv2HS);

  if(aux_reg_detail == NULL)
    report_aux_reg_error(aux);

  switch (aux_reg_detail->id)
    {
    case AUX_ID_lp_start:
      env->lps = val;
      break;

    case AUX_ID_lp_end:
      env->lpe = val;
      break;

    case AUX_ID_identity:
      break;

    case AUX_ID_debug:
      break;

    case AUX_ID_pc:
      /* FIXME! Raise illegal instruction.  */
      break;

    case AUX_ID_status32:
      //printf("Status 32 changed by aux_reg\n");
      set_status32(env, val);
      break;

    case AUX_ID_status32_l1:
      break;

    case AUX_ID_status32_l2:
      break;

    case AUX_ID_int_vector_base:
      env->intvec = val;
      break;

    case AUX_ID_aux_macmode:
      break;

    case AUX_ID_eret:
      env->eret = val;
      break;

    case AUX_ID_erbta:
      env->erbta = val;
      break;

    case AUX_ID_erstatus:
      break;

    case AUX_ID_ecr:
      env->ecr = val;
      break;

    case AUX_ID_bta:
      break;

    case AUX_ID_bta_l1:
      break;

    case AUX_ID_bta_l2:
      break;

    case AUX_ID_control0:
      if (env->timer_build & TB_T0)
        cpu_arc_control_set (env, 0, val);
      break;

    case AUX_ID_control1:
      if (env->timer_build & TB_T1)
        cpu_arc_control_set (env, 1, val);
      break;

    case AUX_ID_count0:
      if (env->timer_build & TB_T0)
        cpu_arc_count_set (env, 0, val);
      break;

    case AUX_ID_count1:
      if (env->timer_build & TB_T1)
        cpu_arc_count_set (env, 1, val);
      break;

    case AUX_ID_limit0:
      cpu_arc_store_limit (env, 0, val);
      break;

    case AUX_ID_limit1:
      cpu_arc_store_limit (env, 1, val);
      break;

    case AUX_ID_irq_build:
      break;

    case AUX_ID_aux_rtc_ctrl:
      arc_rtc_ctrl_set (env, val);
      break;

    default:
      if(aux_reg_detail->aux_reg->set_func != NULL)
        aux_reg_detail->aux_reg->set_func (aux_reg_detail, val, (void *) env);
      else {
	/* TODO: are lr and sr possible delayslot instructions ? */
        do_exception_no_delayslot(env, EXCP_INST_ERROR, 0, 0);
      }
      break;
    }
    cpu_outl(aux, val);
}

static target_ulong get_status(CPUARCState *env)
{
    target_ulong res = 0x00000000;

    res |= (env->stat.Zf) ? BIT(31) : 0;
    res |= (env->stat.Nf) ? BIT(30) : 0;
    res |= (env->stat.Cf) ? BIT(29) : 0;
    res |= (env->stat.Vf) ? BIT(28) : 0;
    res |= (env->stat.Ef) << 1;

    if (env->stopped)
      res |= BIT(25);

    res |= (env->r[63] >> 2) & 0x03ffffff;

    return res;
}

static target_ulong get_debug(CPUARCState *env)
{
  target_ulong res = 0x00000000;

  res |= (env->debug.LD) ? BIT(31) : 0;
  res |= (env->debug.SH) ? BIT(30) : 0;
  res |= (env->debug.BH) ? BIT(29) : 0;
  res |= (env->debug.UB) ? BIT(28) : 0;
  res |= (env->debug.ZZ) ? BIT(27) : 0;
  res |= (env->debug.RA) ? BIT(22) : 0;
  res |= (env->debug.IS) ? BIT(11) : 0;
  res |= (env->debug.FH) ? BIT(1)  : 0;
  res |= (env->debug.SS) ? BIT(0)  : 0;

  return res;
}

static target_ulong get_identity(CPUARCState *env)
{
    target_ulong chipid = 0xffff, arcnum = 0, arcver, res;

    switch (env->family) {
	case ARC_OPCODE_ARC700: {
	    arcver = 0x34;
	} break;

	case ARC_OPCODE_ARCv2EM: {
	    arcver = 0x44;
	} break;

	case ARC_OPCODE_ARCv2HS: {
	    arcver = 0x54;
	} break;

	default: {
	    arcver = 0;
	}
    }

    // TODO: in SMP, arcnum depends on the cpu instance
    res = ((chipid & 0xFFFF) << 16) | ((arcnum & 0xFF) << 8) | (arcver & 0xFF);
    return res;
}

target_ulong helper_lr(CPUARCState *env, uint32_t aux)
{
  target_ulong result = 0;

  struct arc_aux_reg_detail *aux_reg_detail =
    arc_aux_reg_struct_for_address(aux, ARC_OPCODE_ARCv2HS);

  if(aux_reg_detail == NULL)
    report_aux_reg_error(aux);

  switch (aux_reg_detail->id)
    {
    case AUX_ID_status:
      result = get_status(env);
      break;

    case AUX_ID_aux_volatile:
      result = 0xc0000000;
      break;

    case AUX_ID_lp_start:
      result = env->lps;
      break;

    case AUX_ID_lp_end:
      result = env->lpe;
      break;

    case AUX_ID_identity:
      result = get_identity(env);
      break;

    case AUX_ID_exec_ctrl:
      result = 0;
      break;

    case AUX_ID_debug:
      result = get_debug(env);
      break;

    case AUX_ID_pc:
      result = env->pc & 0xfffffffe;
      break;

    case AUX_ID_status32:
      result = get_status32(env);
      break;

    case AUX_ID_status32_l1:
      result = get_status32_l1(env);
      break;

    case AUX_ID_int_vector_base:
      result = env->intvec;
      break;

    case AUX_ID_aux_irq_lv12:
      break;

    case AUX_ID_aux_irq_lev:
      break;

    case AUX_ID_eret:
      result = env->eret;
      break;

    case AUX_ID_erbta:
      result = env->erbta;
      break;

    case AUX_ID_erstatus:
      result = get_status32_internal (&env->stat_er);
      break;

    case AUX_ID_ecr:
      result = env->ecr;
      break;

    case AUX_ID_efa:
      result = env->efa;
      break;

    case AUX_ID_bta:
      result = env->bta;
      break;

    case AUX_ID_bta_l1:
      result = env->bta_l1;
      break;

    case AUX_ID_bta_l2:
      result = env->bta_l2;
      break;

    case AUX_ID_control0:
      result = env->timer[0].T_Cntrl;
      break;

    case AUX_ID_control1:
      result = env->timer[1].T_Cntrl;
      break;

    case AUX_ID_count0:
      result = cpu_arc_count_get (env, 0);
      break;

    case AUX_ID_count1:
      result = cpu_arc_count_get (env, 1);
      break;

    case AUX_ID_limit0:
      result = env->timer[0].T_Limit;
      break;

    case AUX_ID_limit1:
      result = env->timer[1].T_Limit;
      break;

    case AUX_ID_timer_build:
      result = env->timer_build;
      break;

    case AUX_ID_irq_build:
      result = env->irq_build;
      break;

    case AUX_ID_aux_rtc_low:
      result = arc_rtc_count_get (env, true);
      break;

    case AUX_ID_aux_rtc_high:
      result = arc_rtc_count_get (env, false);
      break;

    case AUX_ID_aux_rtc_ctrl:
      result = env->aux_rtc_ctrl;
      break;

    default:
      if(aux_reg_detail->aux_reg->get_func != NULL)
	result = aux_reg_detail->aux_reg->get_func (aux_reg_detail, (void *) env);
      else {
	/* TODO: is lr and sr possible delayslot instructions ? */
        do_exception_no_delayslot(env, EXCP_INST_ERROR, 0, 0);
      }
      break;
    }

  return  result;
}

void helper_halt(CPUARCState *env)
{
    /* TODO: implement */
}

void helper_rtie (CPUARCState *env)
{
  if (env->stat.AEf || (env->aux_irq_act & 0xFFFF) == 0)
    {
      assert (env->stat.Uf == 0);
      CPU_PCL(env) = env->eret;
      env->stat = env->stat_er;
      env->bta = env->erbta;

      /* If returning to userland, restore SP.  */
      if (env->stat.Uf)
        switchSP (env);

      /*FXME! bank selection if needed.  */
      qemu_log_mask(CPU_LOG_INT, "[IRQ] return from exception 0x%08x\n", env->r[63]);
    }
  else
    arc_rtie_interrupts (env);

  qemu_log_mask(CPU_LOG_INT, "[IRQ] RTIE:0x%08x\n", env->r[63]);
}

void helper_flush(CPUARCState *env)
{
  tb_flush((CPUState *)arc_env_get_cpu(env));
}

/* This should only be called from translate, via gen_raise_exception.
   We expect that ENV->PC has already been updated.  */

void QEMU_NORETURN
helper_raise_exception (CPUARCState *env,
			uint32_t index,
			uint32_t causecode,
			uint32_t param)
{
  CPUState *cs = CPU (arc_env_get_cpu(env));
  cs->exception_index = index;
  env->causecode = causecode;
  env->param = param;
  cpu_loop_exit(cs);
}

uint32_t helper_get_status32(CPUARCState *env)
{
  return get_status32(env);
}

void helper_set_status32(CPUARCState *env, uint32_t value)
{
  set_status32(env, value);
}

uint32_t helper_overflow_add_flag(uint32_t dest, uint32_t b, uint32_t c)
{
  dest >>= 31;
  b >>= 31;
  c >>= 31;
  if((dest == 0 && b == 1 && c == 1)
     || (dest == 1 && b == 0 && c == 0))
    return 1;
  else
    return 0;
}

uint32_t helper_overflow_sub_flag(uint32_t dest, uint32_t b, uint32_t c)
{
  dest >>= 31;
  b >>= 31;
  c >>= 31;
  if((dest == 1 && b == 0 && c == 1)
     || (dest == 0 && b == 1 && c == 0))
    return 1;
  else
    return 0;
}

uint32_t helper_mpymu(CPUARCState *env, uint32_t b, uint32_t c)
{
  uint64_t _b = (uint64_t) b;
  uint64_t _c = (uint64_t) c;

  return (uint32_t) ((_b * _c) >> 32);
}

uint32_t helper_mpym(CPUARCState *env, uint32_t b, uint32_t c)
{
  int64_t _b = (int64_t) ((int32_t) b);
  int64_t _c = (int64_t) ((int32_t) c);

//  fprintf(stderr, "B = 0x%llx, C = 0x%llx, result = 0x%llx\n", _b, _c, _b * _c);
  return ((_b * _c) >> 32);
}

uint32_t lf_variable = 0;
uint32_t helper_get_lf(void)
{
  return lf_variable;
}
void helper_set_lf(uint32_t v)
{
  lf_variable = v;
}

/* Local variables:
   eval: (c-set-style "gnu")
   indent-tabs-mode: t
   End:  */
