.equ MAX_TESTNAME_LEN, 32
.macro test_name name
    .data
tn_\name:
    .ascii "\name"
    .space MAX_TESTNAME_LEN - (. - tn_\name), ' '
    .text
.endm

.macro check_r2 val
  sub.f     r0, r2, \val
  mov.eq    r0, 0x30      ; '0'
  mov.ne    r0, 0x31      ; '1'
  print     "Ret:"
  st        r0, [OUTPUT_DEVICE]
  print     "\n"
.endm

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

.equ   OUTPUT_DEVICE, 0x90000000      ; output device address in QEMU

; macro:     print
; input:     message - the string to be printed
; regs used: r11, r12
; example:   print "hello world\n"
;
; caveat emptor:
;   this macro uses relative lables. if the  code using this macro
;   happens to use the same  relative lables, then  the  assembler
;   will get confused. these labels are: '0000', '1111', '2222'
;   last  but  not  least, this  macro   assumes   the   following
;   instructions already work: 'ldb.ab', 'breq', 'stb', 'j'
.macro  print message

  .data
  0000:
  .asciz "\message"
  .align 4

  .text
  mov_s     r11, @0000b                 ; the message to be printed
  1111:
    ldb.ab  r12, [r11, 1]
    breq    r12, 0, @2222f
    stb     r12, [OUTPUT_DEVICE]
    j       @1111b
  2222:
.endm

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; macro:     swap_nibbles_32
; input:     any positive number
; result:    r12
; regs used: r11, r12
; example:   swap_nibbles_32 0x12345678  --> r12 = 0x87654321
;
; description:
;   swaps all the nibles (4-bit digits) in a 32-bit long number
;
; caveat emptor:
;   this  macro assumes the following instructions already work:
;   'asl', 'lsr, 'breq', 'bnz', 'j'
.macro  swap_nibbles_32  number
  asl   r12, \number, 28
  asl   r11, \number, 20
  and   r11, r11, 0x0F000000
  or    r12, r12, r11

  asl   r11, \number, 12
  and   r11, r11, 0x00F00000
  or    r12, r12, r11
  asl   r11, \number, 4
  and   r11, r11, 0x000F0000
  or    r12, r12, r11

  lsr   r11, \number, 4
  and   r11, r11, 0x0000F000
  or    r12, r12, r11
  lsr   r11, \number, 12
  and   r11, r11, 0x00000F00
  or    r12, r12, r11

  lsr   r11, \number, 20
  and   r11, r11, 0x000000F0
  or    r12, r12, r11
  lsr   r11, \number, 28
  and   r11, r11, 0x0000000F
  or    r12, r12, r11
.endm

; macro:     print_number
; input:     BCD (Binary Coded Decimal) number
; regs used: r11, r12
; example:   print 0x123
;            print 0x11       --> to print "11", DO NOT USE print 0xB
;
; description:
;   given a number in BCD form (hexadecimal digits representing a
;   decimal number), prints it to the output.
;
; caveat emptor:
;   this macro uses relative lables. if the  code using this macro
;   happens to use the same  relative lables, then  the  assembler
;   will get confused. these labels are: '4444', '5555'
;   last  but  not  least, this  macro   assumes   the   following
;   instructions already work: 'asl', 'lsr, 'breq', 'bnz', 'j'
.macro print_number  num

  swap_nibbles_32 \num     ; i.e. mov r12, nible_swap(num)
  ; if the input is 0, just go for printing (will print only one byte)
  breq  r12, 0, @5555f
  ; getting rid of trailing 0's
  4444:
  and.f 0, r12, 0x0F
  bnz   @5555f
  lsr   r12, r12, 4
  j     @4444b

  5555:
  and   r11, r12, 0x0F
  add   r11, r11, '0'
  st    r11, [OUTPUT_DEVICE]
  lsr.f r12, r12, 4
  bnz   @5555b
.endm

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; macro:     assert_eq
; input:     a, b - two values/registers to be compared
;            num  - optional: printed error number, default is 1.
;                   valid range is: [0 ... 9]
; regs used: r11, r12
; example:   assert_eq 12, r2
;            assert_eq r1, 8
;            assert_eq r3, r4
;            assert_eq 8 , 9     (although useless for tests)
;
; description:
;   compares  the  two inputs. if they are equal, nothing happens.
;   but if not, then it is going to print "Ret:1" and exit.
;
; caveat emptor:
;   this macro uses a relative lable. if the code using this macro
;   happens to use the  same  relative lable, then  the  assembler
;   will get confused. this label is: '3333'
.macro assert_eq a, b, num=1
  mov   r11, \a
  mov   r12, \b
  breq  r11, r12, @3333f
  print "Ret:"
  print_number \num
  end
3333:
.endm

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; STATUS register and its masks
.equ REG_STAT, 0x0A     ; STATUS32 register
.equ REG_STAT_V, 0x0100 ; mask for Over flow bit
.equ REG_STAT_C, 0x0200 ; mask for Carry bit
.equ REG_STAT_N, 0x0400 ; mask for Negative bit
.equ REG_STAT_Z, 0x0800 ; mask for Zero bit

; macro:     assert_flag
; input:     reg_stat_flag - index to get the corresponding flag
;            bit           - verification value: 0 or 1
;            num           - optional: printed error number, default
;                            is 1. valid range is: [0 ... 9]
; regs used: r11, r12
; example:   assert_flag REG_STAT_Z, 1, num=8
;            assert_flag 0x0200    , 0, num=3
;
; description:
;   extracts the corresponding bit at given index by reg_stat_flag.
;   if it holds  the  same value  as  given 'bit', nothing happens,
;   else it will print an error and exit.
;
; caveat emptor:
;   this macro uses a relative lable. if the code using this macro
;   happens to use the  same  relative lable, then  the  assembler
;   will get confused. this label is: '3333'
.macro assert_flag reg_stat_flag, bit, num
  lr     r11, [REG_STAT]
  and    r11, r11, \reg_stat_flag
  ; if bit=0 then checking if r11 == 0
  ; if bit=1 then checking if r11 == bit_mask
  assert_eq r11, \bit*\reg_stat_flag, \num
.endm

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

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
