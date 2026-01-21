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

static uint8_t memory_read_sfr(memory_t *mem, uint8_t address) {
	switch (address) {
        
		case 0x80: return mem->sfr.P0;
        	case 0x90: return mem->sfr.P1;
        	case 0xA0: return mem->sfr.P2;
        	case 0xB0: return mem->sfr.P3;
        
        	case 0xE0: return mem->sfr.ACC;
        	case 0xF0: return mem->sfr.B;
        	case 0x82: return mem->sfr.DPL;
        	case 0x83: return mem->sfr.DPH;
        	case 0xA8: return mem->sfr.IE;
        	case 0xB8: return mem->sfr.IP;
        	case 0x87: return mem->sfr.PCON;
        	case 0xD0: return mem->sfr.PSW;
        	case 0x99: return mem->sfr.SBUF;
        	case 0x98: return mem->sfr.SCON;
        	case 0x81: return mem->sfr.SP;
        
        	case 0x88: return mem->sfr.TCON;
        	case 0x89: return mem->sfr.TMOD;
        	case 0x8A: return mem->sfr.TL0;
        	case 0x8B: return mem->sfr.TL1;
       	 	case 0x8C: return mem->sfr.TH0;
        	case 0x8D: return mem->sfr.TH1;
        
        	default: return 0xFF;
    	}
}

uint8_t memory_read_data (memory_t *mem, uint8_t address) {
	if (address < 0x80) {
		return mem->ram.bytes[address];
	}	
	else {
		return memory_read_sfr(mem, address);
	}

}

static void memory_write_sfr (memory_t *mem, uint8_t address, uint8_t value) {
	switch (address) {
        	case 0x80: mem->sfr.P0 = value; break;
        	case 0x90: mem->sfr.P1 = value; break;
        	case 0xA0: mem->sfr.P2 = value; break;
        	case 0xB0: mem->sfr.P3 = value; break;
        	
		case 0xE0: mem->sfr.ACC = value; break;
        	case 0xF0: mem->sfr.B = value; break;
        	case 0x82: mem->sfr.DPL = value; break;
        	case 0x83: mem->sfr.DPH = value; break;
        	case 0xA8: mem->sfr.IE = value; break;
       		case 0xB8: mem->sfr.IP = value; break;
        	case 0x87: mem->sfr.PCON = value; break;
        	case 0xD0: mem->sfr.PSW = value; break;
        	case 0x99: mem->sfr.SBUF = value; break;
        	case 0x98: mem->sfr.SCON = value; break;
        	case 0x81: mem->sfr.SP = value; break;
        
		case 0x88: mem->sfr.TCON = value; break;
        	case 0x89: mem->sfr.TMOD = value; break;
        	case 0x8A: mem->sfr.TL0 = value; break;
        	case 0x8B: mem->sfr.TL1 = value; break;
        	case 0x8C: mem->sfr.TH0 = value; break;
        	case 0x8D: mem->sfr.TH1 = value; break;
        
        	default: break;
    	}
	
	if (mem->timers != NULL){
		switch (address) {
			case (0x88):
				mem->timers->TCON = value; 
				write_timers(mem->timers);
				break;

			case (0x89):
				mem->timers->TMOD = value;
				write_timers(mem->timers);	
				break;

			case 0x8A: case 0x8B: case 0x8C: case 0x8D:
				if (address == 0x8A) mem->timers->timer0.TL = value;
                		if (address == 0x8C) mem->timers->timer0.TH = value;
                		if (address == 0x8B) mem->timers->timer1.TL = value;
                		if (address == 0x8D) mem->timers->timer1.TH = value;
               			write_timers(mem->timers);
		}
	
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


