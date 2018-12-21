/*
 *  QEMU ARC CPU
 *
 *  Copyright (c) 2017 Cupertino Miranda
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

#include "translate.h"
#include "arc-semfunc.h"




/* FLAG
 *    Variables: @src
 *    Functions: getCCFlag, getRegister, getBit, Halt, targetHasOption, setRegister
--- code ---
{
  cc_flag = getCCFlag ();
  if((cc_flag == true))
    {
      status32 = getRegister (R_STATUS32);
      if(((getBit (@src, 0) == 1) && (getBit (status32, 7) == 0)))
        {
          status32 = (status32 | 1);
          Halt ();
        }
      else
        {
          status32 = (status32 | (@src & 3840));
          if((getBit (status32, 7) == 0))
            {
              status32 = (status32 | (@src & 30));
            };
          if(targetHasOption (DIV_REM_OPTION))
            {
              status32 = (status32 | (@src & 8192));
            };
          if(targetHasOption (STACK_CHECKING))
            {
              status32 = (status32 | (@src & 16384));
            };
          if(targetHasOption (LL64_OPTION))
            {
              status32 = (status32 | (@src & 524288));
            };
          status32 = (status32 | (@src & 1048576));
        };
      setRegister (R_STATUS32, status32);
    };
}
 */

int
arc2_gen_FLAG (DisasCtxt *ctx, TCGv src)
{
  int ret = BS_NONE;
  TCGv temp_9 = NULL /* REFERENCE */;
  TCGv cc_flag = tcg_temp_local_new_i32();
  TCGv temp_1 = tcg_temp_local_new_i32();
  TCGv temp_2 = tcg_temp_local_new_i32();
  TCGv temp_10 = NULL /* REFERENCE */;
  TCGv status32 = tcg_temp_local_new_i32();
  TCGv temp_12 = tcg_temp_local_new_i32();
  TCGv temp_11 = NULL /* REFERENCE */;
  TCGv temp_3 = tcg_temp_local_new_i32();
  TCGv temp_14 = tcg_temp_local_new_i32();
  TCGv temp_13 = NULL /* REFERENCE */;
  TCGv temp_4 = tcg_temp_local_new_i32();
  TCGv temp_5 = tcg_temp_local_new_i32();
  TCGv temp_6 = tcg_temp_local_new_i32();
  TCGv temp_15 = tcg_temp_local_new_i32();
  TCGv temp_17 = tcg_temp_local_new_i32();
  TCGv temp_16 = NULL /* REFERENCE */;
  TCGv temp_7 = tcg_temp_local_new_i32();
  TCGv temp_8 = tcg_temp_local_new_i32();
  TCGv temp_18 = tcg_temp_local_new_i32();
  TCGv temp_19 = tcg_temp_local_new_i32();
  TCGv temp_20 = tcg_temp_local_new_i32();
  TCGv temp_21 = tcg_temp_local_new_i32();
  TCGv temp_22 = tcg_temp_local_new_i32();
  temp_9 = getCCFlag();
  tcg_gen_mov_i32(cc_flag, temp_9);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_i32(temp_2, temp_1, 1); tcg_gen_andi_i32(temp_2, temp_2, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, arc_true, done_1);;
  temp_10 = getRegister(R_STATUS32);
  tcg_gen_mov_i32(status32, temp_10);
  TCGLabel *else_2 = gen_new_label();
  TCGLabel *done_2 = gen_new_label();
  tcg_gen_movi_i32(temp_12, 0);
  temp_11 = getBit(src, temp_12);
  tcg_gen_setcondi_i32(TCG_COND_EQ, temp_3, temp_11, 1);
  tcg_gen_movi_i32(temp_14, 7);
  temp_13 = getBit(status32, temp_14);
  tcg_gen_setcondi_i32(TCG_COND_EQ, temp_4, temp_13, 0);
  tcg_gen_and_i32(temp_5, temp_3, temp_4);
  tcg_gen_xori_i32(temp_6, temp_5, 1); tcg_gen_andi_i32(temp_6, temp_6, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_6, arc_true, else_2);;
  tcg_gen_ori_i32(status32, status32, 1);
  Halt();
  tcg_gen_br(done_2);
  gen_set_label(else_2);
  tcg_gen_andi_i32(temp_15, src, 3840);
  tcg_gen_or_i32(status32, status32, temp_15);
  TCGLabel *done_3 = gen_new_label();
  tcg_gen_movi_i32(temp_17, 7);
  temp_16 = getBit(status32, temp_17);
  tcg_gen_setcondi_i32(TCG_COND_EQ, temp_7, temp_16, 0);
  tcg_gen_xori_i32(temp_8, temp_7, 1); tcg_gen_andi_i32(temp_8, temp_8, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_8, arc_true, done_3);;
  tcg_gen_andi_i32(temp_18, src, 30);
  tcg_gen_or_i32(status32, status32, temp_18);
  gen_set_label(done_3);
  if (targetHasOption (DIV_REM_OPTION))
    {
    tcg_gen_andi_i32(temp_19, src, 8192);
  tcg_gen_or_i32(status32, status32, temp_19);
;
    }
  else
    {
  ;
    }
  if (targetHasOption (STACK_CHECKING))
    {
    tcg_gen_andi_i32(temp_20, src, 16384);
  tcg_gen_or_i32(status32, status32, temp_20);
;
    }
  else
    {
  ;
    }
  if (targetHasOption (LL64_OPTION))
    {
    tcg_gen_andi_i32(temp_21, src, 524288);
  tcg_gen_or_i32(status32, status32, temp_21);
;
    }
  else
    {
  ;
    }
  tcg_gen_andi_i32(temp_22, src, 1048576);
  tcg_gen_or_i32(status32, status32, temp_22);
  gen_set_label(done_2);
  setRegister(R_STATUS32, status32);
  gen_set_label(done_1);
  if(temp_9 != NULL) tcg_temp_free(temp_9);
  tcg_temp_free(cc_flag);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  if(temp_10 != NULL) tcg_temp_free(temp_10);
  tcg_temp_free(status32);
  tcg_temp_free(temp_12);
  if(temp_11 != NULL) tcg_temp_free(temp_11);
  tcg_temp_free(temp_3);
  tcg_temp_free(temp_14);
  if(temp_13 != NULL) tcg_temp_free(temp_13);
  tcg_temp_free(temp_4);
  tcg_temp_free(temp_5);
  tcg_temp_free(temp_6);
  tcg_temp_free(temp_15);
  tcg_temp_free(temp_17);
  if(temp_16 != NULL) tcg_temp_free(temp_16);
  tcg_temp_free(temp_7);
  tcg_temp_free(temp_8);
  tcg_temp_free(temp_18);
  tcg_temp_free(temp_19);
  tcg_temp_free(temp_20);
  tcg_temp_free(temp_21);
  tcg_temp_free(temp_22);

  return ret;
}





/* ADD
 *    Variables: @b, @c, @a
 *    Functions: getCCFlag, getFFlag, setZFlag, setNFlag, setCFlag, CarryADD, setVFlag, OverflowADD
--- code ---
{
  cc_flag = getCCFlag ();
  lb = @b;
  lc = @c;
  if((cc_flag == true))
    {
      lb = @b;
      lc = @c;
      @a = (@b + @c);
      if((getFFlag () == true))
        {
          setZFlag (@a);
          setNFlag (@a);
          setCFlag (CarryADD (@a, lb, lc));
          setVFlag (OverflowADD (@a, lb, lc));
        };
    };
}
 */

int
arc2_gen_ADD (DisasCtxt *ctx, TCGv b, TCGv c, TCGv a)
{
  int ret = BS_NONE;
  TCGv temp_5 = NULL /* REFERENCE */;
  TCGv cc_flag = tcg_temp_local_new_i32();
  TCGv lb = tcg_temp_local_new_i32();
  TCGv lc = tcg_temp_local_new_i32();
  TCGv temp_1 = tcg_temp_local_new_i32();
  TCGv temp_2 = tcg_temp_local_new_i32();
  TCGv temp_6 = NULL /* REFERENCE */;
  TCGv temp_3 = tcg_temp_local_new_i32();
  TCGv temp_4 = tcg_temp_local_new_i32();
  TCGv temp_8 = NULL /* REFERENCE */;
  TCGv temp_7 = tcg_temp_local_new_i32();
  TCGv temp_10 = NULL /* REFERENCE */;
  TCGv temp_9 = tcg_temp_local_new_i32();
  temp_5 = getCCFlag();
  tcg_gen_mov_i32(cc_flag, temp_5);
  tcg_gen_mov_i32(lb, b);
  tcg_gen_mov_i32(lc, c);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_i32(temp_2, temp_1, 1); tcg_gen_andi_i32(temp_2, temp_2, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, arc_true, done_1);;
  tcg_gen_mov_i32(lb, b);
  tcg_gen_mov_i32(lc, c);
  tcg_gen_add_i32(a, b, c);
  TCGLabel *done_2 = gen_new_label();
  temp_6 = getFFlag();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_3, temp_6, arc_true);
  tcg_gen_xori_i32(temp_4, temp_3, 1); tcg_gen_andi_i32(temp_4, temp_4, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_4, arc_true, done_2);;
  setZFlag(a);
  setNFlag(a);
  temp_8 = CarryADD(a, lb, lc);
  tcg_gen_mov_i32(temp_7, temp_8);
  setCFlag(temp_7);
  temp_10 = OverflowADD(a, lb, lc);
  tcg_gen_mov_i32(temp_9, temp_10);
  setVFlag(temp_9);
  gen_set_label(done_2);
  gen_set_label(done_1);
  if(temp_5 != NULL) tcg_temp_free(temp_5);
  tcg_temp_free(cc_flag);
  tcg_temp_free(lb);
  tcg_temp_free(lc);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  if(temp_6 != NULL) tcg_temp_free(temp_6);
  tcg_temp_free(temp_3);
  tcg_temp_free(temp_4);
  if(temp_8 != NULL) tcg_temp_free(temp_8);
  tcg_temp_free(temp_7);
  if(temp_10 != NULL) tcg_temp_free(temp_10);
  tcg_temp_free(temp_9);

  return ret;
}





/* ADD1
 *    Variables: @b, @c, @a
 *    Functions: getCCFlag, getFFlag, setZFlag, setNFlag, setCFlag, CarryADD, setVFlag, OverflowADD
--- code ---
{
  cc_flag = getCCFlag ();
  lb = @b;
  lc = @c;
  if((cc_flag == true))
    {
      lb = @b;
      lc = @c;
      @a = (@b + (@c << 1));
      if((getFFlag () == true))
        {
          setZFlag (@a);
          setNFlag (@a);
          setCFlag (CarryADD (@a, lb, lc));
          setVFlag (OverflowADD (@a, lb, lc));
        };
    };
}
 */

int
arc2_gen_ADD1 (DisasCtxt *ctx, TCGv b, TCGv c, TCGv a)
{
  int ret = BS_NONE;
  TCGv temp_5 = NULL /* REFERENCE */;
  TCGv cc_flag = tcg_temp_local_new_i32();
  TCGv lb = tcg_temp_local_new_i32();
  TCGv lc = tcg_temp_local_new_i32();
  TCGv temp_1 = tcg_temp_local_new_i32();
  TCGv temp_2 = tcg_temp_local_new_i32();
  TCGv temp_6 = tcg_temp_local_new_i32();
  TCGv temp_7 = NULL /* REFERENCE */;
  TCGv temp_3 = tcg_temp_local_new_i32();
  TCGv temp_4 = tcg_temp_local_new_i32();
  TCGv temp_9 = NULL /* REFERENCE */;
  TCGv temp_8 = tcg_temp_local_new_i32();
  TCGv temp_11 = NULL /* REFERENCE */;
  TCGv temp_10 = tcg_temp_local_new_i32();
  temp_5 = getCCFlag();
  tcg_gen_mov_i32(cc_flag, temp_5);
  tcg_gen_mov_i32(lb, b);
  tcg_gen_mov_i32(lc, c);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_i32(temp_2, temp_1, 1); tcg_gen_andi_i32(temp_2, temp_2, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, arc_true, done_1);;
  tcg_gen_mov_i32(lb, b);
  tcg_gen_mov_i32(lc, c);
  tcg_gen_shli_i32(temp_6, c, 1);
  tcg_gen_add_i32(a, b, temp_6);
  TCGLabel *done_2 = gen_new_label();
  temp_7 = getFFlag();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_3, temp_7, arc_true);
  tcg_gen_xori_i32(temp_4, temp_3, 1); tcg_gen_andi_i32(temp_4, temp_4, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_4, arc_true, done_2);;
  setZFlag(a);
  setNFlag(a);
  temp_9 = CarryADD(a, lb, lc);
  tcg_gen_mov_i32(temp_8, temp_9);
  setCFlag(temp_8);
  temp_11 = OverflowADD(a, lb, lc);
  tcg_gen_mov_i32(temp_10, temp_11);
  setVFlag(temp_10);
  gen_set_label(done_2);
  gen_set_label(done_1);
  if(temp_5 != NULL) tcg_temp_free(temp_5);
  tcg_temp_free(cc_flag);
  tcg_temp_free(lb);
  tcg_temp_free(lc);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  tcg_temp_free(temp_6);
  if(temp_7 != NULL) tcg_temp_free(temp_7);
  tcg_temp_free(temp_3);
  tcg_temp_free(temp_4);
  if(temp_9 != NULL) tcg_temp_free(temp_9);
  tcg_temp_free(temp_8);
  if(temp_11 != NULL) tcg_temp_free(temp_11);
  tcg_temp_free(temp_10);

  return ret;
}





/* ADD2
 *    Variables: @b, @c, @a
 *    Functions: getCCFlag, getFFlag, setZFlag, setNFlag, setCFlag, CarryADD, setVFlag, OverflowADD
--- code ---
{
  cc_flag = getCCFlag ();
  lb = @b;
  lc = @c;
  if((cc_flag == true))
    {
      lb = @b;
      lc = @c;
      @a = (@b + (@c << 2));
      if((getFFlag () == true))
        {
          setZFlag (@a);
          setNFlag (@a);
          setCFlag (CarryADD (@a, lb, lc));
          setVFlag (OverflowADD (@a, lb, lc));
        };
    };
}
 */

int
arc2_gen_ADD2 (DisasCtxt *ctx, TCGv b, TCGv c, TCGv a)
{
  int ret = BS_NONE;
  TCGv temp_5 = NULL /* REFERENCE */;
  TCGv cc_flag = tcg_temp_local_new_i32();
  TCGv lb = tcg_temp_local_new_i32();
  TCGv lc = tcg_temp_local_new_i32();
  TCGv temp_1 = tcg_temp_local_new_i32();
  TCGv temp_2 = tcg_temp_local_new_i32();
  TCGv temp_6 = tcg_temp_local_new_i32();
  TCGv temp_7 = NULL /* REFERENCE */;
  TCGv temp_3 = tcg_temp_local_new_i32();
  TCGv temp_4 = tcg_temp_local_new_i32();
  TCGv temp_9 = NULL /* REFERENCE */;
  TCGv temp_8 = tcg_temp_local_new_i32();
  TCGv temp_11 = NULL /* REFERENCE */;
  TCGv temp_10 = tcg_temp_local_new_i32();
  temp_5 = getCCFlag();
  tcg_gen_mov_i32(cc_flag, temp_5);
  tcg_gen_mov_i32(lb, b);
  tcg_gen_mov_i32(lc, c);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_i32(temp_2, temp_1, 1); tcg_gen_andi_i32(temp_2, temp_2, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, arc_true, done_1);;
  tcg_gen_mov_i32(lb, b);
  tcg_gen_mov_i32(lc, c);
  tcg_gen_shli_i32(temp_6, c, 2);
  tcg_gen_add_i32(a, b, temp_6);
  TCGLabel *done_2 = gen_new_label();
  temp_7 = getFFlag();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_3, temp_7, arc_true);
  tcg_gen_xori_i32(temp_4, temp_3, 1); tcg_gen_andi_i32(temp_4, temp_4, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_4, arc_true, done_2);;
  setZFlag(a);
  setNFlag(a);
  temp_9 = CarryADD(a, lb, lc);
  tcg_gen_mov_i32(temp_8, temp_9);
  setCFlag(temp_8);
  temp_11 = OverflowADD(a, lb, lc);
  tcg_gen_mov_i32(temp_10, temp_11);
  setVFlag(temp_10);
  gen_set_label(done_2);
  gen_set_label(done_1);
  if(temp_5 != NULL) tcg_temp_free(temp_5);
  tcg_temp_free(cc_flag);
  tcg_temp_free(lb);
  tcg_temp_free(lc);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  tcg_temp_free(temp_6);
  if(temp_7 != NULL) tcg_temp_free(temp_7);
  tcg_temp_free(temp_3);
  tcg_temp_free(temp_4);
  if(temp_9 != NULL) tcg_temp_free(temp_9);
  tcg_temp_free(temp_8);
  if(temp_11 != NULL) tcg_temp_free(temp_11);
  tcg_temp_free(temp_10);

  return ret;
}





/* ADD3
 *    Variables: @b, @c, @a
 *    Functions: getCCFlag, getFFlag, setZFlag, setNFlag, setCFlag, CarryADD, setVFlag, OverflowADD
--- code ---
{
  cc_flag = getCCFlag ();
  lb = @b;
  lc = @c;
  if((cc_flag == true))
    {
      lb = @b;
      lc = @c;
      @a = (@b + (@c << 3));
      if((getFFlag () == true))
        {
          setZFlag (@a);
          setNFlag (@a);
          setCFlag (CarryADD (@a, lb, lc));
          setVFlag (OverflowADD (@a, lb, lc));
        };
    };
}
 */

int
arc2_gen_ADD3 (DisasCtxt *ctx, TCGv b, TCGv c, TCGv a)
{
  int ret = BS_NONE;
  TCGv temp_5 = NULL /* REFERENCE */;
  TCGv cc_flag = tcg_temp_local_new_i32();
  TCGv lb = tcg_temp_local_new_i32();
  TCGv lc = tcg_temp_local_new_i32();
  TCGv temp_1 = tcg_temp_local_new_i32();
  TCGv temp_2 = tcg_temp_local_new_i32();
  TCGv temp_6 = tcg_temp_local_new_i32();
  TCGv temp_7 = NULL /* REFERENCE */;
  TCGv temp_3 = tcg_temp_local_new_i32();
  TCGv temp_4 = tcg_temp_local_new_i32();
  TCGv temp_9 = NULL /* REFERENCE */;
  TCGv temp_8 = tcg_temp_local_new_i32();
  TCGv temp_11 = NULL /* REFERENCE */;
  TCGv temp_10 = tcg_temp_local_new_i32();
  temp_5 = getCCFlag();
  tcg_gen_mov_i32(cc_flag, temp_5);
  tcg_gen_mov_i32(lb, b);
  tcg_gen_mov_i32(lc, c);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_i32(temp_2, temp_1, 1); tcg_gen_andi_i32(temp_2, temp_2, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, arc_true, done_1);;
  tcg_gen_mov_i32(lb, b);
  tcg_gen_mov_i32(lc, c);
  tcg_gen_shli_i32(temp_6, c, 3);
  tcg_gen_add_i32(a, b, temp_6);
  TCGLabel *done_2 = gen_new_label();
  temp_7 = getFFlag();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_3, temp_7, arc_true);
  tcg_gen_xori_i32(temp_4, temp_3, 1); tcg_gen_andi_i32(temp_4, temp_4, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_4, arc_true, done_2);;
  setZFlag(a);
  setNFlag(a);
  temp_9 = CarryADD(a, lb, lc);
  tcg_gen_mov_i32(temp_8, temp_9);
  setCFlag(temp_8);
  temp_11 = OverflowADD(a, lb, lc);
  tcg_gen_mov_i32(temp_10, temp_11);
  setVFlag(temp_10);
  gen_set_label(done_2);
  gen_set_label(done_1);
  if(temp_5 != NULL) tcg_temp_free(temp_5);
  tcg_temp_free(cc_flag);
  tcg_temp_free(lb);
  tcg_temp_free(lc);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  tcg_temp_free(temp_6);
  if(temp_7 != NULL) tcg_temp_free(temp_7);
  tcg_temp_free(temp_3);
  tcg_temp_free(temp_4);
  if(temp_9 != NULL) tcg_temp_free(temp_9);
  tcg_temp_free(temp_8);
  if(temp_11 != NULL) tcg_temp_free(temp_11);
  tcg_temp_free(temp_10);

  return ret;
}





/* ADC
 *    Variables: @b, @c, @a
 *    Functions: getCCFlag, getCFlag, getFFlag, setZFlag, setNFlag, setCFlag, CarryADD, setVFlag, OverflowADD
--- code ---
{
  cc_flag = getCCFlag ();
  lb = @b;
  lc = @c;
  if((cc_flag == true))
    {
      lb = @b;
      lc = @c;
      @a = ((@b + @c) + getCFlag ());
      if((getFFlag () == true))
        {
          setZFlag (@a);
          setNFlag (@a);
          setCFlag (CarryADD (@a, lb, lc));
          setVFlag (OverflowADD (@a, lb, lc));
        };
    };
}
 */

int
arc2_gen_ADC (DisasCtxt *ctx, TCGv b, TCGv c, TCGv a)
{
  int ret = BS_NONE;
  TCGv temp_5 = NULL /* REFERENCE */;
  TCGv cc_flag = tcg_temp_local_new_i32();
  TCGv lb = tcg_temp_local_new_i32();
  TCGv lc = tcg_temp_local_new_i32();
  TCGv temp_1 = tcg_temp_local_new_i32();
  TCGv temp_2 = tcg_temp_local_new_i32();
  TCGv temp_6 = tcg_temp_local_new_i32();
  TCGv temp_8 = NULL /* REFERENCE */;
  TCGv temp_7 = tcg_temp_local_new_i32();
  TCGv temp_9 = NULL /* REFERENCE */;
  TCGv temp_3 = tcg_temp_local_new_i32();
  TCGv temp_4 = tcg_temp_local_new_i32();
  TCGv temp_11 = NULL /* REFERENCE */;
  TCGv temp_10 = tcg_temp_local_new_i32();
  TCGv temp_13 = NULL /* REFERENCE */;
  TCGv temp_12 = tcg_temp_local_new_i32();
  temp_5 = getCCFlag();
  tcg_gen_mov_i32(cc_flag, temp_5);
  tcg_gen_mov_i32(lb, b);
  tcg_gen_mov_i32(lc, c);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_i32(temp_2, temp_1, 1); tcg_gen_andi_i32(temp_2, temp_2, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, arc_true, done_1);;
  tcg_gen_mov_i32(lb, b);
  tcg_gen_mov_i32(lc, c);
  tcg_gen_add_i32(temp_6, b, c);
  temp_8 = getCFlag();
  tcg_gen_mov_i32(temp_7, temp_8);
  tcg_gen_add_i32(a, temp_6, temp_7);
  TCGLabel *done_2 = gen_new_label();
  temp_9 = getFFlag();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_3, temp_9, arc_true);
  tcg_gen_xori_i32(temp_4, temp_3, 1); tcg_gen_andi_i32(temp_4, temp_4, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_4, arc_true, done_2);;
  setZFlag(a);
  setNFlag(a);
  temp_11 = CarryADD(a, lb, lc);
  tcg_gen_mov_i32(temp_10, temp_11);
  setCFlag(temp_10);
  temp_13 = OverflowADD(a, lb, lc);
  tcg_gen_mov_i32(temp_12, temp_13);
  setVFlag(temp_12);
  gen_set_label(done_2);
  gen_set_label(done_1);
  if(temp_5 != NULL) tcg_temp_free(temp_5);
  tcg_temp_free(cc_flag);
  tcg_temp_free(lb);
  tcg_temp_free(lc);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  tcg_temp_free(temp_6);
  if(temp_8 != NULL) tcg_temp_free(temp_8);
  tcg_temp_free(temp_7);
  if(temp_9 != NULL) tcg_temp_free(temp_9);
  tcg_temp_free(temp_3);
  tcg_temp_free(temp_4);
  if(temp_11 != NULL) tcg_temp_free(temp_11);
  tcg_temp_free(temp_10);
  if(temp_13 != NULL) tcg_temp_free(temp_13);
  tcg_temp_free(temp_12);

  return ret;
}





/* SBC
 *    Variables: @b, @c, @a
 *    Functions: getCCFlag, getCFlag, getFFlag, setZFlag, setNFlag, setCFlag, CarryADD, setVFlag, OverflowADD
--- code ---
{
  cc_flag = getCCFlag ();
  lb = @b;
  lc = @c;
  if((cc_flag == true))
    {
      lb = @b;
      lc = @c;
      @a = ((@b - @c) - getCFlag ());
      if((getFFlag () == true))
        {
          setZFlag (@a);
          setNFlag (@a);
          setCFlag (CarryADD (@a, lb, lc));
          setVFlag (OverflowADD (@a, lb, lc));
        };
    };
}
 */

int
arc2_gen_SBC (DisasCtxt *ctx, TCGv b, TCGv c, TCGv a)
{
  int ret = BS_NONE;
  TCGv temp_5 = NULL /* REFERENCE */;
  TCGv cc_flag = tcg_temp_local_new_i32();
  TCGv lb = tcg_temp_local_new_i32();
  TCGv lc = tcg_temp_local_new_i32();
  TCGv temp_1 = tcg_temp_local_new_i32();
  TCGv temp_2 = tcg_temp_local_new_i32();
  TCGv temp_6 = tcg_temp_local_new_i32();
  TCGv temp_8 = NULL /* REFERENCE */;
  TCGv temp_7 = tcg_temp_local_new_i32();
  TCGv temp_9 = NULL /* REFERENCE */;
  TCGv temp_3 = tcg_temp_local_new_i32();
  TCGv temp_4 = tcg_temp_local_new_i32();
  TCGv temp_11 = NULL /* REFERENCE */;
  TCGv temp_10 = tcg_temp_local_new_i32();
  TCGv temp_13 = NULL /* REFERENCE */;
  TCGv temp_12 = tcg_temp_local_new_i32();
  temp_5 = getCCFlag();
  tcg_gen_mov_i32(cc_flag, temp_5);
  tcg_gen_mov_i32(lb, b);
  tcg_gen_mov_i32(lc, c);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_i32(temp_2, temp_1, 1); tcg_gen_andi_i32(temp_2, temp_2, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, arc_true, done_1);;
  tcg_gen_mov_i32(lb, b);
  tcg_gen_mov_i32(lc, c);
  tcg_gen_sub_i32(temp_6, b, c);
  temp_8 = getCFlag();
  tcg_gen_mov_i32(temp_7, temp_8);
  tcg_gen_sub_i32(a, temp_6, temp_7);
  TCGLabel *done_2 = gen_new_label();
  temp_9 = getFFlag();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_3, temp_9, arc_true);
  tcg_gen_xori_i32(temp_4, temp_3, 1); tcg_gen_andi_i32(temp_4, temp_4, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_4, arc_true, done_2);;
  setZFlag(a);
  setNFlag(a);
  temp_11 = CarryADD(a, lb, lc);
  tcg_gen_mov_i32(temp_10, temp_11);
  setCFlag(temp_10);
  temp_13 = OverflowADD(a, lb, lc);
  tcg_gen_mov_i32(temp_12, temp_13);
  setVFlag(temp_12);
  gen_set_label(done_2);
  gen_set_label(done_1);
  if(temp_5 != NULL) tcg_temp_free(temp_5);
  tcg_temp_free(cc_flag);
  tcg_temp_free(lb);
  tcg_temp_free(lc);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  tcg_temp_free(temp_6);
  if(temp_8 != NULL) tcg_temp_free(temp_8);
  tcg_temp_free(temp_7);
  if(temp_9 != NULL) tcg_temp_free(temp_9);
  tcg_temp_free(temp_3);
  tcg_temp_free(temp_4);
  if(temp_11 != NULL) tcg_temp_free(temp_11);
  tcg_temp_free(temp_10);
  if(temp_13 != NULL) tcg_temp_free(temp_13);
  tcg_temp_free(temp_12);

  return ret;
}





/* NEG
 *    Variables: @b, @a
 *    Functions: getCCFlag, getFFlag, setZFlag, setNFlag, setCFlag, CarrySUB, setVFlag, OverflowSUB
--- code ---
{
  cc_flag = getCCFlag ();
  lb = @b;
  if((cc_flag == true))
    {
      lb = @b;
      @a = (0 - @b);
      if((getFFlag () == true))
        {
          setZFlag (@a);
          setNFlag (@a);
          setCFlag (CarrySUB (@a, 0, lb));
          setVFlag (OverflowSUB (@a, 0, lb));
        };
    };
}
 */

int
arc2_gen_NEG (DisasCtxt *ctx, TCGv b, TCGv a)
{
  int ret = BS_NONE;
  TCGv temp_5 = NULL /* REFERENCE */;
  TCGv cc_flag = tcg_temp_local_new_i32();
  TCGv lb = tcg_temp_local_new_i32();
  TCGv temp_1 = tcg_temp_local_new_i32();
  TCGv temp_2 = tcg_temp_local_new_i32();
  TCGv temp_6 = NULL /* REFERENCE */;
  TCGv temp_3 = tcg_temp_local_new_i32();
  TCGv temp_4 = tcg_temp_local_new_i32();
  TCGv temp_9 = tcg_temp_local_new_i32();
  TCGv temp_8 = NULL /* REFERENCE */;
  TCGv temp_7 = tcg_temp_local_new_i32();
  TCGv temp_12 = tcg_temp_local_new_i32();
  TCGv temp_11 = NULL /* REFERENCE */;
  TCGv temp_10 = tcg_temp_local_new_i32();
  temp_5 = getCCFlag();
  tcg_gen_mov_i32(cc_flag, temp_5);
  tcg_gen_mov_i32(lb, b);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_i32(temp_2, temp_1, 1); tcg_gen_andi_i32(temp_2, temp_2, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, arc_true, done_1);;
  tcg_gen_mov_i32(lb, b);
  tcg_gen_subfi_i32(a, 0, b);
  TCGLabel *done_2 = gen_new_label();
  temp_6 = getFFlag();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_3, temp_6, arc_true);
  tcg_gen_xori_i32(temp_4, temp_3, 1); tcg_gen_andi_i32(temp_4, temp_4, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_4, arc_true, done_2);;
  setZFlag(a);
  setNFlag(a);
  tcg_gen_movi_i32(temp_9, 0);
  temp_8 = CarrySUB(a, temp_9, lb);
  tcg_gen_mov_i32(temp_7, temp_8);
  setCFlag(temp_7);
  tcg_gen_movi_i32(temp_12, 0);
  temp_11 = OverflowSUB(a, temp_12, lb);
  tcg_gen_mov_i32(temp_10, temp_11);
  setVFlag(temp_10);
  gen_set_label(done_2);
  gen_set_label(done_1);
  if(temp_5 != NULL) tcg_temp_free(temp_5);
  tcg_temp_free(cc_flag);
  tcg_temp_free(lb);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  if(temp_6 != NULL) tcg_temp_free(temp_6);
  tcg_temp_free(temp_3);
  tcg_temp_free(temp_4);
  tcg_temp_free(temp_9);
  if(temp_8 != NULL) tcg_temp_free(temp_8);
  tcg_temp_free(temp_7);
  tcg_temp_free(temp_12);
  if(temp_11 != NULL) tcg_temp_free(temp_11);
  tcg_temp_free(temp_10);

  return ret;
}





/* SUB
 *    Variables: @b, @c, @a
 *    Functions: getCCFlag, getFFlag, setZFlag, setNFlag, setCFlag, CarrySUB, setVFlag, OverflowSUB
--- code ---
{
  cc_flag = getCCFlag ();
  lb = @b;
  lc = @c;
  if((cc_flag == true))
    {
      lb = @b;
      lc = @c;
      @a = (@b - @c);
      if((getFFlag () == true))
        {
          setZFlag (@a);
          setNFlag (@a);
          setCFlag (CarrySUB (@a, lb, lc));
          setVFlag (OverflowSUB (@a, lb, lc));
        };
    };
}
 */

int
arc2_gen_SUB (DisasCtxt *ctx, TCGv b, TCGv c, TCGv a)
{
  int ret = BS_NONE;
  TCGv temp_5 = NULL /* REFERENCE */;
  TCGv cc_flag = tcg_temp_local_new_i32();
  TCGv lb = tcg_temp_local_new_i32();
  TCGv lc = tcg_temp_local_new_i32();
  TCGv temp_1 = tcg_temp_local_new_i32();
  TCGv temp_2 = tcg_temp_local_new_i32();
  TCGv temp_6 = NULL /* REFERENCE */;
  TCGv temp_3 = tcg_temp_local_new_i32();
  TCGv temp_4 = tcg_temp_local_new_i32();
  TCGv temp_8 = NULL /* REFERENCE */;
  TCGv temp_7 = tcg_temp_local_new_i32();
  TCGv temp_10 = NULL /* REFERENCE */;
  TCGv temp_9 = tcg_temp_local_new_i32();
  temp_5 = getCCFlag();
  tcg_gen_mov_i32(cc_flag, temp_5);
  tcg_gen_mov_i32(lb, b);
  tcg_gen_mov_i32(lc, c);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_i32(temp_2, temp_1, 1); tcg_gen_andi_i32(temp_2, temp_2, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, arc_true, done_1);;
  tcg_gen_mov_i32(lb, b);
  tcg_gen_mov_i32(lc, c);
  tcg_gen_sub_i32(a, b, c);
  TCGLabel *done_2 = gen_new_label();
  temp_6 = getFFlag();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_3, temp_6, arc_true);
  tcg_gen_xori_i32(temp_4, temp_3, 1); tcg_gen_andi_i32(temp_4, temp_4, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_4, arc_true, done_2);;
  setZFlag(a);
  setNFlag(a);
  temp_8 = CarrySUB(a, lb, lc);
  tcg_gen_mov_i32(temp_7, temp_8);
  setCFlag(temp_7);
  temp_10 = OverflowSUB(a, lb, lc);
  tcg_gen_mov_i32(temp_9, temp_10);
  setVFlag(temp_9);
  gen_set_label(done_2);
  gen_set_label(done_1);
  if(temp_5 != NULL) tcg_temp_free(temp_5);
  tcg_temp_free(cc_flag);
  tcg_temp_free(lb);
  tcg_temp_free(lc);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  if(temp_6 != NULL) tcg_temp_free(temp_6);
  tcg_temp_free(temp_3);
  tcg_temp_free(temp_4);
  if(temp_8 != NULL) tcg_temp_free(temp_8);
  tcg_temp_free(temp_7);
  if(temp_10 != NULL) tcg_temp_free(temp_10);
  tcg_temp_free(temp_9);

  return ret;
}





/* SUB1
 *    Variables: @b, @c, @a
 *    Functions: getCCFlag, getFFlag, setZFlag, setNFlag, setCFlag, CarrySUB, setVFlag, OverflowSUB
--- code ---
{
  cc_flag = getCCFlag ();
  lb = @b;
  lc = @c;
  if((cc_flag == true))
    {
      lb = @b;
      lc = @c;
      @a = (@b - (@c << 1));
      if((getFFlag () == true))
        {
          setZFlag (@a);
          setNFlag (@a);
          setCFlag (CarrySUB (@a, lb, lc));
          setVFlag (OverflowSUB (@a, lb, lc));
        };
    };
}
 */

int
arc2_gen_SUB1 (DisasCtxt *ctx, TCGv b, TCGv c, TCGv a)
{
  int ret = BS_NONE;
  TCGv temp_5 = NULL /* REFERENCE */;
  TCGv cc_flag = tcg_temp_local_new_i32();
  TCGv lb = tcg_temp_local_new_i32();
  TCGv lc = tcg_temp_local_new_i32();
  TCGv temp_1 = tcg_temp_local_new_i32();
  TCGv temp_2 = tcg_temp_local_new_i32();
  TCGv temp_6 = tcg_temp_local_new_i32();
  TCGv temp_7 = NULL /* REFERENCE */;
  TCGv temp_3 = tcg_temp_local_new_i32();
  TCGv temp_4 = tcg_temp_local_new_i32();
  TCGv temp_9 = NULL /* REFERENCE */;
  TCGv temp_8 = tcg_temp_local_new_i32();
  TCGv temp_11 = NULL /* REFERENCE */;
  TCGv temp_10 = tcg_temp_local_new_i32();
  temp_5 = getCCFlag();
  tcg_gen_mov_i32(cc_flag, temp_5);
  tcg_gen_mov_i32(lb, b);
  tcg_gen_mov_i32(lc, c);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_i32(temp_2, temp_1, 1); tcg_gen_andi_i32(temp_2, temp_2, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, arc_true, done_1);;
  tcg_gen_mov_i32(lb, b);
  tcg_gen_mov_i32(lc, c);
  tcg_gen_shli_i32(temp_6, c, 1);
  tcg_gen_sub_i32(a, b, temp_6);
  TCGLabel *done_2 = gen_new_label();
  temp_7 = getFFlag();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_3, temp_7, arc_true);
  tcg_gen_xori_i32(temp_4, temp_3, 1); tcg_gen_andi_i32(temp_4, temp_4, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_4, arc_true, done_2);;
  setZFlag(a);
  setNFlag(a);
  temp_9 = CarrySUB(a, lb, lc);
  tcg_gen_mov_i32(temp_8, temp_9);
  setCFlag(temp_8);
  temp_11 = OverflowSUB(a, lb, lc);
  tcg_gen_mov_i32(temp_10, temp_11);
  setVFlag(temp_10);
  gen_set_label(done_2);
  gen_set_label(done_1);
  if(temp_5 != NULL) tcg_temp_free(temp_5);
  tcg_temp_free(cc_flag);
  tcg_temp_free(lb);
  tcg_temp_free(lc);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  tcg_temp_free(temp_6);
  if(temp_7 != NULL) tcg_temp_free(temp_7);
  tcg_temp_free(temp_3);
  tcg_temp_free(temp_4);
  if(temp_9 != NULL) tcg_temp_free(temp_9);
  tcg_temp_free(temp_8);
  if(temp_11 != NULL) tcg_temp_free(temp_11);
  tcg_temp_free(temp_10);

  return ret;
}





/* SUB2
 *    Variables: @b, @c, @a
 *    Functions: getCCFlag, getFFlag, setZFlag, setNFlag, setCFlag, CarrySUB, setVFlag, OverflowSUB
--- code ---
{
  cc_flag = getCCFlag ();
  lb = @b;
  lc = @c;
  if((cc_flag == true))
    {
      lb = @b;
      lc = @c;
      @a = (@b - (@c << 2));
      if((getFFlag () == true))
        {
          setZFlag (@a);
          setNFlag (@a);
          setCFlag (CarrySUB (@a, lb, lc));
          setVFlag (OverflowSUB (@a, lb, lc));
        };
    };
}
 */

int
arc2_gen_SUB2 (DisasCtxt *ctx, TCGv b, TCGv c, TCGv a)
{
  int ret = BS_NONE;
  TCGv temp_5 = NULL /* REFERENCE */;
  TCGv cc_flag = tcg_temp_local_new_i32();
  TCGv lb = tcg_temp_local_new_i32();
  TCGv lc = tcg_temp_local_new_i32();
  TCGv temp_1 = tcg_temp_local_new_i32();
  TCGv temp_2 = tcg_temp_local_new_i32();
  TCGv temp_6 = tcg_temp_local_new_i32();
  TCGv temp_7 = NULL /* REFERENCE */;
  TCGv temp_3 = tcg_temp_local_new_i32();
  TCGv temp_4 = tcg_temp_local_new_i32();
  TCGv temp_9 = NULL /* REFERENCE */;
  TCGv temp_8 = tcg_temp_local_new_i32();
  TCGv temp_11 = NULL /* REFERENCE */;
  TCGv temp_10 = tcg_temp_local_new_i32();
  temp_5 = getCCFlag();
  tcg_gen_mov_i32(cc_flag, temp_5);
  tcg_gen_mov_i32(lb, b);
  tcg_gen_mov_i32(lc, c);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_i32(temp_2, temp_1, 1); tcg_gen_andi_i32(temp_2, temp_2, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, arc_true, done_1);;
  tcg_gen_mov_i32(lb, b);
  tcg_gen_mov_i32(lc, c);
  tcg_gen_shli_i32(temp_6, c, 2);
  tcg_gen_sub_i32(a, b, temp_6);
  TCGLabel *done_2 = gen_new_label();
  temp_7 = getFFlag();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_3, temp_7, arc_true);
  tcg_gen_xori_i32(temp_4, temp_3, 1); tcg_gen_andi_i32(temp_4, temp_4, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_4, arc_true, done_2);;
  setZFlag(a);
  setNFlag(a);
  temp_9 = CarrySUB(a, lb, lc);
  tcg_gen_mov_i32(temp_8, temp_9);
  setCFlag(temp_8);
  temp_11 = OverflowSUB(a, lb, lc);
  tcg_gen_mov_i32(temp_10, temp_11);
  setVFlag(temp_10);
  gen_set_label(done_2);
  gen_set_label(done_1);
  if(temp_5 != NULL) tcg_temp_free(temp_5);
  tcg_temp_free(cc_flag);
  tcg_temp_free(lb);
  tcg_temp_free(lc);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  tcg_temp_free(temp_6);
  if(temp_7 != NULL) tcg_temp_free(temp_7);
  tcg_temp_free(temp_3);
  tcg_temp_free(temp_4);
  if(temp_9 != NULL) tcg_temp_free(temp_9);
  tcg_temp_free(temp_8);
  if(temp_11 != NULL) tcg_temp_free(temp_11);
  tcg_temp_free(temp_10);

  return ret;
}





/* SUB3
 *    Variables: @b, @c, @a
 *    Functions: getCCFlag, getFFlag, setZFlag, setNFlag, setCFlag, CarrySUB, setVFlag, OverflowSUB
--- code ---
{
  cc_flag = getCCFlag ();
  lb = @b;
  lc = @c;
  if((cc_flag == true))
    {
      lb = @b;
      lc = @c;
      @a = (@b - (@c << 3));
      if((getFFlag () == true))
        {
          setZFlag (@a);
          setNFlag (@a);
          setCFlag (CarrySUB (@a, lb, lc));
          setVFlag (OverflowSUB (@a, lb, lc));
        };
    };
}
 */

int
arc2_gen_SUB3 (DisasCtxt *ctx, TCGv b, TCGv c, TCGv a)
{
  int ret = BS_NONE;
  TCGv temp_5 = NULL /* REFERENCE */;
  TCGv cc_flag = tcg_temp_local_new_i32();
  TCGv lb = tcg_temp_local_new_i32();
  TCGv lc = tcg_temp_local_new_i32();
  TCGv temp_1 = tcg_temp_local_new_i32();
  TCGv temp_2 = tcg_temp_local_new_i32();
  TCGv temp_6 = tcg_temp_local_new_i32();
  TCGv temp_7 = NULL /* REFERENCE */;
  TCGv temp_3 = tcg_temp_local_new_i32();
  TCGv temp_4 = tcg_temp_local_new_i32();
  TCGv temp_9 = NULL /* REFERENCE */;
  TCGv temp_8 = tcg_temp_local_new_i32();
  TCGv temp_11 = NULL /* REFERENCE */;
  TCGv temp_10 = tcg_temp_local_new_i32();
  temp_5 = getCCFlag();
  tcg_gen_mov_i32(cc_flag, temp_5);
  tcg_gen_mov_i32(lb, b);
  tcg_gen_mov_i32(lc, c);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_i32(temp_2, temp_1, 1); tcg_gen_andi_i32(temp_2, temp_2, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, arc_true, done_1);;
  tcg_gen_mov_i32(lb, b);
  tcg_gen_mov_i32(lc, c);
  tcg_gen_shli_i32(temp_6, c, 3);
  tcg_gen_sub_i32(a, b, temp_6);
  TCGLabel *done_2 = gen_new_label();
  temp_7 = getFFlag();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_3, temp_7, arc_true);
  tcg_gen_xori_i32(temp_4, temp_3, 1); tcg_gen_andi_i32(temp_4, temp_4, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_4, arc_true, done_2);;
  setZFlag(a);
  setNFlag(a);
  temp_9 = CarrySUB(a, lb, lc);
  tcg_gen_mov_i32(temp_8, temp_9);
  setCFlag(temp_8);
  temp_11 = OverflowSUB(a, lb, lc);
  tcg_gen_mov_i32(temp_10, temp_11);
  setVFlag(temp_10);
  gen_set_label(done_2);
  gen_set_label(done_1);
  if(temp_5 != NULL) tcg_temp_free(temp_5);
  tcg_temp_free(cc_flag);
  tcg_temp_free(lb);
  tcg_temp_free(lc);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  tcg_temp_free(temp_6);
  if(temp_7 != NULL) tcg_temp_free(temp_7);
  tcg_temp_free(temp_3);
  tcg_temp_free(temp_4);
  if(temp_9 != NULL) tcg_temp_free(temp_9);
  tcg_temp_free(temp_8);
  if(temp_11 != NULL) tcg_temp_free(temp_11);
  tcg_temp_free(temp_10);

  return ret;
}





/* MAX
 *    Variables: @b, @c, @a
 *    Functions: getCCFlag, getFFlag, setZFlag, setNFlag, setCFlag, CarrySUB, setVFlag, OverflowSUB
--- code ---
{
  cc_flag = getCCFlag ();
  lb = @b;
  lc = @c;
  if((cc_flag == true))
    {
      lb = @b;
      lc = @c;
      alu = (lb - lc);
      if((lc >= lb))
        {
          @a = lc;
        }
      else
        {
          @a = lb;
        };
      if((getFFlag () == true))
        {
          setZFlag (alu);
          setNFlag (alu);
          setCFlag (CarrySUB (@a, lb, lc));
          setVFlag (OverflowSUB (@a, lb, lc));
        };
    };
}
 */

int
arc2_gen_MAX (DisasCtxt *ctx, TCGv b, TCGv c, TCGv a)
{
  int ret = BS_NONE;
  TCGv temp_7 = NULL /* REFERENCE */;
  TCGv cc_flag = tcg_temp_local_new_i32();
  TCGv lb = tcg_temp_local_new_i32();
  TCGv lc = tcg_temp_local_new_i32();
  TCGv temp_1 = tcg_temp_local_new_i32();
  TCGv temp_2 = tcg_temp_local_new_i32();
  TCGv alu = tcg_temp_local_new_i32();
  TCGv temp_3 = tcg_temp_local_new_i32();
  TCGv temp_4 = tcg_temp_local_new_i32();
  TCGv temp_8 = NULL /* REFERENCE */;
  TCGv temp_5 = tcg_temp_local_new_i32();
  TCGv temp_6 = tcg_temp_local_new_i32();
  TCGv temp_10 = NULL /* REFERENCE */;
  TCGv temp_9 = tcg_temp_local_new_i32();
  TCGv temp_12 = NULL /* REFERENCE */;
  TCGv temp_11 = tcg_temp_local_new_i32();
  temp_7 = getCCFlag();
  tcg_gen_mov_i32(cc_flag, temp_7);
  tcg_gen_mov_i32(lb, b);
  tcg_gen_mov_i32(lc, c);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_i32(temp_2, temp_1, 1); tcg_gen_andi_i32(temp_2, temp_2, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, arc_true, done_1);;
  tcg_gen_mov_i32(lb, b);
  tcg_gen_mov_i32(lc, c);
  tcg_gen_sub_i32(alu, lb, lc);
  TCGLabel *else_2 = gen_new_label();
  TCGLabel *done_2 = gen_new_label();
  tcg_gen_setcond_i32(TCG_COND_GE, temp_3, lc, lb);
  tcg_gen_xori_i32(temp_4, temp_3, 1); tcg_gen_andi_i32(temp_4, temp_4, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_4, arc_true, else_2);;
  tcg_gen_mov_i32(a, lc);
  tcg_gen_br(done_2);
  gen_set_label(else_2);
  tcg_gen_mov_i32(a, lb);
  gen_set_label(done_2);
  TCGLabel *done_3 = gen_new_label();
  temp_8 = getFFlag();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_5, temp_8, arc_true);
  tcg_gen_xori_i32(temp_6, temp_5, 1); tcg_gen_andi_i32(temp_6, temp_6, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_6, arc_true, done_3);;
  setZFlag(alu);
  setNFlag(alu);
  temp_10 = CarrySUB(a, lb, lc);
  tcg_gen_mov_i32(temp_9, temp_10);
  setCFlag(temp_9);
  temp_12 = OverflowSUB(a, lb, lc);
  tcg_gen_mov_i32(temp_11, temp_12);
  setVFlag(temp_11);
  gen_set_label(done_3);
  gen_set_label(done_1);
  if(temp_7 != NULL) tcg_temp_free(temp_7);
  tcg_temp_free(cc_flag);
  tcg_temp_free(lb);
  tcg_temp_free(lc);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  tcg_temp_free(alu);
  tcg_temp_free(temp_3);
  tcg_temp_free(temp_4);
  if(temp_8 != NULL) tcg_temp_free(temp_8);
  tcg_temp_free(temp_5);
  tcg_temp_free(temp_6);
  if(temp_10 != NULL) tcg_temp_free(temp_10);
  tcg_temp_free(temp_9);
  if(temp_12 != NULL) tcg_temp_free(temp_12);
  tcg_temp_free(temp_11);

  return ret;
}





/* MIN
 *    Variables: @b, @c, @a
 *    Functions: getCCFlag, getFFlag, setZFlag, setNFlag, setCFlag, CarrySUB, setVFlag, OverflowSUB
--- code ---
{
  cc_flag = getCCFlag ();
  lb = @b;
  lc = @c;
  if((cc_flag == true))
    {
      lb = @b;
      lc = @c;
      alu = (lb - lc);
      if((lc <= lb))
        {
          @a = lc;
        }
      else
        {
          @a = lb;
        };
      if((getFFlag () == true))
        {
          setZFlag (alu);
          setNFlag (alu);
          setCFlag (CarrySUB (@a, lb, lc));
          setVFlag (OverflowSUB (@a, lb, lc));
        };
    };
}
 */

int
arc2_gen_MIN (DisasCtxt *ctx, TCGv b, TCGv c, TCGv a)
{
  int ret = BS_NONE;
  TCGv temp_7 = NULL /* REFERENCE */;
  TCGv cc_flag = tcg_temp_local_new_i32();
  TCGv lb = tcg_temp_local_new_i32();
  TCGv lc = tcg_temp_local_new_i32();
  TCGv temp_1 = tcg_temp_local_new_i32();
  TCGv temp_2 = tcg_temp_local_new_i32();
  TCGv alu = tcg_temp_local_new_i32();
  TCGv temp_3 = tcg_temp_local_new_i32();
  TCGv temp_4 = tcg_temp_local_new_i32();
  TCGv temp_8 = NULL /* REFERENCE */;
  TCGv temp_5 = tcg_temp_local_new_i32();
  TCGv temp_6 = tcg_temp_local_new_i32();
  TCGv temp_10 = NULL /* REFERENCE */;
  TCGv temp_9 = tcg_temp_local_new_i32();
  TCGv temp_12 = NULL /* REFERENCE */;
  TCGv temp_11 = tcg_temp_local_new_i32();
  temp_7 = getCCFlag();
  tcg_gen_mov_i32(cc_flag, temp_7);
  tcg_gen_mov_i32(lb, b);
  tcg_gen_mov_i32(lc, c);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_i32(temp_2, temp_1, 1); tcg_gen_andi_i32(temp_2, temp_2, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, arc_true, done_1);;
  tcg_gen_mov_i32(lb, b);
  tcg_gen_mov_i32(lc, c);
  tcg_gen_sub_i32(alu, lb, lc);
  TCGLabel *else_2 = gen_new_label();
  TCGLabel *done_2 = gen_new_label();
  tcg_gen_setcond_i32(TCG_COND_LE, temp_3, lc, lb);
  tcg_gen_xori_i32(temp_4, temp_3, 1); tcg_gen_andi_i32(temp_4, temp_4, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_4, arc_true, else_2);;
  tcg_gen_mov_i32(a, lc);
  tcg_gen_br(done_2);
  gen_set_label(else_2);
  tcg_gen_mov_i32(a, lb);
  gen_set_label(done_2);
  TCGLabel *done_3 = gen_new_label();
  temp_8 = getFFlag();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_5, temp_8, arc_true);
  tcg_gen_xori_i32(temp_6, temp_5, 1); tcg_gen_andi_i32(temp_6, temp_6, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_6, arc_true, done_3);;
  setZFlag(alu);
  setNFlag(alu);
  temp_10 = CarrySUB(a, lb, lc);
  tcg_gen_mov_i32(temp_9, temp_10);
  setCFlag(temp_9);
  temp_12 = OverflowSUB(a, lb, lc);
  tcg_gen_mov_i32(temp_11, temp_12);
  setVFlag(temp_11);
  gen_set_label(done_3);
  gen_set_label(done_1);
  if(temp_7 != NULL) tcg_temp_free(temp_7);
  tcg_temp_free(cc_flag);
  tcg_temp_free(lb);
  tcg_temp_free(lc);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  tcg_temp_free(alu);
  tcg_temp_free(temp_3);
  tcg_temp_free(temp_4);
  if(temp_8 != NULL) tcg_temp_free(temp_8);
  tcg_temp_free(temp_5);
  tcg_temp_free(temp_6);
  if(temp_10 != NULL) tcg_temp_free(temp_10);
  tcg_temp_free(temp_9);
  if(temp_12 != NULL) tcg_temp_free(temp_12);
  tcg_temp_free(temp_11);

  return ret;
}





/* CMP
 *    Variables: @b, @c
 *    Functions: getCCFlag, setZFlag, setNFlag, setCFlag, CarrySUB, setVFlag, OverflowSUB
--- code ---
{
  cc_flag = getCCFlag ();
  if((cc_flag == true))
    {
      alu = (@b - @c);
      setZFlag (alu);
      setNFlag (alu);
      setCFlag (CarrySUB (alu, @b, @c));
      setVFlag (OverflowSUB (alu, @b, @c));
    };
}
 */

int
arc2_gen_CMP (DisasCtxt *ctx, TCGv b, TCGv c)
{
  int ret = BS_NONE;
  TCGv temp_3 = NULL /* REFERENCE */;
  TCGv cc_flag = tcg_temp_local_new_i32();
  TCGv temp_1 = tcg_temp_local_new_i32();
  TCGv temp_2 = tcg_temp_local_new_i32();
  TCGv alu = tcg_temp_local_new_i32();
  TCGv temp_5 = NULL /* REFERENCE */;
  TCGv temp_4 = tcg_temp_local_new_i32();
  TCGv temp_7 = NULL /* REFERENCE */;
  TCGv temp_6 = tcg_temp_local_new_i32();
  temp_3 = getCCFlag();
  tcg_gen_mov_i32(cc_flag, temp_3);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_i32(temp_2, temp_1, 1); tcg_gen_andi_i32(temp_2, temp_2, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, arc_true, done_1);;
  tcg_gen_sub_i32(alu, b, c);
  setZFlag(alu);
  setNFlag(alu);
  temp_5 = CarrySUB(alu, b, c);
  tcg_gen_mov_i32(temp_4, temp_5);
  setCFlag(temp_4);
  temp_7 = OverflowSUB(alu, b, c);
  tcg_gen_mov_i32(temp_6, temp_7);
  setVFlag(temp_6);
  gen_set_label(done_1);
  if(temp_3 != NULL) tcg_temp_free(temp_3);
  tcg_temp_free(cc_flag);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  tcg_temp_free(alu);
  if(temp_5 != NULL) tcg_temp_free(temp_5);
  tcg_temp_free(temp_4);
  if(temp_7 != NULL) tcg_temp_free(temp_7);
  tcg_temp_free(temp_6);

  return ret;
}





/* AND
 *    Variables: @a, @b, @c
 *    Functions: getCCFlag, getFFlag, setZFlag, setNFlag
--- code ---
{
  cc_flag = getCCFlag ();
  if((cc_flag == true))
    {
      @a = (@b & @c);
      if((getFFlag () == true))
        {
          setZFlag (@a);
          setNFlag (@a);
        };
    };
}
 */

int
arc2_gen_AND (DisasCtxt *ctx, TCGv a, TCGv b, TCGv c)
{
  int ret = BS_NONE;
  TCGv temp_5 = NULL /* REFERENCE */;
  TCGv cc_flag = tcg_temp_local_new_i32();
  TCGv temp_1 = tcg_temp_local_new_i32();
  TCGv temp_2 = tcg_temp_local_new_i32();
  TCGv temp_6 = NULL /* REFERENCE */;
  TCGv temp_3 = tcg_temp_local_new_i32();
  TCGv temp_4 = tcg_temp_local_new_i32();
  temp_5 = getCCFlag();
  tcg_gen_mov_i32(cc_flag, temp_5);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_i32(temp_2, temp_1, 1); tcg_gen_andi_i32(temp_2, temp_2, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, arc_true, done_1);;
  tcg_gen_and_i32(a, b, c);
  TCGLabel *done_2 = gen_new_label();
  temp_6 = getFFlag();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_3, temp_6, arc_true);
  tcg_gen_xori_i32(temp_4, temp_3, 1); tcg_gen_andi_i32(temp_4, temp_4, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_4, arc_true, done_2);;
  setZFlag(a);
  setNFlag(a);
  gen_set_label(done_2);
  gen_set_label(done_1);
  if(temp_5 != NULL) tcg_temp_free(temp_5);
  tcg_temp_free(cc_flag);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  if(temp_6 != NULL) tcg_temp_free(temp_6);
  tcg_temp_free(temp_3);
  tcg_temp_free(temp_4);

  return ret;
}





/* OR
 *    Variables: @a, @b, @c
 *    Functions: getCCFlag, getFFlag, setZFlag, setNFlag
--- code ---
{
  cc_flag = getCCFlag ();
  if((cc_flag == true))
    {
      @a = (@b | @c);
      if((getFFlag () == true))
        {
          setZFlag (@a);
          setNFlag (@a);
        };
    };
}
 */

int
arc2_gen_OR (DisasCtxt *ctx, TCGv a, TCGv b, TCGv c)
{
  int ret = BS_NONE;
  TCGv temp_5 = NULL /* REFERENCE */;
  TCGv cc_flag = tcg_temp_local_new_i32();
  TCGv temp_1 = tcg_temp_local_new_i32();
  TCGv temp_2 = tcg_temp_local_new_i32();
  TCGv temp_6 = NULL /* REFERENCE */;
  TCGv temp_3 = tcg_temp_local_new_i32();
  TCGv temp_4 = tcg_temp_local_new_i32();
  temp_5 = getCCFlag();
  tcg_gen_mov_i32(cc_flag, temp_5);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_i32(temp_2, temp_1, 1); tcg_gen_andi_i32(temp_2, temp_2, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, arc_true, done_1);;
  tcg_gen_or_i32(a, b, c);
  TCGLabel *done_2 = gen_new_label();
  temp_6 = getFFlag();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_3, temp_6, arc_true);
  tcg_gen_xori_i32(temp_4, temp_3, 1); tcg_gen_andi_i32(temp_4, temp_4, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_4, arc_true, done_2);;
  setZFlag(a);
  setNFlag(a);
  gen_set_label(done_2);
  gen_set_label(done_1);
  if(temp_5 != NULL) tcg_temp_free(temp_5);
  tcg_temp_free(cc_flag);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  if(temp_6 != NULL) tcg_temp_free(temp_6);
  tcg_temp_free(temp_3);
  tcg_temp_free(temp_4);

  return ret;
}





/* XOR
 *    Variables: @a, @b, @c
 *    Functions: getCCFlag, getFFlag, setZFlag, setNFlag
--- code ---
{
  cc_flag = getCCFlag ();
  if((cc_flag == true))
    {
      @a = (@b ^ @c);
      if((getFFlag () == true))
        {
          setZFlag (@a);
          setNFlag (@a);
        };
    };
}
 */

int
arc2_gen_XOR (DisasCtxt *ctx, TCGv a, TCGv b, TCGv c)
{
  int ret = BS_NONE;
  TCGv temp_5 = NULL /* REFERENCE */;
  TCGv cc_flag = tcg_temp_local_new_i32();
  TCGv temp_1 = tcg_temp_local_new_i32();
  TCGv temp_2 = tcg_temp_local_new_i32();
  TCGv temp_6 = NULL /* REFERENCE */;
  TCGv temp_3 = tcg_temp_local_new_i32();
  TCGv temp_4 = tcg_temp_local_new_i32();
  temp_5 = getCCFlag();
  tcg_gen_mov_i32(cc_flag, temp_5);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_i32(temp_2, temp_1, 1); tcg_gen_andi_i32(temp_2, temp_2, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, arc_true, done_1);;
  tcg_gen_xor_i32(a, b, c);
  TCGLabel *done_2 = gen_new_label();
  temp_6 = getFFlag();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_3, temp_6, arc_true);
  tcg_gen_xori_i32(temp_4, temp_3, 1); tcg_gen_andi_i32(temp_4, temp_4, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_4, arc_true, done_2);;
  setZFlag(a);
  setNFlag(a);
  gen_set_label(done_2);
  gen_set_label(done_1);
  if(temp_5 != NULL) tcg_temp_free(temp_5);
  tcg_temp_free(cc_flag);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  if(temp_6 != NULL) tcg_temp_free(temp_6);
  tcg_temp_free(temp_3);
  tcg_temp_free(temp_4);

  return ret;
}





/* MOV
 *    Variables: @a, @b
 *    Functions: getCCFlag, getFFlag, setZFlag, setNFlag
--- code ---
{
  cc_flag = getCCFlag ();
  if((cc_flag == true))
    {
      @a = @b;
      if((getFFlag () == true))
        {
          setZFlag (@a);
          setNFlag (@a);
        };
    };
}
 */

int
arc2_gen_MOV (DisasCtxt *ctx, TCGv a, TCGv b)
{
  int ret = BS_NONE;
  TCGv temp_5 = NULL /* REFERENCE */;
  TCGv cc_flag = tcg_temp_local_new_i32();
  TCGv temp_1 = tcg_temp_local_new_i32();
  TCGv temp_2 = tcg_temp_local_new_i32();
  TCGv temp_6 = NULL /* REFERENCE */;
  TCGv temp_3 = tcg_temp_local_new_i32();
  TCGv temp_4 = tcg_temp_local_new_i32();
  temp_5 = getCCFlag();
  tcg_gen_mov_i32(cc_flag, temp_5);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_i32(temp_2, temp_1, 1); tcg_gen_andi_i32(temp_2, temp_2, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, arc_true, done_1);;
  tcg_gen_mov_i32(a, b);
  TCGLabel *done_2 = gen_new_label();
  temp_6 = getFFlag();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_3, temp_6, arc_true);
  tcg_gen_xori_i32(temp_4, temp_3, 1); tcg_gen_andi_i32(temp_4, temp_4, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_4, arc_true, done_2);;
  setZFlag(a);
  setNFlag(a);
  gen_set_label(done_2);
  gen_set_label(done_1);
  if(temp_5 != NULL) tcg_temp_free(temp_5);
  tcg_temp_free(cc_flag);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  if(temp_6 != NULL) tcg_temp_free(temp_6);
  tcg_temp_free(temp_3);
  tcg_temp_free(temp_4);

  return ret;
}





/* ASL
 *    Variables: @b, @c, @a
 *    Functions: getCCFlag, getFFlag, setZFlag, setNFlag, setCFlag, getBit
--- code ---
{
  cc_flag = getCCFlag ();
  if((cc_flag == true))
    {
      lb = @b;
      lc = (@c & 31);
      @a = (lb << lc);
      if((getFFlag () == true))
        {
          setZFlag (@a);
          setNFlag (@a);
          if((lc == 0))
            {
              setCFlag (0);
            }
          else
            {
              setCFlag (getBit (lb, (32 - lc)));
            };
        };
    };
}
 */

int
arc2_gen_ASL (DisasCtxt *ctx, TCGv b, TCGv c, TCGv a)
{
  int ret = BS_NONE;
  TCGv temp_7 = NULL /* REFERENCE */;
  TCGv cc_flag = tcg_temp_local_new_i32();
  TCGv temp_1 = tcg_temp_local_new_i32();
  TCGv temp_2 = tcg_temp_local_new_i32();
  TCGv lb = tcg_temp_local_new_i32();
  TCGv lc = tcg_temp_local_new_i32();
  TCGv temp_8 = NULL /* REFERENCE */;
  TCGv temp_3 = tcg_temp_local_new_i32();
  TCGv temp_4 = tcg_temp_local_new_i32();
  TCGv temp_5 = tcg_temp_local_new_i32();
  TCGv temp_6 = tcg_temp_local_new_i32();
  TCGv temp_9 = tcg_temp_local_new_i32();
  TCGv temp_12 = tcg_temp_local_new_i32();
  TCGv temp_11 = NULL /* REFERENCE */;
  TCGv temp_10 = tcg_temp_local_new_i32();
  temp_7 = getCCFlag();
  tcg_gen_mov_i32(cc_flag, temp_7);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_i32(temp_2, temp_1, 1); tcg_gen_andi_i32(temp_2, temp_2, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, arc_true, done_1);;
  tcg_gen_mov_i32(lb, b);
  tcg_gen_andi_i32(lc, c, 31);
  tcg_gen_shl_i32(a, lb, lc);
  TCGLabel *done_2 = gen_new_label();
  temp_8 = getFFlag();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_3, temp_8, arc_true);
  tcg_gen_xori_i32(temp_4, temp_3, 1); tcg_gen_andi_i32(temp_4, temp_4, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_4, arc_true, done_2);;
  setZFlag(a);
  setNFlag(a);
  TCGLabel *else_3 = gen_new_label();
  TCGLabel *done_3 = gen_new_label();
  tcg_gen_setcondi_i32(TCG_COND_EQ, temp_5, lc, 0);
  tcg_gen_xori_i32(temp_6, temp_5, 1); tcg_gen_andi_i32(temp_6, temp_6, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_6, arc_true, else_3);;
  tcg_gen_movi_i32(temp_9, 0);
  setCFlag(temp_9);
  tcg_gen_br(done_3);
  gen_set_label(else_3);
  tcg_gen_subfi_i32(temp_12, 32, lc);
  temp_11 = getBit(lb, temp_12);
  tcg_gen_mov_i32(temp_10, temp_11);
  setCFlag(temp_10);
  gen_set_label(done_3);
  gen_set_label(done_2);
  gen_set_label(done_1);
  if(temp_7 != NULL) tcg_temp_free(temp_7);
  tcg_temp_free(cc_flag);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  tcg_temp_free(lb);
  tcg_temp_free(lc);
  if(temp_8 != NULL) tcg_temp_free(temp_8);
  tcg_temp_free(temp_3);
  tcg_temp_free(temp_4);
  tcg_temp_free(temp_5);
  tcg_temp_free(temp_6);
  tcg_temp_free(temp_9);
  tcg_temp_free(temp_12);
  if(temp_11 != NULL) tcg_temp_free(temp_11);
  tcg_temp_free(temp_10);

  return ret;
}





/* ASR
 *    Variables: @b, @c, @a
 *    Functions: getCCFlag, arithmeticShiftRight, getFFlag, setZFlag, setNFlag, setCFlag, getBit
--- code ---
{
  cc_flag = getCCFlag ();
  if((cc_flag == true))
    {
      lb = @b;
      lc = (@c & 31);
      @a = arithmeticShiftRight (lb, lc);
      if((getFFlag () == true))
        {
          setZFlag (@a);
          setNFlag (@a);
          if((lc == 0))
            {
              setCFlag (0);
            }
          else
            {
              setCFlag (getBit (lb, (lc - 1)));
            };
        };
    };
}
 */

int
arc2_gen_ASR (DisasCtxt *ctx, TCGv b, TCGv c, TCGv a)
{
  int ret = BS_NONE;
  TCGv temp_7 = NULL /* REFERENCE */;
  TCGv cc_flag = tcg_temp_local_new_i32();
  TCGv temp_1 = tcg_temp_local_new_i32();
  TCGv temp_2 = tcg_temp_local_new_i32();
  TCGv lb = tcg_temp_local_new_i32();
  TCGv lc = tcg_temp_local_new_i32();
  TCGv temp_8 = NULL /* REFERENCE */;
  TCGv temp_9 = NULL /* REFERENCE */;
  TCGv temp_3 = tcg_temp_local_new_i32();
  TCGv temp_4 = tcg_temp_local_new_i32();
  TCGv temp_5 = tcg_temp_local_new_i32();
  TCGv temp_6 = tcg_temp_local_new_i32();
  TCGv temp_10 = tcg_temp_local_new_i32();
  TCGv temp_13 = tcg_temp_local_new_i32();
  TCGv temp_12 = NULL /* REFERENCE */;
  TCGv temp_11 = tcg_temp_local_new_i32();
  temp_7 = getCCFlag();
  tcg_gen_mov_i32(cc_flag, temp_7);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_i32(temp_2, temp_1, 1); tcg_gen_andi_i32(temp_2, temp_2, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, arc_true, done_1);;
  tcg_gen_mov_i32(lb, b);
  tcg_gen_andi_i32(lc, c, 31);
  temp_8 = arithmeticShiftRight(lb, lc);
  tcg_gen_mov_i32(a, temp_8);
  TCGLabel *done_2 = gen_new_label();
  temp_9 = getFFlag();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_3, temp_9, arc_true);
  tcg_gen_xori_i32(temp_4, temp_3, 1); tcg_gen_andi_i32(temp_4, temp_4, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_4, arc_true, done_2);;
  setZFlag(a);
  setNFlag(a);
  TCGLabel *else_3 = gen_new_label();
  TCGLabel *done_3 = gen_new_label();
  tcg_gen_setcondi_i32(TCG_COND_EQ, temp_5, lc, 0);
  tcg_gen_xori_i32(temp_6, temp_5, 1); tcg_gen_andi_i32(temp_6, temp_6, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_6, arc_true, else_3);;
  tcg_gen_movi_i32(temp_10, 0);
  setCFlag(temp_10);
  tcg_gen_br(done_3);
  gen_set_label(else_3);
  tcg_gen_subi_i32(temp_13, lc, 1);
  temp_12 = getBit(lb, temp_13);
  tcg_gen_mov_i32(temp_11, temp_12);
  setCFlag(temp_11);
  gen_set_label(done_3);
  gen_set_label(done_2);
  gen_set_label(done_1);
  if(temp_7 != NULL) tcg_temp_free(temp_7);
  tcg_temp_free(cc_flag);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  tcg_temp_free(lb);
  tcg_temp_free(lc);
  if(temp_8 != NULL) tcg_temp_free(temp_8);
  if(temp_9 != NULL) tcg_temp_free(temp_9);
  tcg_temp_free(temp_3);
  tcg_temp_free(temp_4);
  tcg_temp_free(temp_5);
  tcg_temp_free(temp_6);
  tcg_temp_free(temp_10);
  tcg_temp_free(temp_13);
  if(temp_12 != NULL) tcg_temp_free(temp_12);
  tcg_temp_free(temp_11);

  return ret;
}





/* ASR8
 *    Variables: @b, @a
 *    Functions: getCCFlag, arithmeticShiftRight, getFFlag, setZFlag, setNFlag
--- code ---
{
  cc_flag = getCCFlag ();
  if((cc_flag == true))
    {
      lb = @b;
      @a = arithmeticShiftRight (lb, 8);
      if((getFFlag () == true))
        {
          setZFlag (@a);
          setNFlag (@a);
        };
    };
}
 */

int
arc2_gen_ASR8 (DisasCtxt *ctx, TCGv b, TCGv a)
{
  int ret = BS_NONE;
  TCGv temp_5 = NULL /* REFERENCE */;
  TCGv cc_flag = tcg_temp_local_new_i32();
  TCGv temp_1 = tcg_temp_local_new_i32();
  TCGv temp_2 = tcg_temp_local_new_i32();
  TCGv lb = tcg_temp_local_new_i32();
  TCGv temp_7 = tcg_temp_local_new_i32();
  TCGv temp_6 = NULL /* REFERENCE */;
  TCGv temp_8 = NULL /* REFERENCE */;
  TCGv temp_3 = tcg_temp_local_new_i32();
  TCGv temp_4 = tcg_temp_local_new_i32();
  temp_5 = getCCFlag();
  tcg_gen_mov_i32(cc_flag, temp_5);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_i32(temp_2, temp_1, 1); tcg_gen_andi_i32(temp_2, temp_2, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, arc_true, done_1);;
  tcg_gen_mov_i32(lb, b);
  tcg_gen_movi_i32(temp_7, 8);
  temp_6 = arithmeticShiftRight(lb, temp_7);
  tcg_gen_mov_i32(a, temp_6);
  TCGLabel *done_2 = gen_new_label();
  temp_8 = getFFlag();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_3, temp_8, arc_true);
  tcg_gen_xori_i32(temp_4, temp_3, 1); tcg_gen_andi_i32(temp_4, temp_4, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_4, arc_true, done_2);;
  setZFlag(a);
  setNFlag(a);
  gen_set_label(done_2);
  gen_set_label(done_1);
  if(temp_5 != NULL) tcg_temp_free(temp_5);
  tcg_temp_free(cc_flag);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  tcg_temp_free(lb);
  tcg_temp_free(temp_7);
  if(temp_6 != NULL) tcg_temp_free(temp_6);
  if(temp_8 != NULL) tcg_temp_free(temp_8);
  tcg_temp_free(temp_3);
  tcg_temp_free(temp_4);

  return ret;
}





/* ASR16
 *    Variables: @b, @a
 *    Functions: getCCFlag, arithmeticShiftRight, getFFlag, setZFlag, setNFlag
--- code ---
{
  cc_flag = getCCFlag ();
  if((cc_flag == true))
    {
      lb = @b;
      @a = arithmeticShiftRight (lb, 16);
      if((getFFlag () == true))
        {
          setZFlag (@a);
          setNFlag (@a);
        };
    };
}
 */

int
arc2_gen_ASR16 (DisasCtxt *ctx, TCGv b, TCGv a)
{
  int ret = BS_NONE;
  TCGv temp_5 = NULL /* REFERENCE */;
  TCGv cc_flag = tcg_temp_local_new_i32();
  TCGv temp_1 = tcg_temp_local_new_i32();
  TCGv temp_2 = tcg_temp_local_new_i32();
  TCGv lb = tcg_temp_local_new_i32();
  TCGv temp_7 = tcg_temp_local_new_i32();
  TCGv temp_6 = NULL /* REFERENCE */;
  TCGv temp_8 = NULL /* REFERENCE */;
  TCGv temp_3 = tcg_temp_local_new_i32();
  TCGv temp_4 = tcg_temp_local_new_i32();
  temp_5 = getCCFlag();
  tcg_gen_mov_i32(cc_flag, temp_5);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_i32(temp_2, temp_1, 1); tcg_gen_andi_i32(temp_2, temp_2, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, arc_true, done_1);;
  tcg_gen_mov_i32(lb, b);
  tcg_gen_movi_i32(temp_7, 16);
  temp_6 = arithmeticShiftRight(lb, temp_7);
  tcg_gen_mov_i32(a, temp_6);
  TCGLabel *done_2 = gen_new_label();
  temp_8 = getFFlag();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_3, temp_8, arc_true);
  tcg_gen_xori_i32(temp_4, temp_3, 1); tcg_gen_andi_i32(temp_4, temp_4, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_4, arc_true, done_2);;
  setZFlag(a);
  setNFlag(a);
  gen_set_label(done_2);
  gen_set_label(done_1);
  if(temp_5 != NULL) tcg_temp_free(temp_5);
  tcg_temp_free(cc_flag);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  tcg_temp_free(lb);
  tcg_temp_free(temp_7);
  if(temp_6 != NULL) tcg_temp_free(temp_6);
  if(temp_8 != NULL) tcg_temp_free(temp_8);
  tcg_temp_free(temp_3);
  tcg_temp_free(temp_4);

  return ret;
}





/* LSL16
 *    Variables: @a, @b
 *    Functions: getCCFlag, logicalShiftLeft, getFFlag, setZFlag, setNFlag
--- code ---
{
  cc_flag = getCCFlag ();
  if((cc_flag == true))
    {
      @a = logicalShiftLeft (@b, 16);
      if((getFFlag () == true))
        {
          setZFlag (@a);
          setNFlag (@a);
        };
    };
}
 */

int
arc2_gen_LSL16 (DisasCtxt *ctx, TCGv a, TCGv b)
{
  int ret = BS_NONE;
  TCGv temp_5 = NULL /* REFERENCE */;
  TCGv cc_flag = tcg_temp_local_new_i32();
  TCGv temp_1 = tcg_temp_local_new_i32();
  TCGv temp_2 = tcg_temp_local_new_i32();
  TCGv temp_7 = tcg_temp_local_new_i32();
  TCGv temp_6 = NULL /* REFERENCE */;
  TCGv temp_8 = NULL /* REFERENCE */;
  TCGv temp_3 = tcg_temp_local_new_i32();
  TCGv temp_4 = tcg_temp_local_new_i32();
  temp_5 = getCCFlag();
  tcg_gen_mov_i32(cc_flag, temp_5);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_i32(temp_2, temp_1, 1); tcg_gen_andi_i32(temp_2, temp_2, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, arc_true, done_1);;
  tcg_gen_movi_i32(temp_7, 16);
  temp_6 = logicalShiftLeft(b, temp_7);
  tcg_gen_mov_i32(a, temp_6);
  TCGLabel *done_2 = gen_new_label();
  temp_8 = getFFlag();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_3, temp_8, arc_true);
  tcg_gen_xori_i32(temp_4, temp_3, 1); tcg_gen_andi_i32(temp_4, temp_4, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_4, arc_true, done_2);;
  setZFlag(a);
  setNFlag(a);
  gen_set_label(done_2);
  gen_set_label(done_1);
  if(temp_5 != NULL) tcg_temp_free(temp_5);
  tcg_temp_free(cc_flag);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  tcg_temp_free(temp_7);
  if(temp_6 != NULL) tcg_temp_free(temp_6);
  if(temp_8 != NULL) tcg_temp_free(temp_8);
  tcg_temp_free(temp_3);
  tcg_temp_free(temp_4);

  return ret;
}





/* LSL8
 *    Variables: @a, @b
 *    Functions: getCCFlag, logicalShiftLeft, getFFlag, setZFlag, setNFlag
--- code ---
{
  cc_flag = getCCFlag ();
  if((cc_flag == true))
    {
      @a = logicalShiftLeft (@b, 8);
      if((getFFlag () == true))
        {
          setZFlag (@a);
          setNFlag (@a);
        };
    };
}
 */

int
arc2_gen_LSL8 (DisasCtxt *ctx, TCGv a, TCGv b)
{
  int ret = BS_NONE;
  TCGv temp_5 = NULL /* REFERENCE */;
  TCGv cc_flag = tcg_temp_local_new_i32();
  TCGv temp_1 = tcg_temp_local_new_i32();
  TCGv temp_2 = tcg_temp_local_new_i32();
  TCGv temp_7 = tcg_temp_local_new_i32();
  TCGv temp_6 = NULL /* REFERENCE */;
  TCGv temp_8 = NULL /* REFERENCE */;
  TCGv temp_3 = tcg_temp_local_new_i32();
  TCGv temp_4 = tcg_temp_local_new_i32();
  temp_5 = getCCFlag();
  tcg_gen_mov_i32(cc_flag, temp_5);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_i32(temp_2, temp_1, 1); tcg_gen_andi_i32(temp_2, temp_2, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, arc_true, done_1);;
  tcg_gen_movi_i32(temp_7, 8);
  temp_6 = logicalShiftLeft(b, temp_7);
  tcg_gen_mov_i32(a, temp_6);
  TCGLabel *done_2 = gen_new_label();
  temp_8 = getFFlag();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_3, temp_8, arc_true);
  tcg_gen_xori_i32(temp_4, temp_3, 1); tcg_gen_andi_i32(temp_4, temp_4, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_4, arc_true, done_2);;
  setZFlag(a);
  setNFlag(a);
  gen_set_label(done_2);
  gen_set_label(done_1);
  if(temp_5 != NULL) tcg_temp_free(temp_5);
  tcg_temp_free(cc_flag);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  tcg_temp_free(temp_7);
  if(temp_6 != NULL) tcg_temp_free(temp_6);
  if(temp_8 != NULL) tcg_temp_free(temp_8);
  tcg_temp_free(temp_3);
  tcg_temp_free(temp_4);

  return ret;
}





/* LSR
 *    Variables: @b, @c, @a
 *    Functions: getCCFlag, logicalShiftRight, getFFlag, setZFlag, setNFlag, setCFlag, getBit
--- code ---
{
  cc_flag = getCCFlag ();
  if((cc_flag == true))
    {
      lb = @b;
      lc = (@c & 31);
      @a = logicalShiftRight (lb, lc);
      if((getFFlag () == true))
        {
          setZFlag (@a);
          setNFlag (@a);
          if((lc == 0))
            {
              setCFlag (0);
            }
          else
            {
              setCFlag (getBit (lb, (lc - 1)));
            };
        };
    };
}
 */

int
arc2_gen_LSR (DisasCtxt *ctx, TCGv b, TCGv c, TCGv a)
{
  int ret = BS_NONE;
  TCGv temp_7 = NULL /* REFERENCE */;
  TCGv cc_flag = tcg_temp_local_new_i32();
  TCGv temp_1 = tcg_temp_local_new_i32();
  TCGv temp_2 = tcg_temp_local_new_i32();
  TCGv lb = tcg_temp_local_new_i32();
  TCGv lc = tcg_temp_local_new_i32();
  TCGv temp_8 = NULL /* REFERENCE */;
  TCGv temp_9 = NULL /* REFERENCE */;
  TCGv temp_3 = tcg_temp_local_new_i32();
  TCGv temp_4 = tcg_temp_local_new_i32();
  TCGv temp_5 = tcg_temp_local_new_i32();
  TCGv temp_6 = tcg_temp_local_new_i32();
  TCGv temp_10 = tcg_temp_local_new_i32();
  TCGv temp_13 = tcg_temp_local_new_i32();
  TCGv temp_12 = NULL /* REFERENCE */;
  TCGv temp_11 = tcg_temp_local_new_i32();
  temp_7 = getCCFlag();
  tcg_gen_mov_i32(cc_flag, temp_7);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_i32(temp_2, temp_1, 1); tcg_gen_andi_i32(temp_2, temp_2, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, arc_true, done_1);;
  tcg_gen_mov_i32(lb, b);
  tcg_gen_andi_i32(lc, c, 31);
  temp_8 = logicalShiftRight(lb, lc);
  tcg_gen_mov_i32(a, temp_8);
  TCGLabel *done_2 = gen_new_label();
  temp_9 = getFFlag();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_3, temp_9, arc_true);
  tcg_gen_xori_i32(temp_4, temp_3, 1); tcg_gen_andi_i32(temp_4, temp_4, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_4, arc_true, done_2);;
  setZFlag(a);
  setNFlag(a);
  TCGLabel *else_3 = gen_new_label();
  TCGLabel *done_3 = gen_new_label();
  tcg_gen_setcondi_i32(TCG_COND_EQ, temp_5, lc, 0);
  tcg_gen_xori_i32(temp_6, temp_5, 1); tcg_gen_andi_i32(temp_6, temp_6, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_6, arc_true, else_3);;
  tcg_gen_movi_i32(temp_10, 0);
  setCFlag(temp_10);
  tcg_gen_br(done_3);
  gen_set_label(else_3);
  tcg_gen_subi_i32(temp_13, lc, 1);
  temp_12 = getBit(lb, temp_13);
  tcg_gen_mov_i32(temp_11, temp_12);
  setCFlag(temp_11);
  gen_set_label(done_3);
  gen_set_label(done_2);
  gen_set_label(done_1);
  if(temp_7 != NULL) tcg_temp_free(temp_7);
  tcg_temp_free(cc_flag);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  tcg_temp_free(lb);
  tcg_temp_free(lc);
  if(temp_8 != NULL) tcg_temp_free(temp_8);
  if(temp_9 != NULL) tcg_temp_free(temp_9);
  tcg_temp_free(temp_3);
  tcg_temp_free(temp_4);
  tcg_temp_free(temp_5);
  tcg_temp_free(temp_6);
  tcg_temp_free(temp_10);
  tcg_temp_free(temp_13);
  if(temp_12 != NULL) tcg_temp_free(temp_12);
  tcg_temp_free(temp_11);

  return ret;
}





/* LSR16
 *    Variables: @a, @b
 *    Functions: getCCFlag, logicalShiftRight, getFFlag, setZFlag, setNFlag
--- code ---
{
  cc_flag = getCCFlag ();
  if((cc_flag == true))
    {
      @a = logicalShiftRight (@b, 16);
      if((getFFlag () == true))
        {
          setZFlag (@a);
          setNFlag (@a);
        };
    };
}
 */

int
arc2_gen_LSR16 (DisasCtxt *ctx, TCGv a, TCGv b)
{
  int ret = BS_NONE;
  TCGv temp_5 = NULL /* REFERENCE */;
  TCGv cc_flag = tcg_temp_local_new_i32();
  TCGv temp_1 = tcg_temp_local_new_i32();
  TCGv temp_2 = tcg_temp_local_new_i32();
  TCGv temp_7 = tcg_temp_local_new_i32();
  TCGv temp_6 = NULL /* REFERENCE */;
  TCGv temp_8 = NULL /* REFERENCE */;
  TCGv temp_3 = tcg_temp_local_new_i32();
  TCGv temp_4 = tcg_temp_local_new_i32();
  temp_5 = getCCFlag();
  tcg_gen_mov_i32(cc_flag, temp_5);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_i32(temp_2, temp_1, 1); tcg_gen_andi_i32(temp_2, temp_2, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, arc_true, done_1);;
  tcg_gen_movi_i32(temp_7, 16);
  temp_6 = logicalShiftRight(b, temp_7);
  tcg_gen_mov_i32(a, temp_6);
  TCGLabel *done_2 = gen_new_label();
  temp_8 = getFFlag();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_3, temp_8, arc_true);
  tcg_gen_xori_i32(temp_4, temp_3, 1); tcg_gen_andi_i32(temp_4, temp_4, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_4, arc_true, done_2);;
  setZFlag(a);
  setNFlag(a);
  gen_set_label(done_2);
  gen_set_label(done_1);
  if(temp_5 != NULL) tcg_temp_free(temp_5);
  tcg_temp_free(cc_flag);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  tcg_temp_free(temp_7);
  if(temp_6 != NULL) tcg_temp_free(temp_6);
  if(temp_8 != NULL) tcg_temp_free(temp_8);
  tcg_temp_free(temp_3);
  tcg_temp_free(temp_4);

  return ret;
}





/* LSR8
 *    Variables: @a, @b
 *    Functions: getCCFlag, logicalShiftRight, getFFlag, setZFlag, setNFlag
--- code ---
{
  cc_flag = getCCFlag ();
  if((cc_flag == true))
    {
      @a = logicalShiftRight (@b, 8);
      if((getFFlag () == true))
        {
          setZFlag (@a);
          setNFlag (@a);
        };
    };
}
 */

int
arc2_gen_LSR8 (DisasCtxt *ctx, TCGv a, TCGv b)
{
  int ret = BS_NONE;
  TCGv temp_5 = NULL /* REFERENCE */;
  TCGv cc_flag = tcg_temp_local_new_i32();
  TCGv temp_1 = tcg_temp_local_new_i32();
  TCGv temp_2 = tcg_temp_local_new_i32();
  TCGv temp_7 = tcg_temp_local_new_i32();
  TCGv temp_6 = NULL /* REFERENCE */;
  TCGv temp_8 = NULL /* REFERENCE */;
  TCGv temp_3 = tcg_temp_local_new_i32();
  TCGv temp_4 = tcg_temp_local_new_i32();
  temp_5 = getCCFlag();
  tcg_gen_mov_i32(cc_flag, temp_5);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_i32(temp_2, temp_1, 1); tcg_gen_andi_i32(temp_2, temp_2, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, arc_true, done_1);;
  tcg_gen_movi_i32(temp_7, 8);
  temp_6 = logicalShiftRight(b, temp_7);
  tcg_gen_mov_i32(a, temp_6);
  TCGLabel *done_2 = gen_new_label();
  temp_8 = getFFlag();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_3, temp_8, arc_true);
  tcg_gen_xori_i32(temp_4, temp_3, 1); tcg_gen_andi_i32(temp_4, temp_4, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_4, arc_true, done_2);;
  setZFlag(a);
  setNFlag(a);
  gen_set_label(done_2);
  gen_set_label(done_1);
  if(temp_5 != NULL) tcg_temp_free(temp_5);
  tcg_temp_free(cc_flag);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  tcg_temp_free(temp_7);
  if(temp_6 != NULL) tcg_temp_free(temp_6);
  if(temp_8 != NULL) tcg_temp_free(temp_8);
  tcg_temp_free(temp_3);
  tcg_temp_free(temp_4);

  return ret;
}





/* BIC
 *    Variables: @a, @b, @c
 *    Functions: getCCFlag, getFFlag, setZFlag, setNFlag
--- code ---
{
  cc_flag = getCCFlag ();
  if((cc_flag == true))
    {
      @a = (@b & ~@c);
      if((getFFlag () == true))
        {
          setZFlag (@a);
          setNFlag (@a);
        };
    };
}
 */

int
arc2_gen_BIC (DisasCtxt *ctx, TCGv a, TCGv b, TCGv c)
{
  int ret = BS_NONE;
  TCGv temp_5 = NULL /* REFERENCE */;
  TCGv cc_flag = tcg_temp_local_new_i32();
  TCGv temp_1 = tcg_temp_local_new_i32();
  TCGv temp_2 = tcg_temp_local_new_i32();
  TCGv temp_6 = tcg_temp_local_new_i32();
  TCGv temp_7 = NULL /* REFERENCE */;
  TCGv temp_3 = tcg_temp_local_new_i32();
  TCGv temp_4 = tcg_temp_local_new_i32();
  temp_5 = getCCFlag();
  tcg_gen_mov_i32(cc_flag, temp_5);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_i32(temp_2, temp_1, 1); tcg_gen_andi_i32(temp_2, temp_2, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, arc_true, done_1);;
  tcg_gen_not_i32(temp_6, c);
  tcg_gen_and_i32(a, b, temp_6);
  TCGLabel *done_2 = gen_new_label();
  temp_7 = getFFlag();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_3, temp_7, arc_true);
  tcg_gen_xori_i32(temp_4, temp_3, 1); tcg_gen_andi_i32(temp_4, temp_4, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_4, arc_true, done_2);;
  setZFlag(a);
  setNFlag(a);
  gen_set_label(done_2);
  gen_set_label(done_1);
  if(temp_5 != NULL) tcg_temp_free(temp_5);
  tcg_temp_free(cc_flag);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  tcg_temp_free(temp_6);
  if(temp_7 != NULL) tcg_temp_free(temp_7);
  tcg_temp_free(temp_3);
  tcg_temp_free(temp_4);

  return ret;
}





/* BCLR
 *    Variables: @c, @a, @b
 *    Functions: getCCFlag, getFFlag, setZFlag, setNFlag
--- code ---
{
  cc_flag = getCCFlag ();
  if((cc_flag == true))
    {
      tmp = (1 << (@c & 31));
      @a = (@b & ~tmp);
      if((getFFlag () == true))
        {
          setZFlag (@a);
          setNFlag (@a);
        };
    };
}
 */

int
arc2_gen_BCLR (DisasCtxt *ctx, TCGv c, TCGv a, TCGv b)
{
  int ret = BS_NONE;
  TCGv temp_5 = NULL /* REFERENCE */;
  TCGv cc_flag = tcg_temp_local_new_i32();
  TCGv temp_1 = tcg_temp_local_new_i32();
  TCGv temp_2 = tcg_temp_local_new_i32();
  TCGv temp_6 = tcg_temp_local_new_i32();
  TCGv tmp = tcg_temp_local_new_i32();
  TCGv temp_7 = tcg_temp_local_new_i32();
  TCGv temp_8 = NULL /* REFERENCE */;
  TCGv temp_3 = tcg_temp_local_new_i32();
  TCGv temp_4 = tcg_temp_local_new_i32();
  temp_5 = getCCFlag();
  tcg_gen_mov_i32(cc_flag, temp_5);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_i32(temp_2, temp_1, 1); tcg_gen_andi_i32(temp_2, temp_2, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, arc_true, done_1);;
  tcg_gen_andi_i32(temp_6, c, 31);
  tcg_gen_shlfi_i32(tmp, 1, temp_6);
  tcg_gen_not_i32(temp_7, tmp);
  tcg_gen_and_i32(a, b, temp_7);
  TCGLabel *done_2 = gen_new_label();
  temp_8 = getFFlag();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_3, temp_8, arc_true);
  tcg_gen_xori_i32(temp_4, temp_3, 1); tcg_gen_andi_i32(temp_4, temp_4, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_4, arc_true, done_2);;
  setZFlag(a);
  setNFlag(a);
  gen_set_label(done_2);
  gen_set_label(done_1);
  if(temp_5 != NULL) tcg_temp_free(temp_5);
  tcg_temp_free(cc_flag);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  tcg_temp_free(temp_6);
  tcg_temp_free(tmp);
  tcg_temp_free(temp_7);
  if(temp_8 != NULL) tcg_temp_free(temp_8);
  tcg_temp_free(temp_3);
  tcg_temp_free(temp_4);

  return ret;
}





/* BMSK
 *    Variables: @c, @a, @b
 *    Functions: getCCFlag, getFFlag, setZFlag, setNFlag
--- code ---
{
  cc_flag = getCCFlag ();
  if((cc_flag == true))
    {
      tmp1 = ((@c & 31) + 1);
      if((tmp1 == 32))
        {
          tmp2 = 4294967295;
        }
      else
        {
          tmp2 = ((1 << tmp1) - 1);
        };
      @a = (@b & tmp2);
      if((getFFlag () == true))
        {
          setZFlag (@a);
          setNFlag (@a);
        };
    };
}
 */

int
arc2_gen_BMSK (DisasCtxt *ctx, TCGv c, TCGv a, TCGv b)
{
  int ret = BS_NONE;
  TCGv temp_7 = NULL /* REFERENCE */;
  TCGv cc_flag = tcg_temp_local_new_i32();
  TCGv temp_1 = tcg_temp_local_new_i32();
  TCGv temp_2 = tcg_temp_local_new_i32();
  TCGv temp_8 = tcg_temp_local_new_i32();
  TCGv tmp1 = tcg_temp_local_new_i32();
  TCGv temp_3 = tcg_temp_local_new_i32();
  TCGv temp_4 = tcg_temp_local_new_i32();
  TCGv tmp2 = tcg_temp_local_new_i32();
  TCGv temp_9 = tcg_temp_local_new_i32();
  TCGv temp_10 = NULL /* REFERENCE */;
  TCGv temp_5 = tcg_temp_local_new_i32();
  TCGv temp_6 = tcg_temp_local_new_i32();
  temp_7 = getCCFlag();
  tcg_gen_mov_i32(cc_flag, temp_7);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_i32(temp_2, temp_1, 1); tcg_gen_andi_i32(temp_2, temp_2, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, arc_true, done_1);;
  tcg_gen_andi_i32(temp_8, c, 31);
  tcg_gen_addi_i32(tmp1, temp_8, 1);
  TCGLabel *else_2 = gen_new_label();
  TCGLabel *done_2 = gen_new_label();
  tcg_gen_setcondi_i32(TCG_COND_EQ, temp_3, tmp1, 32);
  tcg_gen_xori_i32(temp_4, temp_3, 1); tcg_gen_andi_i32(temp_4, temp_4, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_4, arc_true, else_2);;
  tcg_gen_movi_i32(tmp2, 4294967295);
  tcg_gen_br(done_2);
  gen_set_label(else_2);
  tcg_gen_shlfi_i32(temp_9, 1, tmp1);
  tcg_gen_subi_i32(tmp2, temp_9, 1);
  gen_set_label(done_2);
  tcg_gen_and_i32(a, b, tmp2);
  TCGLabel *done_3 = gen_new_label();
  temp_10 = getFFlag();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_5, temp_10, arc_true);
  tcg_gen_xori_i32(temp_6, temp_5, 1); tcg_gen_andi_i32(temp_6, temp_6, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_6, arc_true, done_3);;
  setZFlag(a);
  setNFlag(a);
  gen_set_label(done_3);
  gen_set_label(done_1);
  if(temp_7 != NULL) tcg_temp_free(temp_7);
  tcg_temp_free(cc_flag);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  tcg_temp_free(temp_8);
  tcg_temp_free(tmp1);
  tcg_temp_free(temp_3);
  tcg_temp_free(temp_4);
  tcg_temp_free(tmp2);
  tcg_temp_free(temp_9);
  if(temp_10 != NULL) tcg_temp_free(temp_10);
  tcg_temp_free(temp_5);
  tcg_temp_free(temp_6);

  return ret;
}





/* BMSKN
 *    Variables: @c, @a, @b
 *    Functions: getCCFlag, getFFlag, setZFlag, setNFlag
--- code ---
{
  cc_flag = getCCFlag ();
  if((cc_flag == true))
    {
      tmp1 = ((@c & 31) + 1);
      if((tmp1 == 32))
        {
          tmp2 = 4294967295;
        }
      else
        {
          tmp2 = ((1 << tmp1) - 1);
        };
      @a = (@b & ~tmp2);
      if((getFFlag () == true))
        {
          setZFlag (@a);
          setNFlag (@a);
        };
    };
}
 */

int
arc2_gen_BMSKN (DisasCtxt *ctx, TCGv c, TCGv a, TCGv b)
{
  int ret = BS_NONE;
  TCGv temp_7 = NULL /* REFERENCE */;
  TCGv cc_flag = tcg_temp_local_new_i32();
  TCGv temp_1 = tcg_temp_local_new_i32();
  TCGv temp_2 = tcg_temp_local_new_i32();
  TCGv temp_8 = tcg_temp_local_new_i32();
  TCGv tmp1 = tcg_temp_local_new_i32();
  TCGv temp_3 = tcg_temp_local_new_i32();
  TCGv temp_4 = tcg_temp_local_new_i32();
  TCGv tmp2 = tcg_temp_local_new_i32();
  TCGv temp_9 = tcg_temp_local_new_i32();
  TCGv temp_10 = tcg_temp_local_new_i32();
  TCGv temp_11 = NULL /* REFERENCE */;
  TCGv temp_5 = tcg_temp_local_new_i32();
  TCGv temp_6 = tcg_temp_local_new_i32();
  temp_7 = getCCFlag();
  tcg_gen_mov_i32(cc_flag, temp_7);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_i32(temp_2, temp_1, 1); tcg_gen_andi_i32(temp_2, temp_2, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, arc_true, done_1);;
  tcg_gen_andi_i32(temp_8, c, 31);
  tcg_gen_addi_i32(tmp1, temp_8, 1);
  TCGLabel *else_2 = gen_new_label();
  TCGLabel *done_2 = gen_new_label();
  tcg_gen_setcondi_i32(TCG_COND_EQ, temp_3, tmp1, 32);
  tcg_gen_xori_i32(temp_4, temp_3, 1); tcg_gen_andi_i32(temp_4, temp_4, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_4, arc_true, else_2);;
  tcg_gen_movi_i32(tmp2, 4294967295);
  tcg_gen_br(done_2);
  gen_set_label(else_2);
  tcg_gen_shlfi_i32(temp_9, 1, tmp1);
  tcg_gen_subi_i32(tmp2, temp_9, 1);
  gen_set_label(done_2);
  tcg_gen_not_i32(temp_10, tmp2);
  tcg_gen_and_i32(a, b, temp_10);
  TCGLabel *done_3 = gen_new_label();
  temp_11 = getFFlag();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_5, temp_11, arc_true);
  tcg_gen_xori_i32(temp_6, temp_5, 1); tcg_gen_andi_i32(temp_6, temp_6, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_6, arc_true, done_3);;
  setZFlag(a);
  setNFlag(a);
  gen_set_label(done_3);
  gen_set_label(done_1);
  if(temp_7 != NULL) tcg_temp_free(temp_7);
  tcg_temp_free(cc_flag);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  tcg_temp_free(temp_8);
  tcg_temp_free(tmp1);
  tcg_temp_free(temp_3);
  tcg_temp_free(temp_4);
  tcg_temp_free(tmp2);
  tcg_temp_free(temp_9);
  tcg_temp_free(temp_10);
  if(temp_11 != NULL) tcg_temp_free(temp_11);
  tcg_temp_free(temp_5);
  tcg_temp_free(temp_6);

  return ret;
}





/* BSET
 *    Variables: @c, @a, @b
 *    Functions: getCCFlag, getFFlag, setZFlag, setNFlag
--- code ---
{
  cc_flag = getCCFlag ();
  if((cc_flag == true))
    {
      tmp = (1 << (@c & 31));
      @a = (@b | tmp);
      if((getFFlag () == true))
        {
          setZFlag (@a);
          setNFlag (@a);
        };
    };
}
 */

int
arc2_gen_BSET (DisasCtxt *ctx, TCGv c, TCGv a, TCGv b)
{
  int ret = BS_NONE;
  TCGv temp_5 = NULL /* REFERENCE */;
  TCGv cc_flag = tcg_temp_local_new_i32();
  TCGv temp_1 = tcg_temp_local_new_i32();
  TCGv temp_2 = tcg_temp_local_new_i32();
  TCGv temp_6 = tcg_temp_local_new_i32();
  TCGv tmp = tcg_temp_local_new_i32();
  TCGv temp_7 = NULL /* REFERENCE */;
  TCGv temp_3 = tcg_temp_local_new_i32();
  TCGv temp_4 = tcg_temp_local_new_i32();
  temp_5 = getCCFlag();
  tcg_gen_mov_i32(cc_flag, temp_5);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_i32(temp_2, temp_1, 1); tcg_gen_andi_i32(temp_2, temp_2, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, arc_true, done_1);;
  tcg_gen_andi_i32(temp_6, c, 31);
  tcg_gen_shlfi_i32(tmp, 1, temp_6);
  tcg_gen_or_i32(a, b, tmp);
  TCGLabel *done_2 = gen_new_label();
  temp_7 = getFFlag();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_3, temp_7, arc_true);
  tcg_gen_xori_i32(temp_4, temp_3, 1); tcg_gen_andi_i32(temp_4, temp_4, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_4, arc_true, done_2);;
  setZFlag(a);
  setNFlag(a);
  gen_set_label(done_2);
  gen_set_label(done_1);
  if(temp_5 != NULL) tcg_temp_free(temp_5);
  tcg_temp_free(cc_flag);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  tcg_temp_free(temp_6);
  tcg_temp_free(tmp);
  if(temp_7 != NULL) tcg_temp_free(temp_7);
  tcg_temp_free(temp_3);
  tcg_temp_free(temp_4);

  return ret;
}





/* BXOR
 *    Variables: @c, @a, @b
 *    Functions: getCCFlag, getFFlag, setZFlag, setNFlag
--- code ---
{
  cc_flag = getCCFlag ();
  if((cc_flag == true))
    {
      tmp = (1 << @c);
      @a = (@b ^ tmp);
      if((getFFlag () == true))
        {
          setZFlag (@a);
          setNFlag (@a);
        };
    };
}
 */

int
arc2_gen_BXOR (DisasCtxt *ctx, TCGv c, TCGv a, TCGv b)
{
  int ret = BS_NONE;
  TCGv temp_5 = NULL /* REFERENCE */;
  TCGv cc_flag = tcg_temp_local_new_i32();
  TCGv temp_1 = tcg_temp_local_new_i32();
  TCGv temp_2 = tcg_temp_local_new_i32();
  TCGv tmp = tcg_temp_local_new_i32();
  TCGv temp_6 = NULL /* REFERENCE */;
  TCGv temp_3 = tcg_temp_local_new_i32();
  TCGv temp_4 = tcg_temp_local_new_i32();
  temp_5 = getCCFlag();
  tcg_gen_mov_i32(cc_flag, temp_5);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_i32(temp_2, temp_1, 1); tcg_gen_andi_i32(temp_2, temp_2, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, arc_true, done_1);;
  tcg_gen_shlfi_i32(tmp, 1, c);
  tcg_gen_xor_i32(a, b, tmp);
  TCGLabel *done_2 = gen_new_label();
  temp_6 = getFFlag();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_3, temp_6, arc_true);
  tcg_gen_xori_i32(temp_4, temp_3, 1); tcg_gen_andi_i32(temp_4, temp_4, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_4, arc_true, done_2);;
  setZFlag(a);
  setNFlag(a);
  gen_set_label(done_2);
  gen_set_label(done_1);
  if(temp_5 != NULL) tcg_temp_free(temp_5);
  tcg_temp_free(cc_flag);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  tcg_temp_free(tmp);
  if(temp_6 != NULL) tcg_temp_free(temp_6);
  tcg_temp_free(temp_3);
  tcg_temp_free(temp_4);

  return ret;
}





/* ROL
 *    Variables: @src, @n, @dest
 *    Functions: getCCFlag, rotateLeft, getFFlag, setZFlag, setNFlag, setCFlag, extractBits
--- code ---
{
  cc_flag = getCCFlag ();
  if((cc_flag == true))
    {
      lsrc = @src;
      ln = (@n & 31);
      @dest = rotateLeft (lsrc, ln);
      if((getFFlag () == true))
        {
          setZFlag (@dest);
          setNFlag (@dest);
          setCFlag (extractBits (lsrc, (ln - 1), (ln - 1)));
        };
    };
}
 */

int
arc2_gen_ROL (DisasCtxt *ctx, TCGv src, TCGv n, TCGv dest)
{
  int ret = BS_NONE;
  TCGv temp_5 = NULL /* REFERENCE */;
  TCGv cc_flag = tcg_temp_local_new_i32();
  TCGv temp_1 = tcg_temp_local_new_i32();
  TCGv temp_2 = tcg_temp_local_new_i32();
  TCGv lsrc = tcg_temp_local_new_i32();
  TCGv ln = tcg_temp_local_new_i32();
  TCGv temp_6 = NULL /* REFERENCE */;
  TCGv temp_7 = NULL /* REFERENCE */;
  TCGv temp_3 = tcg_temp_local_new_i32();
  TCGv temp_4 = tcg_temp_local_new_i32();
  TCGv temp_11 = tcg_temp_local_new_i32();
  TCGv temp_10 = tcg_temp_local_new_i32();
  TCGv temp_9 = NULL /* REFERENCE */;
  TCGv temp_8 = tcg_temp_local_new_i32();
  temp_5 = getCCFlag();
  tcg_gen_mov_i32(cc_flag, temp_5);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_i32(temp_2, temp_1, 1); tcg_gen_andi_i32(temp_2, temp_2, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, arc_true, done_1);;
  tcg_gen_mov_i32(lsrc, src);
  tcg_gen_andi_i32(ln, n, 31);
  temp_6 = rotateLeft(lsrc, ln);
  tcg_gen_mov_i32(dest, temp_6);
  TCGLabel *done_2 = gen_new_label();
  temp_7 = getFFlag();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_3, temp_7, arc_true);
  tcg_gen_xori_i32(temp_4, temp_3, 1); tcg_gen_andi_i32(temp_4, temp_4, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_4, arc_true, done_2);;
  setZFlag(dest);
  setNFlag(dest);
  tcg_gen_subi_i32(temp_11, ln, 1);
  tcg_gen_subi_i32(temp_10, ln, 1);
  temp_9 = extractBits(lsrc, temp_10, temp_11);
  tcg_gen_mov_i32(temp_8, temp_9);
  setCFlag(temp_8);
  gen_set_label(done_2);
  gen_set_label(done_1);
  if(temp_5 != NULL) tcg_temp_free(temp_5);
  tcg_temp_free(cc_flag);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  tcg_temp_free(lsrc);
  tcg_temp_free(ln);
  if(temp_6 != NULL) tcg_temp_free(temp_6);
  if(temp_7 != NULL) tcg_temp_free(temp_7);
  tcg_temp_free(temp_3);
  tcg_temp_free(temp_4);
  tcg_temp_free(temp_11);
  tcg_temp_free(temp_10);
  if(temp_9 != NULL) tcg_temp_free(temp_9);
  tcg_temp_free(temp_8);

  return ret;
}





/* ROR
 *    Variables: @src, @n, @dest
 *    Functions: getCCFlag, rotateRight, getFFlag, setZFlag, setNFlag, setCFlag, extractBits
--- code ---
{
  cc_flag = getCCFlag ();
  if((cc_flag == true))
    {
      lsrc = @src;
      ln = (@n & 31);
      @dest = rotateRight (lsrc, ln);
      if((getFFlag () == true))
        {
          setZFlag (@dest);
          setNFlag (@dest);
          setCFlag (extractBits (lsrc, (ln - 1), (ln - 1)));
        };
    };
}
 */

int
arc2_gen_ROR (DisasCtxt *ctx, TCGv src, TCGv n, TCGv dest)
{
  int ret = BS_NONE;
  TCGv temp_5 = NULL /* REFERENCE */;
  TCGv cc_flag = tcg_temp_local_new_i32();
  TCGv temp_1 = tcg_temp_local_new_i32();
  TCGv temp_2 = tcg_temp_local_new_i32();
  TCGv lsrc = tcg_temp_local_new_i32();
  TCGv ln = tcg_temp_local_new_i32();
  TCGv temp_6 = NULL /* REFERENCE */;
  TCGv temp_7 = NULL /* REFERENCE */;
  TCGv temp_3 = tcg_temp_local_new_i32();
  TCGv temp_4 = tcg_temp_local_new_i32();
  TCGv temp_11 = tcg_temp_local_new_i32();
  TCGv temp_10 = tcg_temp_local_new_i32();
  TCGv temp_9 = NULL /* REFERENCE */;
  TCGv temp_8 = tcg_temp_local_new_i32();
  temp_5 = getCCFlag();
  tcg_gen_mov_i32(cc_flag, temp_5);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_i32(temp_2, temp_1, 1); tcg_gen_andi_i32(temp_2, temp_2, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, arc_true, done_1);;
  tcg_gen_mov_i32(lsrc, src);
  tcg_gen_andi_i32(ln, n, 31);
  temp_6 = rotateRight(lsrc, ln);
  tcg_gen_mov_i32(dest, temp_6);
  TCGLabel *done_2 = gen_new_label();
  temp_7 = getFFlag();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_3, temp_7, arc_true);
  tcg_gen_xori_i32(temp_4, temp_3, 1); tcg_gen_andi_i32(temp_4, temp_4, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_4, arc_true, done_2);;
  setZFlag(dest);
  setNFlag(dest);
  tcg_gen_subi_i32(temp_11, ln, 1);
  tcg_gen_subi_i32(temp_10, ln, 1);
  temp_9 = extractBits(lsrc, temp_10, temp_11);
  tcg_gen_mov_i32(temp_8, temp_9);
  setCFlag(temp_8);
  gen_set_label(done_2);
  gen_set_label(done_1);
  if(temp_5 != NULL) tcg_temp_free(temp_5);
  tcg_temp_free(cc_flag);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  tcg_temp_free(lsrc);
  tcg_temp_free(ln);
  if(temp_6 != NULL) tcg_temp_free(temp_6);
  if(temp_7 != NULL) tcg_temp_free(temp_7);
  tcg_temp_free(temp_3);
  tcg_temp_free(temp_4);
  tcg_temp_free(temp_11);
  tcg_temp_free(temp_10);
  if(temp_9 != NULL) tcg_temp_free(temp_9);
  tcg_temp_free(temp_8);

  return ret;
}





/* RLC
 *    Variables: @src, @dest
 *    Functions: getCCFlag, getCFlag, getFFlag, setZFlag, setNFlag, setCFlag, extractBits
--- code ---
{
  cc_flag = getCCFlag ();
  if((cc_flag == true))
    {
      lsrc = @src;
      @dest = (lsrc << 1);
      @dest = (@dest | getCFlag ());
      if((getFFlag () == true))
        {
          setZFlag (@dest);
          setNFlag (@dest);
          setCFlag (extractBits (lsrc, 31, 31));
        };
    };
}
 */

int
arc2_gen_RLC (DisasCtxt *ctx, TCGv src, TCGv dest)
{
  int ret = BS_NONE;
  TCGv temp_5 = NULL /* REFERENCE */;
  TCGv cc_flag = tcg_temp_local_new_i32();
  TCGv temp_1 = tcg_temp_local_new_i32();
  TCGv temp_2 = tcg_temp_local_new_i32();
  TCGv lsrc = tcg_temp_local_new_i32();
  TCGv temp_7 = NULL /* REFERENCE */;
  TCGv temp_6 = tcg_temp_local_new_i32();
  TCGv temp_8 = NULL /* REFERENCE */;
  TCGv temp_3 = tcg_temp_local_new_i32();
  TCGv temp_4 = tcg_temp_local_new_i32();
  TCGv temp_12 = tcg_temp_local_new_i32();
  TCGv temp_11 = tcg_temp_local_new_i32();
  TCGv temp_10 = NULL /* REFERENCE */;
  TCGv temp_9 = tcg_temp_local_new_i32();
  temp_5 = getCCFlag();
  tcg_gen_mov_i32(cc_flag, temp_5);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_i32(temp_2, temp_1, 1); tcg_gen_andi_i32(temp_2, temp_2, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, arc_true, done_1);;
  tcg_gen_mov_i32(lsrc, src);
  tcg_gen_shli_i32(dest, lsrc, 1);
  temp_7 = getCFlag();
  tcg_gen_mov_i32(temp_6, temp_7);
  tcg_gen_or_i32(dest, dest, temp_6);
  TCGLabel *done_2 = gen_new_label();
  temp_8 = getFFlag();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_3, temp_8, arc_true);
  tcg_gen_xori_i32(temp_4, temp_3, 1); tcg_gen_andi_i32(temp_4, temp_4, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_4, arc_true, done_2);;
  setZFlag(dest);
  setNFlag(dest);
  tcg_gen_movi_i32(temp_12, 31);
  tcg_gen_movi_i32(temp_11, 31);
  temp_10 = extractBits(lsrc, temp_11, temp_12);
  tcg_gen_mov_i32(temp_9, temp_10);
  setCFlag(temp_9);
  gen_set_label(done_2);
  gen_set_label(done_1);
  if(temp_5 != NULL) tcg_temp_free(temp_5);
  tcg_temp_free(cc_flag);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  tcg_temp_free(lsrc);
  if(temp_7 != NULL) tcg_temp_free(temp_7);
  tcg_temp_free(temp_6);
  if(temp_8 != NULL) tcg_temp_free(temp_8);
  tcg_temp_free(temp_3);
  tcg_temp_free(temp_4);
  tcg_temp_free(temp_12);
  tcg_temp_free(temp_11);
  if(temp_10 != NULL) tcg_temp_free(temp_10);
  tcg_temp_free(temp_9);

  return ret;
}





/* RRC
 *    Variables: @src, @dest
 *    Functions: getCCFlag, getCFlag, getFFlag, setZFlag, setNFlag, setCFlag, extractBits
--- code ---
{
  cc_flag = getCCFlag ();
  if((cc_flag == true))
    {
      lsrc = @src;
      @dest = (lsrc >> 1);
      @dest = (@dest | (getCFlag () << 31));
      if((getFFlag () == true))
        {
          setZFlag (@dest);
          setNFlag (@dest);
          setCFlag (extractBits (lsrc, 0, 0));
        };
    };
}
 */

int
arc2_gen_RRC (DisasCtxt *ctx, TCGv src, TCGv dest)
{
  int ret = BS_NONE;
  TCGv temp_5 = NULL /* REFERENCE */;
  TCGv cc_flag = tcg_temp_local_new_i32();
  TCGv temp_1 = tcg_temp_local_new_i32();
  TCGv temp_2 = tcg_temp_local_new_i32();
  TCGv lsrc = tcg_temp_local_new_i32();
  TCGv temp_8 = NULL /* REFERENCE */;
  TCGv temp_7 = tcg_temp_local_new_i32();
  TCGv temp_6 = tcg_temp_local_new_i32();
  TCGv temp_9 = NULL /* REFERENCE */;
  TCGv temp_3 = tcg_temp_local_new_i32();
  TCGv temp_4 = tcg_temp_local_new_i32();
  TCGv temp_13 = tcg_temp_local_new_i32();
  TCGv temp_12 = tcg_temp_local_new_i32();
  TCGv temp_11 = NULL /* REFERENCE */;
  TCGv temp_10 = tcg_temp_local_new_i32();
  temp_5 = getCCFlag();
  tcg_gen_mov_i32(cc_flag, temp_5);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_i32(temp_2, temp_1, 1); tcg_gen_andi_i32(temp_2, temp_2, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, arc_true, done_1);;
  tcg_gen_mov_i32(lsrc, src);
  tcg_gen_shri_i32(dest, lsrc, 1);
  temp_8 = getCFlag();
  tcg_gen_mov_i32(temp_7, temp_8);
  tcg_gen_shli_i32(temp_6, temp_7, 31);
  tcg_gen_or_i32(dest, dest, temp_6);
  TCGLabel *done_2 = gen_new_label();
  temp_9 = getFFlag();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_3, temp_9, arc_true);
  tcg_gen_xori_i32(temp_4, temp_3, 1); tcg_gen_andi_i32(temp_4, temp_4, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_4, arc_true, done_2);;
  setZFlag(dest);
  setNFlag(dest);
  tcg_gen_movi_i32(temp_13, 0);
  tcg_gen_movi_i32(temp_12, 0);
  temp_11 = extractBits(lsrc, temp_12, temp_13);
  tcg_gen_mov_i32(temp_10, temp_11);
  setCFlag(temp_10);
  gen_set_label(done_2);
  gen_set_label(done_1);
  if(temp_5 != NULL) tcg_temp_free(temp_5);
  tcg_temp_free(cc_flag);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  tcg_temp_free(lsrc);
  if(temp_8 != NULL) tcg_temp_free(temp_8);
  tcg_temp_free(temp_7);
  tcg_temp_free(temp_6);
  if(temp_9 != NULL) tcg_temp_free(temp_9);
  tcg_temp_free(temp_3);
  tcg_temp_free(temp_4);
  tcg_temp_free(temp_13);
  tcg_temp_free(temp_12);
  if(temp_11 != NULL) tcg_temp_free(temp_11);
  tcg_temp_free(temp_10);

  return ret;
}





/* SEXB
 *    Variables: @dest, @src
 *    Functions: getCCFlag, arithmeticShiftRight, getFFlag, setZFlag, setNFlag
--- code ---
{
  cc_flag = getCCFlag ();
  if((cc_flag == true))
    {
      @dest = arithmeticShiftRight ((@src << 24), 24);
      if((getFFlag () == true))
        {
          setZFlag (@dest);
          setNFlag (@dest);
        };
    };
}
 */

int
arc2_gen_SEXB (DisasCtxt *ctx, TCGv dest, TCGv src)
{
  int ret = BS_NONE;
  TCGv temp_5 = NULL /* REFERENCE */;
  TCGv cc_flag = tcg_temp_local_new_i32();
  TCGv temp_1 = tcg_temp_local_new_i32();
  TCGv temp_2 = tcg_temp_local_new_i32();
  TCGv temp_8 = tcg_temp_local_new_i32();
  TCGv temp_7 = tcg_temp_local_new_i32();
  TCGv temp_6 = NULL /* REFERENCE */;
  TCGv temp_9 = NULL /* REFERENCE */;
  TCGv temp_3 = tcg_temp_local_new_i32();
  TCGv temp_4 = tcg_temp_local_new_i32();
  temp_5 = getCCFlag();
  tcg_gen_mov_i32(cc_flag, temp_5);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_i32(temp_2, temp_1, 1); tcg_gen_andi_i32(temp_2, temp_2, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, arc_true, done_1);;
  tcg_gen_movi_i32(temp_8, 24);
  tcg_gen_shli_i32(temp_7, src, 24);
  temp_6 = arithmeticShiftRight(temp_7, temp_8);
  tcg_gen_mov_i32(dest, temp_6);
  TCGLabel *done_2 = gen_new_label();
  temp_9 = getFFlag();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_3, temp_9, arc_true);
  tcg_gen_xori_i32(temp_4, temp_3, 1); tcg_gen_andi_i32(temp_4, temp_4, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_4, arc_true, done_2);;
  setZFlag(dest);
  setNFlag(dest);
  gen_set_label(done_2);
  gen_set_label(done_1);
  if(temp_5 != NULL) tcg_temp_free(temp_5);
  tcg_temp_free(cc_flag);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  tcg_temp_free(temp_8);
  tcg_temp_free(temp_7);
  if(temp_6 != NULL) tcg_temp_free(temp_6);
  if(temp_9 != NULL) tcg_temp_free(temp_9);
  tcg_temp_free(temp_3);
  tcg_temp_free(temp_4);

  return ret;
}





/* SEXH
 *    Variables: @dest, @src
 *    Functions: getCCFlag, arithmeticShiftRight, getFFlag, setZFlag, setNFlag
--- code ---
{
  cc_flag = getCCFlag ();
  if((cc_flag == true))
    {
      @dest = arithmeticShiftRight ((@src << 16), 16);
      if((getFFlag () == true))
        {
          setZFlag (@dest);
          setNFlag (@dest);
        };
    };
}
 */

int
arc2_gen_SEXH (DisasCtxt *ctx, TCGv dest, TCGv src)
{
  int ret = BS_NONE;
  TCGv temp_5 = NULL /* REFERENCE */;
  TCGv cc_flag = tcg_temp_local_new_i32();
  TCGv temp_1 = tcg_temp_local_new_i32();
  TCGv temp_2 = tcg_temp_local_new_i32();
  TCGv temp_8 = tcg_temp_local_new_i32();
  TCGv temp_7 = tcg_temp_local_new_i32();
  TCGv temp_6 = NULL /* REFERENCE */;
  TCGv temp_9 = NULL /* REFERENCE */;
  TCGv temp_3 = tcg_temp_local_new_i32();
  TCGv temp_4 = tcg_temp_local_new_i32();
  temp_5 = getCCFlag();
  tcg_gen_mov_i32(cc_flag, temp_5);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_i32(temp_2, temp_1, 1); tcg_gen_andi_i32(temp_2, temp_2, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, arc_true, done_1);;
  tcg_gen_movi_i32(temp_8, 16);
  tcg_gen_shli_i32(temp_7, src, 16);
  temp_6 = arithmeticShiftRight(temp_7, temp_8);
  tcg_gen_mov_i32(dest, temp_6);
  TCGLabel *done_2 = gen_new_label();
  temp_9 = getFFlag();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_3, temp_9, arc_true);
  tcg_gen_xori_i32(temp_4, temp_3, 1); tcg_gen_andi_i32(temp_4, temp_4, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_4, arc_true, done_2);;
  setZFlag(dest);
  setNFlag(dest);
  gen_set_label(done_2);
  gen_set_label(done_1);
  if(temp_5 != NULL) tcg_temp_free(temp_5);
  tcg_temp_free(cc_flag);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  tcg_temp_free(temp_8);
  tcg_temp_free(temp_7);
  if(temp_6 != NULL) tcg_temp_free(temp_6);
  if(temp_9 != NULL) tcg_temp_free(temp_9);
  tcg_temp_free(temp_3);
  tcg_temp_free(temp_4);

  return ret;
}





/* EXTB
 *    Variables: @dest, @src
 *    Functions: getCCFlag, getFFlag, setZFlag, setNFlag
--- code ---
{
  cc_flag = getCCFlag ();
  if((cc_flag == true))
    {
      @dest = (@src & 255);
      if((getFFlag () == true))
        {
          setZFlag (@dest);
          setNFlag (@dest);
        };
    };
}
 */

int
arc2_gen_EXTB (DisasCtxt *ctx, TCGv dest, TCGv src)
{
  int ret = BS_NONE;
  TCGv temp_5 = NULL /* REFERENCE */;
  TCGv cc_flag = tcg_temp_local_new_i32();
  TCGv temp_1 = tcg_temp_local_new_i32();
  TCGv temp_2 = tcg_temp_local_new_i32();
  TCGv temp_6 = NULL /* REFERENCE */;
  TCGv temp_3 = tcg_temp_local_new_i32();
  TCGv temp_4 = tcg_temp_local_new_i32();
  temp_5 = getCCFlag();
  tcg_gen_mov_i32(cc_flag, temp_5);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_i32(temp_2, temp_1, 1); tcg_gen_andi_i32(temp_2, temp_2, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, arc_true, done_1);;
  tcg_gen_andi_i32(dest, src, 255);
  TCGLabel *done_2 = gen_new_label();
  temp_6 = getFFlag();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_3, temp_6, arc_true);
  tcg_gen_xori_i32(temp_4, temp_3, 1); tcg_gen_andi_i32(temp_4, temp_4, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_4, arc_true, done_2);;
  setZFlag(dest);
  setNFlag(dest);
  gen_set_label(done_2);
  gen_set_label(done_1);
  if(temp_5 != NULL) tcg_temp_free(temp_5);
  tcg_temp_free(cc_flag);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  if(temp_6 != NULL) tcg_temp_free(temp_6);
  tcg_temp_free(temp_3);
  tcg_temp_free(temp_4);

  return ret;
}





/* EXTH
 *    Variables: @dest, @src
 *    Functions: getCCFlag, getFFlag, setZFlag, setNFlag
--- code ---
{
  cc_flag = getCCFlag ();
  if((cc_flag == true))
    {
      @dest = (@src & 65535);
      if((getFFlag () == true))
        {
          setZFlag (@dest);
          setNFlag (@dest);
        };
    };
}
 */

int
arc2_gen_EXTH (DisasCtxt *ctx, TCGv dest, TCGv src)
{
  int ret = BS_NONE;
  TCGv temp_5 = NULL /* REFERENCE */;
  TCGv cc_flag = tcg_temp_local_new_i32();
  TCGv temp_1 = tcg_temp_local_new_i32();
  TCGv temp_2 = tcg_temp_local_new_i32();
  TCGv temp_6 = NULL /* REFERENCE */;
  TCGv temp_3 = tcg_temp_local_new_i32();
  TCGv temp_4 = tcg_temp_local_new_i32();
  temp_5 = getCCFlag();
  tcg_gen_mov_i32(cc_flag, temp_5);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_i32(temp_2, temp_1, 1); tcg_gen_andi_i32(temp_2, temp_2, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, arc_true, done_1);;
  tcg_gen_andi_i32(dest, src, 65535);
  TCGLabel *done_2 = gen_new_label();
  temp_6 = getFFlag();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_3, temp_6, arc_true);
  tcg_gen_xori_i32(temp_4, temp_3, 1); tcg_gen_andi_i32(temp_4, temp_4, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_4, arc_true, done_2);;
  setZFlag(dest);
  setNFlag(dest);
  gen_set_label(done_2);
  gen_set_label(done_1);
  if(temp_5 != NULL) tcg_temp_free(temp_5);
  tcg_temp_free(cc_flag);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  if(temp_6 != NULL) tcg_temp_free(temp_6);
  tcg_temp_free(temp_3);
  tcg_temp_free(temp_4);

  return ret;
}





/* BTST
 *    Variables: @c, @b
 *    Functions: getCCFlag, setZFlag, setNFlag
--- code ---
{
  cc_flag = getCCFlag ();
  if((cc_flag == true))
    {
      tmp = (1 << (@c & 31));
      alu = (@b & tmp);
      setZFlag (alu);
      setNFlag (alu);
    };
}
 */

int
arc2_gen_BTST (DisasCtxt *ctx, TCGv c, TCGv b)
{
  int ret = BS_NONE;
  TCGv temp_3 = NULL /* REFERENCE */;
  TCGv cc_flag = tcg_temp_local_new_i32();
  TCGv temp_1 = tcg_temp_local_new_i32();
  TCGv temp_2 = tcg_temp_local_new_i32();
  TCGv temp_4 = tcg_temp_local_new_i32();
  TCGv tmp = tcg_temp_local_new_i32();
  TCGv alu = tcg_temp_local_new_i32();
  temp_3 = getCCFlag();
  tcg_gen_mov_i32(cc_flag, temp_3);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_i32(temp_2, temp_1, 1); tcg_gen_andi_i32(temp_2, temp_2, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, arc_true, done_1);;
  tcg_gen_andi_i32(temp_4, c, 31);
  tcg_gen_shlfi_i32(tmp, 1, temp_4);
  tcg_gen_and_i32(alu, b, tmp);
  setZFlag(alu);
  setNFlag(alu);
  gen_set_label(done_1);
  if(temp_3 != NULL) tcg_temp_free(temp_3);
  tcg_temp_free(cc_flag);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  tcg_temp_free(temp_4);
  tcg_temp_free(tmp);
  tcg_temp_free(alu);

  return ret;
}





/* TST
 *    Variables: @b, @c
 *    Functions: getCCFlag, setZFlag, setNFlag
--- code ---
{
  cc_flag = getCCFlag ();
  if((cc_flag == true))
    {
      alu = (@b & @c);
      setZFlag (alu);
      setNFlag (alu);
    };
}
 */

int
arc2_gen_TST (DisasCtxt *ctx, TCGv b, TCGv c)
{
  int ret = BS_NONE;
  TCGv temp_3 = NULL /* REFERENCE */;
  TCGv cc_flag = tcg_temp_local_new_i32();
  TCGv temp_1 = tcg_temp_local_new_i32();
  TCGv temp_2 = tcg_temp_local_new_i32();
  TCGv alu = tcg_temp_local_new_i32();
  temp_3 = getCCFlag();
  tcg_gen_mov_i32(cc_flag, temp_3);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_i32(temp_2, temp_1, 1); tcg_gen_andi_i32(temp_2, temp_2, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, arc_true, done_1);;
  tcg_gen_and_i32(alu, b, c);
  setZFlag(alu);
  setNFlag(alu);
  gen_set_label(done_1);
  if(temp_3 != NULL) tcg_temp_free(temp_3);
  tcg_temp_free(cc_flag);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  tcg_temp_free(alu);

  return ret;
}





/* XBFU
 *    Variables: @src2, @src1, @dest
 *    Functions: getCCFlag, extractBits, getFFlag, setZFlag
--- code ---
{
  cc_flag = getCCFlag ();
  if((cc_flag == true))
    {
      N = extractBits (@src2, 4, 0);
      M = (extractBits (@src2, 9, 5) + 1);
      tmp1 = (@src1 >> N);
      tmp2 = ((1 << M) - 1);
      @dest = (tmp1 & tmp2);
      if((getFFlag () == true))
        {
          setZFlag (@dest);
        };
    };
}
 */

int
arc2_gen_XBFU (DisasCtxt *ctx, TCGv src2, TCGv src1, TCGv dest)
{
  int ret = BS_NONE;
  TCGv temp_5 = NULL /* REFERENCE */;
  TCGv cc_flag = tcg_temp_local_new_i32();
  TCGv temp_1 = tcg_temp_local_new_i32();
  TCGv temp_2 = tcg_temp_local_new_i32();
  TCGv temp_8 = tcg_temp_local_new_i32();
  TCGv temp_7 = tcg_temp_local_new_i32();
  TCGv temp_6 = NULL /* REFERENCE */;
  TCGv N = tcg_temp_local_new_i32();
  TCGv temp_12 = tcg_temp_local_new_i32();
  TCGv temp_11 = tcg_temp_local_new_i32();
  TCGv temp_10 = NULL /* REFERENCE */;
  TCGv temp_9 = tcg_temp_local_new_i32();
  TCGv M = tcg_temp_local_new_i32();
  TCGv tmp1 = tcg_temp_local_new_i32();
  TCGv temp_13 = tcg_temp_local_new_i32();
  TCGv tmp2 = tcg_temp_local_new_i32();
  TCGv temp_14 = NULL /* REFERENCE */;
  TCGv temp_3 = tcg_temp_local_new_i32();
  TCGv temp_4 = tcg_temp_local_new_i32();
  temp_5 = getCCFlag();
  tcg_gen_mov_i32(cc_flag, temp_5);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_i32(temp_2, temp_1, 1); tcg_gen_andi_i32(temp_2, temp_2, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, arc_true, done_1);;
  tcg_gen_movi_i32(temp_8, 0);
  tcg_gen_movi_i32(temp_7, 4);
  temp_6 = extractBits(src2, temp_7, temp_8);
  tcg_gen_mov_i32(N, temp_6);
  tcg_gen_movi_i32(temp_12, 5);
  tcg_gen_movi_i32(temp_11, 9);
  temp_10 = extractBits(src2, temp_11, temp_12);
  tcg_gen_mov_i32(temp_9, temp_10);
  tcg_gen_addi_i32(M, temp_9, 1);
  tcg_gen_shr_i32(tmp1, src1, N);
  tcg_gen_shlfi_i32(temp_13, 1, M);
  tcg_gen_subi_i32(tmp2, temp_13, 1);
  tcg_gen_and_i32(dest, tmp1, tmp2);
  TCGLabel *done_2 = gen_new_label();
  temp_14 = getFFlag();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_3, temp_14, arc_true);
  tcg_gen_xori_i32(temp_4, temp_3, 1); tcg_gen_andi_i32(temp_4, temp_4, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_4, arc_true, done_2);;
  setZFlag(dest);
  gen_set_label(done_2);
  gen_set_label(done_1);
  if(temp_5 != NULL) tcg_temp_free(temp_5);
  tcg_temp_free(cc_flag);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  tcg_temp_free(temp_8);
  tcg_temp_free(temp_7);
  if(temp_6 != NULL) tcg_temp_free(temp_6);
  tcg_temp_free(N);
  tcg_temp_free(temp_12);
  tcg_temp_free(temp_11);
  if(temp_10 != NULL) tcg_temp_free(temp_10);
  tcg_temp_free(temp_9);
  tcg_temp_free(M);
  tcg_temp_free(tmp1);
  tcg_temp_free(temp_13);
  tcg_temp_free(tmp2);
  if(temp_14 != NULL) tcg_temp_free(temp_14);
  tcg_temp_free(temp_3);
  tcg_temp_free(temp_4);

  return ret;
}





/* AEX
 *    Variables: @src2, @b
 *    Functions: getCCFlag, readAuxReg, writeAuxReg
--- code ---
{
  cc_flag = getCCFlag ();
  if((cc_flag == true))
    {
      tmp = readAuxReg (@src2);
      writeAuxReg (@src2, @b);
      @b = tmp;
    };
}
 */

int
arc2_gen_AEX (DisasCtxt *ctx, TCGv src2, TCGv b)
{
  int ret = BS_NONE;
  TCGv temp_3 = NULL /* REFERENCE */;
  TCGv cc_flag = tcg_temp_local_new_i32();
  TCGv temp_1 = tcg_temp_local_new_i32();
  TCGv temp_2 = tcg_temp_local_new_i32();
  TCGv temp_4 = NULL /* REFERENCE */;
  TCGv tmp = tcg_temp_local_new_i32();
  temp_3 = getCCFlag();
  tcg_gen_mov_i32(cc_flag, temp_3);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_i32(temp_2, temp_1, 1); tcg_gen_andi_i32(temp_2, temp_2, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, arc_true, done_1);;
  temp_4 = readAuxReg(src2);
  tcg_gen_mov_i32(tmp, temp_4);
  writeAuxReg(src2, b);
  tcg_gen_mov_i32(b, tmp);
  gen_set_label(done_1);
  if(temp_3 != NULL) tcg_temp_free(temp_3);
  tcg_temp_free(cc_flag);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  if(temp_4 != NULL) tcg_temp_free(temp_4);
  tcg_temp_free(tmp);

  return ret;
}





/* LR
 *    Variables: @dest, @src
 *    Functions: readAuxReg
--- code ---
{
  @dest = readAuxReg (@src);
}
 */

int
arc2_gen_LR (DisasCtxt *ctx, TCGv dest, TCGv src)
{
  int ret = BS_NONE;
  TCGv temp_1 = NULL /* REFERENCE */;
  temp_1 = readAuxReg(src);
  tcg_gen_mov_i32(dest, temp_1);
  if(temp_1 != NULL) tcg_temp_free(temp_1);

  return ret;
}





/* SR
 *    Variables: @src2, @src1
 *    Functions: writeAuxReg
--- code ---
{
  writeAuxReg (@src2, @src1);
}
 */

int
arc2_gen_SR (DisasCtxt *ctx, TCGv src2, TCGv src1)
{
  int ret = BS_NONE;

  writeAuxReg(src2, src1);
  return ret;
}





/* MPY
 *    Variables: @b, @c, @a
 *    Functions: getCCFlag, getFFlag, HELPER, setZFlag, setNFlag, setVFlag
--- code ---
{
  cc_flag = getCCFlag ();
  if((cc_flag == true))
    {
      _b = @b;
      _c = @c;
      @a = ((_b * _c) & 4294967295);
      if((getFFlag () == true))
        {
          high_part = HELPER (mpym, _b, _c);
          tmp1 = (high_part & 2147483648);
          tmp2 = (@a & 2147483648);
          setZFlag (@a);
          setNFlag (high_part);
          setVFlag ((tmp1 != tmp2));
        };
    };
}
 */

int
arc2_gen_MPY (DisasCtxt *ctx, TCGv b, TCGv c, TCGv a)
{
  int ret = BS_NONE;
  TCGv temp_5 = NULL /* REFERENCE */;
  TCGv cc_flag = tcg_temp_local_new_i32();
  TCGv temp_1 = tcg_temp_local_new_i32();
  TCGv temp_2 = tcg_temp_local_new_i32();
  TCGv _b = tcg_temp_local_new_i32();
  TCGv _c = tcg_temp_local_new_i32();
  TCGv temp_6 = tcg_temp_local_new_i32();
  TCGv temp_7 = NULL /* REFERENCE */;
  TCGv temp_3 = tcg_temp_local_new_i32();
  TCGv temp_4 = tcg_temp_local_new_i32();
  TCGv high_part = tcg_temp_local_new_i32();
  TCGv tmp1 = tcg_temp_local_new_i32();
  TCGv tmp2 = tcg_temp_local_new_i32();
  TCGv temp_8 = tcg_temp_local_new_i32();
  temp_5 = getCCFlag();
  tcg_gen_mov_i32(cc_flag, temp_5);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_i32(temp_2, temp_1, 1); tcg_gen_andi_i32(temp_2, temp_2, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, arc_true, done_1);;
  tcg_gen_mov_i32(_b, b);
  tcg_gen_mov_i32(_c, c);
  tcg_gen_mul_i32(temp_6, _b, _c);
  tcg_gen_andi_i32(a, temp_6, 4294967295);
  TCGLabel *done_2 = gen_new_label();
  temp_7 = getFFlag();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_3, temp_7, arc_true);
  tcg_gen_xori_i32(temp_4, temp_3, 1); tcg_gen_andi_i32(temp_4, temp_4, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_4, arc_true, done_2);;
  ARC_HELPER(mpym, high_part, _b, _c);
  tcg_gen_andi_i32(tmp1, high_part, 2147483648);
  tcg_gen_andi_i32(tmp2, a, 2147483648);
  setZFlag(a);
  setNFlag(high_part);
  tcg_gen_setcond_i32(TCG_COND_NE, temp_8, tmp1, tmp2);
  setVFlag(temp_8);
  gen_set_label(done_2);
  gen_set_label(done_1);
  if(temp_5 != NULL) tcg_temp_free(temp_5);
  tcg_temp_free(cc_flag);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  tcg_temp_free(_b);
  tcg_temp_free(_c);
  tcg_temp_free(temp_6);
  if(temp_7 != NULL) tcg_temp_free(temp_7);
  tcg_temp_free(temp_3);
  tcg_temp_free(temp_4);
  tcg_temp_free(high_part);
  tcg_temp_free(tmp1);
  tcg_temp_free(tmp2);
  tcg_temp_free(temp_8);

  return ret;
}





/* MPYMU
 *    Variables: @a, @b, @c
 *    Functions: getCCFlag, HELPER, getFFlag, setZFlag, setNFlag, setVFlag
--- code ---
{
  cc_flag = getCCFlag ();
  if((cc_flag == true))
    {
      @a = HELPER (mpymu, @b, @c);
      if((getFFlag () == true))
        {
          setZFlag (@a);
          setNFlag (0);
          setVFlag (0);
        };
    };
}
 */

int
arc2_gen_MPYMU (DisasCtxt *ctx, TCGv a, TCGv b, TCGv c)
{
  int ret = BS_NONE;
  TCGv temp_5 = NULL /* REFERENCE */;
  TCGv cc_flag = tcg_temp_local_new_i32();
  TCGv temp_1 = tcg_temp_local_new_i32();
  TCGv temp_2 = tcg_temp_local_new_i32();
  TCGv temp_6 = NULL /* REFERENCE */;
  TCGv temp_3 = tcg_temp_local_new_i32();
  TCGv temp_4 = tcg_temp_local_new_i32();
  TCGv temp_7 = tcg_temp_local_new_i32();
  TCGv temp_8 = tcg_temp_local_new_i32();
  temp_5 = getCCFlag();
  tcg_gen_mov_i32(cc_flag, temp_5);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_i32(temp_2, temp_1, 1); tcg_gen_andi_i32(temp_2, temp_2, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, arc_true, done_1);;
  ARC_HELPER(mpymu, a, b, c);
  TCGLabel *done_2 = gen_new_label();
  temp_6 = getFFlag();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_3, temp_6, arc_true);
  tcg_gen_xori_i32(temp_4, temp_3, 1); tcg_gen_andi_i32(temp_4, temp_4, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_4, arc_true, done_2);;
  setZFlag(a);
  tcg_gen_movi_i32(temp_7, 0);
  setNFlag(temp_7);
  tcg_gen_movi_i32(temp_8, 0);
  setVFlag(temp_8);
  gen_set_label(done_2);
  gen_set_label(done_1);
  if(temp_5 != NULL) tcg_temp_free(temp_5);
  tcg_temp_free(cc_flag);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  if(temp_6 != NULL) tcg_temp_free(temp_6);
  tcg_temp_free(temp_3);
  tcg_temp_free(temp_4);
  tcg_temp_free(temp_7);
  tcg_temp_free(temp_8);

  return ret;
}





/* MPYM
 *    Variables: @a, @b, @c
 *    Functions: getCCFlag, HELPER, getFFlag, setZFlag, setNFlag, setVFlag
--- code ---
{
  cc_flag = getCCFlag ();
  if((cc_flag == true))
    {
      @a = HELPER (mpym, @b, @c);
      if((getFFlag () == true))
        {
          setZFlag (@a);
          setNFlag (@a);
          setVFlag (0);
        };
    };
}
 */

int
arc2_gen_MPYM (DisasCtxt *ctx, TCGv a, TCGv b, TCGv c)
{
  int ret = BS_NONE;
  TCGv temp_5 = NULL /* REFERENCE */;
  TCGv cc_flag = tcg_temp_local_new_i32();
  TCGv temp_1 = tcg_temp_local_new_i32();
  TCGv temp_2 = tcg_temp_local_new_i32();
  TCGv temp_6 = NULL /* REFERENCE */;
  TCGv temp_3 = tcg_temp_local_new_i32();
  TCGv temp_4 = tcg_temp_local_new_i32();
  TCGv temp_7 = tcg_temp_local_new_i32();
  temp_5 = getCCFlag();
  tcg_gen_mov_i32(cc_flag, temp_5);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_i32(temp_2, temp_1, 1); tcg_gen_andi_i32(temp_2, temp_2, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, arc_true, done_1);;
  ARC_HELPER(mpym, a, b, c);
  TCGLabel *done_2 = gen_new_label();
  temp_6 = getFFlag();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_3, temp_6, arc_true);
  tcg_gen_xori_i32(temp_4, temp_3, 1); tcg_gen_andi_i32(temp_4, temp_4, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_4, arc_true, done_2);;
  setZFlag(a);
  setNFlag(a);
  tcg_gen_movi_i32(temp_7, 0);
  setVFlag(temp_7);
  gen_set_label(done_2);
  gen_set_label(done_1);
  if(temp_5 != NULL) tcg_temp_free(temp_5);
  tcg_temp_free(cc_flag);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  if(temp_6 != NULL) tcg_temp_free(temp_6);
  tcg_temp_free(temp_3);
  tcg_temp_free(temp_4);
  tcg_temp_free(temp_7);

  return ret;
}





/* MPYU
 *    Variables: @b, @c, @a
 *    Functions: getCCFlag, getFFlag, HELPER, setZFlag, setNFlag, setVFlag
--- code ---
{
  cc_flag = getCCFlag ();
  if((cc_flag == true))
    {
      _b = @b;
      _c = @c;
      @a = ((_b * _c) & 4294967295);
      if((getFFlag () == true))
        {
          high_part = HELPER (mpym, _b, _c);
          setZFlag (@a);
          setNFlag (0);
          setVFlag ((high_part > 0));
        };
    };
}
 */

int
arc2_gen_MPYU (DisasCtxt *ctx, TCGv b, TCGv c, TCGv a)
{
  int ret = BS_NONE;
  TCGv temp_5 = NULL /* REFERENCE */;
  TCGv cc_flag = tcg_temp_local_new_i32();
  TCGv temp_1 = tcg_temp_local_new_i32();
  TCGv temp_2 = tcg_temp_local_new_i32();
  TCGv _b = tcg_temp_local_new_i32();
  TCGv _c = tcg_temp_local_new_i32();
  TCGv temp_6 = tcg_temp_local_new_i32();
  TCGv temp_7 = NULL /* REFERENCE */;
  TCGv temp_3 = tcg_temp_local_new_i32();
  TCGv temp_4 = tcg_temp_local_new_i32();
  TCGv high_part = tcg_temp_local_new_i32();
  TCGv temp_8 = tcg_temp_local_new_i32();
  TCGv temp_9 = tcg_temp_local_new_i32();
  temp_5 = getCCFlag();
  tcg_gen_mov_i32(cc_flag, temp_5);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_i32(temp_2, temp_1, 1); tcg_gen_andi_i32(temp_2, temp_2, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, arc_true, done_1);;
  tcg_gen_mov_i32(_b, b);
  tcg_gen_mov_i32(_c, c);
  tcg_gen_mul_i32(temp_6, _b, _c);
  tcg_gen_andi_i32(a, temp_6, 4294967295);
  TCGLabel *done_2 = gen_new_label();
  temp_7 = getFFlag();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_3, temp_7, arc_true);
  tcg_gen_xori_i32(temp_4, temp_3, 1); tcg_gen_andi_i32(temp_4, temp_4, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_4, arc_true, done_2);;
  ARC_HELPER(mpym, high_part, _b, _c);
  setZFlag(a);
  tcg_gen_movi_i32(temp_8, 0);
  setNFlag(temp_8);
  tcg_gen_setcondi_i32(TCG_COND_GT, temp_9, high_part, 0);
  setVFlag(temp_9);
  gen_set_label(done_2);
  gen_set_label(done_1);
  if(temp_5 != NULL) tcg_temp_free(temp_5);
  tcg_temp_free(cc_flag);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  tcg_temp_free(_b);
  tcg_temp_free(_c);
  tcg_temp_free(temp_6);
  if(temp_7 != NULL) tcg_temp_free(temp_7);
  tcg_temp_free(temp_3);
  tcg_temp_free(temp_4);
  tcg_temp_free(high_part);
  tcg_temp_free(temp_8);
  tcg_temp_free(temp_9);

  return ret;
}





/* MPYUW
 *    Variables: @a, @b, @c
 *    Functions: getCCFlag, getFFlag, setZFlag, setNFlag, setVFlag
--- code ---
{
  cc_flag = getCCFlag ();
  if((cc_flag == true))
    {
      @a = ((@b & 65535) * (@c & 65535));
      if((getFFlag () == true))
        {
          setZFlag (@a);
          setNFlag (0);
          setVFlag (0);
        };
    };
}
 */

int
arc2_gen_MPYUW (DisasCtxt *ctx, TCGv a, TCGv b, TCGv c)
{
  int ret = BS_NONE;
  TCGv temp_5 = NULL /* REFERENCE */;
  TCGv cc_flag = tcg_temp_local_new_i32();
  TCGv temp_1 = tcg_temp_local_new_i32();
  TCGv temp_2 = tcg_temp_local_new_i32();
  TCGv temp_7 = tcg_temp_local_new_i32();
  TCGv temp_6 = tcg_temp_local_new_i32();
  TCGv temp_8 = NULL /* REFERENCE */;
  TCGv temp_3 = tcg_temp_local_new_i32();
  TCGv temp_4 = tcg_temp_local_new_i32();
  TCGv temp_9 = tcg_temp_local_new_i32();
  TCGv temp_10 = tcg_temp_local_new_i32();
  temp_5 = getCCFlag();
  tcg_gen_mov_i32(cc_flag, temp_5);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_i32(temp_2, temp_1, 1); tcg_gen_andi_i32(temp_2, temp_2, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, arc_true, done_1);;
  tcg_gen_andi_i32(temp_7, c, 65535);
  tcg_gen_andi_i32(temp_6, b, 65535);
  tcg_gen_mul_i32(a, temp_6, temp_7);
  TCGLabel *done_2 = gen_new_label();
  temp_8 = getFFlag();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_3, temp_8, arc_true);
  tcg_gen_xori_i32(temp_4, temp_3, 1); tcg_gen_andi_i32(temp_4, temp_4, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_4, arc_true, done_2);;
  setZFlag(a);
  tcg_gen_movi_i32(temp_9, 0);
  setNFlag(temp_9);
  tcg_gen_movi_i32(temp_10, 0);
  setVFlag(temp_10);
  gen_set_label(done_2);
  gen_set_label(done_1);
  if(temp_5 != NULL) tcg_temp_free(temp_5);
  tcg_temp_free(cc_flag);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  tcg_temp_free(temp_7);
  tcg_temp_free(temp_6);
  if(temp_8 != NULL) tcg_temp_free(temp_8);
  tcg_temp_free(temp_3);
  tcg_temp_free(temp_4);
  tcg_temp_free(temp_9);
  tcg_temp_free(temp_10);

  return ret;
}





/* MPYW
 *    Variables: @a, @b, @c
 *    Functions: getCCFlag, getFFlag, setZFlag, setNFlag, setVFlag
--- code ---
{
  cc_flag = getCCFlag ();
  if((cc_flag == true))
    {
      @a = ((@b & 65535) * (@c & 65535));
      if((getFFlag () == true))
        {
          setZFlag (@a);
          setNFlag (@a);
          setVFlag (@a);
        };
    };
}
 */

int
arc2_gen_MPYW (DisasCtxt *ctx, TCGv a, TCGv b, TCGv c)
{
  int ret = BS_NONE;
  TCGv temp_5 = NULL /* REFERENCE */;
  TCGv cc_flag = tcg_temp_local_new_i32();
  TCGv temp_1 = tcg_temp_local_new_i32();
  TCGv temp_2 = tcg_temp_local_new_i32();
  TCGv temp_7 = tcg_temp_local_new_i32();
  TCGv temp_6 = tcg_temp_local_new_i32();
  TCGv temp_8 = NULL /* REFERENCE */;
  TCGv temp_3 = tcg_temp_local_new_i32();
  TCGv temp_4 = tcg_temp_local_new_i32();
  temp_5 = getCCFlag();
  tcg_gen_mov_i32(cc_flag, temp_5);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_i32(temp_2, temp_1, 1); tcg_gen_andi_i32(temp_2, temp_2, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, arc_true, done_1);;
  tcg_gen_andi_i32(temp_7, c, 65535);
  tcg_gen_andi_i32(temp_6, b, 65535);
  tcg_gen_mul_i32(a, temp_6, temp_7);
  TCGLabel *done_2 = gen_new_label();
  temp_8 = getFFlag();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_3, temp_8, arc_true);
  tcg_gen_xori_i32(temp_4, temp_3, 1); tcg_gen_andi_i32(temp_4, temp_4, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_4, arc_true, done_2);;
  setZFlag(a);
  setNFlag(a);
  setVFlag(a);
  gen_set_label(done_2);
  gen_set_label(done_1);
  if(temp_5 != NULL) tcg_temp_free(temp_5);
  tcg_temp_free(cc_flag);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  tcg_temp_free(temp_7);
  tcg_temp_free(temp_6);
  if(temp_8 != NULL) tcg_temp_free(temp_8);
  tcg_temp_free(temp_3);
  tcg_temp_free(temp_4);

  return ret;
}





/* DIV
 *    Variables: @src2, @src1, @dest
 *    Functions: getCCFlag, divSigned, getFFlag, setZFlag, setNFlag, setVFlag
--- code ---
{
  cc_flag = getCCFlag ();
  if((cc_flag == true))
    {
      if(((@src2 != 0) && ((@src1 != 2147483648) || (@src2 != 4294967295))))
        {
          @dest = divSigned (@src1, @src2);
          if((getFFlag () == true))
            {
              setZFlag (@dest);
              setNFlag (@dest);
              setVFlag (0);
            };
        }
      else
        {
        };
    };
}
 */

int
arc2_gen_DIV (DisasCtxt *ctx, TCGv src2, TCGv src1, TCGv dest)
{
  int ret = BS_NONE;
  TCGv temp_11 = NULL /* REFERENCE */;
  TCGv cc_flag = tcg_temp_local_new_i32();
  TCGv temp_1 = tcg_temp_local_new_i32();
  TCGv temp_2 = tcg_temp_local_new_i32();
  TCGv temp_3 = tcg_temp_local_new_i32();
  TCGv temp_4 = tcg_temp_local_new_i32();
  TCGv temp_5 = tcg_temp_local_new_i32();
  TCGv temp_6 = tcg_temp_local_new_i32();
  TCGv temp_7 = tcg_temp_local_new_i32();
  TCGv temp_8 = tcg_temp_local_new_i32();
  TCGv temp_12 = NULL /* REFERENCE */;
  TCGv temp_13 = NULL /* REFERENCE */;
  TCGv temp_9 = tcg_temp_local_new_i32();
  TCGv temp_10 = tcg_temp_local_new_i32();
  TCGv temp_14 = tcg_temp_local_new_i32();
  temp_11 = getCCFlag();
  tcg_gen_mov_i32(cc_flag, temp_11);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_i32(temp_2, temp_1, 1); tcg_gen_andi_i32(temp_2, temp_2, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, arc_true, done_1);;
  TCGLabel *else_2 = gen_new_label();
  TCGLabel *done_2 = gen_new_label();
  tcg_gen_setcondi_i32(TCG_COND_NE, temp_3, src2, 0);
  tcg_gen_setcondi_i32(TCG_COND_NE, temp_4, src1, 2147483648);
  tcg_gen_setcondi_i32(TCG_COND_NE, temp_5, src2, 4294967295);
  tcg_gen_or_i32(temp_6, temp_4, temp_5);
  tcg_gen_and_i32(temp_7, temp_3, temp_6);
  tcg_gen_xori_i32(temp_8, temp_7, 1); tcg_gen_andi_i32(temp_8, temp_8, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_8, arc_true, else_2);;
  temp_12 = divSigned(src1, src2);
  tcg_gen_mov_i32(dest, temp_12);
  TCGLabel *done_3 = gen_new_label();
  temp_13 = getFFlag();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_9, temp_13, arc_true);
  tcg_gen_xori_i32(temp_10, temp_9, 1); tcg_gen_andi_i32(temp_10, temp_10, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_10, arc_true, done_3);;
  setZFlag(dest);
  setNFlag(dest);
  tcg_gen_movi_i32(temp_14, 0);
  setVFlag(temp_14);
  gen_set_label(done_3);
  tcg_gen_br(done_2);
  gen_set_label(else_2);
  gen_set_label(done_2);
  gen_set_label(done_1);
  if(temp_11 != NULL) tcg_temp_free(temp_11);
  tcg_temp_free(cc_flag);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  tcg_temp_free(temp_3);
  tcg_temp_free(temp_4);
  tcg_temp_free(temp_5);
  tcg_temp_free(temp_6);
  tcg_temp_free(temp_7);
  tcg_temp_free(temp_8);
  if(temp_12 != NULL) tcg_temp_free(temp_12);
  if(temp_13 != NULL) tcg_temp_free(temp_13);
  tcg_temp_free(temp_9);
  tcg_temp_free(temp_10);
  tcg_temp_free(temp_14);

  return ret;
}





/* DIVU
 *    Variables: @src2, @dest, @src1
 *    Functions: getCCFlag, divUnsigned, getFFlag, setZFlag, setNFlag, setVFlag
--- code ---
{
  cc_flag = getCCFlag ();
  if((cc_flag == true))
    {
      if((@src2 != 0))
        {
          @dest = divUnsigned (@src1, @src2);
          if((getFFlag () == true))
            {
              setZFlag (@dest);
              setNFlag (0);
              setVFlag (0);
            };
        }
      else
        {
        };
    };
}
 */

int
arc2_gen_DIVU (DisasCtxt *ctx, TCGv src2, TCGv dest, TCGv src1)
{
  int ret = BS_NONE;
  TCGv temp_7 = NULL /* REFERENCE */;
  TCGv cc_flag = tcg_temp_local_new_i32();
  TCGv temp_1 = tcg_temp_local_new_i32();
  TCGv temp_2 = tcg_temp_local_new_i32();
  TCGv temp_3 = tcg_temp_local_new_i32();
  TCGv temp_4 = tcg_temp_local_new_i32();
  TCGv temp_8 = NULL /* REFERENCE */;
  TCGv temp_9 = NULL /* REFERENCE */;
  TCGv temp_5 = tcg_temp_local_new_i32();
  TCGv temp_6 = tcg_temp_local_new_i32();
  TCGv temp_10 = tcg_temp_local_new_i32();
  TCGv temp_11 = tcg_temp_local_new_i32();
  temp_7 = getCCFlag();
  tcg_gen_mov_i32(cc_flag, temp_7);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_i32(temp_2, temp_1, 1); tcg_gen_andi_i32(temp_2, temp_2, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, arc_true, done_1);;
  TCGLabel *else_2 = gen_new_label();
  TCGLabel *done_2 = gen_new_label();
  tcg_gen_setcondi_i32(TCG_COND_NE, temp_3, src2, 0);
  tcg_gen_xori_i32(temp_4, temp_3, 1); tcg_gen_andi_i32(temp_4, temp_4, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_4, arc_true, else_2);;
  temp_8 = divUnsigned(src1, src2);
  tcg_gen_mov_i32(dest, temp_8);
  TCGLabel *done_3 = gen_new_label();
  temp_9 = getFFlag();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_5, temp_9, arc_true);
  tcg_gen_xori_i32(temp_6, temp_5, 1); tcg_gen_andi_i32(temp_6, temp_6, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_6, arc_true, done_3);;
  setZFlag(dest);
  tcg_gen_movi_i32(temp_10, 0);
  setNFlag(temp_10);
  tcg_gen_movi_i32(temp_11, 0);
  setVFlag(temp_11);
  gen_set_label(done_3);
  tcg_gen_br(done_2);
  gen_set_label(else_2);
  gen_set_label(done_2);
  gen_set_label(done_1);
  if(temp_7 != NULL) tcg_temp_free(temp_7);
  tcg_temp_free(cc_flag);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  tcg_temp_free(temp_3);
  tcg_temp_free(temp_4);
  if(temp_8 != NULL) tcg_temp_free(temp_8);
  if(temp_9 != NULL) tcg_temp_free(temp_9);
  tcg_temp_free(temp_5);
  tcg_temp_free(temp_6);
  tcg_temp_free(temp_10);
  tcg_temp_free(temp_11);

  return ret;
}





/* REM
 *    Variables: @src2, @src1, @dest
 *    Functions: getCCFlag, divRemainingSigned, getFFlag, setZFlag, setNFlag, setVFlag
--- code ---
{
  cc_flag = getCCFlag ();
  if((cc_flag == true))
    {
      if(((@src2 != 0) && ((@src1 != 2147483648) || (@src2 != 4294967295))))
        {
          @dest = divRemainingSigned (@src1, @src2);
          if((getFFlag () == true))
            {
              setZFlag (@dest);
              setNFlag (@dest);
              setVFlag (0);
            };
        }
      else
        {
        };
    };
}
 */

int
arc2_gen_REM (DisasCtxt *ctx, TCGv src2, TCGv src1, TCGv dest)
{
  int ret = BS_NONE;
  TCGv temp_11 = NULL /* REFERENCE */;
  TCGv cc_flag = tcg_temp_local_new_i32();
  TCGv temp_1 = tcg_temp_local_new_i32();
  TCGv temp_2 = tcg_temp_local_new_i32();
  TCGv temp_3 = tcg_temp_local_new_i32();
  TCGv temp_4 = tcg_temp_local_new_i32();
  TCGv temp_5 = tcg_temp_local_new_i32();
  TCGv temp_6 = tcg_temp_local_new_i32();
  TCGv temp_7 = tcg_temp_local_new_i32();
  TCGv temp_8 = tcg_temp_local_new_i32();
  TCGv temp_12 = NULL /* REFERENCE */;
  TCGv temp_13 = NULL /* REFERENCE */;
  TCGv temp_9 = tcg_temp_local_new_i32();
  TCGv temp_10 = tcg_temp_local_new_i32();
  TCGv temp_14 = tcg_temp_local_new_i32();
  temp_11 = getCCFlag();
  tcg_gen_mov_i32(cc_flag, temp_11);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_i32(temp_2, temp_1, 1); tcg_gen_andi_i32(temp_2, temp_2, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, arc_true, done_1);;
  TCGLabel *else_2 = gen_new_label();
  TCGLabel *done_2 = gen_new_label();
  tcg_gen_setcondi_i32(TCG_COND_NE, temp_3, src2, 0);
  tcg_gen_setcondi_i32(TCG_COND_NE, temp_4, src1, 2147483648);
  tcg_gen_setcondi_i32(TCG_COND_NE, temp_5, src2, 4294967295);
  tcg_gen_or_i32(temp_6, temp_4, temp_5);
  tcg_gen_and_i32(temp_7, temp_3, temp_6);
  tcg_gen_xori_i32(temp_8, temp_7, 1); tcg_gen_andi_i32(temp_8, temp_8, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_8, arc_true, else_2);;
  temp_12 = divRemainingSigned(src1, src2);
  tcg_gen_mov_i32(dest, temp_12);
  TCGLabel *done_3 = gen_new_label();
  temp_13 = getFFlag();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_9, temp_13, arc_true);
  tcg_gen_xori_i32(temp_10, temp_9, 1); tcg_gen_andi_i32(temp_10, temp_10, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_10, arc_true, done_3);;
  setZFlag(dest);
  setNFlag(dest);
  tcg_gen_movi_i32(temp_14, 0);
  setVFlag(temp_14);
  gen_set_label(done_3);
  tcg_gen_br(done_2);
  gen_set_label(else_2);
  gen_set_label(done_2);
  gen_set_label(done_1);
  if(temp_11 != NULL) tcg_temp_free(temp_11);
  tcg_temp_free(cc_flag);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  tcg_temp_free(temp_3);
  tcg_temp_free(temp_4);
  tcg_temp_free(temp_5);
  tcg_temp_free(temp_6);
  tcg_temp_free(temp_7);
  tcg_temp_free(temp_8);
  if(temp_12 != NULL) tcg_temp_free(temp_12);
  if(temp_13 != NULL) tcg_temp_free(temp_13);
  tcg_temp_free(temp_9);
  tcg_temp_free(temp_10);
  tcg_temp_free(temp_14);

  return ret;
}





/* REMU
 *    Variables: @src2, @dest, @src1
 *    Functions: getCCFlag, divRemainingUnsigned, getFFlag, setZFlag, setNFlag, setVFlag
--- code ---
{
  cc_flag = getCCFlag ();
  if((cc_flag == true))
    {
      if((@src2 != 0))
        {
          @dest = divRemainingUnsigned (@src1, @src2);
          if((getFFlag () == true))
            {
              setZFlag (@dest);
              setNFlag (0);
              setVFlag (0);
            };
        }
      else
        {
        };
    };
}
 */

int
arc2_gen_REMU (DisasCtxt *ctx, TCGv src2, TCGv dest, TCGv src1)
{
  int ret = BS_NONE;
  TCGv temp_7 = NULL /* REFERENCE */;
  TCGv cc_flag = tcg_temp_local_new_i32();
  TCGv temp_1 = tcg_temp_local_new_i32();
  TCGv temp_2 = tcg_temp_local_new_i32();
  TCGv temp_3 = tcg_temp_local_new_i32();
  TCGv temp_4 = tcg_temp_local_new_i32();
  TCGv temp_8 = NULL /* REFERENCE */;
  TCGv temp_9 = NULL /* REFERENCE */;
  TCGv temp_5 = tcg_temp_local_new_i32();
  TCGv temp_6 = tcg_temp_local_new_i32();
  TCGv temp_10 = tcg_temp_local_new_i32();
  TCGv temp_11 = tcg_temp_local_new_i32();
  temp_7 = getCCFlag();
  tcg_gen_mov_i32(cc_flag, temp_7);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_i32(temp_2, temp_1, 1); tcg_gen_andi_i32(temp_2, temp_2, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, arc_true, done_1);;
  TCGLabel *else_2 = gen_new_label();
  TCGLabel *done_2 = gen_new_label();
  tcg_gen_setcondi_i32(TCG_COND_NE, temp_3, src2, 0);
  tcg_gen_xori_i32(temp_4, temp_3, 1); tcg_gen_andi_i32(temp_4, temp_4, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_4, arc_true, else_2);;
  temp_8 = divRemainingUnsigned(src1, src2);
  tcg_gen_mov_i32(dest, temp_8);
  TCGLabel *done_3 = gen_new_label();
  temp_9 = getFFlag();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_5, temp_9, arc_true);
  tcg_gen_xori_i32(temp_6, temp_5, 1); tcg_gen_andi_i32(temp_6, temp_6, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_6, arc_true, done_3);;
  setZFlag(dest);
  tcg_gen_movi_i32(temp_10, 0);
  setNFlag(temp_10);
  tcg_gen_movi_i32(temp_11, 0);
  setVFlag(temp_11);
  gen_set_label(done_3);
  tcg_gen_br(done_2);
  gen_set_label(else_2);
  gen_set_label(done_2);
  gen_set_label(done_1);
  if(temp_7 != NULL) tcg_temp_free(temp_7);
  tcg_temp_free(cc_flag);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  tcg_temp_free(temp_3);
  tcg_temp_free(temp_4);
  if(temp_8 != NULL) tcg_temp_free(temp_8);
  if(temp_9 != NULL) tcg_temp_free(temp_9);
  tcg_temp_free(temp_5);
  tcg_temp_free(temp_6);
  tcg_temp_free(temp_10);
  tcg_temp_free(temp_11);

  return ret;
}





/* ABS
 *    Variables: @src, @dest
 *    Functions: Carry, getFFlag, setZFlag, setNFlag, setCFlag, Zero, setVFlag, getNFlag
--- code ---
{
  lsrc = @src;
  alu = (0 - lsrc);
  if((Carry (lsrc) == 1))
    {
      @dest = alu;
    }
  else
    {
      @dest = lsrc;
    };
  if((getFFlag () == true))
    {
      setZFlag (@dest);
      setNFlag (@dest);
      setCFlag (Zero ());
      setVFlag (getNFlag ());
    };
}
 */

int
arc2_gen_ABS (DisasCtxt *ctx, TCGv src, TCGv dest)
{
  int ret = BS_NONE;
  TCGv lsrc = tcg_temp_local_new_i32();
  TCGv alu = tcg_temp_local_new_i32();
  TCGv temp_5 = NULL /* REFERENCE */;
  TCGv temp_1 = tcg_temp_local_new_i32();
  TCGv temp_2 = tcg_temp_local_new_i32();
  TCGv temp_6 = NULL /* REFERENCE */;
  TCGv temp_3 = tcg_temp_local_new_i32();
  TCGv temp_4 = tcg_temp_local_new_i32();
  TCGv temp_7 = tcg_temp_local_new_i32();
  TCGv temp_8 = tcg_temp_local_new_i32();
  tcg_gen_mov_i32(lsrc, src);
  tcg_gen_subfi_i32(alu, 0, lsrc);
  TCGLabel *else_1 = gen_new_label();
  TCGLabel *done_1 = gen_new_label();
  temp_5 = Carry(lsrc);
  tcg_gen_setcondi_i32(TCG_COND_EQ, temp_1, temp_5, 1);
  tcg_gen_xori_i32(temp_2, temp_1, 1); tcg_gen_andi_i32(temp_2, temp_2, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, arc_true, else_1);;
  tcg_gen_mov_i32(dest, alu);
  tcg_gen_br(done_1);
  gen_set_label(else_1);
  tcg_gen_mov_i32(dest, lsrc);
  gen_set_label(done_1);
  TCGLabel *done_2 = gen_new_label();
  temp_6 = getFFlag();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_3, temp_6, arc_true);
  tcg_gen_xori_i32(temp_4, temp_3, 1); tcg_gen_andi_i32(temp_4, temp_4, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_4, arc_true, done_2);;
  setZFlag(dest);
  setNFlag(dest);
  tcg_gen_mov_i32(temp_7, Zero());
  setCFlag(temp_7);
  tcg_gen_mov_i32(temp_8, getNFlag());
  setVFlag(temp_8);
  gen_set_label(done_2);
  tcg_temp_free(lsrc);
  tcg_temp_free(alu);
  if(temp_5 != NULL) tcg_temp_free(temp_5);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  if(temp_6 != NULL) tcg_temp_free(temp_6);
  tcg_temp_free(temp_3);
  tcg_temp_free(temp_4);
  tcg_temp_free(temp_7);
  tcg_temp_free(temp_8);

  return ret;
}





/* SWAP
 *    Variables: @src, @dest
 *    Functions: getFFlag, setZFlag, setNFlag
--- code ---
{
  tmp1 = (@src << 16);
  tmp2 = ((@src >> 16) & 65535);
  @dest = (tmp1 | tmp2);
  if((getFFlag () == true))
    {
      setZFlag (@dest);
      setNFlag (@dest);
    };
}
 */

int
arc2_gen_SWAP (DisasCtxt *ctx, TCGv src, TCGv dest)
{
  int ret = BS_NONE;
  TCGv tmp1 = tcg_temp_local_new_i32();
  TCGv temp_3 = tcg_temp_local_new_i32();
  TCGv tmp2 = tcg_temp_local_new_i32();
  TCGv temp_4 = NULL /* REFERENCE */;
  TCGv temp_1 = tcg_temp_local_new_i32();
  TCGv temp_2 = tcg_temp_local_new_i32();
  tcg_gen_shli_i32(tmp1, src, 16);
  tcg_gen_shri_i32(temp_3, src, 16);
  tcg_gen_andi_i32(tmp2, temp_3, 65535);
  tcg_gen_or_i32(dest, tmp1, tmp2);
  TCGLabel *done_1 = gen_new_label();
  temp_4 = getFFlag();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, temp_4, arc_true);
  tcg_gen_xori_i32(temp_2, temp_1, 1); tcg_gen_andi_i32(temp_2, temp_2, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, arc_true, done_1);;
  setZFlag(dest);
  setNFlag(dest);
  gen_set_label(done_1);
  tcg_temp_free(tmp1);
  tcg_temp_free(temp_3);
  tcg_temp_free(tmp2);
  if(temp_4 != NULL) tcg_temp_free(temp_4);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);

  return ret;
}





/* SWAPE
 *    Variables: @src, @dest
 *    Functions: getFFlag, setZFlag, setNFlag
--- code ---
{
  tmp1 = ((@src << 24) & 4278190080);
  tmp2 = ((@src << 8) & 16711680);
  tmp3 = ((@src >> 8) & 65280);
  tmp4 = ((@src >> 24) & 255);
  @dest = (((tmp1 | tmp2) | tmp3) | tmp4);
  if((getFFlag () == true))
    {
      setZFlag (@dest);
      setNFlag (@dest);
    };
}
 */

int
arc2_gen_SWAPE (DisasCtxt *ctx, TCGv src, TCGv dest)
{
  int ret = BS_NONE;
  TCGv temp_3 = tcg_temp_local_new_i32();
  TCGv tmp1 = tcg_temp_local_new_i32();
  TCGv temp_4 = tcg_temp_local_new_i32();
  TCGv tmp2 = tcg_temp_local_new_i32();
  TCGv temp_5 = tcg_temp_local_new_i32();
  TCGv tmp3 = tcg_temp_local_new_i32();
  TCGv temp_6 = tcg_temp_local_new_i32();
  TCGv tmp4 = tcg_temp_local_new_i32();
  TCGv temp_8 = tcg_temp_local_new_i32();
  TCGv temp_7 = tcg_temp_local_new_i32();
  TCGv temp_9 = NULL /* REFERENCE */;
  TCGv temp_1 = tcg_temp_local_new_i32();
  TCGv temp_2 = tcg_temp_local_new_i32();
  tcg_gen_shli_i32(temp_3, src, 24);
  tcg_gen_andi_i32(tmp1, temp_3, 4278190080);
  tcg_gen_shli_i32(temp_4, src, 8);
  tcg_gen_andi_i32(tmp2, temp_4, 16711680);
  tcg_gen_shri_i32(temp_5, src, 8);
  tcg_gen_andi_i32(tmp3, temp_5, 65280);
  tcg_gen_shri_i32(temp_6, src, 24);
  tcg_gen_andi_i32(tmp4, temp_6, 255);
  tcg_gen_or_i32(temp_8, tmp1, tmp2);
  tcg_gen_or_i32(temp_7, temp_8, tmp3);
  tcg_gen_or_i32(dest, temp_7, tmp4);
  TCGLabel *done_1 = gen_new_label();
  temp_9 = getFFlag();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, temp_9, arc_true);
  tcg_gen_xori_i32(temp_2, temp_1, 1); tcg_gen_andi_i32(temp_2, temp_2, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, arc_true, done_1);;
  setZFlag(dest);
  setNFlag(dest);
  gen_set_label(done_1);
  tcg_temp_free(temp_3);
  tcg_temp_free(tmp1);
  tcg_temp_free(temp_4);
  tcg_temp_free(tmp2);
  tcg_temp_free(temp_5);
  tcg_temp_free(tmp3);
  tcg_temp_free(temp_6);
  tcg_temp_free(tmp4);
  tcg_temp_free(temp_8);
  tcg_temp_free(temp_7);
  if(temp_9 != NULL) tcg_temp_free(temp_9);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);

  return ret;
}





/* NOT
 *    Variables: @dest, @src
 *    Functions: getFFlag, setZFlag, setNFlag
--- code ---
{
  @dest = ~@src;
  if((getFFlag () == true))
    {
      setZFlag (@dest);
      setNFlag (@dest);
    };
}
 */

int
arc2_gen_NOT (DisasCtxt *ctx, TCGv dest, TCGv src)
{
  int ret = BS_NONE;
  TCGv temp_3 = NULL /* REFERENCE */;
  TCGv temp_1 = tcg_temp_local_new_i32();
  TCGv temp_2 = tcg_temp_local_new_i32();
  tcg_gen_not_i32(dest, src);
  TCGLabel *done_1 = gen_new_label();
  temp_3 = getFFlag();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, temp_3, arc_true);
  tcg_gen_xori_i32(temp_2, temp_1, 1); tcg_gen_andi_i32(temp_2, temp_2, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, arc_true, done_1);;
  setZFlag(dest);
  setNFlag(dest);
  gen_set_label(done_1);
  if(temp_3 != NULL) tcg_temp_free(temp_3);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);

  return ret;
}





/* BI
 *    Variables: @c
 *    Functions: setPC, getPCL
--- code ---
{
  setPC ((getPCL () + (@c << 2)));
}
 */

int
arc2_gen_BI (DisasCtxt *ctx, TCGv c)
{
  int ret = BS_NONE;
  TCGv temp_4 = tcg_temp_local_new_i32();
  TCGv temp_3 = NULL /* REFERENCE */;
  TCGv temp_2 = tcg_temp_local_new_i32();
  TCGv temp_1 = tcg_temp_local_new_i32();
  tcg_gen_shli_i32(temp_4, c, 2);
  temp_3 = getPCL();
  tcg_gen_mov_i32(temp_2, temp_3);
  tcg_gen_add_i32(temp_1, temp_2, temp_4);
  setPC(temp_1);
  tcg_temp_free(temp_4);
  if(temp_3 != NULL) tcg_temp_free(temp_3);
  tcg_temp_free(temp_2);
  tcg_temp_free(temp_1);

  return ret;
}





/* BIH
 *    Variables: @c
 *    Functions: setPC, getPCL
--- code ---
{
  setPC ((getPCL () + (@c << 1)));
}
 */

int
arc2_gen_BIH (DisasCtxt *ctx, TCGv c)
{
  int ret = BS_NONE;
  TCGv temp_4 = tcg_temp_local_new_i32();
  TCGv temp_3 = NULL /* REFERENCE */;
  TCGv temp_2 = tcg_temp_local_new_i32();
  TCGv temp_1 = tcg_temp_local_new_i32();
  tcg_gen_shli_i32(temp_4, c, 1);
  temp_3 = getPCL();
  tcg_gen_mov_i32(temp_2, temp_3);
  tcg_gen_add_i32(temp_1, temp_2, temp_4);
  setPC(temp_1);
  tcg_temp_free(temp_4);
  if(temp_3 != NULL) tcg_temp_free(temp_3);
  tcg_temp_free(temp_2);
  tcg_temp_free(temp_1);

  return ret;
}





/* B
 *    Variables: @rd
 *    Functions: getCCFlag, shouldExecuteDelaySlot, executeDelaySlot, setPC, getPCL
--- code ---
{
  cc_flag = getCCFlag ();
  if((shouldExecuteDelaySlot () == true))
    {
      executeDelaySlot ();
    };
  if((cc_flag == true))
    {
      setPC ((getPCL () + @rd));
    };
}
 */

int
arc2_gen_B (DisasCtxt *ctx, TCGv rd)
{
  int ret = BS_NONE;
  TCGv temp_3 = NULL /* REFERENCE */;
  TCGv cc_flag = tcg_temp_local_new_i32();
  TCGv temp_1 = tcg_temp_local_new_i32();
  TCGv temp_2 = tcg_temp_local_new_i32();
  TCGv temp_6 = NULL /* REFERENCE */;
  TCGv temp_5 = tcg_temp_local_new_i32();
  TCGv temp_4 = tcg_temp_local_new_i32();
  temp_3 = getCCFlag();
  tcg_gen_mov_i32(cc_flag, temp_3);
  if ((shouldExecuteDelaySlot () == true))
    {
    executeDelaySlot();
;
    }
  else
    {
  ;
    }
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_i32(temp_2, temp_1, 1); tcg_gen_andi_i32(temp_2, temp_2, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, arc_true, done_1);;
  temp_6 = getPCL();
  tcg_gen_mov_i32(temp_5, temp_6);
  tcg_gen_add_i32(temp_4, temp_5, rd);
  setPC(temp_4);
  gen_set_label(done_1);
  if(temp_3 != NULL) tcg_temp_free(temp_3);
  tcg_temp_free(cc_flag);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  if(temp_6 != NULL) tcg_temp_free(temp_6);
  tcg_temp_free(temp_5);
  tcg_temp_free(temp_4);

  return ret;
}





/* B_S
 *    Variables: @rd
 *    Functions: getCCFlag, killDelaySlot, setPC, getPCL
--- code ---
{
  cc_flag = getCCFlag ();
  if((cc_flag == true))
    {
      killDelaySlot ();
      setPC ((getPCL () + @rd));
    };
}
 */

int
arc2_gen_B_S (DisasCtxt *ctx, TCGv rd)
{
  int ret = BS_NONE;
  TCGv temp_3 = NULL /* REFERENCE */;
  TCGv cc_flag = tcg_temp_local_new_i32();
  TCGv temp_1 = tcg_temp_local_new_i32();
  TCGv temp_2 = tcg_temp_local_new_i32();
  TCGv temp_6 = NULL /* REFERENCE */;
  TCGv temp_5 = tcg_temp_local_new_i32();
  TCGv temp_4 = tcg_temp_local_new_i32();
  temp_3 = getCCFlag();
  tcg_gen_mov_i32(cc_flag, temp_3);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_i32(temp_2, temp_1, 1); tcg_gen_andi_i32(temp_2, temp_2, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, arc_true, done_1);;
  killDelaySlot();
  temp_6 = getPCL();
  tcg_gen_mov_i32(temp_5, temp_6);
  tcg_gen_add_i32(temp_4, temp_5, rd);
  setPC(temp_4);
  gen_set_label(done_1);
  if(temp_3 != NULL) tcg_temp_free(temp_3);
  tcg_temp_free(cc_flag);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  if(temp_6 != NULL) tcg_temp_free(temp_6);
  tcg_temp_free(temp_5);
  tcg_temp_free(temp_4);

  return ret;
}





/* BBIT0
 *    Variables: @b, @c, @rd
 *    Functions: getCCFlag, shouldExecuteDelaySlot, executeDelaySlot, setPC, getPCL
--- code ---
{
  cc_flag = getCCFlag ();
  if((cc_flag == true))
    {
      p_b = @b;
      p_c = (@c & 31);
      tmp = (1 << p_c);
      if((shouldExecuteDelaySlot () == true))
        {
          executeDelaySlot ();
        };
      if(((p_b && tmp) == 0))
        {
          setPC ((getPCL () + @rd));
        };
    };
}
 */

int
arc2_gen_BBIT0 (DisasCtxt *ctx, TCGv b, TCGv c, TCGv rd)
{
  int ret = BS_NONE;
  TCGv temp_6 = NULL /* REFERENCE */;
  TCGv cc_flag = tcg_temp_local_new_i32();
  TCGv temp_1 = tcg_temp_local_new_i32();
  TCGv temp_2 = tcg_temp_local_new_i32();
  TCGv p_b = tcg_temp_local_new_i32();
  TCGv p_c = tcg_temp_local_new_i32();
  TCGv tmp = tcg_temp_local_new_i32();
  TCGv temp_3 = tcg_temp_local_new_i32();
  TCGv temp_4 = tcg_temp_local_new_i32();
  TCGv temp_5 = tcg_temp_local_new_i32();
  TCGv temp_9 = NULL /* REFERENCE */;
  TCGv temp_8 = tcg_temp_local_new_i32();
  TCGv temp_7 = tcg_temp_local_new_i32();
  temp_6 = getCCFlag();
  tcg_gen_mov_i32(cc_flag, temp_6);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_i32(temp_2, temp_1, 1); tcg_gen_andi_i32(temp_2, temp_2, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, arc_true, done_1);;
  tcg_gen_mov_i32(p_b, b);
  tcg_gen_andi_i32(p_c, c, 31);
  tcg_gen_shlfi_i32(tmp, 1, p_c);
  if ((shouldExecuteDelaySlot () == true))
    {
    executeDelaySlot();
;
    }
  else
    {
  ;
    }
  TCGLabel *done_2 = gen_new_label();
  tcg_gen_and_i32(temp_3, p_b, tmp);
  tcg_gen_setcondi_i32(TCG_COND_EQ, temp_4, temp_3, 0);
  tcg_gen_xori_i32(temp_5, temp_4, 1); tcg_gen_andi_i32(temp_5, temp_5, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_5, arc_true, done_2);;
  temp_9 = getPCL();
  tcg_gen_mov_i32(temp_8, temp_9);
  tcg_gen_add_i32(temp_7, temp_8, rd);
  setPC(temp_7);
  gen_set_label(done_2);
  gen_set_label(done_1);
  if(temp_6 != NULL) tcg_temp_free(temp_6);
  tcg_temp_free(cc_flag);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  tcg_temp_free(p_b);
  tcg_temp_free(p_c);
  tcg_temp_free(tmp);
  tcg_temp_free(temp_3);
  tcg_temp_free(temp_4);
  tcg_temp_free(temp_5);
  if(temp_9 != NULL) tcg_temp_free(temp_9);
  tcg_temp_free(temp_8);
  tcg_temp_free(temp_7);

  return ret;
}





/* BBIT1
 *    Variables: @b, @c, @rd
 *    Functions: getCCFlag, shouldExecuteDelaySlot, executeDelaySlot, setPC, getPCL
--- code ---
{
  cc_flag = getCCFlag ();
  if((cc_flag == true))
    {
      p_b = @b;
      p_c = (@c & 31);
      tmp = (1 << p_c);
      if((shouldExecuteDelaySlot () == true))
        {
          executeDelaySlot ();
        };
      if(((p_b && tmp) != 0))
        {
          setPC ((getPCL () + @rd));
        };
    };
}
 */

int
arc2_gen_BBIT1 (DisasCtxt *ctx, TCGv b, TCGv c, TCGv rd)
{
  int ret = BS_NONE;
  TCGv temp_6 = NULL /* REFERENCE */;
  TCGv cc_flag = tcg_temp_local_new_i32();
  TCGv temp_1 = tcg_temp_local_new_i32();
  TCGv temp_2 = tcg_temp_local_new_i32();
  TCGv p_b = tcg_temp_local_new_i32();
  TCGv p_c = tcg_temp_local_new_i32();
  TCGv tmp = tcg_temp_local_new_i32();
  TCGv temp_3 = tcg_temp_local_new_i32();
  TCGv temp_4 = tcg_temp_local_new_i32();
  TCGv temp_5 = tcg_temp_local_new_i32();
  TCGv temp_9 = NULL /* REFERENCE */;
  TCGv temp_8 = tcg_temp_local_new_i32();
  TCGv temp_7 = tcg_temp_local_new_i32();
  temp_6 = getCCFlag();
  tcg_gen_mov_i32(cc_flag, temp_6);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_i32(temp_2, temp_1, 1); tcg_gen_andi_i32(temp_2, temp_2, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, arc_true, done_1);;
  tcg_gen_mov_i32(p_b, b);
  tcg_gen_andi_i32(p_c, c, 31);
  tcg_gen_shlfi_i32(tmp, 1, p_c);
  if ((shouldExecuteDelaySlot () == true))
    {
    executeDelaySlot();
;
    }
  else
    {
  ;
    }
  TCGLabel *done_2 = gen_new_label();
  tcg_gen_and_i32(temp_3, p_b, tmp);
  tcg_gen_setcondi_i32(TCG_COND_NE, temp_4, temp_3, 0);
  tcg_gen_xori_i32(temp_5, temp_4, 1); tcg_gen_andi_i32(temp_5, temp_5, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_5, arc_true, done_2);;
  temp_9 = getPCL();
  tcg_gen_mov_i32(temp_8, temp_9);
  tcg_gen_add_i32(temp_7, temp_8, rd);
  setPC(temp_7);
  gen_set_label(done_2);
  gen_set_label(done_1);
  if(temp_6 != NULL) tcg_temp_free(temp_6);
  tcg_temp_free(cc_flag);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  tcg_temp_free(p_b);
  tcg_temp_free(p_c);
  tcg_temp_free(tmp);
  tcg_temp_free(temp_3);
  tcg_temp_free(temp_4);
  tcg_temp_free(temp_5);
  if(temp_9 != NULL) tcg_temp_free(temp_9);
  tcg_temp_free(temp_8);
  tcg_temp_free(temp_7);

  return ret;
}





/* BL
 *    Variables: @rd
 *    Functions: getCCFlag, shouldExecuteDelaySlot, executeDelaySlot, setBLINK, nextInsnAddressAfterDelaySlot, nextInsnAddress, setPC, getPCL
--- code ---
{
  cc_flag = getCCFlag ();
  if((shouldExecuteDelaySlot () == 1))
    {
      executeDelaySlot ();
    };
  if((cc_flag == true))
    {
      if((shouldExecuteDelaySlot () == 1))
        {
          setBLINK (nextInsnAddressAfterDelaySlot ());
        }
      else
        {
          setBLINK (nextInsnAddress ());
        };
      setPC ((getPCL () + @rd));
    };
}
 */

int
arc2_gen_BL (DisasCtxt *ctx, TCGv rd)
{
  int ret = BS_NONE;
  TCGv temp_3 = NULL /* REFERENCE */;
  TCGv cc_flag = tcg_temp_local_new_i32();
  TCGv temp_1 = tcg_temp_local_new_i32();
  TCGv temp_2 = tcg_temp_local_new_i32();
  TCGv temp_5 = NULL /* REFERENCE */;
  TCGv temp_4 = tcg_temp_local_new_i32();
  TCGv temp_7 = NULL /* REFERENCE */;
  TCGv temp_6 = tcg_temp_local_new_i32();
  TCGv temp_10 = NULL /* REFERENCE */;
  TCGv temp_9 = tcg_temp_local_new_i32();
  TCGv temp_8 = tcg_temp_local_new_i32();
  temp_3 = getCCFlag();
  tcg_gen_mov_i32(cc_flag, temp_3);
  if ((shouldExecuteDelaySlot () == 1))
    {
    executeDelaySlot();
;
    }
  else
    {
  ;
    }
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_i32(temp_2, temp_1, 1); tcg_gen_andi_i32(temp_2, temp_2, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, arc_true, done_1);;
  if ((shouldExecuteDelaySlot () == 1))
    {
    temp_5 = nextInsnAddressAfterDelaySlot();
  tcg_gen_mov_i32(temp_4, temp_5);
  setBLINK(temp_4);
;
    }
  else
    {
    temp_7 = nextInsnAddress();
  tcg_gen_mov_i32(temp_6, temp_7);
  setBLINK(temp_6);
;
    }
  temp_10 = getPCL();
  tcg_gen_mov_i32(temp_9, temp_10);
  tcg_gen_add_i32(temp_8, temp_9, rd);
  setPC(temp_8);
  gen_set_label(done_1);
  if(temp_3 != NULL) tcg_temp_free(temp_3);
  tcg_temp_free(cc_flag);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  if(temp_5 != NULL) tcg_temp_free(temp_5);
  tcg_temp_free(temp_4);
  if(temp_7 != NULL) tcg_temp_free(temp_7);
  tcg_temp_free(temp_6);
  if(temp_10 != NULL) tcg_temp_free(temp_10);
  tcg_temp_free(temp_9);
  tcg_temp_free(temp_8);

  return ret;
}





/* J
 *    Variables: @src
 *    Functions: getCCFlag, shouldExecuteDelaySlot, executeDelaySlot, setPC
--- code ---
{
  cc_flag = getCCFlag ();
  if((shouldExecuteDelaySlot () == 1))
    {
      executeDelaySlot ();
    };
  if((cc_flag == true))
    {
      setPC (@src);
    };
}
 */

int
arc2_gen_J (DisasCtxt *ctx, TCGv src)
{
  int ret = BS_NONE;
  TCGv temp_3 = NULL /* REFERENCE */;
  TCGv cc_flag = tcg_temp_local_new_i32();
  TCGv temp_1 = tcg_temp_local_new_i32();
  TCGv temp_2 = tcg_temp_local_new_i32();
  temp_3 = getCCFlag();
  tcg_gen_mov_i32(cc_flag, temp_3);
  if ((shouldExecuteDelaySlot () == 1))
    {
    executeDelaySlot();
;
    }
  else
    {
  ;
    }
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_i32(temp_2, temp_1, 1); tcg_gen_andi_i32(temp_2, temp_2, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, arc_true, done_1);;
  setPC(src);
  gen_set_label(done_1);
  if(temp_3 != NULL) tcg_temp_free(temp_3);
  tcg_temp_free(cc_flag);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);

  return ret;
}





/* JL
 *    Variables: @src
 *    Functions: getCCFlag, shouldExecuteDelaySlot, executeDelaySlot, setBLINK, nextInsnAddressAfterDelaySlot, nextInsnAddress, setPC
--- code ---
{
  cc_flag = getCCFlag ();
  if((shouldExecuteDelaySlot () == 1))
    {
      executeDelaySlot ();
    };
  if((cc_flag == true))
    {
      if((shouldExecuteDelaySlot () == 1))
        {
          setBLINK (nextInsnAddressAfterDelaySlot ());
        }
      else
        {
          setBLINK (nextInsnAddress ());
        };
      setPC (@src);
    };
}
 */

int
arc2_gen_JL (DisasCtxt *ctx, TCGv src)
{
  int ret = BS_NONE;
  TCGv temp_3 = NULL /* REFERENCE */;
  TCGv cc_flag = tcg_temp_local_new_i32();
  TCGv temp_1 = tcg_temp_local_new_i32();
  TCGv temp_2 = tcg_temp_local_new_i32();
  TCGv temp_5 = NULL /* REFERENCE */;
  TCGv temp_4 = tcg_temp_local_new_i32();
  TCGv temp_7 = NULL /* REFERENCE */;
  TCGv temp_6 = tcg_temp_local_new_i32();
  temp_3 = getCCFlag();
  tcg_gen_mov_i32(cc_flag, temp_3);
  if ((shouldExecuteDelaySlot () == 1))
    {
    executeDelaySlot();
;
    }
  else
    {
  ;
    }
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_i32(temp_2, temp_1, 1); tcg_gen_andi_i32(temp_2, temp_2, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, arc_true, done_1);;
  if ((shouldExecuteDelaySlot () == 1))
    {
    temp_5 = nextInsnAddressAfterDelaySlot();
  tcg_gen_mov_i32(temp_4, temp_5);
  setBLINK(temp_4);
;
    }
  else
    {
    temp_7 = nextInsnAddress();
  tcg_gen_mov_i32(temp_6, temp_7);
  setBLINK(temp_6);
;
    }
  setPC(src);
  gen_set_label(done_1);
  if(temp_3 != NULL) tcg_temp_free(temp_3);
  tcg_temp_free(cc_flag);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  if(temp_5 != NULL) tcg_temp_free(temp_5);
  tcg_temp_free(temp_4);
  if(temp_7 != NULL) tcg_temp_free(temp_7);
  tcg_temp_free(temp_6);

  return ret;
}





/* SETEQ
 *    Variables: @b, @c, @a
 *    Functions: getCCFlag
--- code ---
{
  cc_flag = getCCFlag ();
  if((cc_flag == true))
    {
      p_b = @b;
      p_c = @c;
      if((p_b == p_c))
        {
          @a = true;
        }
      else
        {
          @a = false;
        };
    };
}
 */

int
arc2_gen_SETEQ (DisasCtxt *ctx, TCGv b, TCGv c, TCGv a)
{
  int ret = BS_NONE;
  TCGv temp_5 = NULL /* REFERENCE */;
  TCGv cc_flag = tcg_temp_local_new_i32();
  TCGv temp_1 = tcg_temp_local_new_i32();
  TCGv temp_2 = tcg_temp_local_new_i32();
  TCGv p_b = tcg_temp_local_new_i32();
  TCGv p_c = tcg_temp_local_new_i32();
  TCGv temp_3 = tcg_temp_local_new_i32();
  TCGv temp_4 = tcg_temp_local_new_i32();
  temp_5 = getCCFlag();
  tcg_gen_mov_i32(cc_flag, temp_5);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_i32(temp_2, temp_1, 1); tcg_gen_andi_i32(temp_2, temp_2, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, arc_true, done_1);;
  tcg_gen_mov_i32(p_b, b);
  tcg_gen_mov_i32(p_c, c);
  TCGLabel *else_2 = gen_new_label();
  TCGLabel *done_2 = gen_new_label();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_3, p_b, p_c);
  tcg_gen_xori_i32(temp_4, temp_3, 1); tcg_gen_andi_i32(temp_4, temp_4, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_4, arc_true, else_2);;
  tcg_gen_mov_i32(a, arc_true);
  tcg_gen_br(done_2);
  gen_set_label(else_2);
  tcg_gen_mov_i32(a, arc_false);
  gen_set_label(done_2);
  gen_set_label(done_1);
  if(temp_5 != NULL) tcg_temp_free(temp_5);
  tcg_temp_free(cc_flag);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  tcg_temp_free(p_b);
  tcg_temp_free(p_c);
  tcg_temp_free(temp_3);
  tcg_temp_free(temp_4);

  return ret;
}





/* BREQ
 *    Variables: @b, @c, @offset
 *    Functions: shouldExecuteDelaySlot, executeDelaySlot, setPC, getPCL
--- code ---
{
  p_b = @b;
  p_c = @c;
  if((shouldExecuteDelaySlot () == 1))
    {
      executeDelaySlot ();
    };
  if((p_b == p_c))
    {
      setPC ((getPCL () + @offset));
    }
  else
    {
    };
}
 */

int
arc2_gen_BREQ (DisasCtxt *ctx, TCGv b, TCGv c, TCGv offset)
{
  int ret = BS_NONE;
  TCGv p_b = tcg_temp_local_new_i32();
  TCGv p_c = tcg_temp_local_new_i32();
  TCGv temp_1 = tcg_temp_local_new_i32();
  TCGv temp_2 = tcg_temp_local_new_i32();
  TCGv temp_5 = NULL /* REFERENCE */;
  TCGv temp_4 = tcg_temp_local_new_i32();
  TCGv temp_3 = tcg_temp_local_new_i32();
  tcg_gen_mov_i32(p_b, b);
  tcg_gen_mov_i32(p_c, c);
  if ((shouldExecuteDelaySlot () == 1))
    {
    executeDelaySlot();
;
    }
  else
    {
  ;
    }
  TCGLabel *else_1 = gen_new_label();
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, p_b, p_c);
  tcg_gen_xori_i32(temp_2, temp_1, 1); tcg_gen_andi_i32(temp_2, temp_2, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, arc_true, else_1);;
  temp_5 = getPCL();
  tcg_gen_mov_i32(temp_4, temp_5);
  tcg_gen_add_i32(temp_3, temp_4, offset);
  setPC(temp_3);
  tcg_gen_br(done_1);
  gen_set_label(else_1);
  gen_set_label(done_1);
  tcg_temp_free(p_b);
  tcg_temp_free(p_c);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  if(temp_5 != NULL) tcg_temp_free(temp_5);
  tcg_temp_free(temp_4);
  tcg_temp_free(temp_3);

  return ret;
}





/* SETNE
 *    Variables: @b, @c, @a
 *    Functions: getCCFlag
--- code ---
{
  cc_flag = getCCFlag ();
  if((cc_flag == true))
    {
      p_b = @b;
      p_c = @c;
      if((p_b != p_c))
        {
          @a = true;
        }
      else
        {
          @a = false;
        };
    };
}
 */

int
arc2_gen_SETNE (DisasCtxt *ctx, TCGv b, TCGv c, TCGv a)
{
  int ret = BS_NONE;
  TCGv temp_5 = NULL /* REFERENCE */;
  TCGv cc_flag = tcg_temp_local_new_i32();
  TCGv temp_1 = tcg_temp_local_new_i32();
  TCGv temp_2 = tcg_temp_local_new_i32();
  TCGv p_b = tcg_temp_local_new_i32();
  TCGv p_c = tcg_temp_local_new_i32();
  TCGv temp_3 = tcg_temp_local_new_i32();
  TCGv temp_4 = tcg_temp_local_new_i32();
  temp_5 = getCCFlag();
  tcg_gen_mov_i32(cc_flag, temp_5);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_i32(temp_2, temp_1, 1); tcg_gen_andi_i32(temp_2, temp_2, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, arc_true, done_1);;
  tcg_gen_mov_i32(p_b, b);
  tcg_gen_mov_i32(p_c, c);
  TCGLabel *else_2 = gen_new_label();
  TCGLabel *done_2 = gen_new_label();
  tcg_gen_setcond_i32(TCG_COND_NE, temp_3, p_b, p_c);
  tcg_gen_xori_i32(temp_4, temp_3, 1); tcg_gen_andi_i32(temp_4, temp_4, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_4, arc_true, else_2);;
  tcg_gen_mov_i32(a, arc_true);
  tcg_gen_br(done_2);
  gen_set_label(else_2);
  tcg_gen_mov_i32(a, arc_false);
  gen_set_label(done_2);
  gen_set_label(done_1);
  if(temp_5 != NULL) tcg_temp_free(temp_5);
  tcg_temp_free(cc_flag);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  tcg_temp_free(p_b);
  tcg_temp_free(p_c);
  tcg_temp_free(temp_3);
  tcg_temp_free(temp_4);

  return ret;
}





/* BRNE
 *    Variables: @b, @c, @offset
 *    Functions: shouldExecuteDelaySlot, executeDelaySlot, setPC, getPCL
--- code ---
{
  p_b = @b;
  p_c = @c;
  if((shouldExecuteDelaySlot () == 1))
    {
      executeDelaySlot ();
    };
  if((p_b != p_c))
    {
      setPC ((getPCL () + @offset));
    }
  else
    {
    };
}
 */

int
arc2_gen_BRNE (DisasCtxt *ctx, TCGv b, TCGv c, TCGv offset)
{
  int ret = BS_NONE;
  TCGv p_b = tcg_temp_local_new_i32();
  TCGv p_c = tcg_temp_local_new_i32();
  TCGv temp_1 = tcg_temp_local_new_i32();
  TCGv temp_2 = tcg_temp_local_new_i32();
  TCGv temp_5 = NULL /* REFERENCE */;
  TCGv temp_4 = tcg_temp_local_new_i32();
  TCGv temp_3 = tcg_temp_local_new_i32();
  tcg_gen_mov_i32(p_b, b);
  tcg_gen_mov_i32(p_c, c);
  if ((shouldExecuteDelaySlot () == 1))
    {
    executeDelaySlot();
;
    }
  else
    {
  ;
    }
  TCGLabel *else_1 = gen_new_label();
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_i32(TCG_COND_NE, temp_1, p_b, p_c);
  tcg_gen_xori_i32(temp_2, temp_1, 1); tcg_gen_andi_i32(temp_2, temp_2, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, arc_true, else_1);;
  temp_5 = getPCL();
  tcg_gen_mov_i32(temp_4, temp_5);
  tcg_gen_add_i32(temp_3, temp_4, offset);
  setPC(temp_3);
  tcg_gen_br(done_1);
  gen_set_label(else_1);
  gen_set_label(done_1);
  tcg_temp_free(p_b);
  tcg_temp_free(p_c);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  if(temp_5 != NULL) tcg_temp_free(temp_5);
  tcg_temp_free(temp_4);
  tcg_temp_free(temp_3);

  return ret;
}





/* SETLT
 *    Variables: @b, @c, @a
 *    Functions: getCCFlag
--- code ---
{
  cc_flag = getCCFlag ();
  if((cc_flag == true))
    {
      p_b = @b;
      p_c = @c;
      if((p_b < p_c))
        {
          @a = true;
        }
      else
        {
          @a = false;
        };
    };
}
 */

int
arc2_gen_SETLT (DisasCtxt *ctx, TCGv b, TCGv c, TCGv a)
{
  int ret = BS_NONE;
  TCGv temp_5 = NULL /* REFERENCE */;
  TCGv cc_flag = tcg_temp_local_new_i32();
  TCGv temp_1 = tcg_temp_local_new_i32();
  TCGv temp_2 = tcg_temp_local_new_i32();
  TCGv p_b = tcg_temp_local_new_i32();
  TCGv p_c = tcg_temp_local_new_i32();
  TCGv temp_3 = tcg_temp_local_new_i32();
  TCGv temp_4 = tcg_temp_local_new_i32();
  temp_5 = getCCFlag();
  tcg_gen_mov_i32(cc_flag, temp_5);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_i32(temp_2, temp_1, 1); tcg_gen_andi_i32(temp_2, temp_2, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, arc_true, done_1);;
  tcg_gen_mov_i32(p_b, b);
  tcg_gen_mov_i32(p_c, c);
  TCGLabel *else_2 = gen_new_label();
  TCGLabel *done_2 = gen_new_label();
  tcg_gen_setcond_i32(TCG_COND_LT, temp_3, p_b, p_c);
  tcg_gen_xori_i32(temp_4, temp_3, 1); tcg_gen_andi_i32(temp_4, temp_4, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_4, arc_true, else_2);;
  tcg_gen_mov_i32(a, arc_true);
  tcg_gen_br(done_2);
  gen_set_label(else_2);
  tcg_gen_mov_i32(a, arc_false);
  gen_set_label(done_2);
  gen_set_label(done_1);
  if(temp_5 != NULL) tcg_temp_free(temp_5);
  tcg_temp_free(cc_flag);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  tcg_temp_free(p_b);
  tcg_temp_free(p_c);
  tcg_temp_free(temp_3);
  tcg_temp_free(temp_4);

  return ret;
}





/* BRLT
 *    Variables: @b, @c, @offset
 *    Functions: shouldExecuteDelaySlot, executeDelaySlot, setPC, getPCL
--- code ---
{
  p_b = @b;
  p_c = @c;
  if((shouldExecuteDelaySlot () == 1))
    {
      executeDelaySlot ();
    };
  if((p_b < p_c))
    {
      setPC ((getPCL () + @offset));
    }
  else
    {
    };
}
 */

int
arc2_gen_BRLT (DisasCtxt *ctx, TCGv b, TCGv c, TCGv offset)
{
  int ret = BS_NONE;
  TCGv p_b = tcg_temp_local_new_i32();
  TCGv p_c = tcg_temp_local_new_i32();
  TCGv temp_1 = tcg_temp_local_new_i32();
  TCGv temp_2 = tcg_temp_local_new_i32();
  TCGv temp_5 = NULL /* REFERENCE */;
  TCGv temp_4 = tcg_temp_local_new_i32();
  TCGv temp_3 = tcg_temp_local_new_i32();
  tcg_gen_mov_i32(p_b, b);
  tcg_gen_mov_i32(p_c, c);
  if ((shouldExecuteDelaySlot () == 1))
    {
    executeDelaySlot();
;
    }
  else
    {
  ;
    }
  TCGLabel *else_1 = gen_new_label();
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_i32(TCG_COND_LT, temp_1, p_b, p_c);
  tcg_gen_xori_i32(temp_2, temp_1, 1); tcg_gen_andi_i32(temp_2, temp_2, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, arc_true, else_1);;
  temp_5 = getPCL();
  tcg_gen_mov_i32(temp_4, temp_5);
  tcg_gen_add_i32(temp_3, temp_4, offset);
  setPC(temp_3);
  tcg_gen_br(done_1);
  gen_set_label(else_1);
  gen_set_label(done_1);
  tcg_temp_free(p_b);
  tcg_temp_free(p_c);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  if(temp_5 != NULL) tcg_temp_free(temp_5);
  tcg_temp_free(temp_4);
  tcg_temp_free(temp_3);

  return ret;
}





/* SETGE
 *    Variables: @b, @c, @a
 *    Functions: getCCFlag
--- code ---
{
  cc_flag = getCCFlag ();
  if((cc_flag == true))
    {
      p_b = @b;
      p_c = @c;
      if((p_b >= p_c))
        {
          @a = true;
        }
      else
        {
          @a = false;
        };
    };
}
 */

int
arc2_gen_SETGE (DisasCtxt *ctx, TCGv b, TCGv c, TCGv a)
{
  int ret = BS_NONE;
  TCGv temp_5 = NULL /* REFERENCE */;
  TCGv cc_flag = tcg_temp_local_new_i32();
  TCGv temp_1 = tcg_temp_local_new_i32();
  TCGv temp_2 = tcg_temp_local_new_i32();
  TCGv p_b = tcg_temp_local_new_i32();
  TCGv p_c = tcg_temp_local_new_i32();
  TCGv temp_3 = tcg_temp_local_new_i32();
  TCGv temp_4 = tcg_temp_local_new_i32();
  temp_5 = getCCFlag();
  tcg_gen_mov_i32(cc_flag, temp_5);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_i32(temp_2, temp_1, 1); tcg_gen_andi_i32(temp_2, temp_2, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, arc_true, done_1);;
  tcg_gen_mov_i32(p_b, b);
  tcg_gen_mov_i32(p_c, c);
  TCGLabel *else_2 = gen_new_label();
  TCGLabel *done_2 = gen_new_label();
  tcg_gen_setcond_i32(TCG_COND_GE, temp_3, p_b, p_c);
  tcg_gen_xori_i32(temp_4, temp_3, 1); tcg_gen_andi_i32(temp_4, temp_4, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_4, arc_true, else_2);;
  tcg_gen_mov_i32(a, arc_true);
  tcg_gen_br(done_2);
  gen_set_label(else_2);
  tcg_gen_mov_i32(a, arc_false);
  gen_set_label(done_2);
  gen_set_label(done_1);
  if(temp_5 != NULL) tcg_temp_free(temp_5);
  tcg_temp_free(cc_flag);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  tcg_temp_free(p_b);
  tcg_temp_free(p_c);
  tcg_temp_free(temp_3);
  tcg_temp_free(temp_4);

  return ret;
}





/* BRGE
 *    Variables: @b, @c, @offset
 *    Functions: shouldExecuteDelaySlot, executeDelaySlot, setPC, getPCL
--- code ---
{
  p_b = @b;
  p_c = @c;
  if((shouldExecuteDelaySlot () == 1))
    {
      executeDelaySlot ();
    };
  if((p_b >= p_c))
    {
      setPC ((getPCL () + @offset));
    }
  else
    {
    };
}
 */

int
arc2_gen_BRGE (DisasCtxt *ctx, TCGv b, TCGv c, TCGv offset)
{
  int ret = BS_NONE;
  TCGv p_b = tcg_temp_local_new_i32();
  TCGv p_c = tcg_temp_local_new_i32();
  TCGv temp_1 = tcg_temp_local_new_i32();
  TCGv temp_2 = tcg_temp_local_new_i32();
  TCGv temp_5 = NULL /* REFERENCE */;
  TCGv temp_4 = tcg_temp_local_new_i32();
  TCGv temp_3 = tcg_temp_local_new_i32();
  tcg_gen_mov_i32(p_b, b);
  tcg_gen_mov_i32(p_c, c);
  if ((shouldExecuteDelaySlot () == 1))
    {
    executeDelaySlot();
;
    }
  else
    {
  ;
    }
  TCGLabel *else_1 = gen_new_label();
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_i32(TCG_COND_GE, temp_1, p_b, p_c);
  tcg_gen_xori_i32(temp_2, temp_1, 1); tcg_gen_andi_i32(temp_2, temp_2, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, arc_true, else_1);;
  temp_5 = getPCL();
  tcg_gen_mov_i32(temp_4, temp_5);
  tcg_gen_add_i32(temp_3, temp_4, offset);
  setPC(temp_3);
  tcg_gen_br(done_1);
  gen_set_label(else_1);
  gen_set_label(done_1);
  tcg_temp_free(p_b);
  tcg_temp_free(p_c);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  if(temp_5 != NULL) tcg_temp_free(temp_5);
  tcg_temp_free(temp_4);
  tcg_temp_free(temp_3);

  return ret;
}





/* SETLE
 *    Variables: @b, @c, @a
 *    Functions: getCCFlag
--- code ---
{
  cc_flag = getCCFlag ();
  if((cc_flag == true))
    {
      p_b = @b;
      p_c = @c;
      if((p_b <= p_c))
        {
          @a = true;
        }
      else
        {
          @a = false;
        };
    };
}
 */

int
arc2_gen_SETLE (DisasCtxt *ctx, TCGv b, TCGv c, TCGv a)
{
  int ret = BS_NONE;
  TCGv temp_5 = NULL /* REFERENCE */;
  TCGv cc_flag = tcg_temp_local_new_i32();
  TCGv temp_1 = tcg_temp_local_new_i32();
  TCGv temp_2 = tcg_temp_local_new_i32();
  TCGv p_b = tcg_temp_local_new_i32();
  TCGv p_c = tcg_temp_local_new_i32();
  TCGv temp_3 = tcg_temp_local_new_i32();
  TCGv temp_4 = tcg_temp_local_new_i32();
  temp_5 = getCCFlag();
  tcg_gen_mov_i32(cc_flag, temp_5);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_i32(temp_2, temp_1, 1); tcg_gen_andi_i32(temp_2, temp_2, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, arc_true, done_1);;
  tcg_gen_mov_i32(p_b, b);
  tcg_gen_mov_i32(p_c, c);
  TCGLabel *else_2 = gen_new_label();
  TCGLabel *done_2 = gen_new_label();
  tcg_gen_setcond_i32(TCG_COND_LE, temp_3, p_b, p_c);
  tcg_gen_xori_i32(temp_4, temp_3, 1); tcg_gen_andi_i32(temp_4, temp_4, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_4, arc_true, else_2);;
  tcg_gen_mov_i32(a, arc_true);
  tcg_gen_br(done_2);
  gen_set_label(else_2);
  tcg_gen_mov_i32(a, arc_false);
  gen_set_label(done_2);
  gen_set_label(done_1);
  if(temp_5 != NULL) tcg_temp_free(temp_5);
  tcg_temp_free(cc_flag);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  tcg_temp_free(p_b);
  tcg_temp_free(p_c);
  tcg_temp_free(temp_3);
  tcg_temp_free(temp_4);

  return ret;
}





/* SETGT
 *    Variables: @b, @c, @a
 *    Functions: getCCFlag
--- code ---
{
  cc_flag = getCCFlag ();
  if((cc_flag == true))
    {
      p_b = @b;
      p_c = @c;
      if((p_b > p_c))
        {
          @a = true;
        }
      else
        {
          @a = false;
        };
    };
}
 */

int
arc2_gen_SETGT (DisasCtxt *ctx, TCGv b, TCGv c, TCGv a)
{
  int ret = BS_NONE;
  TCGv temp_5 = NULL /* REFERENCE */;
  TCGv cc_flag = tcg_temp_local_new_i32();
  TCGv temp_1 = tcg_temp_local_new_i32();
  TCGv temp_2 = tcg_temp_local_new_i32();
  TCGv p_b = tcg_temp_local_new_i32();
  TCGv p_c = tcg_temp_local_new_i32();
  TCGv temp_3 = tcg_temp_local_new_i32();
  TCGv temp_4 = tcg_temp_local_new_i32();
  temp_5 = getCCFlag();
  tcg_gen_mov_i32(cc_flag, temp_5);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_i32(temp_2, temp_1, 1); tcg_gen_andi_i32(temp_2, temp_2, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, arc_true, done_1);;
  tcg_gen_mov_i32(p_b, b);
  tcg_gen_mov_i32(p_c, c);
  TCGLabel *else_2 = gen_new_label();
  TCGLabel *done_2 = gen_new_label();
  tcg_gen_setcond_i32(TCG_COND_GT, temp_3, p_b, p_c);
  tcg_gen_xori_i32(temp_4, temp_3, 1); tcg_gen_andi_i32(temp_4, temp_4, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_4, arc_true, else_2);;
  tcg_gen_mov_i32(a, arc_true);
  tcg_gen_br(done_2);
  gen_set_label(else_2);
  tcg_gen_mov_i32(a, arc_false);
  gen_set_label(done_2);
  gen_set_label(done_1);
  if(temp_5 != NULL) tcg_temp_free(temp_5);
  tcg_temp_free(cc_flag);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  tcg_temp_free(p_b);
  tcg_temp_free(p_c);
  tcg_temp_free(temp_3);
  tcg_temp_free(temp_4);

  return ret;
}





/* BRLO
 *    Variables: @b, @c, @offset
 *    Functions: shouldExecuteDelaySlot, executeDelaySlot, unsignedLT, setPC, getPCL
--- code ---
{
  p_b = @b;
  p_c = @c;
  if((shouldExecuteDelaySlot () == 1))
    {
      executeDelaySlot ();
    };
  if(unsignedLT (p_b, p_c))
    {
      setPC ((getPCL () + @offset));
    }
  else
    {
    };
}
 */

int
arc2_gen_BRLO (DisasCtxt *ctx, TCGv b, TCGv c, TCGv offset)
{
  int ret = BS_NONE;
  TCGv p_b = tcg_temp_local_new_i32();
  TCGv p_c = tcg_temp_local_new_i32();
  TCGv temp_2 = NULL /* REFERENCE */;
  TCGv temp_1 = tcg_temp_local_new_i32();
  TCGv temp_5 = NULL /* REFERENCE */;
  TCGv temp_4 = tcg_temp_local_new_i32();
  TCGv temp_3 = tcg_temp_local_new_i32();
  tcg_gen_mov_i32(p_b, b);
  tcg_gen_mov_i32(p_c, c);
  if ((shouldExecuteDelaySlot () == 1))
    {
    executeDelaySlot();
;
    }
  else
    {
  ;
    }
  TCGLabel *else_1 = gen_new_label();
  TCGLabel *done_1 = gen_new_label();
  temp_2 = unsignedLT(p_b, p_c);
  tcg_gen_xori_i32(temp_1, temp_2, 1); tcg_gen_andi_i32(temp_1, temp_1, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_1, arc_true, else_1);;
  temp_5 = getPCL();
  tcg_gen_mov_i32(temp_4, temp_5);
  tcg_gen_add_i32(temp_3, temp_4, offset);
  setPC(temp_3);
  tcg_gen_br(done_1);
  gen_set_label(else_1);
  gen_set_label(done_1);
  tcg_temp_free(p_b);
  tcg_temp_free(p_c);
  if(temp_2 != NULL) tcg_temp_free(temp_2);
  tcg_temp_free(temp_1);
  if(temp_5 != NULL) tcg_temp_free(temp_5);
  tcg_temp_free(temp_4);
  tcg_temp_free(temp_3);

  return ret;
}





/* SETLO
 *    Variables: @b, @c, @a
 *    Functions: unsignedLT
--- code ---
{
  p_b = @b;
  p_c = @c;
  if(unsignedLT (p_b, p_c))
    {
      @a = true;
    }
  else
    {
      @a = false;
    };
}
 */

int
arc2_gen_SETLO (DisasCtxt *ctx, TCGv b, TCGv c, TCGv a)
{
  int ret = BS_NONE;
  TCGv p_b = tcg_temp_local_new_i32();
  TCGv p_c = tcg_temp_local_new_i32();
  TCGv temp_2 = NULL /* REFERENCE */;
  TCGv temp_1 = tcg_temp_local_new_i32();
  tcg_gen_mov_i32(p_b, b);
  tcg_gen_mov_i32(p_c, c);
  TCGLabel *else_1 = gen_new_label();
  TCGLabel *done_1 = gen_new_label();
  temp_2 = unsignedLT(p_b, p_c);
  tcg_gen_xori_i32(temp_1, temp_2, 1); tcg_gen_andi_i32(temp_1, temp_1, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_1, arc_true, else_1);;
  tcg_gen_mov_i32(a, arc_true);
  tcg_gen_br(done_1);
  gen_set_label(else_1);
  tcg_gen_mov_i32(a, arc_false);
  gen_set_label(done_1);
  tcg_temp_free(p_b);
  tcg_temp_free(p_c);
  if(temp_2 != NULL) tcg_temp_free(temp_2);
  tcg_temp_free(temp_1);

  return ret;
}





/* BRHS
 *    Variables: @b, @c, @offset
 *    Functions: shouldExecuteDelaySlot, executeDelaySlot, unsignedGE, setPC, getPCL
--- code ---
{
  p_b = @b;
  p_c = @c;
  if((shouldExecuteDelaySlot () == 1))
    {
      executeDelaySlot ();
    };
  if(unsignedGE (p_b, p_c))
    {
      setPC ((getPCL () + @offset));
    }
  else
    {
    };
}
 */

int
arc2_gen_BRHS (DisasCtxt *ctx, TCGv b, TCGv c, TCGv offset)
{
  int ret = BS_NONE;
  TCGv p_b = tcg_temp_local_new_i32();
  TCGv p_c = tcg_temp_local_new_i32();
  TCGv temp_2 = NULL /* REFERENCE */;
  TCGv temp_1 = tcg_temp_local_new_i32();
  TCGv temp_5 = NULL /* REFERENCE */;
  TCGv temp_4 = tcg_temp_local_new_i32();
  TCGv temp_3 = tcg_temp_local_new_i32();
  tcg_gen_mov_i32(p_b, b);
  tcg_gen_mov_i32(p_c, c);
  if ((shouldExecuteDelaySlot () == 1))
    {
    executeDelaySlot();
;
    }
  else
    {
  ;
    }
  TCGLabel *else_1 = gen_new_label();
  TCGLabel *done_1 = gen_new_label();
  temp_2 = unsignedGE(p_b, p_c);
  tcg_gen_xori_i32(temp_1, temp_2, 1); tcg_gen_andi_i32(temp_1, temp_1, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_1, arc_true, else_1);;
  temp_5 = getPCL();
  tcg_gen_mov_i32(temp_4, temp_5);
  tcg_gen_add_i32(temp_3, temp_4, offset);
  setPC(temp_3);
  tcg_gen_br(done_1);
  gen_set_label(else_1);
  gen_set_label(done_1);
  tcg_temp_free(p_b);
  tcg_temp_free(p_c);
  if(temp_2 != NULL) tcg_temp_free(temp_2);
  tcg_temp_free(temp_1);
  if(temp_5 != NULL) tcg_temp_free(temp_5);
  tcg_temp_free(temp_4);
  tcg_temp_free(temp_3);

  return ret;
}





/* SETHS
 *    Variables: @b, @c, @a
 *    Functions: unsignedGE
--- code ---
{
  p_b = @b;
  p_c = @c;
  if(unsignedGE (p_b, p_c))
    {
      @a = true;
    }
  else
    {
      @a = false;
    };
}
 */

int
arc2_gen_SETHS (DisasCtxt *ctx, TCGv b, TCGv c, TCGv a)
{
  int ret = BS_NONE;
  TCGv p_b = tcg_temp_local_new_i32();
  TCGv p_c = tcg_temp_local_new_i32();
  TCGv temp_2 = NULL /* REFERENCE */;
  TCGv temp_1 = tcg_temp_local_new_i32();
  tcg_gen_mov_i32(p_b, b);
  tcg_gen_mov_i32(p_c, c);
  TCGLabel *else_1 = gen_new_label();
  TCGLabel *done_1 = gen_new_label();
  temp_2 = unsignedGE(p_b, p_c);
  tcg_gen_xori_i32(temp_1, temp_2, 1); tcg_gen_andi_i32(temp_1, temp_1, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_1, arc_true, else_1);;
  tcg_gen_mov_i32(a, arc_true);
  tcg_gen_br(done_1);
  gen_set_label(else_1);
  tcg_gen_mov_i32(a, arc_false);
  gen_set_label(done_1);
  tcg_temp_free(p_b);
  tcg_temp_free(p_c);
  if(temp_2 != NULL) tcg_temp_free(temp_2);
  tcg_temp_free(temp_1);

  return ret;
}





/* EX
 *    Variables: @src, @dest
 *    Functions: getMemory, setMemory
--- code ---
{
  tmp = getMemory (@src, LONG);
  setMemory (@src, LONG, @dest);
  @dest = tmp;
}
 */

int
arc2_gen_EX (DisasCtxt *ctx, TCGv src, TCGv dest)
{
  int ret = BS_NONE;
  TCGv temp_1 = NULL /* REFERENCE */;
  TCGv tmp = tcg_temp_local_new_i32();
  temp_1 = getMemory(src, LONG);
  tcg_gen_mov_i32(tmp, temp_1);
  setMemory(src, LONG, dest);
  tcg_gen_mov_i32(dest, tmp);
  if(temp_1 != NULL) tcg_temp_free(temp_1);
  tcg_temp_free(tmp);

  return ret;
}





/* LLOCK
 *    Variables: @dest, @src
 *    Functions: getMemory, setLF
--- code ---
{
  @dest = getMemory (@src, LONG);
  setLF (1);
}
 */

int
arc2_gen_LLOCK (DisasCtxt *ctx, TCGv dest, TCGv src)
{
  int ret = BS_NONE;
  TCGv temp_1 = NULL /* REFERENCE */;
  TCGv temp_2 = tcg_temp_local_new_i32();
  temp_1 = getMemory(src, LONG);
  tcg_gen_mov_i32(dest, temp_1);
  tcg_gen_movi_i32(temp_2, 1);
  setLF(temp_2);
  if(temp_1 != NULL) tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);

  return ret;
}





/* LLOCKD
 *    Variables: @dest, @src
 *    Functions: getMemory, nextReg, setLF
--- code ---
{
  @dest = getMemory (@src, LONG);
  pair = nextReg (dest);
  pair = getMemory ((@src + 4), LONG);
  setLF (1);
}
 */

int
arc2_gen_LLOCKD (DisasCtxt *ctx, TCGv dest, TCGv src)
{
  int ret = BS_NONE;
  TCGv temp_1 = NULL /* REFERENCE */;
  TCGv pair = tcg_temp_local_new_i32();
  TCGv temp_3 = tcg_temp_local_new_i32();
  TCGv temp_2 = NULL /* REFERENCE */;
  TCGv temp_4 = tcg_temp_local_new_i32();
  temp_1 = getMemory(src, LONG);
  tcg_gen_mov_i32(dest, temp_1);
  pair = nextReg (dest);
  tcg_gen_addi_i32(temp_3, src, 4);
  temp_2 = getMemory(temp_3, LONG);
  tcg_gen_mov_i32(pair, temp_2);
  tcg_gen_movi_i32(temp_4, 1);
  setLF(temp_4);
  if(temp_1 != NULL) tcg_temp_free(temp_1);
  tcg_temp_free(temp_3);
  if(temp_2 != NULL) tcg_temp_free(temp_2);
  tcg_temp_free(temp_4);

  return ret;
}





/* SCOND
 *    Variables: @src, @dest
 *    Functions: getLF, setMemory, setZFlag, setLF
--- code ---
{
  lf = getLF ();
  if((lf == 1))
    {
      setMemory (@src, LONG, @dest);
    };
  setZFlag (!lf);
  setLF (0);
}
 */

int
arc2_gen_SCOND (DisasCtxt *ctx, TCGv src, TCGv dest)
{
  int ret = BS_NONE;
  TCGv lf = tcg_temp_local_new_i32();
  TCGv temp_1 = tcg_temp_local_new_i32();
  TCGv temp_2 = tcg_temp_local_new_i32();
  TCGv temp_3 = tcg_temp_local_new_i32();
  TCGv temp_4 = tcg_temp_local_new_i32();
  tcg_gen_mov_i32(lf, getLF());
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcondi_i32(TCG_COND_EQ, temp_1, lf, 1);
  tcg_gen_xori_i32(temp_2, temp_1, 1); tcg_gen_andi_i32(temp_2, temp_2, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, arc_true, done_1);;
  setMemory(src, LONG, dest);
  gen_set_label(done_1);
  tcg_gen_xori_i32(temp_3, lf, 1); tcg_gen_andi_i32(temp_3, temp_3, 1);;
  setZFlag(temp_3);
  tcg_gen_movi_i32(temp_4, 0);
  setLF(temp_4);
  tcg_temp_free(lf);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  tcg_temp_free(temp_3);
  tcg_temp_free(temp_4);

  return ret;
}





/* SCONDD
 *    Variables: @src, @dest
 *    Functions: getLF, setMemory, nextReg, setZFlag, setLF
--- code ---
{
  lf = getLF ();
  if((lf == 1))
    {
      setMemory (@src, LONG, @dest);
      pair = nextReg (dest);
      setMemory ((@src + 4), LONG, pair);
    };
  setZFlag (!lf);
  setLF (0);
}
 */

int
arc2_gen_SCONDD (DisasCtxt *ctx, TCGv src, TCGv dest)
{
  int ret = BS_NONE;
  TCGv lf = tcg_temp_local_new_i32();
  TCGv temp_1 = tcg_temp_local_new_i32();
  TCGv temp_2 = tcg_temp_local_new_i32();
  TCGv pair = tcg_temp_local_new_i32();
  TCGv temp_3 = tcg_temp_local_new_i32();
  TCGv temp_4 = tcg_temp_local_new_i32();
  TCGv temp_5 = tcg_temp_local_new_i32();
  tcg_gen_mov_i32(lf, getLF());
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcondi_i32(TCG_COND_EQ, temp_1, lf, 1);
  tcg_gen_xori_i32(temp_2, temp_1, 1); tcg_gen_andi_i32(temp_2, temp_2, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, arc_true, done_1);;
  setMemory(src, LONG, dest);
  pair = nextReg (dest);
  tcg_gen_addi_i32(temp_3, src, 4);
  setMemory(temp_3, LONG, pair);
  gen_set_label(done_1);
  tcg_gen_xori_i32(temp_4, lf, 1); tcg_gen_andi_i32(temp_4, temp_4, 1);;
  setZFlag(temp_4);
  tcg_gen_movi_i32(temp_5, 0);
  setLF(temp_5);
  tcg_temp_free(lf);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  tcg_temp_free(temp_3);
  tcg_temp_free(temp_4);
  tcg_temp_free(temp_5);

  return ret;
}





/* DMB
 *    Variables: @a
 *    Functions:
--- code ---
{
  @a = @a;
}
 */

int
arc2_gen_DMB (DisasCtxt *ctx, TCGv a)
{
  int ret = BS_NONE;

  return ret;
}





/* LD
 *    Variables: @src1, @src2, @dest
 *    Functions: getAAFlag, getZZFlag, setDebugLD, getMemory, getFlagX, SignExtend, NoFurtherLoadsPending
--- code ---
{
  AA = getAAFlag ();
  ZZ = getZZFlag ();
  address = 0;
  if(((AA == 0) || (AA == 1)))
    {
      address = (@src1 + @src2);
    };
  if((AA == 2))
    {
      address = @src1;
    };
  if(((AA == 3) && ((ZZ == 0) || (ZZ == 3))))
    {
      address = (@src1 + (@src2 << 2));
    };
  if(((AA == 3) && (ZZ == 2)))
    {
      address = (@src1 + (@src2 << 1));
    };
  if(((AA == 1) || (AA == 2)))
    {
      @src1 = (@src1 + @src2);
    };
  setDebugLD (1);
  @dest = getMemory (address, ZZ);
  if((getFlagX () == 1))
    {
      @dest = SignExtend (@dest, ZZ);
    };
  if(NoFurtherLoadsPending ())
    {
      setDebugLD (0);
    };
}
 */

int
arc2_gen_LD (DisasCtxt *ctx, TCGv src1, TCGv src2, TCGv dest)
{
  int ret = BS_NONE;
  int AA;
  int ZZ;
  TCGv address = tcg_temp_local_new_i32();
  TCGv temp_2 = tcg_temp_local_new_i32();
  TCGv temp_3 = tcg_temp_local_new_i32();
  TCGv temp_4 = tcg_temp_local_new_i32();
  TCGv temp_5 = NULL /* REFERENCE */;
  TCGv temp_1 = tcg_temp_local_new_i32();
  TCGv temp_6 = tcg_temp_local_new_i32();
  AA = getAAFlag ();
  ZZ = getZZFlag ();
  tcg_gen_movi_i32(address, 0);
  if (((AA == 0) || (AA == 1)))
    {
    tcg_gen_add_i32(address, src1, src2);
;
    }
  else
    {
  ;
    }
  if ((AA == 2))
    {
    tcg_gen_mov_i32(address, src1);
;
    }
  else
    {
  ;
    }
  if (((AA == 3) && ((ZZ == 0) || (ZZ == 3))))
    {
    tcg_gen_shli_i32(temp_2, src2, 2);
  tcg_gen_add_i32(address, src1, temp_2);
;
    }
  else
    {
  ;
    }
  if (((AA == 3) && (ZZ == 2)))
    {
    tcg_gen_shli_i32(temp_3, src2, 1);
  tcg_gen_add_i32(address, src1, temp_3);
;
    }
  else
    {
  ;
    }
  if (((AA == 1) || (AA == 2)))
    {
    tcg_gen_add_i32(src1, src1, src2);
;
    }
  else
    {
  ;
    }
  tcg_gen_movi_i32(temp_4, 1);
  setDebugLD(temp_4);
  temp_5 = getMemory(address, ZZ);
  tcg_gen_mov_i32(dest, temp_5);
  if ((getFlagX () == 1))
    {
    tcg_gen_mov_i32(dest, SignExtend(dest, ZZ));
;
    }
  else
    {
  ;
    }
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_xori_i32(temp_1, NoFurtherLoadsPending(), 1); tcg_gen_andi_i32(temp_1, temp_1, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_1, arc_true, done_1);;
  tcg_gen_movi_i32(temp_6, 0);
  setDebugLD(temp_6);
  gen_set_label(done_1);
  tcg_temp_free(address);
  tcg_temp_free(temp_2);
  tcg_temp_free(temp_3);
  tcg_temp_free(temp_4);
  if(temp_5 != NULL) tcg_temp_free(temp_5);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_6);

  return ret;
}





/* LDD
 *    Variables: @src1, @src2, @dest
 *    Functions: getAAFlag, getZZFlag, setDebugLD, getMemory, nextReg, NoFurtherLoadsPending
--- code ---
{
  AA = getAAFlag ();
  ZZ = getZZFlag ();
  address = 0;
  if(((AA == 0) || (AA == 1)))
    {
      address = (@src1 + @src2);
    };
  if((AA == 2))
    {
      address = @src1;
    };
  if(((AA == 3) && ((ZZ == 0) || (ZZ == 3))))
    {
      address = (@src1 + (@src2 << 2));
    };
  if(((AA == 3) && (ZZ == 2)))
    {
      address = (@src1 + (@src2 << 1));
    };
  if(((AA == 1) || (AA == 2)))
    {
      @src1 = (@src1 + @src2);
    };
  setDebugLD (1);
  @dest = getMemory (address, LONG);
  pair = nextReg (dest);
  pair = getMemory ((address + 4), LONG);
  if(NoFurtherLoadsPending ())
    {
      setDebugLD (0);
    };
}
 */

int
arc2_gen_LDD (DisasCtxt *ctx, TCGv src1, TCGv src2, TCGv dest)
{
  int ret = BS_NONE;
  int AA;
  int ZZ;
  TCGv address = tcg_temp_local_new_i32();
  TCGv temp_2 = tcg_temp_local_new_i32();
  TCGv temp_3 = tcg_temp_local_new_i32();
  TCGv temp_4 = tcg_temp_local_new_i32();
  TCGv temp_5 = NULL /* REFERENCE */;
  TCGv pair = tcg_temp_local_new_i32();
  TCGv temp_7 = tcg_temp_local_new_i32();
  TCGv temp_6 = NULL /* REFERENCE */;
  TCGv temp_1 = tcg_temp_local_new_i32();
  TCGv temp_8 = tcg_temp_local_new_i32();
  AA = getAAFlag ();
  ZZ = getZZFlag ();
  tcg_gen_movi_i32(address, 0);
  if (((AA == 0) || (AA == 1)))
    {
    tcg_gen_add_i32(address, src1, src2);
;
    }
  else
    {
  ;
    }
  if ((AA == 2))
    {
    tcg_gen_mov_i32(address, src1);
;
    }
  else
    {
  ;
    }
  if (((AA == 3) && ((ZZ == 0) || (ZZ == 3))))
    {
    tcg_gen_shli_i32(temp_2, src2, 2);
  tcg_gen_add_i32(address, src1, temp_2);
;
    }
  else
    {
  ;
    }
  if (((AA == 3) && (ZZ == 2)))
    {
    tcg_gen_shli_i32(temp_3, src2, 1);
  tcg_gen_add_i32(address, src1, temp_3);
;
    }
  else
    {
  ;
    }
  if (((AA == 1) || (AA == 2)))
    {
    tcg_gen_add_i32(src1, src1, src2);
;
    }
  else
    {
  ;
    }
  tcg_gen_movi_i32(temp_4, 1);
  setDebugLD(temp_4);
  temp_5 = getMemory(address, LONG);
  tcg_gen_mov_i32(dest, temp_5);
  pair = nextReg (dest);
  tcg_gen_addi_i32(temp_7, address, 4);
  temp_6 = getMemory(temp_7, LONG);
  tcg_gen_mov_i32(pair, temp_6);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_xori_i32(temp_1, NoFurtherLoadsPending(), 1); tcg_gen_andi_i32(temp_1, temp_1, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_1, arc_true, done_1);;
  tcg_gen_movi_i32(temp_8, 0);
  setDebugLD(temp_8);
  gen_set_label(done_1);
  tcg_temp_free(address);
  tcg_temp_free(temp_2);
  tcg_temp_free(temp_3);
  tcg_temp_free(temp_4);
  if(temp_5 != NULL) tcg_temp_free(temp_5);
  tcg_temp_free(temp_7);
  if(temp_6 != NULL) tcg_temp_free(temp_6);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_8);

  return ret;
}





/* ST
 *    Variables: @src1, @src2, @dest
 *    Functions: getAAFlag, getZZFlag, setMemory
--- code ---
{
  AA = getAAFlag ();
  ZZ = getZZFlag ();
  address = 0;
  if(((AA == 0) || (AA == 1)))
    {
      address = (@src1 + @src2);
    };
  if((AA == 2))
    {
      address = @src1;
    };
  if(((AA == 3) && ((ZZ == 0) || (ZZ == 3))))
    {
      address = (@src1 + (@src2 << 2));
    };
  if(((AA == 3) && (ZZ == 2)))
    {
      address = (@src1 + (@src2 << 1));
    };
  setMemory (address, ZZ, @dest);
  if(((AA == 1) || (AA == 2)))
    {
      @src1 = (@src1 + @src2);
    };
}
 */

int
arc2_gen_ST (DisasCtxt *ctx, TCGv src1, TCGv src2, TCGv dest)
{
  int ret = BS_NONE;
  int AA;
  int ZZ;
  TCGv address = tcg_temp_local_new_i32();
  TCGv temp_1 = tcg_temp_local_new_i32();
  TCGv temp_2 = tcg_temp_local_new_i32();
  AA = getAAFlag ();
  ZZ = getZZFlag ();
  tcg_gen_movi_i32(address, 0);
  if (((AA == 0) || (AA == 1)))
    {
    tcg_gen_add_i32(address, src1, src2);
;
    }
  else
    {
  ;
    }
  if ((AA == 2))
    {
    tcg_gen_mov_i32(address, src1);
;
    }
  else
    {
  ;
    }
  if (((AA == 3) && ((ZZ == 0) || (ZZ == 3))))
    {
    tcg_gen_shli_i32(temp_1, src2, 2);
  tcg_gen_add_i32(address, src1, temp_1);
;
    }
  else
    {
  ;
    }
  if (((AA == 3) && (ZZ == 2)))
    {
    tcg_gen_shli_i32(temp_2, src2, 1);
  tcg_gen_add_i32(address, src1, temp_2);
;
    }
  else
    {
  ;
    }
  setMemory(address, ZZ, dest);
  if (((AA == 1) || (AA == 2)))
    {
    tcg_gen_add_i32(src1, src1, src2);
;
    }
  else
    {
  ;
    }
  tcg_temp_free(address);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);

  return ret;
}





/* STD
 *    Variables: @src1, @src2, @dest
 *    Functions: getAAFlag, getZZFlag, setMemory, instructionHasRegisterOperandIn, nextReg, getBit
--- code ---
{
  AA = getAAFlag ();
  ZZ = getZZFlag ();
  address = 0;
  if(((AA == 0) || (AA == 1)))
    {
      address = (@src1 + @src2);
    };
  if((AA == 2))
    {
      address = @src1;
    };
  if(((AA == 3) && ((ZZ == 0) || (ZZ == 3))))
    {
      address = (@src1 + (@src2 << 2));
    };
  if(((AA == 3) && (ZZ == 2)))
    {
      address = (@src1 + (@src2 << 1));
    };
  setMemory (address, LONG, @dest);
  if(instructionHasRegisterOperandIn (0))
    {
      pair = nextReg (dest);
    }
  else
    {
      if((getBit (@dest, 31) == 1))
        {
          pair = 4294967295;
        }
      else
        {
          pair = 0;
        };
    };
  setMemory ((address + 4), LONG, pair);
  if(((AA == 1) || (AA == 2)))
    {
      @src1 = (@src1 + @src2);
    };
}
 */

int
arc2_gen_STD (DisasCtxt *ctx, TCGv src1, TCGv src2, TCGv dest)
{
  int ret = BS_NONE;
  int AA;
  int ZZ;
  TCGv address = tcg_temp_local_new_i32();
  TCGv temp_3 = tcg_temp_local_new_i32();
  TCGv temp_4 = tcg_temp_local_new_i32();
  TCGv pair = tcg_temp_local_new_i32();
  TCGv temp_6 = tcg_temp_local_new_i32();
  TCGv temp_5 = NULL /* REFERENCE */;
  TCGv temp_1 = tcg_temp_local_new_i32();
  TCGv temp_2 = tcg_temp_local_new_i32();
  TCGv temp_7 = tcg_temp_local_new_i32();
  AA = getAAFlag ();
  ZZ = getZZFlag ();
  tcg_gen_movi_i32(address, 0);
  if (((AA == 0) || (AA == 1)))
    {
    tcg_gen_add_i32(address, src1, src2);
;
    }
  else
    {
  ;
    }
  if ((AA == 2))
    {
    tcg_gen_mov_i32(address, src1);
;
    }
  else
    {
  ;
    }
  if (((AA == 3) && ((ZZ == 0) || (ZZ == 3))))
    {
    tcg_gen_shli_i32(temp_3, src2, 2);
  tcg_gen_add_i32(address, src1, temp_3);
;
    }
  else
    {
  ;
    }
  if (((AA == 3) && (ZZ == 2)))
    {
    tcg_gen_shli_i32(temp_4, src2, 1);
  tcg_gen_add_i32(address, src1, temp_4);
;
    }
  else
    {
  ;
    }
  setMemory(address, LONG, dest);
  if (instructionHasRegisterOperandIn (0))
    {
    pair = nextReg (dest);
;
    }
  else
    {
    TCGLabel *else_1 = gen_new_label();
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_movi_i32(temp_6, 31);
  temp_5 = getBit(dest, temp_6);
  tcg_gen_setcondi_i32(TCG_COND_EQ, temp_1, temp_5, 1);
  tcg_gen_xori_i32(temp_2, temp_1, 1); tcg_gen_andi_i32(temp_2, temp_2, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, arc_true, else_1);;
  tcg_gen_movi_i32(pair, 4294967295);
  tcg_gen_br(done_1);
  gen_set_label(else_1);
  tcg_gen_movi_i32(pair, 0);
  gen_set_label(done_1);
;
    }
  tcg_gen_addi_i32(temp_7, address, 4);
  setMemory(temp_7, LONG, pair);
  if (((AA == 1) || (AA == 2)))
    {
    tcg_gen_add_i32(src1, src1, src2);
;
    }
  else
    {
  ;
    }
  tcg_temp_free(address);
  tcg_temp_free(temp_3);
  tcg_temp_free(temp_4);
  tcg_temp_free(temp_6);
  if(temp_5 != NULL) tcg_temp_free(temp_5);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  tcg_temp_free(temp_7);

  return ret;
}





/* POP
 *    Variables: @dest
 *    Functions: getMemory, getRegister, setRegister
--- code ---
{
  @dest = getMemory (getRegister (R_SP), LONG);
  setRegister (R_SP, (getRegister (R_SP) + 4));
}
 */

int
arc2_gen_POP (DisasCtxt *ctx, TCGv dest)
{
  int ret = BS_NONE;
  TCGv temp_3 = NULL /* REFERENCE */;
  TCGv temp_2 = tcg_temp_local_new_i32();
  TCGv temp_1 = NULL /* REFERENCE */;
  TCGv temp_6 = NULL /* REFERENCE */;
  TCGv temp_5 = tcg_temp_local_new_i32();
  TCGv temp_4 = tcg_temp_local_new_i32();
  temp_3 = getRegister(R_SP);
  tcg_gen_mov_i32(temp_2, temp_3);
  temp_1 = getMemory(temp_2, LONG);
  tcg_gen_mov_i32(dest, temp_1);
  temp_6 = getRegister(R_SP);
  tcg_gen_mov_i32(temp_5, temp_6);
  tcg_gen_addi_i32(temp_4, temp_5, 4);
  setRegister(R_SP, temp_4);
  if(temp_3 != NULL) tcg_temp_free(temp_3);
  tcg_temp_free(temp_2);
  if(temp_1 != NULL) tcg_temp_free(temp_1);
  if(temp_6 != NULL) tcg_temp_free(temp_6);
  tcg_temp_free(temp_5);
  tcg_temp_free(temp_4);

  return ret;
}





/* PUSH
 *    Variables: @src
 *    Functions: setRegister, getRegister, setMemory
--- code ---
{
  setRegister (R_SP, (getRegister (R_SP) - 4));
  setMemory (getRegister (R_SP), LONG, @src);
}
 */

int
arc2_gen_PUSH (DisasCtxt *ctx, TCGv src)
{
  int ret = BS_NONE;
  TCGv temp_3 = NULL /* REFERENCE */;
  TCGv temp_2 = tcg_temp_local_new_i32();
  TCGv temp_1 = tcg_temp_local_new_i32();
  TCGv temp_5 = NULL /* REFERENCE */;
  TCGv temp_4 = tcg_temp_local_new_i32();
  temp_3 = getRegister(R_SP);
  tcg_gen_mov_i32(temp_2, temp_3);
  tcg_gen_subi_i32(temp_1, temp_2, 4);
  setRegister(R_SP, temp_1);
  temp_5 = getRegister(R_SP);
  tcg_gen_mov_i32(temp_4, temp_5);
  setMemory(temp_4, LONG, src);
  if(temp_3 != NULL) tcg_temp_free(temp_3);
  tcg_temp_free(temp_2);
  tcg_temp_free(temp_1);
  if(temp_5 != NULL) tcg_temp_free(temp_5);
  tcg_temp_free(temp_4);

  return ret;
}





/* LP
 *    Variables: @rd
 *    Functions: getCCFlag, writeAuxReg, getRegIndex, nextInsnAddress, getPCL, setPC
--- code ---
{
  if((getCCFlag () == true))
    {
      writeAuxReg (getRegIndex (LP_START), nextInsnAddress ());
      writeAuxReg (getRegIndex (LP_END), (getPCL () + @rd));
    }
  else
    {
      setPC ((getPCL () + @rd));
    };
}
 */

int
arc2_gen_LP (DisasCtxt *ctx, TCGv rd)
{
  int ret = BS_NONE;
  TCGv temp_3 = NULL /* REFERENCE */;
  TCGv temp_1 = tcg_temp_local_new_i32();
  TCGv temp_2 = tcg_temp_local_new_i32();
  TCGv temp_5 = NULL /* REFERENCE */;
  TCGv temp_4 = tcg_temp_local_new_i32();
  TCGv temp_7 = NULL /* REFERENCE */;
  TCGv temp_6 = tcg_temp_local_new_i32();
  TCGv temp_9 = NULL /* REFERENCE */;
  TCGv temp_8 = tcg_temp_local_new_i32();
  TCGv temp_12 = NULL /* REFERENCE */;
  TCGv temp_11 = tcg_temp_local_new_i32();
  TCGv temp_10 = tcg_temp_local_new_i32();
  TCGv temp_15 = NULL /* REFERENCE */;
  TCGv temp_14 = tcg_temp_local_new_i32();
  TCGv temp_13 = tcg_temp_local_new_i32();
  TCGLabel *else_1 = gen_new_label();
  TCGLabel *done_1 = gen_new_label();
  temp_3 = getCCFlag();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, temp_3, arc_true);
  tcg_gen_xori_i32(temp_2, temp_1, 1); tcg_gen_andi_i32(temp_2, temp_2, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, arc_true, else_1);;
  temp_5 = getRegIndex(LP_START);
  tcg_gen_mov_i32(temp_4, temp_5);
  temp_7 = nextInsnAddress();
  tcg_gen_mov_i32(temp_6, temp_7);
  writeAuxReg(temp_4, temp_6);
  temp_9 = getRegIndex(LP_END);
  tcg_gen_mov_i32(temp_8, temp_9);
  temp_12 = getPCL();
  tcg_gen_mov_i32(temp_11, temp_12);
  tcg_gen_add_i32(temp_10, temp_11, rd);
  writeAuxReg(temp_8, temp_10);
  tcg_gen_br(done_1);
  gen_set_label(else_1);
  temp_15 = getPCL();
  tcg_gen_mov_i32(temp_14, temp_15);
  tcg_gen_add_i32(temp_13, temp_14, rd);
  setPC(temp_13);
  gen_set_label(done_1);
  if(temp_3 != NULL) tcg_temp_free(temp_3);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  if(temp_5 != NULL) tcg_temp_free(temp_5);
  tcg_temp_free(temp_4);
  if(temp_7 != NULL) tcg_temp_free(temp_7);
  tcg_temp_free(temp_6);
  if(temp_9 != NULL) tcg_temp_free(temp_9);
  tcg_temp_free(temp_8);
  if(temp_12 != NULL) tcg_temp_free(temp_12);
  tcg_temp_free(temp_11);
  tcg_temp_free(temp_10);
  if(temp_15 != NULL) tcg_temp_free(temp_15);
  tcg_temp_free(temp_14);
  tcg_temp_free(temp_13);

  return ret;
}





/* NORM
 *    Variables: @src, @dest
 *    Functions: HELPER, getFFlag, setZFlag, setNFlag
--- code ---
{
  psrc = @src;
  i = HELPER (norm, psrc);
  @dest = (31 - i);
  if((getFFlag () == true))
    {
      setZFlag (psrc);
      setNFlag (psrc);
    };
}
 */

int
arc2_gen_NORM (DisasCtxt *ctx, TCGv src, TCGv dest)
{
  int ret = BS_NONE;
  TCGv psrc = tcg_temp_local_new_i32();
  TCGv i = tcg_temp_local_new_i32();
  TCGv temp_3 = NULL /* REFERENCE */;
  TCGv temp_1 = tcg_temp_local_new_i32();
  TCGv temp_2 = tcg_temp_local_new_i32();
  tcg_gen_mov_i32(psrc, src);
  ARC_HELPER(norm, i, psrc);
  tcg_gen_subfi_i32(dest, 31, i);
  TCGLabel *done_1 = gen_new_label();
  temp_3 = getFFlag();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, temp_3, arc_true);
  tcg_gen_xori_i32(temp_2, temp_1, 1); tcg_gen_andi_i32(temp_2, temp_2, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, arc_true, done_1);;
  setZFlag(psrc);
  setNFlag(psrc);
  gen_set_label(done_1);
  tcg_temp_free(psrc);
  tcg_temp_free(i);
  if(temp_3 != NULL) tcg_temp_free(temp_3);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);

  return ret;
}





/* NORMH
 *    Variables: @src, @dest
 *    Functions: HELPER, getFFlag, setZFlag, setNFlag
--- code ---
{
  lsrc = (@src & 65535);
  i = HELPER (normh, lsrc);
  @dest = (15 - i);
  if((getFFlag () == true))
    {
      setZFlag (lsrc);
      setNFlag (lsrc);
    };
}
 */

int
arc2_gen_NORMH (DisasCtxt *ctx, TCGv src, TCGv dest)
{
  int ret = BS_NONE;
  TCGv lsrc = tcg_temp_local_new_i32();
  TCGv i = tcg_temp_local_new_i32();
  TCGv temp_3 = NULL /* REFERENCE */;
  TCGv temp_1 = tcg_temp_local_new_i32();
  TCGv temp_2 = tcg_temp_local_new_i32();
  tcg_gen_andi_i32(lsrc, src, 65535);
  ARC_HELPER(normh, i, lsrc);
  tcg_gen_subfi_i32(dest, 15, i);
  TCGLabel *done_1 = gen_new_label();
  temp_3 = getFFlag();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, temp_3, arc_true);
  tcg_gen_xori_i32(temp_2, temp_1, 1); tcg_gen_andi_i32(temp_2, temp_2, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, arc_true, done_1);;
  setZFlag(lsrc);
  setNFlag(lsrc);
  gen_set_label(done_1);
  tcg_temp_free(lsrc);
  tcg_temp_free(i);
  if(temp_3 != NULL) tcg_temp_free(temp_3);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);

  return ret;
}





/* FLS
 *    Variables: @src, @dest
 *    Functions: HELPER, getFFlag, setZFlag, setNFlag
--- code ---
{
  psrc = @src;
  @dest = HELPER (fls, psrc);
  if((getFFlag () == true))
    {
      setZFlag (psrc);
      setNFlag (psrc);
    };
}
 */

int
arc2_gen_FLS (DisasCtxt *ctx, TCGv src, TCGv dest)
{
  int ret = BS_NONE;
  TCGv psrc = tcg_temp_local_new_i32();
  TCGv temp_3 = NULL /* REFERENCE */;
  TCGv temp_1 = tcg_temp_local_new_i32();
  TCGv temp_2 = tcg_temp_local_new_i32();
  tcg_gen_mov_i32(psrc, src);
  ARC_HELPER(fls, dest, psrc);
  TCGLabel *done_1 = gen_new_label();
  temp_3 = getFFlag();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, temp_3, arc_true);
  tcg_gen_xori_i32(temp_2, temp_1, 1); tcg_gen_andi_i32(temp_2, temp_2, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, arc_true, done_1);;
  setZFlag(psrc);
  setNFlag(psrc);
  gen_set_label(done_1);
  tcg_temp_free(psrc);
  if(temp_3 != NULL) tcg_temp_free(temp_3);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);

  return ret;
}





/* FFS
 *    Variables: @src, @dest
 *    Functions: HELPER, getFFlag, setZFlag, setNFlag
--- code ---
{
  psrc = @src;
  @dest = HELPER (ffs, psrc);
  if((getFFlag () == true))
    {
      setZFlag (psrc);
      setNFlag (psrc);
    };
}
 */

int
arc2_gen_FFS (DisasCtxt *ctx, TCGv src, TCGv dest)
{
  int ret = BS_NONE;
  TCGv psrc = tcg_temp_local_new_i32();
  TCGv temp_3 = NULL /* REFERENCE */;
  TCGv temp_1 = tcg_temp_local_new_i32();
  TCGv temp_2 = tcg_temp_local_new_i32();
  tcg_gen_mov_i32(psrc, src);
  ARC_HELPER(ffs, dest, psrc);
  TCGLabel *done_1 = gen_new_label();
  temp_3 = getFFlag();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, temp_3, arc_true);
  tcg_gen_xori_i32(temp_2, temp_1, 1); tcg_gen_andi_i32(temp_2, temp_2, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, arc_true, done_1);;
  setZFlag(psrc);
  setNFlag(psrc);
  gen_set_label(done_1);
  tcg_temp_free(psrc);
  if(temp_3 != NULL) tcg_temp_free(temp_3);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);

  return ret;
}
