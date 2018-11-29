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

#include "arc-regs.h"

const struct arc_aux_reg arc_aux_regs[ARC_AUX_REGS_LAST] = {
#define DEF(NUM, CPU, SUB, NAME, GET_FUNC, SET_FUNC) \
  { \
    NUM, \
    CPU, \
    SUB, \
    #NAME, \
    sizeof (#NAME) - 1, \
    GET_FUNC, \
    SET_FUNC \
  },
#include "arc-regs.def"
#undef DEF
};
