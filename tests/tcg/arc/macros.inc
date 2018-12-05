.equ MAX_TESTNAME_LEN, 32
.macro test_name name
    .data
tn_\name:
    .ascii "\name"
    .space MAX_TESTNAME_LEN - (. - tn_\name), ' '
    .text
.endm


; macro:   print
; input:   message - the string to be printed
; example: print "hello world\n"
;
; caveat emptor:
;   this macro uses temporary lables. if the code using this macro
;   happens to use the same temporary lables, then  the  assembler
;   will get confused. these labels are: '0000', '1111', '2222'
;   last  but  not  least, this  macro   assumes   the   following
;   instructions already work: 'push',  'pop',  'mov_s',  'ldb_s',
;                              'breq',  'stb',  'add_s',  'j'
.macro  print message
  .equ   OUTPUT_DEVICE, 0x90000000     ; video device address in QEMU

  .data
  0000:
  .asciz "\message"

  .text
  mov_s   r11, @0000b                  ; the message to be printed
  1111:
    ldb.ab	r12, [r11, 1]
    breq	r12, 0, @2222f
    stb		r12, [OUTPUT_DEVICE]
    j       @1111b
  2222:
.endm


.macro check_r2x val
  breq    r2, \val, @1f
  print   "Fail\n"
  .align 4
1:
  print   "Pass\n"
2:
.endm

.macro check_r2 val
  sub.f   r0, r2, \val
  mov.eq  r0, 0x30      ; '0'
  mov.ne  r0, 0x31      ; '1'
  print   "Ret:"
  mov     r2, r0
  st      r2, [OUTPUT_DEVICE]
  print   "\n"
.endm

.macro start
  .text
    .global main
    .align 4
  main:
.endm

.macro end
1:
  st 1, [0xf0000008]
  b @1b
.endm
