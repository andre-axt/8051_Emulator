#include "em8051_types.h"
#include "em8051_cpu.h"
#include "em8051_memory.h"
#include "em8051_timers.h"
#include "em8051_intpts.h"
#include <stdlib.h>

typedef struct Mcu8051_t Mcu8051_t;

int main(){
	Mcu8051_t *mcu = malloc(sizeof(Mcu8051_t));
	if (mcu == NULL) return 1;
	
	mcu->cpu = cpu_init();
    mcu->mem = memory_init();
    mcu->timers = init_timers();
    mcu->intpt = init_intpt();

	if (!mcu->cpu || !mcu->mem || !mcu->timers || !mcu->intpt) {
        if (mcu->cpu){
			free(mcu->cpu);
		}
		if (mcu->mem){
			free(mcu->mem);
		}
		if (mcu->timers){
			free(mcu->timers);
		}
		if (mcu->intpt){
			free(mcu->intpt);
		}
		free(mcu);
        return 1;
	}
	
}
