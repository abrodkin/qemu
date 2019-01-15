.include "macros.inc"

.equ NOTSET, 47806

; conditionally sets the ACC data
.macro setup_acc acch, accl
  .if \accl <> NOTSET
    mov r58, \accl
  .endif
  .if \acch <> NOTSET
    mov r59, \acch
  .endif
.endm

; conditionally checks if ACC holds the given value
.macro verify_acc racch, raccl, test_num
  .if \raccl <> NOTSET
    assert_eq r58, \raccl, \test_num
  .endif
  .if \racch <> NOTSET
    assert_eq r59, \racch, \test_num
  .endif
.endm

; all Z, N, C, V flags are cleared and ACC will become 0
.macro clear_flags_and_accu
  ; clearing the Z N C V flags
  mov r0, 1
  add.f r0, r0, r0
  ; clearing the acc
  mov r58, 0
  mov r59, 0
.endm

; checks if Z, N, C, and V flags are set correctly
.macro verify_flags z=0, n=0, c=0, v=0, test_num
  assert_flag REG_STAT_Z, \z, \test_num
  assert_flag REG_STAT_N, \n, \test_num
  assert_flag REG_STAT_C, \c, \test_num
  assert_flag REG_STAT_V, \v, \test_num
.endm

; macro for testing "MAC" instruction
.macro mac_test acch=NOTSET, accl=NOTSET, val1, val2, res, racch=NOTSET, raccl=NOTSET, n=0, v=0, test_num
  ; initializing data
  setup_acc \acch, \accl
  mov    r0, \val1
  mov    r1, \val2
  ; operation under test
  mac.f  r0, r0, r1
  ; checking the results
  verify_flags n=\n, v=\v, test_num=\test_num
  assert_eq \res, r0, \test_num
  verify_acc \racch, \raccl, \test_num
.endm

; macro for testing "MACU" instruction
.macro macu_test acch=NOTSET, accl=NOTSET, val1, val2, res, racch=NOTSET, raccl=NOTSET, v=0, test_num
  ; initializing data
  setup_acc \acch, \accl
  mov    r0, \val1
  mov    r1, \val2
  ; operation under test
  macu.f  r0, r0, r1
  ; checking the results
  verify_flags v=\v, test_num=\test_num
  assert_eq \res, r0, \test_num
  verify_acc \racch, \raccl, \test_num
.endm


start

;;;;;;;;;;;;;;;;;;;;; MAC ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
mac_test val1=4, val2=5, res=20, test_num=0x01
; acc is now 20
mac_test val1=1, val2=5, res=25, test_num=0x02
; producing a result that sets both acch and accl
mac_test acch=0, accl=0, val1=0x7FFFFFFF, val2=0x7FFFFFFF, res=1, racch=0x3FFFFFFF, raccl=0x01, n=0, v=0, test_num=0x03
; acc is 0x3FFFFFFF00000001
mac_test val1=0x80000000, val2=0x80000000, res=1, racch=0x7FFFFFFF, raccl=0x01, n=0, v=0, test_num=0x04
; acc is 0x7FFFFFFF00000001; going for the kill: N and V will be set
mac_test val1=0x12344321, val2=0x56788654, res=0xE1C14CD5, racch=0x86262098, raccl=0xE1C14CD5, n=1, v=1, test_num=0x05
; "mac" is not supposed to clear the overflow bit
mac_test acch=0, accl=0, val1=0, val2=0, res=0, racch=0, raccl=0, n=0, v=1, test_num=0x06
clear_flags_and_accu


;;;;;;;;;;;;;;;;;;;;; MACU ;;;;;;;;;;;;;;;;;;;;;;;;;;;;
macu_test val1=4, val2=5, res=20, test_num=0x07
; acc is now 20
macu_test val1=1, val2=5, res=25, test_num=0x08
; producing a result that sets both acch and accl
macu_test acch=0, accl=0, val1=0x7FFFFFFF, val2=0x7FFFFFFF, res=1, racch=0x3FFFFFFF, raccl=0x01, v=0, test_num=0x09
; acc is 0x3FFFFFFF00000001
macu_test val1=0x80000000, val2=0x80000000, res=1, racch=0x7FFFFFFF, raccl=0x01, v=0, test_num=0x10
; acc is 0x7FFFFFFF00000001; line below still will not trigger an overflow for MACU
macu_test val1=0x12344321, val2=0x56788654, res=0xE1C14CD5, racch=0x86262098, raccl=0xE1C14CD5, v=0, test_num=0x11
; cause an overflow
macu_test acch=0xFFFFFFFF, accl=0xFFFFFFFF, val1=1, val2=1, res=0, racch=0, raccl=0, v=1, test_num=0x12
; "mac" is not supposed to clear the overflow bit
macu_test acch=0, accl=0, val1=0, val2=0, res=0, racch=0, raccl=0, v=1, test_num=0x13
clear_flags_and_accu


;;;;;;;;;;;;;;;;;;;;; MACD ;;;;;;;;;;;;;;;;;;;;;;;;;;;;


;;;;;;;;;;;;;;;;;;;; MACDU ;;;;;;;;;;;;;;;;;;;;;;;;;;;;



print "Ret:0"

end
