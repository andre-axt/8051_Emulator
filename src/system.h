#ifndef SYSTEM_H
#define SYSTEM_H

#include "cpu.h"
#include "memory.h"
#include "timer.h"
#include "interruptions.h"

typedef struct Mcu8051_t {
    Cpu_t *cpu;
    Memory_t *mem;
    Timers_system_t *timers;
    Interruptions_t *intpt;
} Mcu8051_t;

#endif
