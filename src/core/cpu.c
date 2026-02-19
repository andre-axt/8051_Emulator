#include "cpu.h"
#include "memory.h"
#include "timer.h"
#include "opcode"
#include <stdlib.h>
#include <string.h>

void cpu_init(cpu_t *cpu) {
	memset(cpu, 0, sizeof(cpu_t));

	memory_init(cpu->mem);
	timers_init(cpu->timers);
	
	cpu->mem.timers = cpu->timers;

	cpu->total_cycles = 0;
	cpu->PC = 0x0000;
	cpu->halted = 0;
}

uint8_t fetch_byte(cpu_t *cpu){
	return memory_read_data(cpu->mem, cpu->PC++);

}

uint16_t fetch_word(cpu_t cpu*) {
	uint8_t low = fetch_byte(cpu);
	uint8_t high = fetch_byte(cpu);
	return (high << 8) | low;
}

void cpu_step(cpu_t *cpu) {
	if (cpu->halted) return;

	uint8_t opcode = fetch_byte(cpu);
	instruction_t *instr = &opcode_table[opcode];
	
	if (instr->execute == NULL) {
        	printf("ERROR: Unimplemented opcode 0x%02X at 0x%04X\n", opcode, current_pc);
        	cpu->halted = 1;
        	return;
    	}

	instr->execute(cpu);
	cpu->total_cycles += instr->cycles;

	update_timers(cpu->mem, cpu->total_cycles);

}

void cpu_run(cpu_t *cpu, uint32_t steps) {
	for (uint32_t i = 0; i < steps && !cpu->halted; i++) {
		cpu_step(cpu);
	}

}




