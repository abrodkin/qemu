


/* ADD
 *    Variables: @a, @b, @c
 *    Functions: getCCFlag, getFFlag, setZFlag, setNFlag
 */

int
arc2_gen_ADD (DisasCtxt *ctx, TCGv a, TCGv b, TCGv c)
{

// if(getCCFlag () == true)
  TCGLabel *label_d1 = gen_new_label();
  TCGv cond_2 = tcg_temp_new_i32();
  tcg_gen_mov_i32(cond_2, getCCFlag ());
  TCGv cond_3 = tcg_temp_new_i32();
  tcg_gen_movi_i32(cond_3, 1);

  TCGv cond_1 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, cond_1, cond_2, cond_3);
// getCCFlag () == true
  tcg_gen_brcondi_i32(TCG_COND_NE, cond_1, 1, label_d1);
// @a = @b+@c
// @b + @c
  TCGv var_1 = tcg_temp_new_i32();
  tcg_gen_add_i32 (var_1, b, c);
  tcg_gen_mov_i32 (a, var_1);
// if(getFFlag () == true)
  TCGLabel *label_d2 = gen_new_label();
  TCGv cond_5 = tcg_temp_new_i32();
  tcg_gen_mov_i32(cond_5, getFFlag ());
  TCGv cond_6 = tcg_temp_new_i32();
  tcg_gen_movi_i32(cond_6, 1);

  TCGv cond_4 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, cond_4, cond_5, cond_6);
// getFFlag () == true
  tcg_gen_brcondi_i32(TCG_COND_NE, cond_4, 1, label_d2);

// if(@a == 0)
  TCGLabel *label_d3 = gen_new_label();
  TCGLabel *label_e3 = gen_new_label();
  TCGv cond_8 = tcg_temp_new_i32();
  tcg_gen_mov_i32(cond_8, a);
  TCGv cond_9 = tcg_temp_new_i32();
  tcg_gen_movi_i32(cond_9, 0);

  TCGv cond_7 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, cond_7, cond_8, cond_9);
// @a == 0
  tcg_gen_brcondi_i32(TCG_COND_NE, cond_7, 1, label_e3);
  setZFlag (1);

  gen_set_label(label_e3);
// else
  setZFlag (0);

  gen_set_label(label_d3);
  setNFlag (a);

  gen_set_label(label_d2);

  gen_set_label(label_d1);

  return BS_NONE;
}





/* ADD1
 *    Variables: @a, @b, @c
 *    Functions: getCCFlag, getFFlag, setZFlag, setNFlag
 */

int
arc2_gen_ADD1 (DisasCtxt *ctx, TCGv a, TCGv b, TCGv c)
{

// if(getCCFlag () == true)
  TCGLabel *label_d4 = gen_new_label();
  TCGv cond_11 = tcg_temp_new_i32();
  tcg_gen_mov_i32(cond_11, getCCFlag ());
  TCGv cond_12 = tcg_temp_new_i32();
  tcg_gen_movi_i32(cond_12, 1);

  TCGv cond_10 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, cond_10, cond_11, cond_12);
// getCCFlag () == true
  tcg_gen_brcondi_i32(TCG_COND_NE, cond_10, 1, label_d4);
// @a = @b+@c<<1
// @b + @c<<1
  TCGv var_2 = tcg_temp_new_i32();
// @c << 1
  TCGv var_3 = tcg_temp_new_i32();
  tcg_gen_shli_i32 (var_3, c, 1);
  tcg_gen_add_i32 (var_2, b, var_3);
  tcg_gen_mov_i32 (a, var_2);
// if(getFFlag () == true)
  TCGLabel *label_d5 = gen_new_label();
  TCGv cond_14 = tcg_temp_new_i32();
  tcg_gen_mov_i32(cond_14, getFFlag ());
  TCGv cond_15 = tcg_temp_new_i32();
  tcg_gen_movi_i32(cond_15, 1);

  TCGv cond_13 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, cond_13, cond_14, cond_15);
// getFFlag () == true
  tcg_gen_brcondi_i32(TCG_COND_NE, cond_13, 1, label_d5);

// if(@a == 0)
  TCGLabel *label_d6 = gen_new_label();
  TCGLabel *label_e6 = gen_new_label();
  TCGv cond_17 = tcg_temp_new_i32();
  tcg_gen_mov_i32(cond_17, a);
  TCGv cond_18 = tcg_temp_new_i32();
  tcg_gen_movi_i32(cond_18, 0);

  TCGv cond_16 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, cond_16, cond_17, cond_18);
// @a == 0
  tcg_gen_brcondi_i32(TCG_COND_NE, cond_16, 1, label_e6);
  setZFlag (1);

  gen_set_label(label_e6);
// else
  setZFlag (0);

  gen_set_label(label_d6);
  setNFlag (a);

  gen_set_label(label_d5);

  gen_set_label(label_d4);

  return BS_NONE;
}





/* ADD2
 *    Variables: @a, @b, @c
 *    Functions: getCCFlag, getFFlag, setZFlag, setNFlag
 */

int
arc2_gen_ADD2 (DisasCtxt *ctx, TCGv a, TCGv b, TCGv c)
{

// if(getCCFlag () == true)
  TCGLabel *label_d7 = gen_new_label();
  TCGv cond_20 = tcg_temp_new_i32();
  tcg_gen_mov_i32(cond_20, getCCFlag ());
  TCGv cond_21 = tcg_temp_new_i32();
  tcg_gen_movi_i32(cond_21, 1);

  TCGv cond_19 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, cond_19, cond_20, cond_21);
// getCCFlag () == true
  tcg_gen_brcondi_i32(TCG_COND_NE, cond_19, 1, label_d7);
// @a = @b+@c<<2
// @b + @c<<2
  TCGv var_4 = tcg_temp_new_i32();
// @c << 2
  TCGv var_5 = tcg_temp_new_i32();
  tcg_gen_shli_i32 (var_5, c, 2);
  tcg_gen_add_i32 (var_4, b, var_5);
  tcg_gen_mov_i32 (a, var_4);
// if(getFFlag () == true)
  TCGLabel *label_d8 = gen_new_label();
  TCGv cond_23 = tcg_temp_new_i32();
  tcg_gen_mov_i32(cond_23, getFFlag ());
  TCGv cond_24 = tcg_temp_new_i32();
  tcg_gen_movi_i32(cond_24, 1);

  TCGv cond_22 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, cond_22, cond_23, cond_24);
// getFFlag () == true
  tcg_gen_brcondi_i32(TCG_COND_NE, cond_22, 1, label_d8);

// if(@a == 0)
  TCGLabel *label_d9 = gen_new_label();
  TCGLabel *label_e9 = gen_new_label();
  TCGv cond_26 = tcg_temp_new_i32();
  tcg_gen_mov_i32(cond_26, a);
  TCGv cond_27 = tcg_temp_new_i32();
  tcg_gen_movi_i32(cond_27, 0);

  TCGv cond_25 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, cond_25, cond_26, cond_27);
// @a == 0
  tcg_gen_brcondi_i32(TCG_COND_NE, cond_25, 1, label_e9);
  setZFlag (1);

  gen_set_label(label_e9);
// else
  setZFlag (0);

  gen_set_label(label_d9);
  setNFlag (a);

  gen_set_label(label_d8);

  gen_set_label(label_d7);

  return BS_NONE;
}





/* ADD3
 *    Variables: @a, @b, @c
 *    Functions: getCCFlag, getFFlag, setZFlag, setNFlag
 */

int
arc2_gen_ADD3 (DisasCtxt *ctx, TCGv a, TCGv b, TCGv c)
{

// if(getCCFlag () == true)
  TCGLabel *label_d10 = gen_new_label();
  TCGv cond_29 = tcg_temp_new_i32();
  tcg_gen_mov_i32(cond_29, getCCFlag ());
  TCGv cond_30 = tcg_temp_new_i32();
  tcg_gen_movi_i32(cond_30, 1);

  TCGv cond_28 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, cond_28, cond_29, cond_30);
// getCCFlag () == true
  tcg_gen_brcondi_i32(TCG_COND_NE, cond_28, 1, label_d10);
// @a = @b+@c<<3
// @b + @c<<3
  TCGv var_6 = tcg_temp_new_i32();
// @c << 3
  TCGv var_7 = tcg_temp_new_i32();
  tcg_gen_shli_i32 (var_7, c, 3);
  tcg_gen_add_i32 (var_6, b, var_7);
  tcg_gen_mov_i32 (a, var_6);
// if(getFFlag () == true)
  TCGLabel *label_d11 = gen_new_label();
  TCGv cond_32 = tcg_temp_new_i32();
  tcg_gen_mov_i32(cond_32, getFFlag ());
  TCGv cond_33 = tcg_temp_new_i32();
  tcg_gen_movi_i32(cond_33, 1);

  TCGv cond_31 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, cond_31, cond_32, cond_33);
// getFFlag () == true
  tcg_gen_brcondi_i32(TCG_COND_NE, cond_31, 1, label_d11);

// if(@a == 0)
  TCGLabel *label_d12 = gen_new_label();
  TCGLabel *label_e12 = gen_new_label();
  TCGv cond_35 = tcg_temp_new_i32();
  tcg_gen_mov_i32(cond_35, a);
  TCGv cond_36 = tcg_temp_new_i32();
  tcg_gen_movi_i32(cond_36, 0);

  TCGv cond_34 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, cond_34, cond_35, cond_36);
// @a == 0
  tcg_gen_brcondi_i32(TCG_COND_NE, cond_34, 1, label_e12);
  setZFlag (1);

  gen_set_label(label_e12);
// else
  setZFlag (0);

  gen_set_label(label_d12);
  setNFlag (a);

  gen_set_label(label_d11);

  gen_set_label(label_d10);

  return BS_NONE;
}





/* SUB
 *    Variables: @a, @b, @c
 *    Functions: getCCFlag, getFFlag, setZFlag, setNFlag
 */

int
arc2_gen_SUB (DisasCtxt *ctx, TCGv a, TCGv b, TCGv c)
{

// if(getCCFlag () == true)
  TCGLabel *label_d13 = gen_new_label();
  TCGv cond_38 = tcg_temp_new_i32();
  tcg_gen_mov_i32(cond_38, getCCFlag ());
  TCGv cond_39 = tcg_temp_new_i32();
  tcg_gen_movi_i32(cond_39, 1);

  TCGv cond_37 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, cond_37, cond_38, cond_39);
// getCCFlag () == true
  tcg_gen_brcondi_i32(TCG_COND_NE, cond_37, 1, label_d13);
// @a = @b-@c
// @b - @c
  TCGv var_8 = tcg_temp_new_i32();
  tcg_gen_sub_i32 (var_8, b, c);
  tcg_gen_mov_i32 (a, var_8);
// if(getFFlag () == true)
  TCGLabel *label_d14 = gen_new_label();
  TCGv cond_41 = tcg_temp_new_i32();
  tcg_gen_mov_i32(cond_41, getFFlag ());
  TCGv cond_42 = tcg_temp_new_i32();
  tcg_gen_movi_i32(cond_42, 1);

  TCGv cond_40 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, cond_40, cond_41, cond_42);
// getFFlag () == true
  tcg_gen_brcondi_i32(TCG_COND_NE, cond_40, 1, label_d14);

// if(@a == 0)
  TCGLabel *label_d15 = gen_new_label();
  TCGLabel *label_e15 = gen_new_label();
  TCGv cond_44 = tcg_temp_new_i32();
  tcg_gen_mov_i32(cond_44, a);
  TCGv cond_45 = tcg_temp_new_i32();
  tcg_gen_movi_i32(cond_45, 0);

  TCGv cond_43 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, cond_43, cond_44, cond_45);
// @a == 0
  tcg_gen_brcondi_i32(TCG_COND_NE, cond_43, 1, label_e15);
  setZFlag (1);

  gen_set_label(label_e15);
// else
  setZFlag (0);

  gen_set_label(label_d15);
  setNFlag (a);

  gen_set_label(label_d14);

  gen_set_label(label_d13);

  return BS_NONE;
}





/* MUL
 *    Variables: @a, @b, @c
 *    Functions: getCCFlag, getFFlag, setZFlag, setNFlag
 */

int
arc2_gen_MUL (DisasCtxt *ctx, TCGv a, TCGv b, TCGv c)
{

// if(getCCFlag () == true)
  TCGLabel *label_d16 = gen_new_label();
  TCGv cond_47 = tcg_temp_new_i32();
  tcg_gen_mov_i32(cond_47, getCCFlag ());
  TCGv cond_48 = tcg_temp_new_i32();
  tcg_gen_movi_i32(cond_48, 1);

  TCGv cond_46 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, cond_46, cond_47, cond_48);
// getCCFlag () == true
  tcg_gen_brcondi_i32(TCG_COND_NE, cond_46, 1, label_d16);
// @a = @b*@c
// @b * @c
  TCGv var_9 = tcg_temp_new_i32();
  tcg_gen_mul_i32 (var_9, b, c);
  tcg_gen_mov_i32 (a, var_9);
// if(getFFlag () == true)
  TCGLabel *label_d17 = gen_new_label();
  TCGv cond_50 = tcg_temp_new_i32();
  tcg_gen_mov_i32(cond_50, getFFlag ());
  TCGv cond_51 = tcg_temp_new_i32();
  tcg_gen_movi_i32(cond_51, 1);

  TCGv cond_49 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, cond_49, cond_50, cond_51);
// getFFlag () == true
  tcg_gen_brcondi_i32(TCG_COND_NE, cond_49, 1, label_d17);

// if(@a == 0)
  TCGLabel *label_d18 = gen_new_label();
  TCGLabel *label_e18 = gen_new_label();
  TCGv cond_53 = tcg_temp_new_i32();
  tcg_gen_mov_i32(cond_53, a);
  TCGv cond_54 = tcg_temp_new_i32();
  tcg_gen_movi_i32(cond_54, 0);

  TCGv cond_52 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, cond_52, cond_53, cond_54);
// @a == 0
  tcg_gen_brcondi_i32(TCG_COND_NE, cond_52, 1, label_e18);
  setZFlag (1);

  gen_set_label(label_e18);
// else
  setZFlag (0);

  gen_set_label(label_d18);
  setNFlag (a);

  gen_set_label(label_d17);

  gen_set_label(label_d16);

  return BS_NONE;
}





/* DIV
 *    Variables: @a, @b, @c
 *    Functions: getCCFlag, getFFlag, setZFlag, setNFlag
 */

int
arc2_gen_DIV (DisasCtxt *ctx, TCGv a, TCGv b, TCGv c)
{

// if(getCCFlag () == true)
  TCGLabel *label_d19 = gen_new_label();
  TCGv cond_56 = tcg_temp_new_i32();
  tcg_gen_mov_i32(cond_56, getCCFlag ());
  TCGv cond_57 = tcg_temp_new_i32();
  tcg_gen_movi_i32(cond_57, 1);

  TCGv cond_55 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, cond_55, cond_56, cond_57);
// getCCFlag () == true
  tcg_gen_brcondi_i32(TCG_COND_NE, cond_55, 1, label_d19);
// @a = @b/@c
// @b / @c
  TCGv var_10 = tcg_temp_new_i32();
  tcg_gen_div_i32 (var_10, b, c);
  tcg_gen_mov_i32 (a, var_10);
// if(getFFlag () == true)
  TCGLabel *label_d20 = gen_new_label();
  TCGv cond_59 = tcg_temp_new_i32();
  tcg_gen_mov_i32(cond_59, getFFlag ());
  TCGv cond_60 = tcg_temp_new_i32();
  tcg_gen_movi_i32(cond_60, 1);

  TCGv cond_58 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, cond_58, cond_59, cond_60);
// getFFlag () == true
  tcg_gen_brcondi_i32(TCG_COND_NE, cond_58, 1, label_d20);

// if(@a == 0)
  TCGLabel *label_d21 = gen_new_label();
  TCGLabel *label_e21 = gen_new_label();
  TCGv cond_62 = tcg_temp_new_i32();
  tcg_gen_mov_i32(cond_62, a);
  TCGv cond_63 = tcg_temp_new_i32();
  tcg_gen_movi_i32(cond_63, 0);

  TCGv cond_61 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, cond_61, cond_62, cond_63);
// @a == 0
  tcg_gen_brcondi_i32(TCG_COND_NE, cond_61, 1, label_e21);
  setZFlag (1);

  gen_set_label(label_e21);
// else
  setZFlag (0);

  gen_set_label(label_d21);
  setNFlag (a);

  gen_set_label(label_d20);

  gen_set_label(label_d19);

  return BS_NONE;
}





/* AND
 *    Variables: @a, @b, @c
 *    Functions: getCCFlag, getFFlag, setZFlag, setNFlag
 */

int
arc2_gen_AND (DisasCtxt *ctx, TCGv a, TCGv b, TCGv c)
{

// if(getCCFlag () == true)
  TCGLabel *label_d22 = gen_new_label();
  TCGv cond_65 = tcg_temp_new_i32();
  tcg_gen_mov_i32(cond_65, getCCFlag ());
  TCGv cond_66 = tcg_temp_new_i32();
  tcg_gen_movi_i32(cond_66, 1);

  TCGv cond_64 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, cond_64, cond_65, cond_66);
// getCCFlag () == true
  tcg_gen_brcondi_i32(TCG_COND_NE, cond_64, 1, label_d22);
// @a = @b&@c
// @b & @c
  TCGv var_11 = tcg_temp_new_i32();
  tcg_gen_and_i32 (var_11, b, c);
  tcg_gen_mov_i32 (a, var_11);
// if(getFFlag () == true)
  TCGLabel *label_d23 = gen_new_label();
  TCGv cond_68 = tcg_temp_new_i32();
  tcg_gen_mov_i32(cond_68, getFFlag ());
  TCGv cond_69 = tcg_temp_new_i32();
  tcg_gen_movi_i32(cond_69, 1);

  TCGv cond_67 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, cond_67, cond_68, cond_69);
// getFFlag () == true
  tcg_gen_brcondi_i32(TCG_COND_NE, cond_67, 1, label_d23);

// if(@a == 0)
  TCGLabel *label_d24 = gen_new_label();
  TCGLabel *label_e24 = gen_new_label();
  TCGv cond_71 = tcg_temp_new_i32();
  tcg_gen_mov_i32(cond_71, a);
  TCGv cond_72 = tcg_temp_new_i32();
  tcg_gen_movi_i32(cond_72, 0);

  TCGv cond_70 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, cond_70, cond_71, cond_72);
// @a == 0
  tcg_gen_brcondi_i32(TCG_COND_NE, cond_70, 1, label_e24);
  setZFlag (1);

  gen_set_label(label_e24);
// else
  setZFlag (0);

  gen_set_label(label_d24);
  setNFlag (a);

  gen_set_label(label_d23);

  gen_set_label(label_d22);

  return BS_NONE;
}





/* OR
 *    Variables: @a, @b, @c
 *    Functions: getCCFlag, getFFlag, setZFlag, setNFlag
 */

int
arc2_gen_OR (DisasCtxt *ctx, TCGv a, TCGv b, TCGv c)
{

// if(getCCFlag () == true)
  TCGLabel *label_d25 = gen_new_label();
  TCGv cond_74 = tcg_temp_new_i32();
  tcg_gen_mov_i32(cond_74, getCCFlag ());
  TCGv cond_75 = tcg_temp_new_i32();
  tcg_gen_movi_i32(cond_75, 1);

  TCGv cond_73 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, cond_73, cond_74, cond_75);
// getCCFlag () == true
  tcg_gen_brcondi_i32(TCG_COND_NE, cond_73, 1, label_d25);
// @a = @b|@c
// @b | @c
  TCGv var_12 = tcg_temp_new_i32();
  tcg_gen_or_i32 (var_12, b, c);
  tcg_gen_mov_i32 (a, var_12);
// if(getFFlag () == true)
  TCGLabel *label_d26 = gen_new_label();
  TCGv cond_77 = tcg_temp_new_i32();
  tcg_gen_mov_i32(cond_77, getFFlag ());
  TCGv cond_78 = tcg_temp_new_i32();
  tcg_gen_movi_i32(cond_78, 1);

  TCGv cond_76 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, cond_76, cond_77, cond_78);
// getFFlag () == true
  tcg_gen_brcondi_i32(TCG_COND_NE, cond_76, 1, label_d26);

// if(@a == 0)
  TCGLabel *label_d27 = gen_new_label();
  TCGLabel *label_e27 = gen_new_label();
  TCGv cond_80 = tcg_temp_new_i32();
  tcg_gen_mov_i32(cond_80, a);
  TCGv cond_81 = tcg_temp_new_i32();
  tcg_gen_movi_i32(cond_81, 0);

  TCGv cond_79 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, cond_79, cond_80, cond_81);
// @a == 0
  tcg_gen_brcondi_i32(TCG_COND_NE, cond_79, 1, label_e27);
  setZFlag (1);

  gen_set_label(label_e27);
// else
  setZFlag (0);

  gen_set_label(label_d27);
  setNFlag (a);

  gen_set_label(label_d26);

  gen_set_label(label_d25);

  return BS_NONE;
}





/* XOR
 *    Variables: @a, @b, @c
 *    Functions: getCCFlag, getFFlag, setZFlag, setNFlag
 */

int
arc2_gen_XOR (DisasCtxt *ctx, TCGv a, TCGv b, TCGv c)
{

// if(getCCFlag () == true)
  TCGLabel *label_d28 = gen_new_label();
  TCGv cond_83 = tcg_temp_new_i32();
  tcg_gen_mov_i32(cond_83, getCCFlag ());
  TCGv cond_84 = tcg_temp_new_i32();
  tcg_gen_movi_i32(cond_84, 1);

  TCGv cond_82 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, cond_82, cond_83, cond_84);
// getCCFlag () == true
  tcg_gen_brcondi_i32(TCG_COND_NE, cond_82, 1, label_d28);
// @a = @b^@c
// @b ^ @c
  TCGv var_13 = tcg_temp_new_i32();
  tcg_gen_xor_i32 (var_13, b, c);
  tcg_gen_mov_i32 (a, var_13);
// if(getFFlag () == true)
  TCGLabel *label_d29 = gen_new_label();
  TCGv cond_86 = tcg_temp_new_i32();
  tcg_gen_mov_i32(cond_86, getFFlag ());
  TCGv cond_87 = tcg_temp_new_i32();
  tcg_gen_movi_i32(cond_87, 1);

  TCGv cond_85 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, cond_85, cond_86, cond_87);
// getFFlag () == true
  tcg_gen_brcondi_i32(TCG_COND_NE, cond_85, 1, label_d29);

// if(@a == 0)
  TCGLabel *label_d30 = gen_new_label();
  TCGLabel *label_e30 = gen_new_label();
  TCGv cond_89 = tcg_temp_new_i32();
  tcg_gen_mov_i32(cond_89, a);
  TCGv cond_90 = tcg_temp_new_i32();
  tcg_gen_movi_i32(cond_90, 0);

  TCGv cond_88 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, cond_88, cond_89, cond_90);
// @a == 0
  tcg_gen_brcondi_i32(TCG_COND_NE, cond_88, 1, label_e30);
  setZFlag (1);

  gen_set_label(label_e30);
// else
  setZFlag (0);

  gen_set_label(label_d30);
  setNFlag (a);

  gen_set_label(label_d29);

  gen_set_label(label_d28);

  return BS_NONE;
}





/* MOV
 *    Variables: @a, @b
 *    Functions: getCCFlag, getFFlag, setZFlag, setNFlag
 */

int
arc2_gen_MOV (DisasCtxt *ctx, TCGv a, TCGv b)
{

// if(getCCFlag () == true)
  TCGLabel *label_d31 = gen_new_label();
  TCGv cond_92 = tcg_temp_new_i32();
  tcg_gen_mov_i32(cond_92, getCCFlag ());
  TCGv cond_93 = tcg_temp_new_i32();
  tcg_gen_movi_i32(cond_93, 1);

  TCGv cond_91 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, cond_91, cond_92, cond_93);
// getCCFlag () == true
  tcg_gen_brcondi_i32(TCG_COND_NE, cond_91, 1, label_d31);
// @a = @b
  tcg_gen_mov_i32 (a, b);
// if(getFFlag () == true)
  TCGLabel *label_d32 = gen_new_label();
  TCGv cond_95 = tcg_temp_new_i32();
  tcg_gen_mov_i32(cond_95, getFFlag ());
  TCGv cond_96 = tcg_temp_new_i32();
  tcg_gen_movi_i32(cond_96, 1);

  TCGv cond_94 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, cond_94, cond_95, cond_96);
// getFFlag () == true
  tcg_gen_brcondi_i32(TCG_COND_NE, cond_94, 1, label_d32);

// if(@a == 0)
  TCGLabel *label_d33 = gen_new_label();
  TCGLabel *label_e33 = gen_new_label();
  TCGv cond_98 = tcg_temp_new_i32();
  tcg_gen_mov_i32(cond_98, a);
  TCGv cond_99 = tcg_temp_new_i32();
  tcg_gen_movi_i32(cond_99, 0);

  TCGv cond_97 = tcg_temp_new_i32();
  tcg_gen_setcond_i32(TCG_COND_EQ, cond_97, cond_98, cond_99);
// @a == 0
  tcg_gen_brcondi_i32(TCG_COND_NE, cond_97, 1, label_e33);
  setZFlag (1);

  gen_set_label(label_e33);
// else
  setZFlag (0);

  gen_set_label(label_d33);
  setNFlag (a);

  gen_set_label(label_d32);

  gen_set_label(label_d31);

  return BS_NONE;
}
