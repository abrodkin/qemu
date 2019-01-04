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

#include "qemu/osdep.h"
#include "qemu/log.h"
#include "qemu/error-report.h"
#include "arc-regs.h"
#include "mmu.h"
#include "cpu.h"
#include "qemu/main-loop.h"

/* Static function implementation for reading/writing aux regs.  */
static uint32_t
aux_irq_get (struct arc_aux_reg_detail *aux_reg, void *data)
{
  CPUARCState *env = (CPUARCState *) data;

  /* extract selected IRQ.  */
  const uint32_t irq = env->irq_select;
  const arc_irq_t *irq_bank = &env->irq_bank[irq];

  switch (aux_reg->id)
    {
    case AUX_ID_irq_pending:
      return irq_bank->pending | (env->aux_irq_hint == irq);

    case AUX_ID_irq_select:
      return env->irq_select;

    case AUX_ID_irq_priority:
      return irq_bank->priority;

    case AUX_ID_irq_trigger:
      return irq_bank->trigger;

    case AUX_ID_irq_status:
      return (irq_bank->priority
              | irq_bank->enable << 4
              | irq_bank->trigger << 5
              | (irq_bank->pending | (env->aux_irq_hint == irq)) << 31);

    default:
      break;
    }
  return 0;
}

static void
aux_irq_set (struct arc_aux_reg_detail *aux_reg, uint32_t val, void *data)
{
  CPUARCState *env = (CPUARCState *) data;
  const uint32_t irq = env->irq_select;
  arc_irq_t *irq_bank = &env->irq_bank[irq];

  switch (aux_reg->id)
    {
    case AUX_ID_irq_select:
      env->irq_select = val; /* FIXME! check against the IRQ configured range.  */
      break;

    case AUX_ID_aux_irq_hint:
      /* FIXME! we should clear/trigger an interrupt here.  */
      qemu_mutex_lock_iothread ();
      if (val == 0)
        qemu_irq_lower (env->irq[env->aux_irq_hint]);
      else
        qemu_irq_raise (env->irq[val]);
      env->aux_irq_hint = val;
      qemu_mutex_unlock_iothread ();
      break;

    case AUX_ID_irq_pulse_cancel:
      irq_bank->pending = irq_bank->trigger ? (val & 0x01) : 0;
      break;

    case AUX_ID_irq_trigger:
      irq_bank->trigger = val & 0x01;
      break;

    case AUX_ID_irq_priority:
      irq_bank->priority = val; /* FIXME! check the irq priority ranges.  */
      break;

    case AUX_ID_aux_irq_ctrl:
      /* FIXME! implement me.  */
      break;

    case AUX_ID_irq_enable:
      irq_bank->enable = val & 0x01;
      break;

    case AUX_ID_aux_irq_act:
      env->aux_irq_act = val & 0xffff;
      break;

    default:
      break;
    }
}

struct arc_aux_reg_detail arc_aux_regs_detail[ARC_AUX_REGS_DETAIL_LAST] = {
#define DEF(NUM, CPU, SUB, NAME) \
  { \
    NUM, \
    CPU, \
    SUB, \
    AUX_ID_##NAME, \
    #NAME, \
    sizeof (#NAME) - 1, \
    NULL, \
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

void arc_aux_regs_init(void)
{
  int i;

  for(i = 0; i < ARC_AUX_REGS_DETAIL_LAST; i++)
  {
    enum arc_aux_reg_enum id = arc_aux_regs_detail[i].id;
    struct arc_aux_reg_detail *next = arc_aux_regs[id].first;
    arc_aux_regs_detail[i].next = next;
    arc_aux_regs_detail[i].aux_reg = &(arc_aux_regs[id]);
    arc_aux_regs[id].first = &(arc_aux_regs_detail[i]);
  }
}

int
arc_aux_reg_address_for(enum arc_aux_reg_enum aux_reg_def,
			int isa_mask)
{
  // TODO: This must validate for CPU.
  struct arc_aux_reg_detail *detail = arc_aux_regs[aux_reg_def].first;
  while(detail != NULL) {
    if((detail->cpu & isa_mask) != 0)
      return detail->address;
    detail = detail->next;
  }
  assert(0);
}

struct arc_aux_reg_detail *
arc_aux_reg_struct_for_address(int address, int isa_mask)
{
  int i;
  bool has_default = false;
  struct arc_aux_reg_detail *default_ret;

  /* TODO: Make this a binary search or something faster. */
  for(i = 0; i < ARC_AUX_REGS_DETAIL_LAST; i++) {
    if(arc_aux_regs_detail[i].address == address)
      {
	if (arc_aux_regs_detail[i].cpu == ARC_OPCODE_DEFAULT)
	  {
	    has_default = true;
	    default_ret = &(arc_aux_regs_detail[i]);
	  }
	else if ((arc_aux_regs_detail[i].cpu & isa_mask) != 0)
	  {
	    return &(arc_aux_regs_detail[i]);
	  }
      }
  }

  if(has_default == true)
    return default_ret;

  return NULL;
}

uint32_t
arc_regs_bcr_detault_impl (struct arc_aux_reg_detail *aux_reg, void *data)
{
  return 0;
}

/* TODO: Implement any non implemented auxs regs. */
void TO_IMPLEMENT_SET(struct arc_aux_reg_detail *aux_reg, uint32_t val, void *data)
{
  return;
}
uint32_t TO_IMPLEMENT_GET(struct arc_aux_reg_detail *aux_reg, void *data)
{
  return 0;
}
