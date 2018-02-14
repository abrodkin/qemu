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
};

TCGv arc_gen_verifyCCFlag(DisasCtxt *ctx);
#define getCCFlag() arc_gen_verifyCCFlag(ctx)
TCGv arc_gen_getCarry(DisasCtxt *ctx);
#define getCFlag() arc_gen_getCarry(ctx)
TCGv arc_gen_verifyFFlag(DisasCtxt *ctx);
#define getFFlag() arc_gen_verifyFFlag(ctx)
TCGv to_implement(DisasCtxt *ctx);
TCGv to_implement_wo_abort(DisasCtxt *ctx);
TCGv arc_gen_getMSB(DisasCtxt *ctx, TCGv src);
#define Carry(A) arc_gen_getMSB(ctx, A)
void no_semantics(DisasCtxt *ctx);
#define killDelaySlot() no_semantics(ctx)
void arc2_gen_set_memory (DisasCtxt *ctx, TCGv addr, int size, TCGv src, bool sign_extend);
#define setMemory(ADDRESS, SIZE, VALUE) arc2_gen_set_memory (ctx, ADDRESS, SIZE, VALUE, getFlagX())
TCGv arc2_gen_get_memory (DisasCtxt *ctx, TCGv addr, int size, bool sign_extend);
#define getMemory(ADDRESS, SIZE) arc2_gen_get_memory (ctx, ADDRESS, SIZE, getFlagX())
bool arc2_get_flag_x (DisasCtxt *ctx);
#define getFlagX() arc2_get_flag_x (ctx)
int arc2_get_flag_zz (DisasCtxt *ctx);
#define getZZFlag() arc2_get_flag_zz (ctx)
int arc2_get_flag_aa (DisasCtxt *ctx);
#define getAAFlag() arc2_get_flag_aa (ctx)
TCGv arc2_gen_sign_extend(DisasCtxt *ctx, TCGv value, int size);
#define SignExtend(VALUE, SIZE) arc2_gen_sign_extend (ctx, VALUE, SIZE)
TCGv arc2_gen_no_further_loads_pending(DisasCtxt *ctx);
#define NoFurtherLoadsPending() to_implement_wo_abort(ctx)
void arc2_gen_set_debug(DisasCtxt *ctx, bool value);
#define setDebugLD(A) arc2_gen_set_debug(ctx, A)
void arc2_gen_execute_delayslot(DisasCtxt *ctx);
#define executeDelaySlot() arc2_gen_execute_delayslot(ctx)
bool arc2_gen_should_execute_delayslot(DisasCtxt *ctx);
#define shouldExecuteDelaySlot() arc2_gen_should_execute_delayslot(ctx)
void arc2_gen_setNFlag(TCGv elem);
#define setNFlag(ELEM) arc2_gen_setNFlag(ELEM)
TCGv arc2_gen_getNFlag(void);
#define getNFlag() arc2_gen_getNFlag()


void arc2_gen_setCarry(TCGv elem);
#define setCFlag(ELEM) arc2_gen_setCarry(ELEM)
void arc2_gen_getVFlag(TCGv elem);
#define setVFlag(ELEM) arc2_gen_getVFlag(ELEM)
void arc2_gen_set_zflag(TCGv elem);
#define setZFlag(ELEM) arc2_gen_set_zflag (ELEM)

int arc2_get_tcgv_value(TCGv elem);

TCGv arc2_get_pc(DisasCtxt *ctx);
#define getPC() arc2_get_pc(ctx)

TCGv arc2_get_next_insn_address_after_delayslot(DisasCtxt *ctx);
#define nextInsnAddressAfterDelaySlot() arc2_get_next_insn_address_after_delayslot (ctx)
TCGv arc2_get_next_insn_address(DisasCtxt *ctx);
#define nextInsnAddress() arc2_get_next_insn_address (ctx)
TCGv arc2_gen_get_pcl(DisasCtxt *ctx);
#define getPCL() arc2_gen_get_pcl(ctx)
void arc2_set_pc(DisasCtxt *ctx, TCGv new_pc);
#define setPC(NEW_PC) \
  arc2_set_pc(ctx, NEW_PC); \
  ret = ret == BS_NONE ? BS_BRANCH : ret
void arc2_set_blink(DisasCtxt *ctx, TCGv blink_addr);
#define setBLINK(BLINK_ADDR) arc2_set_blink(ctx, BLINK_ADDR);
TCGv arc2_gen_add_Cf(TCGv dest, TCGv src1, TCGv src2);
#define CarryADD(A, B, C) arc2_gen_add_Cf(A, B, C)
TCGv arc2_gen_add_Vf(TCGv dest, TCGv src1, TCGv src2);
#define OverflowADD(A, B, C) arc2_gen_add_Vf(A, B, C)
TCGv arc2_gen_sub_Cf(TCGv dest, TCGv src1, TCGv src2);
#define CarrySUB(A, B, C) arc2_gen_sub_Cf(A, B, C)

TCGv arc2_gen_sub_Vf(TCGv dest, TCGv src1, TCGv src2);
#define OverflowSUB(A, B, C) arc2_gen_sub_Vf(A, B, C)

TCGv arc2_gen_unsigned_LT(TCGv b, TCGv c);
#define unsignedLT(B, C) arc2_gen_unsigned_LT (B, C)
TCGv arc2_gen_unsigned_GE(TCGv b, TCGv c);
#define unsignedGE(B, C) arc2_gen_unsigned_GE (B, c)
TCGv arc2_gen_logical_shift_right (TCGv b, TCGv c);
#define logicalShiftRight(B, C) \
  arc2_gen_logical_shift_right (B, C)
TCGv arc2_gen_logical_shift_left (TCGv b, TCGv c);
#define logicalShiftLeft(B, C) \
  arc2_gen_logical_shift_left (B, C)
TCGv arc2_gen_get_bit (TCGv a, TCGv pos);
#define getBit(A, POS) \
  arc2_gen_get_bit(A, POS)

TCGv arc2_gen_get_aux_reg_index(enum arc_registers reg_id);
#define getRegIndex(ID) \
  arc2_gen_get_aux_reg_index(ID)
TCGv arc2_gen_read_aux_reg (TCGv reg_id);
#define readAuxReg(A) \
  arc2_gen_read_aux_reg(A)
void arc2_gen_write_aux_reg (TCGv reg_id, TCGv b);
#define writeAuxReg(NAME, B) \
  arc2_gen_write_aux_reg(NAME, B)
void tcg_gen_shlfi_i32(TCGv a, int b, TCGv c);
TCGv arc2_gen_extract_bits (TCGv a, TCGv start, TCGv end);
#define extractBits(ELEM, START, END) \
  arc2_gen_extract_bits(ELEM, START, END)
TCGv arc2_gen_get_register(enum arc_registers reg);
#define getRegister(REG) \
  arc2_gen_get_register(REG)
void arc2_gen_set_register(enum arc_registers reg, TCGv value);
#define setRegister(REG, VALUE) \
  arc2_gen_set_register(REG, VALUE)

TCGv arc2_gen_next_reg(TCGv reg);
#define nextReg(R) \
  arc2_gen_next_reg(R)

#define Zero() (ctx->zero)

#endif /* __TRANSLATE_INST_H__ */
