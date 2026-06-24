#ifndef OPCODES_H
#define OPCODES_H

#include "cpu.h"

typedef struct {
	char *mnemonic;
	uint8_t bytes;
	uint8_t cycles;
	void (*execute)(Cpu_t *);

} Instruction_t;

extern Instruction_t opcode_table[256];

void instr_nop(Cpu_t *cpu);
void instr_ljmp(Cpu_t *cpu);
void instr_sjmp(Cpu_t *cpu);
void instr_ajmp(Cpu_t *cpu);
void instr_mov_a_immed(Cpu_t *cpu);
void instr_mov_direct_immed(Cpu_t *cpu);
void instr_mov_a_direct(Cpu_t *cpu);
void instr_mov_direct_a(Cpu_t *cpu);
void instr_add_a_immed(Cpu_t *cpu);
void instr_setb(Cpu_t *cpu);
void instr_clr(Cpu_t *cpu);
void instr_cpl(Cpu_t *cpu);
void instr_jnb(Cpu_t *cpu);
void instr_jb(Cpu_t *cpu);
void instr_jbc(Cpu_t *cpu);
void instr_anl_a_immed(Cpu_t *cpu);
void instr_orl_a_immed(Cpu_t *cpu);
void instr_xrl_a_immed(Cpu_t *cpu);
void instr_inc_a(Cpu_t *cpu);
void instr_dec_a(Cpu_t *cpu);
void instr_push(Cpu_t *cpu);
void instr_pop(Cpu_t *cpu);
void instr_ret(Cpu_t *cpu);
void instr_reti(Cpu_t *cpu);

extern uint8_t fetch_byte(Cpu_t *cpu);
extern uint16_t fetch_word(Cpu_t *cpu);

#endif
