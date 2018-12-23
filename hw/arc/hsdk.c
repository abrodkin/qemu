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
#include "hw/arc/cpudevs.h"
#include "hw/sysbus.h"

#define HSDK_RAM_BASE		0x80000000
#define HSDK_RAM_SIZE		0x80000000
#define HSDK_IO_BASE		0xf0000000
#define HSDK_IO_SIZE		0x10000000
#define HSDK_UART0_OFFSET	0x5000

static void main_cpu_reset(void *opaque)
{
    ARCCPU *cpu = opaque;

    cpu_reset(CPU(cpu));
}

static void hsdk_init(MachineState *machine)
{
    const char *kernel_filename = machine->kernel_filename;
    MemoryRegion *system_memory = get_system_memory();
    MemoryRegion *system_ram;
    MemoryRegion *system_io;
    ARCCPU *cpu = NULL;
    int n;

    if (strncmp(machine->cpu_model, "archs", 8)) {
        fprintf(stderr, "Expected archs got %s!\n", machine->cpu_model);
        exit(1);
    }

    for (n = 0; n < smp_cpus; n++) {
        cpu = ARC_CPU (cpu_generic_init (TYPE_ARC_CPU, machine->cpu_model));
        if (cpu == NULL) {
            fprintf(stderr, "Unable to find CPU definition!\n");
            exit(1);
        }

       /* Initialize internal devices.  */
        cpu_arc_pic_init (cpu);
        cpu_arc_clock_init (cpu);

        qemu_register_reset(main_cpu_reset, cpu);
        main_cpu_reset(cpu);
    }

    /* Init system DDR */
    system_ram = g_new(MemoryRegion, 1);
    memory_region_init_ram(system_ram, NULL, "arc.ram", HSDK_RAM_SIZE,
                           &error_fatal);
    memory_region_add_subregion(system_memory, HSDK_RAM_BASE, system_ram);

    /* Init IO area */
    system_io = g_new(MemoryRegion, 1);
    memory_region_init_io(system_io, NULL, NULL, NULL, "arc.io", HSDK_IO_SIZE);
    memory_region_add_subregion(system_memory, HSDK_IO_BASE, system_io);

    serial_mm_init(system_io, HSDK_UART0_OFFSET, 2, cpu->env.irq[46],
                   115200, serial_hds[0], DEVICE_NATIVE_ENDIAN);

    arc_load_kernel(cpu, HSDK_RAM_BASE, HSDK_RAM_SIZE, kernel_filename);
}

static void hsdk_machine_init(MachineClass *mc)
{
    mc->desc = "ARC HSDK";
    mc->init = hsdk_init;
    mc->max_cpus = 1;
    mc->is_default = 1;
}

DEFINE_MACHINE("hsdk", hsdk_machine_init)
