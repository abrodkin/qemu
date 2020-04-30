; check_manip_mmu.S
;
; Tests for MMU: manipulate MMU table in exception routines.
; If the test fails, check the end of this file for how to troubleshoot.
; The running code for this test needs to be in address range >= 0x8000_0000.

  .include "macros.inc"
  .include "mmu.inc"

;;;;;;;;;;;;;;;;;;;;;;;;;;;; Bunch of constants ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

  .equ INT_VECT_ADDRESS, 0x80000000 ; physical address for IVT
  .equ STATUS32_AD_BIT , 19         ; Alignment Disable bit
  ; courtesy of macros.inc and mmu.inc
  .extern REG_IVT_BASE
  .extern PAGE_NUMBER_MSK
  .extern REG_PD0_GLOBAL
  .extern REG_PD0_VALID
  .extern REG_PD1_KRNL_W

;;;;;;;;;;;;;;;;;;;;;;;;;;; Test checking routines ;;;;;;;;;;;;;;;;;;;;;;;;;;

; Test case counter
.data
test_nr:
  .word 0x0

; Increment the test counter
.macro prep_test_case
  ld    r13, [test_nr]
  add_s r13, r13, 1       ; increase test case counter
  st    r13, [test_nr]
  mmu_disable
  set_except_handler 0x0
  enable_alignment
.endm

; Disable alignment so there will be no Misaligned exception
.macro disable_alignment
  lr    r11, [status32]
  bset  r11, r11, STATUS32_AD_BIT
  flag  r11
.endm

; Enable alignment again.
.macro enable_alignment
  lr    r11, [status32]
  bclr  r11, r11, STATUS32_AD_BIT
  flag  r11
.endm

;;;;;;;;;;;;;;;;;;;;;;;;; Exception related code ;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; Handler of the day.
  .align 4
handler : .word 0x0

; An exception handler routine that merely jumps to whatever address
; it was told to by the test. See set_except_handler macro. This
; requires ivt.S file to be compiled and linked.
  .align 4
  .global EV_TLBMissD
  .global EV_ProtV
  .type   EV_TLBMissD, @function
  .type   EV_ProtV, @function
EV_TLBMissD:
EV_ProtV:
  ld  r11, [handler]
  j   [r11]

; macro:      set_except_handler
; regs used:  r11
;
; This macro writes the provided ADDR to a temporary place holder
; that later the exception handler routine will jump to.
.macro set_except_handler   addr
  mov  r11, \addr
  st   r11, [handler]
.endm

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; Tests ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; Let the tests begin
  start
  ; use physicall address range for handling exceptions (ivt)
  mov   r0, INT_VECT_ADDRESS
  sr    r0, [REG_IVT_BASE]

; Test case 1:
; Reading from a virtual address that has no entry in TLB. This will
; cause a TLBMissD exception. In return, the exception routine handler
; will add the corresponding entry:
; ,-----------------.------------------.----------------------.
; | virtual address | physical address | (kernel) permissions |
; |-----------------+------------------+----------------------|
; | 0x1337_1334     | 0x7331_1334      | R--                  |
; `-----------------^------------------^----------------------'
; After returning from the exception, the "ld" should go OK.
; Then there comes a write ("st") that will trigger a ProtV exception.
; This time, we allow writing as well:
; ,-----------------.------------------.----------------------.
; | virtual address | physical address | (kernel) permissions |
; |-----------------+------------------+----------------------|
; | 0x1337_1334     | 0x7331_1334      | RW-                  |
; `-----------------^------------------^----------------------'
; the "st" to the same address should go fine.
  .equ T1_VIRT_ADDR, 0x13371334     ; the virtual address; word aligned
  .equ T1_PHYS_ADDR, 0x73311334     ; the physical address (same page offset as VA)
  .equ T1_DATA_1   , 0x00BADB07     ; the test value to read and verify
  .equ T1_DATA_2   , 0x00B07BAD     ; the test value to write and verify
  .equ T1_PD0   , ((T1_VIRT_ADDR & PAGE_NUMBER_MSK) | REG_PD0_GLOBAL | REG_PD0_VALID)
  .equ T1_PD1_R , ((T1_PHYS_ADDR & PAGE_NUMBER_MSK) | REG_PD1_KRNL_R)
  .equ T1_PD1_RW, (T1_PD1_R | REG_PD1_KRNL_W)
  prep_test_case
  mov     r2, 0               ; exception handler counter
  mov     r1, T1_DATA_1       ; plant the data ...
  st      r1, [T1_PHYS_ADDR]  ; ... into the physical address
  set_except_handler @test_1_except_handler
  mmu_enable
test_1_ld:
  ld      r0, [T1_VIRT_ADDR]  ; TLBMissD causing instruction
  cmp     r0, T1_DATA_1
  bne     @fail
  mov     r0, T1_DATA_2
test_1_st:
  st      r0, [T1_VIRT_ADDR]  ; TLBProtV causing instruction
  mmu_disable                 ; MMU bye-bye!
  ld      r1, [T1_PHYS_ADDR]  ; Load the final destination of "st"
  cmp     r1, T1_DATA_2       ; was it written successfuly?
  bne     @fail
  b       @test_1_end
test_1_except_handler:
  add_s   r2, r2, 1
  cmp     r2, 1               ; TLBMissD while loading?
  bne     @1f
  lr      r11, [ecr]
  cmp     r11, 0x50100        ; TLBMissD during a load?
  bne     @fail
  lr      r11, [eret]
  cmp     r11, @test_1_ld     ; instruction causing the exception
  lr      r11, [efa]
  cmp     r11, T1_VIRT_ADDR   ; faulty address is correct?
  jne     @fail
  mov     r11, 0
  sr      r11, [efa]          ; clearing EFA
  mmu_tlb_insert T1_PD0, T1_PD1_R
  rtie
1:
  cmp     r2, 2               ; ProtV during write?
  bne     @fail
  lr      r11, [ecr]
  cmp     r11, 0x60208        ; ProtV from MMU during a write?
  bne     @fail
  lr      r11, [eret]
  cmp     r11, @test_1_st     ; instruction causing the exception
  lr      r11, [efa]
  cmp     r11, T1_VIRT_ADDR   ; faulty address is correct?
  jne     @fail
  mmu_tlb_insert T1_PD0, T1_PD1_RW
  rtie
test_1_end:
  ; Fall through

; Test case 2
; Load a double word data straddled over two consecutive virtual pages:
; ,-------------------------------.,-----------------------------.
; |               ... x0 x1 x2 x3 || x4 x5 x6 x7 x8 ...          |
; `-------------------------------'`-----------------------------'
;  virt=0x0050_2000..0x0050_4000      virt=0x0050_4000..0x050_6000
;
; Only the first page has an entry in TLB:
; ,-----------------.------------------.----------------------.
; | virtual address | physical address | (kernel) permissions |
; |-----------------+------------------+----------------------|
; | 0x0050_2000     | 0x3000_8000      | R--                  |
; `-----------------^------------------^----------------------'
;
; An "ldd" from the last 4 byte of the first page will span to
; the second page. This will lead to an exception (TLBMissD).
  .equ T2_VIRT_ADDR, 0x00502000      ; virtual page address
  .equ T2_PHYS_ADDR, 0x30008000      ; physical page address
  .equ T2_ADDR_OFS,  0x00001FFC      ; the offset in the page
  .equ T2_PD0, ((T2_VIRT_ADDR+T2_ADDR_OFS & PAGE_NUMBER_MSK) | REG_PD0_GLOBAL | REG_PD0_VALID)
  .equ T2_PD1, ((T2_PHYS_ADDR             & PAGE_NUMBER_MSK) | REG_PD1_KRNL_R)

  prep_test_case
  mov     r2, 0               ; exception handler counter
  set_except_handler @test_2_except_handler
  mmu_tlb_insert T2_PD0, T2_PD1
  mmu_enable
test_2_ldd:
  ldd     r0, [T2_VIRT_ADDR+T2_ADDR_OFS]
  cmp     r2, 1
  bne     @fail
  b       @test_2_end         ; success!
test_2_except_handler:
  add     r2, r2, 1           ; increase the counter
  lr      r11, [ecr]
  cmp     r11, 0x50100        ; TLBMissD during a load?
  bne     @fail
  lr      r11, [eret]
  cmp     r11, @test_2_ldd
  jne     @fail
  lr      r11, [efa]
  cmp     r11, T2_VIRT_ADDR+T2_ADDR_OFS+4 ; beginning of next page
  jne     @fail
  mmu_disable
  rtie
test_2_end:
  ; Fall through

; Test case 3
; Load a data word (0x12345678) straddled over two consecutive
; virtual pages:
; ,--------------------.,--------------------.
; |           ... 0x78 || 0x56 0x34 0x12 ... |
; `--------------------'`--------------------'
;  virt=0x0000...0x2000  virt=0x2000...0x4000
;
; Only the first page has an entry in TLB:
; ,-----------------.------------------.----------------------.
; | virtual address | physical address | (kernel) permissions |
; |-----------------+------------------+----------------------|
; | 0x0000_0000     | 0x7000_0000      | R--                  |
; `-----------------^------------------^----------------------'
;
; An "ld" (word-sized) from the last byte of the first page will
; span to the first 3 bytes of the second page. This will lead
; to an exception (TLBMissD). The exception routine will add the
; entry for the second page:
; ,-----------------.------------------.----------------------.
; | virtual address | physical address | (kernel) permissions |
; |-----------------+------------------+----------------------|
; | 0x0000_0000     | 0x7000_0000      | R--                  |
; | 0x0000_2000     | 0x6000_2000      | R--                  |
; `-----------------^------------------^----------------------'
;
; And in the end, we must have fetched the data (0x12345678).
; To make the test realistic, the physical page addresses are not
; consecutive as opposed to their virtual counter parts.
; The alignment check should be disabled for this test.
  .equ T3_VIRT_ADDR_1, 0x00000000      ; two virtual page addresses ...
  .equ T3_VIRT_ADDR_2, 0x00002000      ; ... that are consecutive.
  .equ T3_PHYS_ADDR_1, 0x70000000      ; two physical page addresses ...
  .equ T3_PHYS_ADDR_2, 0x60002000      ; ... that are inconsecutive.
  .equ T3_ADDR_1_OFS,  0x00001FFF      ; the offset in the first pages.
  .equ T3_PD0_ENT1, ((T3_VIRT_ADDR_1+T3_ADDR_1_OFS & PAGE_NUMBER_MSK) | REG_PD0_GLOBAL | REG_PD0_VALID)
  .equ T3_PD1_ENT1, ((T3_PHYS_ADDR_1               & PAGE_NUMBER_MSK) | REG_PD1_KRNL_R)
  .equ T3_PD0_ENT2, ((T3_VIRT_ADDR_2               & PAGE_NUMBER_MSK) | REG_PD0_GLOBAL | REG_PD0_VALID)
  .equ T3_PD1_ENT2, ((T3_PHYS_ADDR_2               & PAGE_NUMBER_MSK) | REG_PD1_KRNL_R)
  prep_test_case
  ; Plant data at the physical addresses
  mov     r1, 0x12345678
  stb     r1, [T3_PHYS_ADDR_1+T3_ADDR_1_OFS]  ; 0x78 at the end of first page
  lsr8    r1, r1
  sth     r1, [T3_PHYS_ADDR_2]                ; 0x56 0x34 at the beginning of 2nd page
  lsr16   r1, r1
  stb     r1, [T3_PHYS_ADDR_2+2]              ; 0x12 The 3rd byte on the 2nd page
  mov     r1, 0                               ; exception handler counter
  disable_alignment
  set_except_handler @test_3_except_handler
  mmu_tlb_insert T3_PD0_ENT1, T3_PD1_ENT1
  mmu_enable
  ; Exception-causing instruction
test_3_ld:
  ld      r0, [T3_VIRT_ADDR_1+T3_ADDR_1_OFS]
  mov     r3, 0x12345678
  cmp     r0, r3
  bne     @fail
  cmp     r1, 1
  bne     @fail
  b       @test_3_end         ; success!
test_3_except_handler:
  add     r1, r1, 1           ; increase the counter
  lr      r11, [ecr]
  cmp     r11, 0x50100        ; TLBMissD during a load?
  bne     @fail
  lr      r11, [eret]
  cmp     r11, @test_3_ld
  jne     @fail
  lr      r11, [efa]
  cmp     r11, T3_VIRT_ADDR_2
  jne     @fail
  mmu_tlb_insert T3_PD0_ENT2, T3_PD1_ENT2
  rtie
test_3_end:
  ; Fall through

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; Reporting ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

valhalla:
  print "[PASS]"
  b @1f

; If a test fails, it jumps here. Although, for the sake of uniformity,
; the printed output does not say much about which test case failed,
; one can uncomment the print_number line below or set a breakpoint
; here to check the R0 register for the test case number.
fail:
  ld r0, [test_nr]
  ;print_number r0
  print "[FAIL]"
1:
  print " MMU: manipulate MMU table in exception routines\n"
  end
