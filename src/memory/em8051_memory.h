#ifndef EM8051_MEMORY_H
#define EM8051_MEMORY_H

#include <stdint.h>

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

}Internal_ram_t;

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

} Sfr_t;

typedef struct Memory_t {
	Internal_ram_t ram;
	Sfr_t sfr;
	uint8_t internal_rom[INTERNAL_ROM_SIZE];

} Memory_t;

Memory_t* memory_init();
uint8_t memory_read_code(Memory_t *mem, uint16_t address);
uint8_t memory_read_data(Memory_t *mem, uint8_t address);
void memory_write_data(Memory_t *mem, uint8_t address, uint8_t value);
int memory_load_program(Memory_t *mem, const uint8_t *program, uint16_t size, uint16_t start_address);
void stack_push_byte(Memory_t *mem, uint8_t value);
uint8_t stack_pop_byte(Memory_t *mem);
void stack_push_word(Memory_t *mem, uint16_t word); // 16-bit addresses
uint16_t stack_pop_word(Memory_t *mem);

#endif
