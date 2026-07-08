#ifndef OPCODES_H
#define OPCODES_H

#include <stdint.h>

typedef struct Mcu8051_t Mcu8051_t;

typedef struct {
	char *mnemonic;
	uint8_t bytes;
	uint8_t cycles;
	void (*execute)(Mcu8051_t *);

} Instruction_t;

extern Instruction_t opcode_table[256];

void instr_nop(Mcu8051_t *mcu);
void instr_ljmp(Mcu8051_t *mcu);
void instr_sjmp(Mcu8051_t *mcu);
void instr_ajmp(Mcu8051_t *mcu);
void instr_mov_a_immed(Mcu8051_t *mcu);
void instr_mov_direct_immed(Mcu8051_t *mcu);
void instr_mov_a_direct(Mcu8051_t *mcu);
void instr_mov_direct_a(Mcu8051_t *mcu);
void instr_add_a_immed(Mcu8051_t *mcu);
void instr_setb(Mcu8051_t *mcu);
void instr_clr(Mcu8051_t *mcu);
void instr_cpl(Mcu8051_t *mcu);
void instr_jnb(Mcu8051_t *mcu);
void instr_jb(Mcu8051_t *mcu);
void instr_jbc(Mcu8051_t *mcu);
void instr_anl_a_immed(Mcu8051_t *mcu);
void instr_orl_a_immed(Mcu8051_t *mcu);
void instr_xrl_a_immed(Mcu8051_t *mcu);
void instr_inc_a(Mcu8051_t *mcu);
void instr_dec_a(Mcu8051_t *mcu);
void instr_push(Mcu8051_t *mcu);
void instr_pop(Mcu8051_t *mcu);
void instr_ret(Mcu8051_t *mcu);
void instr_reti(Mcu8051_t *mcu);

extern uint8_t fetch_byte(Mcu8051_t *mcu);
extern uint16_t fetch_word(Mcu8051_t *mcu);

#endif
