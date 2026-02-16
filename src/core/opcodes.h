#ifndef OPCODES_H
#define OPCODES_H

#include "cpu.h"

typedef struct {
	char *mnemonic;
	uint8_t bytes;
	uint8_t cycles;
	void (*execute)(cpu_t *);

} instrunction_t;

extern instruction_t opcode_table[256];

void instr_nop(cpu_t *cpu);
void instr_ljmp(cpu_t *cpu);
void instr_sjmp(cpu_t *cpu);
void instr_ajmp(cpu_t *cpu);
void instr_mov_a_immed(cpu_t *cpu);
void instr_mov_direct_immed(cpu_t *cpu);
void instr_mov_a_direct(cpu_t *cpu);
void instr_mov_direct_a(cpu_t *cpu);
void instr_add_a_immed(cpu_t *cpu);
void instr_setb(cpu_t *cpu);
void instr_clr(cpu_t *cpu);
void instr_cpl(cpu_t *cpu);
void instr_jnb(cpu_t *cpu);
void instr_jb(cpu_t *cpu);
void instr_jbc(cpu_t *cpu);
void instr_anl_a_immed(cpu_t *cpu);
void instr_orl_a_immed(cpu_t *cpu);
void instr_xrl_a_immed(cpu_t *cpu);
void instr_inc_a(cpu_t *cpu);
void instr_dec_a(cpu_t *cpu);
void instr_push(cpu_t *cpu);
void instr_pop(cpu_t *cpu);
void instr_ret(cpu_t *cpu);
void instr_reti(cpu_t *cpu);

extern uint8_t fetch_byte(cpu_t *cpu);
extern uint16_t fetch_word(cpu_t *cpu);

#endif
