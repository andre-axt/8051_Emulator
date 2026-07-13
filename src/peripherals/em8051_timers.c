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

	uint8_t *TL0 = &mcu->mem->sfr.TL0;
	uint8_t *TH0 = &mcu->mem->sfr.TH0;
	uint8_t *TL1 = &mcu->mem->sfr.TL1;
	uint8_t *TH1 = &mcu->mem->sfr.TH1;
	uint8_t *TCON_REG = &mcu->mem->sfr.TCON;

	uint8_t mode0 = (((tmod & TMOD_M1_0_MASK) << 1) | tmod & TMOD_M0_0_MASK);
	uint8_t mode1 = (((tmod & TMOD_M1_1_MASK) << 1) | tmod & TMOD_M0_1_MASK);

	if (mode0 != 3) {
        if (tcon & TCON_TR0_MASK) {
            if (mode0 == 0) {
                uint16_t timer_val = (*TH0 << 5) | (*TL0 & 0x1F);
                timer_val += cycles;
                *TL0 = timer_val & 0x1F;
                *TH0 = (timer_val >> 5) & 0xFF;
                if (timer_val > 0x1FFF) *TCON_REG |= TCON_TF0_MASK;
            } 
				
            else if (mode0 == 1) { 
                uint32_t timer_val = (*TH0 << 8) | *TL0;
                timer_val += cycles;
                *TL0 = timer_val & 0xFF;
                *TH0 = (timer_val >> 8) & 0xFF;
                if (timer_val > 0xFFFF) *TCON_REG |= TCON_TF0_MASK;
            } 
				
            else if (mode0 == 2) {
                uint16_t sum = *TL0 + cycles;
                if (sum > 0xFF) {
                    *TL0 = *TH0 + (sum - 0x100); 
                    *TCON_REG |= TCON_TF0_MASK;
                } else {
                    *TL0 = sum & 0xFF;
                }
            }
        }
    } 
	
	else {
        if (tcon & TCON_TR0_MASK) {
            uint16_t sum = *TL0 + cycles;
            *TL0 = sum & 0xFF;
            if (sum > 0xFF) *TCON_REG |= TCON_TF0_MASK;
        }

        if (tcon & TCON_TR1_MASK) {
            uint16_t sum = *TH0 + cycles;
            *TH0 = sum & 0xFF;
            if (sum > 0xFF) *TCON_REG |= TCON_TF1_MASK; 
        }
    }

    if (mode1 != 3) {

        if (tcon & TCON_TR1_MASK) {
            if (mode1 == 0) {
                uint16_t timer_val = (*TH1 << 5) | (*TL1 & 0x1F);
                timer_val += cycles;
                *TL1 = timer_val & 0x1F;
                *TH1 = (timer_val >> 5) & 0xFF;
                if (timer_val > 0x1FFF && mode0 != 3) *TCON_REG |= TCON_TF1_MASK;
            } 
				
            else if (mode1 == 1) {
                uint32_t timer_val = (*TH1 << 8) | *TL1;
                timer_val += cycles;
                *TL1 = timer_val & 0xFF;
                *TH1 = (timer_val >> 8) & 0xFF;
                if (timer_val > 0xFFFF && mode0 != 3) *TCON_REG |= TCON_TF1_MASK;
            } 
				
            else if (mode1 == 2) {
                uint16_t sum = *TL1 + cycles;
                if (sum > 0xFF) {
                    *TL1 = *TH1 + (sum - 0x100);
                    if (mode0 != 3) *TCON_REG |= TCON_TF1_MASK;
                } 
				
				else {
                    *TL1 = sum & 0xFF;
                }
            }
        }
    } 

}
