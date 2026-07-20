#ifndef EM8051_OPCODES_H
#define EM8051_OPCODES_H

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
void instr_mov_acc_immed(Mcu8051_t *mcu);
void instr_mov_direct_immed(Mcu8051_t *mcu);
void instr_mov_acc_direct(Mcu8051_t *mcu);
void instr_mov_direct_acc(Mcu8051_t *mcu);
void instr_add_acc_immed(Mcu8051_t *mcu);
void instr_setb(Mcu8051_t *mcu);
void instr_clr_c(Mcu8051_t *mcu);
void instr_clr_acc(Mcu8051_t *mcu);
void instr_clr_bit(Mcu8051_t *mcu);
void instr_cpl(Mcu8051_t *mcu);
void instr_jnb(Mcu8051_t *mcu);
void instr_jb(Mcu8051_t *mcu);
void instr_jbc(Mcu8051_t *mcu);
void instr_jmp(Mcu8051_t *mcu);
void instr_anl_acc_immed(Mcu8051_t *mcu);
void instr_orl_acc_immed(Mcu8051_t *mcu);
void instr_xrl_acc_immed(Mcu8051_t *mcu);
void instr_inc_acc(Mcu8051_t *mcu);
void instr_inc_direct(Mcu8051_t *mcu);
void instr_dec_acc(Mcu8051_t *mcu);
void instr_push(Mcu8051_t *mcu);
void instr_pop(Mcu8051_t *mcu);
void instr_ret(Mcu8051_t *mcu);
void instr_reti(Mcu8051_t *mcu);
void instr_inc_rn(Mcu8051_t *mcu);

#endif
