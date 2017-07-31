-include ../../../config-host.mak

CROSS = arc-elf32-

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

TESTCASES = check_add.stst
#TESTCASES += check_add.stst

all: $(TESTCASES)

#%.o: $(SRC_PATH)/tests/tcg/arc/%.c
#	$(CC) $(CFLAGS) $< -o $@
#
#%.tst: $(SRC_PATH)/tests/tcg/arc/%.c
#	$(CC) $(CFLAGS) $< -o $@

%.o: $(SRC_PATH)/tests/tcg/arc/%.S
	$(CC) $(ASFLAGS) -c $< -o $@ -I$(TST_PATH)

%.stst: %.o $(SRC_PATH)/tests/tcg/arc/macros.inc
	$(LD) -T $(TST_PATH)/tarc.ld $< -o $@

check: $(TESTCASES)
	@for case in $(TESTCASES); do \
	echo $(SIM) $(SIM_FLAGS) ./$$case;\
	$(SIM) $(SIM_FLAGS) ./$$case; \
	done

clean:
	$(RM) -rf $(TESTCASES)
