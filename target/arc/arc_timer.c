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

//#define TIMER_PERIOD(hz) (1000000000LL/(hz))
#define TIMER_PERIOD(A) 10
#define TIMER0_IRQ 16
#define TIMER1_IRQ 17

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
}

/* Update the next timeout time as difference between Count and Limit */
static void cpu_arc_timer_update (CPUARCState *env)
{
  uint32_t wait;
  uint64_t now, next;

  cpu_arc_count_update (env);
  now = env->last_clk;

  if (env->cpu_timer0)
    {
      wait = env->timer[0].T_Limit - env->timer[0].T_Count;
      next = now + (uint64_t) wait * TIMER_PERIOD (env->freq_hz);
      timer_mod (env->cpu_timer0, next);
    }

  /* FIXME! add timer1*/
}

/* Expier the timer function.  Rise an interrupt if required.  */

static void cpu_arc_timer_expire (CPUARCState *env, uint32_t timer)
{
  /* Set the IP bit.  */
  env->timer[timer & 0x01].T_Cntrl |= TMR_IP;

  /* Raise an interrupt if enabled.  */
  if (env->timer[timer & 0x01].T_Cntrl & TMR_IE)
    qemu_irq_raise (env->irq[TIMER0_IRQ + (timer & 0x01)]);
}

/* This callback should occur when the counter is exactly equal to the
   limit value.  Offset the count by one to avoid immediately
   retriggering the callback before any virtual time has passed.  */

static void arc_timer0_cb (void *opaque)
{
  CPUARCState *env = (CPUARCState *) opaque;

  if (!(env->timer_build & TB_T0))
    return;

  if (timer_expired(env->cpu_timer0, qemu_clock_get_ns (QEMU_CLOCK_VIRTUAL)))
    cpu_arc_timer_expire (env, 0);

  cpu_arc_timer_update (env);
}

static void cpu_arc_count_reset (CPUARCState *env, uint32_t timer)
{
  timer &= 0x01;
  env->timer[timer].T_Cntrl = 0;
  env->timer[timer].T_Count = 0;
  env->timer[timer].T_Limit = 0x00ffffff;
}

uint32_t cpu_arc_count_get (CPUARCState *env, uint32_t timer)
{
  cpu_arc_count_update (env);
  return env->timer[timer & 0x01].T_Count;
}

void cpu_arc_count_set (CPUARCState *env, uint32_t timer, uint32_t val)
{
  env->timer[timer & 0x01].T_Count = val;
  cpu_arc_timer_update (env);
}

void cpu_arc_store_limit (CPUARCState *env, uint32_t timer, uint32_t value)
{
  if (!(env->timer_build & TB_T0))
    return;

  env->timer[0].T_Limit = value;
  cpu_arc_timer_update (env);
}

void cpu_arc_control_set (CPUARCState *env, uint32_t timer, uint32_t value)
{
  env->timer[timer & 0x01].T_Cntrl = value;
  qemu_irq_lower (env->irq[TIMER0_IRQ + (timer & 0x01)]);
}

/* Init procedure, called in platform.  */

void cpu_arc_clock_init (ARCCPU *cpu)
{
  CPUARCState *env = &cpu->env;

  cpu_arc_count_reset (env, 0);
  env->cpu_timer0 = timer_new_ns(QEMU_CLOCK_VIRTUAL, &arc_timer0_cb, env);

  env->cpu_timer1 = NULL;
}
