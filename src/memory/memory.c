#include "memory.h"
#include <stdlib.c>

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

	mem->external_rom = NULL;
	mem->external_ram = NULL;

	mem->code_space = NULL;
	mem->data_space = NULL;

	mem->timers = NULL;
}
