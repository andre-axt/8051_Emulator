#include "opcodes.h"
#include <stdio.h>

static uint8_t get_bit(cpu_t *cpu, uint8_t bit_addr) {
	if (bit_addr < 0x80){
		uint8_t byte_addr = 0x20 + (bit_addr >> 3);
		uint8_t bit_pos = bit_addr & 0x07;
		uint8_t byte = memory_read_data(cpu->mem, byte_addr);
		return (byte >> bit_pos) & 1;
	} 

	else if (bit addr >= 0x80) {
		uint8_t sfr_addr = bit_addr & 0xF8;
		uint8_t bit_pos = bit_addr & 0x07;

		switch(sfr_addr) {
			case 0x80: return (cpu->mem.sfr.P0 >> bit_pos) & 1;
			case 0x90: return (cpu->mem.sfr.P1 >> bit_pos) & 1;
			case 0xA0: return (cpu->mem.sfr.P2 >> bit_pos) & 1;
			case 0xB0: return (cpu->mem.sfr.P3 >> bit_pos) & 1;
			case 0xE0: return (cpu->mem.sfr.ACC >> bit_pos) & 1;
			case 0xF0: return (cpu->mem.sfr.B >> bit_pos) & 1;
			case 0x82: return (cpu->mem.sfr.DPL >> bit_pos) & 1;
			case 0x83: return (cpu->mem.sfr.DPH >> bit_pos) & 1;
			case 0xA8: return (cpu->mem.sfr.IE >> bit_pos) & 1;
			case 0xB8: return (cpu->mem.sfr.IP >> bit_pos) & 1;
			case 0x87: return (cpu->mem.sfr.PCON >> bit_pos) & 1;
			case 0xD0: return (cpu->mem.sfr.PSW >> bit_pos) & 1;
			case 0x99: return (cpu->mem.sfr.SBUF >> bit_pos) & 1;
			case 0x98: return (cpu->mem.sfr.SCON >> bit_pos) & 1;
			case 0x81: return (cpu->mem.sfr.SP >> bit_pos) & 1;
			case 0x88: return (cpu->mem.sfr.TCON >> bit_pos) & 1;
			case 0x89: return (cpu->mem.sfr.TMOD >> bit_pos) & 1;
			case 0x8A: return (cpu->mem.sfr.TL0 >> bit_pos) & 1;
			case 0x8B: return (cpu->mem.sfr.TL1 >> bit_pos) & 1;
			case 0x8C: return (cpu->mem.sfr.TH0 >> bit_pos) & 1;
			case 0x8D: return (cpu->mem.sfr.TH1 >> bit_pos) & 1;
			default: return 0;
			
		}
		
	}
	return 0;

}

static uint8_t set_bit(cpu_t *cpu, uint8_t bit_addr, uint8_t value) {
	uint8_t byte_offset = bit_addr >> 3;
	uint8_t byte_addr = 0x20 +byte_offset;
	uint8_t bit_pos = bit_addr & 0x07;
	uint8_t byte = memory_read_data(cpu->mem, byte_addr);

	if (value) {
		byte |= (1 << bit_pos);
	} else {
		byte &= ~(1 << bit_pos);
		
	}
	
	memory_write_data(cpu->mem, byte_addr, byte);
}
