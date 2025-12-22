#ifndef TIMER_H
#define TIMER_H

#include <stdint.h>

#define TMOD_ADDR 0x89
#define TCON_ADDR 0x88
#define TL0_ADDR 0x8A
#define TH0_ADDR 0x8C
#define TL1_ADDR 0x8B
#define TH1_ADDR 0x8D

typedef enum {
	TCON_TF1 = 7,
	TCON_TR1 = 6,
	TCON_TF0 = 5,
	TCON_TR0 = 4,
	TCON_IE1 = 3,
	TCON_IT1 = 2,
        TCON_IE0 = 1,
	TCON_IT0 = 0

} tcon_bits_t;


