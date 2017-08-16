/*
 *  QEMU ARC CPU
 *
 *  Copyright (c) 2016 Michael Rolnik
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR dest PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, see
 *  http://www.gnu.org/licenses/lgpl-2.1.html
 */

/*
    see http://me.bios.io/images/d/dd/ARCompactISA_ProgrammersReference.pdf
*/

#include "translate.h"
#include "qemu/bitops.h"
#include "tcg/tcg.h"
#include "translate-inst.h"

TCGv
arc_gen_verifyCCFlag(DisasCtxt *ctx)
{
  TCGv ret = tcg_temp_new_i32();

  TCGv nZ = tcg_temp_new_i32();
  TCGv nN = tcg_temp_new_i32();
  TCGv nV = tcg_temp_new_i32();
  TCGv nC = tcg_temp_new_i32();

  TCGv c1 = tcg_temp_new_i32();

  switch(ctx->insn.cc)
    {
      // AL, RA
      case 0x00:
	return ctx->one;
	break;
      // EQ, Z
      case 0x01:
	return cpu_Zf;
	break;
      // NE, NZ
      case 0x02:
	tcg_gen_xori_tl(ret, cpu_Zf, 1);
	return ret;
	break;
      // PL, P
      case 0x03:
	tcg_gen_xori_tl(ret, cpu_Nf, 1);
	return ret;
	break;
      // MI, N:
      case 0x04:
	return cpu_Nf;
	break;
      // CS, C, LO
      case 0x05:
	return cpu_Cf;
	break;
      // CC, NC, HS
      case 0x06:
	tcg_gen_xori_tl(ret, cpu_Cf, 1);
	return ret;
	break;
      // VS, V
      case 0x07:
	return cpu_Vf;
	break;
      // VC, NV
      case 0x08:
	tcg_gen_xori_tl(ret, cpu_Vf, 1);
	return ret;
	break;
      // GT
      case 0x09:
	//(N & V & !Z) | (!N & !V & !Z)
	tcg_gen_xori_tl(nZ, cpu_Zf, 1);
	tcg_gen_xori_tl(nN, cpu_Nf, 1);
	tcg_gen_xori_tl(nV, cpu_Vf, 1);

	TCGv c1 = tcg_temp_new_i32();
	tcg_gen_and_tl(ret, c1, cpu_Nf);
	tcg_gen_and_tl(ret, c1, cpu_Vf);
	tcg_gen_and_tl(ret, c1, nZ);

	tcg_gen_and_tl(ret, nN, nV);
	tcg_gen_and_tl(ret, ret, nZ);

	tcg_gen_or_tl(ret, ret, c1);
	break;
      // GE
      case 0x0A:
	//(N & V) | (!N & !V)
	tcg_gen_xori_tl(nN, cpu_Nf, 1);
	tcg_gen_xori_tl(nV, cpu_Vf, 1);

	tcg_gen_and_tl(ret, cpu_Nf, cpu_Vf);

	tcg_gen_and_tl(ret, nN, nV);

	tcg_gen_or_tl(ret, ret, c1);
	break;
      // LT
      case 0x0B:
	//(N & !V) | (!N & V)
	tcg_gen_xori_tl(nN, cpu_Nf, 1);
	tcg_gen_xori_tl(nV, cpu_Vf, 1);
	tcg_gen_and_tl(ret, cpu_Nf, nV);

	tcg_gen_and_tl(ret, nN, cpu_Vf);

	tcg_gen_or_tl(ret, ret, c1);
	break;
      // LE
      case 0x0C:
	// Z | (N & !V) | (!N & V)
	tcg_gen_xori_tl(nN, cpu_Nf, 1);
	tcg_gen_xori_tl(nV, cpu_Vf, 1);
	tcg_gen_and_tl(ret, cpu_Nf, nV);

	tcg_gen_and_tl(ret, nN, cpu_Vf);

	tcg_gen_or_tl(ret, ret, c1);

	tcg_gen_or_tl(ret, ret, cpu_Zf);
	break;
      // HI
      case 0x0D:
	// !C & !Z
	tcg_gen_xori_tl(nC, cpu_Cf, 1);
	tcg_gen_xori_tl(nZ, cpu_Zf, 1);

	tcg_gen_and_tl(ret, nC, nZ);
	break;
      // LS
      case 0x0E:
	// C & Z
	tcg_gen_or_tl(ret, cpu_Cf, cpu_Zf);
	break;
	break;
      // PNZ
      case 0x0F:
	// !N & !Z
	tcg_gen_xori_tl(nN, cpu_Nf, 1);
	tcg_gen_xori_tl(nZ, cpu_Zf, 1);

	tcg_gen_and_tl(ret, nN, nZ);
	break;
    }
  return ret;
}
#define getCCFlag() arc_gen_verifyCCFlag(ctx)


TCGv
arc_gen_getCarry(DisasCtxt *ctx)
{
  TCGv ret = tcg_temp_new_i32();
  tcg_gen_movi_tl(ret, ctx->env->stat.Cf != 0);
  return ret;
}
#define getCFlag() arc_gen_getCarry(ctx)

TCGv
arc_gen_verifyFFlag(DisasCtxt *ctx)
{
  TCGv ret = tcg_temp_new_i32();
  tcg_gen_movi_tl(ret, ctx->insn.f != 0);
  return ret;
}
#define getFFlag() arc_gen_verifyFFlag(ctx)

TCGv
to_implement(DisasCtxt *ctx)
{
  abort();
  return ctx->zero;
}

#define Carry(A) to_implement(ctx)
#define killDelaySlot() to_implement(ctx)


TCGv
to_implement_wo_abort(DisasCtxt *ctx)
{
  return ctx->zero;
}

TCGv
arc2_gen_set_memory (DisasCtxt *ctx, TCGv addr, int size, TCGv src, bool sign_extend)
{
  switch (size)
    {
      case 0x00:
	tcg_gen_qemu_st_tl(src, addr, ctx->memidx, MO_UL);
	break;

      case 0x01:
	if (sign_extend)
	  tcg_gen_qemu_st_tl(src, addr, ctx->memidx, MO_SB);
	else
	  tcg_gen_qemu_st_tl(src, addr, ctx->memidx, MO_UB);
	break;

      case 0x02:
	if (sign_extend)
	  tcg_gen_qemu_st_tl(src, addr, ctx->memidx, MO_SW);
	else
	  tcg_gen_qemu_st_tl(src, addr, ctx->memidx, MO_UW);
	break;

      case 0x03:
	assert(!"reserved");
	break;
    }
}
#define setMemory(ADDRESS, SIZE, VALUE) arc2_gen_set_memory (ctx, ADDRESS, SIZE, VALUE, getFlagX())

TCGv
arc2_gen_get_memory (DisasCtxt *ctx, TCGv addr, int size, bool sign_extend)
{
  TCGv dest = tcg_temp_new_i32();

  switch (size)
    {
      case 0x00:
	tcg_gen_qemu_ld_tl(dest, addr, ctx->memidx, MO_UL);
	break;

      case 0x01:
	if (sign_extend)
	  tcg_gen_qemu_ld_tl(dest, addr, ctx->memidx, MO_SB);
	else
	  tcg_gen_qemu_ld_tl(dest, addr, ctx->memidx, MO_UB);
	break;

      case 0x02:
	if (sign_extend)
	  tcg_gen_qemu_ld_tl(dest, addr, ctx->memidx, MO_SW);
	else
	  tcg_gen_qemu_ld_tl(dest, addr, ctx->memidx, MO_UW);
	break;

      case 0x03:
	assert(!"reserved");
	break;
    }
  return dest;
}
#define getMemory(ADDRESS, SIZE) arc2_gen_get_memory (ctx, ADDRESS, SIZE, getFlagX())

bool
arc2_get_flag_x (DisasCtxt *ctx)
{
  return ctx->insn.x;
}
#define getFlagX() arc2_get_flag_x (ctx)

int
arc2_get_flag_zz (DisasCtxt *ctx)
{
  return ctx->insn.zz;
}
#define getZZFlag() arc2_get_flag_zz (ctx)

int
arc2_get_flag_aa (DisasCtxt *ctx)
{
  return ctx->insn.aa;
}
#define getAAFlag() arc2_get_flag_aa (ctx)

TCGv
arc2_gen_sign_extend(DisasCtxt *ctx, TCGv value, int size)
{
  // NOTE: This is just a place holder.
  // Sign extension is already performed in getMemory and setMemory.
  return value;
}
#define SignExtend(VALUE, SIZE) arc2_gen_sign_extend (ctx, VALUE, SIZE)

TCGv
arc2_gen_no_further_loads_pending(DisasCtxt *ctx)
{
  return ctx->one;
}
#define NoFurtherLoadsPending() to_implement_wo_abort(ctx)

void
arc2_gen_set_debug(DisasCtxt *ctx, bool value)
{
  // TODO: Could not find a reson to set this.
}
#define setDebugLD(A) arc2_gen_set_debug(ctx, A)

void
arc2_gen_execute_delayslot(DisasCtxt *ctx)
{
  static int in_delay_slot = false;
  if (ctx->insn.limm_p == 0 && !in_delay_slot)
    {
      in_delay_slot = true;
      uint32_t cpc = ctx->cpc;
      uint32_t npc = ctx->npc;
      uint32_t dpc = ctx->dpc;
      uint32_t pcl = ctx->pcl;
      insn_t insn = ctx->insn;
      int bstate = ctx->bstate;

      ctx->cpc = ctx->npc;
      ctx->pcl = ctx->cpc & 0xfffffffc;

      ++ctx->ds;

      /* TODO: check for illegal instruction sequence */

      arc_decode (ctx);

      --ctx->ds;

      ctx->cpc = cpc;
      ctx->npc = npc;
      ctx->dpc = dpc;
      ctx->pcl = pcl;
      ctx->insn = insn;
      ctx->bstate = bstate;
      in_delay_slot = false;
    }
  return;
}
#define executeDelaySlot() arc2_gen_execute_delayslot(ctx)

bool
arc2_gen_should_execute_delayslot(DisasCtxt *ctx)
{
  return ctx->insn.d != 0;
  //TCGv ret = tcg_temp_new_i32();
  //tcg_gen_movi_tl(ret, ctx->insn.d != 0);
  //return ret;
}
#define shouldExecuteDelaySlot() arc2_gen_should_execute_delayslot(ctx)

static void arc2_gen_setNFlag(TCGv elem)
{
  // TODO: Check type of elem and set sign bit accordingly.
  tcg_gen_shri_tl(cpu_Nf, elem, 31);
}
#define setNFlag(ELEM) arc2_gen_setNFlag(ELEM)
static TCGv arc2_gen_getNFlag()
{
  return cpu_Nf;
}
#define getNFlag() arc2_gen_getNFlag()

static void arc2_gen_getCFlag(TCGv elem)
{
  // TODO: Check type of elem and set sign bit accordingly.
  tcg_gen_mov_tl(cpu_Cf, elem);
}
#define setCFlag(ELEM) arc2_gen_getCFlag(ELEM)

static void arc2_gen_getVFlag(TCGv elem)
{
  // TODO: Check type of elem and set sign bit accordingly.
  tcg_gen_mov_tl(cpu_Vf, elem);
}
#define setVFlag(ELEM) arc2_gen_getVFlag(ELEM)

static void
arc2_gen_set_zflag(int32_t elem)
{
  tcg_gen_movi_tl(cpu_Zf, elem);
}
#define setZFlag(ELEM) arc2_gen_set_zflag (ELEM)

static int
arc2_get_tcgv_value(TCGv elem)
{
  return GET_TCGV_I32(elem);
}

static TCGv
arc2_get_pc(DisasCtxt *ctx)
{
  return cpu_pc;
  //TCGv ret = tcg_temp_new_i32();
  //tcg_gen_mov_tl(ret, ctx->env->pc);
  //return ret;
}
#define getPC() arc2_get_pc(ctx)



static TCGv
arc2_get_next_insn_address_after_delayslot(DisasCtxt *ctx)
{
  TCGv ret = tcg_temp_new_i32();
  tcg_gen_mov_tl(ret, ctx->dpc);
  return ret;
}
#define nextInsnAddressAfterDelaySlot() arc2_get_next_insn_address_after_delayslot (ctx)

static TCGv
arc2_get_next_insn_address(DisasCtxt *ctx)
{
  TCGv ret = tcg_temp_new_i32();
  tcg_gen_mov_tl(ret, ctx->npc);
  return ret;
}
#define nextInsnAddress() arc2_get_next_insn_address (ctx)





static TCGv
arc2_gen_get_pcl(DisasCtxt *ctx)
{
  TCGv ret = tcg_temp_new_i32();
  tcg_gen_movi_tl(ret, ctx->pcl);
  return ret;
}
#define getPCL() arc2_gen_get_pcl(ctx)

static void
arc2_set_pc(DisasCtxt *ctx, TCGv new_pc)
{
  tcg_gen_mov_i32(cpu_pc, new_pc);
}
#define setPC(NEW_PC) \
  arc2_set_pc(ctx, NEW_PC); \
  ret = ret == BS_NONE ? BS_BRANCH : ret

static void
arc2_set_blink(DisasCtxt *ctx, TCGv blink_addr)
{
  tcg_gen_mov_i32(cpu_blink, blink_addr);
}
#define setBLINK(BLINK_ADDR) arc2_set_blink(ctx, BLINK_ADDR);

static TCGv
arc2_gen_add_Cf(TCGv dest, TCGv src1, TCGv src2)
{
    TCGv t1 = tcg_temp_new_i32();
    TCGv t2 = tcg_temp_new_i32();
    TCGv t3 = tcg_temp_new_i32();
    TCGv ret = tcg_temp_new_i32();

    tcg_gen_and_tl(t1, src1, src2); /*  t1 = src1 & src2                    */
    tcg_gen_andc_tl(t2, src1, dest);/*  t2 = src1 & ~dest                   */
    tcg_gen_andc_tl(t3, src2, dest);/*  t3 = src2 & ~dest                   */
    tcg_gen_or_tl(t1, t1, t2);      /*  t1 = t1 | t2 | t3                   */
    tcg_gen_or_tl(t1, t1, t3);

    tcg_gen_shri_tl(ret, t1, 31);/*  Cf = t1(31)                         */

    tcg_temp_free_i32(t3);
    tcg_temp_free_i32(t2);
    tcg_temp_free_i32(t1);

    return ret;
}
#define CarryADD(A, B, C) arc2_gen_add_Cf(A, B, C)

static TCGv arc2_gen_add_Vf(TCGv dest, TCGv src1, TCGv src2)
{
    TCGv t1 = tcg_temp_new_i32();
    TCGv t2 = tcg_temp_new_i32();
    TCGv ret = tcg_temp_new_i32();

    /*

    src1 & src2 & ~dest | ~src1 & ~src2 & dest = (src1 ^ dest) & ~(src1 ^ src2)

    */
    tcg_gen_xor_tl(t1, src1, dest); /*  t1 = src1 ^ dest                    */
    tcg_gen_xor_tl(t2, src1, src2); /*  t2 = src1 ^ src2                    */
    tcg_gen_andc_tl(t1, t1, t2);    /*  t1 = (src1 ^ src2) & ~(src1 ^ src2) */

    tcg_gen_shri_tl(ret, t1, 31);/*  Vf = t1(31)                         */

    tcg_temp_free_i32(t2);
    tcg_temp_free_i32(t1);

    return ret;
}
#define OverflowADD(A, B, C) arc2_gen_add_Vf(A, B, C)

static TCGv arc2_gen_sub_Cf(TCGv dest, TCGv src1, TCGv src2)
{
    TCGv t1 = tcg_temp_new_i32();
    TCGv t2 = tcg_temp_new_i32();
    TCGv t3 = tcg_temp_new_i32();
    TCGv ret = tcg_temp_new_i32();

    tcg_gen_not_tl(t1, src1);       /*  t1 = ~src1                          */
    tcg_gen_and_tl(t2, t1, src2);   /*  t2 = ~src1 & src2                   */
    tcg_gen_or_tl(t3, t1, src2);    /*  t3 = (~src1 | src2) & dest          */
    tcg_gen_and_tl(t3, t3, dest);
    tcg_gen_or_tl(t2, t2, t3);      /*  t2 = ~src1 & src2
                                           | ~src1 & dest
                                           | dest & src2                    */
    tcg_gen_shri_tl(ret, t2, 31);/*  Cf = t2(31)                         */

    tcg_temp_free_i32(t3);
    tcg_temp_free_i32(t2);
    tcg_temp_free_i32(t1);

    return ret;
}
#define CarrySUB(A, B, C) arc2_gen_sub_Cf(A, B, C)

static TCGv
arc2_gen_sub_Vf(TCGv dest, TCGv src1, TCGv src2)
{
    TCGv t1 = tcg_temp_new_i32();
    TCGv t2 = tcg_temp_new_i32();
    TCGv ret = tcg_temp_new_i32();

    /*
        t1 = src1 & ~src2 & ~dest
           | ~src1 & src2 & dest
           = (src1 ^ dest) & (src1 ^ dest)*/
    tcg_gen_xor_tl(t1, src1, dest);
    tcg_gen_xor_tl(t2, src1, src2);
    tcg_gen_and_tl(t1, t1, t2);
    tcg_gen_shri_tl(ret, t1, 31);/*  Vf = t1(31) */

    tcg_temp_free_i32(t2);
    tcg_temp_free_i32(t1);

    return ret;
}
#define OverflowSUB(A, B, C) arc2_gen_sub_Vf(A, B, C)

static TCGv
arc2_gen_unsigned_LT(TCGv b, TCGv c)
{
  TCGv ret = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_LTU, ret, b, c);
  return ret;
}
#define unsignedLT(B, C) arc2_gen_unsigned_LT (B, C)

static TCGv
arc2_gen_unsigned_GE(TCGv b, TCGv c)
{
  TCGv ret = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_GEU, ret, b, c);
  return ret;
}
#define unsignedGE(B, C) arc2_gen_unsigned_GE (B, c)

static TCGv
arc2_gen_logical_shift_right (TCGv b, TCGv c)
{
  TCGv ret = tcg_temp_new_i32();
  tcg_gen_sar_i32 (ret, b, c);
  return ret;
}
#define logicalShiftRight(B, C) \
  arc2_gen_logical_shift_right (B, C)

static TCGv
arc2_gen_logical_shift_left (TCGv b, TCGv c)
{
  TCGv ret = tcg_temp_new_i32();
  tcg_gen_shl_i32 (ret, b, c);
  return ret;
}
#define logicalShiftLeft(B, C) \
  arc2_gen_logical_shift_left (B, C)

static TCGv
arc2_gen_get_bit (TCGv a, TCGv pos)
{
  TCGv ret = tcg_temp_new_i32();
  tcg_gen_rotl_i32 (ret, a, pos);
  tcg_gen_andi_tl(ret, ret, 1);
  return ret;
}
#define getBit(A, POS) \
  arc2_gen_get_bit(A, POS)


static TCGv
arc2_gen_read_aux_reg (TCGv a)
{
  TCGv ret = tcg_temp_new_i32();
  gen_helper_lr(ret, cpu_env, a);
  return ret;
}
#define readAuxReg(A) \
  arc2_gen_read_aux_reg(A)

static void
arc2_gen_write_aux_reg (TCGv a, TCGv b)
{
  TCGv ret = tcg_temp_new_i32();
  gen_helper_sr(a, b);
}
#define writeAuxReg(A, B) \
  arc2_gen_write_aux_reg(A, B)


static void
tcg_gen_shlfi_i32(TCGv a, int b, TCGv c)
{
  TCGv tmp = tcg_temp_new_i32();
  tcg_gen_movi_i32 (tmp, b);
  tcg_gen_shl_i32 (a, tmp, c);
  tcg_temp_free (tmp);
}


static TCGv
arc2_gen_extract_bits (TCGv a, TCGv start, TCGv end)
{
  TCGv ret = tcg_temp_new_i32();

  TCGv tmp1 = tcg_temp_new_i32();

  tcg_gen_shr_i32 (ret, a, end);

  tcg_gen_sub_i32 (tmp1, start, end);
  tcg_gen_shlfi_i32 (tmp1, 1, tmp1);
  tcg_gen_subi_i32 (tmp1, tmp1, 1);

  tcg_gen_and_i32 (ret, ret, tmp1);

  tcg_temp_free (tmp1);
  return ret;
}
#define extractBits(ELEM, START, END) \
  arc2_gen_extract_bits(ELEM, START, END)


enum arc_registers {
  SP = 0,
};

static TCGv
arc2_gen_get_register(enum arc_registers reg)
{
  switch(reg)
  {
    case SP:
      return cpu_sp;
      break;
  }
}
#define getRegister(REG) \
  arc2_gen_get_register(REG)

static void
arc2_gen_set_register(enum arc_registers reg, TCGv value)
{
  switch(reg)
  {
    case SP:
      tcg_gen_mov_i32 (cpu_sp, value);
      break;
  }
}
#define setRegister(REG, VALUE) \
  arc2_gen_set_register(REG, VALUE)

#define Zero() (ctx->zero)

#undef true
#undef false
#define true (ctx->one)
#define false (ctx->zero)

#include "arc-semfunc1.h"
