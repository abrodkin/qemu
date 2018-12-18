	.include "macros.inc"

	start
	print "Start\n"
	seti
	sr	18, [aux_irq_hint]
	print "End\n"
	end

	.align 4
	.global IRQ_18
	.type IRQ_18, @function
IRQ_18:
	clri
	sr	0, [aux_irq_hint]
	print "Pass SW-IRQ\n"
	end

