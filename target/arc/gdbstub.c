
/*
 * QEMU ARC CPU
 *
 * Copyright (c) 2016 Michael Rolnik
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, see
 * <<a  rel="nofollow" href="http://www.gnu.org/licenses/lgpl-2.1.html">http://www.gnu.org/licenses/lgpl-2.1.html</a>>
 */

#include "qemu/osdep.h"
#include "qemu-common.h"
#include "exec/gdbstub.h"
#include "internals.h"
#include "irq.h"


int arc_cpu_gdb_read_register(CPUState *cs, uint8_t *mem_buf, int n)
{
  ARCCPU *cpu = ARC_CPU(cs);
  CPUARCState *env = &cpu->env;
  uint32_t regval = 0;

  switch (n)
  {
    case 0 ... 31:
      regval = env->r[n];
      break;
    case GDB_REG_58:
      regval = env->r[58];
      break;
    case GDB_REG_59:
      regval = env->r[59];
      break;
    case GDB_REG_60:
      regval = env->r[60];
      break;
    case GDB_REG_63:
      regval = env->r[63];
      break;
    default:
      assert(!"Unsupported register is being read.");
  }

  return gdb_get_reg32(mem_buf, regval);
}


int arc_cpu_gdb_write_register(CPUState *cs, uint8_t *mem_buf, int n)
{
  ARCCPU *cpu = ARC_CPU(cs);
  CPUARCState *env = &cpu->env;
  uint32_t regval = ldl_p(mem_buf);

  switch (n)
  {
    case 0 ... 31:
      env->r[n] = regval;
      break;
    case GDB_REG_58:
      env->r[58] = regval;
      break;
    case GDB_REG_59:
      env->r[59] = regval;
      break;
    case GDB_REG_60:
      env->r[60] = regval;
      break;
    case GDB_REG_63:
      env->r[63] = regval;
      break;
    default:
      assert(!"Unsupported register is being written.");
  }

  return 4;
}


static int
arc_aux_minimal_gdb_get_reg(CPUARCState *env, uint8_t *mem_buf, int regnum)
{
  uint32_t regval = 0;
  switch (regnum)
  {
    case GDB_AUX_REG_PC:
      regval = env->pc;
      break;
    case GDB_AUX_REG_LPS:
      regval = env->lps;
      break;
    case GDB_AUX_REG_LPE:
      regval = env->lpe;
      break;
    case GDB_AUX_REG_STATUS:
      regval = pack_status32(&env->stat);
      break;
    default:
      assert(!"Unsupported auxiliary register is being read.");
  }
  return gdb_get_reg32(mem_buf, regval);
}


static int
arc_aux_minimal_gdb_set_reg(CPUARCState *env, uint8_t *mem_buf, int regnum)
{
  uint16_t regval = ldl_p(mem_buf);
  switch (regnum)
  {
    case GDB_AUX_REG_PC:
      env->pc = regval;
      break;
    case GDB_AUX_REG_LPS:
      env->lps = regval;
      break;
    case GDB_AUX_REG_LPE:
      env->lpe = regval;
      break;
    case GDB_AUX_REG_STATUS:
      unpack_status32(&env->stat, regval);
      break;
    default:
      assert(!"Unsupported auxiliary register is being written.");
  }
  return 4;
}


void arc_cpu_register_gdb_regs_for_features(ARCCPU *cpu)
{
    CPUState *cs = CPU(cpu);

    gdb_register_coprocessor(cs,
                             arc_aux_minimal_gdb_get_reg,    /* getter */
                             arc_aux_minimal_gdb_set_reg,    /* setter */
                             GDB_AUX_REG_LAST,               /* number of registers */
                             "arc-aux-minimal.xml",          /* feature file */
                             0);                             /* position in g packet */
}
