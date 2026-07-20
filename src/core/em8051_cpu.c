#include "em8051_types.h"
#include "em8051_cpu.h"
#include "em8051_memory.h"
#include "em8051_opcodes.h"
#include "em8051_timers.h"
#include "em8051_bitops.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

Cpu_t* cpu_init() {
	Cpu_t *cpu;
	cpu = malloc(sizeof(Cpu_t));
	if(cpu == NULL) return NULL;
	cpu->total_cycles = 0;
	cpu->PC = 0x0000;
	cpu->PC_arg = 0;
	cpu->is_jump = 0;
	cpu->halted = 0;
	#ifdef DEBUG_CPU
		cpu->debug_mode = 1;
	#else
		cpu->debug_mode = 0;
	#endif
	return cpu;
}

void cpu_step(Mcu8051_t *mcu) {
	if (mcu->cpu->halted) return;

	if(mcu->cpu->is_jump) {
		mcu->cpu->PC = mcu->cpu->PC_arg - 1;
		mcu->cpu->is_jump = 0;
	}
	
	uint8_t opcode = fetch_byte(mcu);
	Instruction_t *instr = &opcode_table[opcode];

	if (mcu->cpu->debug_mode) {
		printf("PC: %d\n", mcu->cpu->PC);
		printf("Opcode: %x\n", opcode);
	} 
	
	if (instr->execute == NULL) {
        	mcu->cpu->halted = 1;
        	return;
    }

	instr->execute(mcu);
	mcu->cpu->total_cycles += instr->cycles;
	update_timers(mcu, instr->cycles);


	return;
}

void cpu_run(Mcu8051_t *mcu, uint32_t steps) {
	for (uint32_t i = 0; i < steps && !mcu->cpu->halted; i++) {
		cpu_step(mcu);
	}

	return;

}
