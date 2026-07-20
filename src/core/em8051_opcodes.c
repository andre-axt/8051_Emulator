#include "em8051_opcodes.h"
#include "em8051_types.h"
#include "em8051_memory.h"
#include "em8051_cpu.h"
#include "em8051_bitops.h"
#include <stdlib.h>

Instruction_t opcode_table[256] = {
	[0x00] = { "NOP",   1, 1, instr_nop },
    [0x04] = { "INC A", 1, 1, instr_inc_acc },
    [0x05] = { "INC direct", 2, 2, instr_inc_direct },
	[0x08] = { "INC R0", 1, 1, instr_inc_rn },
    [0x09] = { "INC R1", 1, 1, instr_inc_rn },
    [0x0A] = { "INC R2", 1, 1, instr_inc_rn },
    [0x0B] = { "INC R3", 1, 1, instr_inc_rn },
    [0x0C] = { "INC R4", 1, 1, instr_inc_rn },
    [0x0D] = { "INC R5", 1, 1, instr_inc_rn },
    [0x0E] = { "INC R6", 1, 1, instr_inc_rn },
    [0x0F] = { "INC R7", 1, 1, instr_inc_rn },
	[0x73] = { "JMP @A+DPTR", 1, 1, instr_jmp },
    [0xC0] = { "PUSH byte", 2, 2, instr_push },
	[0xC2] = { "CLR bit", 1, 1, instr_clr_bit },
	[0xC3] = { "CLR C", 1, 1, instr_clr_c },
    [0xD0] = { "POP byte", 2, 2, instr_pop },
	[0xE4] = { "CLR A", 1, 1, instr_clr_acc },

};

void instr_nop(Mcu8051_t *mcu) {
	if (mcu->cpu == NULL) return;
	return;
}

void instr_inc_acc(Mcu8051_t *mcu) {
	if (mcu->cpu == NULL || mcu->mem == NULL) return;
	mcu->mem->sfr.ACC++;
	return;
}

void instr_inc_direct(Mcu8051_t *mcu) {
	if (mcu->cpu == NULL || mcu->mem == NULL) return;
	uint8_t address = fetch_byte(mcu);
    uint8_t value = 1;
	memory_write_data(mcu->mem, address, value);
	return;
}

void instr_inc_rn(Mcu8051_t *mcu) {
    if (mcu->cpu == NULL || mcu->mem == NULL) return; 
	
	uint8_t Rn = fetch_byte(mcu);
    Rn--; 
    
    uint8_t rs0 = (mcu->mem->sfr.PSW >> 3) & 0x01; 
    uint8_t rs1 = (mcu->mem->sfr.PSW >> 4) & 0x01; 
    uint8_t bank = (rs1 << 1) | rs0; 
    
    mcu->mem->ram.banks[bank][Rn]++; 
}

void instr_clr_bit(Mcu8051_t *mcu) {
	if (mcu->cpu == NULL || mcu->mem == NULL) return;
	uint8_t bit = fetch_byte(mcu);
	set_bit(mcu, bit, 0);
	return;
}

void instr_clr_c(Mcu8051_t *mcu) {
	mcu->mem->sfr.PSW &= (uint8_t)~(1u << 3);  
	return;
}

void instr_clr_acc(Mcu8051_t *mcu) {
	mcu->mem->sfr.ACC = 0;
	return;
}

void instr_pop(Mcu8051_t *mcu) {
	if(mcu->cpu == NULL || mcu->mem == NULL) return;
	uint8_t address = fetch_byte(mcu);
    uint8_t value = stack_pop_byte(mcu->mem);
	memory_write_data(mcu->mem, address, value);
	return;
}

void instr_push(Mcu8051_t *mcu) {
	if(mcu->cpu == NULL || mcu->mem == NULL) return;
	uint8_t address = fetch_byte(mcu);
	uint8_t value = memory_read_data(mcu->mem, address);
    stack_push_byte(mcu->mem, value);
	return;
}

void instr_jmp(Mcu8051_t *mcu) {
	if(mcu->cpu == NULL || mcu->mem == NULL) return;
	uint16_t dptr = (mcu->mem->sfr.DPH << 8) | mcu->mem->sfr.DPL;
	uint16_t jmp = (uint16_t)(mcu->mem->sfr.ACC + dptr);
	mcu->cpu->is_jump = 1;
	mcu->cpu->PC_arg = jmp;
}

