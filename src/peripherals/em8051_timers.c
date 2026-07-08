#include "em8051_timers.h"
#include "em8051_types.h"
#include "em8051_memory.h"
#include <stdlib.h>
#include <string.h>

Timers_system_t* init_timers() {
	Timers_system_t *timers;
	timers = malloc(sizeof(Timers_system_t));
	if(timers == NULL) return NULL;

	return timers;
}

void update_timers(Mcu8051_t *mcu, uint32_t cycles) {
	if (mcu == NULL) return;

	uint8_t tmod = mcu->mem->sfr.TMOD;
	uint8_t tcon = mcu->mem->sfr.TCON;

	if (tcon & TCON_TR0_MASK) {
		uint16_t t0 = ((uint16_t)mcu->mem->sfr.TH0 << 8) | mcu->mem->sfr.TL0;
		uint8_t mode0 = tmod & 0x03; 
		
		t0 += cycles;
		switch(mode0) {
			case 0:
				if (t0 >= 0x1FFF) {
					t0 = 0;
					mcu->mem->sfr.TCON |= TCON_TF0_MASK;
				}	
				break;

			case 1:
				if (t0 >= 0xFFFF) {
					t0 = 0;
					mcu->mem->sfr.TCON |= TCON_TF0_MASK;
				}
				break;		
				
			case 2: 
				if (t0 >= 0x00FF) {
					t0 &= 0xFF00;
					mcu->mem->sfr.TCON |= TCON_TF0_MASK;

				}
				break;
		}

		mcu->mem->sfr.TH0 = (uint8_t)(t0 >> 8);
		mcu->mem->sfr.TL0 = (uint8_t)(t0 & 0xFF);
	
	}

	if (tcon & TCON_TR1_MASK) {
		uint16_t t1 = ((uint16_t)mcu->mem->sfr.TH1 << 8) | mcu->mem->sfr.TL1;
		uint8_t mode1 = (tmod >> 4) & 0x03;
	
		t1 += cycles;
		switch(mode1) {
			case 0:
				if (t1 >= 0x1FFF) {
					t1 = 0;
					mcu->mem->sfr.TCON |= TCON_TF1_MASK;
				}
				break;

			case 1:
				if (t1 >= 0xFFFF) {
					t1 = 0;
					mcu->mem->sfr.TCON |= TCON_TF1_MASK;
				}
				break;
		
			case 2: 
				if (t1 >= 0x00FF) {
					t1 &= 0xFF00;
					mcu->mem->sfr.TCON |= TCON_TF1_MASK;
				}


		}

		mcu->mem->sfr.TH1 = (uint8_t)(t1 >> 8);
		mcu->mem->sfr.TL1 = (uint8_t)(t1 & 0xFF);

	}

}
