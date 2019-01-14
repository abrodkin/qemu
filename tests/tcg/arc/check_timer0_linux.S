	.include "macros.inc"

	start
	test_name TIMER0
	;; enable TIMER0 interrupts
	sr	0x01,[control0]
	mov	r0, 0x1fffff
	sr	r0,[limit0]
	sr	0,[count0]
	;; and enable the interrupts
	mov	r3,0
	seti
.loop0:
	brlt	r3, 2, @.loop0
	print	"The end\n"
	end

	;; The ISR has two states:
	;; 1. will return w/o cleaning the interrupt.
	;; 2. will clean the interrupt and exit the test.
	.align 4
	.global IRQ_Timer0
	.type IRQ_Timer0, @function
IRQ_Timer0:
	clri
	breq	r3,1,1f
	;; first state
	print	"First state\n"
	mov	r3,1
	sr	0,[aux_irq_act]
	seti
	j	[ilink]
1:
	;; second state
	;; reset interrupts
	sr	0x00,[control0]
	print "Pass IRQ\n"
	mov	r3, 4
	rtie
	end
