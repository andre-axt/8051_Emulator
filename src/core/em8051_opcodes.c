#include "em8051_opcodes.h"
#include "em8051_types.h"
#include "em8051_memory.h"
#include "em8051_cpu.h"
#include "em8051_bitops.h"
#include <stdlib.h>

Instruction_t opcode_table[256] = {
	[0x00] = { "NOP",   1, 1, instr_nop },
    [0x04] = { "INC A", 1, 1, instr_inc_a },
	[0xC2] = { "CLR bit", 1, 1, instr_clr },
	[0xC3] = { "CLR C", 1, 1, instr_clr },
	[0xE4] = { "CLR A", 1, 1, instr_clr },
    [0xD0] = { "POP byte", 1, 1, instr_pop },
	[0x08] = { "INC R0", 1, 1, instr_inc_r0 },
    [0x09] = { "INC R1", 1, 1, instr_inc_r1 },
    [0x0A] = { "INC R2", 1, 1, instr_inc_r2 },
    [0x0A] = { "INC R3", 1, 1, instr_inc_r3 },
    [0x0A] = { "INC R4", 1, 1, instr_inc_r4 },
    [0x0A] = { "INC R5", 1, 1, instr_inc_r5 },
    [0x0A] = { "INC R6", 1, 1, instr_inc_r6 },
    [0x0A] = { "INC R7", 1, 1, instr_inc_r7 },

}

#define DEFINE_INC_RN(n) \
    void instr_inc_r##n(Mcu8051_t *mcu) { \
        if (mcu->cpu == NULL || mcu->mem == NULL) return; \
        \
        uint8_t rs0 = (mcu->mem->sfr.PSW >> 3) & 0x01; \
        uint8_t rs1 = (mcu->mem->sfr.PSW >> 4) & 0x01; \
        uint8_t bank = (rs1 << 1) | rs0; \
       	mcu->mem->ram.banks[bank][n]++; \
        \
        mcu->cpu->PC++; \
    }


void instr_inc_a(Mcu8051_t *mcu) {
	if (mcu->cpu == NULL || mcu->mem == NULL) return;
	mcu->mem->sfr.ACC++;
	mcu->cpu->PC++;
	return;
}

void instr_nop(Mcu8051_t *mcu) {
	if (mcu->cpu == NULL) return;
	mcu->cpu->PC++;
	return;
}

void instr_clr(Mcu8051_t *mcu) {
	if (mcu->cpu == NULL || mcu->mem == NULL) return;
	
	uint8_t opcode = fetch_byte(mcu);
	
	switch (opcode) {
		case 0xC2 : {
			mcu->cpu->PC++;
			uint8_t bit = fetch_byte(mcu);
			set_bit(mcu, bit, 0);
			break;
		}
		case 0xC3 : {
			mcu->mem->sfr.PSW &= (uint8_t)~(1u << 3);  
			break;
		}
		case 0xE4 : {
			mcu->mem->sfr.ACC = 0;  
			break;
		}
		case default: {
			break;
		}
	}
	mcu->cpu->PC++;
	return;
}

void instr_pop(Mcu8051_t *mcu) {
	if(mcu->cpu == NULL || mcu->mem == NULL) return;
	mcu->cpu->PC++;
	uint8_t byte = fetch_byte(mcu);
    stack_pop_byte(mcu->mem);
	return;
}
