/* ARC BCR Auxiliary register definitions
   Copyright (C) 2015-2017 Free Software Foundation, Inc.

   Contributed by Cupertino Miranda (cmiranda@synopsys.com)

   This file is part of libopcodes.
   This library is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3, or (at your option)
   any later version.

   It is distributed in the hope that it will be useful, but WITHOUT
   ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
   or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public
   License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software Foundation,
   Inc., 51 Franklin Street - Fifth Floor, Boston, MA 02110-1301, USA.  */

#include "bcr.h"
#include "cpu.h"

uint32_t (*default_get_bcr) (uint32_t value) = NULL;

uint32_t
read_bcr_value (struct CPUARCState *env, uint32_t aux)
{
  if(default_get_bcr != NULL)
    return default_get_bcr(aux);
  else
    return 0;
}
