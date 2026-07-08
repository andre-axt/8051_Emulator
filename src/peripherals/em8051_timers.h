#ifndef EM8051_TIMERS_H
#define EM8051_TIMERS_H

#include <stdint.h>

typedef struct Mcu8051_t Mcu8051_t;

#define TMOD_ADDR 0x89
#define TCON_ADDR 0x88
#define TL0_ADDR 0x8A
#define TH0_ADDR 0x8C
#define TL1_ADDR 0x8B
#define TH1_ADDR 0x8D

#define TCON_TF1_MASK (1 << 7)
#define TCON_TR1_MASK (1 << 6)
#define TCON_TF0_MASK (1 << 5)
#define TCON_TR0_MASK (1 << 4)
#define TCON_IE1_MASK (1 << 3)
#define TCON_IT1_MASK (1 << 2)
#define TCON_IE0_MASK (1 << 1)
#define TCON_IT0_MASK (1 << 0)

#define TMOD_GATE1_MASK (1 << 7)
#define TMOD_C_T1_MASK (1 << 6)
#define TMOD_M1_1_MASK (1 << 5)
#define TMOD_M1_0_MASK (1 << 4) 
#define TMOD_GATE0_MASK (1 << 3)
#define TMOD_C_T0_MASK (1 << 2)
#define TMOD_M0_1_MASK (1 << 1)
#define TMOD_M0_0_MASK (1 << 0)

typedef struct Timers_system_t {
	//uint16_t timer0;
	//uint16_t timer1; I really don't know what I'm going to do here, probably add a few variables for future debugging or something like that.
		
} Timers_system_t;

Timers_system_t* init_timers();
void update_timers(Mcu8051_t *mcu, uint32_t cycles);

#endif
