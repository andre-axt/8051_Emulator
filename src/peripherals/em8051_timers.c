#include "em8051_timers.h"
#include "em8051_types.h"
#include "em8051_memory.h"
#include <stdlib.h>

Timers_system_t* init_timers() {
    Timers_system_t *timers = malloc(sizeof(Timers_system_t));
    if (timers == NULL) return NULL;
    return timers;
}

void update_timers(Mcu8051_t *mcu, uint8_t cycles) {
    if (mcu == NULL || mcu->mem == NULL || cycles == 0) return;

    uint8_t tmod = mcu->mem->sfr.TMOD;
    uint8_t tcon = mcu->mem->sfr.TCON;

    uint8_t *TL0 = &mcu->mem->sfr.TL0;
    uint8_t *TH0 = &mcu->mem->sfr.TH0;
    uint8_t *TL1 = &mcu->mem->sfr.TL1;
    uint8_t *TH1 = &mcu->mem->sfr.TH1;

    uint8_t mode0 = tmod & 0x03;
    uint8_t mode1 = (tmod >> 4) & 0x03;

    uint8_t ct0 = tmod & TMOD_C_T0_MASK; 
    uint8_t ct1 = tmod & TMOD_C_T1_MASK;

    if ((tcon & TCON_TR0_MASK) && !ct0) {
        if (mode0 == 0) {

            uint32_t timer_val = ((*TH0 << 5) | (*TL0 & 0x1F)) + cycles;
            if (timer_val > 0x1FFF) {
                mcu->mem->sfr.TCON |= TCON_TF0_MASK;
                timer_val %= 0x2000; 
            }
            *TL0 = timer_val & 0x1F;
            *TH0 = (timer_val >> 5) & 0xFF;
        } 
        else if (mode0 == 1) {

            uint32_t timer_val = ((*TH0 << 8) | *TL0) + cycles;
            if (timer_val > 0xFFFF) {
                mcu->mem->sfr.TCON |= TCON_TF0_MASK;
                timer_val %= 0x10000; 
            }
            *TL0 = timer_val & 0xFF;
            *TH0 = (timer_val >> 8) & 0xFF;
        } 
        else if (mode0 == 2) {
            uint32_t sum = *TL0 + cycles;
            if (sum > 0xFF) {
                mcu->mem->sfr.TCON |= TCON_TF0_MASK;
                uint32_t overflow = sum - 0x100;
                *TL0 = (*TH0 + overflow) & 0xFF;
            } else {
                *TL0 = sum & 0xFF;
            }
        } 
        else if (mode0 == 3) {
            uint32_t sum = *TL0 + cycles;
            if (sum > 0xFF) {
                mcu->mem->sfr.TCON |= TCON_TF0_MASK;
            }
            *TL0 = sum & 0xFF;
        }
    }

    if (mode0 == 3 && (tcon & TCON_TR1_MASK)) {
        uint32_t sum = *TH0 + cycles;
        if (sum > 0xFF) {
            mcu->mem->sfr.TCON |= TCON_TF1_MASK;
        }
        *TH0 = sum & 0xFF;
    }

    if (mode0 != 3 && (tcon & TCON_TR1_MASK) && !ct1) {
        if (mode1 == 0) {
            uint32_t timer_val = ((*TH1 << 5) | (*TL1 & 0x1F)) + cycles;
            if (timer_val > 0x1FFF) {
                mcu->mem->sfr.TCON |= TCON_TF1_MASK;
                timer_val %= 0x2000;
            }
            *TL1 = timer_val & 0x1F;
            *TH1 = (timer_val >> 5) & 0xFF;
        } 
        else if (mode1 == 1) {
            uint32_t timer_val = ((*TH1 << 8) | *TL1) + cycles;
            if (timer_val > 0xFFFF) {
                mcu->mem->sfr.TCON |= TCON_TF1_MASK;
                timer_val %= 0x10000;
            }
            *TL1 = timer_val & 0xFF;
            *TH1 = (timer_val >> 8) & 0xFF;
        } 
        else if (mode1 == 2) {
            uint32_t sum = *TL1 + cycles;
            if (sum > 0xFF) {
                mcu->mem->sfr.TCON |= TCON_TF1_MASK;
                uint32_t overflow = sum - 0x100;
                *TL1 = (*TH1 + overflow) & 0xFF;
            } else {
                *TL1 = sum & 0xFF;
            }
        }
    }
}
