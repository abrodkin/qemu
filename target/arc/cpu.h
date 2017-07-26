 /*
 * QEMU ARC CPU
 *
 * Copyright (c) 2016 Michael Rolnik
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
 * <http://www.gnu.org/licenses/lgpl-2.1.html>
 */

#ifndef CPU_ARC_H
#define CPU_ARC_H

#include "qemu-common.h"
#include "cpu-qom.h"

#define TARGET_LONG_BITS            32

#define CPUArchState struct CPUARCState

#include "exec/cpu-defs.h"
#include "fpu/softfloat.h"

#define TARGET_PAGE_BITS            12
#define TARGET_PHYS_ADDR_SPACE_BITS 32
#define TARGET_VIRT_ADDR_SPACE_BITS 32
#define NB_MMU_MODES                1

#define MMU_IDX                     0

#define PHYS_BASE_RAM               0x00000000
#define VIRT_BASE_RAM               0x00000000

enum arc_features {
  ARC_FEATURE_ARC5,
  ARC_FEATURE_ARC600,
  ARC_FEATURE_ARC700,
  no_features,
};

enum arc_cpu_family {
  ARC_OPCODE_NONE    = 0,
  ARC_OPCODE_ARC600  = 1 << 0,
  ARC_OPCODE_ARC700  = 1 << 1,
  ARC_OPCODE_ARCv2EM = 1 << 2,
  ARC_OPCODE_ARCv2HS = 1 << 3
};

#define CPU_GP(env)     ((env)->r[26])
#define CPU_FP(env)     ((env)->r[27])
#define CPU_SP(env)     ((env)->r[28])
#define CPU_ILINK1(env) ((env)->r[29])
#define CPU_ILINK2(env) ((env)->r[30])
#define CPU_BLINK(env)  ((env)->r[31])
#define CPU_MLO(env)    ((env)->r[57])
#define CPU_MMI(env)    ((env)->r[58])
#define CPU_MHI(env)    ((env)->r[59])
#define CPU_LP(env)     ((env)->r[60])
#define CPU_IMM(env)    ((env)->r[62])
#define CPU_PCL(env)    ((env)->r[63])

typedef struct CPUARCState {
  uint32_t        r[64];

  struct {
    uint32_t    Lf;
    uint32_t    Zf;     /*  zero                    */
    uint32_t    Nf;     /*  negative                */
    uint32_t    Cf;     /*  carry                   */
    uint32_t    Vf;     /*  overflow                */
    uint32_t    Uf;

    uint32_t    DEf;
    uint32_t    AEf;
    uint32_t    A2f;    /*  interrupt 1 is active   */
    uint32_t    A1f;    /*  interrupt 2 is active   */
    uint32_t    E2f;    /*  interrupt 1 mask        */
    uint32_t    E1f;    /*  interrupt 2 mask        */
    uint32_t    Hf;     /*  halt                    */
  } stat, stat_l1, stat_l2, stat_er;

  struct {
    uint32_t    S2;
    uint32_t    S1;
    uint32_t    CS;
  } macmod;

  uint32_t        intvec;

  uint32_t        eret;
  uint32_t        erbta;
  uint32_t        ecr;
  uint32_t        efa;
  uint32_t        bta;
  uint32_t        bta_l1;
  uint32_t        bta_l2;

  uint32_t        pc;     /*  program counter         */
  uint32_t        lps;    /*  loops start             */
  uint32_t        lpe;    /*  loops end               */

  struct {
    uint32_t    LD;     /*  load pending bit        */
    uint32_t    SH;     /*  self halt               */
    uint32_t    BH;     /*  breakpoint halt         */
    uint32_t    UB;     /*  user mode break enabled */
    uint32_t    ZZ;     /*  sleep mode              */
    uint32_t    RA;     /*  reset applied           */
    uint32_t    IS;     /*  single instruction step */
    uint32_t    FH;     /*  force halt              */
    uint32_t    SS;     /*  single step             */
  } debug;
  bool            stopped;

  /* Fields up to this point are cleared by a CPU reset */
  struct {} end_reset_fields;

  /* Those resources are used only in QEMU core */
  CPU_COMMON

  /* Fields after CPU_COMMON are preserved across CPU reset. */
  uint64_t features;
  uint32_t family;

    void *irq[32];
} CPUARCState;

/**
 * ArcCPU:
 * @env: #CPUMBState
 *
 * An ARC CPU.
 */
struct ARCCPU {
  /*< private >*/
  CPUState parent_obj;

  /*< public >*/

  /* ARC Configuration Settings.  */
  struct {
    uint32_t addr_size;
    bool aps_feature;
    bool byte_order;
    bool bitscan_option;
    uint32_t br_bc_entries;
    uint32_t br_pt_entries;
    bool br_bc_full_tag;
    uint8_t br_rs_entries;
    uint32_t br_bc_tag_size;
    uint8_t br_tosq_entries;
    uint8_t br_fb_entries;
    bool code_density;
    bool code_protect;
    uint8_t dccm_mem_cycles;
    bool dccm_posedge;
    uint8_t dccm_mem_bancks;
    uint8_t dc_mem_cycles;
    bool dc_posedge;
    bool dmp_unaligned;
    bool ecc_exception;
    uint32_t external_interrupts;
    uint8_t ecc_option;
    bool firq_option;
    bool fpu_dp_option;
    bool fpu_fma_option;
    bool fpu_div_option;
    bool has_actionpoints;
    bool has_fpu;
    bool has_interrupts;
    bool has_mmu;
    bool has_mpu;
    bool has_timer_0;
    bool has_timer_1;
    bool has_pct;
    bool has_rtt;
    bool has_smart;
    uint32_t intvbase_preset;
    uint32_t lpc_size;
    uint8_t mpu_num_regions;
    uint8_t mpy_option;
    uint32_t mmu_page_size_sel0;
    uint32_t mmu_page_size_sel1;
    uint32_t mmu_pae_enabled;
    uint32_t ntlb_num_entries;
    uint32_t num_actionpoints;
    uint32_t number_of_interrupts;
    uint32_t number_of_levels;
    uint32_t pct_counters;
    uint32_t pct_interrupt;
    uint32_t pc_size;
    uint32_t rgf_num_regs;
    uint32_t rgf_banked_regs;
    uint32_t rgf_num_banks;
    bool rtc_option;
    uint32_t rtt_feature_level;
    bool stack_checking;
    bool swap_option;
    uint32_t smar_stack_entries;
    uint32_t smart_implementation;
    uint32_t stlb_num_entries;
    uint32_t slc_size;
    uint32_t slc_line_size;
    uint32_t slc_ways;
    uint32_t slc_tag_banks;
    uint32_t slc_tram_delay;
    uint32_t slc_dbank_width;
    uint32_t slc_data_banks;
    uint32_t slc_dram_delay;
    bool slc_mem_bus_width;
    uint32_t slc_ecc_option;
    bool slc_data_halfcycle_steal;
    bool slc_data_add_pre_pipeline;
    bool uaux_option;
  } cfg;

  CPUARCState env;
};

static inline ARCCPU *arc_env_get_cpu(CPUARCState *env)
{
  return container_of(env, ARCCPU, env);
}
#define ENV_GET_CPU(e) CPU(arc_env_get_cpu(e))
#define ENV_OFFSET offsetof(ARCCPU, env)

static inline int arc_feature(CPUARCState *env, int feature)
{
    return (env->features & (1U << feature)) != 0;
}

static inline void  arc_set_feature(CPUARCState *env, int feature)
{
    env->features |= (1U << feature);
}

#define cpu_list            arc_cpu_list
#define cpu_signal_handler  cpu_arc_signal_handler

#include "exec/cpu-all.h"

static inline int cpu_mmu_index(CPUARCState *env, bool ifetch)
{
    return  0;
}

void arc_translate_init(void);

ARCCPU *cpu_arc_init(const char *cpu_model);

#define cpu_init(cpu_model) CPU(cpu_arc_init(cpu_model))

void arc_cpu_list(FILE *f, fprintf_function cpu_fprintf);
int cpu_arc_exec(CPUState *cpu);
int cpu_arc_signal_handler(int host_signum, void *pinfo, void *puc);
int arc_cpu_handle_mmu_fault(CPUState *cpu, vaddr address, int rw,
                                int mmu_idx);
int arc_cpu_memory_rw_debug(CPUState *cs, vaddr address, uint8_t *buf,
                                int len, bool is_write);
void arc_cpu_do_interrupt(CPUState *cpu);

void arc_cpu_dump_state(CPUState *cs, FILE *f,
                        fprintf_function cpu_fprintf, int flags);
hwaddr arc_cpu_get_phys_page_debug(CPUState *cpu, vaddr addr);
bool arc_cpu_exec_interrupt(CPUState *cpu, int int_req);
int arc_cpu_gdb_read_register(CPUState *cpu, uint8_t *buf, int reg);
int arc_cpu_gdb_write_register(CPUState *cpu, uint8_t *buf, int reg);

static inline void cpu_get_tb_cpu_state(CPUARCState *env, target_ulong *pc,
                                target_ulong *cs_base, uint32_t *pflags)
{
    *pc = env->pc;
    *cs_base = 0;
    *pflags = 0;
}

static inline int cpu_interrupts_enabled(CPUARCState *env1)
{
    return  0;
}

#include "exec/exec-all.h"

#endif /* !defined (CPU_ARC_H) */
