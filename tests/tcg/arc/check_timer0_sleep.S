  .include "macros.inc"
  .equ INT_VECT_ADDRESS, 0x80000000 ; physical address for IVT

  start

  ; use physicall address range for handling exceptions (ivt)
  mov r0, INT_VECT_ADDRESS
  sr  r0, [REG_IVT_BASE]

  ; enable TIMER0 interrupts
  sr  0x01,[control0]
  mov r0, 0x5ffff
  sr  r0,[limit0]
  sr  0,[count0]
  mov r3, 0
  seti

  sleep

  breq  r3, 1, @.passMe
  print "Fail\n"
  end
.passMe:
  print "Pass\n"
  end

  .align 4
  .global IRQ_Timer0
  .type IRQ_Timer0, @function
IRQ_Timer0:
  clri
  ; reset interrupts
  sr  0x00,[control0]
  mov r3, 1
  rtie
  end
