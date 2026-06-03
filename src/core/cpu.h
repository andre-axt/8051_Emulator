#ifndef CPU_H
#define CPU_H

#include <stdint.h>

typedef struct {
	uint16_t PC;
	uint8_t *SP;
	uint64_t total_cycles;
	uint8_t halted;	

} Cpu_t;

void cpu_init(Cpu_t *cpu);
void cpu_step(Cpu_t *cpu, Memory_t *mem);
void cpu_run(Cpu_t *cpu, uint32_t steps);

#endif
