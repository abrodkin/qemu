


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
  setZFlag(1);
  tcg_gen_br(done_3);
  gen_set_label(else_3);
  setZFlag(0);
  gen_set_label(done_3);
  setNFlag(a);
  tcg_gen_mov_i32(temp_1, CarryADD(a, b, c));
  setCFlag(temp_1);
  tcg_gen_mov_i32(temp_2, OverflowADD(a, b, c));
  setVFlag(temp_2);
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
  TCGv temp_3 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_3, getCCFlag(), true);
  TCGv temp_4 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_4, temp_3, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_4, true, done_1);;
  TCGv temp_1 = tcg_temp_new_i32();
  tcg_gen_shli_i32(temp_1, c, 1);
  tcg_gen_add_i32(a, b, temp_1);
  TCGLabel *done_2 = gen_new_label();
  TCGv temp_5 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_5, getFFlag(), true);
  TCGv temp_6 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_6, temp_5, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_6, true, done_2);;
  TCGLabel *else_3 = gen_new_label();
  TCGLabel *done_3 = gen_new_label();
  TCGv temp_7 = tcg_temp_new_i32();
  tcg_gen_setcondi_i32(TCG_COND_EQ, temp_7, a, 0);
  TCGv temp_8 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_8, temp_7, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_8, true, else_3);;
  setZFlag(1);
  tcg_gen_br(done_3);
  gen_set_label(else_3);
  setZFlag(0);
  gen_set_label(done_3);
  setNFlag(a);
  TCGv temp_2 = tcg_temp_new_i32();
  tcg_gen_mov_i32(temp_2, CarryADD(a, b, c));
  setCFlag(temp_2);
  tcg_gen_mov_i32(temp_3, OverflowADD(a, b, c));
  setVFlag(temp_3);
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
  TCGv temp_4 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_4, getCCFlag(), true);
  TCGv temp_5 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_5, temp_4, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_5, true, done_1);;
  TCGv temp_1 = tcg_temp_new_i32();
  tcg_gen_shli_i32(temp_1, c, 2);
  tcg_gen_add_i32(a, b, temp_1);
  TCGLabel *done_2 = gen_new_label();
  TCGv temp_6 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_6, getFFlag(), true);
  TCGv temp_7 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_7, temp_6, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_7, true, done_2);;
  TCGLabel *else_3 = gen_new_label();
  TCGLabel *done_3 = gen_new_label();
  TCGv temp_8 = tcg_temp_new_i32();
  tcg_gen_setcondi_i32(TCG_COND_EQ, temp_8, a, 0);
  TCGv temp_9 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_9, temp_8, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_9, true, else_3);;
  setZFlag(1);
  tcg_gen_br(done_3);
  gen_set_label(else_3);
  setZFlag(0);
  gen_set_label(done_3);
  setNFlag(a);
  TCGv temp_2 = tcg_temp_new_i32();
  tcg_gen_mov_i32(temp_2, CarryADD(a, b, c));
  setCFlag(temp_2);
  TCGv temp_3 = tcg_temp_new_i32();
  tcg_gen_mov_i32(temp_3, OverflowADD(a, b, c));
  setVFlag(temp_3);
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
  TCGv temp_4 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_4, getCCFlag(), true);
  TCGv temp_5 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_5, temp_4, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_5, true, done_1);;
  TCGv temp_1 = tcg_temp_new_i32();
  tcg_gen_shli_i32(temp_1, c, 3);
  tcg_gen_add_i32(a, b, temp_1);
  TCGLabel *done_2 = gen_new_label();
  TCGv temp_6 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_6, getFFlag(), true);
  TCGv temp_7 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_7, temp_6, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_7, true, done_2);;
  TCGLabel *else_3 = gen_new_label();
  TCGLabel *done_3 = gen_new_label();
  TCGv temp_8 = tcg_temp_new_i32();
  tcg_gen_setcondi_i32(TCG_COND_EQ, temp_8, a, 0);
  TCGv temp_9 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_9, temp_8, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_9, true, else_3);;
  setZFlag(1);
  tcg_gen_br(done_3);
  gen_set_label(else_3);
  setZFlag(0);
  gen_set_label(done_3);
  setNFlag(a);
  TCGv temp_2 = tcg_temp_new_i32();
  tcg_gen_mov_i32(temp_2, CarryADD(a, b, c));
  setCFlag(temp_2);
  TCGv temp_3 = tcg_temp_new_i32();
  tcg_gen_mov_i32(temp_3, OverflowADD(a, b, c));
  setVFlag(temp_3);
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
  TCGv temp_4 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_4, getCCFlag(), true);
  TCGv temp_5 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_5, temp_4, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_5, true, done_1);;
  tcg_gen_mul_i32(a, b, c);
  TCGLabel *done_2 = gen_new_label();
  TCGv temp_6 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_6, getFFlag(), true);
  TCGv temp_7 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_7, temp_6, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_7, true, done_2);;
  TCGLabel *else_3 = gen_new_label();
  TCGLabel *done_3 = gen_new_label();
  TCGv temp_8 = tcg_temp_new_i32();
  tcg_gen_setcondi_i32(TCG_COND_EQ, temp_8, a, 0);
  TCGv temp_9 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_9, temp_8, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_9, true, else_3);;
  setZFlag(1);
  tcg_gen_br(done_3);
  gen_set_label(else_3);
  setZFlag(0);
  gen_set_label(done_3);
  setNFlag(a);
  TCGv temp_1 = tcg_temp_new_i32();
  tcg_gen_mov_i32(temp_1, CarryADD(a, b, c));
  setCFlag(temp_1);
  TCGv temp_2 = tcg_temp_new_i32();
  tcg_gen_mov_i32(temp_2, OverflowADD(a, b, c));
  setVFlag(temp_2);
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
  TCGv temp_3 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_3, getCCFlag(), true);
  TCGv temp_4 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_4, temp_3, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_4, true, done_1);;
  tcg_gen_div_i32(a, b, c);
  TCGLabel *done_2 = gen_new_label();
  TCGv temp_5 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_5, getFFlag(), true);
  TCGv temp_6 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_6, temp_5, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_6, true, done_2);;
  TCGLabel *else_3 = gen_new_label();
  TCGLabel *done_3 = gen_new_label();
  TCGv temp_7 = tcg_temp_new_i32();
  tcg_gen_setcondi_i32(TCG_COND_EQ, temp_7, a, 0);
  TCGv temp_8 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_8, temp_7, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_8, true, else_3);;
  setZFlag(1);
  tcg_gen_br(done_3);
  gen_set_label(else_3);
  setZFlag(0);
  gen_set_label(done_3);
  setNFlag(a);
  TCGv temp_1 = tcg_temp_new_i32();
  tcg_gen_mov_i32(temp_1, CarryADD(a, b, c));
  setCFlag(temp_1);
  TCGv temp_2 = tcg_temp_new_i32();
  tcg_gen_mov_i32(temp_2, OverflowADD(a, b, c));
  setVFlag(temp_2);
  gen_set_label(done_2);
  gen_set_label(done_1);

  return ret;
}





/* AND
 *    Variables: @a, @b, @c
 *    Functions: getCCFlag, getFFlag, setZFlag, setNFlag, setCFlag, CarryADD, setVFlag, OverflowADD
 */

int
arc2_gen_AND (DisasCtxt *ctx, TCGv a, TCGv b, TCGv c)
{
  int ret = BS_NONE;
  TCGLabel *done_1 = gen_new_label();
  TCGv temp_3 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_3, getCCFlag(), true);
  TCGv temp_4 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_4, temp_3, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_4, true, done_1);;
  tcg_gen_and_i32(a, b, c);
  TCGLabel *done_2 = gen_new_label();
  TCGv temp_5 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_5, getFFlag(), true);
  TCGv temp_6 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_6, temp_5, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_6, true, done_2);;
  TCGLabel *else_3 = gen_new_label();
  TCGLabel *done_3 = gen_new_label();
  TCGv temp_7 = tcg_temp_new_i32();
  tcg_gen_setcondi_i32(TCG_COND_EQ, temp_7, a, 0);
  TCGv temp_8 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_8, temp_7, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_8, true, else_3);;
  setZFlag(1);
  tcg_gen_br(done_3);
  gen_set_label(else_3);
  setZFlag(0);
  gen_set_label(done_3);
  setNFlag(a);
  TCGv temp_1 = tcg_temp_new_i32();
  tcg_gen_mov_i32(temp_1, CarryADD(a, b, c));
  setCFlag(temp_1);
  TCGv temp_2 = tcg_temp_new_i32();
  tcg_gen_mov_i32(temp_2, OverflowADD(a, b, c));
  setVFlag(temp_2);
  gen_set_label(done_2);
  gen_set_label(done_1);

  return ret;
}





/* OR
 *    Variables: @a, @b, @c
 *    Functions: getCCFlag, getFFlag, setZFlag, setNFlag, setCFlag, CarryADD, setVFlag, OverflowADD
 */

int
arc2_gen_OR (DisasCtxt *ctx, TCGv a, TCGv b, TCGv c)
{
  int ret = BS_NONE;
  TCGLabel *done_1 = gen_new_label();
  TCGv temp_3 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_3, getCCFlag(), true);
  TCGv temp_4 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_4, temp_3, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_4, true, done_1);;
  tcg_gen_or_i32(a, b, c);
  TCGLabel *done_2 = gen_new_label();
  TCGv temp_5 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_5, getFFlag(), true);
  TCGv temp_6 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_6, temp_5, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_6, true, done_2);;
  TCGLabel *else_3 = gen_new_label();
  TCGLabel *done_3 = gen_new_label();
  TCGv temp_7 = tcg_temp_new_i32();
  tcg_gen_setcondi_i32(TCG_COND_EQ, temp_7, a, 0);
  TCGv temp_8 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_8, temp_7, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_8, true, else_3);;
  setZFlag(1);
  tcg_gen_br(done_3);
  gen_set_label(else_3);
  setZFlag(0);
  gen_set_label(done_3);
  setNFlag(a);
  TCGv temp_1 = tcg_temp_new_i32();
  tcg_gen_mov_i32(temp_1, CarryADD(a, b, c));
  setCFlag(temp_1);
  TCGv temp_2 = tcg_temp_new_i32();
  tcg_gen_mov_i32(temp_2, OverflowADD(a, b, c));
  setVFlag(temp_2);
  gen_set_label(done_2);
  gen_set_label(done_1);

  return ret;
}





/* XOR
 *    Variables: @a, @b, @c
 *    Functions: getCCFlag, getFFlag, setZFlag, setNFlag, setCFlag, CarryADD, setVFlag, OverflowADD
 */

int
arc2_gen_XOR (DisasCtxt *ctx, TCGv a, TCGv b, TCGv c)
{
  int ret = BS_NONE;
  TCGLabel *done_1 = gen_new_label();
  TCGv temp_3 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_3, getCCFlag(), true);
  TCGv temp_4 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_4, temp_3, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_4, true, done_1);;
  tcg_gen_xor_i32(a, b, c);
  TCGLabel *done_2 = gen_new_label();
  TCGv temp_5 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_5, getFFlag(), true);
  TCGv temp_6 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_6, temp_5, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_6, true, done_2);;
  TCGLabel *else_3 = gen_new_label();
  TCGLabel *done_3 = gen_new_label();
  TCGv temp_7 = tcg_temp_new_i32();
  tcg_gen_setcondi_i32(TCG_COND_EQ, temp_7, a, 0);
  TCGv temp_8 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_8, temp_7, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_8, true, else_3);;
  setZFlag(1);
  tcg_gen_br(done_3);
  gen_set_label(else_3);
  setZFlag(0);
  gen_set_label(done_3);
  setNFlag(a);
  TCGv temp_1 = tcg_temp_new_i32();
  tcg_gen_mov_i32(temp_1, CarryADD(a, b, c));
  setCFlag(temp_1);
  TCGv temp_2 = tcg_temp_new_i32();
  tcg_gen_mov_i32(temp_2, OverflowADD(a, b, c));
  setVFlag(temp_2);
  gen_set_label(done_2);
  gen_set_label(done_1);

  return ret;
}





/* MOV
 *    Variables: @a, @b, @c
 *    Functions: getCCFlag, getFFlag, setZFlag, setNFlag, setCFlag, CarryADD, setVFlag, OverflowADD
 */

int
arc2_gen_MOV (DisasCtxt *ctx, TCGv a, TCGv b, TCGv c)
{
  int ret = BS_NONE;
  TCGLabel *done_1 = gen_new_label();
  TCGv temp_3 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_3, getCCFlag(), true);
  TCGv temp_4 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_4, temp_3, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_4, true, done_1);;
  tcg_gen_mov_i32(a, b);
  TCGLabel *done_2 = gen_new_label();
  TCGv temp_5 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_5, getFFlag(), true);
  TCGv temp_6 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_6, temp_5, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_6, true, done_2);;
  TCGLabel *else_3 = gen_new_label();
  TCGLabel *done_3 = gen_new_label();
  TCGv temp_7 = tcg_temp_new_i32();
  tcg_gen_setcondi_i32(TCG_COND_EQ, temp_7, a, 0);
  TCGv temp_8 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_8, temp_7, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_8, true, else_3);;
  setZFlag(1);
  tcg_gen_br(done_3);
  gen_set_label(else_3);
  setZFlag(0);
  gen_set_label(done_3);
  setNFlag(a);
  TCGv temp_1 = tcg_temp_new_i32();
  tcg_gen_mov_i32(temp_1, CarryADD(a, b, c));
  setCFlag(temp_1);
  TCGv temp_2 = tcg_temp_new_i32();
  tcg_gen_mov_i32(temp_2, OverflowADD(a, b, c));
  setVFlag(temp_2);
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
  TCGv temp_3 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_3, getCCFlag(), true);
  TCGv temp_4 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_4, temp_3, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_4, true, done_1);;
  TCGv temp_2 = tcg_temp_new_i32();
  tcg_gen_mov_i32(temp_2, getCFlag());
  TCGv temp_1 = tcg_temp_new_i32();
  tcg_gen_add_i32(temp_1, b, c);
  tcg_gen_add_i32(a, temp_1, temp_2);
  TCGLabel *done_2 = gen_new_label();
  TCGv temp_5 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_5, getFFlag(), true);
  TCGv temp_6 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_6, temp_5, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_6, true, done_2);;
  TCGLabel *else_3 = gen_new_label();
  TCGLabel *done_3 = gen_new_label();
  TCGv temp_7 = tcg_temp_new_i32();
  tcg_gen_setcondi_i32(TCG_COND_EQ, temp_7, a, 0);
  TCGv temp_8 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_8, temp_7, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_8, true, else_3);;
  setZFlag(1);
  tcg_gen_br(done_3);
  gen_set_label(else_3);
  setZFlag(0);
  gen_set_label(done_3);
  setNFlag(a);
  tcg_gen_mov_i32(temp_3, CarryADD(a, b, c));
  setCFlag(temp_3);
  tcg_gen_mov_i32(temp_4, OverflowADD(a, b, c));
  setVFlag(temp_4);
  gen_set_label(done_2);
  gen_set_label(done_1);

  return ret;
}





/* ASL
 *    Variables: @a, @b, @c
 *    Functions: getCCFlag, getFFlag, setZFlag, setNFlag, setCFlag, CarryADD, setVFlag, OverflowADD
 */

int
arc2_gen_ASL (DisasCtxt *ctx, TCGv a, TCGv b, TCGv c)
{
  int ret = BS_NONE;
  TCGLabel *done_1 = gen_new_label();
  TCGv temp_5 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_5, getCCFlag(), true);
  TCGv temp_6 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_6, temp_5, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_6, true, done_1);;
  tcg_gen_shl_i32(a, b, c);
  TCGLabel *done_2 = gen_new_label();
  TCGv temp_7 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_7, getFFlag(), true);
  TCGv temp_8 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_8, temp_7, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_8, true, done_2);;
  TCGLabel *else_3 = gen_new_label();
  TCGLabel *done_3 = gen_new_label();
  TCGv temp_9 = tcg_temp_new_i32();
  tcg_gen_setcondi_i32(TCG_COND_EQ, temp_9, a, 0);
  TCGv temp_10 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_10, temp_9, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_10, true, else_3);;
  setZFlag(1);
  tcg_gen_br(done_3);
  gen_set_label(else_3);
  setZFlag(0);
  gen_set_label(done_3);
  setNFlag(a);
  TCGv temp_1 = tcg_temp_new_i32();
  tcg_gen_mov_i32(temp_1, CarryADD(a, b, c));
  setCFlag(temp_1);
  TCGv temp_2 = tcg_temp_new_i32();
  tcg_gen_mov_i32(temp_2, OverflowADD(a, b, c));
  setVFlag(temp_2);
  gen_set_label(done_2);
  gen_set_label(done_1);

  return ret;
}





/* ASR
 *    Variables: @a, @b, @c
 *    Functions: getCCFlag, getFFlag, setZFlag, setNFlag, setCFlag, CarryADD, setVFlag, OverflowADD
 */

int
arc2_gen_ASR (DisasCtxt *ctx, TCGv a, TCGv b, TCGv c)
{
  int ret = BS_NONE;
  TCGLabel *done_1 = gen_new_label();
  TCGv temp_3 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_3, getCCFlag(), true);
  TCGv temp_4 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_4, temp_3, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_4, true, done_1);;
  tcg_gen_shr_i32(a, b, c);
  TCGLabel *done_2 = gen_new_label();
  TCGv temp_5 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_5, getFFlag(), true);
  TCGv temp_6 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_6, temp_5, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_6, true, done_2);;
  TCGLabel *else_3 = gen_new_label();
  TCGLabel *done_3 = gen_new_label();
  TCGv temp_7 = tcg_temp_new_i32();
  tcg_gen_setcondi_i32(TCG_COND_EQ, temp_7, a, 0);
  TCGv temp_8 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_8, temp_7, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_8, true, else_3);;
  setZFlag(1);
  tcg_gen_br(done_3);
  gen_set_label(else_3);
  setZFlag(0);
  gen_set_label(done_3);
  setNFlag(a);
  TCGv temp_1 = tcg_temp_new_i32();
  tcg_gen_mov_i32(temp_1, CarryADD(a, b, c));
  setCFlag(temp_1);
  TCGv temp_2 = tcg_temp_new_i32();
  tcg_gen_mov_i32(temp_2, OverflowADD(a, b, c));
  setVFlag(temp_2);
  gen_set_label(done_2);
  gen_set_label(done_1);

  return ret;
}





/* ASR16
 *    Variables: @a, @b, @c
 *    Functions: getCCFlag, getFFlag, setZFlag, setNFlag, setCFlag, CarryADD, setVFlag, OverflowADD
 */

int
arc2_gen_ASR16 (DisasCtxt *ctx, TCGv a, TCGv b, TCGv c)
{
  int ret = BS_NONE;
  TCGLabel *done_1 = gen_new_label();
  TCGv temp_3 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_3, getCCFlag(), true);
  TCGv temp_4 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_4, temp_3, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_4, true, done_1);;
  tcg_gen_shri_i32(a, b, 16);
  TCGLabel *done_2 = gen_new_label();
  TCGv temp_5 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_5, getFFlag(), true);
  TCGv temp_6 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_6, temp_5, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_6, true, done_2);;
  TCGLabel *else_3 = gen_new_label();
  TCGLabel *done_3 = gen_new_label();
  TCGv temp_7 = tcg_temp_new_i32();
  tcg_gen_setcondi_i32(TCG_COND_EQ, temp_7, a, 0);
  TCGv temp_8 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_8, temp_7, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_8, true, else_3);;
  setZFlag(1);
  tcg_gen_br(done_3);
  gen_set_label(else_3);
  setZFlag(0);
  gen_set_label(done_3);
  setNFlag(a);
  TCGv temp_1 = tcg_temp_new_i32();
  tcg_gen_mov_i32(temp_1, CarryADD(a, b, c));
  setCFlag(temp_1);
  TCGv temp_2 = tcg_temp_new_i32();
  tcg_gen_mov_i32(temp_2, OverflowADD(a, b, c));
  setVFlag(temp_2);
  gen_set_label(done_2);
  gen_set_label(done_1);

  return ret;
}





/* ASR8
 *    Variables: @a, @b, @c
 *    Functions: getCCFlag, getFFlag, setZFlag, setNFlag, setCFlag, CarryADD, setVFlag, OverflowADD
 */

int
arc2_gen_ASR8 (DisasCtxt *ctx, TCGv a, TCGv b, TCGv c)
{
  int ret = BS_NONE;
  TCGLabel *done_1 = gen_new_label();
  TCGv temp_3 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_3, getCCFlag(), true);
  TCGv temp_4 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_4, temp_3, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_4, true, done_1);;
  tcg_gen_shri_i32(a, b, 16);
  TCGLabel *done_2 = gen_new_label();
  TCGv temp_5 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_5, getFFlag(), true);
  TCGv temp_6 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_6, temp_5, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_6, true, done_2);;
  TCGLabel *else_3 = gen_new_label();
  TCGLabel *done_3 = gen_new_label();
  TCGv temp_7 = tcg_temp_new_i32();
  tcg_gen_setcondi_i32(TCG_COND_EQ, temp_7, a, 0);
  TCGv temp_8 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_8, temp_7, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_8, true, else_3);;
  setZFlag(1);
  tcg_gen_br(done_3);
  gen_set_label(else_3);
  setZFlag(0);
  gen_set_label(done_3);
  setNFlag(a);
  TCGv temp_1 = tcg_temp_new_i32();
  tcg_gen_mov_i32(temp_1, CarryADD(a, b, c));
  setCFlag(temp_1);
  TCGv temp_2 = tcg_temp_new_i32();
  tcg_gen_mov_i32(temp_2, OverflowADD(a, b, c));
  setVFlag(temp_2);
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
  TCGv temp_3 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_3, getCCFlag(), true);
  TCGv temp_4 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_4, temp_3, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_4, true, done_1);;
  tcg_gen_sub_i32(a, b, c);
  TCGLabel *done_2 = gen_new_label();
  TCGv temp_5 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_5, getFFlag(), true);
  TCGv temp_6 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_6, temp_5, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_6, true, done_2);;
  TCGLabel *else_3 = gen_new_label();
  TCGLabel *done_3 = gen_new_label();
  TCGv temp_7 = tcg_temp_new_i32();
  tcg_gen_setcondi_i32(TCG_COND_EQ, temp_7, a, 0);
  TCGv temp_8 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_8, temp_7, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_8, true, else_3);;
  setZFlag(1);
  tcg_gen_br(done_3);
  gen_set_label(else_3);
  setZFlag(0);
  gen_set_label(done_3);
  setNFlag(a);
  TCGv temp_1 = tcg_temp_new_i32();
  tcg_gen_mov_i32(temp_1, CarrySUB(a, b, c));
  setCFlag(temp_1);
  TCGv temp_2 = tcg_temp_new_i32();
  tcg_gen_mov_i32(temp_2, OverflowSUB(a, b, c));
  setVFlag(temp_2);
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
  TCGv temp_3 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_3, getCCFlag(), true);
  TCGv temp_4 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_4, temp_3, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_4, true, done_1);;
  TCGv temp_1 = tcg_temp_new_i32();
  tcg_gen_shli_i32(temp_1, c, 1);
  tcg_gen_sub_i32(a, b, temp_1);
  TCGLabel *done_2 = gen_new_label();
  TCGv temp_5 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_5, getFFlag(), true);
  TCGv temp_6 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_6, temp_5, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_6, true, done_2);;
  TCGLabel *else_3 = gen_new_label();
  TCGLabel *done_3 = gen_new_label();
  TCGv temp_7 = tcg_temp_new_i32();
  tcg_gen_setcondi_i32(TCG_COND_EQ, temp_7, a, 0);
  TCGv temp_8 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_8, temp_7, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_8, true, else_3);;
  setZFlag(1);
  tcg_gen_br(done_3);
  gen_set_label(else_3);
  setZFlag(0);
  gen_set_label(done_3);
  setNFlag(a);
  TCGv temp_2 = tcg_temp_new_i32();
  tcg_gen_mov_i32(temp_2, CarrySUB(a, b, c));
  setCFlag(temp_2);
  tcg_gen_mov_i32(temp_3, OverflowSUB(a, b, c));
  setVFlag(temp_3);
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
  TCGv temp_4 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_4, getCCFlag(), true);
  TCGv temp_5 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_5, temp_4, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_5, true, done_1);;
  TCGv temp_1 = tcg_temp_new_i32();
  tcg_gen_shli_i32(temp_1, c, 2);
  tcg_gen_sub_i32(a, b, temp_1);
  TCGLabel *done_2 = gen_new_label();
  TCGv temp_6 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_6, getFFlag(), true);
  TCGv temp_7 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_7, temp_6, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_7, true, done_2);;
  TCGLabel *else_3 = gen_new_label();
  TCGLabel *done_3 = gen_new_label();
  TCGv temp_8 = tcg_temp_new_i32();
  tcg_gen_setcondi_i32(TCG_COND_EQ, temp_8, a, 0);
  TCGv temp_9 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_9, temp_8, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_9, true, else_3);;
  setZFlag(1);
  tcg_gen_br(done_3);
  gen_set_label(else_3);
  setZFlag(0);
  gen_set_label(done_3);
  setNFlag(a);
  TCGv temp_2 = tcg_temp_new_i32();
  tcg_gen_mov_i32(temp_2, CarrySUB(a, b, c));
  setCFlag(temp_2);
  TCGv temp_3 = tcg_temp_new_i32();
  tcg_gen_mov_i32(temp_3, OverflowSUB(a, b, c));
  setVFlag(temp_3);
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
  TCGv temp_4 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_4, getCCFlag(), true);
  TCGv temp_5 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_5, temp_4, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_5, true, done_1);;
  TCGv temp_1 = tcg_temp_new_i32();
  tcg_gen_shli_i32(temp_1, c, 3);
  tcg_gen_sub_i32(a, b, temp_1);
  TCGLabel *done_2 = gen_new_label();
  TCGv temp_6 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_6, getFFlag(), true);
  TCGv temp_7 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_7, temp_6, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_7, true, done_2);;
  TCGLabel *else_3 = gen_new_label();
  TCGLabel *done_3 = gen_new_label();
  TCGv temp_8 = tcg_temp_new_i32();
  tcg_gen_setcondi_i32(TCG_COND_EQ, temp_8, a, 0);
  TCGv temp_9 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_9, temp_8, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_9, true, else_3);;
  setZFlag(1);
  tcg_gen_br(done_3);
  gen_set_label(else_3);
  setZFlag(0);
  gen_set_label(done_3);
  setNFlag(a);
  TCGv temp_2 = tcg_temp_new_i32();
  tcg_gen_mov_i32(temp_2, CarrySUB(a, b, c));
  setCFlag(temp_2);
  TCGv temp_3 = tcg_temp_new_i32();
  tcg_gen_mov_i32(temp_3, OverflowSUB(a, b, c));
  setVFlag(temp_3);
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
  TCGv temp_4 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_4, getCCFlag(), true);
  TCGv temp_5 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_5, temp_4, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_5, true, done_1);;
  TCGv temp_1 = tcg_temp_new_i32();
  tcg_gen_mul_i32(temp_1, b, c);
  tcg_gen_andi_i32(a, temp_1, 4294967295);
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
  TCGv temp_2 = tcg_temp_new_i32();
  tcg_gen_setcondi_i32(TCG_COND_EQ, temp_2, Carry(src), 1);
  TCGv temp_3 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_3, temp_2, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_3, true, else_1);;
  tcg_gen_mov_i32(dest, alu);
  tcg_gen_br(done_1);
  gen_set_label(else_1);
  tcg_gen_mov_i32(dest, src);
  gen_set_label(done_1);
  TCGLabel *done_2 = gen_new_label();
  TCGv temp_4 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_4, getFFlag(), true);
  TCGv temp_5 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_5, temp_4, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_5, true, done_2);;
  TCGLabel *else_3 = gen_new_label();
  TCGLabel *done_3 = gen_new_label();
  TCGv temp_6 = tcg_temp_new_i32();
  tcg_gen_setcondi_i32(TCG_COND_EQ, temp_6, dest, 0);
  TCGv temp_7 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_7, temp_6, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_7, true, else_3);;
  setZFlag(1);
  tcg_gen_br(done_3);
  gen_set_label(else_3);
  setZFlag(0);
  gen_set_label(done_3);
  setNFlag(dest);
  TCGv temp_1 = tcg_temp_new_i32();
  tcg_gen_mov_i32(temp_1, Zero());
  setCFlag(temp_1);
  tcg_gen_mov_i32(temp_2, getNFlag());
  setVFlag(temp_2);
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
  TCGv temp_3 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_3, getCCFlag(), true);
  TCGv temp_4 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_4, temp_3, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_4, true, done_1);;
  if ((shouldExecuteDelaySlot () == true))
    {
    executeDelaySlot();
;
    }
  TCGv temp_2 = tcg_temp_new_i32();
  tcg_gen_mov_i32(temp_2, getPCL());
  TCGv temp_1 = tcg_temp_new_i32();
  tcg_gen_add_i32(temp_1, temp_2, rd);
  setPC(temp_1);
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
  TCGv temp_3 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_3, getCCFlag(), true);
  TCGv temp_4 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_4, temp_3, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_4, true, done_1);;
  killDelaySlot();
  TCGv temp_2 = tcg_temp_new_i32();
  tcg_gen_mov_i32(temp_2, getPC());
  TCGv temp_1 = tcg_temp_new_i32();
  tcg_gen_add_i32(temp_1, temp_2, rd);
  setPC(temp_1);
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
  TCGv temp_3 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_3, getCCFlag(), true);
  TCGv temp_4 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_4, temp_3, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_4, true, done_1);;
  if ((shouldExecuteDelaySlot () == 1))
    {
    TCGv temp_1 = tcg_temp_new_i32();
  tcg_gen_mov_i32(temp_1, nextInsnAddressAfterDelaySlot());
  setBLINK(temp_1);
  executeDelaySlot();
;
    }
  tcg_gen_mov_i32(temp_4, getPCL());
  tcg_gen_add_i32(temp_3, temp_4, rd);
  setPC(temp_3);
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
  TCGv temp_5 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_5, getCCFlag(), true);
  TCGv temp_6 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_6, temp_5, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_6, true, done_1);;
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
    tcg_gen_mov_i32(temp_1, nextInsnAddressAfterDelaySlot());
  setBLINK(temp_1);
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
  TCGv temp_3 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_3, getCCFlag(), true);
  TCGv temp_4 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_4, temp_3, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_4, true, done_1);;
  TCGv alu = tcg_temp_new_i32();
  tcg_gen_sub_i32(alu, src1, src2);
  TCGLabel *else_2 = gen_new_label();
  TCGLabel *done_2 = gen_new_label();
  TCGv temp_5 = tcg_temp_new_i32();
  tcg_gen_setcondi_i32(TCG_COND_EQ, temp_5, alu, 0);
  TCGv temp_6 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_6, temp_5, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_6, true, else_2);;
  setZFlag(1);
  tcg_gen_br(done_2);
  gen_set_label(else_2);
  setZFlag(0);
  gen_set_label(done_2);
  setNFlag(alu);
  TCGv temp_1 = tcg_temp_new_i32();
  tcg_gen_mov_i32(temp_1, CarrySUB(alu, src1, src2));
  setCFlag(temp_1);
  TCGv temp_2 = tcg_temp_new_i32();
  tcg_gen_mov_i32(temp_2, OverflowSUB(alu, src1, src2));
  setVFlag(temp_2);
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
  TCGLabel *done_1 = gen_new_label();
  TCGv temp_3 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_3, b, c);
  TCGv temp_4 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_4, temp_3, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_4, true, done_1);;
  TCGv temp_2 = tcg_temp_new_i32();
  tcg_gen_mov_i32(temp_2, getPCL());
  TCGv temp_1 = tcg_temp_new_i32();
  tcg_gen_add_i32(temp_1, temp_2, offset);
  setPC(temp_1);
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
  TCGLabel *done_1 = gen_new_label();
  TCGv temp_3 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_NE, temp_3, b, c);
  TCGv temp_4 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_4, temp_3, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_4, true, done_1);;
  TCGv temp_2 = tcg_temp_new_i32();
  tcg_gen_mov_i32(temp_2, getPCL());
  TCGv temp_1 = tcg_temp_new_i32();
  tcg_gen_add_i32(temp_1, temp_2, offset);
  setPC(temp_1);
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
  TCGLabel *done_1 = gen_new_label();
  TCGv temp_3 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_LT, temp_3, b, c);
  TCGv temp_4 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_4, temp_3, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_4, true, done_1);;
  TCGv temp_2 = tcg_temp_new_i32();
  tcg_gen_mov_i32(temp_2, getPCL());
  TCGv temp_1 = tcg_temp_new_i32();
  tcg_gen_add_i32(temp_1, temp_2, offset);
  setPC(temp_1);
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
  TCGLabel *done_1 = gen_new_label();
  TCGv temp_3 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_GE, temp_3, b, c);
  TCGv temp_4 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_4, temp_3, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_4, true, done_1);;
  TCGv temp_2 = tcg_temp_new_i32();
  tcg_gen_mov_i32(temp_2, getPCL());
  TCGv temp_1 = tcg_temp_new_i32();
  tcg_gen_add_i32(temp_1, temp_2, offset);
  setPC(temp_1);
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
  TCGLabel *done_1 = gen_new_label();
  TCGv temp_3 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_3, unsignedLT(b, c), 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_3, true, done_1);;
  TCGv temp_2 = tcg_temp_new_i32();
  tcg_gen_mov_i32(temp_2, getPCL());
  TCGv temp_1 = tcg_temp_new_i32();
  tcg_gen_add_i32(temp_1, temp_2, offset);
  setPC(temp_1);
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
  TCGLabel *done_1 = gen_new_label();
  TCGv temp_3 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_3, unsignedGE(b, c), 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_3, true, done_1);;
  TCGv temp_2 = tcg_temp_new_i32();
  tcg_gen_mov_i32(temp_2, getPCL());
  TCGv temp_1 = tcg_temp_new_i32();
  tcg_gen_add_i32(temp_1, temp_2, offset);
  setPC(temp_1);
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
  if (((AA == 1) || (AA == 2)))
    {
    tcg_gen_add_i32(src1, src1, src2);
;
    }
  setDebugLD(1);
  tcg_gen_mov_i32(dest, getMemory(address, ZZ));
  if ((getFlagX () == 1))
    {
    tcg_gen_mov_i32(dest, SignExtend(dest, ZZ));
;
    }
  TCGLabel *done_1 = gen_new_label();
  TCGv temp_3 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_3, NoFurtherLoadsPending(), 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_3, true, done_1);;
  setDebugLD(0);
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
