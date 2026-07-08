#include "system.h"
#include "opcodes.h"
#include <stdlib.h>
#include <string.h>

uint8_t fetch_byte(Mcu8051_t *mcu) {
    uint8_t instruction = mcu->mem->internal_rom[mcu->cpu->PC]; 
    mcu->cpu->PC++;
    return instruction;
}

Cpu_t* cpu_init() {
	Cpu_t *cpu;
	cpu = malloc(sizeof(Cpu_t));
	if(cpu == NULL) return NULL;
	cpu->total_cycles = 0;
	cpu->PC = 0x0000;
	cpu->halted = 0;
	return cpu;
}

void cpu_step(Mcu8051_t *mcu) {
	if (mcu->cpu->halted) return;

	uint8_t opcode = fetch_byte(mcu);
	Instruction_t *instr = &opcode_table[opcode];
	
	if (instr->execute == NULL) {
        	mcu->cpu->halted = 1;
        	return;
    }

	instr->execute(mcu->cpu);
	mcu->cpu->total_cycles += instr->cycles;
	update_timers(mcu, instr->cycles);
}

void cpu_run(Mcu8051_t *mcu, uint32_t steps) {
	for (uint32_t i = 0; i < steps && !mcu->cpu->halted; i++) {
		cpu_step(mcu);
	}

}
