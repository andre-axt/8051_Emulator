#ifndef CPU_H
#define CPU_H

#include <stdint.h>
#include "memory.h"
#include "timer.h"
#include "interruptions.h"

typedef struct {
	memory_t mem;
	timers_system_t timers;
	Interruptions_t interruptions;
	uint16_t PC;
	uint64_t total_cycles;
	uint8_t halted;	

} cpu_t;

void cpu_init(cpu_t *cpu);
uint8_t fetch_byte(cpu_t *cpu);
uint16_t fetch_word(cpu_t *cpu);
void cpu_step(cpu_t *cpu);
void cpu_run(cpu_t *cpu, uint32_t steps);

#endif
