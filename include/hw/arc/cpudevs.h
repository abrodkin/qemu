#ifndef HW_ARC_CPUDEVS_H
#define HW_ARC_CPUDEVS_H

/* Timer service routines.  */
extern void cpu_arc_clock_init (ARCCPU *);
extern uint32_t cpu_arc_count_get (CPUARCState *, uint32_t);
extern void cpu_arc_count_set (CPUARCState *, uint32_t , uint32_t);
extern void cpu_arc_store_limit (CPUARCState *, uint32_t , uint32_t);
extern void cpu_arc_control_set (CPUARCState *, uint32_t , uint32_t);

extern void cpu_arc_pic_init (ARCCPU *);
extern void arc_initializeTIMER (ARCCPU *);
extern void arc_resetTIMER (ARCCPU *);
extern uint32_t arc_rtc_count_get (CPUARCState *, bool);
extern void arc_rtc_ctrl_set (CPUARCState *, uint32_t);

#endif /* !HW_ARC_CPUDEVS_H */
