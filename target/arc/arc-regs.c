/*
 * QEMU ARC CPU
 *
 * Copyright (c) 2018 Cupertino Miranda
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License) any later version.
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


struct arc_aux_reg_detail arc_aux_regs_detail[ARC_AUX_REGS_DETAIL_LAST] = {
#define DEF(NUM, CPU, SUB, NAME) \
  { \
    NUM, \
    CPU, \
    SUB, \
    NAME, \
    #NAME, \
    sizeof (#NAME) - 1, \
    NULL, \
  },
#include "arc-regs-detail.def"
#undef DEF
};

struct arc_aux_reg arc_aux_regs[ARC_AUX_REGS_LAST] = {
#define AUX_REG(NAME, GET_FUNC, SET_FUNC) \
  { \
    NULL, \
    GET_FUNC, \
    SET_FUNC \
  },
#include "arc-regs.def"
#undef AUX_REG
};

static void arc_aux_regs_init(void)
{
  for(int i = 0; i < ARC_AUX_REGS_DETAIL_LAST; i++)
  {
    enum arc_aux_reg_enum id = arc_aux_regs_detail[i].id;
    struct arc_aux_regs_detail *next = arc_aux_regs[id].first;
    arc_aux_regs_detail[i].next = next;
    arc_aux_regs[id].first = &(arc_aux_regs_detail[i]);
  }
}

int
arc_aux_reg_address_for(enum arc_aux_reg_enum aux_reg_def)
{
  static bool prepared = false;
  if(prepared == false)
  {
    arc_aux_regs_init();
    prepared = true;
  }

  // TODO: This must validate for CPU.
  return arc_aux_regs[aux_reg_def].first->address;
  return -1;
}
