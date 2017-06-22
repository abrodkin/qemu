/* ADD
 *   Variables: @a, @b, @c
 *   Functions: verifyCCFlag, insn_getFFlag, setZFlag, setNFlag
 */

int
arc2_gen_ADD (DisasCtxt *ctx, TCGv a, TCGv b, TCGv c)
{
  TCGv cc_flag = arc_gen_verifyCCFlag(ctx);

  TCGLabel *label_d1 = gen_new_label();
  tcg_gen_brcondi_tl(TCG_COND_NE, cc_flag, 1, label_d1);
  //if(verifyCCFlag () == true)
  //  {
      tcg_gen_add_tl(a, b, c);

      TCGv f_flag = arc_gen_verifyFFlag(ctx);

      TCGLabel *label_d2 = gen_new_label();
      tcg_gen_brcondi_tl(TCG_COND_NE, f_flag, 1, label_d2);
      //if(insn_getFFlag () == true)
      // {
	  TCGLabel *label_e3 = gen_new_label();
	  TCGLabel *label_d3 = gen_new_label();
	  tcg_gen_brcondi_tl(TCG_COND_NE, a, 0, label_e3);

	  //if(@a == 0)
	  //  {
	      //setZFlag (1);
	      setZFlag(1);
	      tcg_gen_br(label_d3);
	  //  }
	  //else
	  //  {
	      gen_set_label(label_e3);
	      setZFlag (0);
	      //tcg_gen_movi_tl(cpu_Cf, 0);
	  //  }
	  gen_set_label(label_d3);
	  setNFlag (a);
	// }
	gen_set_label(label_d2);
    //}
    gen_set_label(label_d1);
  return BS_NONE;
}
