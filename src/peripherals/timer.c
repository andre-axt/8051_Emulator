#include "timer.h"
#include "memory.h"
#include <stdlib.h>

int init_timers (timers_system_t *timers) {
	if(timers == NULL) return 1;

	memset(timers->timer0, 0, sizeof(uint16_t));
	memset(timers->timer1, 0, sizeof(uint16_t));

	return 0;

}

void update_timers(memory_t *mem, uint32_t cycles) {
	if (mem->timers == NULL) return;

	uint8_t tmod = mem->sfr.TMOD;
	uint8_t tcon = mem->sfr.TCON;

	if (tcon & TCON_TR0_MASK) {
		uint16_t *t0 = mem->timers->timer0;
		uint8_t mode0 = tmod & 0x03; 
		
		t0 += cycles;
		switch(mode0) {
			case 0:
				if (t0 >= 0x1FFF) {
					t0 = 0;
					tcon |= TCON_F0_MASK;
				}	
				break;

			case 1:
				if (t0 >= 0xFFFF) {
					t0 = 0;
					tcon |= TCON_F0_MASK;
				}
				break;		
		
		}
	
	}

	if (tcon & TCON_TR1_MASK) {
		uint16_t *t1 = mem->timers->timer1;
		uint8_t mode1 = (tmod1 >> 4) & 0x03;
	
		t1 += cycles;
		switch(mode1) {
			case 0:
				if (t1 >= 0x1FFF) {
					t0 = 0;
					tcon |= TCON_F0_MASK;
				}
				break;

			case 1:
				if (t1 >= 0xFFFF) {
					t0 = 0;
					tcon |= TCON_F0_MASK;
				}
				break;
		
		}

	}

}

