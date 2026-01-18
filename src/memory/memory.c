#include "memory.h"

#include <stdlib.h>
#include <string.h>
#include <stdint.h>

void memory_init(memory_t *mem){
	if (mem == NULL) return;

	memset(mem, 0, sizeof(memory_t));

	memset(mem->ram, 0, sizeof(internal_ram_t);
	memset(mem->rom, 0, INTERNAL_ROM_SIZE);
	mem->ram.current_bank = 0;

	mem->sfr.SP = 0x07;
	mem->sfr.PSW = 0x00;
	mem->sfr.IE = 0x00;
	mem->sfr.IP = 0x00;
	mem->sfr.TCON = 0x00;
	mem->sfr.TMOD = 0x00;
	mem->sfr.PCON = 0x00;
	mem->sfr.ACC = 0x00;
	mem->sfr.B = 0x00;
	mem->sfr.DPTR = 0x00;
	mem->sfr.SBUF = 0x00;
	mem->sfr.SCON = 0x00;
	mem->sfr.TH0 = 0x00;
	mem->sfr.TL0 = 0x00;
	mem->sfr.TH1 = 0x00;
	mem->sfr.TL1 = 0x00;
	mem->sfr.DPH = 0x00;
	mem->sfr.DPL = 0x00;

		
	mem->sfr.P0 = 0xFF;	
	mem->sfr.P1 = 0xFF;
	mem->sfr.P2 = 0xFF;
	mem->sfr.P3 = 0xFF;

	mem->ram.current_bank = 0;

	mem->timers = NULL;
}

uint8_t memory_read_code (memory_t *mem, uint16_t address) {
	if(address < INTERNAL_ROM_SIZE){
		return mem->internal_rom[address];
	}
	return 0xFF;

}

uint8_t memory_read_data (memory_t *mem, uint8_t address) {
	if (address < 0x80) {
		return mem->ram.bytes[address];
	}	
	else {
		return memory_read_sfr(mem, address);
	}

}

uint8_t memory_write_data (memory_t *mem, uint8_t address, uint8_t value) {
	if (address < 0x80) {
		mem->ram.bytes[address] = value;
	}
	else {
		memory_write_sfr(mem, address, value);
	
	}

}

int memory_load_program (memory_t *mem, const uint8_t program, const uint16_t size, const uint16_t start_address) {
	if (mem == NULL || program == NULL || size == 0) {
		return -1;
	
	}

	if (start_address + size < INTERNAL_ROM_SIZE) {
		memcpy(mem->internal_rom[start_address], program, size);
		return 0;
	}

	return 1;

}


