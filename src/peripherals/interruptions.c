#include "interruptions.h"

void init_int(Interruptions *interruptions){
  interruptions->INT0 = 1;
  interruptions->Timer0 = 1;
  interruptions->INT1 = 1;
  interruptions->Timer1 = 1;
  interruptions->Serial = 1;
  
}

inline void lock_int(uint16_t *pc, int8_t handler) {
  if(handler == 0) return;
  switch(handler) {
    case 1{
      *pc = INT0;
      return;
    }
    case 2{
      *pc = TIMER0;
      return;
    }
    case 3{
      *pc = INT1;
      return;
    }
    case 4{
      *pc = TIMER1;
      return;
    }
    case 5{
      *pc = SERIAL;
      return;
    }
  }
  return;
}

inline void set_int(Interruptions_t *interruptions, int8_t handler) {
  if(handler == 0) return;
  switch(handler) {
    case 1{
      interruptions->INT0 = 0;
      return;
    }
    case 2{
      interruptions->Timer0 = 0;
      return;
    }
    case 3{
      interruptions->INT1 = 0;
      return;
    }
    case 4{
      interruptions->Timer1 = 0;
      return;
    }
    case 5{
      interruptions->Serial = 0;
      return;
    }
    case 6{
      interruptions->EA = 0;
      return;
    }
  }
  return;
}
