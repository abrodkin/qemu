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
#include "aux-reg.h"

#define AUX_REG(NAME, NUMBER, RESET_VALUE) NUMBER,
const int aux_reg_number[AUX_REG_SIZE] = {
#include "aux-reg.def"
};
#undef AUX_REG

#define AUX_REG(NAME, NUMBER, RESET_VALUE) RESET_VALUE,
const int aux_reg_reset_value[AUX_REG_SIZE] = {
#include "aux-reg.def"
};
#undef AUX_REG

#define AUX_REG(NAME, NUMBER, RESET_VALUE) #NAME,
const char *aux_reg_name[AUX_REG_SIZE] = {
#include "aux-reg.def"
};

#undef AUX_REG
