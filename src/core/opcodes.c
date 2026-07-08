#include "opcodes.h"
#include "system.h"
#include <stdio.h>

static uint8_t get_bit(Mcu8051_t *mcu, uint8_t bit_addr) {
	if (bit_addr < 0x80){
		uint8_t byte_addr = 0x20 + (bit_addr >> 3);
		uint8_t bit_pos = bit_addr & 0x07;
		uint8_t byte = memory_read_data(mcu->mem, byte_addr);
		return (byte >> bit_pos) & 1;
	} 

	else if (bit_addr >= 0x80) {
		uint8_t sfr_addr = bit_addr & 0xF8;
		uint8_t bit_pos = bit_addr & 0x07;

		switch(sfr_addr) {
			case 0x80: return (mcu->mem->sfr.P0 >> bit_pos) & 1;
			case 0x90: return (mcu->mem->sfr.P1 >> bit_pos) & 1;
			case 0xA0: return (mcu->mem->sfr.P2 >> bit_pos) & 1;
			case 0xB0: return (mcu->mem->sfr.P3 >> bit_pos) & 1;
			case 0xE0: return (mcu->mem->sfr.ACC >> bit_pos) & 1;
			case 0xF0: return (mcu->mem->sfr.B >> bit_pos) & 1;
			case 0x82: return (mcu->mem->sfr.DPL >> bit_pos) & 1;
			case 0x83: return (mcu->mem->sfr.DPH >> bit_pos) & 1;
			case 0xA8: return (mcu->mem->sfr.IE >> bit_pos) & 1;
			case 0xB8: return (mcu->mem->sfr.IP >> bit_pos) & 1;
			case 0x87: return (mcu->mem->sfr.PCON >> bit_pos) & 1;
			case 0xD0: return (mcu->mem->sfr.PSW >> bit_pos) & 1;
			case 0x99: return (mcu->mem->sfr.SBUF >> bit_pos) & 1;
			case 0x98: return (mcu->mem->sfr.SCON >> bit_pos) & 1;
			case 0x81: return (mcu->mem->sfr.SP >> bit_pos) & 1;
			case 0x88: return (mcu->mem->sfr.TCON >> bit_pos) & 1;
			case 0x89: return (mcu->mem->sfr.TMOD >> bit_pos) & 1;
			case 0x8A: return (mcu->mem->sfr.TL0 >> bit_pos) & 1;
			case 0x8B: return (mcu->mem->sfr.TL1 >> bit_pos) & 1;
			case 0x8C: return (mcu->mem->sfr.TH0 >> bit_pos) & 1;
			case 0x8D: return (mcu->mem->sfr.TH1 >> bit_pos) & 1;
			default: return 0;
			
		}
		
	}
	return 0;

}

static void set_bit(Mcu8051_t *mcu, uint8_t bit_addr, uint8_t value) {
	uint8_t byte_offset = bit_addr >> 3;
	uint8_t byte_addr = 0x20 + byte_offset;
	uint8_t bit_pos = bit_addr & 0x07;
	uint8_t byte = memory_read_data(mcu->mem, byte_addr);

	if (value) {
		byte |= (1 << bit_pos);
	} else {
		byte &= ~(1 << bit_pos);
		
	}
	
	memory_write_data(mcu->mem, byte_addr, byte);
}

void instr_nop(Mcu8051_t *mcu) {
	mcu->cpu->PC++;
	return;
}
