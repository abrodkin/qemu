


/* ADD
 *    Variables: @a, @b, @c
 *    Functions: getCCFlag, getFFlag, setZFlag, setNFlag
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
  gen_set_label(done_2);
  gen_set_label(done_1);

  return ret;
}





/* ADD1
 *    Variables: @a, @b, @c
 *    Functions: getCCFlag, getFFlag, setZFlag, setNFlag
 */

int
arc2_gen_ADD1 (DisasCtxt *ctx, TCGv a, TCGv b, TCGv c)
{
  int ret = BS_NONE;
  TCGLabel *done_1 = gen_new_label();
  TCGv temp_7 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_7, getCCFlag(), true);
  TCGv temp_8 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_8, temp_7, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_8, true, done_1);;
  TCGv temp_13 = tcg_temp_new_i32();
  tcg_gen_shli_i32(temp_13, c, 1);
  tcg_gen_add_i32(a, b, temp_13);
  TCGLabel *done_2 = gen_new_label();
  TCGv temp_9 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_9, getFFlag(), true);
  TCGv temp_10 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_10, temp_9, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_10, true, done_2);;
  TCGLabel *else_3 = gen_new_label();
  TCGLabel *done_3 = gen_new_label();
  TCGv temp_11 = tcg_temp_new_i32();
  tcg_gen_setcondi_i32(TCG_COND_EQ, temp_11, a, 0);
  TCGv temp_12 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_12, temp_11, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_12, true, else_3);;
  setZFlag(1);
  tcg_gen_br(done_3);
  gen_set_label(else_3);
  setZFlag(0);
  gen_set_label(done_3);
  setNFlag(a);
  gen_set_label(done_2);
  gen_set_label(done_1);

  return ret;
}





/* ADD2
 *    Variables: @a, @b, @c
 *    Functions: getCCFlag, getFFlag, setZFlag, setNFlag
 */

int
arc2_gen_ADD2 (DisasCtxt *ctx, TCGv a, TCGv b, TCGv c)
{
  int ret = BS_NONE;
  TCGLabel *done_1 = gen_new_label();
  TCGv temp_14 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_14, getCCFlag(), true);
  TCGv temp_15 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_15, temp_14, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_15, true, done_1);;
  TCGv temp_20 = tcg_temp_new_i32();
  tcg_gen_shli_i32(temp_20, c, 2);
  tcg_gen_add_i32(a, b, temp_20);
  TCGLabel *done_2 = gen_new_label();
  TCGv temp_16 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_16, getFFlag(), true);
  TCGv temp_17 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_17, temp_16, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_17, true, done_2);;
  TCGLabel *else_3 = gen_new_label();
  TCGLabel *done_3 = gen_new_label();
  TCGv temp_18 = tcg_temp_new_i32();
  tcg_gen_setcondi_i32(TCG_COND_EQ, temp_18, a, 0);
  TCGv temp_19 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_19, temp_18, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_19, true, else_3);;
  setZFlag(1);
  tcg_gen_br(done_3);
  gen_set_label(else_3);
  setZFlag(0);
  gen_set_label(done_3);
  setNFlag(a);
  gen_set_label(done_2);
  gen_set_label(done_1);

  return ret;
}





/* ADD3
 *    Variables: @a, @b, @c
 *    Functions: getCCFlag, getFFlag, setZFlag, setNFlag
 */

int
arc2_gen_ADD3 (DisasCtxt *ctx, TCGv a, TCGv b, TCGv c)
{
  int ret = BS_NONE;
  TCGLabel *done_1 = gen_new_label();
  TCGv temp_21 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_21, getCCFlag(), true);
  TCGv temp_22 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_22, temp_21, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_22, true, done_1);;
  TCGv temp_27 = tcg_temp_new_i32();
  tcg_gen_shli_i32(temp_27, c, 3);
  tcg_gen_add_i32(a, b, temp_27);
  TCGLabel *done_2 = gen_new_label();
  TCGv temp_23 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_23, getFFlag(), true);
  TCGv temp_24 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_24, temp_23, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_24, true, done_2);;
  TCGLabel *else_3 = gen_new_label();
  TCGLabel *done_3 = gen_new_label();
  TCGv temp_25 = tcg_temp_new_i32();
  tcg_gen_setcondi_i32(TCG_COND_EQ, temp_25, a, 0);
  TCGv temp_26 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_26, temp_25, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_26, true, else_3);;
  setZFlag(1);
  tcg_gen_br(done_3);
  gen_set_label(else_3);
  setZFlag(0);
  gen_set_label(done_3);
  setNFlag(a);
  gen_set_label(done_2);
  gen_set_label(done_1);

  return ret;
}





/* SUB
 *    Variables: @a, @b, @c
 *    Functions: getCCFlag, getFFlag, setZFlag, setNFlag
 */

int
arc2_gen_SUB (DisasCtxt *ctx, TCGv a, TCGv b, TCGv c)
{
  int ret = BS_NONE;
  TCGLabel *done_1 = gen_new_label();
  TCGv temp_28 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_28, getCCFlag(), true);
  TCGv temp_29 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_29, temp_28, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_29, true, done_1);;
  tcg_gen_sub_i32(a, b, c);
  TCGLabel *done_2 = gen_new_label();
  TCGv temp_30 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_30, getFFlag(), true);
  TCGv temp_31 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_31, temp_30, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_31, true, done_2);;
  TCGLabel *else_3 = gen_new_label();
  TCGLabel *done_3 = gen_new_label();
  TCGv temp_32 = tcg_temp_new_i32();
  tcg_gen_setcondi_i32(TCG_COND_EQ, temp_32, a, 0);
  TCGv temp_33 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_33, temp_32, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_33, true, else_3);;
  setZFlag(1);
  tcg_gen_br(done_3);
  gen_set_label(else_3);
  setZFlag(0);
  gen_set_label(done_3);
  setNFlag(a);
  gen_set_label(done_2);
  gen_set_label(done_1);

  return ret;
}





/* MUL
 *    Variables: @a, @b, @c
 *    Functions: getCCFlag, getFFlag, setZFlag, setNFlag
 */

int
arc2_gen_MUL (DisasCtxt *ctx, TCGv a, TCGv b, TCGv c)
{
  int ret = BS_NONE;
  TCGLabel *done_1 = gen_new_label();
  TCGv temp_34 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_34, getCCFlag(), true);
  TCGv temp_35 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_35, temp_34, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_35, true, done_1);;
  tcg_gen_mul_i32(a, b, c);
  TCGLabel *done_2 = gen_new_label();
  TCGv temp_36 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_36, getFFlag(), true);
  TCGv temp_37 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_37, temp_36, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_37, true, done_2);;
  TCGLabel *else_3 = gen_new_label();
  TCGLabel *done_3 = gen_new_label();
  TCGv temp_38 = tcg_temp_new_i32();
  tcg_gen_setcondi_i32(TCG_COND_EQ, temp_38, a, 0);
  TCGv temp_39 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_39, temp_38, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_39, true, else_3);;
  setZFlag(1);
  tcg_gen_br(done_3);
  gen_set_label(else_3);
  setZFlag(0);
  gen_set_label(done_3);
  setNFlag(a);
  gen_set_label(done_2);
  gen_set_label(done_1);

  return ret;
}





/* DIV
 *    Variables: @a, @b, @c
 *    Functions: getCCFlag, getFFlag, setZFlag, setNFlag
 */

int
arc2_gen_DIV (DisasCtxt *ctx, TCGv a, TCGv b, TCGv c)
{
  int ret = BS_NONE;
  TCGLabel *done_1 = gen_new_label();
  TCGv temp_40 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_40, getCCFlag(), true);
  TCGv temp_41 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_41, temp_40, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_41, true, done_1);;
  tcg_gen_div_i32(a, b, c);
  TCGLabel *done_2 = gen_new_label();
  TCGv temp_42 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_42, getFFlag(), true);
  TCGv temp_43 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_43, temp_42, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_43, true, done_2);;
  TCGLabel *else_3 = gen_new_label();
  TCGLabel *done_3 = gen_new_label();
  TCGv temp_44 = tcg_temp_new_i32();
  tcg_gen_setcondi_i32(TCG_COND_EQ, temp_44, a, 0);
  TCGv temp_45 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_45, temp_44, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_45, true, else_3);;
  setZFlag(1);
  tcg_gen_br(done_3);
  gen_set_label(else_3);
  setZFlag(0);
  gen_set_label(done_3);
  setNFlag(a);
  gen_set_label(done_2);
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
  TCGv temp_46 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_46, getCCFlag(), true);
  TCGv temp_47 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_47, temp_46, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_47, true, done_1);;
  tcg_gen_and_i32(a, b, c);
  TCGLabel *done_2 = gen_new_label();
  TCGv temp_48 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_48, getFFlag(), true);
  TCGv temp_49 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_49, temp_48, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_49, true, done_2);;
  TCGLabel *else_3 = gen_new_label();
  TCGLabel *done_3 = gen_new_label();
  TCGv temp_50 = tcg_temp_new_i32();
  tcg_gen_setcondi_i32(TCG_COND_EQ, temp_50, a, 0);
  TCGv temp_51 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_51, temp_50, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_51, true, else_3);;
  setZFlag(1);
  tcg_gen_br(done_3);
  gen_set_label(else_3);
  setZFlag(0);
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
  TCGv temp_52 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_52, getCCFlag(), true);
  TCGv temp_53 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_53, temp_52, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_53, true, done_1);;
  tcg_gen_or_i32(a, b, c);
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
  TCGv temp_58 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_58, getCCFlag(), true);
  TCGv temp_59 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_59, temp_58, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_59, true, done_1);;
  tcg_gen_xor_i32(a, b, c);
  TCGLabel *done_2 = gen_new_label();
  TCGv temp_60 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_60, getFFlag(), true);
  TCGv temp_61 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_61, temp_60, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_61, true, done_2);;
  TCGLabel *else_3 = gen_new_label();
  TCGLabel *done_3 = gen_new_label();
  TCGv temp_62 = tcg_temp_new_i32();
  tcg_gen_setcondi_i32(TCG_COND_EQ, temp_62, a, 0);
  TCGv temp_63 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_63, temp_62, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_63, true, else_3);;
  setZFlag(1);
  tcg_gen_br(done_3);
  gen_set_label(else_3);
  setZFlag(0);
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
  TCGv temp_64 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_64, getCCFlag(), true);
  TCGv temp_65 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_65, temp_64, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_65, true, done_1);;
  tcg_gen_mov_i32(a, b);
  TCGLabel *done_2 = gen_new_label();
  TCGv temp_66 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_66, getFFlag(), true);
  TCGv temp_67 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_67, temp_66, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_67, true, done_2);;
  TCGLabel *else_3 = gen_new_label();
  TCGLabel *done_3 = gen_new_label();
  TCGv temp_68 = tcg_temp_new_i32();
  tcg_gen_setcondi_i32(TCG_COND_EQ, temp_68, a, 0);
  TCGv temp_69 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_69, temp_68, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_69, true, else_3);;
  setZFlag(1);
  tcg_gen_br(done_3);
  gen_set_label(else_3);
  setZFlag(0);
  gen_set_label(done_3);
  setNFlag(a);
  gen_set_label(done_2);
  gen_set_label(done_1);

  return ret;
}





/* ADC
 *    Variables: @a, @b, @c
 *    Functions: getCCFlag, getCFlag, getFFlag, setZFlag, setNFlag
 */

int
arc2_gen_ADC (DisasCtxt *ctx, TCGv a, TCGv b, TCGv c)
{
  int ret = BS_NONE;
  TCGLabel *done_1 = gen_new_label();
  TCGv temp_70 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_70, getCCFlag(), true);
  TCGv temp_71 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_71, temp_70, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_71, true, done_1);;
  TCGv temp_77 = tcg_temp_new_i32();
  tcg_gen_mov_i32(temp_77, getCFlag());
  TCGv temp_76 = tcg_temp_new_i32();
  tcg_gen_add_i32(temp_76, b, c);
  tcg_gen_add_i32(a, temp_76, temp_77);
  TCGLabel *done_2 = gen_new_label();
  TCGv temp_72 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_72, getFFlag(), true);
  TCGv temp_73 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_73, temp_72, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_73, true, done_2);;
  TCGLabel *else_3 = gen_new_label();
  TCGLabel *done_3 = gen_new_label();
  TCGv temp_74 = tcg_temp_new_i32();
  tcg_gen_setcondi_i32(TCG_COND_EQ, temp_74, a, 0);
  TCGv temp_75 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_75, temp_74, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_75, true, else_3);;
  setZFlag(1);
  tcg_gen_br(done_3);
  gen_set_label(else_3);
  setZFlag(0);
  gen_set_label(done_3);
  setNFlag(a);
  gen_set_label(done_2);
  gen_set_label(done_1);

  return ret;
}





/* ASL
 *    Variables: @a, @b, @c
 *    Functions: getCCFlag, getFFlag, setZFlag, setNFlag
 */

int
arc2_gen_ASL (DisasCtxt *ctx, TCGv a, TCGv b, TCGv c)
{
  int ret = BS_NONE;
  TCGLabel *done_1 = gen_new_label();
  TCGv temp_78 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_78, getCCFlag(), true);
  TCGv temp_79 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_79, temp_78, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_79, true, done_1);;
  tcg_gen_shl_i32(a, b, c);
  TCGLabel *done_2 = gen_new_label();
  TCGv temp_80 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_80, getFFlag(), true);
  TCGv temp_81 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_81, temp_80, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_81, true, done_2);;
  TCGLabel *else_3 = gen_new_label();
  TCGLabel *done_3 = gen_new_label();
  TCGv temp_82 = tcg_temp_new_i32();
  tcg_gen_setcondi_i32(TCG_COND_EQ, temp_82, a, 0);
  TCGv temp_83 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_83, temp_82, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_83, true, else_3);;
  setZFlag(1);
  tcg_gen_br(done_3);
  gen_set_label(else_3);
  setZFlag(0);
  gen_set_label(done_3);
  setNFlag(a);
  gen_set_label(done_2);
  gen_set_label(done_1);

  return ret;
}





/* ASR
 *    Variables: @a, @b, @c
 *    Functions: getCCFlag, getFFlag, setZFlag, setNFlag
 */

int
arc2_gen_ASR (DisasCtxt *ctx, TCGv a, TCGv b, TCGv c)
{
  int ret = BS_NONE;
  TCGLabel *done_1 = gen_new_label();
  TCGv temp_84 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_84, getCCFlag(), true);
  TCGv temp_85 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_85, temp_84, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_85, true, done_1);;
  tcg_gen_shr_i32(a, b, c);
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
  TCGv temp_90 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_90, getCCFlag(), true);
  TCGv temp_91 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_91, temp_90, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_91, true, done_1);;
  tcg_gen_shri_i32(a, b, 16);
  TCGLabel *done_2 = gen_new_label();
  TCGv temp_92 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_92, getFFlag(), true);
  TCGv temp_93 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_93, temp_92, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_93, true, done_2);;
  TCGLabel *else_3 = gen_new_label();
  TCGLabel *done_3 = gen_new_label();
  TCGv temp_94 = tcg_temp_new_i32();
  tcg_gen_setcondi_i32(TCG_COND_EQ, temp_94, a, 0);
  TCGv temp_95 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_95, temp_94, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_95, true, else_3);;
  setZFlag(1);
  tcg_gen_br(done_3);
  gen_set_label(else_3);
  setZFlag(0);
  gen_set_label(done_3);
  setNFlag(a);
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
  TCGv temp_96 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_96, getCCFlag(), true);
  TCGv temp_97 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_97, temp_96, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_97, true, done_1);;
  tcg_gen_shri_i32(a, b, 16);
  TCGLabel *done_2 = gen_new_label();
  TCGv temp_98 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_98, getFFlag(), true);
  TCGv temp_99 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_99, temp_98, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_99, true, done_2);;
  TCGLabel *else_3 = gen_new_label();
  TCGLabel *done_3 = gen_new_label();
  TCGv temp_100 = tcg_temp_new_i32();
  tcg_gen_setcondi_i32(TCG_COND_EQ, temp_100, a, 0);
  TCGv temp_101 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_101, temp_100, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_101, true, else_3);;
  setZFlag(1);
  tcg_gen_br(done_3);
  gen_set_label(else_3);
  setZFlag(0);
  gen_set_label(done_3);
  setNFlag(a);
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
  TCGv temp_102 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_102, getCCFlag(), true);
  TCGv temp_103 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_103, temp_102, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_103, true, done_1);;
  TCGv temp_104 = tcg_temp_new_i32();
  tcg_gen_mul_i32(temp_104, b, c);
  tcg_gen_andi_i32(a, temp_104, 4294967295);
  gen_set_label(done_1);

  return ret;
}





/* ABS
 *    Variables: @src, @dest
 *    Functions: Carry, getFFlag, setZFlag, setNFlag
 */

int
arc2_gen_ABS (DisasCtxt *ctx, TCGv src, TCGv dest)
{
  int ret = BS_NONE;
  TCGv alu = tcg_temp_new_i32();
  tcg_gen_subfi_i32(alu, 0, src);
  TCGLabel *else_1 = gen_new_label();
  TCGLabel *done_1 = gen_new_label();
  TCGv temp_105 = tcg_temp_new_i32();
  tcg_gen_setcondi_i32(TCG_COND_EQ, temp_105, Carry(src), 1);
  TCGv temp_106 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_106, temp_105, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_106, true, else_1);;
  tcg_gen_mov_i32(dest, alu);
  tcg_gen_br(done_1);
  gen_set_label(else_1);
  tcg_gen_mov_i32(dest, src);
  gen_set_label(done_1);
  TCGLabel *done_2 = gen_new_label();
  TCGv temp_107 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_107, getFFlag(), true);
  TCGv temp_108 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_108, temp_107, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_108, true, done_2);;
  TCGLabel *else_3 = gen_new_label();
  TCGLabel *done_3 = gen_new_label();
  TCGv temp_109 = tcg_temp_new_i32();
  tcg_gen_setcondi_i32(TCG_COND_EQ, temp_109, dest, 0);
  TCGv temp_110 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_110, temp_109, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_110, true, else_3);;
  setZFlag(1);
  tcg_gen_br(done_3);
  gen_set_label(else_3);
  setZFlag(0);
  gen_set_label(done_3);
  setNFlag(dest);
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
  TCGv temp_111 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_111, getCCFlag(), true);
  TCGv temp_112 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_112, temp_111, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_112, true, done_1);;
  if ((shouldExecuteDelaySlot () == true))
    {
    executeDelaySlot();
;
    }
  TCGv temp_114 = tcg_temp_new_i32();
  tcg_gen_mov_i32(temp_114, getPCL());
  TCGv temp_113 = tcg_temp_new_i32();
  tcg_gen_add_i32(temp_113, temp_114, rd);
  setPC(temp_113);
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
  TCGv temp_115 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_115, getCCFlag(), true);
  TCGv temp_116 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_116, temp_115, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_116, true, done_1);;
  killDelaySlot();
  TCGv temp_118 = tcg_temp_new_i32();
  tcg_gen_mov_i32(temp_118, getPC());
  TCGv temp_117 = tcg_temp_new_i32();
  tcg_gen_add_i32(temp_117, temp_118, rd);
  setPC(temp_117);
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
  TCGv temp_119 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, temp_119, getCCFlag(), true);
  TCGv temp_120 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_120, temp_119, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_120, true, done_1);;
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
 *    Functions: getAAFlag, getZZFlag, setDebugLD, getZZSize, Memory, getFlagX, SignExtend, NoFurtherLoadsPending
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
    TCGv temp_124 = tcg_temp_new_i32();
  tcg_gen_shli_i32(temp_124, src2, 2);
  tcg_gen_add_i32(address, src1, temp_124);
;
    }
  if (((AA == 3) && (ZZ == 2)))
    {
    TCGv temp_125 = tcg_temp_new_i32();
  tcg_gen_shli_i32(temp_125, src2, 1);
  tcg_gen_add_i32(address, src1, temp_125);
;
    }
  if (((AA == 1) || (AA == 2)))
    {
    tcg_gen_add_i32(src1, src1, src2);
;
    }
  setDebugLD(1);
  TCGv size = tcg_temp_new_i32();
  tcg_gen_mov_i32(size, getZZSize());
  tcg_gen_mov_i32(dest, Memory(address, size));
  TCGLabel *done_1 = gen_new_label();
  TCGv temp_121 = tcg_temp_new_i32();
  tcg_gen_setcondi_i32(TCG_COND_EQ, temp_121, getFlagX(), 1);
  TCGv temp_122 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_122, temp_121, 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_122, true, done_1);;
  tcg_gen_mov_i32(dest, SignExtend(dest, size));
  gen_set_label(done_1);
  TCGLabel *done_2 = gen_new_label();
  TCGv temp_123 = tcg_temp_new_i32();
  tcg_gen_xori_i32(temp_123, NoFurtherLoadsPending(), 1);
  tcg_gen_brcond_i32(TCG_COND_EQ, temp_123, true, done_2);;
  setDebugLD(0);
  gen_set_label(done_2);

  return ret;
}
