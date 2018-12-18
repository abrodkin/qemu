	.include "macros.inc"

	.section .ivt, "a", @progbits
#define IVT_ENTRY(name) \
    .word name `\
    .weak name `\
    .set name, _exit_halt

; handler's name,          number, name,       offset in IVT (hex/dec)
	.word main                   ; 0   program entry point  0x0     0
	IVT_ENTRY(memory_error)      ; 1   memory_error         0x4     4
	IVT_ENTRY(instruction_error) ; 2   instruction_error    0x8     8
	IVT_ENTRY(EV_MachineCheck)   ; 3   EV_MachineCheck      0xC     12
	IVT_ENTRY(EV_TLBMissI)       ; 4   EV_TLBMissI          0x10    16
	IVT_ENTRY(EV_TLBMissD)       ; 5   EV_TLBMissD          0x14    20
	IVT_ENTRY(EV_ProtV)          ; 6   EV_ProtV             0x18    24
	IVT_ENTRY(EV_PrivilegeV)     ; 7   EV_PrivilegeV        0x1C    28
	IVT_ENTRY(EV_SWI)            ; 8   EV_SWI               0x20    32
	IVT_ENTRY(EV_Trap)           ; 9   EV_Trap              0x24    36
	IVT_ENTRY(EV_Extension)      ; 10  EV_Extension         0x28    40
	IVT_ENTRY(EV_DivZero)        ; 11  EV_DivZero           0x2C    44
	IVT_ENTRY(EV_DCError)        ; 12  EV_DCError           0x30    48
	IVT_ENTRY(EV_Maligned)       ; 13  EV_Maligned          0x34    52
	IVT_ENTRY(EV_Ex14)           ; 14  unused               0x38    56
	IVT_ENTRY(EV_Ex15)           ; 15  unused               0x3C    60
	.word IRQ_Timer0        ; 16  Timer 0              0x40    64
	IVT_ENTRY(IRQ_Timer1)        ; 17  Timer 1              0x44    68
	IVT_ENTRY(IRQ_18)            ; 18                       0x48    72
	IVT_ENTRY(IRQ_19)            ; 19                       0x4C    76
	IVT_ENTRY(IRQ_20)            ; 20                       0x50    80

	start
	test_name TIMER0
	mov	r0, 0x00
	sr	r0,[0x21]
	print	 "......"
	lr 	r2,[0x21]
	breq	r2, 0, @.lfail
	print	"."
	lr	r0,[0x21]
	breq	r0,r2,@.lfail
	print	"Pass\n"
	sr	0x01,[0x22]
	sr	0xff,[0x23]
	mov	r3, 0
	seti
.loop0:
	breq	r3, 0, @.loop0
	print	"The end\n"
	end
.lfail:
	print	"Fail\n"
	end

	.align 4
	.global IRQ_Timer0
	.type IRQ_Timer0, @function
IRQ_Timer0:
	clri
	sr	0x00,[0x22]
	print "Pass IRQ\n"
	mov	r3, 1
	;; 	rtie
	end

	.global	 _exit_halt
	.type	 _exit_halt, @function
	.align 4
_exit_halt:
	print "Fail\n"
	end
