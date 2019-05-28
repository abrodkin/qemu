/*
 *  QEMU ARC CPU
 *
 *  Copyright (c); 2016 Michael Rolnik
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option); any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR dest PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, see
 *  <<a  rel="nofollow" href="http://www.gnu.org/licenses/lgpl-2.1.html">http://www.gnu.org/licenses/lgpl-2.1.html</a>>
 */

#ifndef __TRANSLATE_INST_H__
#define __TRANSLATE_INST_H__

#include "translate.h"
#include "qemu/bitops.h"
#include "tcg/tcg.h"
#include "arc-regs.h"

typedef enum ARC_COND {
    ARC_COND_AL      = 0x00,
    ARC_COND_RA      = 0x00,
    ARC_COND_EQ      = 0x01,
    ARC_COND_Z       = 0x01,
    ARC_COND_NE      = 0x02,
    ARC_COND_NZ      = 0x02,
    ARC_COND_PL      = 0x03,
    ARC_COND_P       = 0x03,
    ARC_COND_MI      = 0x04,
    ARC_COND_N       = 0x04,
    ARC_COND_CS      = 0x05,
    ARC_COND_C       = 0x05,
    ARC_COND_LO      = 0x05,
    ARC_COND_CC      = 0x06,
    ARC_COND_NC      = 0x06,
    ARC_COND_HS      = 0x06,
    ARC_COND_VS      = 0x07,
    ARC_COND_V       = 0x07,
    ARC_COND_VC      = 0x08,
    ARC_COND_NV      = 0x08,
    ARC_COND_GT      = 0x09,
    ARC_COND_GE      = 0x0a,
    ARC_COND_LT      = 0x0b,
    ARC_COND_LE      = 0x0c,
    ARC_COND_HI      = 0x0d,
    ARC_COND_LS      = 0x0e,
    ARC_COND_PNZ     = 0x0f,
} ARC_COND;

#define ARC_HELPER(NAME, RET, ...) \
  gen_helper_##NAME (RET, cpu_env, __VA_ARGS__)

//int arc_gen_ADC(DisasCtxt *c, TCGv dest, TCGv src1, TCGv src2);
//int arc_gen_ADD(DisasCtxt *c, TCGv dest, TCGv src1, TCGv src2);
//int arc_gen_ADD1(DisasCtxt *c, TCGv dest, TCGv src1, TCGv src2);
//int arc_gen_ADD2(DisasCtxt *c, TCGv dest, TCGv src1, TCGv src2);
//int arc_gen_ADD3(DisasCtxt *c, TCGv dest, TCGv src1, TCGv src2);
//
//int arc_gen_SUB(DisasCtxt *c, TCGv dest, TCGv src1, TCGv src2);
//int arc_gen_SUB1(DisasCtxt *c, TCGv dest, TCGv src1, TCGv src2);
//int arc_gen_SUB2(DisasCtxt *c, TCGv dest, TCGv src1, TCGv src2);
//int arc_gen_SUB3(DisasCtxt *c, TCGv dest, TCGv src1, TCGv src2);
//int arc_gen_SBC(DisasCtxt *c, TCGv dest, TCGv src1, TCGv src2);
//int arc_gen_RSUB(DisasCtxt *c, TCGv dest, TCGv src1, TCGv src2);
//int arc_gen_CMP(DisasCtxt *c, TCGv src1, TCGv src2);
//
//int arc_gen_AND(DisasCtxt *c, TCGv dest, TCGv src1, TCGv src2);
//int arc_gen_OR(DisasCtxt *c, TCGv dest, TCGv src1, TCGv src2);
//int arc_gen_BIC(DisasCtxt *c, TCGv dest, TCGv src1, TCGv src2);
//int arc_gen_XOR(DisasCtxt *c, TCGv dest, TCGv src1, TCGv src2);
//int arc_gen_TST(DisasCtxt *c, TCGv src1, TCGv src2);
//
//int arc_gen_ASL(DisasCtxt *c, TCGv dest, TCGv src1);
//int arc_gen_ASLm(DisasCtxt *c, TCGv dest, TCGv src1, TCGv src2);
//int arc_gen_ASR(DisasCtxt *c, TCGv dest, TCGv src1);
//int arc_gen_ASRm(DisasCtxt *c, TCGv dest, TCGv src1, TCGv src2);
//int arc_gen_LSR(DisasCtxt *c, TCGv dest, TCGv src1);
//int arc_gen_LSRm(DisasCtxt *c, TCGv dest, TCGv src1, TCGv src2);
//int arc_gen_ROR(DisasCtxt *c, TCGv dest, TCGv src1);
//int arc_gen_RORm(DisasCtxt *c, TCGv dest, TCGv src1, TCGv src2);
//
//int arc_gen_EX(DisasCtxt *c, TCGv dest, TCGv src1);
//int arc_gen_LD(DisasCtxt *c, TCGv dest, TCGv src1, TCGv src2);
//int arc_gen_LDW(DisasCtxt *ctx, TCGv dest, TCGv src1, TCGv src2);
//int arc_gen_LDB(DisasCtxt *ctx, TCGv dest, TCGv src1, TCGv src2);
//int arc_gen_ST(DisasCtxt *c, TCGv src1, TCGv src2, TCGv src3);
//int arc_gen_STW(DisasCtxt *ctx, TCGv dest, TCGv src1, TCGv src2);
//int arc_gen_STB(DisasCtxt *ctx, TCGv dest, TCGv src1, TCGv src2);
//int arc_gen_PREFETCH(DisasCtxt *c, TCGv src1, TCGv src2);
//int arc_gen_SYNC(DisasCtxt *c);
//
//int arc_gen_MAX(DisasCtxt *c, TCGv dest, TCGv src1, TCGv src2);
//int arc_gen_MIN(DisasCtxt *c, TCGv dest, TCGv src1, TCGv src2);
//
//int arc_gen_MOV(DisasCtxt *c, TCGv dest, TCGv src1);
//int arc_gen_EXTB(DisasCtxt *c, TCGv dest, TCGv src1);
//int arc_gen_EXTW(DisasCtxt *c, TCGv dest, TCGv src1);
//int arc_gen_SEXB(DisasCtxt *c, TCGv dest, TCGv src1);
//int arc_gen_SEXW(DisasCtxt *c, TCGv dest, TCGv src1);
//int arc_gen_SWAP(DisasCtxt *c, TCGv dest, TCGv src1);
//
//int arc_gen_NEG(DisasCtxt *c, TCGv dest, TCGv src1);
//int arc_gen_ABS(DisasCtxt *c, TCGv dest, TCGv src1);
//int arc_gen_NOT(DisasCtxt *c, TCGv dest, TCGv src1);
//
//int arc_gen_POP(DisasCtxt *c, TCGv src1);
//int arc_gen_PUSH(DisasCtxt *c, TCGv src1);
//
//int arc_gen_BCLR(DisasCtxt *c, TCGv dest, TCGv src1, TCGv src2);
//int arc_gen_BMSK(DisasCtxt *c, TCGv dest, TCGv src1, TCGv src2);
//int arc_gen_BSET(DisasCtxt *c, TCGv dest, TCGv src1, TCGv src2);
//int arc_gen_BTST(DisasCtxt *c, TCGv src1, TCGv src2);
//int arc_gen_BXOR(DisasCtxt *c, TCGv dest, TCGv src1, TCGv src2);
//
//int arc_gen_RRC(DisasCtxt *c, TCGv dest, TCGv src1);
//int arc_gen_RLC(DisasCtxt *c, TCGv dest, TCGv src1);
//
//int arc_gen_NORMW(DisasCtxt *c, TCGv dest, TCGv src1);
//int arc_gen_NORM(DisasCtxt *c, TCGv dest, TCGv src1);
//
//int arc_gen_MPY(DisasCtxt *c, TCGv dest, TCGv src1, TCGv src2);
//int arc_gen_MPYH(DisasCtxt *c, TCGv dest, TCGv src1, TCGv src2);
//int arc_gen_MPYHU(DisasCtxt *c, TCGv dest, TCGv src1, TCGv src2);
//int arc_gen_MPYU(DisasCtxt *c, TCGv dest, TCGv src1, TCGv src2);
//
//int arc_gen_DIVAW(DisasCtxt *c, TCGv dest, TCGv src1, TCGv src2);
//int arc_gen_MUL64(DisasCtxt *c, TCGv dest, TCGv src1, TCGv src2);
//int arc_gen_MULU64(DisasCtxt *c, TCGv dest, TCGv src1, TCGv src2);
//
//int arc_gen_BBIT0(DisasCtxt *c, TCGv src1, TCGv src2, TCGv rd);
//int arc_gen_BBIT1(DisasCtxt *c, TCGv src1, TCGv src2, TCGv rd);
//int arc_gen_BR(DisasCtxt *c, TCGv src1, TCGv src2, TCGv Rd, TCGCond cond);
//
//void arc_gen_jump_ifnot(DisasCtxt *ctx, ARC_COND cond, TCGLabel *label_skip);
//int arc_gen_B(DisasCtxt *c, TCGv rd, ARC_COND cond);
//int arc_gen_BL(DisasCtxt *c, TCGv Rd, ARC_COND cond);
//
//int arc_gen_J(DisasCtxt *c, TCGv src1, ARC_COND cond);
//int arc_gen_JL(DisasCtxt *c, TCGv src1, ARC_COND cond);
//
//int arc_gen_LR(DisasCtxt *c, TCGv dest, TCGv src1);
//int arc_gen_SR(DisasCtxt *c, TCGv src1, TCGv src2);
//
//int arc_gen_ADDS(DisasCtxt *c, TCGv dest, TCGv src1, TCGv src2);
//int arc_gen_ADDSDW(DisasCtxt *c, TCGv dest, TCGv src1, TCGv src2);
//int arc_gen_SUBS(DisasCtxt *ctx, TCGv dest, TCGv src1, TCGv src2);
//int arc_gen_SUBSDW(DisasCtxt *ctx, TCGv dest, TCGv src1, TCGv src2);
//
//int arc_gen_ABSS(DisasCtxt *c, TCGv dest, TCGv src1);
//int arc_gen_ABSSW(DisasCtxt *c, TCGv dest, TCGv src1);
//int arc_gen_SAT16(DisasCtxt *c, TCGv dest, TCGv src1);
//int arc_gen_RND16(DisasCtxt *c, TCGv dest, TCGv src1);
//int arc_gen_NEGS(DisasCtxt *c, TCGv dest, TCGv src1);
//int arc_gen_NEGSW(DisasCtxt *c, TCGv dest, TCGv src1);
//
//int arc_gen_ASLS(DisasCtxt *c, TCGv dest, TCGv src1, TCGv src2);
//int arc_gen_ASRS(DisasCtxt *ctx, TCGv dest, TCGv src1, TCGv src2);
//
//int arc_gen_SLEEP(DisasCtxt *c, TCGv src1);
//int arc_gen_BRK(DisasCtxt *c);
//int arc_gen_FLAG(DisasCtxt *c, TCGv src1);
//
//int arc_gen_NOP(DisasCtxt *c);
//int arc_gen_UNIMP(DisasCtxt *c);
//
//int arc_gen_SWI(DisasCtxt *c);
//int arc_gen_TRAP(DisasCtxt *c, TCGv src1);
//
//int arc_gen_RTIE(DisasCtxt *c);
//
//int arc_gen_LPcc(DisasCtxt *ctx, TCGv Rd, unsigned Q);

enum arc_registers {
  R_SP = 0,
  R_STATUS32,
  R_ACCLO,
  R_ACCHI
};

enum target_options {
  INVALID_TARGET_OPTIONS = -1,
  DIV_REM_OPTION,
  STACK_CHECKING,
  LL64_OPTION
};

/* TODO: Change this to allow something else then ARC HS. */
#define LP_START (arc_aux_reg_address_for(AUX_ID_lp_start, ARC_OPCODE_ARCv2HS))
#define LP_END (arc_aux_reg_address_for(AUX_ID_lp_end, ARC_OPCODE_ARCv2HS))

#define ReplMask(DEST, SRC, MASK) \
  gen_helper_repl_mask (DEST, DEST, SRC, MASK)


void arc_gen_verifyCCFlag(DisasCtxt *ctx, TCGv ret);
#define getCCFlag(R) arc_gen_verifyCCFlag(ctx, R)

#define getFFlag(R) ((int) ctx->insn.f)

void to_implement(DisasCtxt *ctx);
void to_implement_wo_abort(DisasCtxt *ctx);

void no_semantics(DisasCtxt *ctx);
#define killDelaySlot()
void arc2_gen_set_memory (DisasCtxt *ctx, TCGv addr, int size, TCGv src, bool sign_extend);
#define setMemory(ADDRESS, SIZE, VALUE) arc2_gen_set_memory (ctx, ADDRESS, SIZE, VALUE, getFlagX())
void arc2_gen_get_memory (DisasCtxt *ctx, TCGv ret, TCGv addr, int size, bool sign_extend);
#define getMemory(R, ADDRESS, SIZE) arc2_gen_get_memory (ctx, R, ADDRESS, SIZE, getFlagX())

#define getFlagX() (ctx->insn.x)
#define getZZFlag() (ctx->insn.zz)
#define getAAFlag() (ctx->insn.aa)

#define SignExtend(VALUE, SIZE) VALUE
//#define SignExtend(VALUE, SIZE) arc2_gen_sign_extend (ctx, VALUE, SIZE)
void arc2_gen_no_further_loads_pending(DisasCtxt *ctx, TCGv ret);
#define NoFurtherLoadsPending(R) arc2_gen_no_further_loads_pending(ctx, R)
void arc2_gen_set_debug(DisasCtxt *ctx, bool value);
#define setDebugLD(A) arc2_gen_set_debug(ctx, A)
void arc2_gen_execute_delayslot(DisasCtxt *ctx);
#define executeDelaySlot() arc2_gen_execute_delayslot(ctx)
bool arc2_gen_should_execute_delayslot(DisasCtxt *ctx);
#define shouldExecuteDelaySlot() arc2_gen_should_execute_delayslot(ctx)

void arc2_gen_setNFlag(TCGv elem);
#define setNFlag(ELEM) arc2_gen_setNFlag(ELEM)
#define getNFlag(R) cpu_Nf

#define setCFlag(ELEM) tcg_gen_mov_tl(cpu_Cf, ELEM)
#define getCFlag(R)    tcg_gen_mov_tl(R, cpu_Cf)

void arc2_gen_setVFlag(TCGv elem);
#define setVFlag(ELEM) arc2_gen_setVFlag(ELEM)
void arc2_gen_set_zflag(TCGv elem);
#define setZFlag(ELEM) arc2_gen_set_zflag (ELEM)

int arc2_get_tcgv_value(TCGv elem);

#define nextInsnAddressAfterDelaySlot(R) tcg_gen_movi_tl(R, ctx->dpc);

#define nextInsnAddress(R) tcg_gen_movi_tl(R, ctx->npc)
#define getPCL(R) tcg_gen_movi_tl(R, ctx->pcl)

#define setPC(NEW_PC) \
  gen_goto_tb(ctx, 1, NEW_PC); \
  ret = ret == DISAS_NEXT ? DISAS_NORETURN : ret

#define setBLINK(BLINK_ADDR) tcg_gen_mov_i32(cpu_blink, BLINK_ADDR);

#define Carry(R, A) tcg_gen_shri_tl(R, A, 31);
void arc2_gen_add_Cf(TCGv ret, TCGv dest, TCGv src1, TCGv src2);
#define CarryADD(R, A, B, C) arc2_gen_add_Cf(R, A, B, C)
void arc2_gen_add_Vf(TCGv ret, TCGv dest, TCGv src1, TCGv src2);
#define OverflowADD(R, A, B, C) arc2_gen_add_Vf(R, A, B, C)
void arc2_gen_sub_Cf(TCGv ret, TCGv dest, TCGv src1, TCGv src2);
#define CarrySUB(R, A, B, C) arc2_gen_sub_Cf(R, A, B, C)

void arc2_gen_sub_Vf(TCGv ret, TCGv dest, TCGv src1, TCGv src2);
#define OverflowSUB(R, A, B, C) arc2_gen_sub_Vf(R, A, B, C)

//void arc2_gen_unsigned_LT(TCGv ret, TCGv b, TCGv c);
#define unsignedLT(R, B, C) tcg_gen_setcond_i32(TCG_COND_LTU, R, B, C);
//#define unsignedLT(R, B, C) arc2_gen_unsigned_LT (R, B, C)

//TCGv arc2_gen_unsigned_GE(TCGv ret, TCGv b, TCGv c);
//#define unsignedGE(R, B, C) arc2_gen_unsigned_GE (R, B, C)
#define unsignedGE(R, B, C) tcg_gen_setcond_i32(TCG_COND_GEU, R, B, C)

//TCGv arc2_gen_logical_shift_right (TCGv ret, TCGv b, TCGv c);
#define logicalShiftRight(R, B, C) tcg_gen_shr_i32(R, B, C)

//TCGv arc2_gen_logical_shift_left (TCGv ret, TCGv b, TCGv c);
#define logicalShiftLeft(R, B, C) tcg_gen_shl_i32(R, B, C)

//TCGv arc2_gen_arithmetic_shift_right (TCGv ret, TCGv b, TCGv c);
#define arithmeticShiftRight(R, B, C) tcg_gen_sar_i32 (R, B, C)

//TCGv arc2_gen_rotate_left (TCGv ret, TCGv b, TCGv c);
#define rotateLeft(R, B, C) tcg_gen_rotl_i32 (R, B, C)

//TCGv arc2_gen_rotate_right (TCGv ret, TCGv b, TCGv c);
#define rotateRight(R, B, C) tcg_gen_rotr_i32 (R, B, C)

void arc2_gen_get_bit (TCGv ret, TCGv a, TCGv pos);
#define getBit(R, A, POS) arc2_gen_get_bit(R, A, POS)

#define getRegIndex(R, ID) tcg_gen_movi_tl(R, (int) ID)

#define readAuxReg(R, A) gen_helper_lr(R, cpu_env, A)
/*
 * Here, by returning DISAS_UPDATE we are making SR the end
 * of a Translation Block (TB). This is necessary because
 * somtimes writing to control registers updates how a TB is
 * handled, like enabling MMU/MPU. If SR is not marked as the
 * end, the next instructions are fetched and generated and
 * the updated outcome (page/region permissions) is not taken
 * into account.
 */
#define writeAuxReg(NAME, B)            \
    gen_helper_sr(cpu_env, B, NAME);    \
    ret = DISAS_UPDATE

/*
 * At the end of a SYNC instruction, it is guaranteed that
 * handling the current interrupt is finished and the raising
 * pulse signal (if any), is cleared. By marking SYNC as the
 * end of a TB we gave a chance to interrupt threads to execute.
 */
#define syncReturnDisasUpdate()     (ret = DISAS_UPDATE)

void arc2_gen_mac(TCGv phi, TCGv_i32 b, TCGv_i32 c);
#define MAC(R, B, C) \
  arc2_gen_mac(R, B, C)
void arc2_gen_macu(TCGv phi, TCGv_i32 b, TCGv_i32 c);
#define MACU(R, B, C) \
  arc2_gen_macu(R, B, C)


void arc2_gen_extract_bits (TCGv ret, TCGv a, TCGv start, TCGv end);
#define extractBits(R, ELEM, START, END) \
  arc2_gen_extract_bits(R, ELEM, START, END)
void arc2_gen_get_register(TCGv ret, enum arc_registers reg);
#define getRegister(R, REG) \
  arc2_gen_get_register(R, REG)
void arc2_gen_set_register(enum arc_registers reg, TCGv value);
#define setRegister(REG, VALUE) \
  arc2_gen_set_register(REG, VALUE)

#define divSigned(R, SRC1, SRC2) tcg_gen_div_i32(R, SRC1, SRC2)
#define divUnsigned(R, SRC1, SRC2) tcg_gen_divu_i32(R, SRC1, SRC2)
#define divRemainingSigned(R, SRC1, SRC2) tcg_gen_rem_i32(R, SRC1, SRC2)
#define divRemainingUnsigned(R, SRC1, SRC2) tcg_gen_remu_i32(R, SRC1, SRC2)

#define Halt() \
  to_implement_wo_abort(ctx)

void arc2_has_interrupts(DisasCtxt *ctx, TCGv ret);
#define hasInterrupts(R) arc2_has_interrupts(ctx, R)
#define doNothing()

#define setLF(VALUE) tcg_gen_mov_tl(cpu_lock_lf_var, VALUE)
#define getLF(R) tcg_gen_mov_tl(R, cpu_lock_lf_var)

/* Statically infered return function */

TCGv arc2_gen_next_reg(TCGv reg);
#define nextReg(A) \
  arc2_gen_next_reg(A)

/* TODO (issue #62): this must be removed */
#define Zero()  (ctx->zero)

bool arc2_target_has_option(enum target_options option);
#define targetHasOption(OPTION) \
  arc2_target_has_option(OPTION)

bool arc_is_instruction_operand_a_register(DisasCtxt *ctx, int nop);
#define instructionHasRegisterOperandIn(NOP) \
   arc_is_instruction_operand_a_register(ctx, NOP)

void tcg_gen_shlfi_i32(TCGv a, int b, TCGv c);

#endif /* __TRANSLATE_INST_H__ */

