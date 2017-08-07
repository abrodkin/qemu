/* Decoder for the ARC.
   Copyright (C) 2017 Free Software Foundation, Inc.

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public License
   as published by the Free Software Foundation; either version 2.1 of
   the License, or (at your option) any later version.

   This library is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with GAS or GDB; see the file COPYING3.  If not, write to
   the Free Software Foundation, 51 Franklin Street - Fifth Floor, Boston,
   MA 02110-1301, USA.  */

#include "arc-decoder.h"
#include "exec/cpu_ldst.h"
#include "qemu/osdep.h"
#include "qemu/bswap.h"
#include "cpu.h"
#include "arc-functions.h"
#include "arc-fxi.h"
#include "translate.h"

#define ARRANGE_ENDIAN(endianess, buf)          \
  ((endianess) ? arc_getm32 (buf) : bswap32 (buf))

/* The operands table.

   The format of the operands table is:

   BITS SHIFT DEFAULT_RELOC FLAGS INSERT_FUN EXTRACT_FUN.  */
const struct arc_operand arc_operands[] =
{
  /* The fields are bits, shift, insert, extract, flags.  The zero
     index is used to indicate end-of-list.  */
#define UNUSED		0
  { 0, 0, 0, 0, 0, 0 },

#define IGNORED		(UNUSED + 1)
  { 0, 0, 0, ARC_OPERAND_IGNORE | ARC_OPERAND_UNSIGNED | ARC_OPERAND_NCHK, 0, 0 },

  /* The plain integer register fields.  Used by 32 bit
     instructions.  */
#define RA		(IGNORED + 1)
  { 6, 0, 0, ARC_OPERAND_IR, 0, 0 },
#define RA_CHK		(RA + 1)
  { 6, 0, 0, ARC_OPERAND_IR, insert_ra_chk, 0 },
#define RB		(RA_CHK + 1)
  { 6, 12, 0, ARC_OPERAND_IR, insert_rb, extract_rb },
#define RB_CHK		(RB + 1)
  { 6, 12, 0, ARC_OPERAND_IR, insert_rb_chk, extract_rb },
#define RC		(RB_CHK + 1)
  { 6, 6, 0, ARC_OPERAND_IR, 0, 0 },
#define RBdup		(RC + 1)
  { 6, 12, 0, ARC_OPERAND_IR | ARC_OPERAND_DUPLICATE, insert_rb, extract_rb },

#define RAD		(RBdup + 1)
  { 6, 0, 0, ARC_OPERAND_IR | ARC_OPERAND_TRUNCATE, insert_rad, 0 },
#define RCD		(RAD + 1)
  { 6, 6, 0, ARC_OPERAND_IR | ARC_OPERAND_TRUNCATE, insert_rcd, 0 },

  /* The plain integer register fields.  Used by short
     instructions.  */
#define RA16		(RCD + 1)
#define RA_S		(RCD + 1)
  { 4, 0, 0, ARC_OPERAND_IR, insert_ras, extract_ras },
#define RB16		(RA16 + 1)
#define RB_S		(RA16 + 1)
  { 4, 8, 0, ARC_OPERAND_IR, insert_rbs, extract_rbs },
#define RB16dup		(RB16 + 1)
#define RB_Sdup		(RB16 + 1)
  { 4, 8, 0, ARC_OPERAND_IR | ARC_OPERAND_DUPLICATE, insert_rbs, extract_rbs },
#define RC16		(RB16dup + 1)
#define RC_S		(RB16dup + 1)
  { 4, 5, 0, ARC_OPERAND_IR, insert_rcs, extract_rcs },
#define R6H		(RC16 + 1)   /* 6bit register field 'h' used
					by V1 cpus.  */
  { 6, 5, 0, ARC_OPERAND_IR, insert_rhv1, extract_rhv1 },
#define R5H		(R6H + 1)    /* 5bit register field 'h' used
					by V2 cpus.  */
#define RH_S		(R6H + 1)    /* 5bit register field 'h' used
					by V2 cpus.  */
  { 5, 5, 0, ARC_OPERAND_IR, insert_rhv2, extract_rhv2 },
#define R5Hdup		(R5H + 1)
#define RH_Sdup		(R5H + 1)
  { 5, 5, 0, ARC_OPERAND_IR | ARC_OPERAND_DUPLICATE,
    insert_rhv2, extract_rhv2 },

#define RG		(R5Hdup + 1)
#define G_S		(R5Hdup + 1)
  { 5, 5, 0, ARC_OPERAND_IR, insert_g_s, extract_g_s },

  /* Fix registers.  */
#define R0		(RG + 1)
#define R0_S		(RG + 1)
  { 0, 0, 0, ARC_OPERAND_IR, insert_r0, extract_r0 },
#define R1		(R0 + 1)
#define R1_S		(R0 + 1)
  { 1, 0, 0, ARC_OPERAND_IR, insert_r1, extract_r1 },
#define R2		(R1 + 1)
#define R2_S		(R1 + 1)
  { 2, 0, 0, ARC_OPERAND_IR, insert_r2, extract_r2 },
#define R3		(R2 + 1)
#define R3_S		(R2 + 1)
  { 2, 0, 0, ARC_OPERAND_IR, insert_r3, extract_r3 },
#define RSP		(R3 + 1)
#define SP_S		(R3 + 1)
  { 5, 0, 0, ARC_OPERAND_IR, insert_sp, extract_sp },
#define SPdup		(RSP + 1)
#define SP_Sdup		(RSP + 1)
  { 5, 0, 0, ARC_OPERAND_IR | ARC_OPERAND_DUPLICATE, insert_sp, extract_sp },
#define GP		(SPdup + 1)
#define GP_S		(SPdup + 1)
  { 5, 0, 0, ARC_OPERAND_IR, insert_gp, extract_gp },

#define PCL_S		(GP + 1)
  { 1, 0, 0, ARC_OPERAND_IR | ARC_OPERAND_NCHK, insert_pcl, extract_pcl },

#define BLINK		(PCL_S + 1)
#define BLINK_S		(PCL_S + 1)
  { 5, 0, 0, ARC_OPERAND_IR, insert_blink, extract_blink },

#define ILINK1		(BLINK + 1)
  { 5, 0, 0, ARC_OPERAND_IR, insert_ilink1, extract_ilink1 },
#define ILINK2		(ILINK1 + 1)
  { 5, 0, 0, ARC_OPERAND_IR, insert_ilink2, extract_ilink2 },

  /* Long immediate.  */
#define LIMM		(ILINK2 + 1)
#define LIMM_S		(ILINK2 + 1)
  { 32, 0, 0, ARC_OPERAND_LIMM, insert_limm, 0 },
#define LIMMdup		(LIMM + 1)
  { 32, 0, 0, ARC_OPERAND_LIMM | ARC_OPERAND_DUPLICATE, insert_limm, 0 },

  /* Special operands.  */
#define ZA		(LIMMdup + 1)
#define ZB		(LIMMdup + 1)
#define ZA_S		(LIMMdup + 1)
#define ZB_S		(LIMMdup + 1)
#define ZC_S		(LIMMdup + 1)
  { 0, 0, 0, ARC_OPERAND_UNSIGNED, insert_za, 0 },

#define RRANGE_EL	(ZA + 1)
  { 4, 0, 0, ARC_OPERAND_UNSIGNED | ARC_OPERAND_NCHK | ARC_OPERAND_TRUNCATE,
    insert_rrange, extract_rrange},
#define R13_EL		(RRANGE_EL + 1)
  { 1, 0, 0, ARC_OPERAND_IR | ARC_OPERAND_IGNORE | ARC_OPERAND_NCHK,
    insert_r13el, extract_rrange },
#define FP_EL		(R13_EL + 1)
  { 1, 0, 0, ARC_OPERAND_IR | ARC_OPERAND_IGNORE | ARC_OPERAND_NCHK,
    insert_fpel, extract_fpel },
#define BLINK_EL	(FP_EL + 1)
  { 1, 0, 0, ARC_OPERAND_IR | ARC_OPERAND_IGNORE | ARC_OPERAND_NCHK,
    insert_blinkel, extract_blinkel },
#define PCL_EL		(BLINK_EL + 1)
  { 1, 0, 0, ARC_OPERAND_IR | ARC_OPERAND_IGNORE | ARC_OPERAND_NCHK,
    insert_pclel, extract_pclel },

  /* Fake operand to handle the T flag.  */
#define BRAKET		(PCL_EL + 1)
#define BRAKETdup	(PCL_EL + 1)
  { 0, 0, 0, ARC_OPERAND_FAKE | ARC_OPERAND_BRAKET, 0, 0 },

  /* Fake operand to handle the T flag.  */
#define FKT_T		(BRAKET + 1)
  { 1, 3, 0, ARC_OPERAND_FAKE, insert_Ybit, 0 },
  /* Fake operand to handle the T flag.  */
#define FKT_NT		(FKT_T + 1)
  { 1, 3, 0, ARC_OPERAND_FAKE, insert_NYbit, 0 },

  /* UIMM6_20 mask = 00000000000000000000111111000000.  */
#define UIMM6_20       (FKT_NT + 1)
  {6, 0, 0, ARC_OPERAND_UNSIGNED, insert_uimm6_20, extract_uimm6_20},

  /* Exactly like the above but used by relaxation.  */
#define UIMM6_20R      (UIMM6_20 + 1)
  {6, 0, -UIMM6_20R, ARC_OPERAND_UNSIGNED | ARC_OPERAND_PCREL,
   insert_uimm6_20, extract_uimm6_20},

  /* SIMM12_20 mask = 00000000000000000000111111222222.  */
#define SIMM12_20	(UIMM6_20R + 1)
  {12, 0, 0, ARC_OPERAND_SIGNED, insert_simm12_20, extract_simm12_20},

  /* Exactly like the above but used by relaxation.  */
#define SIMM12_20R	(SIMM12_20 + 1)
  {12, 0, -SIMM12_20R, ARC_OPERAND_SIGNED | ARC_OPERAND_PCREL,
   insert_simm12_20, extract_simm12_20},

  /* UIMM12_20 mask = 00000000000000000000111111222222.  */
#define UIMM12_20	(SIMM12_20R + 1)
  {12, 0, 0, ARC_OPERAND_UNSIGNED, insert_simm12_20, extract_uimm12_20},

  /* SIMM3_5_S mask = 0000011100000000.  */
#define SIMM3_5_S	(UIMM12_20 + 1)
  {3, 0, 0, ARC_OPERAND_SIGNED | ARC_OPERAND_NCHK,
   insert_simm3s, extract_simm3s},

  /* UIMM7_A32_11_S mask = 0000000000011111.  */
#define UIMM7_A32_11_S	     (SIMM3_5_S + 1)
  {7, 0, 0, ARC_OPERAND_UNSIGNED | ARC_OPERAND_ALIGNED32
   | ARC_OPERAND_TRUNCATE | ARC_OPERAND_IGNORE, insert_uimm7_a32_11_s,
   extract_uimm7_a32_11_s},

  /* The same as above but used by relaxation.  */
#define UIMM7_A32_11R_S	     (UIMM7_A32_11_S + 1)
  {7, 0, -UIMM7_A32_11R_S, ARC_OPERAND_UNSIGNED | ARC_OPERAND_ALIGNED32
   | ARC_OPERAND_TRUNCATE | ARC_OPERAND_IGNORE | ARC_OPERAND_PCREL,
   insert_uimm7_a32_11_s, extract_uimm7_a32_11_s},

  /* UIMM7_9_S mask = 0000000001111111.  */
#define UIMM7_9_S	(UIMM7_A32_11R_S + 1)
  {7, 0, 0, ARC_OPERAND_UNSIGNED, insert_uimm7_9_s, extract_uimm7_9_s},

  /* UIMM3_13_S mask = 0000000000000111.  */
#define UIMM3_13_S	 (UIMM7_9_S + 1)
  {3, 0, 0, ARC_OPERAND_UNSIGNED, insert_uimm3_13_s, extract_uimm3_13_s},

  /* Exactly like the above but used for relaxation.  */
#define UIMM3_13R_S	 (UIMM3_13_S + 1)
  {3, 0, -UIMM3_13R_S, ARC_OPERAND_UNSIGNED | ARC_OPERAND_PCREL,
   insert_uimm3_13_s, extract_uimm3_13_s},

  /* SIMM11_A32_7_S mask = 0000000111111111.  */
#define SIMM11_A32_7_S	     (UIMM3_13R_S + 1)
  {11, 0, 0, ARC_OPERAND_SIGNED | ARC_OPERAND_ALIGNED32
   | ARC_OPERAND_TRUNCATE, insert_simm11_a32_7_s, extract_simm11_a32_7_s},

  /* UIMM6_13_S mask = 0000000002220111.  */
#define UIMM6_13_S	 (SIMM11_A32_7_S + 1)
  {6, 0, 0, ARC_OPERAND_UNSIGNED, insert_uimm6_13_s, extract_uimm6_13_s},
  /* UIMM5_11_S mask = 0000000000011111.  */
#define UIMM5_11_S	 (UIMM6_13_S + 1)
  {5, 0, 0, ARC_OPERAND_UNSIGNED | ARC_OPERAND_IGNORE, insert_uimm5_11_s,
   extract_uimm5_11_s},

  /* SIMM9_A16_8 mask = 00000000111111102000000000000000.  */
#define SIMM9_A16_8	  (UIMM5_11_S + 1)
  {9, 0, -SIMM9_A16_8, ARC_OPERAND_SIGNED | ARC_OPERAND_ALIGNED16
   | ARC_OPERAND_PCREL | ARC_OPERAND_TRUNCATE, insert_simm9_a16_8,
   extract_simm9_a16_8},

  /* UIMM6_8 mask = 00000000000000000000111111000000.	 */
#define UIMM6_8	      (SIMM9_A16_8 + 1)
  {6, 0, 0, ARC_OPERAND_UNSIGNED, insert_uimm6_8, extract_uimm6_8},

  /* SIMM21_A16_5 mask = 00000111111111102222222222000000.  */
#define SIMM21_A16_5	   (UIMM6_8 + 1)
  {21, 0, 0, ARC_OPERAND_SIGNED
   | ARC_OPERAND_ALIGNED16 | ARC_OPERAND_TRUNCATE | ARC_OPERAND_PCREL,
   insert_simm21_a16_5, extract_simm21_a16_5},

  /* SIMM25_A16_5 mask = 00000111111111102222222222003333.  */
#define SIMM25_A16_5	   (SIMM21_A16_5 + 1)
  {25, 0, 0, ARC_OPERAND_SIGNED
   | ARC_OPERAND_ALIGNED16 | ARC_OPERAND_TRUNCATE | ARC_OPERAND_PCREL,
   insert_simm25_a16_5, extract_simm25_a16_5},

  /* SIMM10_A16_7_S mask = 0000000111111111.  */
#define SIMM10_A16_7_S	     (SIMM25_A16_5 + 1)
  {10, 0, -SIMM10_A16_7_S, ARC_OPERAND_SIGNED | ARC_OPERAND_ALIGNED16
   | ARC_OPERAND_TRUNCATE | ARC_OPERAND_PCREL, insert_simm10_a16_7_s,
   extract_simm10_a16_7_s},

#define SIMM10_A16_7_Sbis    (SIMM10_A16_7_S + 1)
  {10, 0, -SIMM10_A16_7_Sbis, ARC_OPERAND_SIGNED | ARC_OPERAND_ALIGNED16
   | ARC_OPERAND_TRUNCATE, insert_simm10_a16_7_s, extract_simm10_a16_7_s},

  /* SIMM7_A16_10_S mask = 0000000000111111.  */
#define SIMM7_A16_10_S	     (SIMM10_A16_7_Sbis + 1)
  {7, 0, -SIMM7_A16_10_S, ARC_OPERAND_SIGNED | ARC_OPERAND_ALIGNED16
   | ARC_OPERAND_TRUNCATE | ARC_OPERAND_PCREL, insert_simm7_a16_10_s,
   extract_simm7_a16_10_s},

  /* SIMM21_A32_5 mask = 00000111111111002222222222000000.  */
#define SIMM21_A32_5	   (SIMM7_A16_10_S + 1)
  {21, 0, 0, ARC_OPERAND_SIGNED | ARC_OPERAND_ALIGNED32
   | ARC_OPERAND_TRUNCATE | ARC_OPERAND_PCREL, insert_simm21_a32_5,
   extract_simm21_a32_5},

  /* SIMM25_A32_5 mask = 00000111111111002222222222003333.  */
#define SIMM25_A32_5	   (SIMM21_A32_5 + 1)
  {25, 0, 0, ARC_OPERAND_SIGNED | ARC_OPERAND_ALIGNED32
   | ARC_OPERAND_TRUNCATE | ARC_OPERAND_PCREL, insert_simm25_a32_5,
   extract_simm25_a32_5},

  /* SIMM13_A32_5_S mask = 0000011111111111.  */
#define SIMM13_A32_5_S	     (SIMM25_A32_5 + 1)
  {13, 0, 0, ARC_OPERAND_SIGNED | ARC_OPERAND_ALIGNED32
   | ARC_OPERAND_TRUNCATE | ARC_OPERAND_PCREL, insert_simm13_a32_5_s,
   extract_simm13_a32_5_s},

  /* SIMM8_A16_9_S mask = 0000000001111111.  */
#define SIMM8_A16_9_S	    (SIMM13_A32_5_S + 1)
  {8, 0, -SIMM8_A16_9_S, ARC_OPERAND_SIGNED | ARC_OPERAND_ALIGNED16
   | ARC_OPERAND_TRUNCATE | ARC_OPERAND_PCREL, insert_simm8_a16_9_s,
   extract_simm8_a16_9_s},

/* UIMM10_6_S_JLIOFF mask = 0000001111111111.  */
#define UIMM10_6_S_JLIOFF     (SIMM8_A16_9_S + 1)
  {12, 0, 0, ARC_OPERAND_UNSIGNED
   | ARC_OPERAND_ALIGNED32 | ARC_OPERAND_TRUNCATE, insert_uimm10_6_s,
   extract_uimm10_6_s},

  /* UIMM3_23 mask = 00000000000000000000000111000000.  */
#define UIMM3_23       (UIMM10_6_S_JLIOFF + 1)
  {3, 0, 0, ARC_OPERAND_UNSIGNED, insert_uimm3_23, extract_uimm3_23},

  /* UIMM10_6_S mask = 0000001111111111.  */
#define UIMM10_6_S	 (UIMM3_23 + 1)
  {10, 0, 0, ARC_OPERAND_UNSIGNED, insert_uimm10_6_s, extract_uimm10_6_s},

  /* UIMM6_11_S mask = 0000002200011110.  */
#define UIMM6_11_S	 (UIMM10_6_S + 1)
  {6, 0, 0, ARC_OPERAND_UNSIGNED, insert_uimm6_11_s, extract_uimm6_11_s},

  /* SIMM9_8 mask = 00000000111111112000000000000000.	 */
#define SIMM9_8	      (UIMM6_11_S + 1)
  {9, 0, 0, ARC_OPERAND_SIGNED | ARC_OPERAND_IGNORE,
   insert_simm9_8, extract_simm9_8},

  /* The same as above but used by relaxation.  */
#define SIMM9_8R      (SIMM9_8 + 1)
  {9, 0, -SIMM9_8R, ARC_OPERAND_SIGNED | ARC_OPERAND_IGNORE
   | ARC_OPERAND_PCREL, insert_simm9_8, extract_simm9_8},

  /* UIMM10_A32_8_S mask = 0000000011111111.  */
#define UIMM10_A32_8_S	     (SIMM9_8R + 1)
  {10, 0, -UIMM10_A32_8_S, ARC_OPERAND_UNSIGNED | ARC_OPERAND_ALIGNED32
   | ARC_OPERAND_TRUNCATE | ARC_OPERAND_PCREL, insert_uimm10_a32_8_s,
   extract_uimm10_a32_8_s},

  /* SIMM9_7_S mask = 0000000111111111.  */
#define SIMM9_7_S	(UIMM10_A32_8_S + 1)
  {9, 0, 0, ARC_OPERAND_SIGNED, insert_simm9_7_s,
   extract_simm9_7_s},

  /* UIMM6_A16_11_S mask = 0000000000011111.  */
#define UIMM6_A16_11_S	     (SIMM9_7_S + 1)
  {6, 0, 0, ARC_OPERAND_UNSIGNED | ARC_OPERAND_ALIGNED16
   | ARC_OPERAND_TRUNCATE  | ARC_OPERAND_IGNORE, insert_uimm6_a16_11_s,
   extract_uimm6_a16_11_s},

  /* UIMM5_A32_11_S mask = 0000020000011000.  */
#define UIMM5_A32_11_S	     (UIMM6_A16_11_S + 1)
  {5, 0, 0, ARC_OPERAND_UNSIGNED | ARC_OPERAND_ALIGNED32
   | ARC_OPERAND_TRUNCATE | ARC_OPERAND_IGNORE, insert_uimm5_a32_11_s,
   extract_uimm5_a32_11_s},

  /* SIMM11_A32_13_S mask = 0000022222200111.	 */
#define SIMM11_A32_13_S	      (UIMM5_A32_11_S + 1)
  {11, 0, 0, ARC_OPERAND_SIGNED | ARC_OPERAND_ALIGNED32
   | ARC_OPERAND_TRUNCATE, insert_simm11_a32_13_s, extract_simm11_a32_13_s},

  /* UIMM7_13_S mask = 0000000022220111.  */
#define UIMM7_13_S	 (SIMM11_A32_13_S + 1)
  {7, 0, 0, ARC_OPERAND_UNSIGNED, insert_uimm7_13_s, extract_uimm7_13_s},

  /* UIMM6_A16_21 mask = 00000000000000000000011111000000.  */
#define UIMM6_A16_21	   (UIMM7_13_S + 1)
  {6, 0, 0, ARC_OPERAND_UNSIGNED | ARC_OPERAND_ALIGNED16
   | ARC_OPERAND_TRUNCATE, insert_uimm6_a16_21, extract_uimm6_a16_21},

  /* UIMM7_11_S mask = 0000022200011110.  */
#define UIMM7_11_S	 (UIMM6_A16_21 + 1)
  {7, 0, 0, ARC_OPERAND_UNSIGNED, insert_uimm7_11_s, extract_uimm7_11_s},

  /* UIMM7_A16_20 mask = 00000000000000000000111111000000.  */
#define UIMM7_A16_20	   (UIMM7_11_S + 1)
  {7, 0, -UIMM7_A16_20, ARC_OPERAND_UNSIGNED | ARC_OPERAND_ALIGNED16
   | ARC_OPERAND_TRUNCATE | ARC_OPERAND_PCREL, insert_uimm7_a16_20,
   extract_uimm7_a16_20},

  /* SIMM13_A16_20 mask = 00000000000000000000111111222222.  */
#define SIMM13_A16_20	    (UIMM7_A16_20 + 1)
  {13, 0, -SIMM13_A16_20, ARC_OPERAND_SIGNED | ARC_OPERAND_ALIGNED16
   | ARC_OPERAND_TRUNCATE | ARC_OPERAND_PCREL, insert_simm13_a16_20,
   extract_simm13_a16_20},

  /* UIMM8_8_S mask = 0000000011111111.  */
#define UIMM8_8_S	(SIMM13_A16_20 + 1)
  {8, 0, 0, ARC_OPERAND_UNSIGNED, insert_uimm8_8_s, extract_uimm8_8_s},

  /* The same as above but used for relaxation.  */
#define UIMM8_8R_S	(UIMM8_8_S + 1)
  {8, 0, -UIMM8_8R_S, ARC_OPERAND_UNSIGNED | ARC_OPERAND_PCREL,
   insert_uimm8_8_s, extract_uimm8_8_s},

  /* W6 mask = 00000000000000000000111111000000.  */
#define W6	 (UIMM8_8R_S + 1)
  {6, 0, 0, ARC_OPERAND_SIGNED, insert_w6, extract_w6},

  /* UIMM6_5_S mask = 0000011111100000.  */
#define UIMM6_5_S	(W6 + 1)
  {6, 0, 0, ARC_OPERAND_UNSIGNED, insert_uimm6_5_s, extract_uimm6_5_s},

  /* ARC NPS400 Support: See comment near head of file.  */
#define NPS_R_DST_3B	(UIMM6_5_S + 1)
  { 3, 24, 0, ARC_OPERAND_IR | ARC_OPERAND_NCHK, insert_nps_3bit_reg_at_24_dst, extract_nps_3bit_reg_at_24_dst },

#define NPS_R_SRC1_3B	(NPS_R_DST_3B + 1)
  { 3, 24, 0, ARC_OPERAND_IR | ARC_OPERAND_DUPLICATE | ARC_OPERAND_NCHK, insert_nps_3bit_reg_at_24_dst, extract_nps_3bit_reg_at_24_dst },

#define NPS_R_SRC2_3B	(NPS_R_SRC1_3B + 1)
  { 3, 21, 0, ARC_OPERAND_IR | ARC_OPERAND_NCHK, insert_nps_3bit_reg_at_21_src2, extract_nps_3bit_reg_at_21_src2 },

#define NPS_R_DST	(NPS_R_SRC2_3B + 1)
  { 6, 21, 0, ARC_OPERAND_IR, NULL, NULL },

#define NPS_R_SRC1	(NPS_R_DST + 1)
  { 6, 21, 0, ARC_OPERAND_IR | ARC_OPERAND_DUPLICATE, NULL, NULL },

#define NPS_BITOP_DST_POS	(NPS_R_SRC1 + 1)
  { 5, 5, 0, ARC_OPERAND_UNSIGNED, 0, 0 },

#define NPS_BITOP_SRC_POS	(NPS_BITOP_DST_POS + 1)
  { 5, 0, 0, ARC_OPERAND_UNSIGNED, 0, 0 },

#define NPS_BITOP_SIZE		(NPS_BITOP_SRC_POS + 1)
  { 5, 10, 0, ARC_OPERAND_UNSIGNED | ARC_OPERAND_NCHK, insert_nps_bitop_size, extract_nps_bitop_size },

#define NPS_BITOP_DST_POS_SZ    (NPS_BITOP_SIZE + 1)
  { 5, 0, 0, ARC_OPERAND_UNSIGNED, insert_nps_dst_pos_and_size, extract_nps_dst_pos_and_size },

#define NPS_BITOP_SIZE_2B	(NPS_BITOP_DST_POS_SZ + 1)
  { 0, 0, 0, ARC_OPERAND_UNSIGNED | ARC_OPERAND_NCHK, insert_nps_bitop_size_2b, extract_nps_bitop_size_2b },

#define NPS_BITOP_UIMM8		(NPS_BITOP_SIZE_2B + 1)
  { 8, 0, 0, ARC_OPERAND_UNSIGNED, insert_nps_bitop_uimm8, extract_nps_bitop_uimm8 },

#define NPS_UIMM16		(NPS_BITOP_UIMM8 + 1)
  { 16, 0, 0, ARC_OPERAND_UNSIGNED, NULL, NULL },

#define NPS_SIMM16              (NPS_UIMM16 + 1)
  { 16, 0, 0, ARC_OPERAND_SIGNED, NULL, NULL },

#define NPS_RFLT_UIMM6		(NPS_SIMM16 + 1)
  { 6, 6, 0, ARC_OPERAND_UNSIGNED | ARC_OPERAND_NCHK, insert_nps_rflt_uimm6, extract_nps_rflt_uimm6 },

#define NPS_XLDST_UIMM16	(NPS_RFLT_UIMM6 + 1)
  { 16, 0, 0, ARC_OPERAND_UNSIGNED | ARC_OPERAND_NCHK, insert_nps_cmem_uimm16, extract_nps_cmem_uimm16 },

#define NPS_SRC2_POS           (NPS_XLDST_UIMM16 + 1)
  { 0, 0, 0, ARC_OPERAND_UNSIGNED | ARC_OPERAND_NCHK, insert_nps_src2_pos, extract_nps_src2_pos },

#define NPS_SRC1_POS           (NPS_SRC2_POS + 1)
  { 0, 0, 0, ARC_OPERAND_UNSIGNED | ARC_OPERAND_NCHK, insert_nps_src1_pos, extract_nps_src1_pos },

#define NPS_ADDB_SIZE          (NPS_SRC1_POS + 1)
  { 0, 0, 0, ARC_OPERAND_UNSIGNED | ARC_OPERAND_NCHK, insert_nps_addb_size, extract_nps_addb_size },

#define NPS_ANDB_SIZE          (NPS_ADDB_SIZE + 1)
  { 0, 0, 0, ARC_OPERAND_UNSIGNED | ARC_OPERAND_NCHK, insert_nps_andb_size, extract_nps_andb_size },

#define NPS_FXORB_SIZE         (NPS_ANDB_SIZE + 1)
  { 0, 0, 0, ARC_OPERAND_UNSIGNED | ARC_OPERAND_NCHK, insert_nps_fxorb_size, extract_nps_fxorb_size },

#define NPS_WXORB_SIZE         (NPS_FXORB_SIZE + 1)
  { 0, 0, 0, ARC_OPERAND_UNSIGNED | ARC_OPERAND_NCHK, insert_nps_wxorb_size, extract_nps_wxorb_size },

#define NPS_R_XLDST    (NPS_WXORB_SIZE + 1)
  { 6, 5, 0, ARC_OPERAND_IR, NULL, NULL },

#define NPS_DIV_UIMM4    (NPS_R_XLDST + 1)
  { 4, 5, 0, ARC_OPERAND_UNSIGNED, NULL, NULL },

#define NPS_QCMP_SIZE         (NPS_DIV_UIMM4 + 1)
  { 0, 0, 0, ARC_OPERAND_UNSIGNED | ARC_OPERAND_NCHK, insert_nps_qcmp_size, extract_nps_qcmp_size },

#define NPS_QCMP_M1         (NPS_QCMP_SIZE + 1)
  { 1, 14, 0, ARC_OPERAND_UNSIGNED, NULL, extract_nps_qcmp_m1 },

#define NPS_QCMP_M2         (NPS_QCMP_M1 + 1)
  { 1, 15, 0, ARC_OPERAND_UNSIGNED, NULL, extract_nps_qcmp_m2 },

#define NPS_QCMP_M3         (NPS_QCMP_M2 + 1)
  { 4, 5, 0, ARC_OPERAND_UNSIGNED, NULL, extract_nps_qcmp_m3 },

#define NPS_CALC_ENTRY_SIZE	(NPS_QCMP_M3 + 1)
  { 0, 0, 0, ARC_OPERAND_UNSIGNED | ARC_OPERAND_NCHK, insert_nps_calc_entry_size, extract_nps_calc_entry_size },

#define NPS_R_DST_3B_SHORT	(NPS_CALC_ENTRY_SIZE + 1)
  { 3, 8, 0, ARC_OPERAND_IR | ARC_OPERAND_NCHK, insert_nps_3bit_reg_at_8_dst, extract_nps_3bit_reg_at_8_dst },

#define NPS_R_SRC1_3B_SHORT	(NPS_R_DST_3B_SHORT + 1)
  { 3, 8, 0, ARC_OPERAND_IR | ARC_OPERAND_DUPLICATE | ARC_OPERAND_NCHK, insert_nps_3bit_reg_at_8_dst, extract_nps_3bit_reg_at_8_dst },

#define NPS_R_SRC2_3B_SHORT	(NPS_R_SRC1_3B_SHORT + 1)
  { 3, 5, 0, ARC_OPERAND_IR | ARC_OPERAND_NCHK, insert_nps_3bit_reg_at_5_src2, extract_nps_3bit_reg_at_5_src2 },

#define NPS_BITOP_SIZE2		(NPS_R_SRC2_3B_SHORT + 1)
  { 5, 25, 0, ARC_OPERAND_UNSIGNED | ARC_OPERAND_NCHK, insert_nps_bitop2_size, extract_nps_bitop2_size },

#define NPS_BITOP_SIZE1		(NPS_BITOP_SIZE2 + 1)
  { 5, 20, 0, ARC_OPERAND_UNSIGNED | ARC_OPERAND_NCHK, insert_nps_bitop1_size, extract_nps_bitop1_size },

#define NPS_BITOP_DST_POS3_POS4		(NPS_BITOP_SIZE1 + 1)
  { 5, 0, 0, ARC_OPERAND_UNSIGNED, insert_nps_bitop_dst_pos3_pos4, extract_nps_bitop_dst_pos3_pos4 },

#define NPS_BITOP_DST_POS4		(NPS_BITOP_DST_POS3_POS4 + 1)
  { 5, 42, 0, ARC_OPERAND_UNSIGNED, NULL, NULL },

#define NPS_BITOP_DST_POS3		(NPS_BITOP_DST_POS4 + 1)
  { 5, 37, 0, ARC_OPERAND_UNSIGNED, NULL, NULL },

#define NPS_BITOP_DST_POS2		(NPS_BITOP_DST_POS3 + 1)
  { 5, 15, 0, ARC_OPERAND_UNSIGNED, NULL, NULL },

#define NPS_BITOP_DST_POS1		(NPS_BITOP_DST_POS2 + 1)
  { 5, 10, 0, ARC_OPERAND_UNSIGNED, NULL, NULL },

#define NPS_BITOP_SRC_POS4		(NPS_BITOP_DST_POS1 + 1)
  { 5, 32, 0, ARC_OPERAND_UNSIGNED, NULL, NULL },

#define NPS_BITOP_SRC_POS3		(NPS_BITOP_SRC_POS4 + 1)
  { 5, 20, 0, ARC_OPERAND_UNSIGNED, NULL, NULL },

#define NPS_BITOP_SRC_POS2		(NPS_BITOP_SRC_POS3 + 1)
  { 5, 5, 0, ARC_OPERAND_UNSIGNED, NULL, NULL },

#define NPS_BITOP_SRC_POS1		(NPS_BITOP_SRC_POS2 + 1)
  { 5, 0, 0, ARC_OPERAND_UNSIGNED, NULL, NULL },

#define NPS_BITOP_MOD4			(NPS_BITOP_SRC_POS1 + 1)
  { 2, 0, 0, ARC_OPERAND_UNSIGNED, insert_nps_bitop_mod4, extract_nps_bitop_mod4 },

#define NPS_BITOP_MOD3		(NPS_BITOP_MOD4 + 1)
  { 2, 29, 0, ARC_OPERAND_UNSIGNED, NULL, NULL },

#define NPS_BITOP_MOD2		(NPS_BITOP_MOD3 + 1)
  { 2, 27, 0, ARC_OPERAND_UNSIGNED, NULL, NULL },

#define NPS_BITOP_MOD1		(NPS_BITOP_MOD2 + 1)
  { 2, 25, 0, ARC_OPERAND_UNSIGNED, NULL, NULL },

#define NPS_BITOP_INS_EXT	(NPS_BITOP_MOD1 + 1)
  { 5, 20, 0, ARC_OPERAND_UNSIGNED, insert_nps_bitop_ins_ext, extract_nps_bitop_ins_ext },

#define NPS_FIELD_START_POS     (NPS_BITOP_INS_EXT + 1)
  { 3, 3, 0, ARC_OPERAND_UNSIGNED, NULL, NULL },

#define NPS_FIELD_SIZE          (NPS_FIELD_START_POS + 1)
  { 3, 6, 0, ARC_OPERAND_UNSIGNED | ARC_OPERAND_NCHK, insert_nps_field_size, extract_nps_field_size },

#define NPS_SHIFT_FACTOR        (NPS_FIELD_SIZE + 1)
  { 3, 9, 0, ARC_OPERAND_UNSIGNED | ARC_OPERAND_NCHK, insert_nps_shift_factor, extract_nps_shift_factor },

#define NPS_BITS_TO_SCRAMBLE    (NPS_SHIFT_FACTOR + 1)
  { 3, 12, 0, ARC_OPERAND_UNSIGNED | ARC_OPERAND_NCHK, insert_nps_bits_to_scramble, extract_nps_bits_to_scramble },

#define NPS_SRC2_POS_5B         (NPS_BITS_TO_SCRAMBLE + 1)
  { 5, 5, 0, ARC_OPERAND_UNSIGNED, NULL, NULL },

#define NPS_BDLEN_MAX_LEN       (NPS_SRC2_POS_5B + 1)
  { 8, 5, 0, ARC_OPERAND_UNSIGNED | ARC_OPERAND_NCHK, insert_nps_bdlen_max_len, extract_nps_bdlen_max_len },

#define NPS_MIN_HOFS       (NPS_BDLEN_MAX_LEN + 1)
  { 4, 6, 0, ARC_OPERAND_UNSIGNED | ARC_OPERAND_NCHK, insert_nps_min_hofs, extract_nps_min_hofs },

#define NPS_PSBC       (NPS_MIN_HOFS + 1)
  { 1, 11, 0, ARC_OPERAND_UNSIGNED, NULL, NULL },

#define NPS_DPI_DST       (NPS_PSBC + 1)
  { 5, 11, 0, ARC_OPERAND_IR, NULL, NULL },

  /* NPS_DPI_SRC1_3B is similar to NPS_R_SRC1_3B but doesn't duplicate an operand */
#define NPS_DPI_SRC1_3B    (NPS_DPI_DST + 1)
  { 3, 24, 0, ARC_OPERAND_IR | ARC_OPERAND_NCHK, insert_nps_3bit_reg_at_24_dst, extract_nps_3bit_reg_at_24_dst },

#define NPS_HASH_WIDTH       (NPS_DPI_SRC1_3B + 1)
  { 5, 6, 0, ARC_OPERAND_UNSIGNED | ARC_OPERAND_NCHK, insert_nps_hash_width, extract_nps_hash_width },

#define NPS_HASH_PERM       (NPS_HASH_WIDTH + 1)
  { 3, 2, 0, ARC_OPERAND_UNSIGNED, NULL, NULL },

#define NPS_HASH_NONLINEAR       (NPS_HASH_PERM + 1)
  { 1, 5, 0, ARC_OPERAND_UNSIGNED, NULL, NULL },

#define NPS_HASH_BASEMAT       (NPS_HASH_NONLINEAR + 1)
  { 2, 0, 0, ARC_OPERAND_UNSIGNED, NULL, NULL },

#define NPS_HASH_LEN       (NPS_HASH_BASEMAT + 1)
  { 3, 2, 0, ARC_OPERAND_UNSIGNED | ARC_OPERAND_NCHK, insert_nps_hash_len, extract_nps_hash_len },

#define NPS_HASH_OFS       (NPS_HASH_LEN + 1)
  { 2, 0, 0, ARC_OPERAND_UNSIGNED, NULL, NULL },

#define NPS_HASH_BASEMAT2       (NPS_HASH_OFS + 1)
  { 1, 5, 0, ARC_OPERAND_UNSIGNED, NULL, NULL },

#define NPS_E4BY_INDEX0       (NPS_HASH_BASEMAT2 + 1)
  { 3, 8, 0, ARC_OPERAND_UNSIGNED, NULL, NULL },

#define NPS_E4BY_INDEX1       (NPS_E4BY_INDEX0 + 1)
  { 3, 5, 0, ARC_OPERAND_UNSIGNED, NULL, NULL },

#define NPS_E4BY_INDEX2       (NPS_E4BY_INDEX1 + 1)
  { 3, 2, 0, ARC_OPERAND_UNSIGNED, NULL, NULL },

#define NPS_E4BY_INDEX3       (NPS_E4BY_INDEX2 + 1)
  { 2, 0, 0, ARC_OPERAND_UNSIGNED | ARC_OPERAND_NCHK, insert_nps_index3, extract_nps_index3 },

#define COLON      (NPS_E4BY_INDEX3 + 1)
  { 0, 0, 0, ARC_OPERAND_COLON | ARC_OPERAND_FAKE, NULL, NULL },

#define NPS_BD      (COLON + 1)
  { 0, 0, 0, ARC_OPERAND_ADDRTYPE | ARC_OPERAND_NCHK, insert_nps_bd, extract_nps_bd },

#define NPS_JID      (NPS_BD + 1)
  { 0, 0, 0, ARC_OPERAND_ADDRTYPE | ARC_OPERAND_NCHK, insert_nps_jid, extract_nps_jid },

#define NPS_LBD      (NPS_JID + 1)
  { 0, 0, 0, ARC_OPERAND_ADDRTYPE | ARC_OPERAND_NCHK, insert_nps_lbd, extract_nps_lbd },

#define NPS_MBD      (NPS_LBD + 1)
  { 0, 0, 0, ARC_OPERAND_ADDRTYPE | ARC_OPERAND_NCHK, insert_nps_mbd, extract_nps_mbd },

#define NPS_SD      (NPS_MBD + 1)
  { 0, 0, 0, ARC_OPERAND_ADDRTYPE | ARC_OPERAND_NCHK, insert_nps_sd, extract_nps_sd },

#define NPS_SM      (NPS_SD + 1)
  { 0, 0, 0, ARC_OPERAND_ADDRTYPE | ARC_OPERAND_NCHK, insert_nps_sm, extract_nps_sm },

#define NPS_XA      (NPS_SM + 1)
  { 0, 0, 0, ARC_OPERAND_ADDRTYPE | ARC_OPERAND_NCHK, insert_nps_xa, extract_nps_xa },

#define NPS_XD      (NPS_XA + 1)
  { 0, 0, 0, ARC_OPERAND_ADDRTYPE | ARC_OPERAND_NCHK, insert_nps_xd, extract_nps_xd },

#define NPS_CD      (NPS_XD + 1)
  { 0, 0, 0, ARC_OPERAND_ADDRTYPE | ARC_OPERAND_NCHK, insert_nps_cd, extract_nps_cd },

#define NPS_CBD      (NPS_CD + 1)
  { 0, 0, 0, ARC_OPERAND_ADDRTYPE | ARC_OPERAND_NCHK, insert_nps_cbd, extract_nps_cbd },

#define NPS_CJID      (NPS_CBD + 1)
  { 0, 0, 0, ARC_OPERAND_ADDRTYPE | ARC_OPERAND_NCHK, insert_nps_cjid, extract_nps_cjid },

#define NPS_CLBD      (NPS_CJID + 1)
  { 0, 0, 0, ARC_OPERAND_ADDRTYPE | ARC_OPERAND_NCHK, insert_nps_clbd, extract_nps_clbd },

#define NPS_CM      (NPS_CLBD + 1)
  { 0, 0, 0, ARC_OPERAND_ADDRTYPE | ARC_OPERAND_NCHK, insert_nps_cm, extract_nps_cm },

#define NPS_CSD      (NPS_CM + 1)
  { 0, 0, 0, ARC_OPERAND_ADDRTYPE | ARC_OPERAND_NCHK, insert_nps_csd, extract_nps_csd },

#define NPS_CXA      (NPS_CSD + 1)
  { 0, 0, 0, ARC_OPERAND_ADDRTYPE | ARC_OPERAND_NCHK, insert_nps_cxa, extract_nps_cxa },

#define NPS_CXD      (NPS_CXA + 1)
  { 0, 0, 0, ARC_OPERAND_ADDRTYPE | ARC_OPERAND_NCHK, insert_nps_cxd, extract_nps_cxd },

#define NPS_BD_TYPE     (NPS_CXD + 1)
  { 1, 10, 0, ARC_OPERAND_UNSIGNED, NULL, NULL },

#define NPS_BMU_NUM     (NPS_BD_TYPE + 1)
  { 3, 0, 0, ARC_OPERAND_UNSIGNED | ARC_OPERAND_NCHK, insert_nps_bd_num_buff, extract_nps_bd_num_buff },

#define NPS_PMU_NXT_DST     (NPS_BMU_NUM + 1)
  { 4, 6, 0, ARC_OPERAND_UNSIGNED, NULL, NULL },

#define NPS_PMU_NUM_JOB     (NPS_PMU_NXT_DST + 1)
  { 2, 6, 0, ARC_OPERAND_UNSIGNED | ARC_OPERAND_NCHK, insert_nps_pmu_num_job, extract_nps_pmu_num_job },

#define NPS_R_DST_3B_48	(NPS_PMU_NUM_JOB + 1)
  { 3, 40, 0, ARC_OPERAND_IR | ARC_OPERAND_NCHK, insert_nps_3bit_reg_at_40_dst, extract_nps_3bit_reg_at_40_dst },

#define NPS_R_SRC1_3B_48	(NPS_R_DST_3B_48 + 1)
  { 3, 40, 0, ARC_OPERAND_IR | ARC_OPERAND_DUPLICATE | ARC_OPERAND_NCHK, insert_nps_3bit_reg_at_40_dst, extract_nps_3bit_reg_at_40_dst },

#define NPS_R_SRC2_3B_48	(NPS_R_SRC1_3B_48 + 1)
  { 3, 37, 0, ARC_OPERAND_IR | ARC_OPERAND_NCHK, insert_nps_3bit_reg_at_37_src2, extract_nps_3bit_reg_at_37_src2 },

#define NPS_R_DST_3B_64		(NPS_R_SRC2_3B_48 + 1)
  { 3, 56, 0, ARC_OPERAND_IR | ARC_OPERAND_NCHK, insert_nps_3bit_reg_at_56_dst, extract_nps_3bit_reg_at_56_dst },

#define NPS_R_SRC1_3B_64	(NPS_R_DST_3B_64 + 1)
  { 3, 56, 0, ARC_OPERAND_IR | ARC_OPERAND_DUPLICATE | ARC_OPERAND_NCHK, insert_nps_3bit_reg_at_56_dst, extract_nps_3bit_reg_at_56_dst },

#define NPS_R_SRC2_3B_64	(NPS_R_SRC1_3B_64 + 1)
  { 3, 53, 0, ARC_OPERAND_IR | ARC_OPERAND_NCHK, insert_nps_3bit_reg_at_53_src2, extract_nps_3bit_reg_at_53_src2 },

#define NPS_RA_64               (NPS_R_SRC2_3B_64 + 1)
  { 6, 53, 0, ARC_OPERAND_IR, NULL, NULL },

#define NPS_RB_64               (NPS_RA_64 + 1)
  { 5, 48, 0, ARC_OPERAND_IR, NULL, NULL },

#define NPS_RBdup_64            (NPS_RB_64 + 1)
  { 5, 43, 0, ARC_OPERAND_IR | ARC_OPERAND_DUPLICATE, NULL, NULL },

#define NPS_RBdouble_64         (NPS_RBdup_64 + 1)
  { 10, 43, 0, ARC_OPERAND_IR | ARC_OPERAND_NCHK, insert_nps_rbdouble_64, extract_nps_rbdouble_64 },

#define NPS_RC_64               (NPS_RBdouble_64 + 1)
  { 5, 43, 0, ARC_OPERAND_IR, NULL, NULL },

#define NPS_UIMM16_0_64         (NPS_RC_64 + 1)
  { 16, 0, 0, ARC_OPERAND_UNSIGNED, NULL, NULL },

#define NPS_PROTO_SIZE         (NPS_UIMM16_0_64 + 1)
  { 6, 16, 0, ARC_OPERAND_UNSIGNED | ARC_OPERAND_NCHK, insert_nps_proto_size, extract_nps_proto_size }
};

/* The flag operands table.

   The format of the table is
   NAME CODE BITS SHIFT FAVAIL.  */
const struct arc_flag_operand arc_flag_operands[] =
{
#define F_NULL	0
  { 0, 0, 0, 0, 0},
#define F_ALWAYS    (F_NULL + 1)
  { "al", 0, 0, 0, 0 },
#define F_RA	    (F_ALWAYS + 1)
  { "ra", 0, 0, 0, 0 },
#define F_EQUAL	    (F_RA + 1)
  { "eq", 1, 5, 0, 1 },
#define F_ZERO	    (F_EQUAL + 1)
  { "z",  1, 5, 0, 0 },
#define F_NOTEQUAL  (F_ZERO + 1)
  { "ne", 2, 5, 0, 1 },
#define F_NOTZERO   (F_NOTEQUAL + 1)
  { "nz", 2, 5, 0, 0 },
#define F_POZITIVE  (F_NOTZERO + 1)
  { "p",  3, 5, 0, 1 },
#define F_PL	    (F_POZITIVE + 1)
  { "pl", 3, 5, 0, 0 },
#define F_NEGATIVE  (F_PL + 1)
  { "n",  4, 5, 0, 1 },
#define F_MINUS	    (F_NEGATIVE + 1)
  { "mi", 4, 5, 0, 0 },
#define F_CARRY	    (F_MINUS + 1)
  { "c",  5, 5, 0, 1 },
#define F_CARRYSET  (F_CARRY + 1)
  { "cs", 5, 5, 0, 0 },
#define F_LOWER	    (F_CARRYSET + 1)
  { "lo", 5, 5, 0, 0 },
#define F_CARRYCLR  (F_LOWER + 1)
  { "cc", 6, 5, 0, 0 },
#define F_NOTCARRY (F_CARRYCLR + 1)
  { "nc", 6, 5, 0, 1 },
#define F_HIGHER   (F_NOTCARRY + 1)
  { "hs", 6, 5, 0, 0 },
#define F_OVERFLOWSET (F_HIGHER + 1)
  { "vs", 7, 5, 0, 0 },
#define F_OVERFLOW (F_OVERFLOWSET + 1)
  { "v",  7, 5, 0, 1 },
#define F_NOTOVERFLOW (F_OVERFLOW + 1)
  { "nv", 8, 5, 0, 1 },
#define F_OVERFLOWCLR (F_NOTOVERFLOW + 1)
  { "vc", 8, 5, 0, 0 },
#define F_GT	   (F_OVERFLOWCLR + 1)
  { "gt", 9, 5, 0, 1 },
#define F_GE	   (F_GT + 1)
  { "ge", 10, 5, 0, 1 },
#define F_LT	   (F_GE + 1)
  { "lt", 11, 5, 0, 1 },
#define F_LE	   (F_LT + 1)
  { "le", 12, 5, 0, 1 },
#define F_HI	   (F_LE + 1)
  { "hi", 13, 5, 0, 1 },
#define F_LS	   (F_HI + 1)
  { "ls", 14, 5, 0, 1 },
#define F_PNZ	   (F_LS + 1)
  { "pnz", 15, 5, 0, 1 },

  /* FLAG.  */
#define F_FLAG     (F_PNZ + 1)
  { "f",  1, 1, 15, 1 },
#define F_FFAKE     (F_FLAG + 1)
  { "f",  0, 0, 0, 1 },

  /* Delay slot.  */
#define F_ND	   (F_FFAKE + 1)
  { "nd", 0, 1, 5, 0 },
#define F_D	   (F_ND + 1)
  { "d",  1, 1, 5, 1 },
#define F_DFAKE	   (F_D + 1)
  { "d",  0, 0, 0, 1 },
#define F_DNZ_ND   (F_DFAKE + 1)
  { "nd", 0, 1, 16, 0 },
#define F_DNZ_D	   (F_DNZ_ND + 1)
  { "d",  1, 1, 16, 1 },

  /* Data size.  */
#define F_SIZEB1   (F_DNZ_D + 1)
  { "b", 1, 2, 1, 1 },
#define F_SIZEB7   (F_SIZEB1 + 1)
  { "b", 1, 2, 7, 1 },
#define F_SIZEB17  (F_SIZEB7 + 1)
  { "b", 1, 2, 17, 1 },
#define F_SIZEW1   (F_SIZEB17 + 1)
  { "w", 2, 2, 1, 0 },
#define F_SIZEW7   (F_SIZEW1 + 1)
  { "w", 2, 2, 7, 0 },
#define F_SIZEW17  (F_SIZEW7 + 1)
  { "w", 2, 2, 17, 0 },

  /* Sign extension.  */
#define F_SIGN6   (F_SIZEW17 + 1)
  { "x", 1, 1, 6, 1 },
#define F_SIGN16  (F_SIGN6 + 1)
  { "x", 1, 1, 16, 1 },
#define F_SIGNX   (F_SIGN16 + 1)
  { "x", 0, 0, 0, 1 },

  /* Address write-back modes.  */
#define F_A3       (F_SIGNX + 1)
  { "a", 1, 2, 3, 0 },
#define F_A9       (F_A3 + 1)
  { "a", 1, 2, 9, 0 },
#define F_A22      (F_A9 + 1)
  { "a", 1, 2, 22, 0 },
#define F_AW3      (F_A22 + 1)
  { "aw", 1, 2, 3, 1 },
#define F_AW9      (F_AW3 + 1)
  { "aw", 1, 2, 9, 1 },
#define F_AW22     (F_AW9 + 1)
  { "aw", 1, 2, 22, 1 },
#define F_AB3      (F_AW22 + 1)
  { "ab", 2, 2, 3, 1 },
#define F_AB9      (F_AB3 + 1)
  { "ab", 2, 2, 9, 1 },
#define F_AB22     (F_AB9 + 1)
  { "ab", 2, 2, 22, 1 },
#define F_AS3      (F_AB22 + 1)
  { "as", 3, 2, 3, 1 },
#define F_AS9      (F_AS3 + 1)
  { "as", 3, 2, 9, 1 },
#define F_AS22     (F_AS9 + 1)
  { "as", 3, 2, 22, 1 },
#define F_ASFAKE   (F_AS22 + 1)
  { "as", 0, 0, 0, 1 },

  /* Cache bypass.  */
#define F_DI5     (F_ASFAKE + 1)
  { "di", 1, 1, 5, 1 },
#define F_DI11    (F_DI5 + 1)
  { "di", 1, 1, 11, 1 },
#define F_DI14    (F_DI11 + 1)
  { "di", 1, 1, 14, 1 },
#define F_DI15    (F_DI14 + 1)
  { "di", 1, 1, 15, 1 },

  /* ARCv2 specific.  */
#define F_NT     (F_DI15 + 1)
  { "nt", 0, 1, 3, 1},
#define F_T      (F_NT + 1)
  { "t", 1, 1, 3, 1},
#define F_H1     (F_T + 1)
  { "h", 2, 2, 1, 1 },
#define F_H7     (F_H1 + 1)
  { "h", 2, 2, 7, 1 },
#define F_H17    (F_H7 + 1)
  { "h", 2, 2, 17, 1 },
#define F_SIZED  (F_H17 + 1)
  { "dd", 8, 0, 0, 0 },  /* Fake.  */

  /* Fake Flags.  */
#define F_NE   (F_SIZED + 1)
  { "ne", 0, 0, 0, 1 },

  /* ARC NPS400 Support: See comment near head of file.  */
#define F_NPS_CL (F_NE + 1)
  { "cl", 0, 0, 0, 1 },

#define F_NPS_FLAG (F_NPS_CL + 1)
  { "f", 1, 1, 20, 1 },

#define F_NPS_R     (F_NPS_FLAG + 1)
  { "r",  1, 1, 15, 1 },

#define F_NPS_RW     (F_NPS_R + 1)
  { "rw", 0, 1, 7, 1 },

#define F_NPS_RD     (F_NPS_RW + 1)
  { "rd", 1, 1, 7, 1 },

#define F_NPS_WFT     (F_NPS_RD + 1)
  { "wft", 0, 0, 0, 1 },

#define F_NPS_IE1     (F_NPS_WFT + 1)
  { "ie1", 1, 2, 8, 1 },

#define F_NPS_IE2     (F_NPS_IE1 + 1)
  { "ie2", 2, 2, 8, 1 },

#define F_NPS_IE12     (F_NPS_IE2 + 1)
  { "ie12", 3, 2, 8, 1 },

#define F_NPS_SYNC_RD     (F_NPS_IE12 + 1)
  { "rd", 0, 1, 6, 1 },

#define F_NPS_SYNC_WR     (F_NPS_SYNC_RD + 1)
  { "wr", 1, 1, 6, 1 },

#define F_NPS_HWS_OFF     (F_NPS_SYNC_WR + 1)
  { "off", 0, 0, 0, 1 },

#define F_NPS_HWS_RESTORE     (F_NPS_HWS_OFF + 1)
  { "restore", 0, 0, 0, 1 },

#define F_NPS_SX     (F_NPS_HWS_RESTORE + 1)
  { "sx",  1, 1, 14, 1 },

#define F_NPS_AR     (F_NPS_SX + 1)
  { "ar",  0, 1, 0, 1 },

#define F_NPS_AL     (F_NPS_AR + 1)
  { "al",  1, 1, 0, 1 },

#define F_NPS_S      (F_NPS_AL + 1)
  { "s",   0, 0, 0, 1 },

#define F_NPS_ZNCV_RD      (F_NPS_S + 1)
  { "rd",  0, 1, 15, 1 },

#define F_NPS_ZNCV_WR      (F_NPS_ZNCV_RD + 1)
  { "wr",  1, 1, 15, 1 },

#define F_NPS_P0      (F_NPS_ZNCV_WR + 1)
  { "p0", 0, 0, 0, 1 },

#define F_NPS_P1      (F_NPS_P0 + 1)
  { "p1", 0, 0, 0, 1 },

#define F_NPS_P2      (F_NPS_P1 + 1)
  { "p2", 0, 0, 0, 1 },

#define F_NPS_P3      (F_NPS_P2 + 1)
  { "p3", 0, 0, 0, 1 },

#define F_NPS_LDBIT_DI      (F_NPS_P3 + 1)
  { "di", 0, 0, 0, 1 },

#define F_NPS_LDBIT_CL1      (F_NPS_LDBIT_DI + 1)
  { "cl", 1, 1, 6, 1 },

#define F_NPS_LDBIT_CL2      (F_NPS_LDBIT_CL1 + 1)
  { "cl", 1, 1, 16, 1 },

#define F_NPS_LDBIT_X2_1      (F_NPS_LDBIT_CL2 + 1)
  { "x2", 1, 2, 9, 1 },

#define F_NPS_LDBIT_X2_2      (F_NPS_LDBIT_X2_1 + 1)
  { "x2", 1, 2, 22, 1 },

#define F_NPS_LDBIT_X4_1      (F_NPS_LDBIT_X2_2 + 1)
  { "x4", 2, 2, 9, 1 },

#define F_NPS_LDBIT_X4_2      (F_NPS_LDBIT_X4_1 + 1)
  { "x4", 2, 2, 22, 1 },
};

/* Table of the flag classes.

   The format of the table is
   CLASS {FLAG_CODE}.  */
const struct arc_flag_class arc_flag_classes[] =
{
#define C_EMPTY     0
  { F_CLASS_NONE, { F_NULL } },

#define C_CC_EQ     (C_EMPTY + 1)
  {F_CLASS_IMPLICIT | F_CLASS_COND, {F_EQUAL, F_NULL} },

#define C_CC_GE     (C_CC_EQ + 1)
  {F_CLASS_IMPLICIT | F_CLASS_COND, {F_GE, F_NULL} },

#define C_CC_GT     (C_CC_GE + 1)
  {F_CLASS_IMPLICIT | F_CLASS_COND, {F_GT, F_NULL} },

#define C_CC_HI     (C_CC_GT + 1)
  {F_CLASS_IMPLICIT | F_CLASS_COND, {F_HI, F_NULL} },

#define C_CC_HS     (C_CC_HI + 1)
  {F_CLASS_IMPLICIT | F_CLASS_COND, {F_NOTCARRY, F_NULL} },

#define C_CC_LE     (C_CC_HS + 1)
  {F_CLASS_IMPLICIT | F_CLASS_COND, {F_LE, F_NULL} },

#define C_CC_LO     (C_CC_LE + 1)
  {F_CLASS_IMPLICIT | F_CLASS_COND, {F_CARRY, F_NULL} },

#define C_CC_LS     (C_CC_LO + 1)
  {F_CLASS_IMPLICIT | F_CLASS_COND, {F_LS, F_NULL} },

#define C_CC_LT     (C_CC_LS + 1)
  {F_CLASS_IMPLICIT | F_CLASS_COND, {F_LT, F_NULL} },

#define C_CC_NE     (C_CC_LT + 1)
  {F_CLASS_IMPLICIT | F_CLASS_COND, {F_NOTEQUAL, F_NULL} },

#define C_AA_AB     (C_CC_NE + 1)
  {F_CLASS_IMPLICIT | F_CLASS_WB, {F_AB3, F_NULL} },

#define C_AA_AW     (C_AA_AB + 1)
  {F_CLASS_IMPLICIT | F_CLASS_WB, {F_AW3, F_NULL} },

#define C_ZZ_D      (C_AA_AW + 1)
  {F_CLASS_IMPLICIT | F_CLASS_ZZ, {F_SIZED, F_NULL} },

#define C_ZZ_H      (C_ZZ_D + 1)
  {F_CLASS_IMPLICIT | F_CLASS_ZZ, {F_H1, F_NULL} },

#define C_ZZ_B      (C_ZZ_H + 1)
  {F_CLASS_IMPLICIT | F_CLASS_ZZ, {F_SIZEB1, F_NULL} },

#define C_CC	    (C_ZZ_B + 1)
  { F_CLASS_OPTIONAL | F_CLASS_EXTEND | F_CLASS_COND,
    { F_ALWAYS, F_RA, F_EQUAL, F_ZERO, F_NOTEQUAL,
      F_NOTZERO, F_POZITIVE, F_PL, F_NEGATIVE, F_MINUS,
      F_CARRY, F_CARRYSET, F_LOWER, F_CARRYCLR,
      F_NOTCARRY, F_HIGHER, F_OVERFLOWSET, F_OVERFLOW,
      F_NOTOVERFLOW, F_OVERFLOWCLR, F_GT, F_GE, F_LT,
      F_LE, F_HI, F_LS, F_PNZ, F_NULL } },

#define C_AA_ADDR3  (C_CC + 1)
#define C_AA27	    (C_CC + 1)
  { F_CLASS_OPTIONAL | F_CLASS_WB, { F_A3, F_AW3, F_AB3, F_AS3, F_NULL } },
#define C_AA_ADDR9  (C_AA_ADDR3 + 1)
#define C_AA21	     (C_AA_ADDR3 + 1)
  { F_CLASS_OPTIONAL | F_CLASS_WB, { F_A9, F_AW9, F_AB9, F_AS9, F_NULL } },
#define C_AA_ADDR22 (C_AA_ADDR9 + 1)
#define C_AA8	   (C_AA_ADDR9 + 1)
  { F_CLASS_OPTIONAL | F_CLASS_WB, { F_A22, F_AW22, F_AB22, F_AS22, F_NULL } },

#define C_F	    (C_AA_ADDR22 + 1)
  { F_CLASS_OPTIONAL | F_CLASS_F, { F_FLAG, F_NULL } },
#define C_FHARD	    (C_F + 1)
  { F_CLASS_OPTIONAL | F_CLASS_F, { F_FFAKE, F_NULL } },

#define C_T	    (C_FHARD + 1)
  { F_CLASS_OPTIONAL, { F_NT, F_T, F_NULL } },
#define C_D	    (C_T + 1)
  { F_CLASS_OPTIONAL | F_CLASS_D, { F_ND, F_D, F_NULL } },
#define C_DNZ_D     (C_D + 1)
  { F_CLASS_OPTIONAL | F_CLASS_D, { F_DNZ_ND, F_DNZ_D, F_NULL } },

#define C_DHARD	    (C_DNZ_D + 1)
  { F_CLASS_OPTIONAL | F_CLASS_D, { F_DFAKE, F_NULL } },

#define C_DI20	    (C_DHARD + 1)
  { F_CLASS_OPTIONAL | F_CLASS_DI, { F_DI11, F_NULL }},
#define C_DI14	    (C_DI20 + 1)
  { F_CLASS_OPTIONAL | F_CLASS_DI, { F_DI14, F_NULL }},
#define C_DI16	    (C_DI14 + 1)
  { F_CLASS_OPTIONAL | F_CLASS_DI, { F_DI15, F_NULL }},
#define C_DI26	    (C_DI16 + 1)
  { F_CLASS_OPTIONAL | F_CLASS_DI, { F_DI5, F_NULL }},

#define C_X25	    (C_DI26 + 1)
  { F_CLASS_OPTIONAL | F_CLASS_X, { F_SIGN6, F_NULL }},
#define C_X15	   (C_X25 + 1)
  { F_CLASS_OPTIONAL | F_CLASS_X, { F_SIGN16, F_NULL }},
#define C_XHARD	   (C_X15 + 1)
#define C_X	   (C_X15 + 1)
  { F_CLASS_OPTIONAL | F_CLASS_X, { F_SIGNX, F_NULL }},

#define C_ZZ13	      (C_X + 1)
  { F_CLASS_OPTIONAL | F_CLASS_ZZ, { F_SIZEB17, F_SIZEW17, F_H17, F_NULL}},
#define C_ZZ23	      (C_ZZ13 + 1)
  { F_CLASS_OPTIONAL | F_CLASS_ZZ, { F_SIZEB7, F_SIZEW7, F_H7, F_NULL}},
#define C_ZZ29	      (C_ZZ23 + 1)
  { F_CLASS_OPTIONAL | F_CLASS_ZZ, { F_SIZEB1, F_SIZEW1, F_H1, F_NULL}},

#define C_AS	    (C_ZZ29 + 1)
  { F_CLASS_OPTIONAL | F_CLASS_WB, { F_ASFAKE, F_NULL}},

#define C_NE	    (C_AS + 1)
  { F_CLASS_OPTIONAL | F_CLASS_COND, { F_NE, F_NULL}},

  /* ARC NPS400 Support: See comment near head of file.  */
#define C_NPS_CL     (C_NE + 1)
  { F_CLASS_REQUIRED, { F_NPS_CL, F_NULL}},

#define C_NPS_F     (C_NPS_CL + 1)
  { F_CLASS_OPTIONAL, { F_NPS_FLAG, F_NULL}},

#define C_NPS_R     (C_NPS_F + 1)
  { F_CLASS_OPTIONAL, { F_NPS_R, F_NULL}},

#define C_NPS_SCHD_RW     (C_NPS_R + 1)
  { F_CLASS_REQUIRED, { F_NPS_RW, F_NPS_RD, F_NULL}},

#define C_NPS_SCHD_TRIG     (C_NPS_SCHD_RW + 1)
  { F_CLASS_REQUIRED, { F_NPS_WFT, F_NULL}},

#define C_NPS_SCHD_IE     (C_NPS_SCHD_TRIG + 1)
  { F_CLASS_OPTIONAL, { F_NPS_IE1, F_NPS_IE2, F_NPS_IE12, F_NULL}},

#define C_NPS_SYNC     (C_NPS_SCHD_IE + 1)
  { F_CLASS_REQUIRED, { F_NPS_SYNC_RD, F_NPS_SYNC_WR, F_NULL}},

#define C_NPS_HWS_OFF     (C_NPS_SYNC + 1)
  { F_CLASS_REQUIRED, { F_NPS_HWS_OFF, F_NULL}},

#define C_NPS_HWS_RESTORE     (C_NPS_HWS_OFF + 1)
  { F_CLASS_REQUIRED, { F_NPS_HWS_RESTORE, F_NULL}},

#define C_NPS_SX     (C_NPS_HWS_RESTORE + 1)
  { F_CLASS_OPTIONAL, { F_NPS_SX, F_NULL}},

#define C_NPS_AR_AL     (C_NPS_SX + 1)
  { F_CLASS_REQUIRED, { F_NPS_AR, F_NPS_AL, F_NULL}},

#define C_NPS_S    (C_NPS_AR_AL + 1)
  { F_CLASS_REQUIRED, { F_NPS_S, F_NULL}},

#define C_NPS_ZNCV    (C_NPS_S + 1)
  { F_CLASS_REQUIRED, { F_NPS_ZNCV_RD, F_NPS_ZNCV_WR, F_NULL}},

#define C_NPS_P0    (C_NPS_ZNCV + 1)
  { F_CLASS_REQUIRED, { F_NPS_P0, F_NULL }},

#define C_NPS_P1    (C_NPS_P0 + 1)
  { F_CLASS_REQUIRED, { F_NPS_P1, F_NULL }},

#define C_NPS_P2    (C_NPS_P1 + 1)
  { F_CLASS_REQUIRED, { F_NPS_P2, F_NULL }},

#define C_NPS_P3    (C_NPS_P2 + 1)
  { F_CLASS_REQUIRED, { F_NPS_P3, F_NULL }},

#define C_NPS_LDBIT_DI    (C_NPS_P3 + 1)
  { F_CLASS_REQUIRED, { F_NPS_LDBIT_DI, F_NULL }},

#define C_NPS_LDBIT_CL1    (C_NPS_LDBIT_DI + 1)
  { F_CLASS_OPTIONAL, { F_NPS_LDBIT_CL1, F_NULL }},

#define C_NPS_LDBIT_CL2    (C_NPS_LDBIT_CL1 + 1)
  { F_CLASS_OPTIONAL, { F_NPS_LDBIT_CL2, F_NULL }},

#define C_NPS_LDBIT_X_1    (C_NPS_LDBIT_CL2 + 1)
  { F_CLASS_OPTIONAL, { F_NPS_LDBIT_X2_1, F_NPS_LDBIT_X4_1, F_NULL }},

#define C_NPS_LDBIT_X_2    (C_NPS_LDBIT_X_1 + 1)
  { F_CLASS_OPTIONAL, { F_NPS_LDBIT_X2_2, F_NPS_LDBIT_X4_2, F_NULL }},
};

/* List with special cases instructions and the applicable flags.  */
const struct arc_flag_special arc_flag_special_cases[] =
{
  { "b", { F_ALWAYS, F_RA, F_EQUAL, F_ZERO, F_NOTEQUAL, F_NOTZERO, F_POZITIVE,
	   F_PL, F_NEGATIVE, F_MINUS, F_CARRY, F_CARRYSET, F_LOWER, F_CARRYCLR,
	   F_NOTCARRY, F_HIGHER, F_OVERFLOWSET, F_OVERFLOW, F_NOTOVERFLOW,
	   F_OVERFLOWCLR, F_GT, F_GE, F_LT, F_LE, F_HI, F_LS, F_PNZ, F_NULL } },
  { "bl", { F_ALWAYS, F_RA, F_EQUAL, F_ZERO, F_NOTEQUAL, F_NOTZERO, F_POZITIVE,
	    F_PL, F_NEGATIVE, F_MINUS, F_CARRY, F_CARRYSET, F_LOWER, F_CARRYCLR,
	    F_NOTCARRY, F_HIGHER, F_OVERFLOWSET, F_OVERFLOW, F_NOTOVERFLOW,
	    F_OVERFLOWCLR, F_GT, F_GE, F_LT, F_LE, F_HI, F_LS, F_PNZ, F_NULL } },
  { "br", { F_ALWAYS, F_RA, F_EQUAL, F_ZERO, F_NOTEQUAL, F_NOTZERO, F_POZITIVE,
	    F_PL, F_NEGATIVE, F_MINUS, F_CARRY, F_CARRYSET, F_LOWER, F_CARRYCLR,
	    F_NOTCARRY, F_HIGHER, F_OVERFLOWSET, F_OVERFLOW, F_NOTOVERFLOW,
	    F_OVERFLOWCLR, F_GT, F_GE, F_LT, F_LE, F_HI, F_LS, F_PNZ, F_NULL } },
  { "j", { F_ALWAYS, F_RA, F_EQUAL, F_ZERO, F_NOTEQUAL, F_NOTZERO, F_POZITIVE,
	   F_PL, F_NEGATIVE, F_MINUS, F_CARRY, F_CARRYSET, F_LOWER, F_CARRYCLR,
	   F_NOTCARRY, F_HIGHER, F_OVERFLOWSET, F_OVERFLOW, F_NOTOVERFLOW,
	   F_OVERFLOWCLR, F_GT, F_GE, F_LT, F_LE, F_HI, F_LS, F_PNZ, F_NULL } },
  { "jl", { F_ALWAYS, F_RA, F_EQUAL, F_ZERO, F_NOTEQUAL, F_NOTZERO, F_POZITIVE,
	    F_PL, F_NEGATIVE, F_MINUS, F_CARRY, F_CARRYSET, F_LOWER, F_CARRYCLR,
	    F_NOTCARRY, F_HIGHER, F_OVERFLOWSET, F_OVERFLOW, F_NOTOVERFLOW,
	    F_OVERFLOWCLR, F_GT, F_GE, F_LT, F_LE, F_HI, F_LS, F_PNZ, F_NULL } },
  { "lp", { F_ALWAYS, F_RA, F_EQUAL, F_ZERO, F_NOTEQUAL, F_NOTZERO, F_POZITIVE,
	    F_PL, F_NEGATIVE, F_MINUS, F_CARRY, F_CARRYSET, F_LOWER, F_CARRYCLR,
	    F_NOTCARRY, F_HIGHER, F_OVERFLOWSET, F_OVERFLOW, F_NOTOVERFLOW,
	    F_OVERFLOWCLR, F_GT, F_GE, F_LT, F_LE, F_HI, F_LS, F_PNZ, F_NULL } },
  { "set", { F_ALWAYS, F_RA, F_EQUAL, F_ZERO, F_NOTEQUAL, F_NOTZERO, F_POZITIVE,
	     F_PL, F_NEGATIVE, F_MINUS, F_CARRY, F_CARRYSET, F_LOWER, F_CARRYCLR,
	     F_NOTCARRY, F_HIGHER, F_OVERFLOWSET, F_OVERFLOW, F_NOTOVERFLOW,
	     F_OVERFLOWCLR, F_GT, F_GE, F_LT, F_LE, F_HI, F_LS, F_PNZ, F_NULL } },
  { "ld", { F_SIZEB17, F_SIZEW17, F_H17, F_NULL } },
  { "st", { F_SIZEB1, F_SIZEW1, F_H1, F_NULL } }
};

const unsigned arc_num_flag_special = ARRAY_SIZE (arc_flag_special_cases);

/* The opcode table.

   The format of the opcode table is:

   NAME OPCODE MASK CPU CLASS SUBCLASS { OPERANDS } { FLAGS }.

   The table is organised such that, where possible, all instructions with
   the same mnemonic are together in a block.  When the assembler searches
   for a suitable instruction the entries are checked in table order, so
   more specific, or specialised cases should appear earlier in the table.

   As an example, consider two instructions 'add a,b,u6' and 'add
   a,b,limm'.  The first takes a 6-bit immediate that is encoded within the
   32-bit instruction, while the second takes a 32-bit immediate that is
   encoded in a follow-on 32-bit, making the total instruction length
   64-bits.  In this case the u6 variant must appear first in the table, as
   all u6 immediates could also be encoded using the 'limm' extension,
   however, we want to use the shorter instruction wherever possible.

   It is possible though to split instructions with the same mnemonic into
   multiple groups.  However, the instructions are still checked in table
   order, even across groups.  The only time that instructions with the
   same mnemonic should be split into different groups is when different
   variants of the instruction appear in different architectures, in which
   case, grouping all instructions from a particular architecture together
   might be preferable to merging the instruction into the main instruction
   table.

   An example of this split instruction groups can be found with the 'sync'
   instruction.  The core arc architecture provides a 'sync' instruction,
   while the nps instruction set extension provides 'sync.rd' and
   'sync.wr'.  The rd/wr flags are instruction flags, not part of the
   mnemonic, so we end up with two groups for the sync instruction, the
   first within the core arc instruction table, and the second within the
   nps extension instructions.  */
const struct arc_opcode arc_opcodes[] =
{
#include "arc-tbl.h"
  { NULL, 0, 0, 0, 0, 0, { 0 }, { 0 } }
};

/* Return length of an opcode in bytes.  */

static uint8_t
arc_opcode_len (const struct arc_opcode *opcode)
{
  if (opcode->mask < 0x10000ull)
    return 2;

  if (opcode->mask < 0x100000000ull)
    return 4;

  if (opcode->mask < 0x1000000000000ull)
    return 6;

  return 8;
}

/* Arrange to middle endian, used by LITTLE ENDIAN systems.  */

static uint32_t
arc_getm32 (uint32_t data)
{
  uint32_t value = 0;

  value = ((data & 0xff00) | (data & 0xff)) << 16;
  value |= ((data & 0xff0000) | (data & 0xff000000)) >> 16;
  return value;
}

/* Calculate the instruction length for an instruction starting with
   MSB and LSB, the most and least significant byte.  The ISA_MASK is
   used to filter the instructions considered to only those that are
   part of the current architecture.

   The instruction lengths are calculated from the ARC_OPCODE table,
   and cached for later use.  */

unsigned int
arc_insn_length (uint16_t insn, uint16_t cpu_type)
{
  uint8_t major_opcode;
  uint8_t msb, lsb;

  msb = (uint8_t)(insn >> 8);
  lsb = (uint8_t)(insn & 0xFF);
  major_opcode = msb >> 3;

  switch (cpu_type)
    {
    case ARC_OPCODE_ARC700:
      /* The nps400 extension set requires this special casing of the
	 instruction length calculation.  Right now this is not causing any
	 problems as none of the known extensions overlap in opcode space,
	 but, if they ever do then we might need to start carrying
	 information around in the elf about which extensions are in use.  */
      if (major_opcode == 0xb)
	{
	  uint8_t minor_opcode = lsb & 0x1f;

	  if (minor_opcode < 4)
	    return 6;
	  else if (minor_opcode == 0x10 || minor_opcode == 0x11)
	    return 8;
	}
      if (major_opcode == 0xa)
	{
	  return 8;
	}
      /* Fall through.  */
    case ARC_OPCODE_ARC600:
      return (major_opcode > 0xb) ? 2 : 4;
      break;

    case ARC_OPCODE_ARCv2EM:
    case ARC_OPCODE_ARCv2HS:
      return (major_opcode > 0x7) ? 2 : 4;
      break;

    default:
      abort ();
    }
}

static const struct arc_opcode *
find_format (insn_t *pinsn, uint64_t insn, uint8_t insn_len, uint32_t isa_mask)
{
  uint32_t i = 0;
  const struct arc_opcode *opcode = NULL;
  const uint8_t *opidx;
  const uint8_t *flgidx;
  bool has_limm = false;

  do {
    bool invalid = false;
    uint32_t noperands = 0;

    opcode = &arc_opcodes[i++];
    memset (pinsn, 0, sizeof (*pinsn));

    if (!(opcode->cpu & isa_mask))
      continue;

    if (arc_opcode_len (opcode) != (int) insn_len)
      continue;

    if ((insn & opcode->mask) != opcode->opcode)
      continue;

    has_limm = false;

    /* Possible candidate, check the operands.  */
    for (opidx = opcode->operands; *opidx; opidx++)
      {
        int value, limmind;
        const struct arc_operand *operand = &arc_operands[*opidx];

        if (operand->flags & ARC_OPERAND_FAKE)
          continue;

        if (operand->extract)
          value = (*operand->extract) (insn, &invalid);
        else
          value = (insn >> operand->shift) & ((1 << operand->bits) - 1);

        /* Check for LIMM indicator.  If it is there, then make sure
           we pick the right format.  */
        limmind = (isa_mask & ARC_OPCODE_ARCV2) ? 0x1E : 0x3E;
        if (operand->flags & ARC_OPERAND_IR
            && !(operand->flags & ARC_OPERAND_LIMM))
          {
            if ((value == 0x3E && insn_len == 4)
                || (value == limmind && insn_len == 2))
              {
                invalid = TRUE;
                break;
              }
          }

        if (operand->flags & ARC_OPERAND_LIMM
            && !(operand->flags & ARC_OPERAND_DUPLICATE))
          has_limm = true;

        pinsn->operands[noperands].value = value;
        pinsn->operands[noperands].type = operand->flags;
	noperands += 1;
      }

    /* Check the flags.  */
    for (flgidx = opcode->flags; *flgidx; flgidx++)
      {
        /* Get a valid flag class.  */
        const struct arc_flag_class *cl_flags = &arc_flag_classes[*flgidx];
        const unsigned *flgopridx;
        bool foundA = false, foundB = false;
        unsigned int value;

        /* FIXME! Add check for EXTENSION flags.  */

        for (flgopridx = cl_flags->flags; *flgopridx; ++flgopridx)
          {
            const struct arc_flag_operand *flg_operand =
              &arc_flag_operands[*flgopridx];

            /* Check for the implicit flags.  */
            if (cl_flags->flag_class & F_CLASS_IMPLICIT)
              {
                if (cl_flags->flag_class & F_CLASS_COND)
                  pinsn->cc = flg_operand->code;
                else if (cl_flags->flag_class & F_CLASS_WB)
                  pinsn->aa = flg_operand->code;
                else if (cl_flags->flag_class & F_CLASS_ZZ)
                  pinsn->zz = flg_operand->code;
                continue;
              }

            value = (insn >> flg_operand->shift)
              & ((1 << flg_operand->bits) - 1);
            if (value == flg_operand->code)
              {
                if (cl_flags->flag_class & F_CLASS_ZZ)
                  switch (flg_operand->name[0])
                    {
                    case 'b':
                      pinsn->zz = 1;
                      break;
                    case 'h':
                    case 'w':
                      pinsn->zz = 2;
                      break;
                    default:
                      pinsn->zz = 4;
                      break;
                    }

		// TODO: This has a problem: instruction "b label" sets this to true.
                if (cl_flags->flag_class & F_CLASS_D)
                  pinsn->d = value ? true : false;

                if (cl_flags->flag_class & F_CLASS_COND)
                  pinsn->cc = value;

                if (cl_flags->flag_class & F_CLASS_WB)
                  pinsn->aa = value;

                if (cl_flags->flag_class & F_CLASS_F)
                  pinsn->f = true;

                if (cl_flags->flag_class & F_CLASS_DI)
                  pinsn->di = true;

                if (cl_flags->flag_class & F_CLASS_X)
                  pinsn->x = true;

                foundA = true;
              }
            if (value)
              foundB = true;
          }

        if (!foundA && foundB)
          {
            invalid = TRUE;
            break;
          }
      }

    if (invalid)
      continue;

    /* The instruction is valid.  */
    pinsn->limm_p = has_limm;
    pinsn->class = (uint32_t) opcode->insn_class;

    /* FIXME! here add extra info about the instruction e.g. delay
       slot, data size, write back, etc.  */
    return opcode;
  } while (opcode->mask);

  memset (pinsn, 0, sizeof (*pinsn));
  return NULL;
}

static bool
read_and_decode_context (DisasCtxt *ctx,
                         const struct arc_opcode **opcode_p)
{
  uint16_t buffer[2];
  uint8_t length;
  uint64_t insn;

  /* Read the first 16 bits, figure it out what kind of instruction it is.  */
  buffer[0] = cpu_lduw_code(ctx->env, ctx->cpc);
  length = arc_insn_length (buffer[0], ctx->env->family);

  switch (length)
    {
    case 2:
      /* 16-bit instructions.  */
      insn = (uint64_t) buffer[0];
      break;
    case 4:
      /* 32-bit instructions.  */
      buffer[1] = cpu_lduw_code(ctx->env, ctx->cpc + 2);
      uint32_t buf = (buffer[0] << 16) | buffer[1];
      insn = buf;
      break;
    default:
      abort ();
    }

  /* Now, we have read the entire opcode, decode it and place the
   * relevant info into opcode and ctx->insn.  */
  *opcode_p = find_format (&ctx->insn, insn, length, ctx->env->family);

  if (*opcode_p == NULL)
    return false;

  /* If the instruction requires long immediate, read the extra 4
   * bytes and initialize the relevant fields.  */
  if (ctx->insn.limm_p)
    {
      ctx->insn.limm = ARRANGE_ENDIAN (true,
                                       cpu_ldl_code (ctx->env,
                                                     ctx->cpc + length));
      length += 4;
    }
  else
    ctx->insn.limm = 0;

  /* Update context.  */
  ctx->insn.len = length;
  ctx->npc = ctx->cpc + length;
  ctx->pcl = ctx->cpc & 0xfffffffc;

  return true;
}

static int arc_gen_INVALID (DisasCtxt *ctx)
{
    printf("invalid inst @:%08x\n", ctx->cpc);
    return BS_NONE;
}

/* Helper to be used by the disassembler.  */

const struct arc_opcode *
arc_find_format (insn_t *insnd, uint64_t insn, uint8_t insn_len, uint32_t isa_mask)
{
  memset (insnd, 0, sizeof (*insnd));
  return find_format (insnd, insn, insn_len, isa_mask);
}

enum arc_opcode_map {
  MAP_NONE = -1,
#define MAPPING(...)
#define SEMANTIC_FUNCTION(NAME, NOPS, ...) \
  MAP_##NAME,
#include "arc-semfunc_mapping.h"
#undef MAPPING
#undef SEMANTIC_FUNCTION
  /* Add some include to generated files */
  MAP_LAST
};

const char
number_of_ops_semfunc[MAP_LAST + 1] = {
#define SEMANTIC_FUNCTION(NAME, NOPS, ...) NOPS,
#define MAPPING(...)
#include "arc-semfunc_mapping.h"
#undef MAPPING
#undef SEMANTIC_FUNCTION
    2
};

static enum arc_opcode_map
arc_map_opcode (const struct arc_opcode *opcode)
{
#define SEMANTIC_FUNCTION(...)
#define MAPPING(MNEMONIC, ENUM) \
  if(strcmp(opcode->name, #MNEMONIC) == 0) \
    return MAP_##ENUM;
#include "arc-semfunc_mapping.h"
#undef MAPPING
#undef SEMANTIC_FUNCTION
  return MAP_NONE;
}

static void
arc_debug_opcode(const struct arc_opcode *opcode, const char *msg)
{
  printf("%s for %s\n", msg, opcode->name);
}

static TCGv
arc2_decode_operand(DisasCtxt *ctx, unsigned char nop)
{
  TCGv ret;

  operand_t operand = ctx->insn.operands[nop];

  if(operand.type & ARC_OPERAND_IR)
    ret = cpu_r[operand.value];
  else
    {
      int32_t i = operand.value;
      if (operand.type & ARC_OPERAND_LIMM)
        i = ctx->insn.limm;

      ret = tcg_const_local_i32(i);
    }

  return ret;
}

int arc_decode (DisasCtxt *ctx)
{
  const struct arc_opcode *opcode = NULL;
  static bool should_stop = false;
  int ret = BS_NONE;
  enum arc_opcode_map mapping;

  /* Call the disassembler.  */
  if (!read_and_decode_context (ctx, &opcode))
    return arc_gen_INVALID (ctx);

  /* Do the mapping.  */
  if((mapping = arc_map_opcode (opcode)) != MAP_NONE)
    {
      TCGv ops[10];
      int i;
      for (i = 0; i < number_of_ops_semfunc[mapping]; i++)
        {
          ops[i] = arc2_decode_operand (ctx, i);
        }

      switch(mapping)
        {

#define SEMANTIC_FUNCTION_CALL_1(NAME) \
  arc2_gen_##NAME (ctx, ops[0]);
#define SEMANTIC_FUNCTION_CALL_2(NAME) \
  arc2_gen_##NAME (ctx, ops[0], ops[1]);
#define SEMANTIC_FUNCTION_CALL_3(NAME) \
  arc2_gen_##NAME (ctx, ops[0], ops[1], ops[2]);

#define MAPPING(...)
#define SEMANTIC_FUNCTION(NAME, NOPS, ...) \
	    case MAP_##NAME: \
	      ret = SEMANTIC_FUNCTION_CALL_##NOPS(NAME); \
	      break;
#include "arc-semfunc_mapping.h"
#undef SEMANTIC_FUNCTION
#undef MAPPING
        default:
          arc_debug_opcode(opcode, "Could not map opcode");
          should_stop = true;
          break;
        }
    }
  else
    {
      arc_debug_opcode(opcode, "Could not identify opcode");
      should_stop = true;
    }

#ifdef DEBUG_TCG
  #error "HERE"
#endif
  ret = (!opcode || should_stop) ? BS_STOP : ret;
  return ret;
}
/* Local variables:
   eval: (c-set-style "gnu")
   indent-tabs-mode: t
   End:  */
