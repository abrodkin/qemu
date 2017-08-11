


/* ADD
 *    Variables: @a, @b, @c
 *    Functions: getCCFlag, getFFlag, setZFlag, setNFlag, setCFlag, CarryADD, setVFlag, OverflowADD
 */

int
arc2_gen_ADD (DisasCtxt *ctx, TCGv a, TCGv b, TCGv c)
{
  int ret = BS_NONE;
  TCGLabel *done_1 = gen_new_label();
  TCGv temp_1 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, getCCFlag(), true);
  TCGv temp_2 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_2, temp_1, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, true, done_1);;
  tcg_gen_add_i32(a, b, c);
  TCGLabel *done_2 = gen_new_label();
  TCGv temp_3 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_3, getFFlag(), true);
  TCGv temp_4 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_4, temp_3, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_4, true, done_2);;
  TCGLabel *else_3 = gen_new_label();
  TCGLabel *done_3 = gen_new_label();
  TCGv temp_5 = tcg_temp_new_i32();
  tcg_gen_setcondi_i32(TCG_COND_EQ, temp_5, a, 0);
  TCGv temp_6 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_6, temp_5, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_6, true, else_3);;
  TCGv temp_7 = tcg_temp_new_i32();
  tcg_gen_movi_i32(temp_7, 1);
  setZFlag(temp_7);
  tcg_gen_br(done_3);
  gen_set_label(else_3);
  TCGv temp_8 = tcg_temp_new_i32();
  tcg_gen_movi_i32(temp_8, 0);
  setZFlag(temp_8);
  gen_set_label(done_3);
  setNFlag(a);
  TCGv temp_9 = tcg_temp_new_i32();
  tcg_gen_mov_i32(temp_9, CarryADD(a, b, c));
  setCFlag(temp_9);
  TCGv temp_10 = tcg_temp_new_i32();
  tcg_gen_mov_i32(temp_10, OverflowADD(a, b, c));
  setVFlag(temp_10);
  gen_set_label(done_2);
  gen_set_label(done_1);

  return ret;
}





/* ADD1
 *    Variables: @a, @b, @c
 *    Functions: getCCFlag, getFFlag, setZFlag, setNFlag, setCFlag, CarryADD, setVFlag, OverflowADD
 */

int
arc2_gen_ADD1 (DisasCtxt *ctx, TCGv a, TCGv b, TCGv c)
{
  int ret = BS_NONE;
  TCGLabel *done_1 = gen_new_label();
  TCGv temp_1 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, getCCFlag(), true);
  TCGv temp_2 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_2, temp_1, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, true, done_1);;
  TCGv temp_7 = tcg_temp_new_i32();
  tcg_gen_shli_i32(temp_7, c, 1);
  tcg_gen_add_i32(a, b, temp_7);
  TCGLabel *done_2 = gen_new_label();
  TCGv temp_3 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_3, getFFlag(), true);
  TCGv temp_4 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_4, temp_3, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_4, true, done_2);;
  TCGLabel *else_3 = gen_new_label();
  TCGLabel *done_3 = gen_new_label();
  TCGv temp_5 = tcg_temp_new_i32();
  tcg_gen_setcondi_i32(TCG_COND_EQ, temp_5, a, 0);
  TCGv temp_6 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_6, temp_5, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_6, true, else_3);;
  TCGv temp_8 = tcg_temp_new_i32();
  tcg_gen_movi_i32(temp_8, 1);
  setZFlag(temp_8);
  tcg_gen_br(done_3);
  gen_set_label(else_3);
  TCGv temp_9 = tcg_temp_new_i32();
  tcg_gen_movi_i32(temp_9, 0);
  setZFlag(temp_9);
  gen_set_label(done_3);
  setNFlag(a);
  TCGv temp_10 = tcg_temp_new_i32();
  tcg_gen_mov_i32(temp_10, CarryADD(a, b, c));
  setCFlag(temp_10);
  TCGv temp_11 = tcg_temp_new_i32();
  tcg_gen_mov_i32(temp_11, OverflowADD(a, b, c));
  setVFlag(temp_11);
  gen_set_label(done_2);
  gen_set_label(done_1);

  return ret;
}





/* ADD2
 *    Variables: @a, @b, @c
 *    Functions: getCCFlag, getFFlag, setZFlag, setNFlag, setCFlag, CarryADD, setVFlag, OverflowADD
 */

int
arc2_gen_ADD2 (DisasCtxt *ctx, TCGv a, TCGv b, TCGv c)
{
  int ret = BS_NONE;
  TCGLabel *done_1 = gen_new_label();
  TCGv temp_1 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, getCCFlag(), true);
  TCGv temp_2 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_2, temp_1, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, true, done_1);;
  TCGv temp_7 = tcg_temp_new_i32();
  tcg_gen_shli_i32(temp_7, c, 2);
  tcg_gen_add_i32(a, b, temp_7);
  TCGLabel *done_2 = gen_new_label();
  TCGv temp_3 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_3, getFFlag(), true);
  TCGv temp_4 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_4, temp_3, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_4, true, done_2);;
  TCGLabel *else_3 = gen_new_label();
  TCGLabel *done_3 = gen_new_label();
  TCGv temp_5 = tcg_temp_new_i32();
  tcg_gen_setcondi_i32(TCG_COND_EQ, temp_5, a, 0);
  TCGv temp_6 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_6, temp_5, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_6, true, else_3);;
  TCGv temp_8 = tcg_temp_new_i32();
  tcg_gen_movi_i32(temp_8, 1);
  setZFlag(temp_8);
  tcg_gen_br(done_3);
  gen_set_label(else_3);
  TCGv temp_9 = tcg_temp_new_i32();
  tcg_gen_movi_i32(temp_9, 0);
  setZFlag(temp_9);
  gen_set_label(done_3);
  setNFlag(a);
  TCGv temp_10 = tcg_temp_new_i32();
  tcg_gen_mov_i32(temp_10, CarryADD(a, b, c));
  setCFlag(temp_10);
  TCGv temp_11 = tcg_temp_new_i32();
  tcg_gen_mov_i32(temp_11, OverflowADD(a, b, c));
  setVFlag(temp_11);
  gen_set_label(done_2);
  gen_set_label(done_1);

  return ret;
}





/* ADD3
 *    Variables: @a, @b, @c
 *    Functions: getCCFlag, getFFlag, setZFlag, setNFlag, setCFlag, CarryADD, setVFlag, OverflowADD
 */

int
arc2_gen_ADD3 (DisasCtxt *ctx, TCGv a, TCGv b, TCGv c)
{
  int ret = BS_NONE;
  TCGLabel *done_1 = gen_new_label();
  TCGv temp_1 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, getCCFlag(), true);
  TCGv temp_2 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_2, temp_1, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, true, done_1);;
  TCGv temp_7 = tcg_temp_new_i32();
  tcg_gen_shli_i32(temp_7, c, 3);
  tcg_gen_add_i32(a, b, temp_7);
  TCGLabel *done_2 = gen_new_label();
  TCGv temp_3 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_3, getFFlag(), true);
  TCGv temp_4 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_4, temp_3, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_4, true, done_2);;
  TCGLabel *else_3 = gen_new_label();
  TCGLabel *done_3 = gen_new_label();
  TCGv temp_5 = tcg_temp_new_i32();
  tcg_gen_setcondi_i32(TCG_COND_EQ, temp_5, a, 0);
  TCGv temp_6 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_6, temp_5, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_6, true, else_3);;
  TCGv temp_8 = tcg_temp_new_i32();
  tcg_gen_movi_i32(temp_8, 1);
  setZFlag(temp_8);
  tcg_gen_br(done_3);
  gen_set_label(else_3);
  TCGv temp_9 = tcg_temp_new_i32();
  tcg_gen_movi_i32(temp_9, 0);
  setZFlag(temp_9);
  gen_set_label(done_3);
  setNFlag(a);
  TCGv temp_10 = tcg_temp_new_i32();
  tcg_gen_mov_i32(temp_10, CarryADD(a, b, c));
  setCFlag(temp_10);
  TCGv temp_11 = tcg_temp_new_i32();
  tcg_gen_mov_i32(temp_11, OverflowADD(a, b, c));
  setVFlag(temp_11);
  gen_set_label(done_2);
  gen_set_label(done_1);

  return ret;
}





/* MUL
 *    Variables: @a, @b, @c
 *    Functions: getCCFlag, getFFlag, setZFlag, setNFlag, setCFlag, CarryADD, setVFlag, OverflowADD
 */

int
arc2_gen_MUL (DisasCtxt *ctx, TCGv a, TCGv b, TCGv c)
{
  int ret = BS_NONE;
  TCGLabel *done_1 = gen_new_label();
  TCGv temp_1 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, getCCFlag(), true);
  TCGv temp_2 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_2, temp_1, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, true, done_1);;
  tcg_gen_mul_i32(a, b, c);
  TCGLabel *done_2 = gen_new_label();
  TCGv temp_3 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_3, getFFlag(), true);
  TCGv temp_4 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_4, temp_3, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_4, true, done_2);;
  TCGLabel *else_3 = gen_new_label();
  TCGLabel *done_3 = gen_new_label();
  TCGv temp_5 = tcg_temp_new_i32();
  tcg_gen_setcondi_i32(TCG_COND_EQ, temp_5, a, 0);
  TCGv temp_6 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_6, temp_5, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_6, true, else_3);;
  TCGv temp_7 = tcg_temp_new_i32();
  tcg_gen_movi_i32(temp_7, 1);
  setZFlag(temp_7);
  tcg_gen_br(done_3);
  gen_set_label(else_3);
  TCGv temp_8 = tcg_temp_new_i32();
  tcg_gen_movi_i32(temp_8, 0);
  setZFlag(temp_8);
  gen_set_label(done_3);
  setNFlag(a);
  TCGv temp_9 = tcg_temp_new_i32();
  tcg_gen_mov_i32(temp_9, CarryADD(a, b, c));
  setCFlag(temp_9);
  TCGv temp_10 = tcg_temp_new_i32();
  tcg_gen_mov_i32(temp_10, OverflowADD(a, b, c));
  setVFlag(temp_10);
  gen_set_label(done_2);
  gen_set_label(done_1);

  return ret;
}





/* DIV
 *    Variables: @a, @b, @c
 *    Functions: getCCFlag, getFFlag, setZFlag, setNFlag, setCFlag, CarryADD, setVFlag, OverflowADD
 */

int
arc2_gen_DIV (DisasCtxt *ctx, TCGv a, TCGv b, TCGv c)
{
  int ret = BS_NONE;
  TCGLabel *done_1 = gen_new_label();
  TCGv temp_1 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, getCCFlag(), true);
  TCGv temp_2 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_2, temp_1, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, true, done_1);;
  tcg_gen_div_i32(a, b, c);
  TCGLabel *done_2 = gen_new_label();
  TCGv temp_3 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_3, getFFlag(), true);
  TCGv temp_4 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_4, temp_3, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_4, true, done_2);;
  TCGLabel *else_3 = gen_new_label();
  TCGLabel *done_3 = gen_new_label();
  TCGv temp_5 = tcg_temp_new_i32();
  tcg_gen_setcondi_i32(TCG_COND_EQ, temp_5, a, 0);
  TCGv temp_6 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_6, temp_5, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_6, true, else_3);;
  TCGv temp_7 = tcg_temp_new_i32();
  tcg_gen_movi_i32(temp_7, 1);
  setZFlag(temp_7);
  tcg_gen_br(done_3);
  gen_set_label(else_3);
  TCGv temp_8 = tcg_temp_new_i32();
  tcg_gen_movi_i32(temp_8, 0);
  setZFlag(temp_8);
  gen_set_label(done_3);
  setNFlag(a);
  TCGv temp_9 = tcg_temp_new_i32();
  tcg_gen_mov_i32(temp_9, CarryADD(a, b, c));
  setCFlag(temp_9);
  TCGv temp_10 = tcg_temp_new_i32();
  tcg_gen_mov_i32(temp_10, OverflowADD(a, b, c));
  setVFlag(temp_10);
  gen_set_label(done_2);
  gen_set_label(done_1);

  return ret;
}





/* ADC
 *    Variables: @a, @b, @c
 *    Functions: getCCFlag, getCFlag, getFFlag, setZFlag, setNFlag, setCFlag, CarryADD, setVFlag, OverflowADD
 */

int
arc2_gen_ADC (DisasCtxt *ctx, TCGv a, TCGv b, TCGv c)
{
  int ret = BS_NONE;
  TCGLabel *done_1 = gen_new_label();
  TCGv temp_1 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, getCCFlag(), true);
  TCGv temp_2 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_2, temp_1, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, true, done_1);;
  TCGv temp_8 = tcg_temp_new_i32();
  tcg_gen_mov_i32(temp_8, getCFlag());
  TCGv temp_7 = tcg_temp_new_i32();
  tcg_gen_add_i32(temp_7, b, c);
  tcg_gen_add_i32(a, temp_7, temp_8);
  TCGLabel *done_2 = gen_new_label();
  TCGv temp_3 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_3, getFFlag(), true);
  TCGv temp_4 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_4, temp_3, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_4, true, done_2);;
  TCGLabel *else_3 = gen_new_label();
  TCGLabel *done_3 = gen_new_label();
  TCGv temp_5 = tcg_temp_new_i32();
  tcg_gen_setcondi_i32(TCG_COND_EQ, temp_5, a, 0);
  TCGv temp_6 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_6, temp_5, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_6, true, else_3);;
  TCGv temp_9 = tcg_temp_new_i32();
  tcg_gen_movi_i32(temp_9, 1);
  setZFlag(temp_9);
  tcg_gen_br(done_3);
  gen_set_label(else_3);
  TCGv temp_10 = tcg_temp_new_i32();
  tcg_gen_movi_i32(temp_10, 0);
  setZFlag(temp_10);
  gen_set_label(done_3);
  setNFlag(a);
  TCGv temp_11 = tcg_temp_new_i32();
  tcg_gen_mov_i32(temp_11, CarryADD(a, b, c));
  setCFlag(temp_11);
  TCGv temp_12 = tcg_temp_new_i32();
  tcg_gen_mov_i32(temp_12, OverflowADD(a, b, c));
  setVFlag(temp_12);
  gen_set_label(done_2);
  gen_set_label(done_1);

  return ret;
}





/* SUB
 *    Variables: @a, @b, @c
 *    Functions: getCCFlag, getFFlag, setZFlag, setNFlag, setCFlag, CarrySUB, setVFlag, OverflowSUB
 */

int
arc2_gen_SUB (DisasCtxt *ctx, TCGv a, TCGv b, TCGv c)
{
  int ret = BS_NONE;
  TCGLabel *done_1 = gen_new_label();
  TCGv temp_1 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, getCCFlag(), true);
  TCGv temp_2 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_2, temp_1, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, true, done_1);;
  tcg_gen_sub_i32(a, b, c);
  TCGLabel *done_2 = gen_new_label();
  TCGv temp_3 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_3, getFFlag(), true);
  TCGv temp_4 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_4, temp_3, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_4, true, done_2);;
  TCGLabel *else_3 = gen_new_label();
  TCGLabel *done_3 = gen_new_label();
  TCGv temp_5 = tcg_temp_new_i32();
  tcg_gen_setcondi_i32(TCG_COND_EQ, temp_5, a, 0);
  TCGv temp_6 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_6, temp_5, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_6, true, else_3);;
  TCGv temp_7 = tcg_temp_new_i32();
  tcg_gen_movi_i32(temp_7, 1);
  setZFlag(temp_7);
  tcg_gen_br(done_3);
  gen_set_label(else_3);
  TCGv temp_8 = tcg_temp_new_i32();
  tcg_gen_movi_i32(temp_8, 0);
  setZFlag(temp_8);
  gen_set_label(done_3);
  setNFlag(a);
  TCGv temp_9 = tcg_temp_new_i32();
  tcg_gen_mov_i32(temp_9, CarrySUB(a, b, c));
  setCFlag(temp_9);
  TCGv temp_10 = tcg_temp_new_i32();
  tcg_gen_mov_i32(temp_10, OverflowSUB(a, b, c));
  setVFlag(temp_10);
  gen_set_label(done_2);
  gen_set_label(done_1);

  return ret;
}





/* SUB1
 *    Variables: @a, @b, @c
 *    Functions: getCCFlag, getFFlag, setZFlag, setNFlag, setCFlag, CarrySUB, setVFlag, OverflowSUB
 */

int
arc2_gen_SUB1 (DisasCtxt *ctx, TCGv a, TCGv b, TCGv c)
{
  int ret = BS_NONE;
  TCGLabel *done_1 = gen_new_label();
  TCGv temp_1 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, getCCFlag(), true);
  TCGv temp_2 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_2, temp_1, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, true, done_1);;
  TCGv temp_7 = tcg_temp_new_i32();
  tcg_gen_shli_i32(temp_7, c, 1);
  tcg_gen_sub_i32(a, b, temp_7);
  TCGLabel *done_2 = gen_new_label();
  TCGv temp_3 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_3, getFFlag(), true);
  TCGv temp_4 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_4, temp_3, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_4, true, done_2);;
  TCGLabel *else_3 = gen_new_label();
  TCGLabel *done_3 = gen_new_label();
  TCGv temp_5 = tcg_temp_new_i32();
  tcg_gen_setcondi_i32(TCG_COND_EQ, temp_5, a, 0);
  TCGv temp_6 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_6, temp_5, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_6, true, else_3);;
  TCGv temp_8 = tcg_temp_new_i32();
  tcg_gen_movi_i32(temp_8, 1);
  setZFlag(temp_8);
  tcg_gen_br(done_3);
  gen_set_label(else_3);
  TCGv temp_9 = tcg_temp_new_i32();
  tcg_gen_movi_i32(temp_9, 0);
  setZFlag(temp_9);
  gen_set_label(done_3);
  setNFlag(a);
  TCGv temp_10 = tcg_temp_new_i32();
  tcg_gen_mov_i32(temp_10, CarrySUB(a, b, c));
  setCFlag(temp_10);
  TCGv temp_11 = tcg_temp_new_i32();
  tcg_gen_mov_i32(temp_11, OverflowSUB(a, b, c));
  setVFlag(temp_11);
  gen_set_label(done_2);
  gen_set_label(done_1);

  return ret;
}





/* SUB2
 *    Variables: @a, @b, @c
 *    Functions: getCCFlag, getFFlag, setZFlag, setNFlag, setCFlag, CarrySUB, setVFlag, OverflowSUB
 */

int
arc2_gen_SUB2 (DisasCtxt *ctx, TCGv a, TCGv b, TCGv c)
{
  int ret = BS_NONE;
  TCGLabel *done_1 = gen_new_label();
  TCGv temp_1 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, getCCFlag(), true);
  TCGv temp_2 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_2, temp_1, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, true, done_1);;
  TCGv temp_7 = tcg_temp_new_i32();
  tcg_gen_shli_i32(temp_7, c, 2);
  tcg_gen_sub_i32(a, b, temp_7);
  TCGLabel *done_2 = gen_new_label();
  TCGv temp_3 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_3, getFFlag(), true);
  TCGv temp_4 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_4, temp_3, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_4, true, done_2);;
  TCGLabel *else_3 = gen_new_label();
  TCGLabel *done_3 = gen_new_label();
  TCGv temp_5 = tcg_temp_new_i32();
  tcg_gen_setcondi_i32(TCG_COND_EQ, temp_5, a, 0);
  TCGv temp_6 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_6, temp_5, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_6, true, else_3);;
  TCGv temp_8 = tcg_temp_new_i32();
  tcg_gen_movi_i32(temp_8, 1);
  setZFlag(temp_8);
  tcg_gen_br(done_3);
  gen_set_label(else_3);
  TCGv temp_9 = tcg_temp_new_i32();
  tcg_gen_movi_i32(temp_9, 0);
  setZFlag(temp_9);
  gen_set_label(done_3);
  setNFlag(a);
  TCGv temp_10 = tcg_temp_new_i32();
  tcg_gen_mov_i32(temp_10, CarrySUB(a, b, c));
  setCFlag(temp_10);
  TCGv temp_11 = tcg_temp_new_i32();
  tcg_gen_mov_i32(temp_11, OverflowSUB(a, b, c));
  setVFlag(temp_11);
  gen_set_label(done_2);
  gen_set_label(done_1);

  return ret;
}





/* SUB3
 *    Variables: @a, @b, @c
 *    Functions: getCCFlag, getFFlag, setZFlag, setNFlag, setCFlag, CarrySUB, setVFlag, OverflowSUB
 */

int
arc2_gen_SUB3 (DisasCtxt *ctx, TCGv a, TCGv b, TCGv c)
{
  int ret = BS_NONE;
  TCGLabel *done_1 = gen_new_label();
  TCGv temp_1 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, getCCFlag(), true);
  TCGv temp_2 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_2, temp_1, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, true, done_1);;
  TCGv temp_7 = tcg_temp_new_i32();
  tcg_gen_shli_i32(temp_7, c, 3);
  tcg_gen_sub_i32(a, b, temp_7);
  TCGLabel *done_2 = gen_new_label();
  TCGv temp_3 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_3, getFFlag(), true);
  TCGv temp_4 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_4, temp_3, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_4, true, done_2);;
  TCGLabel *else_3 = gen_new_label();
  TCGLabel *done_3 = gen_new_label();
  TCGv temp_5 = tcg_temp_new_i32();
  tcg_gen_setcondi_i32(TCG_COND_EQ, temp_5, a, 0);
  TCGv temp_6 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_6, temp_5, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_6, true, else_3);;
  TCGv temp_8 = tcg_temp_new_i32();
  tcg_gen_movi_i32(temp_8, 1);
  setZFlag(temp_8);
  tcg_gen_br(done_3);
  gen_set_label(else_3);
  TCGv temp_9 = tcg_temp_new_i32();
  tcg_gen_movi_i32(temp_9, 0);
  setZFlag(temp_9);
  gen_set_label(done_3);
  setNFlag(a);
  TCGv temp_10 = tcg_temp_new_i32();
  tcg_gen_mov_i32(temp_10, CarrySUB(a, b, c));
  setCFlag(temp_10);
  TCGv temp_11 = tcg_temp_new_i32();
  tcg_gen_mov_i32(temp_11, OverflowSUB(a, b, c));
  setVFlag(temp_11);
  gen_set_label(done_2);
  gen_set_label(done_1);

  return ret;
}





/* MAX
 *    Variables: @b, @c, @a
 *    Functions: getCCFlag, getFFlag, setZFlag, setNFlag, setCFlag, CarrySUB, setVFlag, OverflowSUB
 */

int
arc2_gen_MAX (DisasCtxt *ctx, TCGv b, TCGv c, TCGv a)
{
  int ret = BS_NONE;
  TCGLabel *done_1 = gen_new_label();
  TCGv temp_1 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, getCCFlag(), true);
  TCGv temp_2 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_2, temp_1, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, true, done_1);;
  TCGv alu = tcg_temp_new_i32();
  tcg_gen_sub_i32(alu, b, c);
  TCGLabel *else_2 = gen_new_label();
  TCGLabel *done_2 = gen_new_label();
  TCGv temp_3 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_GE, temp_3, c, b);
  TCGv temp_4 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_4, temp_3, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_4, true, else_2);;
  tcg_gen_mov_i32(a, c);
  tcg_gen_br(done_2);
  gen_set_label(else_2);
  tcg_gen_mov_i32(a, b);
  gen_set_label(done_2);
  TCGLabel *done_3 = gen_new_label();
  TCGv temp_5 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_5, getFFlag(), true);
  TCGv temp_6 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_6, temp_5, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_6, true, done_3);;
  TCGLabel *else_4 = gen_new_label();
  TCGLabel *done_4 = gen_new_label();
  TCGv temp_7 = tcg_temp_new_i32();
  tcg_gen_setcondi_i32(TCG_COND_EQ, temp_7, alu, 0);
  TCGv temp_8 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_8, temp_7, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_8, true, else_4);;
  TCGv temp_9 = tcg_temp_new_i32();
  tcg_gen_movi_i32(temp_9, 1);
  setZFlag(temp_9);
  tcg_gen_br(done_4);
  gen_set_label(else_4);
  TCGv temp_10 = tcg_temp_new_i32();
  tcg_gen_movi_i32(temp_10, 0);
  setZFlag(temp_10);
  gen_set_label(done_4);
  setNFlag(alu);
  TCGv temp_11 = tcg_temp_new_i32();
  tcg_gen_mov_i32(temp_11, CarrySUB(a, b, c));
  setCFlag(temp_11);
  TCGv temp_12 = tcg_temp_new_i32();
  tcg_gen_mov_i32(temp_12, OverflowSUB(a, b, c));
  setVFlag(temp_12);
  gen_set_label(done_3);
  gen_set_label(done_1);

  return ret;
}





/* MIN
 *    Variables: @b, @c, @a
 *    Functions: getCCFlag, getFFlag, setZFlag, setNFlag, setCFlag, CarrySUB, setVFlag, OverflowSUB
 */

int
arc2_gen_MIN (DisasCtxt *ctx, TCGv b, TCGv c, TCGv a)
{
  int ret = BS_NONE;
  TCGLabel *done_1 = gen_new_label();
  TCGv temp_1 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, getCCFlag(), true);
  TCGv temp_2 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_2, temp_1, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, true, done_1);;
  TCGv alu = tcg_temp_new_i32();
  tcg_gen_sub_i32(alu, b, c);
  TCGLabel *else_2 = gen_new_label();
  TCGLabel *done_2 = gen_new_label();
  TCGv temp_3 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_LE, temp_3, c, b);
  TCGv temp_4 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_4, temp_3, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_4, true, else_2);;
  tcg_gen_mov_i32(a, c);
  tcg_gen_br(done_2);
  gen_set_label(else_2);
  tcg_gen_mov_i32(a, b);
  gen_set_label(done_2);
  TCGLabel *done_3 = gen_new_label();
  TCGv temp_5 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_5, getFFlag(), true);
  TCGv temp_6 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_6, temp_5, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_6, true, done_3);;
  TCGLabel *else_4 = gen_new_label();
  TCGLabel *done_4 = gen_new_label();
  TCGv temp_7 = tcg_temp_new_i32();
  tcg_gen_setcondi_i32(TCG_COND_EQ, temp_7, alu, 0);
  TCGv temp_8 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_8, temp_7, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_8, true, else_4);;
  TCGv temp_9 = tcg_temp_new_i32();
  tcg_gen_movi_i32(temp_9, 1);
  setZFlag(temp_9);
  tcg_gen_br(done_4);
  gen_set_label(else_4);
  TCGv temp_10 = tcg_temp_new_i32();
  tcg_gen_movi_i32(temp_10, 0);
  setZFlag(temp_10);
  gen_set_label(done_4);
  setNFlag(alu);
  TCGv temp_11 = tcg_temp_new_i32();
  tcg_gen_mov_i32(temp_11, CarrySUB(a, b, c));
  setCFlag(temp_11);
  TCGv temp_12 = tcg_temp_new_i32();
  tcg_gen_mov_i32(temp_12, OverflowSUB(a, b, c));
  setVFlag(temp_12);
  gen_set_label(done_3);
  gen_set_label(done_1);

  return ret;
}





/* AND
 *    Variables: @a, @b, @c
 *    Functions: getCCFlag, getFFlag, setZFlag, setNFlag
 */

int
arc2_gen_AND (DisasCtxt *ctx, TCGv a, TCGv b, TCGv c)
{
  int ret = BS_NONE;
  TCGLabel *done_1 = gen_new_label();
  TCGv temp_1 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, getCCFlag(), true);
  TCGv temp_2 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_2, temp_1, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, true, done_1);;
  tcg_gen_and_i32(a, b, c);
  TCGLabel *done_2 = gen_new_label();
  TCGv temp_3 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_3, getFFlag(), true);
  TCGv temp_4 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_4, temp_3, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_4, true, done_2);;
  TCGLabel *else_3 = gen_new_label();
  TCGLabel *done_3 = gen_new_label();
  TCGv temp_5 = tcg_temp_new_i32();
  tcg_gen_setcondi_i32(TCG_COND_EQ, temp_5, a, 0);
  TCGv temp_6 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_6, temp_5, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_6, true, else_3);;
  TCGv temp_7 = tcg_temp_new_i32();
  tcg_gen_movi_i32(temp_7, 1);
  setZFlag(temp_7);
  tcg_gen_br(done_3);
  gen_set_label(else_3);
  TCGv temp_8 = tcg_temp_new_i32();
  tcg_gen_movi_i32(temp_8, 0);
  setZFlag(temp_8);
  gen_set_label(done_3);
  setNFlag(a);
  gen_set_label(done_2);
  gen_set_label(done_1);

  return ret;
}





/* OR
 *    Variables: @a, @b, @c
 *    Functions: getCCFlag, getFFlag, setZFlag, setNFlag
 */

int
arc2_gen_OR (DisasCtxt *ctx, TCGv a, TCGv b, TCGv c)
{
  int ret = BS_NONE;
  TCGLabel *done_1 = gen_new_label();
  TCGv temp_1 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, getCCFlag(), true);
  TCGv temp_2 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_2, temp_1, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, true, done_1);;
  tcg_gen_or_i32(a, b, c);
  TCGLabel *done_2 = gen_new_label();
  TCGv temp_3 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_3, getFFlag(), true);
  TCGv temp_4 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_4, temp_3, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_4, true, done_2);;
  TCGLabel *else_3 = gen_new_label();
  TCGLabel *done_3 = gen_new_label();
  TCGv temp_5 = tcg_temp_new_i32();
  tcg_gen_setcondi_i32(TCG_COND_EQ, temp_5, a, 0);
  TCGv temp_6 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_6, temp_5, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_6, true, else_3);;
  TCGv temp_7 = tcg_temp_new_i32();
  tcg_gen_movi_i32(temp_7, 1);
  setZFlag(temp_7);
  tcg_gen_br(done_3);
  gen_set_label(else_3);
  TCGv temp_8 = tcg_temp_new_i32();
  tcg_gen_movi_i32(temp_8, 0);
  setZFlag(temp_8);
  gen_set_label(done_3);
  setNFlag(a);
  gen_set_label(done_2);
  gen_set_label(done_1);

  return ret;
}





/* XOR
 *    Variables: @a, @b, @c
 *    Functions: getCCFlag, getFFlag, setZFlag, setNFlag
 */

int
arc2_gen_XOR (DisasCtxt *ctx, TCGv a, TCGv b, TCGv c)
{
  int ret = BS_NONE;
  TCGLabel *done_1 = gen_new_label();
  TCGv temp_1 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, getCCFlag(), true);
  TCGv temp_2 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_2, temp_1, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, true, done_1);;
  tcg_gen_xor_i32(a, b, c);
  TCGLabel *done_2 = gen_new_label();
  TCGv temp_3 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_3, getFFlag(), true);
  TCGv temp_4 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_4, temp_3, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_4, true, done_2);;
  TCGLabel *else_3 = gen_new_label();
  TCGLabel *done_3 = gen_new_label();
  TCGv temp_5 = tcg_temp_new_i32();
  tcg_gen_setcondi_i32(TCG_COND_EQ, temp_5, a, 0);
  TCGv temp_6 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_6, temp_5, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_6, true, else_3);;
  TCGv temp_7 = tcg_temp_new_i32();
  tcg_gen_movi_i32(temp_7, 1);
  setZFlag(temp_7);
  tcg_gen_br(done_3);
  gen_set_label(else_3);
  TCGv temp_8 = tcg_temp_new_i32();
  tcg_gen_movi_i32(temp_8, 0);
  setZFlag(temp_8);
  gen_set_label(done_3);
  setNFlag(a);
  gen_set_label(done_2);
  gen_set_label(done_1);

  return ret;
}





/* MOV
 *    Variables: @a, @b
 *    Functions: getCCFlag, getFFlag, setZFlag, setNFlag
 */

int
arc2_gen_MOV (DisasCtxt *ctx, TCGv a, TCGv b)
{
  int ret = BS_NONE;
  TCGLabel *done_1 = gen_new_label();
  TCGv temp_1 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, getCCFlag(), true);
  TCGv temp_2 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_2, temp_1, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, true, done_1);;
  tcg_gen_mov_i32(a, b);
  TCGLabel *done_2 = gen_new_label();
  TCGv temp_3 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_3, getFFlag(), true);
  TCGv temp_4 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_4, temp_3, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_4, true, done_2);;
  TCGLabel *else_3 = gen_new_label();
  TCGLabel *done_3 = gen_new_label();
  TCGv temp_5 = tcg_temp_new_i32();
  tcg_gen_setcondi_i32(TCG_COND_EQ, temp_5, a, 0);
  TCGv temp_6 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_6, temp_5, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_6, true, else_3);;
  TCGv temp_7 = tcg_temp_new_i32();
  tcg_gen_movi_i32(temp_7, 1);
  setZFlag(temp_7);
  tcg_gen_br(done_3);
  gen_set_label(else_3);
  TCGv temp_8 = tcg_temp_new_i32();
  tcg_gen_movi_i32(temp_8, 0);
  setZFlag(temp_8);
  gen_set_label(done_3);
  setNFlag(a);
  gen_set_label(done_2);
  gen_set_label(done_1);

  return ret;
}





/* ASL
 *    Variables: @a, @b, @c
 *    Functions: getCCFlag, getFFlag, setZFlag, setNFlag, setCFlag, getBit
 */

int
arc2_gen_ASL (DisasCtxt *ctx, TCGv a, TCGv b, TCGv c)
{
  int ret = BS_NONE;
  TCGLabel *done_1 = gen_new_label();
  TCGv temp_1 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, getCCFlag(), true);
  TCGv temp_2 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_2, temp_1, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, true, done_1);;
  tcg_gen_shl_i32(a, b, c);
  TCGLabel *done_2 = gen_new_label();
  TCGv temp_3 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_3, getFFlag(), true);
  TCGv temp_4 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_4, temp_3, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_4, true, done_2);;
  TCGLabel *else_3 = gen_new_label();
  TCGLabel *done_3 = gen_new_label();
  TCGv temp_5 = tcg_temp_new_i32();
  tcg_gen_setcondi_i32(TCG_COND_EQ, temp_5, a, 0);
  TCGv temp_6 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_6, temp_5, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_6, true, else_3);;
  TCGv temp_9 = tcg_temp_new_i32();
  tcg_gen_movi_i32(temp_9, 1);
  setZFlag(temp_9);
  tcg_gen_br(done_3);
  gen_set_label(else_3);
  TCGv temp_10 = tcg_temp_new_i32();
  tcg_gen_movi_i32(temp_10, 0);
  setZFlag(temp_10);
  gen_set_label(done_3);
  setNFlag(a);
  TCGLabel *else_4 = gen_new_label();
  TCGLabel *done_4 = gen_new_label();
  TCGv temp_7 = tcg_temp_new_i32();
  tcg_gen_setcondi_i32(TCG_COND_EQ, temp_7, c, 0);
  TCGv temp_8 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_8, temp_7, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_8, true, else_4);;
  TCGv temp_11 = tcg_temp_new_i32();
  tcg_gen_movi_i32(temp_11, 0);
  setCFlag(temp_11);
  tcg_gen_br(done_4);
  gen_set_label(else_4);
  TCGv temp_13 = tcg_temp_new_i32();
  tcg_gen_subfi_i32(temp_13, 32, c);
  TCGv temp_12 = tcg_temp_new_i32();
  tcg_gen_mov_i32(temp_12, getBit(b, temp_13));
  setCFlag(temp_12);
  gen_set_label(done_4);
  gen_set_label(done_2);
  gen_set_label(done_1);

  return ret;
}





/* ASR
 *    Variables: @a, @b, @c
 *    Functions: getCCFlag, getFFlag, setZFlag, setNFlag, setCFlag, getBit
 */

int
arc2_gen_ASR (DisasCtxt *ctx, TCGv a, TCGv b, TCGv c)
{
  int ret = BS_NONE;
  TCGLabel *done_1 = gen_new_label();
  TCGv temp_1 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, getCCFlag(), true);
  TCGv temp_2 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_2, temp_1, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, true, done_1);;
  tcg_gen_shr_i32(a, b, c);
  TCGLabel *done_2 = gen_new_label();
  TCGv temp_3 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_3, getFFlag(), true);
  TCGv temp_4 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_4, temp_3, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_4, true, done_2);;
  TCGLabel *else_3 = gen_new_label();
  TCGLabel *done_3 = gen_new_label();
  TCGv temp_5 = tcg_temp_new_i32();
  tcg_gen_setcondi_i32(TCG_COND_EQ, temp_5, a, 0);
  TCGv temp_6 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_6, temp_5, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_6, true, else_3);;
  TCGv temp_9 = tcg_temp_new_i32();
  tcg_gen_movi_i32(temp_9, 1);
  setZFlag(temp_9);
  tcg_gen_br(done_3);
  gen_set_label(else_3);
  TCGv temp_10 = tcg_temp_new_i32();
  tcg_gen_movi_i32(temp_10, 0);
  setZFlag(temp_10);
  gen_set_label(done_3);
  setNFlag(a);
  TCGLabel *else_4 = gen_new_label();
  TCGLabel *done_4 = gen_new_label();
  TCGv temp_7 = tcg_temp_new_i32();
  tcg_gen_setcondi_i32(TCG_COND_EQ, temp_7, c, 0);
  TCGv temp_8 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_8, temp_7, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_8, true, else_4);;
  TCGv temp_11 = tcg_temp_new_i32();
  tcg_gen_movi_i32(temp_11, 0);
  setCFlag(temp_11);
  tcg_gen_br(done_4);
  gen_set_label(else_4);
  TCGv temp_13 = tcg_temp_new_i32();
  tcg_gen_subi_i32(temp_13, c, 1);
  TCGv temp_12 = tcg_temp_new_i32();
  tcg_gen_mov_i32(temp_12, getBit(b, temp_13));
  setCFlag(temp_12);
  gen_set_label(done_4);
  gen_set_label(done_2);
  gen_set_label(done_1);

  return ret;
}





/* ASR8
 *    Variables: @a, @b
 *    Functions: getCCFlag, getFFlag, setZFlag, setNFlag
 */

int
arc2_gen_ASR8 (DisasCtxt *ctx, TCGv a, TCGv b)
{
  int ret = BS_NONE;
  TCGLabel *done_1 = gen_new_label();
  TCGv temp_1 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, getCCFlag(), true);
  TCGv temp_2 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_2, temp_1, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, true, done_1);;
  tcg_gen_shri_i32(a, b, 16);
  TCGLabel *done_2 = gen_new_label();
  TCGv temp_3 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_3, getFFlag(), true);
  TCGv temp_4 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_4, temp_3, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_4, true, done_2);;
  TCGLabel *else_3 = gen_new_label();
  TCGLabel *done_3 = gen_new_label();
  TCGv temp_5 = tcg_temp_new_i32();
  tcg_gen_setcondi_i32(TCG_COND_EQ, temp_5, a, 0);
  TCGv temp_6 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_6, temp_5, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_6, true, else_3);;
  TCGv temp_7 = tcg_temp_new_i32();
  tcg_gen_movi_i32(temp_7, 1);
  setZFlag(temp_7);
  tcg_gen_br(done_3);
  gen_set_label(else_3);
  TCGv temp_8 = tcg_temp_new_i32();
  tcg_gen_movi_i32(temp_8, 0);
  setZFlag(temp_8);
  gen_set_label(done_3);
  setNFlag(a);
  gen_set_label(done_2);
  gen_set_label(done_1);

  return ret;
}





/* ASR16
 *    Variables: @a, @b
 *    Functions: getCCFlag, getFFlag, setZFlag, setNFlag
 */

int
arc2_gen_ASR16 (DisasCtxt *ctx, TCGv a, TCGv b)
{
  int ret = BS_NONE;
  TCGLabel *done_1 = gen_new_label();
  TCGv temp_1 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, getCCFlag(), true);
  TCGv temp_2 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_2, temp_1, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, true, done_1);;
  tcg_gen_shri_i32(a, b, 16);
  TCGLabel *done_2 = gen_new_label();
  TCGv temp_3 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_3, getFFlag(), true);
  TCGv temp_4 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_4, temp_3, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_4, true, done_2);;
  TCGLabel *else_3 = gen_new_label();
  TCGLabel *done_3 = gen_new_label();
  TCGv temp_5 = tcg_temp_new_i32();
  tcg_gen_setcondi_i32(TCG_COND_EQ, temp_5, a, 0);
  TCGv temp_6 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_6, temp_5, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_6, true, else_3);;
  TCGv temp_7 = tcg_temp_new_i32();
  tcg_gen_movi_i32(temp_7, 1);
  setZFlag(temp_7);
  tcg_gen_br(done_3);
  gen_set_label(else_3);
  TCGv temp_8 = tcg_temp_new_i32();
  tcg_gen_movi_i32(temp_8, 0);
  setZFlag(temp_8);
  gen_set_label(done_3);
  setNFlag(a);
  gen_set_label(done_2);
  gen_set_label(done_1);

  return ret;
}





/* LSL16
 *    Variables: @a, @b
 *    Functions: getCCFlag, logicalShiftLeft, getFFlag, setZFlag, setNFlag
 */

int
arc2_gen_LSL16 (DisasCtxt *ctx, TCGv a, TCGv b)
{
  int ret = BS_NONE;
  TCGLabel *done_1 = gen_new_label();
  TCGv temp_1 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, getCCFlag(), true);
  TCGv temp_2 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_2, temp_1, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, true, done_1);;
  TCGv temp_7 = tcg_temp_new_i32();
  tcg_gen_movi_i32(temp_7, 16);
  tcg_gen_mov_i32(a, logicalShiftLeft(b, temp_7));
  TCGLabel *done_2 = gen_new_label();
  TCGv temp_3 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_3, getFFlag(), true);
  TCGv temp_4 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_4, temp_3, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_4, true, done_2);;
  TCGLabel *else_3 = gen_new_label();
  TCGLabel *done_3 = gen_new_label();
  TCGv temp_5 = tcg_temp_new_i32();
  tcg_gen_setcondi_i32(TCG_COND_EQ, temp_5, a, 0);
  TCGv temp_6 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_6, temp_5, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_6, true, else_3);;
  TCGv temp_8 = tcg_temp_new_i32();
  tcg_gen_movi_i32(temp_8, 1);
  setZFlag(temp_8);
  tcg_gen_br(done_3);
  gen_set_label(else_3);
  TCGv temp_9 = tcg_temp_new_i32();
  tcg_gen_movi_i32(temp_9, 0);
  setZFlag(temp_9);
  gen_set_label(done_3);
  setNFlag(a);
  gen_set_label(done_2);
  gen_set_label(done_1);

  return ret;
}





/* LSL8
 *    Variables: @a, @b
 *    Functions: getCCFlag, logicalShiftLeft, getFFlag, setZFlag, setNFlag
 */

int
arc2_gen_LSL8 (DisasCtxt *ctx, TCGv a, TCGv b)
{
  int ret = BS_NONE;
  TCGLabel *done_1 = gen_new_label();
  TCGv temp_1 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, getCCFlag(), true);
  TCGv temp_2 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_2, temp_1, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, true, done_1);;
  TCGv temp_7 = tcg_temp_new_i32();
  tcg_gen_movi_i32(temp_7, 8);
  tcg_gen_mov_i32(a, logicalShiftLeft(b, temp_7));
  TCGLabel *done_2 = gen_new_label();
  TCGv temp_3 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_3, getFFlag(), true);
  TCGv temp_4 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_4, temp_3, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_4, true, done_2);;
  TCGLabel *else_3 = gen_new_label();
  TCGLabel *done_3 = gen_new_label();
  TCGv temp_5 = tcg_temp_new_i32();
  tcg_gen_setcondi_i32(TCG_COND_EQ, temp_5, a, 0);
  TCGv temp_6 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_6, temp_5, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_6, true, else_3);;
  TCGv temp_8 = tcg_temp_new_i32();
  tcg_gen_movi_i32(temp_8, 1);
  setZFlag(temp_8);
  tcg_gen_br(done_3);
  gen_set_label(else_3);
  TCGv temp_9 = tcg_temp_new_i32();
  tcg_gen_movi_i32(temp_9, 0);
  setZFlag(temp_9);
  gen_set_label(done_3);
  setNFlag(a);
  gen_set_label(done_2);
  gen_set_label(done_1);

  return ret;
}





/* LSR
 *    Variables: @a, @b, @c
 *    Functions: getCCFlag, logicalShiftRight, getFFlag, setZFlag, setNFlag, setCFlag, getBit
 */

int
arc2_gen_LSR (DisasCtxt *ctx, TCGv a, TCGv b, TCGv c)
{
  int ret = BS_NONE;
  TCGLabel *done_1 = gen_new_label();
  TCGv temp_1 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, getCCFlag(), true);
  TCGv temp_2 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_2, temp_1, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, true, done_1);;
  tcg_gen_mov_i32(a, logicalShiftRight(b, c));
  TCGLabel *done_2 = gen_new_label();
  TCGv temp_3 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_3, getFFlag(), true);
  TCGv temp_4 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_4, temp_3, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_4, true, done_2);;
  TCGLabel *else_3 = gen_new_label();
  TCGLabel *done_3 = gen_new_label();
  TCGv temp_5 = tcg_temp_new_i32();
  tcg_gen_setcondi_i32(TCG_COND_EQ, temp_5, a, 0);
  TCGv temp_6 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_6, temp_5, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_6, true, else_3);;
  TCGv temp_9 = tcg_temp_new_i32();
  tcg_gen_movi_i32(temp_9, 1);
  setZFlag(temp_9);
  tcg_gen_br(done_3);
  gen_set_label(else_3);
  TCGv temp_10 = tcg_temp_new_i32();
  tcg_gen_movi_i32(temp_10, 0);
  setZFlag(temp_10);
  gen_set_label(done_3);
  setNFlag(a);
  TCGLabel *else_4 = gen_new_label();
  TCGLabel *done_4 = gen_new_label();
  TCGv temp_7 = tcg_temp_new_i32();
  tcg_gen_setcondi_i32(TCG_COND_EQ, temp_7, c, 0);
  TCGv temp_8 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_8, temp_7, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_8, true, else_4);;
  TCGv temp_11 = tcg_temp_new_i32();
  tcg_gen_movi_i32(temp_11, 0);
  setCFlag(temp_11);
  tcg_gen_br(done_4);
  gen_set_label(else_4);
  TCGv temp_13 = tcg_temp_new_i32();
  tcg_gen_subi_i32(temp_13, c, 1);
  TCGv temp_12 = tcg_temp_new_i32();
  tcg_gen_mov_i32(temp_12, getBit(b, temp_13));
  setCFlag(temp_12);
  gen_set_label(done_4);
  gen_set_label(done_2);
  gen_set_label(done_1);

  return ret;
}





/* LSR16
 *    Variables: @a, @b
 *    Functions: getCCFlag, logicalShiftRight, getFFlag, setZFlag, setNFlag
 */

int
arc2_gen_LSR16 (DisasCtxt *ctx, TCGv a, TCGv b)
{
  int ret = BS_NONE;
  TCGLabel *done_1 = gen_new_label();
  TCGv temp_1 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, getCCFlag(), true);
  TCGv temp_2 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_2, temp_1, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, true, done_1);;
  TCGv temp_7 = tcg_temp_new_i32();
  tcg_gen_movi_i32(temp_7, 16);
  tcg_gen_mov_i32(a, logicalShiftRight(b, temp_7));
  TCGLabel *done_2 = gen_new_label();
  TCGv temp_3 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_3, getFFlag(), true);
  TCGv temp_4 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_4, temp_3, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_4, true, done_2);;
  TCGLabel *else_3 = gen_new_label();
  TCGLabel *done_3 = gen_new_label();
  TCGv temp_5 = tcg_temp_new_i32();
  tcg_gen_setcondi_i32(TCG_COND_EQ, temp_5, a, 0);
  TCGv temp_6 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_6, temp_5, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_6, true, else_3);;
  TCGv temp_8 = tcg_temp_new_i32();
  tcg_gen_movi_i32(temp_8, 1);
  setZFlag(temp_8);
  tcg_gen_br(done_3);
  gen_set_label(else_3);
  TCGv temp_9 = tcg_temp_new_i32();
  tcg_gen_movi_i32(temp_9, 0);
  setZFlag(temp_9);
  gen_set_label(done_3);
  setNFlag(a);
  gen_set_label(done_2);
  gen_set_label(done_1);

  return ret;
}





/* LSR8
 *    Variables: @a, @b
 *    Functions: getCCFlag, logicalShiftRight, getFFlag, setZFlag, setNFlag
 */

int
arc2_gen_LSR8 (DisasCtxt *ctx, TCGv a, TCGv b)
{
  int ret = BS_NONE;
  TCGLabel *done_1 = gen_new_label();
  TCGv temp_1 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, getCCFlag(), true);
  TCGv temp_2 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_2, temp_1, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, true, done_1);;
  TCGv temp_7 = tcg_temp_new_i32();
  tcg_gen_movi_i32(temp_7, 8);
  tcg_gen_mov_i32(a, logicalShiftRight(b, temp_7));
  TCGLabel *done_2 = gen_new_label();
  TCGv temp_3 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_3, getFFlag(), true);
  TCGv temp_4 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_4, temp_3, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_4, true, done_2);;
  TCGLabel *else_3 = gen_new_label();
  TCGLabel *done_3 = gen_new_label();
  TCGv temp_5 = tcg_temp_new_i32();
  tcg_gen_setcondi_i32(TCG_COND_EQ, temp_5, a, 0);
  TCGv temp_6 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_6, temp_5, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_6, true, else_3);;
  TCGv temp_8 = tcg_temp_new_i32();
  tcg_gen_movi_i32(temp_8, 1);
  setZFlag(temp_8);
  tcg_gen_br(done_3);
  gen_set_label(else_3);
  TCGv temp_9 = tcg_temp_new_i32();
  tcg_gen_movi_i32(temp_9, 0);
  setZFlag(temp_9);
  gen_set_label(done_3);
  setNFlag(a);
  gen_set_label(done_2);
  gen_set_label(done_1);

  return ret;
}





/* BIC
 *    Variables: @a, @b, @c
 *    Functions: getCCFlag, getFFlag, setZFlag, setNFlag
 */

int
arc2_gen_BIC (DisasCtxt *ctx, TCGv a, TCGv b, TCGv c)
{
  int ret = BS_NONE;
  TCGLabel *done_1 = gen_new_label();
  TCGv temp_1 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, getCCFlag(), true);
  TCGv temp_2 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_2, temp_1, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, true, done_1);;
  TCGv temp_7 = tcg_temp_new_i32();
  tcg_gen_neg_i32(temp_7, c);
  tcg_gen_and_i32(a, b, temp_7);
  TCGLabel *done_2 = gen_new_label();
  TCGv temp_3 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_3, getFFlag(), true);
  TCGv temp_4 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_4, temp_3, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_4, true, done_2);;
  TCGLabel *else_3 = gen_new_label();
  TCGLabel *done_3 = gen_new_label();
  TCGv temp_5 = tcg_temp_new_i32();
  tcg_gen_setcondi_i32(TCG_COND_EQ, temp_5, a, 0);
  TCGv temp_6 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_6, temp_5, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_6, true, else_3);;
  TCGv temp_8 = tcg_temp_new_i32();
  tcg_gen_movi_i32(temp_8, 1);
  setZFlag(temp_8);
  tcg_gen_br(done_3);
  gen_set_label(else_3);
  TCGv temp_9 = tcg_temp_new_i32();
  tcg_gen_movi_i32(temp_9, 0);
  setZFlag(temp_9);
  gen_set_label(done_3);
  setNFlag(a);
  gen_set_label(done_2);
  gen_set_label(done_1);

  return ret;
}





/* BCLR
 *    Variables: @c, @a, @b
 *    Functions: getCCFlag, getFFlag, setZFlag, setNFlag
 */

int
arc2_gen_BCLR (DisasCtxt *ctx, TCGv c, TCGv a, TCGv b)
{
  int ret = BS_NONE;
  TCGLabel *done_1 = gen_new_label();
  TCGv temp_1 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, getCCFlag(), true);
  TCGv temp_2 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_2, temp_1, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, true, done_1);;
  TCGv temp_7 = tcg_temp_new_i32();
  tcg_gen_andi_i32(temp_7, c, 31);
  TCGv tmp = tcg_temp_new_i32();
  tcg_gen_shlfi_i32(tmp, 1, temp_7);
  TCGv temp_8 = tcg_temp_new_i32();
  tcg_gen_neg_i32(temp_8, tmp);
  tcg_gen_and_i32(a, b, temp_8);
  TCGLabel *done_2 = gen_new_label();
  TCGv temp_3 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_3, getFFlag(), true);
  TCGv temp_4 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_4, temp_3, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_4, true, done_2);;
  TCGLabel *else_3 = gen_new_label();
  TCGLabel *done_3 = gen_new_label();
  TCGv temp_5 = tcg_temp_new_i32();
  tcg_gen_setcondi_i32(TCG_COND_EQ, temp_5, a, 0);
  TCGv temp_6 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_6, temp_5, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_6, true, else_3);;
  TCGv temp_9 = tcg_temp_new_i32();
  tcg_gen_movi_i32(temp_9, 1);
  setZFlag(temp_9);
  tcg_gen_br(done_3);
  gen_set_label(else_3);
  TCGv temp_10 = tcg_temp_new_i32();
  tcg_gen_movi_i32(temp_10, 0);
  setZFlag(temp_10);
  gen_set_label(done_3);
  setNFlag(a);
  gen_set_label(done_2);
  gen_set_label(done_1);

  return ret;
}





/* TST
 *    Variables: @b, @c
 *    Functions: getCCFlag, getFFlag, setZFlag, setNFlag
 */

int
arc2_gen_TST (DisasCtxt *ctx, TCGv b, TCGv c)
{
  int ret = BS_NONE;
  TCGLabel *done_1 = gen_new_label();
  TCGv temp_1 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, getCCFlag(), true);
  TCGv temp_2 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_2, temp_1, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, true, done_1);;
  TCGv alu = tcg_temp_new_i32();
  tcg_gen_and_i32(alu, b, c);
  TCGLabel *done_2 = gen_new_label();
  TCGv temp_3 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_3, getFFlag(), true);
  TCGv temp_4 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_4, temp_3, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_4, true, done_2);;
  TCGLabel *else_3 = gen_new_label();
  TCGLabel *done_3 = gen_new_label();
  TCGv temp_5 = tcg_temp_new_i32();
  tcg_gen_setcondi_i32(TCG_COND_EQ, temp_5, alu, 0);
  TCGv temp_6 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_6, temp_5, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_6, true, else_3);;
  TCGv temp_7 = tcg_temp_new_i32();
  tcg_gen_movi_i32(temp_7, 1);
  setZFlag(temp_7);
  tcg_gen_br(done_3);
  gen_set_label(else_3);
  TCGv temp_8 = tcg_temp_new_i32();
  tcg_gen_movi_i32(temp_8, 0);
  setZFlag(temp_8);
  gen_set_label(done_3);
  setNFlag(alu);
  gen_set_label(done_2);
  gen_set_label(done_1);

  return ret;
}





/* BMSK
 *    Variables: @c, @a, @b
 *    Functions: getCCFlag, getFFlag, setZFlag, setNFlag
 */

int
arc2_gen_BMSK (DisasCtxt *ctx, TCGv c, TCGv a, TCGv b)
{
  int ret = BS_NONE;
  TCGLabel *done_1 = gen_new_label();
  TCGv temp_1 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, getCCFlag(), true);
  TCGv temp_2 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_2, temp_1, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, true, done_1);;
  TCGv temp_7 = tcg_temp_new_i32();
  tcg_gen_andi_i32(temp_7, c, 31);
  TCGv tmp1 = tcg_temp_new_i32();
  tcg_gen_addi_i32(tmp1, temp_7, 1);
  TCGv temp_8 = tcg_temp_new_i32();
  tcg_gen_shlfi_i32(temp_8, 1, tmp1);
  TCGv tmp2 = tcg_temp_new_i32();
  tcg_gen_subi_i32(tmp2, temp_8, 1);
  tcg_gen_and_i32(a, b, tmp2);
  TCGLabel *done_2 = gen_new_label();
  TCGv temp_3 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_3, getFFlag(), true);
  TCGv temp_4 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_4, temp_3, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_4, true, done_2);;
  TCGLabel *else_3 = gen_new_label();
  TCGLabel *done_3 = gen_new_label();
  TCGv temp_5 = tcg_temp_new_i32();
  tcg_gen_setcondi_i32(TCG_COND_EQ, temp_5, a, 0);
  TCGv temp_6 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_6, temp_5, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_6, true, else_3);;
  TCGv temp_9 = tcg_temp_new_i32();
  tcg_gen_movi_i32(temp_9, 1);
  setZFlag(temp_9);
  tcg_gen_br(done_3);
  gen_set_label(else_3);
  TCGv temp_10 = tcg_temp_new_i32();
  tcg_gen_movi_i32(temp_10, 0);
  setZFlag(temp_10);
  gen_set_label(done_3);
  setNFlag(a);
  gen_set_label(done_2);
  gen_set_label(done_1);

  return ret;
}





/* BMSKN
 *    Variables: @c, @a, @b
 *    Functions: getCCFlag, getFFlag, setZFlag, setNFlag
 */

int
arc2_gen_BMSKN (DisasCtxt *ctx, TCGv c, TCGv a, TCGv b)
{
  int ret = BS_NONE;
  TCGLabel *done_1 = gen_new_label();
  TCGv temp_1 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, getCCFlag(), true);
  TCGv temp_2 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_2, temp_1, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, true, done_1);;
  TCGv temp_7 = tcg_temp_new_i32();
  tcg_gen_andi_i32(temp_7, c, 31);
  TCGv tmp1 = tcg_temp_new_i32();
  tcg_gen_addi_i32(tmp1, temp_7, 1);
  TCGv temp_8 = tcg_temp_new_i32();
  tcg_gen_shlfi_i32(temp_8, 1, tmp1);
  TCGv tmp2 = tcg_temp_new_i32();
  tcg_gen_subi_i32(tmp2, temp_8, 1);
  TCGv temp_9 = tcg_temp_new_i32();
  tcg_gen_neg_i32(temp_9, tmp2);
  tcg_gen_and_i32(a, b, temp_9);
  TCGLabel *done_2 = gen_new_label();
  TCGv temp_3 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_3, getFFlag(), true);
  TCGv temp_4 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_4, temp_3, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_4, true, done_2);;
  TCGLabel *else_3 = gen_new_label();
  TCGLabel *done_3 = gen_new_label();
  TCGv temp_5 = tcg_temp_new_i32();
  tcg_gen_setcondi_i32(TCG_COND_EQ, temp_5, a, 0);
  TCGv temp_6 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_6, temp_5, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_6, true, else_3);;
  TCGv temp_10 = tcg_temp_new_i32();
  tcg_gen_movi_i32(temp_10, 1);
  setZFlag(temp_10);
  tcg_gen_br(done_3);
  gen_set_label(else_3);
  TCGv temp_11 = tcg_temp_new_i32();
  tcg_gen_movi_i32(temp_11, 0);
  setZFlag(temp_11);
  gen_set_label(done_3);
  setNFlag(a);
  gen_set_label(done_2);
  gen_set_label(done_1);

  return ret;
}





/* BSET
 *    Variables: @c, @a, @b
 *    Functions: getCCFlag, getFFlag, setZFlag, setNFlag
 */

int
arc2_gen_BSET (DisasCtxt *ctx, TCGv c, TCGv a, TCGv b)
{
  int ret = BS_NONE;
  TCGLabel *done_1 = gen_new_label();
  TCGv temp_1 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, getCCFlag(), true);
  TCGv temp_2 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_2, temp_1, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, true, done_1);;
  TCGv temp_7 = tcg_temp_new_i32();
  tcg_gen_andi_i32(temp_7, c, 31);
  TCGv tmp = tcg_temp_new_i32();
  tcg_gen_shlfi_i32(tmp, 1, temp_7);
  tcg_gen_or_i32(a, b, tmp);
  TCGLabel *done_2 = gen_new_label();
  TCGv temp_3 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_3, getFFlag(), true);
  TCGv temp_4 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_4, temp_3, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_4, true, done_2);;
  TCGLabel *else_3 = gen_new_label();
  TCGLabel *done_3 = gen_new_label();
  TCGv temp_5 = tcg_temp_new_i32();
  tcg_gen_setcondi_i32(TCG_COND_EQ, temp_5, a, 0);
  TCGv temp_6 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_6, temp_5, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_6, true, else_3);;
  TCGv temp_8 = tcg_temp_new_i32();
  tcg_gen_movi_i32(temp_8, 1);
  setZFlag(temp_8);
  tcg_gen_br(done_3);
  gen_set_label(else_3);
  TCGv temp_9 = tcg_temp_new_i32();
  tcg_gen_movi_i32(temp_9, 0);
  setZFlag(temp_9);
  gen_set_label(done_3);
  setNFlag(a);
  gen_set_label(done_2);
  gen_set_label(done_1);

  return ret;
}





/* BTST
 *    Variables: @c, @b
 *    Functions: getCCFlag, getFFlag, setZFlag, setNFlag
 */

int
arc2_gen_BTST (DisasCtxt *ctx, TCGv c, TCGv b)
{
  int ret = BS_NONE;
  TCGLabel *done_1 = gen_new_label();
  TCGv temp_1 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, getCCFlag(), true);
  TCGv temp_2 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_2, temp_1, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, true, done_1);;
  TCGv temp_7 = tcg_temp_new_i32();
  tcg_gen_andi_i32(temp_7, c, 31);
  TCGv tmp = tcg_temp_new_i32();
  tcg_gen_shlfi_i32(tmp, 1, temp_7);
  TCGv alu = tcg_temp_new_i32();
  tcg_gen_and_i32(alu, b, tmp);
  TCGLabel *done_2 = gen_new_label();
  TCGv temp_3 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_3, getFFlag(), true);
  TCGv temp_4 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_4, temp_3, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_4, true, done_2);;
  TCGLabel *else_3 = gen_new_label();
  TCGLabel *done_3 = gen_new_label();
  TCGv temp_5 = tcg_temp_new_i32();
  tcg_gen_setcondi_i32(TCG_COND_EQ, temp_5, alu, 0);
  TCGv temp_6 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_6, temp_5, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_6, true, else_3);;
  TCGv temp_8 = tcg_temp_new_i32();
  tcg_gen_movi_i32(temp_8, 1);
  setZFlag(temp_8);
  tcg_gen_br(done_3);
  gen_set_label(else_3);
  TCGv temp_9 = tcg_temp_new_i32();
  tcg_gen_movi_i32(temp_9, 0);
  setZFlag(temp_9);
  gen_set_label(done_3);
  setNFlag(alu);
  gen_set_label(done_2);
  gen_set_label(done_1);

  return ret;
}





/* MPY
 *    Variables: @a, @b, @c
 *    Functions: getCCFlag
 */

int
arc2_gen_MPY (DisasCtxt *ctx, TCGv a, TCGv b, TCGv c)
{
  int ret = BS_NONE;
  TCGLabel *done_1 = gen_new_label();
  TCGv temp_1 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, getCCFlag(), true);
  TCGv temp_2 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_2, temp_1, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, true, done_1);;
  TCGv temp_3 = tcg_temp_new_i32();
  tcg_gen_mul_i32(temp_3, b, c);
  tcg_gen_andi_i32(a, temp_3, 4294967295);
  gen_set_label(done_1);

  return ret;
}





/* ABS
 *    Variables: @src, @dest
 *    Functions: Carry, getFFlag, setZFlag, setNFlag, setCFlag, Zero, setVFlag, getNFlag
 */

int
arc2_gen_ABS (DisasCtxt *ctx, TCGv src, TCGv dest)
{
  int ret = BS_NONE;
  TCGv alu = tcg_temp_new_i32();
  tcg_gen_subfi_i32(alu, 0, src);
  TCGLabel *else_1 = gen_new_label();
  TCGLabel *done_1 = gen_new_label();
  TCGv temp_1 = tcg_temp_new_i32();
  tcg_gen_setcondi_i32(TCG_COND_EQ, temp_1, Carry(src), 1);
  TCGv temp_2 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_2, temp_1, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, true, else_1);;
  tcg_gen_mov_i32(dest, alu);
  tcg_gen_br(done_1);
  gen_set_label(else_1);
  tcg_gen_mov_i32(dest, src);
  gen_set_label(done_1);
  TCGLabel *done_2 = gen_new_label();
  TCGv temp_3 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_3, getFFlag(), true);
  TCGv temp_4 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_4, temp_3, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_4, true, done_2);;
  TCGLabel *else_3 = gen_new_label();
  TCGLabel *done_3 = gen_new_label();
  TCGv temp_5 = tcg_temp_new_i32();
  tcg_gen_setcondi_i32(TCG_COND_EQ, temp_5, dest, 0);
  TCGv temp_6 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_6, temp_5, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_6, true, else_3);;
  TCGv temp_7 = tcg_temp_new_i32();
  tcg_gen_movi_i32(temp_7, 1);
  setZFlag(temp_7);
  tcg_gen_br(done_3);
  gen_set_label(else_3);
  TCGv temp_8 = tcg_temp_new_i32();
  tcg_gen_movi_i32(temp_8, 0);
  setZFlag(temp_8);
  gen_set_label(done_3);
  setNFlag(dest);
  TCGv temp_9 = tcg_temp_new_i32();
  tcg_gen_mov_i32(temp_9, Zero());
  setCFlag(temp_9);
  TCGv temp_10 = tcg_temp_new_i32();
  tcg_gen_mov_i32(temp_10, getNFlag());
  setVFlag(temp_10);
  gen_set_label(done_2);

  return ret;
}





/* B
 *    Variables: @rd
 *    Functions: getCCFlag, shouldExecuteDelaySlot, executeDelaySlot, setPC, getPCL
 */

int
arc2_gen_B (DisasCtxt *ctx, TCGv rd)
{
  int ret = BS_NONE;
  TCGLabel *done_1 = gen_new_label();
  TCGv temp_1 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, getCCFlag(), true);
  TCGv temp_2 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_2, temp_1, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, true, done_1);;
  if ((shouldExecuteDelaySlot () == true))
    {
    executeDelaySlot();
;
    }
  TCGv temp_4 = tcg_temp_new_i32();
  tcg_gen_mov_i32(temp_4, getPCL());
  TCGv temp_3 = tcg_temp_new_i32();
  tcg_gen_add_i32(temp_3, temp_4, rd);
  setPC(temp_3);
  gen_set_label(done_1);

  return ret;
}





/* B_S
 *    Variables: @rd
 *    Functions: getCCFlag, killDelaySlot, setPC, getPC
 */

int
arc2_gen_B_S (DisasCtxt *ctx, TCGv rd)
{
  int ret = BS_NONE;
  TCGLabel *done_1 = gen_new_label();
  TCGv temp_1 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, getCCFlag(), true);
  TCGv temp_2 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_2, temp_1, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, true, done_1);;
  killDelaySlot();
  TCGv temp_4 = tcg_temp_new_i32();
  tcg_gen_mov_i32(temp_4, getPC());
  TCGv temp_3 = tcg_temp_new_i32();
  tcg_gen_add_i32(temp_3, temp_4, rd);
  setPC(temp_3);
  gen_set_label(done_1);

  return ret;
}





/* BBIT0
 *    Variables: @c, @b, @rd
 *    Functions: getCCFlag, shouldExecuteDelaySlot, executeDelaySlot, setPC, getPCL
 */

int
arc2_gen_BBIT0 (DisasCtxt *ctx, TCGv c, TCGv b, TCGv rd)
{
  int ret = BS_NONE;
  TCGLabel *done_1 = gen_new_label();
  TCGv temp_1 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, getCCFlag(), true);
  TCGv temp_2 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_2, temp_1, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, true, done_1);;
  TCGv tmp = tcg_temp_new_i32();
  tcg_gen_shlfi_i32(tmp, 1, c);
  TCGLabel *done_2 = gen_new_label();
  TCGv temp_3 = tcg_temp_new_i32();
  tcg_gen_and_i32(temp_3, b, tmp);
  TCGv temp_4 = tcg_temp_new_i32();
  tcg_gen_setcondi_i32(TCG_COND_EQ, temp_4, temp_3, 0);
  TCGv temp_5 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_5, temp_4, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_5, true, done_2);;
  if ((shouldExecuteDelaySlot () == true))
    {
    executeDelaySlot();
;
    }
  TCGv temp_7 = tcg_temp_new_i32();
  tcg_gen_mov_i32(temp_7, getPCL());
  TCGv temp_6 = tcg_temp_new_i32();
  tcg_gen_add_i32(temp_6, temp_7, rd);
  setPC(temp_6);
  gen_set_label(done_2);
  gen_set_label(done_1);

  return ret;
}





/* BBIT1
 *    Variables: @c, @b, @rd
 *    Functions: getCCFlag, shouldExecuteDelaySlot, executeDelaySlot, setPC, getPCL
 */

int
arc2_gen_BBIT1 (DisasCtxt *ctx, TCGv c, TCGv b, TCGv rd)
{
  int ret = BS_NONE;
  TCGLabel *done_1 = gen_new_label();
  TCGv temp_1 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, getCCFlag(), true);
  TCGv temp_2 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_2, temp_1, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, true, done_1);;
  TCGv tmp = tcg_temp_new_i32();
  tcg_gen_shlfi_i32(tmp, 1, c);
  TCGLabel *done_2 = gen_new_label();
  TCGv temp_3 = tcg_temp_new_i32();
  tcg_gen_and_i32(temp_3, b, tmp);
  TCGv temp_4 = tcg_temp_new_i32();
  tcg_gen_setcondi_i32(TCG_COND_EQ, temp_4, temp_3, 1);
  TCGv temp_5 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_5, temp_4, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_5, true, done_2);;
  if ((shouldExecuteDelaySlot () == true))
    {
    executeDelaySlot();
;
    }
  TCGv temp_7 = tcg_temp_new_i32();
  tcg_gen_mov_i32(temp_7, getPCL());
  TCGv temp_6 = tcg_temp_new_i32();
  tcg_gen_add_i32(temp_6, temp_7, rd);
  setPC(temp_6);
  gen_set_label(done_2);
  gen_set_label(done_1);

  return ret;
}





/* BL
 *    Variables: @rd
 *    Functions: getCCFlag, shouldExecuteDelaySlot, setBLINK, nextInsnAddressAfterDelaySlot, executeDelaySlot, nextInsnAddress, setPC, getPCL
 */

int
arc2_gen_BL (DisasCtxt *ctx, TCGv rd)
{
  int ret = BS_NONE;
  TCGLabel *done_1 = gen_new_label();
  TCGv temp_1 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, getCCFlag(), true);
  TCGv temp_2 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_2, temp_1, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, true, done_1);;
  if ((shouldExecuteDelaySlot () == 1))
    {
    TCGv temp_3 = tcg_temp_new_i32();
  tcg_gen_mov_i32(temp_3, nextInsnAddressAfterDelaySlot());
  setBLINK(temp_3);
  executeDelaySlot();
;
    }
  TCGv temp_6 = tcg_temp_new_i32();
  tcg_gen_mov_i32(temp_6, getPCL());
  TCGv temp_5 = tcg_temp_new_i32();
  tcg_gen_add_i32(temp_5, temp_6, rd);
  setPC(temp_5);
  gen_set_label(done_1);

  return ret;
}





/* J
 *    Variables: @src
 *    Functions: getCCFlag, shouldExecuteDelaySlot, executeDelaySlot, setPC
 */

int
arc2_gen_J (DisasCtxt *ctx, TCGv src)
{
  int ret = BS_NONE;
  TCGLabel *done_1 = gen_new_label();
  TCGv temp_1 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, getCCFlag(), true);
  TCGv temp_2 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_2, temp_1, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, true, done_1);;
  if ((shouldExecuteDelaySlot () == 1))
    {
    executeDelaySlot();
;
    }
  setPC(src);
  gen_set_label(done_1);

  return ret;
}





/* JL
 *    Variables: @src
 *    Functions: getCCFlag, shouldExecuteDelaySlot, setBLINK, nextInsnAddressAfterDelaySlot, executeDelaySlot, nextInsnAddress, setPC
 */

int
arc2_gen_JL (DisasCtxt *ctx, TCGv src)
{
  int ret = BS_NONE;
  TCGLabel *done_1 = gen_new_label();
  TCGv temp_1 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, getCCFlag(), true);
  TCGv temp_2 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_2, temp_1, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, true, done_1);;
  if ((shouldExecuteDelaySlot () == 1))
    {
    TCGv temp_3 = tcg_temp_new_i32();
  tcg_gen_mov_i32(temp_3, nextInsnAddressAfterDelaySlot());
  setBLINK(temp_3);
  executeDelaySlot();
;
    }
  setPC(src);
  gen_set_label(done_1);

  return ret;
}





/* CMP
 *    Variables: @src1, @src2
 *    Functions: getCCFlag, setZFlag, setNFlag, setCFlag, CarrySUB, setVFlag, OverflowSUB
 */

int
arc2_gen_CMP (DisasCtxt *ctx, TCGv src1, TCGv src2)
{
  int ret = BS_NONE;
  TCGLabel *done_1 = gen_new_label();
  TCGv temp_1 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, getCCFlag(), true);
  TCGv temp_2 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_2, temp_1, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, true, done_1);;
  TCGv alu = tcg_temp_new_i32();
  tcg_gen_sub_i32(alu, src1, src2);
  TCGLabel *else_2 = gen_new_label();
  TCGLabel *done_2 = gen_new_label();
  TCGv temp_3 = tcg_temp_new_i32();
  tcg_gen_setcondi_i32(TCG_COND_EQ, temp_3, alu, 0);
  TCGv temp_4 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_4, temp_3, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_4, true, else_2);;
  TCGv temp_5 = tcg_temp_new_i32();
  tcg_gen_movi_i32(temp_5, 1);
  setZFlag(temp_5);
  tcg_gen_br(done_2);
  gen_set_label(else_2);
  TCGv temp_6 = tcg_temp_new_i32();
  tcg_gen_movi_i32(temp_6, 0);
  setZFlag(temp_6);
  gen_set_label(done_2);
  setNFlag(alu);
  TCGv temp_7 = tcg_temp_new_i32();
  tcg_gen_mov_i32(temp_7, CarrySUB(alu, src1, src2));
  setCFlag(temp_7);
  TCGv temp_8 = tcg_temp_new_i32();
  tcg_gen_mov_i32(temp_8, OverflowSUB(alu, src1, src2));
  setVFlag(temp_8);
  gen_set_label(done_1);

  return ret;
}





/* BREQ
 *    Variables: @b, @c, @offset
 *    Functions: setPC, getPCL
 */

int
arc2_gen_BREQ (DisasCtxt *ctx, TCGv b, TCGv c, TCGv offset)
{
  int ret = BS_NONE;
  TCGLabel *else_1 = gen_new_label();
  TCGLabel *done_1 = gen_new_label();
  TCGv temp_1 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, b, c);
  TCGv temp_2 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_2, temp_1, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, true, else_1);;
  TCGv temp_4 = tcg_temp_new_i32();
  tcg_gen_mov_i32(temp_4, getPCL());
  TCGv temp_3 = tcg_temp_new_i32();
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
 */

int
arc2_gen_SETEQ (DisasCtxt *ctx, TCGv b, TCGv c, TCGv a)
{
  int ret = BS_NONE;
  TCGLabel *else_1 = gen_new_label();
  TCGLabel *done_1 = gen_new_label();
  TCGv temp_1 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_1, b, c);
  TCGv temp_2 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_2, temp_1, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, true, else_1);;
  tcg_gen_mov_i32(a, true);
  tcg_gen_br(done_1);
  gen_set_label(else_1);
  tcg_gen_mov_i32(a, false);
  gen_set_label(done_1);

  return ret;
}





/* BRNE
 *    Variables: @b, @c, @offset
 *    Functions: setPC, getPCL
 */

int
arc2_gen_BRNE (DisasCtxt *ctx, TCGv b, TCGv c, TCGv offset)
{
  int ret = BS_NONE;
  TCGLabel *else_1 = gen_new_label();
  TCGLabel *done_1 = gen_new_label();
  TCGv temp_1 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_NE, temp_1, b, c);
  TCGv temp_2 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_2, temp_1, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, true, else_1);;
  TCGv temp_4 = tcg_temp_new_i32();
  tcg_gen_mov_i32(temp_4, getPCL());
  TCGv temp_3 = tcg_temp_new_i32();
  tcg_gen_add_i32(temp_3, temp_4, offset);
  setPC(temp_3);
  tcg_gen_br(done_1);
  gen_set_label(else_1);
  gen_set_label(done_1);

  return ret;
}





/* SETNE
 *    Variables: @b, @c, @a
 *    Functions:
 */

int
arc2_gen_SETNE (DisasCtxt *ctx, TCGv b, TCGv c, TCGv a)
{
  int ret = BS_NONE;
  TCGLabel *else_1 = gen_new_label();
  TCGLabel *done_1 = gen_new_label();
  TCGv temp_1 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_NE, temp_1, b, c);
  TCGv temp_2 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_2, temp_1, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, true, else_1);;
  tcg_gen_mov_i32(a, true);
  tcg_gen_br(done_1);
  gen_set_label(else_1);
  tcg_gen_mov_i32(a, false);
  gen_set_label(done_1);

  return ret;
}





/* BRLT
 *    Variables: @b, @c, @offset
 *    Functions: setPC, getPCL
 */

int
arc2_gen_BRLT (DisasCtxt *ctx, TCGv b, TCGv c, TCGv offset)
{
  int ret = BS_NONE;
  TCGLabel *else_1 = gen_new_label();
  TCGLabel *done_1 = gen_new_label();
  TCGv temp_1 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_LT, temp_1, b, c);
  TCGv temp_2 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_2, temp_1, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, true, else_1);;
  TCGv temp_4 = tcg_temp_new_i32();
  tcg_gen_mov_i32(temp_4, getPCL());
  TCGv temp_3 = tcg_temp_new_i32();
  tcg_gen_add_i32(temp_3, temp_4, offset);
  setPC(temp_3);
  tcg_gen_br(done_1);
  gen_set_label(else_1);
  gen_set_label(done_1);

  return ret;
}





/* SETLT
 *    Variables: @b, @c, @a
 *    Functions:
 */

int
arc2_gen_SETLT (DisasCtxt *ctx, TCGv b, TCGv c, TCGv a)
{
  int ret = BS_NONE;
  TCGLabel *else_1 = gen_new_label();
  TCGLabel *done_1 = gen_new_label();
  TCGv temp_1 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_LT, temp_1, b, c);
  TCGv temp_2 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_2, temp_1, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, true, else_1);;
  tcg_gen_mov_i32(a, true);
  tcg_gen_br(done_1);
  gen_set_label(else_1);
  tcg_gen_mov_i32(a, false);
  gen_set_label(done_1);

  return ret;
}





/* BRGE
 *    Variables: @b, @c, @offset
 *    Functions: setPC, getPCL
 */

int
arc2_gen_BRGE (DisasCtxt *ctx, TCGv b, TCGv c, TCGv offset)
{
  int ret = BS_NONE;
  TCGLabel *else_1 = gen_new_label();
  TCGLabel *done_1 = gen_new_label();
  TCGv temp_1 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_GE, temp_1, b, c);
  TCGv temp_2 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_2, temp_1, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, true, else_1);;
  TCGv temp_4 = tcg_temp_new_i32();
  tcg_gen_mov_i32(temp_4, getPCL());
  TCGv temp_3 = tcg_temp_new_i32();
  tcg_gen_add_i32(temp_3, temp_4, offset);
  setPC(temp_3);
  tcg_gen_br(done_1);
  gen_set_label(else_1);
  gen_set_label(done_1);

  return ret;
}





/* SETGE
 *    Variables: @b, @c, @a
 *    Functions:
 */

int
arc2_gen_SETGE (DisasCtxt *ctx, TCGv b, TCGv c, TCGv a)
{
  int ret = BS_NONE;
  TCGLabel *else_1 = gen_new_label();
  TCGLabel *done_1 = gen_new_label();
  TCGv temp_1 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_GE, temp_1, b, c);
  TCGv temp_2 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_2, temp_1, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, true, else_1);;
  tcg_gen_mov_i32(a, true);
  tcg_gen_br(done_1);
  gen_set_label(else_1);
  tcg_gen_mov_i32(a, false);
  gen_set_label(done_1);

  return ret;
}





/* SETLE
 *    Variables: @b, @c, @a
 *    Functions:
 */

int
arc2_gen_SETLE (DisasCtxt *ctx, TCGv b, TCGv c, TCGv a)
{
  int ret = BS_NONE;
  TCGLabel *else_1 = gen_new_label();
  TCGLabel *done_1 = gen_new_label();
  TCGv temp_1 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_LE, temp_1, b, c);
  TCGv temp_2 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_2, temp_1, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, true, else_1);;
  tcg_gen_mov_i32(a, true);
  tcg_gen_br(done_1);
  gen_set_label(else_1);
  tcg_gen_mov_i32(a, false);
  gen_set_label(done_1);

  return ret;
}





/* SETGT
 *    Variables: @b, @c, @a
 *    Functions:
 */

int
arc2_gen_SETGT (DisasCtxt *ctx, TCGv b, TCGv c, TCGv a)
{
  int ret = BS_NONE;
  TCGLabel *else_1 = gen_new_label();
  TCGLabel *done_1 = gen_new_label();
  TCGv temp_1 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_GT, temp_1, b, c);
  TCGv temp_2 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_2, temp_1, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_2, true, else_1);;
  tcg_gen_mov_i32(a, true);
  tcg_gen_br(done_1);
  gen_set_label(else_1);
  tcg_gen_mov_i32(a, false);
  gen_set_label(done_1);

  return ret;
}





/* BRLO
 *    Variables: @b, @c, @offset
 *    Functions: unsignedLT, setPC, getPCL
 */

int
arc2_gen_BRLO (DisasCtxt *ctx, TCGv b, TCGv c, TCGv offset)
{
  int ret = BS_NONE;
  TCGLabel *else_1 = gen_new_label();
  TCGLabel *done_1 = gen_new_label();
  TCGv temp_1 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_1, unsignedLT(b, c), 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_1, true, else_1);;
  TCGv temp_3 = tcg_temp_new_i32();
  tcg_gen_mov_i32(temp_3, getPCL());
  TCGv temp_2 = tcg_temp_new_i32();
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
 */

int
arc2_gen_SETLO (DisasCtxt *ctx, TCGv b, TCGv c, TCGv a)
{
  int ret = BS_NONE;
  TCGLabel *else_1 = gen_new_label();
  TCGLabel *done_1 = gen_new_label();
  TCGv temp_1 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_1, unsignedLT(b, c), 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_1, true, else_1);;
  tcg_gen_mov_i32(a, true);
  tcg_gen_br(done_1);
  gen_set_label(else_1);
  tcg_gen_mov_i32(a, false);
  gen_set_label(done_1);

  return ret;
}





/* BRHS
 *    Variables: @b, @c, @offset
 *    Functions: unsignedGE, setPC, getPCL
 */

int
arc2_gen_BRHS (DisasCtxt *ctx, TCGv b, TCGv c, TCGv offset)
{
  int ret = BS_NONE;
  TCGLabel *else_1 = gen_new_label();
  TCGLabel *done_1 = gen_new_label();
  TCGv temp_1 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_1, unsignedGE(b, c), 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_1, true, else_1);;
  TCGv temp_3 = tcg_temp_new_i32();
  tcg_gen_mov_i32(temp_3, getPCL());
  TCGv temp_2 = tcg_temp_new_i32();
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
 */

int
arc2_gen_SETHS (DisasCtxt *ctx, TCGv b, TCGv c, TCGv a)
{
  int ret = BS_NONE;
  TCGLabel *else_1 = gen_new_label();
  TCGLabel *done_1 = gen_new_label();
  TCGv temp_1 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_1, unsignedGE(b, c), 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_1, true, else_1);;
  tcg_gen_mov_i32(a, true);
  tcg_gen_br(done_1);
  gen_set_label(else_1);
  tcg_gen_mov_i32(a, false);
  gen_set_label(done_1);

  return ret;
}





/* LD
 *    Variables: @src1, @src2, @dest
 *    Functions: getAAFlag, getZZFlag, setDebugLD, getMemory, getFlagX, SignExtend, NoFurtherLoadsPending
 */

int
arc2_gen_LD (DisasCtxt *ctx, TCGv src1, TCGv src2, TCGv dest)
{
  int ret = BS_NONE;
  int AA;
  AA = getAAFlag ();
  int ZZ;
  ZZ = getZZFlag ();
  TCGv address = tcg_temp_new_i32();
  tcg_gen_movi_i32(address, 0);
  if (((AA == 0) || (AA == 1)))
    {
    tcg_gen_add_i32(address, src1, src2);
;
    }
  if ((AA == 2))
    {
    tcg_gen_mov_i32(address, src1);
;
    }
  if (((AA == 3) && (ZZ == 0)))
    {
    TCGv temp_2 = tcg_temp_new_i32();
  tcg_gen_shli_i32(temp_2, src2, 2);
  tcg_gen_add_i32(address, src1, temp_2);
;
    }
  if (((AA == 3) && (ZZ == 2)))
    {
    TCGv temp_3 = tcg_temp_new_i32();
  tcg_gen_shli_i32(temp_3, src2, 1);
  tcg_gen_add_i32(address, src1, temp_3);
;
    }
  if (((AA == 1) || (AA == 2)))
    {
    tcg_gen_add_i32(src1, src1, src2);
;
    }
  TCGv temp_4 = tcg_temp_new_i32();
  tcg_gen_movi_i32(temp_4, 1);
  setDebugLD(temp_4);
  tcg_gen_mov_i32(dest, getMemory(address, ZZ));
  if ((getFlagX () == 1))
    {
    tcg_gen_mov_i32(dest, SignExtend(dest, ZZ));
;
    }
  TCGLabel *done_1 = gen_new_label();
  TCGv temp_1 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_1, NoFurtherLoadsPending(), 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_1, true, done_1);;
  TCGv temp_5 = tcg_temp_new_i32();
  tcg_gen_movi_i32(temp_5, 0);
  setDebugLD(temp_5);
  gen_set_label(done_1);

  return ret;
}





/* ST
 *    Variables: @src1, @src2, @dest
 *    Functions: getAAFlag, getZZFlag, setMemory
 */

int
arc2_gen_ST (DisasCtxt *ctx, TCGv src1, TCGv src2, TCGv dest)
{
  int ret = BS_NONE;
  int AA;
  AA = getAAFlag ();
  int ZZ;
  ZZ = getZZFlag ();
  TCGv address = tcg_temp_new_i32();
  tcg_gen_movi_i32(address, 0);
  if (((AA == 0) || (AA == 1)))
    {
    tcg_gen_add_i32(address, src1, src2);
;
    }
  if ((AA == 2))
    {
    tcg_gen_mov_i32(address, src1);
;
    }
  if (((AA == 3) && (ZZ == 0)))
    {
    TCGv temp_1 = tcg_temp_new_i32();
  tcg_gen_shli_i32(temp_1, src2, 2);
  tcg_gen_add_i32(address, src1, temp_1);
;
    }
  if (((AA == 3) && (ZZ == 2)))
    {
    TCGv temp_2 = tcg_temp_new_i32();
  tcg_gen_shli_i32(temp_2, src2, 1);
  tcg_gen_add_i32(address, src1, temp_2);
;
    }
  setMemory(address, ZZ, dest);
  if (((AA == 1) || (AA == 2)))
    {
    tcg_gen_add_i32(src1, src1, src2);
;
    }

  return ret;
}
