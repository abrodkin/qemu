  .include "macros.inc"

  start
  
  lr  r0, [status32]
  or  r0, r0, 128      ; set the STATUS32.U
  sr  r0, [erstatus] 
  mov r0, @user_mode
  sr  r0, [eret]
  rtie

user_mode:
  ; must cause privilege violation exception
  rtie

good:
  print "You're on a righteous path.\n"
  end

  .align 4
  .global EV_PrivilegeV
  .type EV_PrivilegeV, @function
EV_PrivilegeV:
  lr r0, [eret]
  breq r0, @user_mode, @return
    print "Life sucks. Get over it!\n"
    end
return:
  mov r0, @good
  sr  r0, [eret]
  rtie
