/*
 * QEMU ARC CPU - IRQ subsystem
 *
 * Copyright (c) 2019
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
#include "cpu.h"
#include "qemu/main-loop.h"
#include "irq.h"
#include "exec/cpu_ldst.h"

/* Static functions and variables. */

static uint32_t save_reg_pair_32[] =
  { 0, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30};

static uint32_t save_reg_pair_16[] =
  { 0, 2, 10, 12, 14, 26, 28, 30};

static uint32_t pack_status32 (status_t *status_r)
{
  uint32_t res = 0x00000000;

  res |= (status_r->IEf & 0x1) << 31;
  res |= (status_r->USf & 0x1) << 20;
  res |= (status_r->ADf & 0x1) << 19;
  res |= (status_r->RBf & 0x7) << 16;
  res |= (status_r->ESf & 0x1) << 15;
  res |= (status_r->SCf & 0x1) << 14;
  res |= (status_r->DZf & 0x1) << 13;
  res |= (status_r->Lf  & 0x1) << 12;
  res |= (status_r->Zf  & 0x1) << 11;
  res |= (status_r->Nf  & 0x1) << 10;
  res |= (status_r->Cf  & 0x1) << 9;
  res |= (status_r->Vf  & 0x1) << 8;
  res |= (status_r->Uf  & 0x1) << 7;
  res |= (status_r->DEf & 0x1) << 6;
  res |= (status_r->AEf & 0x1) << 5;
  res |= (status_r->Ef  & 0xf) << 1;

  return res;
}

static void unpack_status32(CPUARCState *env, uint32_t value)
{
  env->stat.IEf = ((value >> 31) & 0x1);
  env->stat.USf = ((value >> 20) & 0x1);
  env->stat.ADf = ((value >> 19) & 0x1);
  env->stat.RBf = ((value >> 16) & 0x7);
  env->stat.ESf = ((value >> 15) & 0x1);
  env->stat.SCf = ((value >> 14) & 0x1);
  env->stat.DZf = ((value >> 13) & 0x1);
  env->stat.Lf  = ((value >> 12) & 0x1);
  env->stat.Zf  = ((value >> 11) & 0x1);
  env->stat.Nf  = ((value >> 10) & 0x1);
  env->stat.Cf  = ((value >> 9)  & 0x1);
  env->stat.Vf  = ((value >> 8)  & 0x1);
  env->stat.Uf  = ((value >> 7)  & 0x1);
  env->stat.DEf = ((value >> 6)  & 0x1);
  env->stat.AEf = ((value >> 5)  & 0x1);
  env->stat.Ef  = ((value >> 1)  & 0xf);
  //env->stat.Hf  = ((value >> 0)  & 0x1);
}

/* Return from fast interrupts.  */

static void arc_rtie_firq (CPUARCState *env)
{
  assert (env->stat.AEf == 0);

  qemu_log_mask (CPU_LOG_INT, "[IRQ] exit firq: U=%d, AUX_IRQ_ACT.U=%d\n",
		 env->stat.Uf, env->aux_irq_act >> 31);

  /* Clear currently active interrupt.  */
  env->aux_irq_act &= 0xfffffffe;

  /* First, check if we need to restore userland SP. */
  if (((env->aux_irq_act & 0xFFFF) == 0) && (env->aux_irq_act & 0x80000000))
    {
      uint32_t tmp;
      qemu_log_mask (CPU_LOG_INT,
		     "[IRQ] swap: r28 <= 0x%08x  AUX_USER_SP <= 0x%08x\n",
		     env->aux_user_sp, CPU_SP (env));

      tmp = env->aux_user_sp;
      env->aux_user_sp = CPU_SP (env);
      CPU_SP (env) = tmp;
      /* TODO: maybe we need to flush the tcg buffer to switch into
	 kernel mode.  */
    }

  env->stat = env->stat_l1; /* FIXME use status32_p0 reg.  */
  env->aux_irq_act &= ~(env->stat.Uf << 31); /* Keep U-bit in sync.  */

  /* FIXME! fix current reg bank if RB bit is changed.  */

  CPU_PCL (env) = CPU_ILINK (env);
  env->pc = CPU_ILINK (env);
}

static uint32_t irq_pop (CPUARCState *env)
{
  uint32_t rval;
  rval = cpu_ldl_data (env, CPU_SP (env));

  qemu_log_mask (CPU_LOG_INT, "[IRQ] Pop [SP:0x%08x] => 0x%08x\n",
		 CPU_SP (env), rval);
  CPU_SP (env) += 4;
  return rval;
}

/* Return from regular interrupts.  */

static void arc_rtie_irq (CPUARCState *env)
{
  uint32_t tmp;

  assert ((env->aux_irq_act & 0xFFFF) != 0);
  assert (env->stat.AEf == 0);

  /* Clear currently active interrupt.  */
  tmp = __builtin_ctz (env->aux_irq_act & 0xffff);
  /* FIXME! I assume the current active interrupt is the one which is
     the highest in the aux_irq_act register.  */
  env->aux_irq_act &= ~(1 << tmp);

  qemu_log_mask (CPU_LOG_INT,
		 "[IRQ] exit irq:%d U:%d AE:%d IE:%d E:%d\n",
		 -1, env->stat.Uf, env->stat.AEf, env->stat.IEf,
		 env->stat.Ef);

  if (((env->aux_irq_act & 0xffff) == 0)
      && (env->aux_irq_act & 0x80000000) && (env->aux_irq_ctrl & (1 << 11)))
    {
      uint32_t tmp;
      qemu_log_mask (CPU_LOG_INT,
		     "[IRQ] swap: r28 <= 0x%08x  AUX_USER_SP <= 0x%08x\n",
		     env->aux_user_sp, CPU_SP (env));

      tmp = env->aux_user_sp;
      env->aux_user_sp = CPU_SP (env);
      CPU_SP (env) = tmp;
      /* TODO: maybe we need to flush the tcg buffer to switch into
	 kernel mode.  */
    }

  /* Pop requested number of registers.  */
  uint32_t *save_reg_pair = save_reg_pair_32; /* FIXME! select rf16 when needed.  */
  for (uint32_t i = 0; i < (env->aux_irq_ctrl & 0x1F); ++i)
    {
      env->r[save_reg_pair[i]] = irq_pop (env);
      env->r[save_reg_pair[i] + 1] = irq_pop (env);
    }

  /* Pop BLINK */
  if (env->aux_irq_ctrl & (1 << 9) && ((env->aux_irq_ctrl & 0x1F) != 16))
    CPU_BLINK (env) = irq_pop (env);

  /* Pop lp_end, lp_start, lp_count if aux_irq_ctrl.l bit is set.  */
  if (env->aux_irq_ctrl & (1 << 10))
    {
      env->lpe = irq_pop (env);
      env->lps = irq_pop (env);
      CPU_LP (env) = irq_pop (env);
    }

  /* Pop EI_BASE, JLI_BASE, LDI_BASE if LP bit is set and Code Density
     feature is enabled.  FIXME!*/
#if 0
  if (cpu->cfg.code_density && (env->aux_irq_ctrl & (1 << 13)))
    {
      /* env->aux_ei_base  = irq_pop (env); */
      /* env->aux_ldi_base = irq_pop (env); */
      /* env->aux_jli_base = irq_pop (env); */
    }
#endif

  CPU_ILINK (env) = irq_pop (env); /* CPU PC*/
  uint32_t tmp_stat = irq_pop (env); /* status. */

  /* Late switch to Kernel SP if previously in User thread.  */
  if (((env->aux_irq_act & 0xffff) == 0)
      && env->stat.Uf && !(env->aux_irq_ctrl & (1 << 11)))
    {
      uint32_t tmp;
      qemu_log_mask (CPU_LOG_INT,
		     "[IRQ] swap : r28 <= 0x%08x  AUX_USER_SP <= 0x%08x\n",
		     env->aux_user_sp, CPU_SP (env));

      tmp = env->aux_user_sp;
      env->aux_user_sp = CPU_SP (env);
      CPU_SP (env) = tmp;
      /* TODO: maybe we need to flush the tcg buffer to switch into
	 kernel mode.  */
    }

  unpack_status32 (env, tmp_stat);
  env->aux_irq_act &= ~(env->stat.Uf << 31); /* Keep U-bit in sync.  */
  CPU_PCL (env) = CPU_ILINK (env);
  env->pc = CPU_ILINK (env);
}

static void arc_enter_firq (ARCCPU *cpu, uint32_t vector)
{
  CPUARCState *env = &cpu->env;

  /* Reset RTC state machine -> AUX_RTC_CTRL &= 0x3fffffff */
  qemu_log_mask (CPU_LOG_INT,
		 "[IRQ] enter firq:%d U:%d AE:%d IE:%d E:%d\n",
		 vector, env->stat.Uf, env->stat.AEf, env->stat.IEf,
		 env->stat.Ef);

  /* Switch SP with AUX_SP.  */
  if (env->stat.Uf)
    {
      uint32_t tmp;
      qemu_log_mask (CPU_LOG_INT,
		     "[IRQ] swap: r28 <= 0x%08x  AUX_USER_SP <= 0x%08x\n",
		     env->aux_user_sp, CPU_SP (env));

      tmp = env->aux_user_sp;
      env->aux_user_sp = CPU_SP (env);
      CPU_SP (env) = tmp;
      /* TODO: maybe we need to flush the tcg buffer to switch into
	 kernel mode.  */
    }

  /* Clobber ILINK with address of interrupting instruction.  */
  CPU_ILINK (env) = env->pc & 0xfffffffe;
  env->stat_l1 = env->stat;

  /* Set stat {Z = U; U = 0; L = 1; ES = 0; DZ = 0; DE = 0;} */
  env->stat.Lf = 1;
  env->stat.Zf = env->stat.Uf; /* Old User/Kernel bit.  */
  env->stat.Uf = 0; /* FIXME! Switch to kernel mode.  */
  env->stat.ESf = 0;
  env->stat.DZf = 0;
  env->stat.DEf = 0;

  /* Set .RB to 1 if additional register banks are specified.  */
  if (cpu->cfg.rgf_num_banks > 0)
    {
      env->stat.RBf = 1;
      /* FIXME! Switch to first register bank. */
    }
}

static void irq_push (CPUARCState *env, uint32_t regval)
{
  CPU_SP (env) -= 4;
  qemu_log_mask (CPU_LOG_INT, "[IRQ] Push [SP:0x%08x] <= 0x%08x\n",
		 CPU_SP (env), regval);
  cpu_stl_data (env, CPU_SP (env), regval);
}

static void arc_enter_irq (ARCCPU *cpu, uint32_t vector)
{
  CPUARCState *env = &cpu->env;

  /* Reset RTC state machine -> AUX_RTC_CTRL &= 0x3fffffff */
  qemu_log_mask (CPU_LOG_INT, "[IRQ] enter irq:%d U:%d AE:%d IE:%d E:%d\n",
		 vector, env->stat.Uf, env->stat.AEf, env->stat.IEf,
		 env->stat.Ef);

  /* Early switch to kernel sp if previously in user thread */
  if (env->stat.Uf && !(env->aux_irq_ctrl & (1 << 11)))
    {
      uint32_t tmp;
      qemu_log_mask (CPU_LOG_INT,
		     "[IRQ] swap : r28 <= 0x%08x  AUX_USER_SP <= 0x%08x\n",
		     env->aux_user_sp, CPU_SP (env));

      tmp = env->aux_user_sp;
      env->aux_user_sp = CPU_SP (env);
      CPU_SP (env) = tmp;
      /* TODO: maybe we need to flush the tcg buffer to switch into
	 kernel mode.  */
    }

  /* Clobber ILINK with address of interrupting instruction.  */
  CPU_ILINK (env) = env->pc & 0xfffffffe;

  /* Start pushing regs and stat.  */
  irq_push (env, pack_status32 (&env->stat));
  irq_push (env, env->pc);


  /* Push EI_BASE, JLI_BASE, LDI_BASE if LP bit is set and Code Density
     feature is enabled */
  if (cpu->cfg.code_density && (env->aux_irq_ctrl & (1 << 13)))
    {
      /* FIXME! irq_push (env, env->aux_jli_base); */
      /* FIXME! irq_push (env, env->aux_ldi_base); */
      /* FIXME! irq_push (env, env->aux_ei_base); */
    }

  /* Push LP_COUNT, LP_START, LP_END registers if required.  */
  if (env->aux_irq_ctrl & (1 << 10))
    {
      irq_push (env, CPU_LP (env));
      irq_push (env, env->lps);
      irq_push (env, env->lpe);
    }

  /* Push BLINK register if required */
  if (env->aux_irq_ctrl & (1 << 9) && ((env->aux_irq_ctrl & 0x1F) != 16))
    irq_push (env, CPU_BLINK (env));

  /* Push selected AUX_IRQ_CTRL.NR of registers onto stack.  */
  uint32_t *save_reg_pair = cpu->cfg.rgf_num_regs == 32 ?
    save_reg_pair_32 : save_reg_pair_16;
  for (uint32_t i = (env->aux_irq_ctrl & 0x1F); i > 0; --i)
    {
      irq_push (env, env->r[save_reg_pair[i-1] + 1]);
      irq_push (env, env->r[save_reg_pair[i-1]]);
    }

  /* Late switch to Kernel SP if previously in User thread.  */
  if (env->stat.Uf && (env->aux_irq_ctrl & (1 << 11)))
    {
      uint32_t tmp;
      qemu_log_mask (CPU_LOG_INT,
		     "[IRQ] swap : r28 <= 0x%08x  AUX_USER_SP <= 0x%08x\n",
		     env->aux_user_sp, CPU_SP (env));

      tmp = env->aux_user_sp;
      env->aux_user_sp = CPU_SP (env);
      CPU_SP (env) = tmp;
      /* TODO: maybe we need to flush the tcg buffer to switch into
	 kernel mode.  */
    }

  /* Set STATUS bits */
  env->stat.Zf = env->stat.Uf; /* Old User/Kernel mode.	 */
  env->stat.Lf = 1;
  env->stat.ESf = 0;
  env->stat.DZf = 0;
  env->stat.DEf	 = 0;
  env->stat.Uf = 0; /* FIXME! switch to kernel mode.  */
}

/* Function implementation for reading/writing aux regs.  */
uint32_t
aux_irq_get (struct arc_aux_reg_detail *aux_reg, void *data)
{
  CPUARCState *env = (CPUARCState *) data;
  uint32_t tmp;

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

    case AUX_ID_aux_irq_act:
      return env->aux_irq_act;

    case AUX_ID_aux_irq_ctrl:
      return env->aux_irq_ctrl;

    case AUX_ID_icause:
      if ((env->aux_irq_act & 0xffff) == 0)
	return 0;
      tmp = __builtin_ctz (env->aux_irq_act & 0xffff);
      return env->icause[tmp];

    default:
      break;
    }
  return 0;
}

void
aux_irq_set (struct arc_aux_reg_detail *aux_reg, uint32_t val, void *data)
{
  CPUARCState *env = (CPUARCState *) data;
  const uint32_t irq = env->irq_select;
  arc_irq_t *irq_bank = &env->irq_bank[irq];

  switch (aux_reg->id)
    {
    case AUX_ID_irq_select:
      env->irq_select = val; /* FIXME! check against the IRQ configured range.	*/
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
      env->aux_irq_ctrl = val & 0x2e1f;
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

/* Check if we can interrupt the cpu.  */

bool arc_cpu_exec_interrupt (CPUState *cs, int interrupt_request)
{
  ARCCPU *cpu = ARC_CPU (cs);
  CPUARCState *env = &cpu->env;
  bool found = false;
  uint32_t vectno = 0;
  uint32_t offset, priority;

  /* TODO: Check if we are in a delay slot.  We may need to avoid
     executing interrupts when in delay slots.	*/

  /* Check if we should execute this interrupt.	 */
  if ((env->stat.Hf != 0)
      /* The interrupts are enabled.  */
      || (env->stat.IEf != 1)
      /* We are not in an exception.  */
      || (env->stat.AEf != 0)
      || (!(interrupt_request & CPU_INTERRUPT_HARD)))
    return false;

  /* Check if any interrupts are pending. */
  if (!env->irq_priority_pending)
    return false;

  /* Find the first IRQ to serve.  */
  priority = 0;
  do
    {
      if ((env->timer[0].T_Cntrl & TMR_IP)
	  && (((env->timer_build & TB_P0_MSK) >> 16) == priority))
	{
	  vectno = 0;
	  found = true;
	}
      else if ((env->timer[1].T_Cntrl & TMR_IP)
	       && (((env->timer_build & TB_P1_MSK) >> 20) == priority))
	{
	  vectno = 1;
	  found	 = true;
	}
      else
	{
	  for (vectno = 0;
	       vectno < cpu->cfg.number_of_interrupts; vectno++)
	    if (env->irq_bank[16 + vectno].priority == priority
		&& env->irq_bank[16 + vectno].pending)
	      {
		found = true;
		break;
	      }
	}
    }
  while (!found && ((++priority) < cpu->cfg.number_of_levels));

  /* No valid interrupt has been found. */
  if (!found)
    return false;

  qemu_log_mask (CPU_LOG_INT, "[IRQ] interrupt at pc=0x%08x\n", env->pc);

  /* Adjust vector number.  */
  vectno += 16;

  /* Set the AUX_IRQ_ACT.  */
  if ((env->aux_irq_act & 0xffff) == 0)
    env->aux_irq_act |= env->stat.Uf << 31;
  env->aux_irq_act |= 1 << priority;

  /* Set ICAUSE register.  */
  env->icause[priority] = vectno;

  /* Cleanup pending bit.  */
  env->irq_priority_pending &= ~(1 << priority);

  /* Do FIRQ if possible.  */
  if (cpu->cfg.firq_option && priority == 0)
    arc_enter_firq (cpu, vectno);
  else
    arc_enter_irq (cpu, vectno);

  /* XX. The PC is set with the appropriate exception vector. */
  offset = vectno << 2;
  env->pc = cpu_ldl_code (env, env->intvec + offset);
  CPU_PCL (env) = env->pc & 0xfffffffe;

  qemu_log_mask(CPU_LOG_INT, "[IRQ] isr=0x%08x vec=0x%08x, priority=0x%04x\n",
		env->pc, offset, priority);

  return true;
}

/* To be called in the RTIE helper.  */

bool arc_rtie_interrupts (CPUARCState *env)
{
  if (env->stat.AEf || ((env->aux_irq_act & 0xffff) == 0))
    return false;

  /* FIXME! Reset RTC state.  */

  if ((env->aux_irq_act & 0xffff) == 1 /* && cpu->cfg.firq_option*/ )
    arc_rtie_firq (env);
  else
    arc_rtie_irq (env);
  return true;
}
