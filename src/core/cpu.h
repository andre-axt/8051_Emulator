#ifndef CPU_H
#define CPU_H

#include <stdint.h>
#include "memory.h"
#include "timer.h"

typedef struct {
	memory_t mem;
	timers_system_t timers;
	uint16_t PC;
	uint64_t total_cycles;
	uint8_t halted;	

} cpu_t;

void cpu_init(cpu_t *cpu);

#endif
