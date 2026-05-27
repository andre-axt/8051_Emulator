#ifndef INTERRUPTIONS_H
#define INTERRUPTIONS_H
#include <stdint.h>

#define INT0 0x03
#define TIMER0 0x0B
#define INT1 0x13
#define TIMER1 0x1B
#define SERIAL 0x23

#define IE_EX0   (1 << 0)  
#define IE_ET0   (1 << 1) 
#define IE_EX1   (1 << 2)  
#define IE_ET1   (1 << 3)  
#define IE_ES    (1 << 4)  
#define IE_ET2   (1 << 5)  
#define IE_EA    (1 << 7)  

typedef struct {
  	int8_t INT0;
  	int8_t Timer0;
  	int8_t INT1;
  	int8_t Timer1;
  	int8_t Serial;
  	uint8_t *IE; 
	uint8_t *IP;
} Interruptions_t

int8_t init_int(Interruptions_t *interruptions); //Just reset all interrupts to 1
int8_t check_int(Interruptions_t *interruptions); 
int8_t lock_int(Interruptions_t *interruptions, int8_t handler); // 0 = nothing, 1 = INT0, 2 = Timer0, 3 = INT1, 4 = Timer1, 5 = Serial
