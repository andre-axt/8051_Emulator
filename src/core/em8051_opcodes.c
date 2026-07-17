#include "em8051_opcodes.h"
#include "em8051_types.h"
#include "em8051_memory.h"
#include "em8051_cpu.h"
#include "em8051_bitops.h"
#include <stdlib.h>

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

DEFINE_INC_RN(0)
DEFINE_INC_RN(1)
DEFINE_INC_RN(2)
DEFINE_INC_RN(3)
DEFINE_INC_RN(4)
DEFINE_INC_RN(5)
DEFINE_INC_RN(6)
DEFINE_INC_RN(7)

#undef DEFINE_INC_RN

Instruction_t opcode_table[256] = {
	[0x00] = { "NOP",   1, 1, instr_nop },
    [0x04] = { "INC A", 1, 1, instr_inc_a },
    [0x05] = { "INC direct", 2, 2, instr_inc_direct },
	[0x08] = { "INC R0", 1, 1, instr_inc_r0 },
    [0x09] = { "INC R1", 1, 1, instr_inc_r1 },
    [0x0A] = { "INC R2", 1, 1, instr_inc_r2 },
    [0x0B] = { "INC R3", 1, 1, instr_inc_r3 },
    [0x0C] = { "INC R4", 1, 1, instr_inc_r4 },
    [0x0D] = { "INC R5", 1, 1, instr_inc_r5 },
    [0x0E] = { "INC R6", 1, 1, instr_inc_r6 },
    [0x0F] = { "INC R7", 1, 1, instr_inc_r7 },
    [0xC0] = { "PUSH byte", 2, 2, instr_push },
	[0xC2] = { "CLR bit", 1, 1, instr_clr_bit },
	[0xC3] = { "CLR C", 1, 1, instr_clr_c },
    [0xD0] = { "POP byte", 2, 2, instr_pop },
	[0xE4] = { "CLR A", 1, 1, instr_clr_a },

};


void instr_inc_a(Mcu8051_t *mcu) {
	if (mcu->cpu == NULL || mcu->mem == NULL) return;
	mcu->mem->sfr.ACC++;
	mcu->cpu->PC++;
	return;
}

void instr_inc_direct(Mcu8051_t *mcu) {
	if (mcu->cpu == NULL || mcu->mem == NULL) return;
	mcu->cpu->PC++;
	uint8_t address = fetch_byte(mcu);
    uint8_t value = 1;
	memory_write_data(mcu->mem, address, value);
	mcu->cpu->PC++;
	return;
}

void instr_nop(Mcu8051_t *mcu) {
	if (mcu->cpu == NULL) return;
	mcu->cpu->PC++;
	return;
}

void instr_clr_bit(Mcu8051_t *mcu) {
	if (mcu->cpu == NULL || mcu->mem == NULL) return;

	uint8_t opcode = fetch_byte(mcu);
	mcu->cpu->PC++;
	uint8_t bit = fetch_byte(mcu);
	set_bit(mcu, bit, 0);
	mcu->cpu->PC++;
	return;
}

void instr_clr_c(Mcu8051_t *mcu) {
	mcu->mem->sfr.PSW &= (uint8_t)~(1u << 3);  
	mcu->cpu->PC++;
	return;
}

void instr_clr_a(Mcu8051_t *mcu) {
	mcu->mem->sfr.ACC = 0;
	mcu->cpu->PC++;
	return;
}

void instr_pop(Mcu8051_t *mcu) {
	if(mcu->cpu == NULL || mcu->mem == NULL) return;
	mcu->cpu->PC++;
	uint8_t address = fetch_byte(mcu);
    uint8_t value = stack_pop_byte(mcu->mem);
	memory_write_data(mcu->mem, address, value);
	mcu->cpu->PC++;
	return;
}

void instr_push(Mcu8051_t *mcu) {
	if(mcu->cpu == NULL || mcu->mem == NULL) return;
	mcu->cpu->PC++;
	uint8_t address = fetch_byte(mcu);
	uint8_t value = memory_read_data(mcu->mem, address);
    stack_push_byte(mcu->mem, value);
	mcu->cpu->PC++;
	return;
}
