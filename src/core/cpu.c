#include "cpu.h"
#include "memory.h"
#include "timer.h"
#include <stdlib.h>
#include <string.h>

void cpu_init(cpu_t *cpu) {
	memset(cpu, 0, sizeof(cpu_t));

	memory_init(cpu->mem);
	timers_init(cpu->timers);
	
	cpu->mem.timers = cpu->timers;

	cpu->total_cycles = 0;
	cpu->PC = 0x0000;

}
