	.include "macros.inc"

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
