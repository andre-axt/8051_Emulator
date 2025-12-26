#ifndef TIMER_H
#define TIMER_H

#include <stdint.h>

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

typedef struct {
	uint8_t TH;
	uint8_t TL;

} timer_t;

typedef struct {
	timer_t timer0;
	timer_t timer1;
        uint8_t TCON;
        uint8_t TMOD;
	uint64_t total_cycles;	
} timers_system;


