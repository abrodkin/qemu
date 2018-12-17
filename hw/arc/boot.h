#ifndef ARC_BOOT_H
#define ARC_BOOT_H

#include "hw/hw.h"
#include "cpu.h"

void arc_load_kernel(ARCCPU *cpu, ram_addr_t ddr_base, ram_addr_t ram_size,
                     const char *kernel_filename);

#endif /* ARC_BOOT_H */
