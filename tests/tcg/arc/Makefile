-include ../../../config-host.mak

CROSS = arc-elf32-
#CROSS = arc-snps-linux-uclibc-

SIM = ../../../arc-softmmu/qemu-system-arc
SIM_FLAGS = -M arc-sim -m 3G -nographic -no-reboot -monitor none \
	-serial stdio -kernel
#SIM_FLAGS=-cpu archs
TST_PATH = $(SRC_PATH)/tests/tcg/arc

CC = $(CROSS)gcc
LD = $(CROSS)ld
AS = $(CROSS)as
CFLAGS  = -mcpu=archs -O2 --specs=qemu.specs
ASFLAGS = -mcpu=archs
LDPHYSFLAGS = --section-start=.text=0x80000000

TESTCASES = check_add.tst
TESTCASES += check_lp.tst
TESTCASES += check_lp02.tst
TESTCASES += check_lp03.tst
TESTCASES += check_addx.tst
TESTCASES += check_andx.tst
TESTCASES += check_aslx.tst
TESTCASES += check_asrx.tst
TESTCASES += check_orx.tst
TESTCASES += check_rorx.tst
TESTCASES += check_subx.tst
TESTCASES += check_xorx.tst
TESTCASES += check_beqx.tst
TESTCASES += check_bnex.tst
TESTCASES += check_brhsx.tst
TESTCASES += check_brlox.tst
TESTCASES += check_breqx.tst
TESTCASES += check_brnex.tst
TESTCASES += check_brltx.tst
TESTCASES += check_brgex.tst
TESTCASES += check_ldstx.tst
TESTCASES += check_stld.tst
TESTCASES += check_lsrx.tst
TESTCASES += check_beq.tst
TESTCASES += check_carry.tst
TESTCASES += check_flags.tst
TESTCASES += check_t01.tst
TESTCASES += check_t02.tst
TESTCASES += check_basic1.tst
TESTCASES += check_basic2.tst
TESTCASES += check_norm.tst
TESTCASES += check_excp.tst
TESTCASES += check_excp_1.ctst
TESTCASES += check_mmu.tst
TESTCASES += check_excp_mmu.tst
TESTCASES += check_timer0.tst
TESTCASES += check_timer0_loop.tst
TESTCASES += check_timer0_linux.tst
TESTCASES += check_timer0_sleep.tst
TESTCASES += check_swirq.tst
TESTCASES += check_swirq1.tst
TESTCASES += check_mpyw.tst
TESTCASES += check_subf.tst
TESTCASES += check_mac.tst

all: $(TESTCASES)
OBJECTS = ivt.o

%.o: $(SRC_PATH)/tests/tcg/arc/%.S
	echo "Running: $(CC) $(ASFLAGS) -c $< -o $@ -I$(TST_PATH)"; \
	$(CC) $(ASFLAGS) -c $< -o $@ -I$(TST_PATH)

%_mmu.tst: %_mmu.o ${OBJECTS} $(SRC_PATH)/tests/tcg/arc/macros.inc $(SRC_PATH)/tests/tcg/arc/mmu.inc
	echo "Running: $(LD) $(LDPHYSFLAGS) -T $(TST_PATH)/tarc.ld ${OBJECTS} $< -o $@"; \
	$(LD) $(LDPHYSFLAGS) -T $(TST_PATH)/tarc.ld ${OBJECTS} $< -o $@

%.tst: %.o ${OBJECTS} $(SRC_PATH)/tests/tcg/arc/macros.inc
	echo "Running: $(LD) -T $(TST_PATH)/tarc.ld ${OBJECTS} $< -o $@"; \
	$(LD) -T $(TST_PATH)/tarc.ld ${OBJECTS} $< -o $@

%.ctst: $(SRC_PATH)/tests/tcg/arc/%.c
	$(CC) $(CFLAGS) -Wl,-marcv2elfx -L $(SRC_PATH)/tests/tcg/arc/ $< -o $@

check: $(TESTCASES)
	@for case in $(TESTCASES); do \
	echo $(SIM) $(SIM_FLAGS) ./$$case;\
	$(SIM) $(SIM_FLAGS) ./$$case; \
	done

clean:
	$(RM) -rf $(TESTCASES)
