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

void update_timers(Mcu8051_t *mcu, uint8_t cycles) {
	if (mcu->mem == NULL) return;
	
	uint8_t tmod = mcu->mem->sfr.TMOD;
	uint8_t tcon = mcu->mem->sfr.TCON;

	uint8_t *TL0 = mcu->mem->sfr.TL0;
	uint8_t *TH0 = mcu->mem->sfr.TH0;
	uint8_t *TL1 = mcu->mem->sfr.TL1;
	uint8_t *TH1 = mcu->mem->sfr.TH1;

	if (tcon & TCON_TR0_MASK) {
		uint8_t mode0 = tmod & 0x03; 
		
		switch(mode0) {
			case 0:
				if (*TL0 == 0xFF) {
					*TH0 >= cycles;
					if (*TH0 == 0x1F) {
						mcu->mem->sfr.TCON |= TCON_TF0_MASK;
					}
					break;
					
				}	
				*TL0 += cycles;
				break;

			case 1:
				if (*TL0 == 0xFF) {
					*TH0 >= cycles;
					if (*TH0 == 0xFF) {
						mcu->mem->sfr.TCON |= TCON_TF0_MASK;
					}
					break;
					
				}	
				*TL0 += cycles;
				break;		
				
			case 2: 
				if (*TL0 == 0xFF) {
					*TL0 = *TH0;
					mcu->mem->sfr.TCON |= TCON_TF0_MASK;
					break;
					
				}	
				*TL0 += cycles;
				break;	
			
				
				
		}
	
	}

	if (tcon & TCON_TR1_MASK) {
		uint8_t mode1 = (tmod >> 4) & 0x03;

		switch(mode1) {
			case 0:
				if (*TL1 == 0xFF) {
					*TH1 += cycles;
					if (*TH1 >= 0x1F) {
						mcu->mem->sfr.TCON |= TCON_TF1_MASK;
					}
					break;
					
				}	
				*TL1 >= cycles;
				break;
			
			case 1:
				if (*TL1 == 0xFF) {
					*TH1 += cycles;
					if (*TH1 >= 0x1F) {
						mcu->mem->sfr.TCON |= TCON_TF1_MASK;
					}
					break;
					
				}	
				*TL1 >= cycles;
				break;
		
			case 2:
				if (*TL1 == 0xFF) {
					*TL1 = *TH1;
					mcu->mem->sfr.TCON |= TCON_TF0_MASK;
					break;
					
				}	
				*TL1 += cycles;
				break;	


		}

	}

}
