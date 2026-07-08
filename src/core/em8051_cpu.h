#ifndef EM8051_CPU_H
#define EM8051_CPU_H

#include <stdint.h>

typedef struct Mcu8051_t Mcu8051_t;

typedef struct Cpu_t {
	uint16_t PC;
	uint64_t total_cycles;
	uint8_t halted;	

} Cpu_t;

Cpu_t* cpu_init();
void cpu_step(Mcu8051_t *mcu); 
void cpu_run(Mcu8051_t *mcu, uint32_t steps);

#endif
