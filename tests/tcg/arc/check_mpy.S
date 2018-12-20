.include "macros.inc"

start

.macro mul_test val1, val2, res
  mov  r0, \val1
  mov  r1, \val2
  mpyw r2, r0, r1
  assert_eq \res, r2
.endm


; 0x11220005 * 0x00120020 --> 0x0005 * 0x0020 = 160
mul_test  0x11220005, 0x00120020, 160

; 0xFFFFFFFF * 0x00000007 --> 0xFFFF (-1) * 0x0007 = 0xFFFFFFF9 (-7)
mul_test  0xFFFFFFFF, 0x00000007, 0xFFFFFFF9

print "Ret:0"        ; we have survived all the asserts

end
