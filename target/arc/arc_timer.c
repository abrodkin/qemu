/*
 * QEMU ARC CPU-timer support
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include "qemu/osdep.h"
#include "qemu/timer.h"
#include "cpu.h"
#include "hw/arc/cpudevs.h"
#include "arc_timer.h"

#define TIMER_PERIOD(hz) (1000000000LL/(hz))
/* ARC timer update function.  */

static void cpu_arc_count_update (CPUARCState *env)
{
  uint64_t now;

  now = qemu_clock_get_ns(QEMU_CLOCK_VIRTUAL);

  if ((env->timer_build & TB_T0) && env->cpu_timer0)
    env->timer[0].T_Count += (uint32_t)((now - env->last_clk) /
					TIMER_PERIOD (env->freq_hz));
  if ((env->timer_build & TB_T1) && env->cpu_timer1)
    env->timer[1].T_Count += (uint32_t)((now - env->last_clk) /
					TIMER_PERIOD (env->freq_hz));

  env->last_clk = now;
  qemu_log_mask(LOG_UNIMP, "[TMRx] Timer count update\n");
}

/* Update the next timeout time as difference between Count and Limit */
static void cpu_arc_timer_update (CPUARCState *env, uint32_t timer)
{
  uint32_t wait;
  uint64_t now, next;

  now = qemu_clock_get_ns(QEMU_CLOCK_VIRTUAL);

  if (timer ? env->cpu_timer1 : env->cpu_timer0)
    {
      wait = env->timer[timer].T_Limit - env->timer[timer].T_Count;
      next = now + (uint64_t) wait * TIMER_PERIOD (env->freq_hz);
      timer_mod (timer ? env->cpu_timer1 : env->cpu_timer0, next);
      qemu_log_mask(LOG_UNIMP,
		    "[TMR%d] Timer update in 0x%08x - 0x%08x = 0x%08x\n",
		    timer, env->timer[timer].T_Limit,
		    env->timer[timer].T_Count, wait);
    }
  cpu_arc_count_update (env);
}

/* Expire the timer function.  Rise an interrupt if required.  */

static void cpu_arc_timer_expire (CPUARCState *env, uint32_t timer)
{
  qemu_log_mask(LOG_UNIMP, "[TMR%d] Timer expired\n", timer);

  /* Raise an interrupt if enabled.  */
  if ((env->timer[timer & 0x01].T_Cntrl & TMR_IE)
      && !(env->timer[timer & 0x01].T_Cntrl & TMR_IP))
    {
      qemu_log_mask(LOG_UNIMP, "[TMR%d] Rising IRQ\n", timer);
      qemu_irq_raise (env->irq[TIMER0_IRQ + (timer & 0x01)]);
    }

  /* Set the IP bit.  */
  env->timer[timer & 0x01].T_Cntrl |= TMR_IP;
}

/* This callback should occur when the counter is exactly equal to the
   limit value.	 Offset the count by one to avoid immediately
   retriggering the callback before any virtual time has passed.  */

static void arc_timer0_cb (void *opaque)
{
  CPUARCState *env = (CPUARCState *) opaque;

  if (!(env->timer_build & TB_T0))
    return;

  if (timer_expired(env->cpu_timer0, qemu_clock_get_ns (QEMU_CLOCK_VIRTUAL)))
    cpu_arc_timer_expire (env, 0);

  cpu_arc_timer_update (env, 0);
}

static void arc_timer1_cb (void *opaque)
{
  CPUARCState *env = (CPUARCState *) opaque;

  if (!(env->timer_build & TB_T1))
    return;

  if (timer_expired(env->cpu_timer1, qemu_clock_get_ns (QEMU_CLOCK_VIRTUAL)))
    cpu_arc_timer_expire (env, 1);

  cpu_arc_timer_update (env, 1);
}

static void cpu_arc_rtc_hl_update (CPUARCState *env)
{
  uint64_t now;
  union
  {
    uint64_t llreg;
    uint32_t reg[2];
  } rtc_regs;

  now = qemu_clock_get_ns(QEMU_CLOCK_VIRTUAL);

  if ((env->timer_build & TB_RTC) && env->cpu_rtc
      && (env->aux_irq_ctrl & 0x01))
    {
      rtc_regs.llreg = ((now - env->last_clk) / TIMER_PERIOD (env->freq_hz));
      env->aux_rtc_low += rtc_regs.reg[1];
      env->aux_rtc_high += rtc_regs.reg[0];
    }

  env->last_clk = now;
  qemu_log_mask(LOG_UNIMP, "[RTC] RTC count-regs update\n");
}

/* Update the next timeout time as difference between Count and Limit */
static void cpu_arc_rtc_update (CPUARCState *env)
{
  uint64_t wait = 0;
  uint64_t now, next;

  cpu_arc_rtc_hl_update (env);
  now = env->last_clk;

  if (env->cpu_rtc)
    {
      wait = -1ULL - ((((uint64_t) env->aux_rtc_high) << 32) + env->aux_rtc_low);
      next = now + (uint64_t) wait * TIMER_PERIOD (env->freq_hz);
      timer_mod (env->cpu_rtc, next);
    }
  qemu_log_mask(LOG_UNIMP, "[RTC] RTC update\n");
}

static void arc_rtc_cb (void *opaque)
{
  CPUARCState *env = (CPUARCState *) opaque;

  if (!(env->timer_build & TB_RTC))
    return;

  if (timer_expired(env->cpu_rtc, qemu_clock_get_ns (QEMU_CLOCK_VIRTUAL)))
    {
      qemu_log_mask(LOG_UNIMP, "[RTC] RTC expired\n");
    }

  /* Update the RTC registers.  */
  cpu_arc_rtc_update (env);
}

static void cpu_arc_count_reset (CPUARCState *env, uint32_t timer)
{
  timer &= 0x01;
  env->timer[timer].T_Cntrl = 0;
  env->timer[timer].T_Count = 0;
  env->timer[timer].T_Limit = 0x00ffffff;
}

static uint32_t cpu_arc_count_get (CPUARCState *env, uint32_t timer)
{
  cpu_arc_count_update (env);
  return env->timer[timer & 0x01].T_Count;
}

static void cpu_arc_count_set (CPUARCState *env, uint32_t timer, uint32_t val)
{
  env->timer[timer & 0x01].T_Count = val;
  cpu_arc_timer_update (env, timer);
}

static void cpu_arc_store_limit (CPUARCState *env,
				 uint32_t timer, uint32_t value)
{
  switch (timer)
    {
    case 0:
      if (!(env->timer_build & TB_T0))
	return;
      break;
    case 1:
      if (!(env->timer_build & TB_T1))
	return;
      break;
    default:
      break;
    }
  env->timer[timer].T_Limit = value;
  cpu_arc_timer_update (env, timer);
}

static void cpu_arc_control_set (CPUARCState *env,
				 uint32_t timer, uint32_t value)
{
  timer &= 0x1;
  if ((env->timer[timer].T_Cntrl & TMR_IP) && !(value & TMR_IP))
      qemu_irq_lower (env->irq[TIMER0_IRQ + (timer)]);
  env->timer[timer].T_Cntrl = value & 0x1f;
  cpu_arc_timer_update (env, timer);
}

/* Init procedure, called in platform.	*/

void cpu_arc_clock_init (ARCCPU *cpu)
{
  CPUARCState *env = &cpu->env;

  if (env->timer_build & TB_T0)
    {
      cpu_arc_count_reset (env, 0);
      env->cpu_timer0 = timer_new_ns(QEMU_CLOCK_VIRTUAL, &arc_timer0_cb, env);
    }

  if (env->timer_build & TB_T1)
    {
      cpu_arc_count_reset (env, 1);
      env->cpu_timer1 = timer_new_ns(QEMU_CLOCK_VIRTUAL, &arc_timer1_cb, env);
    }

  if (env->timer_build & TB_RTC)
    env->cpu_rtc = timer_new_ns (QEMU_CLOCK_VIRTUAL, &arc_rtc_cb, env);
}

void arc_initializeTIMER (ARCCPU *cpu)
{
  CPUARCState *env = &cpu->env;

  /* FIXME! add default timer priorities.  */
  env->timer_build = 0x04 | (cpu->cfg.has_timer_0 ? TB_T0 : 0) |
    (cpu->cfg.has_timer_1 ? TB_T1 : 0) |
    (cpu->cfg.rtc_option ? TB_RTC : 0);
}

void arc_resetTIMER (ARCCPU *cpu)
{
  CPUARCState *env = &cpu->env;

  if (env->timer_build & TB_T0)
    cpu_arc_count_reset (env, 0);

  if (env->timer_build & TB_T1)
    cpu_arc_count_reset (env, 1);
}

static uint32_t arc_rtc_count_get (CPUARCState *env, bool lower)
{
  cpu_arc_rtc_hl_update (env);
  return lower ? env->aux_rtc_low : env->aux_rtc_high;
}

static void arc_rtc_ctrl_set (CPUARCState *env, uint32_t val)
{
  assert (env->stat.Uf == 0);

  env->aux_irq_ctrl = 0xc0000000 | (val & 0x01);
  if (val & 0x02)
    {
      env->aux_rtc_low = 0;
      env->aux_rtc_high = 0;
    }
}

/* Function implementation for reading/writing aux regs.  */
uint32_t
aux_timer_get (struct arc_aux_reg_detail *aux_reg_detail, void *data)
{
  CPUARCState *env = (CPUARCState *) data;

  switch (aux_reg_detail->id)
    {
    case AUX_ID_control0:
      return env->timer[0].T_Cntrl;
      break;

    case AUX_ID_control1:
      return env->timer[1].T_Cntrl;
      break;

    case AUX_ID_count0:
      return cpu_arc_count_get (env, 0);
      break;

    case AUX_ID_count1:
      return cpu_arc_count_get (env, 1);
      break;

    case AUX_ID_limit0:
      return env->timer[0].T_Limit;
      break;

    case AUX_ID_limit1:
      return env->timer[1].T_Limit;
      break;

    case AUX_ID_timer_build:
      return env->timer_build;
      break;

    case AUX_ID_aux_rtc_low:
      return arc_rtc_count_get (env, true);
      break;

    case AUX_ID_aux_rtc_high:
      return arc_rtc_count_get (env, false);
      break;

    case AUX_ID_aux_rtc_ctrl:
      return env->aux_rtc_ctrl;
      break;

    default:
      break;
    }
  return 0;
}

void
aux_timer_set (struct arc_aux_reg_detail *aux_reg_detail, uint32_t val, void *data)
{
  CPUARCState *env = (CPUARCState *) data;

  switch (aux_reg_detail->id)
    {
    case AUX_ID_control0:
      if (env->timer_build & TB_T0)
	cpu_arc_control_set (env, 0, val);
      break;

    case AUX_ID_control1:
      if (env->timer_build & TB_T1)
	cpu_arc_control_set (env, 1, val);
      break;

    case AUX_ID_count0:
      if (env->timer_build & TB_T0)
	cpu_arc_count_set (env, 0, val);
      break;

    case AUX_ID_count1:
      if (env->timer_build & TB_T1)
	cpu_arc_count_set (env, 1, val);
      break;

    case AUX_ID_limit0:
      cpu_arc_store_limit (env, 0, val);
      break;

    case AUX_ID_limit1:
      cpu_arc_store_limit (env, 1, val);
      break;

    case AUX_ID_aux_rtc_ctrl:
      arc_rtc_ctrl_set (env, val);
      break;

    default:
      break;
    }
}
