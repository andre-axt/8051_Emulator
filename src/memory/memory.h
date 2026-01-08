#ifndef MEMORY_H
#define MEMORY_H

#include <stdint.h>
#include <timer.h>

#define INTERNAL_ROM_SIZE 4096
#define INTERNAL_RAM_SIZE 128
#define SFR_SIZE 128
#define TOTAL_ADDRESS_SPACE 65536

typedef struct {
	uint8_t raw[INTERNAL_RAM_SIZE];

	union {
		struct {
			uint8_t banks[4][8];
			uint8_t bit_addressable[16];
			uint8_t general_ram[80];

		};
		uint8_t bytes[INTERNAL_RAM_SIZE];
	
	};
	uint8_t current_bank;

}internal_ram_t;

typedef struct {
	uint8_t ACC;
	uint8_t B;

	uint8_t DPH;
	uint8_t DPL;

	uint8_t IE;
	uint8_t IP;

	uint8_t P0;
	uint8_t P1;
	uint8_t P2;
	uint8_t P3;

	uint8_t PCON;
	uint8_t PSW;

	uint8_t SCON;
	uint8_t SBUF;

	uint8_t SP;

	uint8_t TMOD;
	uint8_t TCON;
	uint8_t TL0;
	uint8_t TH0;
	uint8_t TL1;
	uint8_t TH1;

} sfr_t;

typedef struct {
	internal_ram_t ram;
	sfr_t sfr;
	uint8_t internal_rom[INTERNAL_ROM_SIZE];

	uint8_t *external_rom;
	uint8_t *external_ram;

	struct {
		uint8_t *code_space;
		uint8_t *data_space;

	}
	timer_system_t *timers;


} memory_t;

void memory_init(memory_t *mem);

#endif
