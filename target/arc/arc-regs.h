/*
 * QEMU ARC CPU
 *
 * Copyright (c) 2018 Cupertino Miranda
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
 * http://www.gnu.org/licenses/lgpl-2.1.html
 */

#ifndef ARC_REGS_H
#define ARC_REGS_H

#include "arc-decoder.h"

#ifndef ARC
enum arc_aux_regs_enum {
  ARC_AUX_REGS_INVALID = -1,
#define DEF(N,CPU,B,NAME,C,D) CPU##_##NAME,
#include "arc-regs.def"
#undef DEF
  ARC_AUX_REGS_LAST
};
#endif

struct arc_aux_regs_data;
typedef void (* aux_reg_set_func)(struct arc_aux_reg *aux_reg, uint32_t val, void *data);
typedef uint32_t (* aux_reg_get_func)(struct arc_aux_reg *aux_reg, void *data);
struct arc_aux_reg {

  /* Register address.  */
  int address;

  /* One bit flags for the opcode.  These are primarily used to
     indicate specific processors and environments support the
     instructions.  */
  enum arc_cpu_family cpu;

  /* AUX register subclass.  */
  insn_subclass_t subclass;

  /* Register name.  */
  const char *name;

  /* Size of the string.  */
  size_t length;

  /* get and set function for lr and sr helpers */
  aux_reg_get_func get_func;
  aux_reg_set_func set_func;
};

extern const struct arc_aux_reg arc_aux_regs[ARC_AUX_REGS_LAST];

#endif /* ARC_REGS_H */
