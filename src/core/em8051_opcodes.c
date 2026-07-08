#include "em8051_opcodes.h"
#include "em8051_types.h"
#include "em8051_memory.h"
#include "em8051_cpu.h"
#include "em8051_bitops.h"
#include <stdio.h>

void instr_nop(Mcu8051_t *mcu) {
	mcu->cpu->PC++;
	return;
}
