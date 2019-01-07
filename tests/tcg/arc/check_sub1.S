.include "macros.inc"

.macro sub1_flags_test val1, val2, res, z=0, n=0, c=0, v=0, test_num=1
  mov    r0, \val1
  mov    r1, \val2
  sub1.f r2, r0, r1
  assert_eq   \res, r2, \test_num
  assert_flag REG_STAT_Z, \z, \test_num
  assert_flag REG_STAT_N, \n, \test_num
  assert_flag REG_STAT_C, \c, \test_num
  assert_flag REG_STAT_V, \v, \test_num
.endm

start

;  0xa0a87000    - 0x58000000<<1  = 0xf0a87000
;sub1_flags_test 0xa0a87000, 0x58000000, 0xf0a87000, z=0, n=1, c=1, v=0

;  0xa0a87000    - 0xb0000000     = 0xf0a87000
sub1_flags_test 0xa0000000, 0x58000000, 0xf0000000, z=0, n=1, c=1, v=0


print "Ret:0"        ; we have survived all the asserts

end
