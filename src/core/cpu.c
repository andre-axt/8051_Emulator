#include "cpu.h"
#include "memory.h"
#include "timer.h"
#include "opcodes.h"
#include <stdlib.h>
#include <string.h>

Cpu_t* cpu_init() {
	Cpu_t *cpu;
	cpu = malloc(sizeof(cpu_t));
	if(cpu == NULL) return NULL;
	cpu->total_cycles = 0;
	cpu->PC = 0x0000;
	cpu->halted = 0;
	cpu->SP = NULL;
	return cpu;
}

void cpu_step(Cpu_t *cpu, Memory_t *mem) {
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
	update_timers(mem, cpu->total_cycles);
}

void cpu_run(Cpu_t *cpu, uint32_t steps) {
	for (uint32_t i = 0; i < steps && !cpu->halted; i++) {
		cpu_step(cpu);
	}

}
