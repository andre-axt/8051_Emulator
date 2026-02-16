#include "timer.h"
#include "memory.h"
#include <stdlib.h>
#include <string.h>

int init_timers (timers_system_t *timers) {
	if(timers == NULL) return 1;

	timers->timer0 = 0;
	timers->timer1 = 0;

	return 0;

}

void update_timers(memory_t *mem, uint32_t cycles) {
	if (mem->timers == NULL) return;

	uint8_t tmod = mem->sfr.TMOD;
	uint8_t tcon = mem->sfr.TCON;

	if (tcon & TCON_TR0_MASK) {
		uint16_t t0 = mem->timers->timer0;
		uint8_t mode0 = tmod & 0x03; 
		
		t0 += cycles;
		switch(mode0) {
			case 0:
				if (t0 >= 0x1FFF) {
					t0 = 0;
					mem->sfr.TCON |= TCON_F0_MASK;
				}	
				break;

			case 1:
				if (t0 >= 0xFFFF) {
					t0 = 0;
					mem->sfr.TCON |= TCON_F0_MASK;
				}
				break;		
				
			case 2: 
				if (t0 >= 0x00FF) {
					t0 = (t0 & 0xFF00) + mem->sfr.THO;
					mem->sfr.TCON |= TCON_TF0_MASK;

				}
				break;
		}

		mem->timers->timer0 = t0;
		update_sfr_from_timer0(mem);
	
	}

	if (tcon & TCON_TR1_MASK) {
		uint16_t t1 = mem->timers->timer1;
		uint8_t mode1 = (tmod >> 4) & 0x03;
	
		t1 += cycles;
		switch(mode1) {
			case 0:
				if (t1 >= 0x1FFF) {
					t0 = 0;
					mem->sfr.TCON |= TCON_F1_MASK;
				}
				break;

			case 1:
				if (t1 >= 0xFFFF) {
					t0 = 0;
					mem->sfr.TCON |= TCON_F1_MASK;
				}
				break;
		
			case 2: 
				if (t1 >= 0x00FF) {
					t1 = (t1 & 0xFF00) + mem->sfr.TH1;
					mem->sfr.TCON |= TCON_TF1_MASK;
				}


		}

		mem->timers->timer1 = t1;
		update_sfr_from_timer1(mem);

	}


}
