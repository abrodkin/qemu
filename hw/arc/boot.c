/*
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, see <http://www.gnu.org/licenses/>.
 */

#include "qemu/osdep.h"
#include "boot.h"
#include "elf.h"
#include "hw/loader.h"
#include "sysemu/qtest.h"

void arc_load_kernel(ARCCPU *cpu, ram_addr_t ddr_base, ram_addr_t ram_size,
                     const char *kernel_filename)
{
    uint64_t elf_entry;
    long kernel_size;
    hwaddr entry;

    if (kernel_filename && !qtest_enabled()) {
        kernel_size = load_elf(kernel_filename, NULL, NULL, NULL,
                               &elf_entry, NULL, NULL, 0, cpu->env.family > 2 ?
                               EM_ARC_COMPACT2 : EM_ARC_COMPACT,
                               1, 0);
        entry = elf_entry;
        if (kernel_size < 0) {
            kernel_size = load_uimage(kernel_filename,
                                      &entry, NULL, NULL, NULL, NULL);
        }
        if (kernel_size < 0) {
            kernel_size = load_image_targphys(kernel_filename, ddr_base,
                                              ram_size);
            entry = ddr_base;
        }

        if (kernel_size < 0) {
            fprintf(stderr, "QEMU: couldn't load the kernel '%s'\n",
                    kernel_filename);
            exit(1);
        }
        cpu->env.pc = entry;
    }
}
