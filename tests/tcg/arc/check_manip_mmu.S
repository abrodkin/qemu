.include "macros.inc"
.include "mmu.inc"

; courtesy of macros.inc and mmu.inc
.extern REG_IVT_BASE
.extern PAGE_NUMBER_MSK
.extern REG_PD0_GLOBAL
.extern REG_PD0_VALID
.extern REG_PD1_KRNL_W

; test data
; making an entry for the TLB
;
; ,------------------------------------.
; | VPN(VA), G=1, V=1 | PPN(PHY), Wk=1 |
; `------------------------------------'
; where:
; VPN(VA) is the virtual page number of logical address
; G is the global bit
; V is the validity bit
; PPN(PHY) is the physical page number
; Wk is the write permission in kernel mode

; obviously, the offsets in both addresses must be the same
.equ VIRT_ADR    , 0x13371334     ; the virtual address; word aligned
.equ PHYS_ADR    , 0x73311334     ; the physical address > 0x7FFFFFFF
.equ MAGICDATA1  , 0x00BADB07     ; the test value to read and verify
.equ MAGICDATA2  , 0x00B07BAD     ; the test value to write and verify
.equ PD0_VPN     , (VIRT_ADR & PAGE_NUMBER_MSK)
.equ PD1_PPN     , (PHYS_ADR & PAGE_NUMBER_MSK)
.equ PD0_BITS    , (PD0_VPN | REG_PD0_GLOBAL | REG_PD0_VALID)
.equ PD1_R_BITS  , (PD1_PPN | REG_PD1_KRNL_R)
.equ PD1_RW_BITS , (PD1_PPN | REG_PD1_KRNL_R | REG_PD1_KRNL_W)
.equ INT_VECT_ADDRESS, 0x80000000 ; physical address for IVT

; each time the exception is raised, this is incremented
TLB_MissD_counter: .word 0x0
ProtV_counter:     .word 0x0

  start

  ; use physicall address range for handling exceptions (ivt)
  mov   r0, INT_VECT_ADDRESS
  sr    r0, [REG_IVT_BASE]

  ; planting the first magic number at physical address
  mov   r0, MAGICDATA1
  st    r0, [PHYS_ADR]

  mmu_enable

  ; read the mapped virtual address
  ld    r1, [VIRT_ADR] ; this must cause a MissD exception
  cmp   r0, r1         ; r0 contains MAGICDATA1
  bne   @badboy
  ld    r1, [TLB_MissD_counter]
  cmp_s r1, 1
  bne   @badboy
  ld    r1, [ProtV_counter]
  cmp_s r1, 0
  bne   @badboy

  ; write to the mapped virtual address
  mov   r0, MAGICDATA2
  st    r0, [VIRT_ADR]   ; this must cause a ProtV exception

  mmu_disable

  ; with mmu disabled, read from physical address and
  ; verify that it is the same  as the  value written
  ; to the mapped virtual address earlier
  ld    r1, [PHYS_ADR]
  cmp   r0, r1           ; r0 contains the MAGICDATA2
  bne   @badboy
  ld    r1, [TLB_MissD_counter]
  cmp_s r1, 1
  bne   @badboy
  ld    r1, [ProtV_counter]
  cmp_s r1, 1
  beq   @goodboy

badboy:
  print "Nope. Try again!\n"
  j     @adios

goodboy:
  print "You are officially an MMU manipulator!\n"

adios:
  end

  .align 4
  .global EV_TLBMissD
  .type EV_TLBMissD, @function
EV_TLBMissD:
  ; increase the counter first
  ld    r11, [TLB_MissD_counter]
  add   r11, r11, 1
  st    r11, [TLB_MissD_counter]
  ; add entry with "read only" permission
  mmu_tlb_insert PD0_BITS, PD1_R_BITS
  rtie

  .align 4
  .global EV_ProtV
  .type EV_ProtV, @function
EV_ProtV:
  ; increase the counter first
  ld    r11, [ProtV_counter]
  add   r11, r11, 1
  st    r11, [ProtV_counter]
  ; re-add entry with "read/write" permission
  mmu_tlb_insert PD0_BITS, PD1_RW_BITS
  rtie
