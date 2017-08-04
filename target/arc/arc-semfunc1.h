


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
  TCGv temp_7 = tcg_temp_new_i32();
  tcg_gen_mov_i32(temp_7, CarryADD(a, b, c));
  setCFlag(temp_7);
  TCGv temp_8 = tcg_temp_new_i32();
  tcg_gen_mov_i32(temp_8, OverflowADD(a, b, c));
  setVFlag(temp_8);
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
  TCGv temp_9 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_9, getCCFlag(), true);
  TCGv temp_10 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_10, temp_9, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_10, true, done_1);;
  TCGv temp_15 = tcg_temp_new_i32();
  tcg_gen_shli_i32(temp_15, c, 1);
  tcg_gen_add_i32(a, b, temp_15);
  TCGLabel *done_2 = gen_new_label();
  TCGv temp_11 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_11, getFFlag(), true);
  TCGv temp_12 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_12, temp_11, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_12, true, done_2);;
  TCGLabel *else_3 = gen_new_label();
  TCGLabel *done_3 = gen_new_label();
  TCGv temp_13 = tcg_temp_new_i32();
  tcg_gen_setcondi_i32(TCG_COND_EQ, temp_13, a, 0);
  TCGv temp_14 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_14, temp_13, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_14, true, else_3);;
  setZFlag(1);
  tcg_gen_br(done_3);
  gen_set_label(else_3);
  setZFlag(0);
  gen_set_label(done_3);
  setNFlag(a);
  TCGv temp_16 = tcg_temp_new_i32();
  tcg_gen_mov_i32(temp_16, CarryADD(a, b, c));
  setCFlag(temp_16);
  TCGv temp_17 = tcg_temp_new_i32();
  tcg_gen_mov_i32(temp_17, OverflowADD(a, b, c));
  setVFlag(temp_17);
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
  TCGv temp_18 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_18, getCCFlag(), true);
  TCGv temp_19 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_19, temp_18, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_19, true, done_1);;
  TCGv temp_24 = tcg_temp_new_i32();
  tcg_gen_shli_i32(temp_24, c, 2);
  tcg_gen_add_i32(a, b, temp_24);
  TCGLabel *done_2 = gen_new_label();
  TCGv temp_20 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_20, getFFlag(), true);
  TCGv temp_21 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_21, temp_20, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_21, true, done_2);;
  TCGLabel *else_3 = gen_new_label();
  TCGLabel *done_3 = gen_new_label();
  TCGv temp_22 = tcg_temp_new_i32();
  tcg_gen_setcondi_i32(TCG_COND_EQ, temp_22, a, 0);
  TCGv temp_23 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_23, temp_22, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_23, true, else_3);;
  setZFlag(1);
  tcg_gen_br(done_3);
  gen_set_label(else_3);
  setZFlag(0);
  gen_set_label(done_3);
  setNFlag(a);
  TCGv temp_25 = tcg_temp_new_i32();
  tcg_gen_mov_i32(temp_25, CarryADD(a, b, c));
  setCFlag(temp_25);
  TCGv temp_26 = tcg_temp_new_i32();
  tcg_gen_mov_i32(temp_26, OverflowADD(a, b, c));
  setVFlag(temp_26);
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
  TCGv temp_27 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_27, getCCFlag(), true);
  TCGv temp_28 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_28, temp_27, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_28, true, done_1);;
  TCGv temp_33 = tcg_temp_new_i32();
  tcg_gen_shli_i32(temp_33, c, 3);
  tcg_gen_add_i32(a, b, temp_33);
  TCGLabel *done_2 = gen_new_label();
  TCGv temp_29 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_29, getFFlag(), true);
  TCGv temp_30 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_30, temp_29, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_30, true, done_2);;
  TCGLabel *else_3 = gen_new_label();
  TCGLabel *done_3 = gen_new_label();
  TCGv temp_31 = tcg_temp_new_i32();
  tcg_gen_setcondi_i32(TCG_COND_EQ, temp_31, a, 0);
  TCGv temp_32 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_32, temp_31, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_32, true, else_3);;
  setZFlag(1);
  tcg_gen_br(done_3);
  gen_set_label(else_3);
  setZFlag(0);
  gen_set_label(done_3);
  setNFlag(a);
  TCGv temp_34 = tcg_temp_new_i32();
  tcg_gen_mov_i32(temp_34, CarryADD(a, b, c));
  setCFlag(temp_34);
  TCGv temp_35 = tcg_temp_new_i32();
  tcg_gen_mov_i32(temp_35, OverflowADD(a, b, c));
  setVFlag(temp_35);
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
  TCGv temp_36 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_36, getCCFlag(), true);
  TCGv temp_37 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_37, temp_36, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_37, true, done_1);;
  tcg_gen_mul_i32(a, b, c);
  TCGLabel *done_2 = gen_new_label();
  TCGv temp_38 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_38, getFFlag(), true);
  TCGv temp_39 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_39, temp_38, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_39, true, done_2);;
  TCGLabel *else_3 = gen_new_label();
  TCGLabel *done_3 = gen_new_label();
  TCGv temp_40 = tcg_temp_new_i32();
  tcg_gen_setcondi_i32(TCG_COND_EQ, temp_40, a, 0);
  TCGv temp_41 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_41, temp_40, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_41, true, else_3);;
  setZFlag(1);
  tcg_gen_br(done_3);
  gen_set_label(else_3);
  setZFlag(0);
  gen_set_label(done_3);
  setNFlag(a);
  TCGv temp_42 = tcg_temp_new_i32();
  tcg_gen_mov_i32(temp_42, CarryADD(a, b, c));
  setCFlag(temp_42);
  TCGv temp_43 = tcg_temp_new_i32();
  tcg_gen_mov_i32(temp_43, OverflowADD(a, b, c));
  setVFlag(temp_43);
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
  TCGv temp_44 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_44, getCCFlag(), true);
  TCGv temp_45 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_45, temp_44, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_45, true, done_1);;
  tcg_gen_div_i32(a, b, c);
  TCGLabel *done_2 = gen_new_label();
  TCGv temp_46 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_46, getFFlag(), true);
  TCGv temp_47 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_47, temp_46, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_47, true, done_2);;
  TCGLabel *else_3 = gen_new_label();
  TCGLabel *done_3 = gen_new_label();
  TCGv temp_48 = tcg_temp_new_i32();
  tcg_gen_setcondi_i32(TCG_COND_EQ, temp_48, a, 0);
  TCGv temp_49 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_49, temp_48, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_49, true, else_3);;
  setZFlag(1);
  tcg_gen_br(done_3);
  gen_set_label(else_3);
  setZFlag(0);
  gen_set_label(done_3);
  setNFlag(a);
  TCGv temp_50 = tcg_temp_new_i32();
  tcg_gen_mov_i32(temp_50, CarryADD(a, b, c));
  setCFlag(temp_50);
  TCGv temp_51 = tcg_temp_new_i32();
  tcg_gen_mov_i32(temp_51, OverflowADD(a, b, c));
  setVFlag(temp_51);
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
  TCGv temp_52 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_52, getCCFlag(), true);
  TCGv temp_53 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_53, temp_52, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_53, true, done_1);;
  tcg_gen_and_i32(a, b, c);
  TCGLabel *done_2 = gen_new_label();
  TCGv temp_54 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_54, getFFlag(), true);
  TCGv temp_55 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_55, temp_54, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_55, true, done_2);;
  TCGLabel *else_3 = gen_new_label();
  TCGLabel *done_3 = gen_new_label();
  TCGv temp_56 = tcg_temp_new_i32();
  tcg_gen_setcondi_i32(TCG_COND_EQ, temp_56, a, 0);
  TCGv temp_57 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_57, temp_56, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_57, true, else_3);;
  setZFlag(1);
  tcg_gen_br(done_3);
  gen_set_label(else_3);
  setZFlag(0);
  gen_set_label(done_3);
  setNFlag(a);
  TCGv temp_58 = tcg_temp_new_i32();
  tcg_gen_mov_i32(temp_58, CarryADD(a, b, c));
  setCFlag(temp_58);
  TCGv temp_59 = tcg_temp_new_i32();
  tcg_gen_mov_i32(temp_59, OverflowADD(a, b, c));
  setVFlag(temp_59);
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
  TCGv temp_60 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_60, getCCFlag(), true);
  TCGv temp_61 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_61, temp_60, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_61, true, done_1);;
  tcg_gen_or_i32(a, b, c);
  TCGLabel *done_2 = gen_new_label();
  TCGv temp_62 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_62, getFFlag(), true);
  TCGv temp_63 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_63, temp_62, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_63, true, done_2);;
  TCGLabel *else_3 = gen_new_label();
  TCGLabel *done_3 = gen_new_label();
  TCGv temp_64 = tcg_temp_new_i32();
  tcg_gen_setcondi_i32(TCG_COND_EQ, temp_64, a, 0);
  TCGv temp_65 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_65, temp_64, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_65, true, else_3);;
  setZFlag(1);
  tcg_gen_br(done_3);
  gen_set_label(else_3);
  setZFlag(0);
  gen_set_label(done_3);
  setNFlag(a);
  TCGv temp_66 = tcg_temp_new_i32();
  tcg_gen_mov_i32(temp_66, CarryADD(a, b, c));
  setCFlag(temp_66);
  TCGv temp_67 = tcg_temp_new_i32();
  tcg_gen_mov_i32(temp_67, OverflowADD(a, b, c));
  setVFlag(temp_67);
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
  TCGv temp_68 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_68, getCCFlag(), true);
  TCGv temp_69 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_69, temp_68, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_69, true, done_1);;
  tcg_gen_xor_i32(a, b, c);
  TCGLabel *done_2 = gen_new_label();
  TCGv temp_70 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_70, getFFlag(), true);
  TCGv temp_71 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_71, temp_70, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_71, true, done_2);;
  TCGLabel *else_3 = gen_new_label();
  TCGLabel *done_3 = gen_new_label();
  TCGv temp_72 = tcg_temp_new_i32();
  tcg_gen_setcondi_i32(TCG_COND_EQ, temp_72, a, 0);
  TCGv temp_73 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_73, temp_72, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_73, true, else_3);;
  setZFlag(1);
  tcg_gen_br(done_3);
  gen_set_label(else_3);
  setZFlag(0);
  gen_set_label(done_3);
  setNFlag(a);
  TCGv temp_74 = tcg_temp_new_i32();
  tcg_gen_mov_i32(temp_74, CarryADD(a, b, c));
  setCFlag(temp_74);
  TCGv temp_75 = tcg_temp_new_i32();
  tcg_gen_mov_i32(temp_75, OverflowADD(a, b, c));
  setVFlag(temp_75);
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
  TCGv temp_76 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_76, getCCFlag(), true);
  TCGv temp_77 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_77, temp_76, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_77, true, done_1);;
  tcg_gen_mov_i32(a, b);
  TCGLabel *done_2 = gen_new_label();
  TCGv temp_78 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_78, getFFlag(), true);
  TCGv temp_79 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_79, temp_78, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_79, true, done_2);;
  TCGLabel *else_3 = gen_new_label();
  TCGLabel *done_3 = gen_new_label();
  TCGv temp_80 = tcg_temp_new_i32();
  tcg_gen_setcondi_i32(TCG_COND_EQ, temp_80, a, 0);
  TCGv temp_81 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_81, temp_80, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_81, true, else_3);;
  setZFlag(1);
  tcg_gen_br(done_3);
  gen_set_label(else_3);
  setZFlag(0);
  gen_set_label(done_3);
  setNFlag(a);
  TCGv temp_82 = tcg_temp_new_i32();
  tcg_gen_mov_i32(temp_82, CarryADD(a, b, c));
  setCFlag(temp_82);
  TCGv temp_83 = tcg_temp_new_i32();
  tcg_gen_mov_i32(temp_83, OverflowADD(a, b, c));
  setVFlag(temp_83);
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
  TCGv temp_84 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_84, getCCFlag(), true);
  TCGv temp_85 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_85, temp_84, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_85, true, done_1);;
  TCGv temp_91 = tcg_temp_new_i32();
  tcg_gen_mov_i32(temp_91, getCFlag());
  TCGv temp_90 = tcg_temp_new_i32();
  tcg_gen_add_i32(temp_90, b, c);
  tcg_gen_add_i32(a, temp_90, temp_91);
  TCGLabel *done_2 = gen_new_label();
  TCGv temp_86 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_86, getFFlag(), true);
  TCGv temp_87 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_87, temp_86, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_87, true, done_2);;
  TCGLabel *else_3 = gen_new_label();
  TCGLabel *done_3 = gen_new_label();
  TCGv temp_88 = tcg_temp_new_i32();
  tcg_gen_setcondi_i32(TCG_COND_EQ, temp_88, a, 0);
  TCGv temp_89 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_89, temp_88, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_89, true, else_3);;
  setZFlag(1);
  tcg_gen_br(done_3);
  gen_set_label(else_3);
  setZFlag(0);
  gen_set_label(done_3);
  setNFlag(a);
  TCGv temp_92 = tcg_temp_new_i32();
  tcg_gen_mov_i32(temp_92, CarryADD(a, b, c));
  setCFlag(temp_92);
  TCGv temp_93 = tcg_temp_new_i32();
  tcg_gen_mov_i32(temp_93, OverflowADD(a, b, c));
  setVFlag(temp_93);
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
  TCGv temp_94 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_94, getCCFlag(), true);
  TCGv temp_95 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_95, temp_94, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_95, true, done_1);;
  tcg_gen_shl_i32(a, b, c);
  TCGLabel *done_2 = gen_new_label();
  TCGv temp_96 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_96, getFFlag(), true);
  TCGv temp_97 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_97, temp_96, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_97, true, done_2);;
  TCGLabel *else_3 = gen_new_label();
  TCGLabel *done_3 = gen_new_label();
  TCGv temp_98 = tcg_temp_new_i32();
  tcg_gen_setcondi_i32(TCG_COND_EQ, temp_98, a, 0);
  TCGv temp_99 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_99, temp_98, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_99, true, else_3);;
  setZFlag(1);
  tcg_gen_br(done_3);
  gen_set_label(else_3);
  setZFlag(0);
  gen_set_label(done_3);
  setNFlag(a);
  TCGv temp_100 = tcg_temp_new_i32();
  tcg_gen_mov_i32(temp_100, CarryADD(a, b, c));
  setCFlag(temp_100);
  TCGv temp_101 = tcg_temp_new_i32();
  tcg_gen_mov_i32(temp_101, OverflowADD(a, b, c));
  setVFlag(temp_101);
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
  TCGv temp_102 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_102, getCCFlag(), true);
  TCGv temp_103 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_103, temp_102, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_103, true, done_1);;
  tcg_gen_shr_i32(a, b, c);
  TCGLabel *done_2 = gen_new_label();
  TCGv temp_104 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_104, getFFlag(), true);
  TCGv temp_105 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_105, temp_104, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_105, true, done_2);;
  TCGLabel *else_3 = gen_new_label();
  TCGLabel *done_3 = gen_new_label();
  TCGv temp_106 = tcg_temp_new_i32();
  tcg_gen_setcondi_i32(TCG_COND_EQ, temp_106, a, 0);
  TCGv temp_107 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_107, temp_106, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_107, true, else_3);;
  setZFlag(1);
  tcg_gen_br(done_3);
  gen_set_label(else_3);
  setZFlag(0);
  gen_set_label(done_3);
  setNFlag(a);
  TCGv temp_108 = tcg_temp_new_i32();
  tcg_gen_mov_i32(temp_108, CarryADD(a, b, c));
  setCFlag(temp_108);
  TCGv temp_109 = tcg_temp_new_i32();
  tcg_gen_mov_i32(temp_109, OverflowADD(a, b, c));
  setVFlag(temp_109);
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
  TCGv temp_110 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_110, getCCFlag(), true);
  TCGv temp_111 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_111, temp_110, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_111, true, done_1);;
  tcg_gen_shri_i32(a, b, 16);
  TCGLabel *done_2 = gen_new_label();
  TCGv temp_112 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_112, getFFlag(), true);
  TCGv temp_113 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_113, temp_112, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_113, true, done_2);;
  TCGLabel *else_3 = gen_new_label();
  TCGLabel *done_3 = gen_new_label();
  TCGv temp_114 = tcg_temp_new_i32();
  tcg_gen_setcondi_i32(TCG_COND_EQ, temp_114, a, 0);
  TCGv temp_115 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_115, temp_114, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_115, true, else_3);;
  setZFlag(1);
  tcg_gen_br(done_3);
  gen_set_label(else_3);
  setZFlag(0);
  gen_set_label(done_3);
  setNFlag(a);
  TCGv temp_116 = tcg_temp_new_i32();
  tcg_gen_mov_i32(temp_116, CarryADD(a, b, c));
  setCFlag(temp_116);
  TCGv temp_117 = tcg_temp_new_i32();
  tcg_gen_mov_i32(temp_117, OverflowADD(a, b, c));
  setVFlag(temp_117);
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
  TCGv temp_118 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_118, getCCFlag(), true);
  TCGv temp_119 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_119, temp_118, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_119, true, done_1);;
  tcg_gen_shri_i32(a, b, 16);
  TCGLabel *done_2 = gen_new_label();
  TCGv temp_120 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_120, getFFlag(), true);
  TCGv temp_121 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_121, temp_120, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_121, true, done_2);;
  TCGLabel *else_3 = gen_new_label();
  TCGLabel *done_3 = gen_new_label();
  TCGv temp_122 = tcg_temp_new_i32();
  tcg_gen_setcondi_i32(TCG_COND_EQ, temp_122, a, 0);
  TCGv temp_123 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_123, temp_122, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_123, true, else_3);;
  setZFlag(1);
  tcg_gen_br(done_3);
  gen_set_label(else_3);
  setZFlag(0);
  gen_set_label(done_3);
  setNFlag(a);
  TCGv temp_124 = tcg_temp_new_i32();
  tcg_gen_mov_i32(temp_124, CarryADD(a, b, c));
  setCFlag(temp_124);
  TCGv temp_125 = tcg_temp_new_i32();
  tcg_gen_mov_i32(temp_125, OverflowADD(a, b, c));
  setVFlag(temp_125);
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
  TCGv temp_126 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_126, getCCFlag(), true);
  TCGv temp_127 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_127, temp_126, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_127, true, done_1);;
  tcg_gen_sub_i32(a, b, c);
  TCGLabel *done_2 = gen_new_label();
  TCGv temp_128 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_128, getFFlag(), true);
  TCGv temp_129 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_129, temp_128, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_129, true, done_2);;
  TCGLabel *else_3 = gen_new_label();
  TCGLabel *done_3 = gen_new_label();
  TCGv temp_130 = tcg_temp_new_i32();
  tcg_gen_setcondi_i32(TCG_COND_EQ, temp_130, a, 0);
  TCGv temp_131 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_131, temp_130, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_131, true, else_3);;
  setZFlag(1);
  tcg_gen_br(done_3);
  gen_set_label(else_3);
  setZFlag(0);
  gen_set_label(done_3);
  setNFlag(a);
  TCGv temp_132 = tcg_temp_new_i32();
  tcg_gen_mov_i32(temp_132, CarrySUB(a, b, c));
  setCFlag(temp_132);
  TCGv temp_133 = tcg_temp_new_i32();
  tcg_gen_mov_i32(temp_133, OverflowSUB(a, b, c));
  setVFlag(temp_133);
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
  TCGv temp_134 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_134, getCCFlag(), true);
  TCGv temp_135 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_135, temp_134, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_135, true, done_1);;
  TCGv temp_136 = tcg_temp_new_i32();
  tcg_gen_mul_i32(temp_136, b, c);
  tcg_gen_andi_i32(a, temp_136, 4294967295);
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
  TCGv temp_137 = tcg_temp_new_i32();
  tcg_gen_setcondi_i32(TCG_COND_EQ, temp_137, Carry(src), 1);
  TCGv temp_138 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_138, temp_137, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_138, true, else_1);;
  tcg_gen_mov_i32(dest, alu);
  tcg_gen_br(done_1);
  gen_set_label(else_1);
  tcg_gen_mov_i32(dest, src);
  gen_set_label(done_1);
  TCGLabel *done_2 = gen_new_label();
  TCGv temp_139 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_139, getFFlag(), true);
  TCGv temp_140 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_140, temp_139, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_140, true, done_2);;
  TCGLabel *else_3 = gen_new_label();
  TCGLabel *done_3 = gen_new_label();
  TCGv temp_141 = tcg_temp_new_i32();
  tcg_gen_setcondi_i32(TCG_COND_EQ, temp_141, dest, 0);
  TCGv temp_142 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_142, temp_141, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_142, true, else_3);;
  setZFlag(1);
  tcg_gen_br(done_3);
  gen_set_label(else_3);
  setZFlag(0);
  gen_set_label(done_3);
  setNFlag(dest);
  TCGv temp_143 = tcg_temp_new_i32();
  tcg_gen_mov_i32(temp_143, Zero());
  setCFlag(temp_143);
  TCGv temp_144 = tcg_temp_new_i32();
  tcg_gen_mov_i32(temp_144, getNFlag());
  setVFlag(temp_144);
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
  TCGv temp_145 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_145, getCCFlag(), true);
  TCGv temp_146 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_146, temp_145, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_146, true, done_1);;
  if ((shouldExecuteDelaySlot () == true))
    {
    executeDelaySlot();
;
    }
  TCGv temp_148 = tcg_temp_new_i32();
  tcg_gen_mov_i32(temp_148, getPCL());
  TCGv temp_147 = tcg_temp_new_i32();
  tcg_gen_add_i32(temp_147, temp_148, rd);
  setPC(temp_147);
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
  TCGv temp_149 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_149, getCCFlag(), true);
  TCGv temp_150 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_150, temp_149, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_150, true, done_1);;
  killDelaySlot();
  TCGv temp_152 = tcg_temp_new_i32();
  tcg_gen_mov_i32(temp_152, getPC());
  TCGv temp_151 = tcg_temp_new_i32();
  tcg_gen_add_i32(temp_151, temp_152, rd);
  setPC(temp_151);
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
  TCGv temp_153 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_153, getCCFlag(), true);
  TCGv temp_154 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_154, temp_153, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_154, true, done_1);;
  if ((shouldExecuteDelaySlot () == 1))
    {
    executeDelaySlot();
;
    }
  setPC(src);
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
    TCGv temp_156 = tcg_temp_new_i32();
  tcg_gen_shli_i32(temp_156, src2, 2);
  tcg_gen_add_i32(address, src1, temp_156);
;
    }
  if (((AA == 3) && (ZZ == 2)))
    {
    TCGv temp_157 = tcg_temp_new_i32();
  tcg_gen_shli_i32(temp_157, src2, 1);
  tcg_gen_add_i32(address, src1, temp_157);
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
  TCGv temp_155 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_155, NoFurtherLoadsPending(), 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_155, true, done_1);;
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
    TCGv temp_158 = tcg_temp_new_i32();
  tcg_gen_shli_i32(temp_158, src2, 2);
  tcg_gen_add_i32(address, src1, temp_158);
;
    }
  if (((AA == 3) && (ZZ == 2)))
    {
    TCGv temp_159 = tcg_temp_new_i32();
  tcg_gen_shli_i32(temp_159, src2, 1);
  tcg_gen_add_i32(address, src1, temp_159);
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
