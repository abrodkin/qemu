.equ MAX_TESTNAME_LEN, 32
.macro test_name name
        .data
tn_\name:
        .ascii "\name"
        .space MAX_TESTNAME_LEN - (. - tn_\name), ' '
        .text
\name:
.endm

.macro tc_pass
        mov	r2, 'P'
        st      r2, [0x90000000]
        mov     r2, 'a'
        st      r2, [0x90000000]
        mov     r2, 's'
        st      r2, [0x90000000]
        mov     r2, 's'
        st      r2, [0x90000000]
        mov     r2, '\n'
        st      r2, [0x90000000]
.endm

.macro tc_fail
        mov     r2, 'F'
        st      r2, [0x90000000]
        mov     r2, 'a'
        st      r2, [0x90000000]
        mov     r2, 'i'
        st      r2, [0x90000000]
        mov     r2, 'l'
        st      r2, [0x90000000]
        mov     r2, '\n'
        st      r2, [0x90000000]
.endm

.macro check_r2x val
	breq	r2, \val, 1f
	tc_fail
	.align 4
1:
        tc_pass
2:
.endm

.macro check_r2 val
	sub.f 	r0,r2,\val
	mov.eq	r0,0x30
	mov.ne	r0,0x31
        mov     r2, 'R'
        st      r2, [0x90000000]
        mov     r2, 'e'
        st      r2, [0x90000000]
        mov     r2, 't'
        st      r2, [0x90000000]
        mov     r2, ':'
        st      r2, [0x90000000]
	mov	r2,r0
        st      r2, [0x90000000]
        mov     r2, '\n'
        st      r2, [0x90000000]
.endm

.macro start
	.text
        .global main
	.align 4
main:
.endm

.macro end
1:
        st 1,[0xf0000008]
        b @1b
.endm
