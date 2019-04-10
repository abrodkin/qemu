	.include "macros.inc"

	start
	print "Check if an IRQ gets re-trigger while in ISR:"
	;; Set the stack somewhere
	mov	sp, 0x1000
	seti
	mov	r0,0
	;; Use IRQ18 for the test.
	sr	18, [AUX_IRQ_HINT]
	;; Sleep until we get the IRQ
	sleep
	brlt	r0, 2, @.failMe
	print " Pass\n"
	end
.failMe:
	print " Fail\n"
	end

	/* The delay between writing to the AUX_IRQ_HINT register and
	the interrupt being taken is implementation specific.  Hence,
	we need to save/restore any clobber register by ISR.  */
	.align 4
	.global IRQ_18
	.type IRQ_18, @function
IRQ_18:
	clri
	add	r0,r0,1
	;; clean the IRQ
	sr	0, [AUX_IRQ_HINT]
	brgt	r0,1,@.extisr
	;; retrigger the irq
	sr	18, [AUX_IRQ_HINT]
	print " SW-IRQ 0,"
	rtie
.extisr:
	print " SW-IRQ 1,"
	rtie
	end
