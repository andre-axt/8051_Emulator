#include "opcodes.h"
#include <stdio.h>

static uint8_t get_bit(cpu_t *cpu, uint8_t bit_addr) {
	if (bit_addr > 0x7F){
		printf("error: bit address");
		return 1;
	} 
	return uint8_t bit = cpu->mem->ram.bytes[bit_addr];

}

void instr_setb(cpu_t *cpu){
	
}
