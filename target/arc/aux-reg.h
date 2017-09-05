/*
 *  QEMU ARC CPU
 *
 *  Copyright (c) 2017 Cupertino Miranda
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, see
 *  <http://www.gnu.org/licenses/lgpl-2.1.html>
 */
#ifndef ARC_AUX_REG_H
#define ARC_AUX_REG_H

#define AUX_REG(NAME, NUMBER, RESET_VALUE) NAME,
enum arc_aux_regs {
  AUX_REG_INVALID = -1,
#include "aux-reg.def"
  AUX_REG_SIZE
};
#undef AUX_REG

extern const int aux_reg_number[AUX_REG_SIZE];
extern const int aux_reg_reset_value[AUX_REG_SIZE];
extern const char *aux_reg_name[AUX_REG_SIZE];

#endif /* ARC_AUX_REG_H */
