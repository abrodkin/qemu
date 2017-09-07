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
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, see
 *  <http://www.gnu.org/licenses/lgpl-2.1.html>
 */

#ifndef ARC_TRANSLATE_H_
#define ARC_TRANSLATE_H_


#include "qemu/osdep.h"
#include "arc-common.h"

#include "tcg/tcg.h"
#include "cpu.h"
#include "exec/exec-all.h"
#include "disas/disas.h"
#include "tcg-op.h"
#include "exec/cpu_ldst.h"

#include "exec/helper-proto.h"
#include "exec/helper-gen.h"
#include "exec/log.h"

#include "aux-reg.h"

extern TCGv_env cpu_env;

extern TCGv     cpu_gp;
extern TCGv     cpu_fp;
extern TCGv     cpu_sp;
extern TCGv     cpu_ilink1;
extern TCGv     cpu_ilink2;
extern TCGv     cpu_blink;
extern TCGv     cpu_pcl;
extern TCGv     cpu_limm;

extern TCGv     cpu_mlo;
extern TCGv     cpu_mmi;
extern TCGv     cpu_mhi;

extern TCGv     cpu_S1f;
extern TCGv     cpu_S2f;
extern TCGv     cpu_CSf;

extern TCGv     cpu_Lf;
extern TCGv     cpu_Zf;
extern TCGv     cpu_Nf;
extern TCGv     cpu_Cf;
extern TCGv     cpu_Vf;
extern TCGv     cpu_Uf;

extern TCGv     cpu_DEf;
extern TCGv     cpu_AEf;
extern TCGv     cpu_A2f;
extern TCGv     cpu_A1f;
extern TCGv     cpu_E2f;
extern TCGv     cpu_E1f;
extern TCGv     cpu_Hf;

extern TCGv     cpu_l1_Lf;
extern TCGv     cpu_l1_Zf;
extern TCGv     cpu_l1_Nf;
extern TCGv     cpu_l1_Cf;
extern TCGv     cpu_l1_Vf;
extern TCGv     cpu_l1_Uf;

extern TCGv     cpu_l1_DEf;
extern TCGv     cpu_l1_AEf;
extern TCGv     cpu_l1_A2f;
extern TCGv     cpu_l1_A1f;
extern TCGv     cpu_l1_E2f;
extern TCGv     cpu_l1_E1f;
extern TCGv     cpu_l1_Hf;

extern TCGv     cpu_l2_Lf;
extern TCGv     cpu_l2_Zf;
extern TCGv     cpu_l2_Nf;
extern TCGv     cpu_l2_Cf;
extern TCGv     cpu_l2_Vf;
extern TCGv     cpu_l2_Uf;

extern TCGv     cpu_l2_DEf;
extern TCGv     cpu_l2_AEf;
extern TCGv     cpu_l2_A2f;
extern TCGv     cpu_l2_A1f;
extern TCGv     cpu_l2_E2f;
extern TCGv     cpu_l2_E1f;
extern TCGv     cpu_l2_Hf;

extern TCGv     cpu_er_Lf;
extern TCGv     cpu_er_Zf;
extern TCGv     cpu_er_Nf;
extern TCGv     cpu_er_Cf;
extern TCGv     cpu_er_Vf;
extern TCGv     cpu_er_Uf;

extern TCGv     cpu_er_DEf;
extern TCGv     cpu_er_AEf;
extern TCGv     cpu_er_A2f;
extern TCGv     cpu_er_A1f;
extern TCGv     cpu_er_E2f;
extern TCGv     cpu_er_E1f;
extern TCGv     cpu_er_Hf;

extern TCGv     cpu_eret;
extern TCGv     cpu_erbta;
extern TCGv     cpu_ecr;
extern TCGv     cpu_efa;

extern TCGv     cpu_pc;
extern TCGv     cpu_lpc;
extern TCGv     cpu_lps;
extern TCGv     cpu_lpe;

extern TCGv     cpu_bta;
extern TCGv     cpu_bta_l1;
extern TCGv     cpu_bta_l2;

extern TCGv     cpu_r[64];

extern TCGv     cpu_intvec;

extern TCGv     cpu_debug_LD;
extern TCGv     cpu_debug_SH;
extern TCGv     cpu_debug_BH;
extern TCGv     cpu_debug_UB;
extern TCGv     cpu_debug_ZZ;
extern TCGv     cpu_debug_RA;
extern TCGv     cpu_debug_IS;
extern TCGv     cpu_debug_FH;
extern TCGv     cpu_debug_SS;

//extern TCGv	cpu_aux_regs[AUX_REG_SIZE];

enum {
    BS_NONE      = 0x00,     /*  Nothing special (none of the below          */
    BS_STOP      = 0x01,     /*  We want to stop translation for any reason  */
    BS_BRANCH    = 0x02,     /*  A branch condition is reached               */
    BS_BRANCH_DS = 0x03,     /*  A branch condition is reached               */
    BS_EXCP      = 0x04,     /*  An exception condition is reached           */
    BS_BREAK     = 0x05,
    BS_BRANCH_HW_LOOP,	     /*  A branch condition in LP_END for hardware loops  */
};

#define BS_DELAYED_SLOT(n)  ((n) ? BS_BRANCH_DS : BS_BRANCH)

typedef struct DisasCtxt DisasCtxt;

struct DisasCtxt {
    struct TranslationBlock    *tb;

    uint32_t cpc;   /*  current pc      */
    uint32_t npc;   /*  next pc         */
    uint32_t dpc;   /*  next next pc    */
    uint32_t pcl;
    uint32_t lpe;
    uint32_t lps;

    unsigned ds;    /*  we are within ds*/

    TCGv one;       /*  0x00000000      */
    TCGv zero;      /*  0x00000000      */

    insn_t insn;

    int memidx;
    int bstate;
    int singlestep;

    CPUARCState *env;
};

int arc_decode(DisasCtxt *ctx);

void gen_goto_tb(DisasCtxt *ctx, int n, TCGv dest);

#endif

