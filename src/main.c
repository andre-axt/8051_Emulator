#include "interruptions.h"
#include "timers.h"
#include "memory.h"
#include "cpu.h"

typedef struct {
	Interruptions_t *intpt;
	Timers_system_t *timers;
	Memory_t *mem;
	Cpu_t *cpu;
} 8051_t;

int main(){
	// nothing for now

}
