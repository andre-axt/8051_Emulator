#include "em8051_memory.h"
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>

Memory_t* memory_init(){
	Memory_t *mem = malloc(sizeof(Memory_t));

	if (mem == NULL) return NULL;

	memset(mem, 0, sizeof(Memory_t));
	memset(&(mem->ram), 0, sizeof(Internal_ram_t));
	memset(&(mem->internal_rom), 0, INTERNAL_ROM_SIZE);

	#ifdef DEBUG_MEMORY
		mem->debug_mode = 1;
	#else
		mem->debug_mode = 0;
	#endif

	mem->sfr.SP = 0x07;
	mem->sfr.PSW = 0x00;
	mem->sfr.IE = 0x00;
	mem->sfr.IP = 0x00;
	mem->sfr.TCON = 0x00;
	mem->sfr.TMOD = 0x00;
	mem->sfr.PCON = 0x00;
	mem->sfr.ACC = 0x00;
	mem->sfr.B = 0x00;
	mem->sfr.SBUF = 0x00;
	mem->sfr.SCON = 0x00;
	mem->sfr.DPH = 0x00;
	mem->sfr.DPL = 0x00;
	
	mem->sfr.TL0 = 0x00;
	mem->sfr.TH0 = 0x00;
	mem->sfr.TL1 = 0x00;
	mem->sfr.TH1 = 0x00;
		
	mem->sfr.P0 = 0xFF;	
	mem->sfr.P1 = 0xFF;
	mem->sfr.P2 = 0xFF;
	mem->sfr.P3 = 0xFF;

	return mem;
}

uint8_t memory_read_code (Memory_t *mem, uint16_t address) {
	if(address < INTERNAL_ROM_SIZE){
		return mem->internal_rom[address];
	}
	return 0xFF;

}

static uint8_t memory_read_sfr(Memory_t *mem, uint8_t address) {
	switch (address) {
        
		case P0_ADDR:   return mem->sfr.P0;
		case P1_ADDR:   return mem->sfr.P1;
		case P2_ADDR:   return mem->sfr.P2;
		case P3_ADDR:   return mem->sfr.P3;
        
		case ACC_ADDR:  return mem->sfr.ACC;
		case B_ADDR:    return mem->sfr.B;
		case DPL_ADDR:  return mem->sfr.DPL;
		case DPH_ADDR:  return mem->sfr.DPH;
		case IE_ADDR:   return mem->sfr.IE;
		case IP_ADDR:   return mem->sfr.IP;
		case PCON_ADDR: return mem->sfr.PCON;
		case PSW_ADDR:  return mem->sfr.PSW;
		case SBUF_ADDR: return mem->sfr.SBUF;
		case SCON_ADDR: return mem->sfr.SCON;
		case SP_ADDR:   return mem->sfr.SP;
        
		case TCON_ADDR: return mem->sfr.TCON;
		case TMOD_ADDR: return mem->sfr.TMOD;
		case TL0_ADDR:  return mem->sfr.TL0;
		case TL1_ADDR:  return mem->sfr.TL1;
		case TH0_ADDR:  return mem->sfr.TH0;
		case TH1_ADDR:  return mem->sfr.TH1;
        
		default: return 0xFF;
    }
}

uint8_t memory_read_data (Memory_t *mem, uint8_t address) {
	if (address < 0x80) {
		uint8_t value = mem->ram.bytes[address];
		if(mem->debug_mode) printf("memory_read_data returned - %d", value);
		return value;
	}	
	else {
		uint8_t value = memory_read_sfr(mem, address);
		if(mem->debug_mode) printf("memory_read_data returned - %d", value);
		return value;
	}

}

static void memory_write_sfr (Memory_t *mem, uint8_t address, uint8_t value) {
	switch (address) {
		case P0_ADDR:   mem->sfr.P0 = value; break;
		case P1_ADDR:   mem->sfr.P1 = value; break;
		case P2_ADDR:   mem->sfr.P2 = value; break;
		case P3_ADDR:   mem->sfr.P3 = value; break;
        	
		case ACC_ADDR:  mem->sfr.ACC = value; break;
		case B_ADDR:    mem->sfr.B = value; break;
		case DPL_ADDR:  mem->sfr.DPL = value; break;
		case DPH_ADDR:  mem->sfr.DPH = value; break;
		case IE_ADDR:   mem->sfr.IE = value; break;
		case IP_ADDR:   mem->sfr.IP = value; break;
		case PCON_ADDR: mem->sfr.PCON = value; break;
		case PSW_ADDR:  mem->sfr.PSW = value; break;
		case SBUF_ADDR: mem->sfr.SBUF = value; break;
		case SCON_ADDR: mem->sfr.SCON = value; break;
		case SP_ADDR:   mem->sfr.SP = value; break;
        
		case TCON_ADDR: mem->sfr.TCON = value; break;
		case TMOD_ADDR: mem->sfr.TMOD = value; break;
		case TL0_ADDR:  mem->sfr.TL0 = value; break;
		case TL1_ADDR:  mem->sfr.TL1 = value; break;
		case TH0_ADDR:  mem->sfr.TH0 = value; break;
		case TH1_ADDR:  mem->sfr.TH1 = value; break;
        
		default: break;
    }

}

void memory_write_data (Memory_t *mem, uint8_t address, uint8_t value) {
	if (address < 0x80) {
		mem->ram.bytes[address] = value;
	}
	else {
		memory_write_sfr(mem, address, value);
	
	}

}

int8_t memory_load_program (Memory_t *mem, const uint8_t *program, const uint16_t size, const uint16_t start_address) {
	if (mem == NULL || program == NULL || size == 0) {
		return -1;
	
	}

	if (start_address + size <= INTERNAL_ROM_SIZE) {
		memcpy(&(mem->internal_rom[start_address]), program, size);
		return 0;
	}

	return 1;

}

void stack_push_byte(Memory_t *mem, uint8_t value) {
	mem->sfr.SP++;
	memory_write_data(mem, mem->sfr.SP, value);
}

uint8_t stack_pop_byte(Memory_t *mem) {
    uint8_t value = memory_read_data(mem, mem->sfr.SP);
    mem->sfr.SP--; 
    return value;
}

void stack_push_word(Memory_t *mem, uint16_t word) {
    stack_push_byte(mem, word & 0xFF);         
    stack_push_byte(mem, (word >> 8) & 0xFF);  
}

uint16_t stack_pop_word(Memory_t *mem) {
    uint8_t high = stack_pop_byte(mem);        
    uint8_t low = stack_pop_byte(mem);         
    return (uint16_t)((high << 8) | low);
}
