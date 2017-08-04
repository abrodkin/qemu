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
#include "qapi/error.h"
#include "qemu-common.h"
#include "cpu.h"
#include "hw/hw.h"
#include "hw/boards.h"
#include "elf.h"
#include "hw/char/serial.h"
#include "net/net.h"
#include "hw/loader.h"
#include "exec/memory.h"
#include "exec/address-spaces.h"
#include "sysemu/sysemu.h"
#include "hw/sysbus.h"
#include "sysemu/qtest.h"

#define KERNEL_LOAD_ADDR 0x100

static void main_cpu_reset(void *opaque)
{
    ARCCPU *cpu = opaque;

    cpu_reset(CPU(cpu));
}

static void arc_sim_net_init(MemoryRegion *address_space,
                             hwaddr base,
                             hwaddr descriptors,
                             qemu_irq irq, NICInfo *nd)
{
    DeviceState *dev;
    SysBusDevice *s;

    dev = qdev_create(NULL, "open_eth");
    qdev_set_nic_properties(dev, nd);
    qdev_init_nofail(dev);

    s = SYS_BUS_DEVICE(dev);
    sysbus_connect_irq(s, 0, irq);
    memory_region_add_subregion(address_space, base,
                                sysbus_mmio_get_region(s, 0));
    memory_region_add_subregion(address_space, descriptors,
                                sysbus_mmio_get_region(s, 1));
}

static void cpu_arc_load_kernel(ram_addr_t ram_size,
                                const char *kernel_filename,
                                ARCCPU *cpu)
{
    long kernel_size;
    uint64_t elf_entry;
    hwaddr entry;

    if (kernel_filename && !qtest_enabled()) {
        kernel_size = load_elf(kernel_filename, NULL, NULL,
                               &elf_entry, NULL, NULL, 0, cpu->env.family > 2 ?
                               EM_ARC_COMPACT2 : EM_ARC_COMPACT,
                               1, 0);
        entry = elf_entry;
        if (kernel_size < 0) {
            kernel_size = load_uimage(kernel_filename,
                                      &entry, NULL, NULL, NULL, NULL);
        }
        if (kernel_size < 0) {
            kernel_size = load_image_targphys(kernel_filename,
                                              KERNEL_LOAD_ADDR,
                                              ram_size - KERNEL_LOAD_ADDR);
            entry = KERNEL_LOAD_ADDR;
        }

        if (kernel_size < 0) {
            fprintf(stderr, "QEMU: couldn't load the kernel '%s'\n",
                    kernel_filename);
            exit(1);
        }
        cpu->env.pc = entry;
    }
}

static uint64_t arc_io_read(void *opaque, hwaddr addr,
        unsigned size)
{
    return 0;
}

static void arc_io_write(void *opaque, hwaddr addr,
        uint64_t val, unsigned size)
{
    switch (addr) {
    case 0x08: /* board reset.  */
        qemu_system_reset_request (SHUTDOWN_CAUSE_GUEST_RESET);
        break;
    default:
        break;
    }
}

static const MemoryRegionOps arc_io_ops = {
    .read = arc_io_read,
    .write = arc_io_write,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void arc_sim_init(MachineState *machine)
{
    ram_addr_t ram_size = machine->ram_size;
    const char *cpu_model = machine->cpu_model;
    const char *kernel_filename = machine->kernel_filename;
    ARCCPU *cpu = NULL;
    MemoryRegion *ram, *system_io;
    int n;

    if (!cpu_model) {
        cpu_model = "archs";
    }

    for (n = 0; n < smp_cpus; n++) {
        cpu = cpu_arc_init(cpu_model);
        if (cpu == NULL) {
            fprintf(stderr, "Unable to find CPU definition!\n");
            exit(1);
        }
        qemu_register_reset(main_cpu_reset, cpu);
        main_cpu_reset(cpu);
    }

    ram = g_malloc(sizeof(*ram));
    memory_region_init_ram(ram, NULL, "arc.ram", ram_size, &error_fatal);
    memory_region_add_subregion(get_system_memory(), 0, ram);

    system_io = g_malloc (sizeof (*system_io));
    memory_region_init_io (system_io, NULL, &arc_io_ops, NULL, "arc.io",
                           1024);
    memory_region_add_subregion (get_system_memory(), 0xf0000000, system_io);

    serial_mm_init(get_system_memory(), 0x90000000, 0, cpu->env.irq[2],
                   115200, serial_hds[0], DEVICE_NATIVE_ENDIAN);

    if (nd_table[0].used) {
        arc_sim_net_init(get_system_memory(), 0x92000000,
                              0x92000400, cpu->env.irq[4], nd_table);
    }

    cpu_arc_load_kernel(ram_size, kernel_filename, cpu);
}

static void arc_sim_machine_init(MachineClass *mc)
{
    mc->desc = "ARCxx simulation";
    mc->init = arc_sim_init;
    mc->max_cpus = 1;
    mc->is_default = 1;
}

DEFINE_MACHINE("arc-sim", arc_sim_machine_init)
