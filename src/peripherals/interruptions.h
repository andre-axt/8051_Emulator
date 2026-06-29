#ifndef INTERRUPTIONS_H
#define INTERRUPTIONS_H
#include <stdint.h>
#include <stddef.h>

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
#define IE_EA    (1 << 7)

#define IP_PX0	 (1 << 0)
#define IP_PT0	 (1 << 1)
#define IP_PX1	 (1 << 2)
#define IP_PT1	 (1 << 3)
#define IP_PS	 (1 << 4)

typedef struct {
  	int8_t Int0;
  	int8_t Timer0;
  	int8_t Int1;
  	int8_t Timer1;
  	int8_t Serial;
  	uint8_t *IE; 
	uint8_t *IP;
} Interruptions_t;

Interruptions_t* init_intpt();
int8_t check_intpt(Interruptions_t *interruptions); // returns 0 = nothing, 1 = INT0, 2 = Timer0, 3 = INT1, 4 = Timer1, 5 = Serial 
int8_t get_priority_from_intpt(uint8_t *IP, int8_t handler);
inline void lock_intpt(uint16_t *pc, int8_t handler); // handler: 0 = nothing, 1 = INT0, 2 = Timer0, 3 = INT1, 4 = Timer1, 5 = Serial
inline void set_intpt(Interruptions_t *interruptions, int8_t handler); // set to 0, handler: 0 = nothing, 1 = INT0, 2 = Timer0, 3 = INT1, 4 = Timer1, 5 = Serial, 6 = EA
#endif
