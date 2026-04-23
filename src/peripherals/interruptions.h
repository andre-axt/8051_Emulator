#ifndef INTERRUPTIONS_H
#define INTERRUPTIONS_H
#include <stdint.h>

#define INT0 0x03
#define TIMER0 0x0B
#define INT1 0x13
#define TIMER1 0x1B
#define SERIAL 0x23

typedef struct {
  int8_t INT0;
  int8_t Timer0;
  int8_t INT1;
  int8_t Timer1;
  int8_t Serial;
} Interruptions_t

int8_t init_int(Interruption *interruptions); //Just reset all interrupts to 1.
int8_t lock_int(Interruption *interruptions); //Currently, the idea is to set a signal to freeze and configure the PC according to the interrupt location.
