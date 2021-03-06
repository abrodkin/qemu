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
#include "boot.h"
#include "hw/boards.h"
#include "hw/char/serial.h"
#include "exec/address-spaces.h"
#include "sysemu/reset.h"
#include "sysemu/sysemu.h"
#include "hw/arc/cpudevs.h"
#include "hw/sysbus.h"

#define SIMHS_RAM_BASE      0x80000000
#define SIMHS_RAM_SIZE      0x80000000
#define SIMHS_IO_BASE       0xf0000000
#define SIMHS_IO_SIZE       0x10000000
#define SIMHS_UART0_OFFSET  0x0
#define SIMHS_UART0_IRQ     24

/* VirtIO */
#define SIMHS_VIRTIO_NUMBER 5
#define SIMHS_VIRTIO_OFFSET 0x100000
#define SIMHS_VIRTIO_BASE   (SIMHS_IO_BASE + SIMHS_VIRTIO_OFFSET)
#define SIMHS_VIRTIO_SIZE   0x2000
#define SIMHS_VIRTIO_IRQ    31

static void simhs_init(MachineState *machine)
{
    static struct arc_boot_info boot_info;
    unsigned int smp_cpus = machine->smp.cpus;
    MemoryRegion *system_memory = get_system_memory();
    MemoryRegion *system_ram;
    MemoryRegion *system_io;
    ARCCPU *cpu = NULL;
    int n;

    boot_info.ram_start = SIMHS_RAM_BASE;
    boot_info.ram_size = SIMHS_RAM_SIZE;
    boot_info.kernel_filename = machine->kernel_filename;
    boot_info.kernel_cmdline = machine->kernel_cmdline;

    for (n = 0; n < smp_cpus; n++) {
        cpu = ARC_CPU(cpu_create("archs-" TYPE_ARC_CPU));
        if (cpu == NULL) {
            fprintf(stderr, "Unable to find CPU definition!\n");
            exit(1);
        }

       /* Initialize internal devices. */
        cpu_arc_pic_init(cpu);
        cpu_arc_clock_init(cpu);

        qemu_register_reset(arc_cpu_reset, cpu);
    }

    /* Init system DDR */
    system_ram = g_new(MemoryRegion, 1);
    memory_region_init_ram(system_ram, NULL, "arc.ram", SIMHS_RAM_SIZE,
                           &error_fatal);
    memory_region_add_subregion(system_memory, SIMHS_RAM_BASE, system_ram);

    /* Init IO area */
    system_io = g_new(MemoryRegion, 1);
    memory_region_init_io(system_io, NULL, NULL, NULL, "arc.io",
                          SIMHS_IO_SIZE);
    memory_region_add_subregion(system_memory, SIMHS_IO_BASE, system_io);

    serial_mm_init(system_io, SIMHS_UART0_OFFSET, 2,
                   cpu->env.irq[SIMHS_UART0_IRQ], 115200, serial_hd(0),
                   DEVICE_NATIVE_ENDIAN);

    for (n=0; n < SIMHS_VIRTIO_NUMBER; n++) {
        sysbus_create_simple("virtio-mmio",
                             SIMHS_VIRTIO_BASE + SIMHS_VIRTIO_SIZE * n,
                             cpu->env.irq[SIMHS_VIRTIO_IRQ + n]);
    }

    arc_load_kernel(cpu, &boot_info);
}

static void simhs_machine_init(MachineClass *mc)
{
    mc->desc = "ARC HS Simulator";
    mc->init = simhs_init;
    mc->max_cpus = 1;
    mc->is_default = 1;
}

DEFINE_MACHINE("simhs", simhs_machine_init)


/*-*-indent-tabs-mode:nil;tab-width:4;indent-line-function:'insert-tab'-*-*/
/* vim: set ts=4 sw=4 et: */
