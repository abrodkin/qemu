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

#include "qemu/osdep.h"
#include "cpu.h"
#include "exec/helper-proto.h"
#include "exec/ioport.h"
#include "translate-all.h"
#include "arc-regs.h"


//target_ulong helper_norm(CPUARCState *env, uint32_t src1)
//{
//    if (src1 == 0x00000000 || src1 == 0xffffffff) {
//        return 31;
//    } else {
//        if ((src1 & 0x80000000) == 0x80000000) {
//            src1 = ~src1;
//        }
//        return clz32(src1) - 1;
//    }
//}
target_ulong helper_norm(CPUARCState *env, uint32_t src1)
{
  int i;
  int32_t tmp = (int32_t) src1;
  if(tmp == 0 || tmp == -1)
    return 0;
  for(i = 0; i <= 31; i++)
  {
    if((tmp >> i) == 0) break;
    if((tmp >> i) == -1) break;
  }
  return i;
}

//target_ulong helper_normw(CPUARCState *env, uint32_t src1)
//{
//    src1 &= 0xffff;
//
//    if (src1 == 0x0000 || src1 == 0xffff) {
//        return 15;
//    } else {
//        if ((src1 & 0x8000) == 0x8000) {
//            src1 = ~src1 & 0xffff;
//        }
//        return clz32(src1) - 17;
//    }
//}
target_ulong helper_normh(CPUARCState *env, uint32_t src1)
{
  int i;
  for(i = 0; i <= 15; i++)
  {
    if(src1 >> i == 0) break;
    if(src1 >> i == -1) break;
  }
  return i;
}

target_ulong helper_ffs(CPUARCState *env, uint32_t src)
{
  int i;
  if(src == 0)
    return 31;
  for(i = 0; i <= 31; i++)
    if(((src >> i) & 1) != 0)
      break;
  return i;
}

target_ulong helper_fls(CPUARCState *env, uint32_t src)
{
  int i;
  for(i = 31; i >= 0; i++)
    if(((src >> i) & 1) != 0)
      break;
  return i;
}

void helper_sr(CPUARCState *env, uint32_t val, uint32_t aux)
{
    switch (arc_aux_reg_struct_for_address(aux, ARC_OPCODE_ARCv2HS)->id) {
        case AUX_ID_status: {
        } break;

        case AUX_ID_semaphore: {
        } break;

        case AUX_ID_lp_start: {
	  env->lps = val;
        } break;

        case AUX_ID_lp_end: {
	  env->lpe = val;
        } break;

        case AUX_ID_identity: {
        } break;

        case AUX_ID_debug: {
        } break;

        case AUX_ID_pc: {
        } break;

        case AUX_ID_status32: {
        } break;

        case AUX_ID_status32_l1: {
        } break;

        case AUX_ID_status32_l2: {
        } break;

        case AUX_ID_mulhi: {
        } break;

        case AUX_ID_int_vector_base: {
        } break;

        case AUX_ID_aux_macmode: {
        } break;

        case AUX_ID_aux_irq_lv12: {
        } break;

        case AUX_ID_aux_irq_lev: {
        } break;

        case AUX_ID_aux_irq_hint: {
        } break;

        case AUX_ID_eret: {
        } break;

        case AUX_ID_erbta: {
        } break;

        case AUX_ID_erstatus: {
        } break;

        case AUX_ID_ecr: {
        } break;

        case AUX_ID_efa: {
        } break;

        case AUX_ID_icause1: {
        } break;

        case AUX_ID_icause2: {
        } break;

        case AUX_ID_aux_ienable: {
        } break;

        case AUX_ID_aux_itrigger: {
        } break;

        case AUX_ID_bta: {
        } break;

        case AUX_ID_bta_l1: {
        } break;

        case AUX_ID_bta_l2: {
        } break;

        case AUX_ID_aux_irq_pulse_cancel: {
        } break;

        case AUX_ID_aux_irq_pending: {
        } break;

        default: {
            cpu_outl(aux, val);
        }
    }
    cpu_outl(aux, val);
}

static target_ulong get_status(CPUARCState *env)
{
    target_ulong res = 0x00000000;

    res |= (env->stat.Zf) ? BIT(31) : 0;
    res |= (env->stat.Nf) ? BIT(30) : 0;
    res |= (env->stat.Cf) ? BIT(29) : 0;
    res |= (env->stat.Vf) ? BIT(28) : 0;
    res |= (env->stat.E2f) ? BIT(27) : 0;
    res |= (env->stat.E1f) ? BIT(26) : 0;

    if (env->stopped) {
        res |= BIT(25);
    }

    res |= (env->r[63] >> 2) & 0x03ffffff;

    return res;
}

static target_ulong get_status32(CPUARCState *env)
{
    target_ulong res = 0x00000000;

    res |= (env->stat.Lf) ? BIT(12) : 0;
    res |= (env->stat.Zf) ? BIT(11) : 0;
    res |= (env->stat.Nf) ? BIT(10) : 0;
    res |= (env->stat.Cf) ? BIT(9)  : 0;
    res |= (env->stat.Vf) ? BIT(8)  : 0;
    res |= (env->stat.Uf) ? BIT(7)  : 0;
    res |= (env->stat.DEf) ? BIT(6)  : 0;
    res |= (env->stat.AEf) ? BIT(5)  : 0;
    res |= (env->stat.A2f) ? BIT(4)  : 0;
    res |= (env->stat.A1f) ? BIT(3)  : 0;
    res |= (env->stat.E2f) ? BIT(2)  : 0;
    res |= (env->stat.E1f) ? BIT(1)  : 0;

    if (env->stopped) {
        res |= BIT(0);
    }

    return res;
}
static void set_status32(CPUARCState *env, target_ulong value)
{
    env->stat.Lf = ((value >> 12) & 1);
    env->stat.Zf = ((value >> 11) & 1);
    env->stat.Nf = ((value >> 10) & 1);
    env->stat.Cf = ((value >> 9)  & 1);
    env->stat.Vf = ((value >> 8)  & 1);
    env->stat.Uf = ((value >> 7)  & 1);
    env->stat.DEf = ((value >> 6) & 1);
    env->stat.AEf = ((value >> 5) & 1);
    env->stat.A2f = ((value >> 4) & 1);
    env->stat.A1f = ((value >> 3) & 1);
    env->stat.E2f = ((value >> 2) & 1);
    env->stat.E1f = ((value >> 1) & 1);
}

static target_ulong get_status32_l1(CPUARCState *env)
{
    target_ulong res = 0x00000000;

    res |= (env->stat_l1.Lf) ? BIT(12) : 0;
    res |= (env->stat_l1.Zf) ? BIT(11) : 0;
    res |= (env->stat_l1.Nf) ? BIT(10) : 0;
    res |= (env->stat_l1.Cf) ? BIT(9)  : 0;
    res |= (env->stat_l1.Vf) ? BIT(8)  : 0;
    res |= (env->stat_l1.Uf) ? BIT(7)  : 0;
    res |= (env->stat_l1.DEf) ? BIT(6)  : 0;
    res |= (env->stat_l1.AEf) ? BIT(5)  : 0;
    res |= (env->stat_l1.A2f) ? BIT(4)  : 0;
    res |= (env->stat_l1.A1f) ? BIT(3)  : 0;
    res |= (env->stat_l1.E2f) ? BIT(2)  : 0;
    res |= (env->stat_l1.E1f) ? BIT(1)  : 0;

    return res;
}

static target_ulong get_status32_l2(CPUARCState *env)
{
    target_ulong res = 0x00000000;

    res |= (env->stat_l2.Lf) ? BIT(12) : 0;
    res |= (env->stat_l2.Zf) ? BIT(11) : 0;
    res |= (env->stat_l2.Nf) ? BIT(10) : 0;
    res |= (env->stat_l2.Cf) ? BIT(9)  : 0;
    res |= (env->stat_l2.Vf) ? BIT(8)  : 0;
    res |= (env->stat_l2.Uf) ? BIT(7)  : 0;
    res |= (env->stat_l2.DEf) ? BIT(6)  : 0;
    res |= (env->stat_l2.AEf) ? BIT(5)  : 0;
    res |= (env->stat_l2.A2f) ? BIT(4)  : 0;
    res |= (env->stat_l2.A1f) ? BIT(3)  : 0;
    res |= (env->stat_l2.E2f) ? BIT(2)  : 0;
    res |= (env->stat_l2.E1f) ? BIT(1)  : 0;

    return res;
}

static target_ulong get_debug(CPUARCState *env)
{
    target_ulong res = 0x00000000;

    res |= (env->debug.LD) ? BIT(31) : 0;
    res |= (env->debug.SH) ? BIT(30) : 0;
    res |= (env->debug.BH) ? BIT(29) : 0;
    res |= (env->debug.UB) ? BIT(28) : 0;
    res |= (env->debug.ZZ) ? BIT(27) : 0;
    res |= (env->debug.RA) ? BIT(22) : 0;
    res |= (env->debug.IS) ? BIT(11) : 0;
    res |= (env->debug.FH) ? BIT(1)  : 0;
    res |= (env->debug.SS) ? BIT(0)  : 0;

    return res;
}

static target_ulong get_identity(CPUARCState *env)
{
    target_ulong chipid = 0xffff, arcnum = 0, arcver, res;

    switch (env->family) {
        case ARC_OPCODE_ARC700: {
            arcver = 0x34;
        } break;

        case ARC_OPCODE_ARCv2EM: {
            arcver = 0x44;
        } break;

        case ARC_OPCODE_ARCv2HS: {
            arcver = 0x54;
        } break;

        default: {
            arcver = 0;
        }
    }

    // TODO: in SMP, arcnum depends on the cpu instance
    res = ((chipid & 0xFFFF) << 16) | ((arcnum & 0xFF) << 8) | (arcver & 0xFF);
    return res;
}

target_ulong helper_lr(CPUARCState *env, uint32_t aux)
{
    target_ulong result = 0;

    switch (arc_aux_reg_struct_for_address(aux, ARC_OPCODE_ARCv2HS)->id) {
        case AUX_ID_status: {
            result = get_status(env);
        } break;

        /*
            NOTE: SEMAPHORE should be handled by a device
        */

        case AUX_ID_lp_start: {
	    result = env->lps;
        } break;

        case AUX_ID_lp_end: {
	    result = env->lpe;
        } break;
        case AUX_ID_identity: {
            result = get_identity(env);
        } break;

        case AUX_ID_debug: {
            result = get_debug(env);
        } break;

        case AUX_ID_pc: {
            result = env->pc & 0xfffffffe;
        } break;

        case AUX_ID_status32: {
            result = get_status32(env);
        } break;

        case AUX_ID_status32_l1: {
            result = get_status32_l1(env);
        } break;

        case AUX_ID_status32_l2: {
            result = get_status32_l2(env);
        } break;

        case AUX_ID_mulhi: {
            result = CPU_MHI(env);
        } break;

        case AUX_ID_int_vector_base: {
            result = env->intvec;
        } break;

        case AUX_ID_aux_macmode: {
        } break;

        case AUX_ID_aux_irq_lv12: {
        } break;

        case AUX_ID_aux_irq_lev: {
        } break;

        case AUX_ID_aux_irq_hint: {
        } break;

        case AUX_ID_eret: {
            result = env->eret;
        } break;

        case AUX_ID_erbta: {
            result = env->erbta;
        } break;

        case AUX_ID_erstatus: {
        } break;

        case AUX_ID_ecr: {
            result = env->ecr;
        } break;

        case AUX_ID_efa: {
            result = env->efa;
        } break;

        case AUX_ID_icause1: {
        } break;

        case AUX_ID_icause2: {
        } break;

        case AUX_ID_aux_ienable: {
        } break;

        case AUX_ID_aux_itrigger: {
        } break;

        case AUX_ID_bta: {
            result = env->bta;
        } break;

        case AUX_ID_bta_l1: {
            result = env->bta_l1;
        } break;

        case AUX_ID_bta_l2: {
            result = env->bta_l2;
        } break;

        case AUX_ID_aux_irq_pulse_cancel: {
        } break;

        case AUX_ID_aux_irq_pending: {
        } break;

        default: {
            result = cpu_inl(aux);
        }
    }

    return  result;
}

void helper_halt(CPUARCState *env)
{
    /* TODO: implement */
}

void helper_rtie(CPUARCState *env)
{
    if (env->stat.AEf) {
        CPU_PCL(env) = env->eret;
        env->stat = env->stat_er;
        env->bta = env->erbta;
    } else if (env->stat.A2f) {
        CPU_PCL(env) = CPU_ILINK2(env);
        env->stat = env->stat_l2;
        env->bta = env->bta_l2;
    } else if (env->stat.A1f) {
        CPU_PCL(env) = CPU_ILINK1(env);
        env->stat = env->stat_l1;
        env->bta = env->bta_l1;
    } else {
        CPU_PCL(env) = env->eret;
        env->stat = env->stat_er;
        env->bta = env->stat.AEf;
    }
}

void helper_flush(CPUARCState *env)
{
    tb_flush((CPUState *)arc_env_get_cpu(env));
}

void helper_raise_exception (CPUARCState *env, uint32_t index)
{
    CPUState *cs = CPU (arc_env_get_cpu(env));
    cpu_loop_exit(cs);
}

uint32_t helper_get_status32(CPUARCState *env)
{
  return get_status32(env);
}

void helper_set_status32(CPUARCState *env, uint32_t value)
{
  set_status32(env, value);
}

uint32_t helper_overflow_add_flag(uint32_t dest, uint32_t b, uint32_t c)
{
  dest >>= 31;
  b >>= 31;
  c >>= 31;
  if((dest == 0 && b == 1 && c == 1)
     || (dest == 1 && b == 0 && c == 0))
    return 1;
  else
    return 0;
}

uint32_t helper_overflow_sub_flag(uint32_t dest, uint32_t b, uint32_t c)
{
  dest >>= 31;
  b >>= 31;
  c >>= 31;
  if((dest == 1 && b == 0 && c == 1)
     || (dest == 0 && b == 1 && c == 0))
    return 1;
  else
    return 0;
}

uint32_t helper_mpymu(CPUARCState *env, uint32_t b, uint32_t c)
{
  uint64_t _b = (uint64_t) b;
  uint64_t _c = (uint64_t) c;

  return (uint32_t) ((_b * _c) >> 32);
}

uint32_t helper_mpym(CPUARCState *env, uint32_t b, uint32_t c)
{
  int64_t _b = (int64_t) ((int32_t) b);
  int64_t _c = (int64_t) ((int32_t) c);

//  fprintf(stderr, "B = 0x%llx, C = 0x%llx, result = 0x%llx\n", _b, _c, _b * _c);
  return ((_b * _c) >> 32);
}

uint32_t lf_variable = 0;
uint32_t helper_get_lf(void)
{
  return lf_variable;
}
void helper_set_lf(uint32_t v)
{
  lf_variable = v;
}
