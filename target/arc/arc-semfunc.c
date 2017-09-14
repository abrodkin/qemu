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




/* ADD
 *    Variables: @a, @b, @c
 *    Functions: getCCFlag, getFFlag, setZFlag, setNFlag, setCFlag, CarryADD, setVFlag, OverflowADD
--- code ---
{
  if((getCCFlag () == true))
    {
      @a = (@b + @c);
      if((getFFlag () == true))
        {
          setZFlag (@a);
          setNFlag (@a);
          setCFlag (CarryADD (@a, @b, @c));
          setVFlag (OverflowADD (@a, @b, @c));
        };
    };
}
 */

int
arc2_gen_ADD (DisasCtxt *ctx, TCGv a, TCGv b, TCGv c)
{
  int ret = BS_NONE;
  TCGLabel *done_1 = gen_new_label();
  TCGv temp_1 = tcg_temp_local_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, getCCFlag(), arc_true);
  TCGv temp_2 = tcg_temp_local_new_i32();
  tcg_gen_xori_i32(temp_2, temp_1, 1); tcg_gen_andi_i32(temp_2, temp_2, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, arc_true, done_1);;
  tcg_gen_add_i32(a, b, c);
  TCGLabel *done_2 = gen_new_label();
  TCGv temp_3 = tcg_temp_local_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_3, getFFlag(), arc_true);
  TCGv temp_4 = tcg_temp_local_new_i32();
  tcg_gen_xori_i32(temp_4, temp_3, 1); tcg_gen_andi_i32(temp_4, temp_4, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_4, arc_true, done_2);;
  setZFlag(a);
  setNFlag(a);
  TCGv temp_5 = tcg_temp_local_new_i32();
  tcg_gen_mov_i32(temp_5, CarryADD(a, b, c));
  setCFlag(temp_5);
  TCGv temp_6 = tcg_temp_local_new_i32();
  tcg_gen_mov_i32(temp_6, OverflowADD(a, b, c));
  setVFlag(temp_6);
  gen_set_label(done_2);
  gen_set_label(done_1);

  return ret;
}





/* ADD1
 *    Variables: @a, @b, @c
 *    Functions: getCCFlag, getFFlag, setZFlag, setNFlag, setCFlag, CarryADD, setVFlag, OverflowADD
--- code ---
{
  if((getCCFlag () == true))
    {
      @a = (@b + (@c << 1));
      if((getFFlag () == true))
        {
          setZFlag (@a);
          setNFlag (@a);
          setCFlag (CarryADD (@a, @b, @c));
          setVFlag (OverflowADD (@a, @b, @c));
        };
    };
}
 */

int
arc2_gen_ADD1 (DisasCtxt *ctx, TCGv a, TCGv b, TCGv c)
{
  int ret = BS_NONE;
  TCGLabel *done_1 = gen_new_label();
  TCGv temp_1 = tcg_temp_local_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, getCCFlag(), arc_true);
  TCGv temp_2 = tcg_temp_local_new_i32();
  tcg_gen_xori_i32(temp_2, temp_1, 1); tcg_gen_andi_i32(temp_2, temp_2, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, arc_true, done_1);;
  TCGv temp_5 = tcg_temp_local_new_i32();
  tcg_gen_shli_i32(temp_5, c, 1);
  tcg_gen_add_i32(a, b, temp_5);
  TCGLabel *done_2 = gen_new_label();
  TCGv temp_3 = tcg_temp_local_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_3, getFFlag(), arc_true);
  TCGv temp_4 = tcg_temp_local_new_i32();
  tcg_gen_xori_i32(temp_4, temp_3, 1); tcg_gen_andi_i32(temp_4, temp_4, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_4, arc_true, done_2);;
  setZFlag(a);
  setNFlag(a);
  TCGv temp_6 = tcg_temp_local_new_i32();
  tcg_gen_mov_i32(temp_6, CarryADD(a, b, c));
  setCFlag(temp_6);
  TCGv temp_7 = tcg_temp_local_new_i32();
  tcg_gen_mov_i32(temp_7, OverflowADD(a, b, c));
  setVFlag(temp_7);
  gen_set_label(done_2);
  gen_set_label(done_1);

  return ret;
}





/* ADD2
 *    Variables: @a, @b, @c
 *    Functions: getCCFlag, getFFlag, setZFlag, setNFlag, setCFlag, CarryADD, setVFlag, OverflowADD
--- code ---
{
  if((getCCFlag () == true))
    {
      @a = (@b + (@c << 2));
      if((getFFlag () == true))
        {
          setZFlag (@a);
          setNFlag (@a);
          setCFlag (CarryADD (@a, @b, @c));
          setVFlag (OverflowADD (@a, @b, @c));
        };
    };
}
 */

int
arc2_gen_ADD2 (DisasCtxt *ctx, TCGv a, TCGv b, TCGv c)
{
  int ret = BS_NONE;
  TCGLabel *done_1 = gen_new_label();
  TCGv temp_1 = tcg_temp_local_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, getCCFlag(), arc_true);
  TCGv temp_2 = tcg_temp_local_new_i32();
  tcg_gen_xori_i32(temp_2, temp_1, 1); tcg_gen_andi_i32(temp_2, temp_2, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, arc_true, done_1);;
  TCGv temp_5 = tcg_temp_local_new_i32();
  tcg_gen_shli_i32(temp_5, c, 2);
  tcg_gen_add_i32(a, b, temp_5);
  TCGLabel *done_2 = gen_new_label();
  TCGv temp_3 = tcg_temp_local_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_3, getFFlag(), arc_true);
  TCGv temp_4 = tcg_temp_local_new_i32();
  tcg_gen_xori_i32(temp_4, temp_3, 1); tcg_gen_andi_i32(temp_4, temp_4, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_4, arc_true, done_2);;
  setZFlag(a);
  setNFlag(a);
  TCGv temp_6 = tcg_temp_local_new_i32();
  tcg_gen_mov_i32(temp_6, CarryADD(a, b, c));
  setCFlag(temp_6);
  TCGv temp_7 = tcg_temp_local_new_i32();
  tcg_gen_mov_i32(temp_7, OverflowADD(a, b, c));
  setVFlag(temp_7);
  gen_set_label(done_2);
  gen_set_label(done_1);

  return ret;
}





/* ADD3
 *    Variables: @a, @b, @c
 *    Functions: getCCFlag, getFFlag, setZFlag, setNFlag, setCFlag, CarryADD, setVFlag, OverflowADD
--- code ---
{
  if((getCCFlag () == true))
    {
      @a = (@b + (@c << 3));
      if((getFFlag () == true))
        {
          setZFlag (@a);
          setNFlag (@a);
          setCFlag (CarryADD (@a, @b, @c));
          setVFlag (OverflowADD (@a, @b, @c));
        };
    };
}
 */

int
arc2_gen_ADD3 (DisasCtxt *ctx, TCGv a, TCGv b, TCGv c)
{
  int ret = BS_NONE;
  TCGLabel *done_1 = gen_new_label();
  TCGv temp_1 = tcg_temp_local_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, getCCFlag(), arc_true);
  TCGv temp_2 = tcg_temp_local_new_i32();
  tcg_gen_xori_i32(temp_2, temp_1, 1); tcg_gen_andi_i32(temp_2, temp_2, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, arc_true, done_1);;
  TCGv temp_5 = tcg_temp_local_new_i32();
  tcg_gen_shli_i32(temp_5, c, 3);
  tcg_gen_add_i32(a, b, temp_5);
  TCGLabel *done_2 = gen_new_label();
  TCGv temp_3 = tcg_temp_local_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_3, getFFlag(), arc_true);
  TCGv temp_4 = tcg_temp_local_new_i32();
  tcg_gen_xori_i32(temp_4, temp_3, 1); tcg_gen_andi_i32(temp_4, temp_4, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_4, arc_true, done_2);;
  setZFlag(a);
  setNFlag(a);
  TCGv temp_6 = tcg_temp_local_new_i32();
  tcg_gen_mov_i32(temp_6, CarryADD(a, b, c));
  setCFlag(temp_6);
  TCGv temp_7 = tcg_temp_local_new_i32();
  tcg_gen_mov_i32(temp_7, OverflowADD(a, b, c));
  setVFlag(temp_7);
  gen_set_label(done_2);
  gen_set_label(done_1);

  return ret;
}





/* ADC
 *    Variables: @a, @b, @c
 *    Functions: getCCFlag, getCFlag, getFFlag, setZFlag, setNFlag, setCFlag, CarryADD, setVFlag, OverflowADD
--- code ---
{
  if((getCCFlag () == true))
    {
      @a = ((@b + @c) + getCFlag ());
      if((getFFlag () == true))
        {
          setZFlag (@a);
          setNFlag (@a);
          setCFlag (CarryADD (@a, @b, @c));
          setVFlag (OverflowADD (@a, @b, @c));
        };
    };
}
 */

int
arc2_gen_ADC (DisasCtxt *ctx, TCGv a, TCGv b, TCGv c)
{
  int ret = BS_NONE;
  TCGLabel *done_1 = gen_new_label();
  TCGv temp_1 = tcg_temp_local_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, getCCFlag(), arc_true);
  TCGv temp_2 = tcg_temp_local_new_i32();
  tcg_gen_xori_i32(temp_2, temp_1, 1); tcg_gen_andi_i32(temp_2, temp_2, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, arc_true, done_1);;
  TCGv temp_6 = tcg_temp_local_new_i32();
  tcg_gen_mov_i32(temp_6, getCFlag());
  TCGv temp_5 = tcg_temp_local_new_i32();
  tcg_gen_add_i32(temp_5, b, c);
  tcg_gen_add_i32(a, temp_5, temp_6);
  TCGLabel *done_2 = gen_new_label();
  TCGv temp_3 = tcg_temp_local_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_3, getFFlag(), arc_true);
  TCGv temp_4 = tcg_temp_local_new_i32();
  tcg_gen_xori_i32(temp_4, temp_3, 1); tcg_gen_andi_i32(temp_4, temp_4, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_4, arc_true, done_2);;
  setZFlag(a);
  setNFlag(a);
  TCGv temp_7 = tcg_temp_local_new_i32();
  tcg_gen_mov_i32(temp_7, CarryADD(a, b, c));
  setCFlag(temp_7);
  TCGv temp_8 = tcg_temp_local_new_i32();
  tcg_gen_mov_i32(temp_8, OverflowADD(a, b, c));
  setVFlag(temp_8);
  gen_set_label(done_2);
  gen_set_label(done_1);

  return ret;
}





/* SBC
 *    Variables: @a, @b, @c
 *    Functions: getCCFlag, getCFlag, getFFlag, setZFlag, setNFlag, setCFlag, CarryADD, setVFlag, OverflowADD
--- code ---
{
  if((getCCFlag () == true))
    {
      @a = ((@b - @c) - getCFlag ());
      if((getFFlag () == true))
        {
          setZFlag (@a);
          setNFlag (@a);
          setCFlag (CarryADD (@a, @b, @c));
          setVFlag (OverflowADD (@a, @b, @c));
        };
    };
}
 */

int
arc2_gen_SBC (DisasCtxt *ctx, TCGv a, TCGv b, TCGv c)
{
  int ret = BS_NONE;
  TCGLabel *done_1 = gen_new_label();
  TCGv temp_1 = tcg_temp_local_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, getCCFlag(), arc_true);
  TCGv temp_2 = tcg_temp_local_new_i32();
  tcg_gen_xori_i32(temp_2, temp_1, 1); tcg_gen_andi_i32(temp_2, temp_2, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, arc_true, done_1);;
  TCGv temp_6 = tcg_temp_local_new_i32();
  tcg_gen_mov_i32(temp_6, getCFlag());
  TCGv temp_5 = tcg_temp_local_new_i32();
  tcg_gen_sub_i32(temp_5, b, c);
  tcg_gen_sub_i32(a, temp_5, temp_6);
  TCGLabel *done_2 = gen_new_label();
  TCGv temp_3 = tcg_temp_local_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_3, getFFlag(), arc_true);
  TCGv temp_4 = tcg_temp_local_new_i32();
  tcg_gen_xori_i32(temp_4, temp_3, 1); tcg_gen_andi_i32(temp_4, temp_4, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_4, arc_true, done_2);;
  setZFlag(a);
  setNFlag(a);
  TCGv temp_7 = tcg_temp_local_new_i32();
  tcg_gen_mov_i32(temp_7, CarryADD(a, b, c));
  setCFlag(temp_7);
  TCGv temp_8 = tcg_temp_local_new_i32();
  tcg_gen_mov_i32(temp_8, OverflowADD(a, b, c));
  setVFlag(temp_8);
  gen_set_label(done_2);
  gen_set_label(done_1);

  return ret;
}





/* SUB
 *    Variables: @a, @b, @c
 *    Functions: getCCFlag, getFFlag, setZFlag, setNFlag, setCFlag, CarrySUB, setVFlag, OverflowSUB
--- code ---
{
  if((getCCFlag () == true))
    {
      @a = (@b - @c);
      if((getFFlag () == true))
        {
          setZFlag (@a);
          setNFlag (@a);
          setCFlag (CarrySUB (@a, @b, @c));
          setVFlag (OverflowSUB (@a, @b, @c));
        };
    };
}
 */

int
arc2_gen_SUB (DisasCtxt *ctx, TCGv a, TCGv b, TCGv c)
{
  int ret = BS_NONE;
  TCGLabel *done_1 = gen_new_label();
  TCGv temp_1 = tcg_temp_local_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, getCCFlag(), arc_true);
  TCGv temp_2 = tcg_temp_local_new_i32();
  tcg_gen_xori_i32(temp_2, temp_1, 1); tcg_gen_andi_i32(temp_2, temp_2, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, arc_true, done_1);;
  tcg_gen_sub_i32(a, b, c);
  TCGLabel *done_2 = gen_new_label();
  TCGv temp_3 = tcg_temp_local_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_3, getFFlag(), arc_true);
  TCGv temp_4 = tcg_temp_local_new_i32();
  tcg_gen_xori_i32(temp_4, temp_3, 1); tcg_gen_andi_i32(temp_4, temp_4, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_4, arc_true, done_2);;
  setZFlag(a);
  setNFlag(a);
  TCGv temp_5 = tcg_temp_local_new_i32();
  tcg_gen_mov_i32(temp_5, CarrySUB(a, b, c));
  setCFlag(temp_5);
  TCGv temp_6 = tcg_temp_local_new_i32();
  tcg_gen_mov_i32(temp_6, OverflowSUB(a, b, c));
  setVFlag(temp_6);
  gen_set_label(done_2);
  gen_set_label(done_1);

  return ret;
}





/* SUB1
 *    Variables: @a, @b, @c
 *    Functions: getCCFlag, getFFlag, setZFlag, setNFlag, setCFlag, CarrySUB, setVFlag, OverflowSUB
--- code ---
{
  if((getCCFlag () == true))
    {
      @a = (@b - (@c << 1));
      if((getFFlag () == true))
        {
          setZFlag (@a);
          setNFlag (@a);
          setCFlag (CarrySUB (@a, @b, @c));
          setVFlag (OverflowSUB (@a, @b, @c));
        };
    };
}
 */

int
arc2_gen_SUB1 (DisasCtxt *ctx, TCGv a, TCGv b, TCGv c)
{
  int ret = BS_NONE;
  TCGLabel *done_1 = gen_new_label();
  TCGv temp_1 = tcg_temp_local_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, getCCFlag(), arc_true);
  TCGv temp_2 = tcg_temp_local_new_i32();
  tcg_gen_xori_i32(temp_2, temp_1, 1); tcg_gen_andi_i32(temp_2, temp_2, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, arc_true, done_1);;
  TCGv temp_5 = tcg_temp_local_new_i32();
  tcg_gen_shli_i32(temp_5, c, 1);
  tcg_gen_sub_i32(a, b, temp_5);
  TCGLabel *done_2 = gen_new_label();
  TCGv temp_3 = tcg_temp_local_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_3, getFFlag(), arc_true);
  TCGv temp_4 = tcg_temp_local_new_i32();
  tcg_gen_xori_i32(temp_4, temp_3, 1); tcg_gen_andi_i32(temp_4, temp_4, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_4, arc_true, done_2);;
  setZFlag(a);
  setNFlag(a);
  TCGv temp_6 = tcg_temp_local_new_i32();
  tcg_gen_mov_i32(temp_6, CarrySUB(a, b, c));
  setCFlag(temp_6);
  TCGv temp_7 = tcg_temp_local_new_i32();
  tcg_gen_mov_i32(temp_7, OverflowSUB(a, b, c));
  setVFlag(temp_7);
  gen_set_label(done_2);
  gen_set_label(done_1);

  return ret;
}





/* SUB2
 *    Variables: @a, @b, @c
 *    Functions: getCCFlag, getFFlag, setZFlag, setNFlag, setCFlag, CarrySUB, setVFlag, OverflowSUB
--- code ---
{
  if((getCCFlag () == true))
    {
      @a = (@b - (@c << 2));
      if((getFFlag () == true))
        {
          setZFlag (@a);
          setNFlag (@a);
          setCFlag (CarrySUB (@a, @b, @c));
          setVFlag (OverflowSUB (@a, @b, @c));
        };
    };
}
 */

int
arc2_gen_SUB2 (DisasCtxt *ctx, TCGv a, TCGv b, TCGv c)
{
  int ret = BS_NONE;
  TCGLabel *done_1 = gen_new_label();
  TCGv temp_1 = tcg_temp_local_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, getCCFlag(), arc_true);
  TCGv temp_2 = tcg_temp_local_new_i32();
  tcg_gen_xori_i32(temp_2, temp_1, 1); tcg_gen_andi_i32(temp_2, temp_2, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, arc_true, done_1);;
  TCGv temp_5 = tcg_temp_local_new_i32();
  tcg_gen_shli_i32(temp_5, c, 2);
  tcg_gen_sub_i32(a, b, temp_5);
  TCGLabel *done_2 = gen_new_label();
  TCGv temp_3 = tcg_temp_local_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_3, getFFlag(), arc_true);
  TCGv temp_4 = tcg_temp_local_new_i32();
  tcg_gen_xori_i32(temp_4, temp_3, 1); tcg_gen_andi_i32(temp_4, temp_4, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_4, arc_true, done_2);;
  setZFlag(a);
  setNFlag(a);
  TCGv temp_6 = tcg_temp_local_new_i32();
  tcg_gen_mov_i32(temp_6, CarrySUB(a, b, c));
  setCFlag(temp_6);
  TCGv temp_7 = tcg_temp_local_new_i32();
  tcg_gen_mov_i32(temp_7, OverflowSUB(a, b, c));
  setVFlag(temp_7);
  gen_set_label(done_2);
  gen_set_label(done_1);

  return ret;
}





/* SUB3
 *    Variables: @a, @b, @c
 *    Functions: getCCFlag, getFFlag, setZFlag, setNFlag, setCFlag, CarrySUB, setVFlag, OverflowSUB
--- code ---
{
  if((getCCFlag () == true))
    {
      @a = (@b - (@c << 3));
      if((getFFlag () == true))
        {
          setZFlag (@a);
          setNFlag (@a);
          setCFlag (CarrySUB (@a, @b, @c));
          setVFlag (OverflowSUB (@a, @b, @c));
        };
    };
}
 */

int
arc2_gen_SUB3 (DisasCtxt *ctx, TCGv a, TCGv b, TCGv c)
{
  int ret = BS_NONE;
  TCGLabel *done_1 = gen_new_label();
  TCGv temp_1 = tcg_temp_local_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, getCCFlag(), arc_true);
  TCGv temp_2 = tcg_temp_local_new_i32();
  tcg_gen_xori_i32(temp_2, temp_1, 1); tcg_gen_andi_i32(temp_2, temp_2, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, arc_true, done_1);;
  TCGv temp_5 = tcg_temp_local_new_i32();
  tcg_gen_shli_i32(temp_5, c, 3);
  tcg_gen_sub_i32(a, b, temp_5);
  TCGLabel *done_2 = gen_new_label();
  TCGv temp_3 = tcg_temp_local_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_3, getFFlag(), arc_true);
  TCGv temp_4 = tcg_temp_local_new_i32();
  tcg_gen_xori_i32(temp_4, temp_3, 1); tcg_gen_andi_i32(temp_4, temp_4, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_4, arc_true, done_2);;
  setZFlag(a);
  setNFlag(a);
  TCGv temp_6 = tcg_temp_local_new_i32();
  tcg_gen_mov_i32(temp_6, CarrySUB(a, b, c));
  setCFlag(temp_6);
  TCGv temp_7 = tcg_temp_local_new_i32();
  tcg_gen_mov_i32(temp_7, OverflowSUB(a, b, c));
  setVFlag(temp_7);
  gen_set_label(done_2);
  gen_set_label(done_1);

  return ret;
}





/* MAX
 *    Variables: @b, @c, @a
 *    Functions: getCCFlag, getFFlag, setZFlag, setNFlag, setCFlag, CarrySUB, setVFlag, OverflowSUB
--- code ---
{
  if((getCCFlag () == true))
    {
      alu = (@b - @c);
      if((@c >= @b))
        {
          @a = @c;
        }
      else
        {
          @a = @b;
        };
      if((getFFlag () == true))
        {
          setZFlag (alu);
          setNFlag (alu);
          setCFlag (CarrySUB (@a, @b, @c));
          setVFlag (OverflowSUB (@a, @b, @c));
        };
    };
}
 */

int
arc2_gen_MAX (DisasCtxt *ctx, TCGv b, TCGv c, TCGv a)
{
  int ret = BS_NONE;
  TCGLabel *done_1 = gen_new_label();
  TCGv temp_1 = tcg_temp_local_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, getCCFlag(), arc_true);
  TCGv temp_2 = tcg_temp_local_new_i32();
  tcg_gen_xori_i32(temp_2, temp_1, 1); tcg_gen_andi_i32(temp_2, temp_2, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, arc_true, done_1);;
  TCGv alu = tcg_temp_local_new_i32();
  tcg_gen_sub_i32(alu, b, c);
  TCGLabel *else_2 = gen_new_label();
  TCGLabel *done_2 = gen_new_label();
  TCGv temp_3 = tcg_temp_local_new_i32();
  tcg_gen_setcond_i32(TCG_COND_GE, temp_3, c, b);
  TCGv temp_4 = tcg_temp_local_new_i32();
  tcg_gen_xori_i32(temp_4, temp_3, 1); tcg_gen_andi_i32(temp_4, temp_4, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_4, arc_true, else_2);;
  tcg_gen_mov_i32(a, c);
  tcg_gen_br(done_2);
  gen_set_label(else_2);
  tcg_gen_mov_i32(a, b);
  gen_set_label(done_2);
  TCGLabel *done_3 = gen_new_label();
  TCGv temp_5 = tcg_temp_local_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_5, getFFlag(), arc_true);
  TCGv temp_6 = tcg_temp_local_new_i32();
  tcg_gen_xori_i32(temp_6, temp_5, 1); tcg_gen_andi_i32(temp_6, temp_6, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_6, arc_true, done_3);;
  setZFlag(alu);
  setNFlag(alu);
  TCGv temp_7 = tcg_temp_local_new_i32();
  tcg_gen_mov_i32(temp_7, CarrySUB(a, b, c));
  setCFlag(temp_7);
  TCGv temp_8 = tcg_temp_local_new_i32();
  tcg_gen_mov_i32(temp_8, OverflowSUB(a, b, c));
  setVFlag(temp_8);
  gen_set_label(done_3);
  gen_set_label(done_1);

  return ret;
}





/* MIN
 *    Variables: @b, @c, @a
 *    Functions: getCCFlag, getFFlag, setZFlag, setNFlag, setCFlag, CarrySUB, setVFlag, OverflowSUB
--- code ---
{
  if((getCCFlag () == true))
    {
      alu = (@b - @c);
      if((@c <= @b))
        {
          @a = @c;
        }
      else
        {
          @a = @b;
        };
      if((getFFlag () == true))
        {
          setZFlag (alu);
          setNFlag (alu);
          setCFlag (CarrySUB (@a, @b, @c));
          setVFlag (OverflowSUB (@a, @b, @c));
        };
    };
}
 */

int
arc2_gen_MIN (DisasCtxt *ctx, TCGv b, TCGv c, TCGv a)
{
  int ret = BS_NONE;
  TCGLabel *done_1 = gen_new_label();
  TCGv temp_1 = tcg_temp_local_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, getCCFlag(), arc_true);
  TCGv temp_2 = tcg_temp_local_new_i32();
  tcg_gen_xori_i32(temp_2, temp_1, 1); tcg_gen_andi_i32(temp_2, temp_2, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, arc_true, done_1);;
  TCGv alu = tcg_temp_local_new_i32();
  tcg_gen_sub_i32(alu, b, c);
  TCGLabel *else_2 = gen_new_label();
  TCGLabel *done_2 = gen_new_label();
  TCGv temp_3 = tcg_temp_local_new_i32();
  tcg_gen_setcond_i32(TCG_COND_LE, temp_3, c, b);
  TCGv temp_4 = tcg_temp_local_new_i32();
  tcg_gen_xori_i32(temp_4, temp_3, 1); tcg_gen_andi_i32(temp_4, temp_4, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_4, arc_true, else_2);;
  tcg_gen_mov_i32(a, c);
  tcg_gen_br(done_2);
  gen_set_label(else_2);
  tcg_gen_mov_i32(a, b);
  gen_set_label(done_2);
  TCGLabel *done_3 = gen_new_label();
  TCGv temp_5 = tcg_temp_local_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_5, getFFlag(), arc_true);
  TCGv temp_6 = tcg_temp_local_new_i32();
  tcg_gen_xori_i32(temp_6, temp_5, 1); tcg_gen_andi_i32(temp_6, temp_6, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_6, arc_true, done_3);;
  setZFlag(alu);
  setNFlag(alu);
  TCGv temp_7 = tcg_temp_local_new_i32();
  tcg_gen_mov_i32(temp_7, CarrySUB(a, b, c));
  setCFlag(temp_7);
  TCGv temp_8 = tcg_temp_local_new_i32();
  tcg_gen_mov_i32(temp_8, OverflowSUB(a, b, c));
  setVFlag(temp_8);
  gen_set_label(done_3);
  gen_set_label(done_1);

  return ret;
}





/* CMP
 *    Variables: @b, @c
 *    Functions: getCCFlag, setZFlag, setNFlag, setCFlag, CarrySUB, setVFlag, OverflowSUB
--- code ---
{
  if((getCCFlag () == true))
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
  TCGLabel *done_1 = gen_new_label();
  TCGv temp_1 = tcg_temp_local_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, getCCFlag(), arc_true);
  TCGv temp_2 = tcg_temp_local_new_i32();
  tcg_gen_xori_i32(temp_2, temp_1, 1); tcg_gen_andi_i32(temp_2, temp_2, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, arc_true, done_1);;
  TCGv alu = tcg_temp_local_new_i32();
  tcg_gen_sub_i32(alu, b, c);
  setZFlag(alu);
  setNFlag(alu);
  TCGv temp_3 = tcg_temp_local_new_i32();
  tcg_gen_mov_i32(temp_3, CarrySUB(alu, b, c));
  setCFlag(temp_3);
  TCGv temp_4 = tcg_temp_local_new_i32();
  tcg_gen_mov_i32(temp_4, OverflowSUB(alu, b, c));
  setVFlag(temp_4);
  gen_set_label(done_1);

  return ret;
}





/* AND
 *    Variables: @a, @b, @c
 *    Functions: getCCFlag, getFFlag, setZFlag, setNFlag
--- code ---
{
  if((getCCFlag () == true))
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
  TCGLabel *done_1 = gen_new_label();
  TCGv temp_1 = tcg_temp_local_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, getCCFlag(), arc_true);
  TCGv temp_2 = tcg_temp_local_new_i32();
  tcg_gen_xori_i32(temp_2, temp_1, 1); tcg_gen_andi_i32(temp_2, temp_2, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, arc_true, done_1);;
  tcg_gen_and_i32(a, b, c);
  TCGLabel *done_2 = gen_new_label();
  TCGv temp_3 = tcg_temp_local_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_3, getFFlag(), arc_true);
  TCGv temp_4 = tcg_temp_local_new_i32();
  tcg_gen_xori_i32(temp_4, temp_3, 1); tcg_gen_andi_i32(temp_4, temp_4, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_4, arc_true, done_2);;
  setZFlag(a);
  setNFlag(a);
  gen_set_label(done_2);
  gen_set_label(done_1);

  return ret;
}





/* OR
 *    Variables: @a, @b, @c
 *    Functions: getCCFlag, getFFlag, setZFlag, setNFlag
--- code ---
{
  if((getCCFlag () == true))
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
  TCGLabel *done_1 = gen_new_label();
  TCGv temp_1 = tcg_temp_local_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, getCCFlag(), arc_true);
  TCGv temp_2 = tcg_temp_local_new_i32();
  tcg_gen_xori_i32(temp_2, temp_1, 1); tcg_gen_andi_i32(temp_2, temp_2, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, arc_true, done_1);;
  tcg_gen_or_i32(a, b, c);
  TCGLabel *done_2 = gen_new_label();
  TCGv temp_3 = tcg_temp_local_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_3, getFFlag(), arc_true);
  TCGv temp_4 = tcg_temp_local_new_i32();
  tcg_gen_xori_i32(temp_4, temp_3, 1); tcg_gen_andi_i32(temp_4, temp_4, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_4, arc_true, done_2);;
  setZFlag(a);
  setNFlag(a);
  gen_set_label(done_2);
  gen_set_label(done_1);

  return ret;
}





/* XOR
 *    Variables: @a, @b, @c
 *    Functions: getCCFlag, getFFlag, setZFlag, setNFlag
--- code ---
{
  if((getCCFlag () == true))
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
  TCGLabel *done_1 = gen_new_label();
  TCGv temp_1 = tcg_temp_local_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, getCCFlag(), arc_true);
  TCGv temp_2 = tcg_temp_local_new_i32();
  tcg_gen_xori_i32(temp_2, temp_1, 1); tcg_gen_andi_i32(temp_2, temp_2, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, arc_true, done_1);;
  tcg_gen_xor_i32(a, b, c);
  TCGLabel *done_2 = gen_new_label();
  TCGv temp_3 = tcg_temp_local_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_3, getFFlag(), arc_true);
  TCGv temp_4 = tcg_temp_local_new_i32();
  tcg_gen_xori_i32(temp_4, temp_3, 1); tcg_gen_andi_i32(temp_4, temp_4, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_4, arc_true, done_2);;
  setZFlag(a);
  setNFlag(a);
  gen_set_label(done_2);
  gen_set_label(done_1);

  return ret;
}





/* MOV
 *    Variables: @a, @b
 *    Functions: getCCFlag, getFFlag, setZFlag, setNFlag
--- code ---
{
  if((getCCFlag () == true))
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
  TCGLabel *done_1 = gen_new_label();
  TCGv temp_1 = tcg_temp_local_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, getCCFlag(), arc_true);
  TCGv temp_2 = tcg_temp_local_new_i32();
  tcg_gen_xori_i32(temp_2, temp_1, 1); tcg_gen_andi_i32(temp_2, temp_2, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, arc_true, done_1);;
  tcg_gen_mov_i32(a, b);
  TCGLabel *done_2 = gen_new_label();
  TCGv temp_3 = tcg_temp_local_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_3, getFFlag(), arc_true);
  TCGv temp_4 = tcg_temp_local_new_i32();
  tcg_gen_xori_i32(temp_4, temp_3, 1); tcg_gen_andi_i32(temp_4, temp_4, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_4, arc_true, done_2);;
  setZFlag(a);
  setNFlag(a);
  gen_set_label(done_2);
  gen_set_label(done_1);

  return ret;
}





/* ASL
 *    Variables: @a, @b, @c
 *    Functions: getCCFlag, getFFlag, setZFlag, setNFlag, setCFlag, getBit
--- code ---
{
  if((getCCFlag () == true))
    {
      @a = (@b << @c);
      if((getFFlag () == true))
        {
          setZFlag (@a);
          setNFlag (@a);
          if((@c == 0))
            {
              setCFlag (0);
            }
          else
            {
              setCFlag (getBit (@b, (32 - @c)));
            };
        };
    };
}
 */

int
arc2_gen_ASL (DisasCtxt *ctx, TCGv a, TCGv b, TCGv c)
{
  int ret = BS_NONE;
  TCGLabel *done_1 = gen_new_label();
  TCGv temp_1 = tcg_temp_local_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, getCCFlag(), arc_true);
  TCGv temp_2 = tcg_temp_local_new_i32();
  tcg_gen_xori_i32(temp_2, temp_1, 1); tcg_gen_andi_i32(temp_2, temp_2, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, arc_true, done_1);;
  tcg_gen_shl_i32(a, b, c);
  TCGLabel *done_2 = gen_new_label();
  TCGv temp_3 = tcg_temp_local_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_3, getFFlag(), arc_true);
  TCGv temp_4 = tcg_temp_local_new_i32();
  tcg_gen_xori_i32(temp_4, temp_3, 1); tcg_gen_andi_i32(temp_4, temp_4, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_4, arc_true, done_2);;
  setZFlag(a);
  setNFlag(a);
  TCGLabel *else_3 = gen_new_label();
  TCGLabel *done_3 = gen_new_label();
  TCGv temp_5 = tcg_temp_local_new_i32();
  tcg_gen_setcondi_i32(TCG_COND_EQ, temp_5, c, 0);
  TCGv temp_6 = tcg_temp_local_new_i32();
  tcg_gen_xori_i32(temp_6, temp_5, 1); tcg_gen_andi_i32(temp_6, temp_6, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_6, arc_true, else_3);;
  TCGv temp_7 = tcg_temp_local_new_i32();
  tcg_gen_movi_i32(temp_7, 0);
  setCFlag(temp_7);
  tcg_gen_br(done_3);
  gen_set_label(else_3);
  TCGv temp_9 = tcg_temp_local_new_i32();
  tcg_gen_subfi_i32(temp_9, 32, c);
  TCGv temp_8 = tcg_temp_local_new_i32();
  tcg_gen_mov_i32(temp_8, getBit(b, temp_9));
  setCFlag(temp_8);
  gen_set_label(done_3);
  gen_set_label(done_2);
  gen_set_label(done_1);

  return ret;
}





/* ASR
 *    Variables: @a, @b, @c
 *    Functions: getCCFlag, getFFlag, setZFlag, setNFlag, setCFlag, getBit
--- code ---
{
  if((getCCFlag () == true))
    {
      @a = (@b >> @c);
      if((getFFlag () == true))
        {
          setZFlag (@a);
          setNFlag (@a);
          if((@c == 0))
            {
              setCFlag (0);
            }
          else
            {
              setCFlag (getBit (@b, (@c - 1)));
            };
        };
    };
}
 */

int
arc2_gen_ASR (DisasCtxt *ctx, TCGv a, TCGv b, TCGv c)
{
  int ret = BS_NONE;
  TCGLabel *done_1 = gen_new_label();
  TCGv temp_1 = tcg_temp_local_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, getCCFlag(), arc_true);
  TCGv temp_2 = tcg_temp_local_new_i32();
  tcg_gen_xori_i32(temp_2, temp_1, 1); tcg_gen_andi_i32(temp_2, temp_2, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, arc_true, done_1);;
  tcg_gen_shr_i32(a, b, c);
  TCGLabel *done_2 = gen_new_label();
  TCGv temp_3 = tcg_temp_local_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_3, getFFlag(), arc_true);
  TCGv temp_4 = tcg_temp_local_new_i32();
  tcg_gen_xori_i32(temp_4, temp_3, 1); tcg_gen_andi_i32(temp_4, temp_4, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_4, arc_true, done_2);;
  setZFlag(a);
  setNFlag(a);
  TCGLabel *else_3 = gen_new_label();
  TCGLabel *done_3 = gen_new_label();
  TCGv temp_5 = tcg_temp_local_new_i32();
  tcg_gen_setcondi_i32(TCG_COND_EQ, temp_5, c, 0);
  TCGv temp_6 = tcg_temp_local_new_i32();
  tcg_gen_xori_i32(temp_6, temp_5, 1); tcg_gen_andi_i32(temp_6, temp_6, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_6, arc_true, else_3);;
  TCGv temp_7 = tcg_temp_local_new_i32();
  tcg_gen_movi_i32(temp_7, 0);
  setCFlag(temp_7);
  tcg_gen_br(done_3);
  gen_set_label(else_3);
  TCGv temp_9 = tcg_temp_local_new_i32();
  tcg_gen_subi_i32(temp_9, c, 1);
  TCGv temp_8 = tcg_temp_local_new_i32();
  tcg_gen_mov_i32(temp_8, getBit(b, temp_9));
  setCFlag(temp_8);
  gen_set_label(done_3);
  gen_set_label(done_2);
  gen_set_label(done_1);

  return ret;
}





/* ASR8
 *    Variables: @a, @b
 *    Functions: getCCFlag, getFFlag, setZFlag, setNFlag
--- code ---
{
  if((getCCFlag () == true))
    {
      @a = (@b >> 16);
      if((getFFlag () == true))
        {
          setZFlag (@a);
          setNFlag (@a);
        };
    };
}
 */

int
arc2_gen_ASR8 (DisasCtxt *ctx, TCGv a, TCGv b)
{
  int ret = BS_NONE;
  TCGLabel *done_1 = gen_new_label();
  TCGv temp_1 = tcg_temp_local_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, getCCFlag(), arc_true);
  TCGv temp_2 = tcg_temp_local_new_i32();
  tcg_gen_xori_i32(temp_2, temp_1, 1); tcg_gen_andi_i32(temp_2, temp_2, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, arc_true, done_1);;
  tcg_gen_shri_i32(a, b, 16);
  TCGLabel *done_2 = gen_new_label();
  TCGv temp_3 = tcg_temp_local_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_3, getFFlag(), arc_true);
  TCGv temp_4 = tcg_temp_local_new_i32();
  tcg_gen_xori_i32(temp_4, temp_3, 1); tcg_gen_andi_i32(temp_4, temp_4, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_4, arc_true, done_2);;
  setZFlag(a);
  setNFlag(a);
  gen_set_label(done_2);
  gen_set_label(done_1);

  return ret;
}





/* ASR16
 *    Variables: @a, @b
 *    Functions: getCCFlag, getFFlag, setZFlag, setNFlag
--- code ---
{
  if((getCCFlag () == true))
    {
      @a = (@b >> 16);
      if((getFFlag () == true))
        {
          setZFlag (@a);
          setNFlag (@a);
        };
    };
}
 */

int
arc2_gen_ASR16 (DisasCtxt *ctx, TCGv a, TCGv b)
{
  int ret = BS_NONE;
  TCGLabel *done_1 = gen_new_label();
  TCGv temp_1 = tcg_temp_local_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, getCCFlag(), arc_true);
  TCGv temp_2 = tcg_temp_local_new_i32();
  tcg_gen_xori_i32(temp_2, temp_1, 1); tcg_gen_andi_i32(temp_2, temp_2, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, arc_true, done_1);;
  tcg_gen_shri_i32(a, b, 16);
  TCGLabel *done_2 = gen_new_label();
  TCGv temp_3 = tcg_temp_local_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_3, getFFlag(), arc_true);
  TCGv temp_4 = tcg_temp_local_new_i32();
  tcg_gen_xori_i32(temp_4, temp_3, 1); tcg_gen_andi_i32(temp_4, temp_4, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_4, arc_true, done_2);;
  setZFlag(a);
  setNFlag(a);
  gen_set_label(done_2);
  gen_set_label(done_1);

  return ret;
}





/* LSL16
 *    Variables: @a, @b
 *    Functions: getCCFlag, logicalShiftLeft, getFFlag, setZFlag, setNFlag
--- code ---
{
  if((getCCFlag () == true))
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
  TCGLabel *done_1 = gen_new_label();
  TCGv temp_1 = tcg_temp_local_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, getCCFlag(), arc_true);
  TCGv temp_2 = tcg_temp_local_new_i32();
  tcg_gen_xori_i32(temp_2, temp_1, 1); tcg_gen_andi_i32(temp_2, temp_2, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, arc_true, done_1);;
  TCGv temp_5 = tcg_temp_local_new_i32();
  tcg_gen_movi_i32(temp_5, 16);
  tcg_gen_mov_i32(a, logicalShiftLeft(b, temp_5));
  TCGLabel *done_2 = gen_new_label();
  TCGv temp_3 = tcg_temp_local_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_3, getFFlag(), arc_true);
  TCGv temp_4 = tcg_temp_local_new_i32();
  tcg_gen_xori_i32(temp_4, temp_3, 1); tcg_gen_andi_i32(temp_4, temp_4, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_4, arc_true, done_2);;
  setZFlag(a);
  setNFlag(a);
  gen_set_label(done_2);
  gen_set_label(done_1);

  return ret;
}





/* LSL8
 *    Variables: @a, @b
 *    Functions: getCCFlag, logicalShiftLeft, getFFlag, setZFlag, setNFlag
--- code ---
{
  if((getCCFlag () == true))
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
  TCGLabel *done_1 = gen_new_label();
  TCGv temp_1 = tcg_temp_local_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, getCCFlag(), arc_true);
  TCGv temp_2 = tcg_temp_local_new_i32();
  tcg_gen_xori_i32(temp_2, temp_1, 1); tcg_gen_andi_i32(temp_2, temp_2, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, arc_true, done_1);;
  TCGv temp_5 = tcg_temp_local_new_i32();
  tcg_gen_movi_i32(temp_5, 8);
  tcg_gen_mov_i32(a, logicalShiftLeft(b, temp_5));
  TCGLabel *done_2 = gen_new_label();
  TCGv temp_3 = tcg_temp_local_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_3, getFFlag(), arc_true);
  TCGv temp_4 = tcg_temp_local_new_i32();
  tcg_gen_xori_i32(temp_4, temp_3, 1); tcg_gen_andi_i32(temp_4, temp_4, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_4, arc_true, done_2);;
  setZFlag(a);
  setNFlag(a);
  gen_set_label(done_2);
  gen_set_label(done_1);

  return ret;
}





/* LSR
 *    Variables: @a, @b, @c
 *    Functions: getCCFlag, logicalShiftRight, getFFlag, setZFlag, setNFlag, setCFlag, getBit
--- code ---
{
  if((getCCFlag () == true))
    {
      @a = logicalShiftRight (@b, @c);
      if((getFFlag () == true))
        {
          setZFlag (@a);
          setNFlag (@a);
          if((@c == 0))
            {
              setCFlag (0);
            }
          else
            {
              setCFlag (getBit (@b, (@c - 1)));
            };
        };
    };
}
 */

int
arc2_gen_LSR (DisasCtxt *ctx, TCGv a, TCGv b, TCGv c)
{
  int ret = BS_NONE;
  TCGLabel *done_1 = gen_new_label();
  TCGv temp_1 = tcg_temp_local_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, getCCFlag(), arc_true);
  TCGv temp_2 = tcg_temp_local_new_i32();
  tcg_gen_xori_i32(temp_2, temp_1, 1); tcg_gen_andi_i32(temp_2, temp_2, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, arc_true, done_1);;
  tcg_gen_mov_i32(a, logicalShiftRight(b, c));
  TCGLabel *done_2 = gen_new_label();
  TCGv temp_3 = tcg_temp_local_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_3, getFFlag(), arc_true);
  TCGv temp_4 = tcg_temp_local_new_i32();
  tcg_gen_xori_i32(temp_4, temp_3, 1); tcg_gen_andi_i32(temp_4, temp_4, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_4, arc_true, done_2);;
  setZFlag(a);
  setNFlag(a);
  TCGLabel *else_3 = gen_new_label();
  TCGLabel *done_3 = gen_new_label();
  TCGv temp_5 = tcg_temp_local_new_i32();
  tcg_gen_setcondi_i32(TCG_COND_EQ, temp_5, c, 0);
  TCGv temp_6 = tcg_temp_local_new_i32();
  tcg_gen_xori_i32(temp_6, temp_5, 1); tcg_gen_andi_i32(temp_6, temp_6, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_6, arc_true, else_3);;
  TCGv temp_7 = tcg_temp_local_new_i32();
  tcg_gen_movi_i32(temp_7, 0);
  setCFlag(temp_7);
  tcg_gen_br(done_3);
  gen_set_label(else_3);
  TCGv temp_9 = tcg_temp_local_new_i32();
  tcg_gen_subi_i32(temp_9, c, 1);
  TCGv temp_8 = tcg_temp_local_new_i32();
  tcg_gen_mov_i32(temp_8, getBit(b, temp_9));
  setCFlag(temp_8);
  gen_set_label(done_3);
  gen_set_label(done_2);
  gen_set_label(done_1);

  return ret;
}





/* LSR16
 *    Variables: @a, @b
 *    Functions: getCCFlag, logicalShiftRight, getFFlag, setZFlag, setNFlag
--- code ---
{
  if((getCCFlag () == true))
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
  TCGLabel *done_1 = gen_new_label();
  TCGv temp_1 = tcg_temp_local_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, getCCFlag(), arc_true);
  TCGv temp_2 = tcg_temp_local_new_i32();
  tcg_gen_xori_i32(temp_2, temp_1, 1); tcg_gen_andi_i32(temp_2, temp_2, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, arc_true, done_1);;
  TCGv temp_5 = tcg_temp_local_new_i32();
  tcg_gen_movi_i32(temp_5, 16);
  tcg_gen_mov_i32(a, logicalShiftRight(b, temp_5));
  TCGLabel *done_2 = gen_new_label();
  TCGv temp_3 = tcg_temp_local_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_3, getFFlag(), arc_true);
  TCGv temp_4 = tcg_temp_local_new_i32();
  tcg_gen_xori_i32(temp_4, temp_3, 1); tcg_gen_andi_i32(temp_4, temp_4, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_4, arc_true, done_2);;
  setZFlag(a);
  setNFlag(a);
  gen_set_label(done_2);
  gen_set_label(done_1);

  return ret;
}





/* LSR8
 *    Variables: @a, @b
 *    Functions: getCCFlag, logicalShiftRight, getFFlag, setZFlag, setNFlag
--- code ---
{
  if((getCCFlag () == true))
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
  TCGLabel *done_1 = gen_new_label();
  TCGv temp_1 = tcg_temp_local_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, getCCFlag(), arc_true);
  TCGv temp_2 = tcg_temp_local_new_i32();
  tcg_gen_xori_i32(temp_2, temp_1, 1); tcg_gen_andi_i32(temp_2, temp_2, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, arc_true, done_1);;
  TCGv temp_5 = tcg_temp_local_new_i32();
  tcg_gen_movi_i32(temp_5, 8);
  tcg_gen_mov_i32(a, logicalShiftRight(b, temp_5));
  TCGLabel *done_2 = gen_new_label();
  TCGv temp_3 = tcg_temp_local_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_3, getFFlag(), arc_true);
  TCGv temp_4 = tcg_temp_local_new_i32();
  tcg_gen_xori_i32(temp_4, temp_3, 1); tcg_gen_andi_i32(temp_4, temp_4, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_4, arc_true, done_2);;
  setZFlag(a);
  setNFlag(a);
  gen_set_label(done_2);
  gen_set_label(done_1);

  return ret;
}





/* BIC
 *    Variables: @a, @b, @c
 *    Functions: getCCFlag, getFFlag, setZFlag, setNFlag
--- code ---
{
  if((getCCFlag () == true))
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
  TCGLabel *done_1 = gen_new_label();
  TCGv temp_1 = tcg_temp_local_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, getCCFlag(), arc_true);
  TCGv temp_2 = tcg_temp_local_new_i32();
  tcg_gen_xori_i32(temp_2, temp_1, 1); tcg_gen_andi_i32(temp_2, temp_2, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, arc_true, done_1);;
  TCGv temp_5 = tcg_temp_local_new_i32();
  tcg_gen_neg_i32(temp_5, c);
  tcg_gen_and_i32(a, b, temp_5);
  TCGLabel *done_2 = gen_new_label();
  TCGv temp_3 = tcg_temp_local_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_3, getFFlag(), arc_true);
  TCGv temp_4 = tcg_temp_local_new_i32();
  tcg_gen_xori_i32(temp_4, temp_3, 1); tcg_gen_andi_i32(temp_4, temp_4, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_4, arc_true, done_2);;
  setZFlag(a);
  setNFlag(a);
  gen_set_label(done_2);
  gen_set_label(done_1);

  return ret;
}





/* BCLR
 *    Variables: @c, @a, @b
 *    Functions: getCCFlag, getFFlag, setZFlag, setNFlag
--- code ---
{
  if((getCCFlag () == true))
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
  TCGLabel *done_1 = gen_new_label();
  TCGv temp_1 = tcg_temp_local_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, getCCFlag(), arc_true);
  TCGv temp_2 = tcg_temp_local_new_i32();
  tcg_gen_xori_i32(temp_2, temp_1, 1); tcg_gen_andi_i32(temp_2, temp_2, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, arc_true, done_1);;
  TCGv temp_5 = tcg_temp_local_new_i32();
  tcg_gen_andi_i32(temp_5, c, 31);
  TCGv tmp = tcg_temp_local_new_i32();
  tcg_gen_shlfi_i32(tmp, 1, temp_5);
  TCGv temp_6 = tcg_temp_local_new_i32();
  tcg_gen_neg_i32(temp_6, tmp);
  tcg_gen_and_i32(a, b, temp_6);
  TCGLabel *done_2 = gen_new_label();
  TCGv temp_3 = tcg_temp_local_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_3, getFFlag(), arc_true);
  TCGv temp_4 = tcg_temp_local_new_i32();
  tcg_gen_xori_i32(temp_4, temp_3, 1); tcg_gen_andi_i32(temp_4, temp_4, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_4, arc_true, done_2);;
  setZFlag(a);
  setNFlag(a);
  gen_set_label(done_2);
  gen_set_label(done_1);

  return ret;
}





/* TST
 *    Variables: @b, @c
 *    Functions: getCCFlag, getFFlag, setZFlag, setNFlag
--- code ---
{
  if((getCCFlag () == true))
    {
      alu = (@b & @c);
      if((getFFlag () == true))
        {
          setZFlag (alu);
          setNFlag (alu);
        };
    };
}
 */

int
arc2_gen_TST (DisasCtxt *ctx, TCGv b, TCGv c)
{
  int ret = BS_NONE;
  TCGLabel *done_1 = gen_new_label();
  TCGv temp_1 = tcg_temp_local_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, getCCFlag(), arc_true);
  TCGv temp_2 = tcg_temp_local_new_i32();
  tcg_gen_xori_i32(temp_2, temp_1, 1); tcg_gen_andi_i32(temp_2, temp_2, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, arc_true, done_1);;
  TCGv alu = tcg_temp_local_new_i32();
  tcg_gen_and_i32(alu, b, c);
  TCGLabel *done_2 = gen_new_label();
  TCGv temp_3 = tcg_temp_local_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_3, getFFlag(), arc_true);
  TCGv temp_4 = tcg_temp_local_new_i32();
  tcg_gen_xori_i32(temp_4, temp_3, 1); tcg_gen_andi_i32(temp_4, temp_4, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_4, arc_true, done_2);;
  setZFlag(alu);
  setNFlag(alu);
  gen_set_label(done_2);
  gen_set_label(done_1);

  return ret;
}





/* BMSK
 *    Variables: @c, @a, @b
 *    Functions: getCCFlag, getFFlag, setZFlag, setNFlag
--- code ---
{
  if((getCCFlag () == true))
    {
      tmp1 = ((@c & 31) + 1);
      tmp2 = ((1 << tmp1) - 1);
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
  TCGLabel *done_1 = gen_new_label();
  TCGv temp_1 = tcg_temp_local_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, getCCFlag(), arc_true);
  TCGv temp_2 = tcg_temp_local_new_i32();
  tcg_gen_xori_i32(temp_2, temp_1, 1); tcg_gen_andi_i32(temp_2, temp_2, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, arc_true, done_1);;
  TCGv temp_5 = tcg_temp_local_new_i32();
  tcg_gen_andi_i32(temp_5, c, 31);
  TCGv tmp1 = tcg_temp_local_new_i32();
  tcg_gen_addi_i32(tmp1, temp_5, 1);
  TCGv temp_6 = tcg_temp_local_new_i32();
  tcg_gen_shlfi_i32(temp_6, 1, tmp1);
  TCGv tmp2 = tcg_temp_local_new_i32();
  tcg_gen_subi_i32(tmp2, temp_6, 1);
  tcg_gen_and_i32(a, b, tmp2);
  TCGLabel *done_2 = gen_new_label();
  TCGv temp_3 = tcg_temp_local_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_3, getFFlag(), arc_true);
  TCGv temp_4 = tcg_temp_local_new_i32();
  tcg_gen_xori_i32(temp_4, temp_3, 1); tcg_gen_andi_i32(temp_4, temp_4, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_4, arc_true, done_2);;
  setZFlag(a);
  setNFlag(a);
  gen_set_label(done_2);
  gen_set_label(done_1);

  return ret;
}





/* BMSKN
 *    Variables: @c, @a, @b
 *    Functions: getCCFlag, getFFlag, setZFlag, setNFlag
--- code ---
{
  if((getCCFlag () == true))
    {
      tmp1 = ((@c & 31) + 1);
      tmp2 = ((1 << tmp1) - 1);
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
  TCGLabel *done_1 = gen_new_label();
  TCGv temp_1 = tcg_temp_local_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, getCCFlag(), arc_true);
  TCGv temp_2 = tcg_temp_local_new_i32();
  tcg_gen_xori_i32(temp_2, temp_1, 1); tcg_gen_andi_i32(temp_2, temp_2, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, arc_true, done_1);;
  TCGv temp_5 = tcg_temp_local_new_i32();
  tcg_gen_andi_i32(temp_5, c, 31);
  TCGv tmp1 = tcg_temp_local_new_i32();
  tcg_gen_addi_i32(tmp1, temp_5, 1);
  TCGv temp_6 = tcg_temp_local_new_i32();
  tcg_gen_shlfi_i32(temp_6, 1, tmp1);
  TCGv tmp2 = tcg_temp_local_new_i32();
  tcg_gen_subi_i32(tmp2, temp_6, 1);
  TCGv temp_7 = tcg_temp_local_new_i32();
  tcg_gen_neg_i32(temp_7, tmp2);
  tcg_gen_and_i32(a, b, temp_7);
  TCGLabel *done_2 = gen_new_label();
  TCGv temp_3 = tcg_temp_local_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_3, getFFlag(), arc_true);
  TCGv temp_4 = tcg_temp_local_new_i32();
  tcg_gen_xori_i32(temp_4, temp_3, 1); tcg_gen_andi_i32(temp_4, temp_4, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_4, arc_true, done_2);;
  setZFlag(a);
  setNFlag(a);
  gen_set_label(done_2);
  gen_set_label(done_1);

  return ret;
}





/* BSET
 *    Variables: @c, @a, @b
 *    Functions: getCCFlag, getFFlag, setZFlag, setNFlag
--- code ---
{
  if((getCCFlag () == true))
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
  TCGLabel *done_1 = gen_new_label();
  TCGv temp_1 = tcg_temp_local_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, getCCFlag(), arc_true);
  TCGv temp_2 = tcg_temp_local_new_i32();
  tcg_gen_xori_i32(temp_2, temp_1, 1); tcg_gen_andi_i32(temp_2, temp_2, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, arc_true, done_1);;
  TCGv temp_5 = tcg_temp_local_new_i32();
  tcg_gen_andi_i32(temp_5, c, 31);
  TCGv tmp = tcg_temp_local_new_i32();
  tcg_gen_shlfi_i32(tmp, 1, temp_5);
  tcg_gen_or_i32(a, b, tmp);
  TCGLabel *done_2 = gen_new_label();
  TCGv temp_3 = tcg_temp_local_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_3, getFFlag(), arc_true);
  TCGv temp_4 = tcg_temp_local_new_i32();
  tcg_gen_xori_i32(temp_4, temp_3, 1); tcg_gen_andi_i32(temp_4, temp_4, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_4, arc_true, done_2);;
  setZFlag(a);
  setNFlag(a);
  gen_set_label(done_2);
  gen_set_label(done_1);

  return ret;
}





/* BTST
 *    Variables: @c, @b
 *    Functions: getCCFlag, getFFlag, setZFlag, setNFlag
--- code ---
{
  if((getCCFlag () == true))
    {
      tmp = (1 << (@c & 31));
      alu = (@b & tmp);
      if((getFFlag () == true))
        {
          setZFlag (alu);
          setNFlag (alu);
        };
    };
}
 */

int
arc2_gen_BTST (DisasCtxt *ctx, TCGv c, TCGv b)
{
  int ret = BS_NONE;
  TCGLabel *done_1 = gen_new_label();
  TCGv temp_1 = tcg_temp_local_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, getCCFlag(), arc_true);
  TCGv temp_2 = tcg_temp_local_new_i32();
  tcg_gen_xori_i32(temp_2, temp_1, 1); tcg_gen_andi_i32(temp_2, temp_2, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, arc_true, done_1);;
  TCGv temp_5 = tcg_temp_local_new_i32();
  tcg_gen_andi_i32(temp_5, c, 31);
  TCGv tmp = tcg_temp_local_new_i32();
  tcg_gen_shlfi_i32(tmp, 1, temp_5);
  TCGv alu = tcg_temp_local_new_i32();
  tcg_gen_and_i32(alu, b, tmp);
  TCGLabel *done_2 = gen_new_label();
  TCGv temp_3 = tcg_temp_local_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_3, getFFlag(), arc_true);
  TCGv temp_4 = tcg_temp_local_new_i32();
  tcg_gen_xori_i32(temp_4, temp_3, 1); tcg_gen_andi_i32(temp_4, temp_4, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_4, arc_true, done_2);;
  setZFlag(alu);
  setNFlag(alu);
  gen_set_label(done_2);
  gen_set_label(done_1);

  return ret;
}





/* BXOR
 *    Variables: @c, @a, @b
 *    Functions: getCCFlag, getFFlag, setZFlag, setNFlag
--- code ---
{
  if((getCCFlag () == true))
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
  TCGLabel *done_1 = gen_new_label();
  TCGv temp_1 = tcg_temp_local_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, getCCFlag(), arc_true);
  TCGv temp_2 = tcg_temp_local_new_i32();
  tcg_gen_xori_i32(temp_2, temp_1, 1); tcg_gen_andi_i32(temp_2, temp_2, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, arc_true, done_1);;
  TCGv tmp = tcg_temp_local_new_i32();
  tcg_gen_shlfi_i32(tmp, 1, c);
  tcg_gen_xor_i32(a, b, tmp);
  TCGLabel *done_2 = gen_new_label();
  TCGv temp_3 = tcg_temp_local_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_3, getFFlag(), arc_true);
  TCGv temp_4 = tcg_temp_local_new_i32();
  tcg_gen_xori_i32(temp_4, temp_3, 1); tcg_gen_andi_i32(temp_4, temp_4, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_4, arc_true, done_2);;
  setZFlag(a);
  setNFlag(a);
  gen_set_label(done_2);
  gen_set_label(done_1);

  return ret;
}





/* ROL
 *    Variables: @n, @src, @dest
 *    Functions: getCCFlag, logicalShiftRight, extractBits, getFFlag, setZFlag, setNFlag, setCFlag
--- code ---
{
  if((getCCFlag () == true))
    {
      shr = (32 - @n);
      tmp1 = logicalShiftRight (extractBits (@src, 31, (31 - @n)), shr);
      tmp2 = (@src << @n);
      @dest = (tmp1 | tmp2);
      if((getFFlag () == true))
        {
          setZFlag (@dest);
          setNFlag (@dest);
          setCFlag (extractBits (@src, (@n - 1), (@n - 1)));
        };
    };
}
 */

int
arc2_gen_ROL (DisasCtxt *ctx, TCGv n, TCGv src, TCGv dest)
{
  int ret = BS_NONE;
  TCGLabel *done_1 = gen_new_label();
  TCGv temp_1 = tcg_temp_local_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, getCCFlag(), arc_true);
  TCGv temp_2 = tcg_temp_local_new_i32();
  tcg_gen_xori_i32(temp_2, temp_1, 1); tcg_gen_andi_i32(temp_2, temp_2, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, arc_true, done_1);;
  TCGv shr = tcg_temp_local_new_i32();
  tcg_gen_subfi_i32(shr, 32, n);
  TCGv temp_7 = tcg_temp_local_new_i32();
  tcg_gen_subfi_i32(temp_7, 31, n);
  TCGv temp_6 = tcg_temp_local_new_i32();
  tcg_gen_movi_i32(temp_6, 31);
  TCGv temp_5 = tcg_temp_local_new_i32();
  tcg_gen_mov_i32(temp_5, extractBits(src, temp_6, temp_7));
  TCGv tmp1 = tcg_temp_local_new_i32();
  tcg_gen_mov_i32(tmp1, logicalShiftRight(temp_5, shr));
  TCGv tmp2 = tcg_temp_local_new_i32();
  tcg_gen_shl_i32(tmp2, src, n);
  tcg_gen_or_i32(dest, tmp1, tmp2);
  TCGLabel *done_2 = gen_new_label();
  TCGv temp_3 = tcg_temp_local_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_3, getFFlag(), arc_true);
  TCGv temp_4 = tcg_temp_local_new_i32();
  tcg_gen_xori_i32(temp_4, temp_3, 1); tcg_gen_andi_i32(temp_4, temp_4, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_4, arc_true, done_2);;
  setZFlag(dest);
  setNFlag(dest);
  TCGv temp_10 = tcg_temp_local_new_i32();
  tcg_gen_subi_i32(temp_10, n, 1);
  TCGv temp_9 = tcg_temp_local_new_i32();
  tcg_gen_subi_i32(temp_9, n, 1);
  TCGv temp_8 = tcg_temp_local_new_i32();
  tcg_gen_mov_i32(temp_8, extractBits(src, temp_9, temp_10));
  setCFlag(temp_8);
  gen_set_label(done_2);
  gen_set_label(done_1);

  return ret;
}





/* ROR
 *    Variables: @n, @src, @dest
 *    Functions: getCCFlag, extractBits, getFFlag, setZFlag, setNFlag, setCFlag
--- code ---
{
  if((getCCFlag () == true))
    {
      shl = (32 - @n);
      tmp1 = (extractBits (@src, (@n - 1), 0) << shl);
      tmp2 = (@src >> @n);
      @dest = (tmp1 | tmp2);
      if((getFFlag () == true))
        {
          setZFlag (@dest);
          setNFlag (@dest);
          setCFlag (extractBits (@src, (@n - 1), (@n - 1)));
        };
    };
}
 */

int
arc2_gen_ROR (DisasCtxt *ctx, TCGv n, TCGv src, TCGv dest)
{
  int ret = BS_NONE;
  TCGLabel *done_1 = gen_new_label();
  TCGv temp_1 = tcg_temp_local_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, getCCFlag(), arc_true);
  TCGv temp_2 = tcg_temp_local_new_i32();
  tcg_gen_xori_i32(temp_2, temp_1, 1); tcg_gen_andi_i32(temp_2, temp_2, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, arc_true, done_1);;
  TCGv shl = tcg_temp_local_new_i32();
  tcg_gen_subfi_i32(shl, 32, n);
  TCGv temp_7 = tcg_temp_local_new_i32();
  tcg_gen_movi_i32(temp_7, 0);
  TCGv temp_6 = tcg_temp_local_new_i32();
  tcg_gen_subi_i32(temp_6, n, 1);
  TCGv temp_5 = tcg_temp_local_new_i32();
  tcg_gen_mov_i32(temp_5, extractBits(src, temp_6, temp_7));
  TCGv tmp1 = tcg_temp_local_new_i32();
  tcg_gen_shl_i32(tmp1, temp_5, shl);
  TCGv tmp2 = tcg_temp_local_new_i32();
  tcg_gen_shr_i32(tmp2, src, n);
  tcg_gen_or_i32(dest, tmp1, tmp2);
  TCGLabel *done_2 = gen_new_label();
  TCGv temp_3 = tcg_temp_local_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_3, getFFlag(), arc_true);
  TCGv temp_4 = tcg_temp_local_new_i32();
  tcg_gen_xori_i32(temp_4, temp_3, 1); tcg_gen_andi_i32(temp_4, temp_4, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_4, arc_true, done_2);;
  setZFlag(dest);
  setNFlag(dest);
  TCGv temp_10 = tcg_temp_local_new_i32();
  tcg_gen_subi_i32(temp_10, n, 1);
  TCGv temp_9 = tcg_temp_local_new_i32();
  tcg_gen_subi_i32(temp_9, n, 1);
  TCGv temp_8 = tcg_temp_local_new_i32();
  tcg_gen_mov_i32(temp_8, extractBits(src, temp_9, temp_10));
  setCFlag(temp_8);
  gen_set_label(done_2);
  gen_set_label(done_1);

  return ret;
}





/* RLC
 *    Variables: @dest, @src
 *    Functions: getCCFlag, getCFlag, getFFlag, setZFlag, setNFlag, setCFlag, extractBits
--- code ---
{
  if((getCCFlag () == true))
    {
      @dest = (@src << 1);
      @dest = (@dest | getCFlag ());
      if((getFFlag () == true))
        {
          setZFlag (@dest);
          setNFlag (@dest);
          setCFlag (extractBits (@src, 31, 31));
        };
    };
}
 */

int
arc2_gen_RLC (DisasCtxt *ctx, TCGv dest, TCGv src)
{
  int ret = BS_NONE;
  TCGLabel *done_1 = gen_new_label();
  TCGv temp_1 = tcg_temp_local_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, getCCFlag(), arc_true);
  TCGv temp_2 = tcg_temp_local_new_i32();
  tcg_gen_xori_i32(temp_2, temp_1, 1); tcg_gen_andi_i32(temp_2, temp_2, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, arc_true, done_1);;
  tcg_gen_shli_i32(dest, src, 1);
  TCGv temp_5 = tcg_temp_local_new_i32();
  tcg_gen_mov_i32(temp_5, getCFlag());
  tcg_gen_or_i32(dest, dest, temp_5);
  TCGLabel *done_2 = gen_new_label();
  TCGv temp_3 = tcg_temp_local_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_3, getFFlag(), arc_true);
  TCGv temp_4 = tcg_temp_local_new_i32();
  tcg_gen_xori_i32(temp_4, temp_3, 1); tcg_gen_andi_i32(temp_4, temp_4, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_4, arc_true, done_2);;
  setZFlag(dest);
  setNFlag(dest);
  TCGv temp_8 = tcg_temp_local_new_i32();
  tcg_gen_movi_i32(temp_8, 31);
  TCGv temp_7 = tcg_temp_local_new_i32();
  tcg_gen_movi_i32(temp_7, 31);
  TCGv temp_6 = tcg_temp_local_new_i32();
  tcg_gen_mov_i32(temp_6, extractBits(src, temp_7, temp_8));
  setCFlag(temp_6);
  gen_set_label(done_2);
  gen_set_label(done_1);

  return ret;
}





/* RRC
 *    Variables: @dest, @src
 *    Functions: getCCFlag, getCFlag, getFFlag, setZFlag, setNFlag, setCFlag, extractBits
--- code ---
{
  if((getCCFlag () == true))
    {
      @dest = (@src >> 1);
      @dest = (@dest | (getCFlag () << 31));
      if((getFFlag () == true))
        {
          setZFlag (@dest);
          setNFlag (@dest);
          setCFlag (extractBits (@src, 0, 0));
        };
    };
}
 */

int
arc2_gen_RRC (DisasCtxt *ctx, TCGv dest, TCGv src)
{
  int ret = BS_NONE;
  TCGLabel *done_1 = gen_new_label();
  TCGv temp_1 = tcg_temp_local_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, getCCFlag(), arc_true);
  TCGv temp_2 = tcg_temp_local_new_i32();
  tcg_gen_xori_i32(temp_2, temp_1, 1); tcg_gen_andi_i32(temp_2, temp_2, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, arc_true, done_1);;
  tcg_gen_shri_i32(dest, src, 1);
  TCGv temp_6 = tcg_temp_local_new_i32();
  tcg_gen_mov_i32(temp_6, getCFlag());
  TCGv temp_5 = tcg_temp_local_new_i32();
  tcg_gen_shli_i32(temp_5, temp_6, 31);
  tcg_gen_or_i32(dest, dest, temp_5);
  TCGLabel *done_2 = gen_new_label();
  TCGv temp_3 = tcg_temp_local_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_3, getFFlag(), arc_true);
  TCGv temp_4 = tcg_temp_local_new_i32();
  tcg_gen_xori_i32(temp_4, temp_3, 1); tcg_gen_andi_i32(temp_4, temp_4, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_4, arc_true, done_2);;
  setZFlag(dest);
  setNFlag(dest);
  TCGv temp_9 = tcg_temp_local_new_i32();
  tcg_gen_movi_i32(temp_9, 0);
  TCGv temp_8 = tcg_temp_local_new_i32();
  tcg_gen_movi_i32(temp_8, 0);
  TCGv temp_7 = tcg_temp_local_new_i32();
  tcg_gen_mov_i32(temp_7, extractBits(src, temp_8, temp_9));
  setCFlag(temp_7);
  gen_set_label(done_2);
  gen_set_label(done_1);

  return ret;
}





/* SEXB
 *    Variables: @dest, @src
 *    Functions: getCCFlag, getFFlag, setZFlag, setNFlag
--- code ---
{
  if((getCCFlag () == true))
    {
      @dest = ((@src << 24) >> 24);
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
  TCGLabel *done_1 = gen_new_label();
  TCGv temp_1 = tcg_temp_local_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, getCCFlag(), arc_true);
  TCGv temp_2 = tcg_temp_local_new_i32();
  tcg_gen_xori_i32(temp_2, temp_1, 1); tcg_gen_andi_i32(temp_2, temp_2, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, arc_true, done_1);;
  TCGv temp_5 = tcg_temp_local_new_i32();
  tcg_gen_shli_i32(temp_5, src, 24);
  tcg_gen_shri_i32(dest, temp_5, 24);
  TCGLabel *done_2 = gen_new_label();
  TCGv temp_3 = tcg_temp_local_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_3, getFFlag(), arc_true);
  TCGv temp_4 = tcg_temp_local_new_i32();
  tcg_gen_xori_i32(temp_4, temp_3, 1); tcg_gen_andi_i32(temp_4, temp_4, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_4, arc_true, done_2);;
  setZFlag(dest);
  setNFlag(dest);
  gen_set_label(done_2);
  gen_set_label(done_1);

  return ret;
}





/* SEXH
 *    Variables: @dest, @src
 *    Functions: getCCFlag, getFFlag, setZFlag, setNFlag
--- code ---
{
  if((getCCFlag () == true))
    {
      @dest = ((@src << 16) >> 16);
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
  TCGLabel *done_1 = gen_new_label();
  TCGv temp_1 = tcg_temp_local_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, getCCFlag(), arc_true);
  TCGv temp_2 = tcg_temp_local_new_i32();
  tcg_gen_xori_i32(temp_2, temp_1, 1); tcg_gen_andi_i32(temp_2, temp_2, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, arc_true, done_1);;
  TCGv temp_5 = tcg_temp_local_new_i32();
  tcg_gen_shli_i32(temp_5, src, 16);
  tcg_gen_shri_i32(dest, temp_5, 16);
  TCGLabel *done_2 = gen_new_label();
  TCGv temp_3 = tcg_temp_local_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_3, getFFlag(), arc_true);
  TCGv temp_4 = tcg_temp_local_new_i32();
  tcg_gen_xori_i32(temp_4, temp_3, 1); tcg_gen_andi_i32(temp_4, temp_4, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_4, arc_true, done_2);;
  setZFlag(dest);
  setNFlag(dest);
  gen_set_label(done_2);
  gen_set_label(done_1);

  return ret;
}





/* EXTB
 *    Variables: @dest, @src
 *    Functions: getCCFlag, getFFlag, setZFlag, setNFlag
--- code ---
{
  if((getCCFlag () == true))
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
  TCGLabel *done_1 = gen_new_label();
  TCGv temp_1 = tcg_temp_local_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, getCCFlag(), arc_true);
  TCGv temp_2 = tcg_temp_local_new_i32();
  tcg_gen_xori_i32(temp_2, temp_1, 1); tcg_gen_andi_i32(temp_2, temp_2, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, arc_true, done_1);;
  tcg_gen_andi_i32(dest, src, 255);
  TCGLabel *done_2 = gen_new_label();
  TCGv temp_3 = tcg_temp_local_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_3, getFFlag(), arc_true);
  TCGv temp_4 = tcg_temp_local_new_i32();
  tcg_gen_xori_i32(temp_4, temp_3, 1); tcg_gen_andi_i32(temp_4, temp_4, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_4, arc_true, done_2);;
  setZFlag(dest);
  setNFlag(dest);
  gen_set_label(done_2);
  gen_set_label(done_1);

  return ret;
}





/* EXTH
 *    Variables: @dest, @src
 *    Functions: getCCFlag, getFFlag, setZFlag, setNFlag
--- code ---
{
  if((getCCFlag () == true))
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
  TCGLabel *done_1 = gen_new_label();
  TCGv temp_1 = tcg_temp_local_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, getCCFlag(), arc_true);
  TCGv temp_2 = tcg_temp_local_new_i32();
  tcg_gen_xori_i32(temp_2, temp_1, 1); tcg_gen_andi_i32(temp_2, temp_2, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, arc_true, done_1);;
  tcg_gen_andi_i32(dest, src, 65535);
  TCGLabel *done_2 = gen_new_label();
  TCGv temp_3 = tcg_temp_local_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_3, getFFlag(), arc_true);
  TCGv temp_4 = tcg_temp_local_new_i32();
  tcg_gen_xori_i32(temp_4, temp_3, 1); tcg_gen_andi_i32(temp_4, temp_4, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_4, arc_true, done_2);;
  setZFlag(dest);
  setNFlag(dest);
  gen_set_label(done_2);
  gen_set_label(done_1);

  return ret;
}





/* XBFU
 *    Variables: @src2, @src1, @dest
 *    Functions: getCCFlag, extractBits, getFFlag, setZFlag
--- code ---
{
  if((getCCFlag () == true))
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
  TCGLabel *done_1 = gen_new_label();
  TCGv temp_1 = tcg_temp_local_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, getCCFlag(), arc_true);
  TCGv temp_2 = tcg_temp_local_new_i32();
  tcg_gen_xori_i32(temp_2, temp_1, 1); tcg_gen_andi_i32(temp_2, temp_2, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, arc_true, done_1);;
  TCGv temp_6 = tcg_temp_local_new_i32();
  tcg_gen_movi_i32(temp_6, 0);
  TCGv temp_5 = tcg_temp_local_new_i32();
  tcg_gen_movi_i32(temp_5, 4);
  TCGv N = tcg_temp_local_new_i32();
  tcg_gen_mov_i32(N, extractBits(src2, temp_5, temp_6));
  TCGv temp_9 = tcg_temp_local_new_i32();
  tcg_gen_movi_i32(temp_9, 5);
  TCGv temp_8 = tcg_temp_local_new_i32();
  tcg_gen_movi_i32(temp_8, 9);
  TCGv temp_7 = tcg_temp_local_new_i32();
  tcg_gen_mov_i32(temp_7, extractBits(src2, temp_8, temp_9));
  TCGv M = tcg_temp_local_new_i32();
  tcg_gen_addi_i32(M, temp_7, 1);
  TCGv tmp1 = tcg_temp_local_new_i32();
  tcg_gen_shr_i32(tmp1, src1, N);
  TCGv temp_10 = tcg_temp_local_new_i32();
  tcg_gen_shlfi_i32(temp_10, 1, M);
  TCGv tmp2 = tcg_temp_local_new_i32();
  tcg_gen_subi_i32(tmp2, temp_10, 1);
  tcg_gen_and_i32(dest, tmp1, tmp2);
  TCGLabel *done_2 = gen_new_label();
  TCGv temp_3 = tcg_temp_local_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_3, getFFlag(), arc_true);
  TCGv temp_4 = tcg_temp_local_new_i32();
  tcg_gen_xori_i32(temp_4, temp_3, 1); tcg_gen_andi_i32(temp_4, temp_4, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_4, arc_true, done_2);;
  setZFlag(dest);
  gen_set_label(done_2);
  gen_set_label(done_1);

  return ret;
}





/* AEX
 *    Variables: @src2, @b
 *    Functions: getCCFlag, readAuxReg, writeAuxReg
--- code ---
{
  if((getCCFlag () == true))
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
  TCGLabel *done_1 = gen_new_label();
  TCGv temp_1 = tcg_temp_local_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, getCCFlag(), arc_true);
  TCGv temp_2 = tcg_temp_local_new_i32();
  tcg_gen_xori_i32(temp_2, temp_1, 1); tcg_gen_andi_i32(temp_2, temp_2, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, arc_true, done_1);;
  TCGv tmp = tcg_temp_local_new_i32();
  tcg_gen_mov_i32(tmp, readAuxReg(src2));
  writeAuxReg(src2, b);
  tcg_gen_mov_i32(b, tmp);
  gen_set_label(done_1);

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
  tcg_gen_mov_i32(dest, readAuxReg(src));

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
 *    Variables: @a, @b, @c
 *    Functions: getCCFlag
--- code ---
{
  if((getCCFlag () == true))
    {
      @a = ((@b * @c) & 4294967295);
    };
}
 */

int
arc2_gen_MPY (DisasCtxt *ctx, TCGv a, TCGv b, TCGv c)
{
  int ret = BS_NONE;
  TCGLabel *done_1 = gen_new_label();
  TCGv temp_1 = tcg_temp_local_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, getCCFlag(), arc_true);
  TCGv temp_2 = tcg_temp_local_new_i32();
  tcg_gen_xori_i32(temp_2, temp_1, 1); tcg_gen_andi_i32(temp_2, temp_2, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, arc_true, done_1);;
  TCGv temp_3 = tcg_temp_local_new_i32();
  tcg_gen_mul_i32(temp_3, b, c);
  tcg_gen_andi_i32(a, temp_3, 4294967295);
  gen_set_label(done_1);

  return ret;
}





/* ABS
 *    Variables: @src, @dest
 *    Functions: Carry, getFFlag, setZFlag, setNFlag, setCFlag, Zero, setVFlag, getNFlag
--- code ---
{
  alu = (0 - @src);
  if((Carry (@src) == 1))
    {
      @dest = alu;
    }
  else
    {
      @dest = @src;
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
  TCGv alu = tcg_temp_local_new_i32();
  tcg_gen_subfi_i32(alu, 0, src);
  TCGLabel *else_1 = gen_new_label();
  TCGLabel *done_1 = gen_new_label();
  TCGv temp_1 = tcg_temp_local_new_i32();
  tcg_gen_setcondi_i32(TCG_COND_EQ, temp_1, Carry(src), 1);
  TCGv temp_2 = tcg_temp_local_new_i32();
  tcg_gen_xori_i32(temp_2, temp_1, 1); tcg_gen_andi_i32(temp_2, temp_2, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, arc_true, else_1);;
  tcg_gen_mov_i32(dest, alu);
  tcg_gen_br(done_1);
  gen_set_label(else_1);
  tcg_gen_mov_i32(dest, src);
  gen_set_label(done_1);
  TCGLabel *done_2 = gen_new_label();
  TCGv temp_3 = tcg_temp_local_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_3, getFFlag(), arc_true);
  TCGv temp_4 = tcg_temp_local_new_i32();
  tcg_gen_xori_i32(temp_4, temp_3, 1); tcg_gen_andi_i32(temp_4, temp_4, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_4, arc_true, done_2);;
  setZFlag(dest);
  setNFlag(dest);
  TCGv temp_5 = tcg_temp_local_new_i32();
  tcg_gen_mov_i32(temp_5, Zero());
  setCFlag(temp_5);
  TCGv temp_6 = tcg_temp_local_new_i32();
  tcg_gen_mov_i32(temp_6, getNFlag());
  setVFlag(temp_6);
  gen_set_label(done_2);

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
  tcg_gen_shli_i32(tmp1, src, 16);
  TCGv temp_3 = tcg_temp_local_new_i32();
  tcg_gen_shri_i32(temp_3, src, 16);
  TCGv tmp2 = tcg_temp_local_new_i32();
  tcg_gen_andi_i32(tmp2, temp_3, 65535);
  tcg_gen_or_i32(dest, tmp1, tmp2);
  TCGLabel *done_1 = gen_new_label();
  TCGv temp_1 = tcg_temp_local_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, getFFlag(), arc_true);
  TCGv temp_2 = tcg_temp_local_new_i32();
  tcg_gen_xori_i32(temp_2, temp_1, 1); tcg_gen_andi_i32(temp_2, temp_2, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, arc_true, done_1);;
  setZFlag(dest);
  setNFlag(dest);
  gen_set_label(done_1);

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
  tcg_gen_shli_i32(temp_3, src, 24);
  TCGv tmp1 = tcg_temp_local_new_i32();
  tcg_gen_andi_i32(tmp1, temp_3, 4278190080);
  TCGv temp_4 = tcg_temp_local_new_i32();
  tcg_gen_shli_i32(temp_4, src, 8);
  TCGv tmp2 = tcg_temp_local_new_i32();
  tcg_gen_andi_i32(tmp2, temp_4, 16711680);
  TCGv temp_5 = tcg_temp_local_new_i32();
  tcg_gen_shri_i32(temp_5, src, 8);
  TCGv tmp3 = tcg_temp_local_new_i32();
  tcg_gen_andi_i32(tmp3, temp_5, 65280);
  TCGv temp_6 = tcg_temp_local_new_i32();
  tcg_gen_shri_i32(temp_6, src, 24);
  TCGv tmp4 = tcg_temp_local_new_i32();
  tcg_gen_andi_i32(tmp4, temp_6, 255);
  TCGv temp_8 = tcg_temp_local_new_i32();
  tcg_gen_or_i32(temp_8, tmp1, tmp2);
  TCGv temp_7 = tcg_temp_local_new_i32();
  tcg_gen_or_i32(temp_7, temp_8, tmp3);
  tcg_gen_or_i32(dest, temp_7, tmp4);
  TCGLabel *done_1 = gen_new_label();
  TCGv temp_1 = tcg_temp_local_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, getFFlag(), arc_true);
  TCGv temp_2 = tcg_temp_local_new_i32();
  tcg_gen_xori_i32(temp_2, temp_1, 1); tcg_gen_andi_i32(temp_2, temp_2, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, arc_true, done_1);;
  setZFlag(dest);
  setNFlag(dest);
  gen_set_label(done_1);

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
  TCGv temp_3 = tcg_temp_local_new_i32();
  tcg_gen_shli_i32(temp_3, c, 2);
  TCGv temp_2 = tcg_temp_local_new_i32();
  tcg_gen_mov_i32(temp_2, getPCL());
  TCGv temp_1 = tcg_temp_local_new_i32();
  tcg_gen_add_i32(temp_1, temp_2, temp_3);
  setPC(temp_1);

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
  TCGv temp_3 = tcg_temp_local_new_i32();
  tcg_gen_shli_i32(temp_3, c, 1);
  TCGv temp_2 = tcg_temp_local_new_i32();
  tcg_gen_mov_i32(temp_2, getPCL());
  TCGv temp_1 = tcg_temp_local_new_i32();
  tcg_gen_add_i32(temp_1, temp_2, temp_3);
  setPC(temp_1);

  return ret;
}





/* B
 *    Variables: @rd
 *    Functions: shouldExecuteDelaySlot, executeDelaySlot, getCCFlag, setPC, getPCL
--- code ---
{
  if((shouldExecuteDelaySlot () == true))
    {
      executeDelaySlot ();
    };
  if((getCCFlag () == true))
    {
      setPC ((getPCL () + @rd));
    };
}
 */

int
arc2_gen_B (DisasCtxt *ctx, TCGv rd)
{
  int ret = BS_NONE;
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
  TCGv temp_1 = tcg_temp_local_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, getCCFlag(), arc_true);
  TCGv temp_2 = tcg_temp_local_new_i32();
  tcg_gen_xori_i32(temp_2, temp_1, 1); tcg_gen_andi_i32(temp_2, temp_2, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, arc_true, done_1);;
  TCGv temp_4 = tcg_temp_local_new_i32();
  tcg_gen_mov_i32(temp_4, getPCL());
  TCGv temp_3 = tcg_temp_local_new_i32();
  tcg_gen_add_i32(temp_3, temp_4, rd);
  setPC(temp_3);
  gen_set_label(done_1);

  return ret;
}





/* B_S
 *    Variables: @rd
 *    Functions: getCCFlag, killDelaySlot, setPC, getPCL
--- code ---
{
  if((getCCFlag () == true))
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
  TCGLabel *done_1 = gen_new_label();
  TCGv temp_1 = tcg_temp_local_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, getCCFlag(), arc_true);
  TCGv temp_2 = tcg_temp_local_new_i32();
  tcg_gen_xori_i32(temp_2, temp_1, 1); tcg_gen_andi_i32(temp_2, temp_2, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, arc_true, done_1);;
  killDelaySlot();
  TCGv temp_4 = tcg_temp_local_new_i32();
  tcg_gen_mov_i32(temp_4, getPCL());
  TCGv temp_3 = tcg_temp_local_new_i32();
  tcg_gen_add_i32(temp_3, temp_4, rd);
  setPC(temp_3);
  gen_set_label(done_1);

  return ret;
}





/* BBIT0
 *    Variables: @c, @b, @rd
 *    Functions: getCCFlag, shouldExecuteDelaySlot, executeDelaySlot, setPC, getPCL
--- code ---
{
  if((getCCFlag () == true))
    {
      tmp = (1 << @c);
      if(((@b && tmp) == 0))
        {
          if((shouldExecuteDelaySlot () == true))
            {
              executeDelaySlot ();
            };
          setPC ((getPCL () + @rd));
        };
    };
}
 */

int
arc2_gen_BBIT0 (DisasCtxt *ctx, TCGv c, TCGv b, TCGv rd)
{
  int ret = BS_NONE;
  TCGLabel *done_1 = gen_new_label();
  TCGv temp_1 = tcg_temp_local_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, getCCFlag(), arc_true);
  TCGv temp_2 = tcg_temp_local_new_i32();
  tcg_gen_xori_i32(temp_2, temp_1, 1); tcg_gen_andi_i32(temp_2, temp_2, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, arc_true, done_1);;
  TCGv tmp = tcg_temp_local_new_i32();
  tcg_gen_shlfi_i32(tmp, 1, c);
  TCGLabel *done_2 = gen_new_label();
  TCGv temp_3 = tcg_temp_local_new_i32();
  tcg_gen_and_i32(temp_3, b, tmp);
  TCGv temp_4 = tcg_temp_local_new_i32();
  tcg_gen_setcondi_i32(TCG_COND_EQ, temp_4, temp_3, 0);
  TCGv temp_5 = tcg_temp_local_new_i32();
  tcg_gen_xori_i32(temp_5, temp_4, 1); tcg_gen_andi_i32(temp_5, temp_5, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_5, arc_true, done_2);;
  if ((shouldExecuteDelaySlot () == true))
    {
    executeDelaySlot();
;
    }
  else
    {
  ;
    }
  TCGv temp_7 = tcg_temp_local_new_i32();
  tcg_gen_mov_i32(temp_7, getPCL());
  TCGv temp_6 = tcg_temp_local_new_i32();
  tcg_gen_add_i32(temp_6, temp_7, rd);
  setPC(temp_6);
  gen_set_label(done_2);
  gen_set_label(done_1);

  return ret;
}





/* BBIT1
 *    Variables: @c, @b, @rd
 *    Functions: getCCFlag, shouldExecuteDelaySlot, executeDelaySlot, setPC, getPCL
--- code ---
{
  if((getCCFlag () == true))
    {
      tmp = (1 << @c);
      if(((@b && tmp) == 1))
        {
          if((shouldExecuteDelaySlot () == true))
            {
              executeDelaySlot ();
            };
          setPC ((getPCL () + @rd));
        };
    };
}
 */

int
arc2_gen_BBIT1 (DisasCtxt *ctx, TCGv c, TCGv b, TCGv rd)
{
  int ret = BS_NONE;
  TCGLabel *done_1 = gen_new_label();
  TCGv temp_1 = tcg_temp_local_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, getCCFlag(), arc_true);
  TCGv temp_2 = tcg_temp_local_new_i32();
  tcg_gen_xori_i32(temp_2, temp_1, 1); tcg_gen_andi_i32(temp_2, temp_2, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, arc_true, done_1);;
  TCGv tmp = tcg_temp_local_new_i32();
  tcg_gen_shlfi_i32(tmp, 1, c);
  TCGLabel *done_2 = gen_new_label();
  TCGv temp_3 = tcg_temp_local_new_i32();
  tcg_gen_and_i32(temp_3, b, tmp);
  TCGv temp_4 = tcg_temp_local_new_i32();
  tcg_gen_setcondi_i32(TCG_COND_EQ, temp_4, temp_3, 1);
  TCGv temp_5 = tcg_temp_local_new_i32();
  tcg_gen_xori_i32(temp_5, temp_4, 1); tcg_gen_andi_i32(temp_5, temp_5, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_5, arc_true, done_2);;
  if ((shouldExecuteDelaySlot () == true))
    {
    executeDelaySlot();
;
    }
  else
    {
  ;
    }
  TCGv temp_7 = tcg_temp_local_new_i32();
  tcg_gen_mov_i32(temp_7, getPCL());
  TCGv temp_6 = tcg_temp_local_new_i32();
  tcg_gen_add_i32(temp_6, temp_7, rd);
  setPC(temp_6);
  gen_set_label(done_2);
  gen_set_label(done_1);

  return ret;
}





/* BL
 *    Variables: @rd
 *    Functions: shouldExecuteDelaySlot, executeDelaySlot, getCCFlag, setBLINK, nextInsnAddressAfterDelaySlot, nextInsnAddress, setPC, getPCL
--- code ---
{
  if((shouldExecuteDelaySlot () == 1))
    {
      executeDelaySlot ();
    };
  if((getCCFlag () == true))
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
  TCGv temp_1 = tcg_temp_local_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, getCCFlag(), arc_true);
  TCGv temp_2 = tcg_temp_local_new_i32();
  tcg_gen_xori_i32(temp_2, temp_1, 1); tcg_gen_andi_i32(temp_2, temp_2, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, arc_true, done_1);;
  if ((shouldExecuteDelaySlot () == 1))
    {
    TCGv temp_3 = tcg_temp_local_new_i32();
  tcg_gen_mov_i32(temp_3, nextInsnAddressAfterDelaySlot());
  setBLINK(temp_3);
;
    }
  else
    {
    TCGv temp_4 = tcg_temp_local_new_i32();
  tcg_gen_mov_i32(temp_4, nextInsnAddress());
  setBLINK(temp_4);
;
    }
  TCGv temp_6 = tcg_temp_local_new_i32();
  tcg_gen_mov_i32(temp_6, getPCL());
  TCGv temp_5 = tcg_temp_local_new_i32();
  tcg_gen_add_i32(temp_5, temp_6, rd);
  setPC(temp_5);
  gen_set_label(done_1);

  return ret;
}





/* J
 *    Variables: @src
 *    Functions: shouldExecuteDelaySlot, executeDelaySlot, getCCFlag, setPC
--- code ---
{
  if((shouldExecuteDelaySlot () == 1))
    {
      executeDelaySlot ();
    };
  if((getCCFlag () == true))
    {
      setPC (@src);
    };
}
 */

int
arc2_gen_J (DisasCtxt *ctx, TCGv src)
{
  int ret = BS_NONE;
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
  TCGv temp_1 = tcg_temp_local_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, getCCFlag(), arc_true);
  TCGv temp_2 = tcg_temp_local_new_i32();
  tcg_gen_xori_i32(temp_2, temp_1, 1); tcg_gen_andi_i32(temp_2, temp_2, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, arc_true, done_1);;
  setPC(src);
  gen_set_label(done_1);

  return ret;
}





/* JL
 *    Variables: @src
 *    Functions: shouldExecuteDelaySlot, executeDelaySlot, getCCFlag, setBLINK, nextInsnAddressAfterDelaySlot, nextInsnAddress, setPC
--- code ---
{
  if((shouldExecuteDelaySlot () == 1))
    {
      executeDelaySlot ();
    };
  if((getCCFlag () == true))
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
  TCGv temp_1 = tcg_temp_local_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, getCCFlag(), arc_true);
  TCGv temp_2 = tcg_temp_local_new_i32();
  tcg_gen_xori_i32(temp_2, temp_1, 1); tcg_gen_andi_i32(temp_2, temp_2, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, arc_true, done_1);;
  if ((shouldExecuteDelaySlot () == 1))
    {
    TCGv temp_3 = tcg_temp_local_new_i32();
  tcg_gen_mov_i32(temp_3, nextInsnAddressAfterDelaySlot());
  setBLINK(temp_3);
;
    }
  else
    {
    TCGv temp_4 = tcg_temp_local_new_i32();
  tcg_gen_mov_i32(temp_4, nextInsnAddress());
  setBLINK(temp_4);
;
    }
  setPC(src);
  gen_set_label(done_1);

  return ret;
}





/* BREQ
 *    Variables: @b, @c, @offset
 *    Functions: shouldExecuteDelaySlot, executeDelaySlot, setPC, getPCL
--- code ---
{
  if((shouldExecuteDelaySlot () == 1))
    {
      executeDelaySlot ();
    };
  if((@b == @c))
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
  TCGv temp_1 = tcg_temp_local_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, b, c);
  TCGv temp_2 = tcg_temp_local_new_i32();
  tcg_gen_xori_i32(temp_2, temp_1, 1); tcg_gen_andi_i32(temp_2, temp_2, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, arc_true, else_1);;
  TCGv temp_4 = tcg_temp_local_new_i32();
  tcg_gen_mov_i32(temp_4, getPCL());
  TCGv temp_3 = tcg_temp_local_new_i32();
  tcg_gen_add_i32(temp_3, temp_4, offset);
  setPC(temp_3);
  tcg_gen_br(done_1);
  gen_set_label(else_1);
  gen_set_label(done_1);

  return ret;
}





/* BRNE
 *    Variables: @b, @c, @offset
 *    Functions: shouldExecuteDelaySlot, executeDelaySlot, setPC, getPCL
--- code ---
{
  if((shouldExecuteDelaySlot () == 1))
    {
      executeDelaySlot ();
    };
  if((@b != @c))
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
  TCGv temp_1 = tcg_temp_local_new_i32();
  tcg_gen_setcond_i32(TCG_COND_NE, temp_1, b, c);
  TCGv temp_2 = tcg_temp_local_new_i32();
  tcg_gen_xori_i32(temp_2, temp_1, 1); tcg_gen_andi_i32(temp_2, temp_2, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, arc_true, else_1);;
  TCGv temp_4 = tcg_temp_local_new_i32();
  tcg_gen_mov_i32(temp_4, getPCL());
  TCGv temp_3 = tcg_temp_local_new_i32();
  tcg_gen_add_i32(temp_3, temp_4, offset);
  setPC(temp_3);
  tcg_gen_br(done_1);
  gen_set_label(else_1);
  gen_set_label(done_1);

  return ret;
}





/* BRLT
 *    Variables: @b, @c, @offset
 *    Functions: shouldExecuteDelaySlot, executeDelaySlot, setPC, getPCL
--- code ---
{
  if((shouldExecuteDelaySlot () == 1))
    {
      executeDelaySlot ();
    };
  if((@b < @c))
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
  TCGv temp_1 = tcg_temp_local_new_i32();
  tcg_gen_setcond_i32(TCG_COND_LT, temp_1, b, c);
  TCGv temp_2 = tcg_temp_local_new_i32();
  tcg_gen_xori_i32(temp_2, temp_1, 1); tcg_gen_andi_i32(temp_2, temp_2, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, arc_true, else_1);;
  TCGv temp_4 = tcg_temp_local_new_i32();
  tcg_gen_mov_i32(temp_4, getPCL());
  TCGv temp_3 = tcg_temp_local_new_i32();
  tcg_gen_add_i32(temp_3, temp_4, offset);
  setPC(temp_3);
  tcg_gen_br(done_1);
  gen_set_label(else_1);
  gen_set_label(done_1);

  return ret;
}





/* BRGE
 *    Variables: @b, @c, @offset
 *    Functions: shouldExecuteDelaySlot, executeDelaySlot, setPC, getPCL
--- code ---
{
  if((shouldExecuteDelaySlot () == 1))
    {
      executeDelaySlot ();
    };
  if((@b >= @c))
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
  TCGv temp_1 = tcg_temp_local_new_i32();
  tcg_gen_setcond_i32(TCG_COND_GE, temp_1, b, c);
  TCGv temp_2 = tcg_temp_local_new_i32();
  tcg_gen_xori_i32(temp_2, temp_1, 1); tcg_gen_andi_i32(temp_2, temp_2, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, arc_true, else_1);;
  TCGv temp_4 = tcg_temp_local_new_i32();
  tcg_gen_mov_i32(temp_4, getPCL());
  TCGv temp_3 = tcg_temp_local_new_i32();
  tcg_gen_add_i32(temp_3, temp_4, offset);
  setPC(temp_3);
  tcg_gen_br(done_1);
  gen_set_label(else_1);
  gen_set_label(done_1);

  return ret;
}





/* SETEQ
 *    Variables: @b, @c, @a
 *    Functions:
--- code ---
{
  if((@b == @c))
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
arc2_gen_SETEQ (DisasCtxt *ctx, TCGv b, TCGv c, TCGv a)
{
  int ret = BS_NONE;
  TCGLabel *else_1 = gen_new_label();
  TCGLabel *done_1 = gen_new_label();
  TCGv temp_1 = tcg_temp_local_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, b, c);
  TCGv temp_2 = tcg_temp_local_new_i32();
  tcg_gen_xori_i32(temp_2, temp_1, 1); tcg_gen_andi_i32(temp_2, temp_2, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, arc_true, else_1);;
  tcg_gen_mov_i32(a, arc_true);
  tcg_gen_br(done_1);
  gen_set_label(else_1);
  tcg_gen_mov_i32(a, arc_false);
  gen_set_label(done_1);

  return ret;
}





/* SETNE
 *    Variables: @b, @c, @a
 *    Functions:
--- code ---
{
  if((@b != @c))
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
arc2_gen_SETNE (DisasCtxt *ctx, TCGv b, TCGv c, TCGv a)
{
  int ret = BS_NONE;
  TCGLabel *else_1 = gen_new_label();
  TCGLabel *done_1 = gen_new_label();
  TCGv temp_1 = tcg_temp_local_new_i32();
  tcg_gen_setcond_i32(TCG_COND_NE, temp_1, b, c);
  TCGv temp_2 = tcg_temp_local_new_i32();
  tcg_gen_xori_i32(temp_2, temp_1, 1); tcg_gen_andi_i32(temp_2, temp_2, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, arc_true, else_1);;
  tcg_gen_mov_i32(a, arc_true);
  tcg_gen_br(done_1);
  gen_set_label(else_1);
  tcg_gen_mov_i32(a, arc_false);
  gen_set_label(done_1);

  return ret;
}





/* SETLT
 *    Variables: @b, @c, @a
 *    Functions:
--- code ---
{
  if((@b < @c))
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
arc2_gen_SETLT (DisasCtxt *ctx, TCGv b, TCGv c, TCGv a)
{
  int ret = BS_NONE;
  TCGLabel *else_1 = gen_new_label();
  TCGLabel *done_1 = gen_new_label();
  TCGv temp_1 = tcg_temp_local_new_i32();
  tcg_gen_setcond_i32(TCG_COND_LT, temp_1, b, c);
  TCGv temp_2 = tcg_temp_local_new_i32();
  tcg_gen_xori_i32(temp_2, temp_1, 1); tcg_gen_andi_i32(temp_2, temp_2, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, arc_true, else_1);;
  tcg_gen_mov_i32(a, arc_true);
  tcg_gen_br(done_1);
  gen_set_label(else_1);
  tcg_gen_mov_i32(a, arc_false);
  gen_set_label(done_1);

  return ret;
}





/* SETGE
 *    Variables: @b, @c, @a
 *    Functions:
--- code ---
{
  if((@b >= @c))
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
arc2_gen_SETGE (DisasCtxt *ctx, TCGv b, TCGv c, TCGv a)
{
  int ret = BS_NONE;
  TCGLabel *else_1 = gen_new_label();
  TCGLabel *done_1 = gen_new_label();
  TCGv temp_1 = tcg_temp_local_new_i32();
  tcg_gen_setcond_i32(TCG_COND_GE, temp_1, b, c);
  TCGv temp_2 = tcg_temp_local_new_i32();
  tcg_gen_xori_i32(temp_2, temp_1, 1); tcg_gen_andi_i32(temp_2, temp_2, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, arc_true, else_1);;
  tcg_gen_mov_i32(a, arc_true);
  tcg_gen_br(done_1);
  gen_set_label(else_1);
  tcg_gen_mov_i32(a, arc_false);
  gen_set_label(done_1);

  return ret;
}





/* SETLE
 *    Variables: @b, @c, @a
 *    Functions:
--- code ---
{
  if((@b <= @c))
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
arc2_gen_SETLE (DisasCtxt *ctx, TCGv b, TCGv c, TCGv a)
{
  int ret = BS_NONE;
  TCGLabel *else_1 = gen_new_label();
  TCGLabel *done_1 = gen_new_label();
  TCGv temp_1 = tcg_temp_local_new_i32();
  tcg_gen_setcond_i32(TCG_COND_LE, temp_1, b, c);
  TCGv temp_2 = tcg_temp_local_new_i32();
  tcg_gen_xori_i32(temp_2, temp_1, 1); tcg_gen_andi_i32(temp_2, temp_2, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, arc_true, else_1);;
  tcg_gen_mov_i32(a, arc_true);
  tcg_gen_br(done_1);
  gen_set_label(else_1);
  tcg_gen_mov_i32(a, arc_false);
  gen_set_label(done_1);

  return ret;
}





/* SETGT
 *    Variables: @b, @c, @a
 *    Functions:
--- code ---
{
  if((@b > @c))
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
arc2_gen_SETGT (DisasCtxt *ctx, TCGv b, TCGv c, TCGv a)
{
  int ret = BS_NONE;
  TCGLabel *else_1 = gen_new_label();
  TCGLabel *done_1 = gen_new_label();
  TCGv temp_1 = tcg_temp_local_new_i32();
  tcg_gen_setcond_i32(TCG_COND_GT, temp_1, b, c);
  TCGv temp_2 = tcg_temp_local_new_i32();
  tcg_gen_xori_i32(temp_2, temp_1, 1); tcg_gen_andi_i32(temp_2, temp_2, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, arc_true, else_1);;
  tcg_gen_mov_i32(a, arc_true);
  tcg_gen_br(done_1);
  gen_set_label(else_1);
  tcg_gen_mov_i32(a, arc_false);
  gen_set_label(done_1);

  return ret;
}





/* BRLO
 *    Variables: @b, @c, @offset
 *    Functions: unsignedLT, setPC, getPCL
--- code ---
{
  if(unsignedLT (@b, @c))
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
  TCGLabel *else_1 = gen_new_label();
  TCGLabel *done_1 = gen_new_label();
  TCGv temp_1 = tcg_temp_local_new_i32();
  tcg_gen_xori_i32(temp_1, unsignedLT(b, c), 1); tcg_gen_andi_i32(temp_1, temp_1, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_1, arc_true, else_1);;
  TCGv temp_3 = tcg_temp_local_new_i32();
  tcg_gen_mov_i32(temp_3, getPCL());
  TCGv temp_2 = tcg_temp_local_new_i32();
  tcg_gen_add_i32(temp_2, temp_3, offset);
  setPC(temp_2);
  tcg_gen_br(done_1);
  gen_set_label(else_1);
  gen_set_label(done_1);

  return ret;
}





/* SETLO
 *    Variables: @b, @c, @a
 *    Functions: unsignedLT
--- code ---
{
  if(unsignedLT (@b, @c))
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
  TCGLabel *else_1 = gen_new_label();
  TCGLabel *done_1 = gen_new_label();
  TCGv temp_1 = tcg_temp_local_new_i32();
  tcg_gen_xori_i32(temp_1, unsignedLT(b, c), 1); tcg_gen_andi_i32(temp_1, temp_1, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_1, arc_true, else_1);;
  tcg_gen_mov_i32(a, arc_true);
  tcg_gen_br(done_1);
  gen_set_label(else_1);
  tcg_gen_mov_i32(a, arc_false);
  gen_set_label(done_1);

  return ret;
}





/* BRHS
 *    Variables: @b, @c, @offset
 *    Functions: unsignedGE, setPC, getPCL
--- code ---
{
  if(unsignedGE (@b, @c))
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
  TCGLabel *else_1 = gen_new_label();
  TCGLabel *done_1 = gen_new_label();
  TCGv temp_1 = tcg_temp_local_new_i32();
  tcg_gen_xori_i32(temp_1, unsignedGE(b, c), 1); tcg_gen_andi_i32(temp_1, temp_1, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_1, arc_true, else_1);;
  TCGv temp_3 = tcg_temp_local_new_i32();
  tcg_gen_mov_i32(temp_3, getPCL());
  TCGv temp_2 = tcg_temp_local_new_i32();
  tcg_gen_add_i32(temp_2, temp_3, offset);
  setPC(temp_2);
  tcg_gen_br(done_1);
  gen_set_label(else_1);
  gen_set_label(done_1);

  return ret;
}





/* SETHS
 *    Variables: @b, @c, @a
 *    Functions: unsignedGE
--- code ---
{
  if(unsignedGE (@b, @c))
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
  TCGLabel *else_1 = gen_new_label();
  TCGLabel *done_1 = gen_new_label();
  TCGv temp_1 = tcg_temp_local_new_i32();
  tcg_gen_xori_i32(temp_1, unsignedGE(b, c), 1); tcg_gen_andi_i32(temp_1, temp_1, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_1, arc_true, else_1);;
  tcg_gen_mov_i32(a, arc_true);
  tcg_gen_br(done_1);
  gen_set_label(else_1);
  tcg_gen_mov_i32(a, arc_false);
  gen_set_label(done_1);

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
  if(((AA == 3) && (ZZ == 0)))
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
  AA = getAAFlag ();
  int ZZ;
  ZZ = getZZFlag ();
  TCGv address = tcg_temp_local_new_i32();
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
  if (((AA == 3) && (ZZ == 0)))
    {
    TCGv temp_2 = tcg_temp_local_new_i32();
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
    TCGv temp_3 = tcg_temp_local_new_i32();
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
  TCGv temp_4 = tcg_temp_local_new_i32();
  tcg_gen_movi_i32(temp_4, 1);
  setDebugLD(temp_4);
  tcg_gen_mov_i32(dest, getMemory(address, ZZ));
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
  TCGv temp_1 = tcg_temp_local_new_i32();
  tcg_gen_xori_i32(temp_1, NoFurtherLoadsPending(), 1); tcg_gen_andi_i32(temp_1, temp_1, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_1, arc_true, done_1);;
  TCGv temp_5 = tcg_temp_local_new_i32();
  tcg_gen_movi_i32(temp_5, 0);
  setDebugLD(temp_5);
  gen_set_label(done_1);

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
  if(((AA == 3) && (ZZ == 0)))
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
  pair = nextReg (@dest);
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
  AA = getAAFlag ();
  int ZZ;
  ZZ = getZZFlag ();
  TCGv address = tcg_temp_local_new_i32();
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
  if (((AA == 3) && (ZZ == 0)))
    {
    TCGv temp_2 = tcg_temp_local_new_i32();
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
    TCGv temp_3 = tcg_temp_local_new_i32();
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
  TCGv temp_4 = tcg_temp_local_new_i32();
  tcg_gen_movi_i32(temp_4, 1);
  setDebugLD(temp_4);
  tcg_gen_mov_i32(dest, getMemory(address, LONG));
  TCGv pair;
  pair = nextReg (dest);
  TCGv temp_5 = tcg_temp_local_new_i32();
  tcg_gen_addi_i32(temp_5, address, 4);
  tcg_gen_mov_i32(pair, getMemory(temp_5, LONG));
  TCGLabel *done_1 = gen_new_label();
  TCGv temp_1 = tcg_temp_local_new_i32();
  tcg_gen_xori_i32(temp_1, NoFurtherLoadsPending(), 1); tcg_gen_andi_i32(temp_1, temp_1, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_1, arc_true, done_1);;
  TCGv temp_6 = tcg_temp_local_new_i32();
  tcg_gen_movi_i32(temp_6, 0);
  setDebugLD(temp_6);
  gen_set_label(done_1);

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
  if(((AA == 3) && (ZZ == 0)))
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
  AA = getAAFlag ();
  int ZZ;
  ZZ = getZZFlag ();
  TCGv address = tcg_temp_local_new_i32();
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
  if (((AA == 3) && (ZZ == 0)))
    {
    TCGv temp_1 = tcg_temp_local_new_i32();
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
    TCGv temp_2 = tcg_temp_local_new_i32();
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

  return ret;
}





/* STD
 *    Variables: @src1, @src2, @dest
 *    Functions: getAAFlag, getZZFlag, setMemory, nextReg
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
  if(((AA == 3) && (ZZ == 0)))
    {
      address = (@src1 + (@src2 << 2));
    };
  if(((AA == 3) && (ZZ == 2)))
    {
      address = (@src1 + (@src2 << 1));
    };
  setMemory (address, LONG, @dest);
  pair = nextReg (@dest);
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
  AA = getAAFlag ();
  int ZZ;
  ZZ = getZZFlag ();
  TCGv address = tcg_temp_local_new_i32();
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
  if (((AA == 3) && (ZZ == 0)))
    {
    TCGv temp_1 = tcg_temp_local_new_i32();
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
    TCGv temp_2 = tcg_temp_local_new_i32();
  tcg_gen_shli_i32(temp_2, src2, 1);
  tcg_gen_add_i32(address, src1, temp_2);
;
    }
  else
    {
  ;
    }
  setMemory(address, LONG, dest);
  TCGv pair;
  pair = nextReg (dest);
  TCGv temp_3 = tcg_temp_local_new_i32();
  tcg_gen_addi_i32(temp_3, address, 4);
  setMemory(temp_3, LONG, pair);
  if (((AA == 1) || (AA == 2)))
    {
    tcg_gen_add_i32(src1, src1, src2);
;
    }
  else
    {
  ;
    }

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
  TCGv temp_1 = tcg_temp_local_new_i32();
  tcg_gen_mov_i32(temp_1, getRegister(R_SP));
  tcg_gen_mov_i32(dest, getMemory(temp_1, LONG));
  TCGv temp_3 = tcg_temp_local_new_i32();
  tcg_gen_mov_i32(temp_3, getRegister(R_SP));
  TCGv temp_2 = tcg_temp_local_new_i32();
  tcg_gen_addi_i32(temp_2, temp_3, 4);
  setRegister(R_SP, temp_2);

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
  TCGv temp_2 = tcg_temp_local_new_i32();
  tcg_gen_mov_i32(temp_2, getRegister(R_SP));
  TCGv temp_1 = tcg_temp_local_new_i32();
  tcg_gen_subi_i32(temp_1, temp_2, 4);
  setRegister(R_SP, temp_1);
  TCGv temp_3 = tcg_temp_local_new_i32();
  tcg_gen_mov_i32(temp_3, getRegister(R_SP));
  setMemory(temp_3, LONG, src);

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
  TCGLabel *else_1 = gen_new_label();
  TCGLabel *done_1 = gen_new_label();
  TCGv temp_1 = tcg_temp_local_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, getCCFlag(), arc_true);
  TCGv temp_2 = tcg_temp_local_new_i32();
  tcg_gen_xori_i32(temp_2, temp_1, 1); tcg_gen_andi_i32(temp_2, temp_2, 1);;
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, arc_true, else_1);;
  TCGv temp_4 = tcg_temp_local_new_i32();
  tcg_gen_mov_i32(temp_4, nextInsnAddress());
  TCGv temp_3 = tcg_temp_local_new_i32();
  tcg_gen_mov_i32(temp_3, getRegIndex(LP_START));
  writeAuxReg(temp_3, temp_4);
  TCGv temp_7 = tcg_temp_local_new_i32();
  tcg_gen_mov_i32(temp_7, getPCL());
  TCGv temp_5 = tcg_temp_local_new_i32();
  tcg_gen_mov_i32(temp_5, getRegIndex(LP_END));
  TCGv temp_6 = tcg_temp_local_new_i32();
  tcg_gen_add_i32(temp_6, temp_7, rd);
  writeAuxReg(temp_5, temp_6);
  tcg_gen_br(done_1);
  gen_set_label(else_1);
  TCGv temp_9 = tcg_temp_local_new_i32();
  tcg_gen_mov_i32(temp_9, getPCL());
  TCGv temp_8 = tcg_temp_local_new_i32();
  tcg_gen_add_i32(temp_8, temp_9, rd);
  setPC(temp_8);
  gen_set_label(done_1);

  return ret;
}
