	.include "macros.inc"

	start
	test_name TIMER0
	mov	r0, 0x0
	sr	r0,[0x21]
	print	 "......"
	lr 	r2,[0x21]
	breq	r2, 0, @.lfail
	print	"."
	lr	r0,[0x21]
	breq	r0,r2,@.lfail
	print	"Pass\n"
	sr	0x01,[0x22]
	mov	r0, 0xffff
	sr	r0,[0x23]
	sr	0,[0x21]
	mov	r3, 0
	seti
.loop0:
	clri    r4
	breq	r3, 0, @.loop0
	seti    r4
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
	rtie
	end
