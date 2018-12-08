.include "macros.inc"

start

.equ REG_PD0         , 0x460          ; aux register TLBPD0
.equ REG_PD1         , 0x461          ; aux register TLBPD1
.equ REG_TLB_INDX    , 0x464          ; aux register TLB Index
.equ REG_TLB_CMD     , 0x465          ; aux register TLB command
.equ REG_PID         , 0x468          ; aux register Process Identity
.equ REG_PID_TLB_SET , 0x80000000     ; the setting  mask for TLB bit in PID
.equ REG_PID_TLB_CLR , 0x7FFFFFFF     ; the clearing mask for TLB bit in PID
;.equ VIRT_ADR        , 0x10000000     ; the virtual address (<= 0x7FFFFFFF)
;.equ PHYS_ADR        , 0x70000000     ; the physical address mapped for VA
.equ VIRT_ADR        , 0x13370000     ; the virtual address (<= 0x7FFFFFFF)
.equ PHYS_ADR        , 0x73310000     ; the physical address mapped for VA
.equ DATA            , 0x00BADB07     ; the test value to write and read
.equ PAGE_INDEX_BITS , 13             ; page size is _assumed_ to be 8 KB
.equ REG_PD0_VG_SET  , 0x00000300     ; Global and Valid bit set in TLBPD0
.equ REG_PD0_VPN_POS , 13             ; Virtual Page Number bit position
.equ REG_PD0_VPN     , (VIRT_ADR >> PAGE_INDEX_BITS) << REG_PD0_VPN_POS
.equ REG_PD0_BITS    , (REG_PD0_VG_SET | REG_PD0_VPN)
.equ REG_PD1_KRNL_RWE, 0x20           ; allow "write" in kernel mode
.equ REG_PD1_PPN_POS , 13             ; Physical Page Number bit position
.equ REG_PD1_PPN     , (PHYS_ADR >> PAGE_INDEX_BITS) << REG_PD1_PPN_POS
.equ REG_PD1_BITS    , (REG_PD1_KRNL_RWE | REG_PD1_PPN)
.equ TLB_CMD_WRITE   , 0x01           ; write command for TLB
.equ TLB_CMD_READ    , 0x02           ; read command for TLB
.equ TLB_CMD_GET_INDX, 0x03           ; get index command for TLB
.equ TLB_CMD_PROBE   , 0x04           ; probe command for TLB
.equ TLB_CMD_INSERT  , 0x07           ; insert command for TLB


; enable mmu
mov r3, REG_PID_TLB_SET
sr  r3, [REG_PID]

; insert into table: VA 0x13371337 (Global) --> PHY: 0x73317331 (RW kernel)
mov r0, REG_PD0_BITS
sr  r0, [REG_PD0]
mov r1, REG_PD1_BITS
sr  r1, [REG_PD1]
mov r3, TLB_CMD_INSERT
sr  r3, [REG_TLB_CMD]

; write to physicall address through the virtual address
mov r0, DATA
st  r0, [VIRT_ADR]

; disable mmu
lr  r3, [REG_PID]
and r3, r3, REG_PID_TLB_CLR
sr  r3, [REG_PID]

; with mmu disabled read from physical address now
ld  r1, [PHYS_ADR]
cmp r0, r1
beq @goodboy

print "You suck!\n"
j   @adios

goodboy:
print "Yay, you got the MMU right :)\n"

adios:
end
