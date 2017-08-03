-include ../../../config-host.mak

CROSS = arc-elf32-
#CROSS = arc-snps-linux-uclibc-

SIM = ../../../arc-softmmu/qemu-system-arc
SIM_FLAGS = -M arc-sim -m 128M -nographic -no-reboot -monitor none \
	-serial stdio -kernel
#SIM_FLAGS=-cpu archs
TST_PATH = $(SRC_PATH)/tests/tcg/arc

CC = $(CROSS)gcc
LD = $(CROSS)ld
AS = $(CROSS)as
CFLAGS  = -mcpu=archs -O1
ASFLAGS = -mcpu=archs

TESTCASES = check_add.tst
TESTCASES += check_addx.tst
TESTCASES += check_andx.tst
TESTCASES += check_orx.tst
TESTCASES += check_subx.tst
TESTCASES += check_xorx.tst
TESTCASES += check_beqx.tst
TESTCASES += check_bnex.tst
TESTCASES += check_ldstx.tst

all: $(TESTCASES)

%.o: $(SRC_PATH)/tests/tcg/arc/%.S
	$(CC) $(ASFLAGS) -c $< -o $@ -I$(TST_PATH)

%.tst: %.o $(SRC_PATH)/tests/tcg/arc/macros.inc
	$(LD) -T $(TST_PATH)/tarc.ld $< -o $@

check: $(TESTCASES)
	@for case in $(TESTCASES); do \
	echo $(SIM) $(SIM_FLAGS) ./$$case;\
	$(SIM) $(SIM_FLAGS) ./$$case; \
	done

clean:
	$(RM) -rf $(TESTCASES)
