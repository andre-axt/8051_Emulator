#include "interruptions.h"
#include "timers.h"
#include "memory.h"
#include "cpu.h"

typedef struct {
	Interruptions_t *intpt;
	Timers_system_t *timers;
	Memory_t *mem;
	Cpu_t *cpu;
} 8051_t; // It will stay here until I think of a better place to put this struct.

8051_t *8051;

int main(){
	8051 = malloc(sizeof(8051_t);
	if (8051 == NULL) return 1;
	8051->cpu = cpu_init();
	if (8051->cpu == NULL){
		free(8051);
		return 1;
	}
	8051->mem = memory_init();
	if (8051->mem == NULL){
		free(8051->cpu);
		free(8051);
		return 1;
	} 
	8051->timers = init_timers();
	if (8051->timers == NULL){
		free(8051->cpu);
		free(8051->mem);
		free(8051);
		return 1;
	} 
	&8051->mem->sfr.TL0 = (uint8_t *)&8051->timers->timer0;
	&8051->mem->sfr.TH0 = ((uint8_t *)&8051->timers->timer0) + 1;
	&8051->mem->sfr.TL1 = (uint8_t *)&8051->timers->timer1;
	&8051->mem->sfr.TH1 = ((uint8_t *)&8051->timers->timer1) + 1;
	8051->intpt = init_int();
	if (8051->inipt == NULL){
		free(8051->cpu);
		free(8051->mem);
		free(8051->timers);
		free(8051);
		return 1;
	} 
	
}
