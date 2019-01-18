/*
 *  QEMU ARC CPU
 *
 *  Copyright (c) 2019
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
#include "arc-decoder.h"

TCGv
arc_gen_verifyCCFlag(DisasCtxt *ctx)
{
  TCGv ret = tcg_temp_local_new_i32();
  TCGv c1 = tcg_temp_local_new_i32();

  TCGv nZ = tcg_temp_local_new_i32();
  TCGv nN = tcg_temp_local_new_i32();
  TCGv nV = tcg_temp_local_new_i32();
  TCGv nC = tcg_temp_local_new_i32();

  switch(ctx->insn.cc)
    {
      // AL, RA
      case 0x00:
	tcg_gen_movi_i32(ret, 1);
	break;
      // EQ, Z
      case 0x01:
	tcg_gen_mov_i32(ret, cpu_Zf);
	break;
      // NE, NZ
      case 0x02:
	tcg_gen_xori_tl(ret, cpu_Zf, 1);
	break;
      // PL, P
      case 0x03:
	tcg_gen_xori_tl(ret, cpu_Nf, 1);
	break;
      // MI, N:
      case 0x04:
	tcg_gen_mov_i32(ret, cpu_Nf);
	break;
      // CS, C, LO
      case 0x05:
	tcg_gen_mov_i32(ret, cpu_Cf);
	break;
      // CC, NC, HS
      case 0x06:
	tcg_gen_xori_tl(ret, cpu_Cf, 1);
	break;
      // VS, V
      case 0x07:
	tcg_gen_mov_i32(ret, cpu_Vf);
	break;
      // VC, NV
      case 0x08:
	tcg_gen_xori_tl(ret, cpu_Vf, 1);
	break;
      // GT
      case 0x09:
	//(N & V & !Z) | (!N & !V & !Z)
	tcg_gen_xori_tl(nZ, cpu_Zf, 1);
	tcg_gen_xori_tl(nN, cpu_Nf, 1);
	tcg_gen_xori_tl(nV, cpu_Vf, 1);

	tcg_gen_mov_tl(c1, cpu_Nf);
	tcg_gen_and_tl(c1, c1, cpu_Vf);
	tcg_gen_and_tl(c1, c1, nZ);

	tcg_gen_mov_tl(ret, nN);
	tcg_gen_and_tl(ret, ret, nV);
	tcg_gen_and_tl(ret, ret, nZ);

	tcg_gen_or_tl(ret, c1, ret);
	break;
      // GE
      case 0x0A:
	//(N & V) | (!N & !V)
	tcg_gen_xori_tl(nN, cpu_Nf, 1);
	tcg_gen_xori_tl(nV, cpu_Vf, 1);

	tcg_gen_and_tl(c1, cpu_Nf, cpu_Vf);

	tcg_gen_and_tl(ret, nN, nV);

	tcg_gen_or_tl(ret, c1, ret);
	break;
      // LT
      case 0x0B:
	//(N & !V) | (!N & V)
	tcg_gen_xori_tl(nN, cpu_Nf, 1);
	tcg_gen_xori_tl(nV, cpu_Vf, 1);

	tcg_gen_and_tl(c1, cpu_Nf, nV);

	tcg_gen_and_tl(ret, nN, cpu_Vf);

	tcg_gen_or_tl(ret, ret, c1);
	break;
      // LE
      case 0x0C:
	// Z | (N & !V) | (!N & V)
	tcg_gen_xori_tl(nN, cpu_Nf, 1);
	tcg_gen_xori_tl(nV, cpu_Vf, 1);

	tcg_gen_and_tl(c1, cpu_Nf, nV);

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
      // PNZ
      case 0x0F:
	// !N & !Z
	tcg_gen_xori_tl(nN, cpu_Nf, 1);
	tcg_gen_xori_tl(nZ, cpu_Zf, 1);

	tcg_gen_and_tl(ret, nN, nZ);
	break;
    }

  tcg_temp_free_i32(c1);
  tcg_temp_free_i32(nZ);
  tcg_temp_free_i32(nN);
  tcg_temp_free_i32(nV);
  tcg_temp_free_i32(nC);

  return ret;
}

TCGv
arc_gen_getMSB(DisasCtxt *ctx, TCGv src)
{
  TCGv ret = tcg_temp_local_new_i32();

  tcg_gen_shri_tl(ret, src, 31);

  return ret;
}

void
arc2_gen_setCarry(TCGv elem)
{
  // TODO: Check type of elem and set sign bit accordingly.
  tcg_gen_mov_tl(cpu_Cf, elem);
}

TCGv
arc_gen_getCarry(DisasCtxt *ctx)
{
  TCGv ret = tcg_temp_local_new_i32();
  tcg_gen_mov_tl(ret, cpu_Cf);
  return ret;
}

TCGv
arc_gen_verifyFFlag(DisasCtxt *ctx)
{
  return tcg_const_i32 ((int) ctx->insn.f != 0);
}

TCGv
to_implement(DisasCtxt *ctx)
{
  abort();
  return ctx->zero;
}



TCGv
to_implement_wo_abort(DisasCtxt *ctx)
{
  return ctx->zero;
}

void
no_semantics(DisasCtxt *ctx)
{
  return;
}

void
arc2_gen_set_memory (DisasCtxt *ctx, TCGv vaddr, int size, TCGv src, bool sign_extend)
{
  TCGv addr = tcg_temp_local_new_i32();

  tcg_gen_movi_tl (cpu_npc_helper, ctx->npc);
  gen_helper_mmu_translate_write(addr, cpu_env, vaddr);

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
  tcg_temp_free(addr);
}

TCGv
arc2_gen_get_memory (DisasCtxt *ctx, TCGv vaddr, int size, bool sign_extend)
{
  TCGv dest = tcg_temp_local_new_i32();
  TCGv addr = tcg_temp_local_new_i32();
  tcg_gen_movi_tl (cpu_npc_helper, ctx->npc);
  gen_helper_mmu_translate_read(addr, cpu_env, vaddr);

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

  tcg_temp_free(addr);
  return dest;
}

bool
arc2_get_flag_x (DisasCtxt *ctx)
{
  return ctx->insn.x;
}

int
arc2_get_flag_zz (DisasCtxt *ctx)
{
  return ctx->insn.zz;
}

int
arc2_get_flag_aa (DisasCtxt *ctx)
{
  return ctx->insn.aa;
}

TCGv
arc2_gen_sign_extend(DisasCtxt *ctx, TCGv value, int size)
{
  // NOTE: This is just a place holder.
  // Sign extension is already performed in getMemory and setMemory.
  return value;
}

TCGv
arc2_gen_no_further_loads_pending(DisasCtxt *ctx)
{
  return ctx->one;
}

void
arc2_gen_set_debug(DisasCtxt *ctx, bool value)
{
  // TODO: Could not find a reson to set this.
}

void
arc2_gen_execute_delayslot(DisasCtxt *ctx)
{
  static int in_delay_slot = false;
  if (ctx->insn.limm_p == 0 && !in_delay_slot)
    {
      in_delay_slot = true;
      uint32_t cpc = ctx->cpc;
      uint32_t pcl = ctx->pcl;
      insn_t insn = ctx->insn;

      ctx->cpc = ctx->npc;
      ctx->pcl = ctx->cpc & 0xfffffffc;

      ++ctx->ds;

      /* TODO: check for illegal instruction sequence */

      arc_decode (ctx);

      assert (ctx->bstate == BS_NONE);

      --ctx->ds;

      /* Make dpc(delay_slot next pc) become npc(next pc) of the delayslot
       * instruction.  */
      ctx->dpc = ctx->npc;

      /* Restore old values.  */
      ctx->cpc = cpc;
      ctx->pcl = pcl;
      ctx->insn = insn;
      ctx->bstate = BS_BRANCH_DS;
      in_delay_slot = false;
    }
  return;
}

bool
arc2_gen_should_execute_delayslot(DisasCtxt *ctx)
{
  return ctx->insn.d != 0;
  //TCGv ret = tcg_temp_local_new_i32();
  //tcg_gen_movi_tl(ret, ctx->insn.d != 0);
  //return ret;
}

void arc2_gen_setNFlag(TCGv elem)
{
  // TODO: Check type of elem and set sign bit accordingly.
  tcg_gen_shri_tl(cpu_Nf, elem, 31);
}
TCGv arc2_gen_getNFlag(void)
{
  return cpu_Nf;
}

void
arc2_gen_setVFlag(TCGv elem)
{
  // TODO: Check type of elem and set sign bit accordingly.
  tcg_gen_mov_tl(cpu_Vf, elem);
}

void
arc2_gen_set_zflag(TCGv elem)
{
  TCGv zero = tcg_const_local_i32 (0);
  tcg_gen_setcond_i32 (TCG_COND_EQ, cpu_Zf, elem, zero);
  tcg_temp_free_i32 (zero);
}


int
arc2_get_tcgv_value(TCGv elem)
{
  assert(0);
  return 0;
  //return GET_TCGV_I32(elem);
}

TCGv
arc2_get_next_insn_address_after_delayslot(DisasCtxt *ctx)
{
  return tcg_const_i32 (ctx->dpc);
}

TCGv
arc2_get_next_insn_address(DisasCtxt *ctx)
{
  return tcg_const_i32 (ctx->npc);
}

TCGv
arc2_gen_get_pcl(DisasCtxt *ctx)
{
  return tcg_const_i32 (ctx->pcl);
}

void
arc2_set_pc(DisasCtxt *ctx, TCGv new_pc)
{
  gen_goto_tb(ctx, 1, new_pc);
}

void
arc2_set_blink(DisasCtxt *ctx, TCGv blink_addr)
{
  tcg_gen_mov_i32(cpu_blink, blink_addr);
}

TCGv
arc2_gen_add_Cf(TCGv dest, TCGv src1, TCGv src2)
{
    TCGv t1 = tcg_temp_local_new_i32();
    TCGv t2 = tcg_temp_local_new_i32();
    TCGv t3 = tcg_temp_local_new_i32();
    TCGv ret = tcg_temp_local_new_i32();

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

//TCGv
//arc2_gen_add_Vf(TCGv dest, TCGv src1, TCGv src2)
//{
//    TCGv t1 = tcg_temp_local_new_i32();
//    TCGv t2 = tcg_temp_local_new_i32();
//    TCGv ret = tcg_temp_local_new_i32();
//
//    /*
//
//    src1 & src2 & ~dest | ~src1 & ~src2 & dest = (src1 ^ dest) & ~(src1 ^ src2)
//
//    */
//    tcg_gen_xor_tl(t1, src1, dest); /*  t1 = src1 ^ dest                    */
//    tcg_gen_xor_tl(t2, src1, src2); /*  t2 = src1 ^ src2                    */
//    tcg_gen_andc_tl(t1, t1, t2);    /*  t1 = (src1 ^ src2) & ~(src1 ^ src2) */
//
//    tcg_gen_shri_tl(ret, t1, 31);/*  Vf = t1(31)                         */
//
//    tcg_temp_free_i32(t2);
//    tcg_temp_free_i32(t1);
//
//    return ret;
//}
/* dest = T0 + T1. Compute C, N, V and Z flags */

TCGv
arc2_gen_add_Vf(TCGv_i32 dest, TCGv_i32 t0, TCGv_i32 t1)
{
  TCGv ret = tcg_temp_local_new_i32();
  gen_helper_overflow_add_flag(ret, dest, t0, t1);
  return ret;
  //  TCGv ret = tcg_temp_local_new_i32();
  //  TCGv_i32 tmp = tcg_temp_local_new_i32();

  //  tcg_gen_xor_i32(ret, cpu_Nf, t0);
  //  tcg_gen_xor_i32(tmp, t0, t1);
  //  tcg_gen_andc_i32(ret, ret, tmp);
  //  tcg_temp_free_i32(tmp);

  //  return ret;
}

/* dest = src1 - src2. Compute C, N, V and Z flags */
TCGv
arc2_gen_sub_Cf(TCGv dest, TCGv src1, TCGv src2)
{
  TCGv t1 = tcg_temp_local_new_i32();
  TCGv t2 = tcg_temp_local_new_i32();
  TCGv t3 = tcg_temp_local_new_i32();
  TCGv ret = tcg_temp_local_new_i32();

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

//TCGv
//arc2_gen_sub_Vf(TCGv dest, TCGv src1, TCGv src2)
//{
//    TCGv t1 = tcg_temp_local_new_i32();
//    TCGv t2 = tcg_temp_local_new_i32();
//    TCGv ret = tcg_temp_local_new_i32();
//
//    /*
//	t1 = src1 & ~src2 & ~dest
//	   | ~src1 & src2 & dest
//	   = (src1 ^ dest) & (src1 ^ dest)*/
//    tcg_gen_xor_tl(t1, src1, dest);
//    tcg_gen_xor_tl(t2, src1, src2);
//    tcg_gen_and_tl(t1, t1, t2);
//    tcg_gen_shri_tl(ret, t1, 31);/*  Vf = t1(31) */
//
//    tcg_temp_free_i32(t2);
//    tcg_temp_free_i32(t1);
//
//    return ret;
//}
/* dest = T0 - T1. Compute C, N, V and Z flags */
TCGv
arc2_gen_sub_Vf(TCGv_i32 dest, TCGv_i32 t0, TCGv_i32 t1)
{
  TCGv ret = tcg_temp_local_new_i32();
  gen_helper_overflow_sub_flag(ret, dest, t0, t1);
  return ret;
  //  TCGv ret = tcg_temp_local_new_i32();
  //  TCGv_i32 tmp = tcg_temp_local_new_i32();

  //  tcg_gen_xor_i32(ret, cpu_Nf, t0);
  //  tcg_gen_xor_i32(tmp, t0, t1);
  //  tcg_gen_and_i32(ret, ret, tmp);

  //  tcg_temp_free_i32(tmp);

  //  return ret;
}

TCGv
arc2_gen_unsigned_LT(TCGv b, TCGv c)
{
  TCGv ret = tcg_temp_local_new_i32();
  tcg_gen_setcond_i32(TCG_COND_LTU, ret, b, c);
  return ret;
}

TCGv
arc2_gen_unsigned_GE(TCGv b, TCGv c)
{
  TCGv ret = tcg_temp_local_new_i32();
  tcg_gen_setcond_i32(TCG_COND_GEU, ret, b, c);
  return ret;
}

TCGv
arc2_gen_logical_shift_right (TCGv b, TCGv c)
{
  TCGv ret = tcg_temp_local_new_i32();
  tcg_gen_shr_i32 (ret, b, c);
  return ret;
}

TCGv
arc2_gen_logical_shift_left (TCGv b, TCGv c)
{
  TCGv ret = tcg_temp_local_new_i32();
  tcg_gen_shl_i32 (ret, b, c);
  return ret;
}

TCGv
arc2_gen_arithmetic_shift_right (TCGv b, TCGv c)
{
  TCGv ret = tcg_temp_local_new_i32();
  tcg_gen_sar_i32 (ret, b, c);
  return ret;
}

TCGv
arc2_gen_rotate_left (TCGv b, TCGv c)
{
  TCGv ret = tcg_temp_local_new_i32();
  tcg_gen_rotl_i32 (ret, b, c);
  return ret;
}

TCGv
arc2_gen_rotate_right (TCGv b, TCGv c)
{
  TCGv ret = tcg_temp_local_new_i32();
  tcg_gen_rotr_i32 (ret, b, c);
  return ret;
}

TCGv
arc2_gen_get_bit (TCGv a, TCGv pos)
{
  TCGv ret = tcg_temp_local_new_i32();
  tcg_gen_rotr_i32 (ret, a, pos);
  tcg_gen_andi_tl(ret, ret, 1);
  return ret;
}

TCGv
arc2_gen_get_aux_reg_index(enum arc_registers reg_id)
{
  return tcg_const_i32 ((int) reg_id);
}

TCGv
arc2_gen_read_aux_reg (TCGv reg_id)
{
  TCGv ret = tcg_temp_local_new_i32();
  gen_helper_lr(ret, cpu_env, reg_id);
  return ret;
}

void
arc2_gen_write_aux_reg (TCGv reg_id, TCGv b)
{
  gen_helper_sr(cpu_env, b, reg_id);
}


void
tcg_gen_shlfi_i32(TCGv a, int b, TCGv c)
{
  TCGv tmp = tcg_temp_local_new_i32();
  tcg_gen_movi_i32 (tmp, b);
  tcg_gen_shl_i32 (a, tmp, c);
  tcg_temp_free (tmp);
}


/* accumulator += b32 * c32 */
TCGv
arc2_gen_mac(TCGv_i32 b32, TCGv_i32 c32)
{
  TCGv_i32 plo = tcg_temp_new_i32();
  TCGv_i32 phi = tcg_temp_local_new_i32();
  tcg_gen_muls2_i32(plo, phi, b32, c32);

  /* adding the product to the accumulator */
  tcg_gen_add2_i32(cpu_acclo, cpu_acchi, cpu_acclo, cpu_acchi, plo, phi);
  tcg_temp_free(plo);

  /* return the high_part of multiplication ==> used for overflow detection */
  return phi;
}


/* unsigned version */
TCGv
arc2_gen_macu(TCGv_i32 b32, TCGv_i32 c32)
{
  TCGv_i32 plo = tcg_temp_new_i32();
  TCGv_i32 phi = tcg_temp_local_new_i32();
  tcg_gen_mulu2_i32(plo, phi, b32, c32);

  /* adding the product to the accumulator */
  tcg_gen_add2_i32(cpu_acclo, cpu_acchi, cpu_acclo, cpu_acchi, plo, phi);
  tcg_temp_free(plo);

  /* return the high_part of multiplication ==> used for overflow detection */
  return phi;
}



TCGv
arc2_gen_extract_bits (TCGv a, TCGv start, TCGv end)
{
  TCGv ret = tcg_temp_local_new_i32();

  TCGv tmp1 = tcg_temp_local_new_i32();

  tcg_gen_shr_i32 (ret, a, end);

  tcg_gen_sub_i32 (tmp1, start, end);
  tcg_gen_addi_i32 (tmp1, tmp1, 1);
  tcg_gen_shlfi_i32 (tmp1, 1, tmp1);
  tcg_gen_subi_i32 (tmp1, tmp1, 1);

  tcg_gen_and_i32 (ret, ret, tmp1);

  tcg_temp_free (tmp1);
  return ret;
}


TCGv
arc2_gen_get_register(enum arc_registers reg)
{
  TCGv ret = tcg_temp_local_new_i32();
  switch(reg)
  {
    case R_SP:
      tcg_gen_mov_i32 (ret, cpu_sp);
      break;
    case R_STATUS32:
      gen_helper_get_status32(ret, cpu_env);
      break;
    case R_ACCLO:
      tcg_gen_mov_i32(ret, cpu_acclo);
      break;
    case R_ACCHI:
      tcg_gen_mov_i32(ret, cpu_acchi);
      break;
    default:
      assert(!"Should not be reached");
  }
  return ret;
}
void
arc2_gen_set_register(enum arc_registers reg, TCGv value)
{
  switch(reg)
  {
    case R_SP:
      tcg_gen_mov_i32 (cpu_sp, value);
      break;
    case R_STATUS32:
      gen_helper_set_status32(cpu_env, value);
      break;
    case R_ACCLO:
      tcg_gen_mov_i32(cpu_acclo, value);
      break;
    case R_ACCHI:
      tcg_gen_mov_i32(cpu_acchi, value);
      break;
    default:
      assert(!"Should not be reached");
  }
}

TCGv
arc2_gen_next_reg(TCGv reg)
{
  int i;
  for(i = 0; i < 64; i+= 2)
    if(reg == cpu_r[i])
      return cpu_r[i+1];
  assert(!"Should not reach here!");
}

bool
arc2_target_has_option(enum target_options option)
{
  /* TODO: Fill with meaningful cases. */
  switch(option) {
    case LL64_OPTION:
      return true;
      break;
    default:
      break;
  }
  return false;
}

bool arc_is_instruction_operand_a_register(DisasCtxt *ctx, int nop)
{
  assert (nop < ctx->insn.n_ops);
  operand_t operand = ctx->insn.operands[nop];

  return (operand.type & ARC_OPERAND_IR) != 0;
}

TCGv arc2_gen_div_signed(TCGv src1, TCGv src2)
{
  TCGv ret = tcg_temp_local_new_i32();
  tcg_gen_div_i32(ret, src1, src2);
  return ret;
}

TCGv arc2_gen_div_unsigned(TCGv src1, TCGv src2)
{
  TCGv ret = tcg_temp_local_new_i32();
  tcg_gen_divu_i32(ret, src1, src2);
  return ret;
}
TCGv arc2_gen_div_remaining_signed(TCGv src1, TCGv src2)
{
  TCGv ret = tcg_temp_local_new_i32();
  tcg_gen_rem_i32(ret, src1, src2);
  return ret;
}

TCGv arc2_gen_div_remaining_unsigned(TCGv src1, TCGv src2)
{
  TCGv ret = tcg_temp_local_new_i32();
  tcg_gen_remu_i32(ret, src1, src2);
  return ret;
}

/* TODO: Get this from props ... */
TCGv arc2_has_interrupts(DisasCtxt *ctx) {
  TCGv ret = tcg_temp_local_new_i32();
  tcg_gen_movi_i32(ret, 1);
  return ret;
}

TCGv arc2_gen_get_lf(void)
{
  TCGv ret = tcg_temp_local_new_i32();
  gen_helper_get_lf(ret);
  return ret;
}

void arc2_gen_set_lf(TCGv value)
{
  gen_helper_set_lf(value);
}
