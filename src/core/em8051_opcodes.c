#include "em8051_opcodes.h"
#include "em8051_types.h"
#include "em8051_memory.h"
#include "em8051_cpu.h"
#include "em8051_bitops.h"
#include <stdlib.h>

Instruction_t opcode_table[256] = {
	[0x00] = { "NOP", 1, 1, instr_nop },
	[0x01] = { "AJMP label", 2, 2, instr_ajmp },
	[0x02] = { "LJMP label", 3, 2, instr_ljmp },
	[0x03] = { "RR A", 1, 1, instr_rr },
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
    [0x10] = { "JBC bit_adress, address", 3, 2, instr_jbc },
    [0x13] = { "RRC A", 1, 1, instr_rrc },
    [0x22] = { "RET", 1, 2, instr_ret },
    [0x32] = { "RETI", 1, 2, instr_reti },
	[0x73] = { "JMP @A+DPTR", 1, 1, instr_jmp },
    [0x80] = { "SJMP rel", 2, 2, instr_sjmp },
    [0xC0] = { "PUSH byte", 2, 2, instr_push },
	[0xC2] = { "CLR bit", 1, 1, instr_clr_bit },
	[0xC3] = { "CLR C", 1, 1, instr_clr_c },
    [0xD0] = { "POP byte", 2, 2, instr_pop },
    [0xD2] = { "SETB bit", 2, 1, instr_setb_bit },
    [0xD3] = { "SETB C", 1, 1, instr_setb_c },
	[0xE4] = { "CLR A", 1, 1, instr_clr_acc },

};

void instr_nop(Mcu8051_t *mcu) {
	if (mcu->cpu == NULL) return;
	return;
}

void instr_ajmp(Mcu8051_t *mcu) {
    if (mcu == NULL || mcu->cpu == NULL || mcu->mem == NULL) return;
	
    uint8_t opcode = memory_read_code(mcu->mem, mcu->cpu->PC - 1);
    uint8_t low_byte = fetch_byte(mcu);
    uint16_t page_offset = ((uint16_t)(opcode & 0xE0)) << 3;
    uint16_t target_address = (mcu->cpu->PC & 0xF800) | page_offset | low_byte;

    mcu->cpu->PC = target_address;
	return;
}

void instr_ljmp(Mcu8051_t *mcu) {
	if (mcu->cpu == NULL || mcu->mem == NULL) return;
	uint16_t jump = fetch_word(mcu);
	mcu->cpu->PC = jump;
	return;
}

void instr_rr(Mcu8051_t *mcu) {
	if (mcu->cpu == NULL || mcu->mem == NULL) return;
	mcu->mem->sfr.ACC >>= 1;
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
    uint8_t value = memory_read_data(mcu->mem, address);
	memory_write_data(mcu->mem, address, value + 1);
	return;
}

void instr_inc_rn(Mcu8051_t *mcu) {
    if (mcu->cpu == NULL || mcu->mem == NULL) return; 
	uint8_t opcode = fetch_byte(mcu);
	uint8_t Rn = opcode & 0x07;
	uint8_t bank = (mcu->mem->sfr.PSW >> 3) & 0x03;
    
    mcu->mem->ram.banks[bank][Rn]++; 
	return;
}

void instr_jbc(Mcu8051_t *mcu) {
	if(mcu->cpu == NULL || mcu->mem == NULL) return;
	
	uint8_t bit_address = fetch_byte(mcu);
	int8_t rel_offset = (int8_t)fetch_byte(mcu);
	
	if (get_bit(mcu, bit_address)) { 
        set_bit(mcu, bit_address, 0); 
        mcu->cpu->PC += rel_offset;
    }
	return;
}

void instr_rrc(Mcu8051_t *mcu) {
	if (mcu->cpu == NULL || mcu->mem == NULL) return;
	mcu->mem->sfr.ACC = (mcu->mem->sfr.ACC & ~PSW_CY_MASK) | (mcu->mem->sfr.PSW & PSW_CY_MASK);
	mcu->mem->sfr.PSW = (mcu->mem->sfr.PSW & ~PSW_CY_MASK) | ((mcu->mem->sfr.ACC & 1) ? PSW_CY_MASK : 0);
	mcu->mem->sfr.ACC >>= 1;
	return;
}

void instr_jmp(Mcu8051_t *mcu) {
	if(mcu->cpu == NULL || mcu->mem == NULL) return;
	uint16_t dptr = (mcu->mem->sfr.DPH << 8) | mcu->mem->sfr.DPL;
	uint16_t jmp = (uint16_t)(mcu->mem->sfr.ACC + dptr);
	mcu->cpu->PC_arg = jmp;
	return;
}

void instr_push(Mcu8051_t *mcu) {
	if(mcu->cpu == NULL || mcu->mem == NULL) return;
	uint8_t address = fetch_byte(mcu);
	uint8_t value = memory_read_data(mcu->mem, address);
    stack_push_byte(mcu->mem, value);
	return;
}

void instr_clr_bit(Mcu8051_t *mcu) {
	if (mcu->cpu == NULL || mcu->mem == NULL) return;
	uint8_t bit = fetch_byte(mcu);
	set_bit(mcu, bit, 0);
	return;
}

void instr_clr_c(Mcu8051_t *mcu) {
	mcu->mem->sfr.PSW &= ~PSW_CY_MASK;
	return;
}

void instr_pop(Mcu8051_t *mcu) {
	if(mcu->cpu == NULL || mcu->mem == NULL) return;
	uint8_t address = fetch_byte(mcu);
    uint8_t value = stack_pop_byte(mcu->mem);
	memory_write_data(mcu->mem, address, value);
	return;
}

void instr_clr_acc(Mcu8051_t *mcu) {
	mcu->mem->sfr.ACC = 0;
	return;
}

void instr_setb_bit(Mcu8051_t *mcu) {
	if (mcu->cpu == NULL || mcu->mem == NULL) return;
	uint8_t bit = fetch_byte(mcu);
	set_bit(mcu, bit, 1);
	return;
}

void instr_setb_c(Mcu8051_t *mcu) {
	if (mcu->cpu == NULL || mcu->mem == NULL) return;
	mcu->mem->sfr.PSW |= PSW_CY_MASK;
	return;
}

void instr_reti(Mcu8051_t *mcu) {
    if (mcu == NULL || mcu->mem == NULL || mcu->cpu == NULL) return;
    mcu->cpu->PC = stack_pop_word(mcu->mem);
	return;
}

void instr_sjmp(Mcu8051_t *mcu) {
    if (mcu == NULL || mcu->cpu == NULL) return;

    int8_t rel_offset = (int8_t)fetch_byte(mcu);

    mcu->cpu->PC += rel_offset;
}

void instr_ret(Mcu8051_t *mcu) {
    if (mcu == NULL || mcu->cpu == NULL || mcu->mem == NULL) return;

    mcu->cpu->PC = stack_pop_word(mcu->mem);
}
