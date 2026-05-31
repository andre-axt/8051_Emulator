#include "interruptions.h"

void init_int(Interruptions *interruptions){
  interruptions->INT0 = 1;
  interruptions->Timer0 = 1;
  interruptions->INT1 = 1;
  interruptions->Timer1 = 1;
  interruptions->Serial = 1;
  
}

int8_t get_priority(uint8_t *IP, int8_t handler) {
  if(handler == 0) return -1;
  switch(handler) {
    case 1 {
      if(*IP && P_PX0) {
        return 1;
      }	
      return 0;
    }
    case 2 {
      if(*IP && P_PT0) {
        return 1;
      }	
      return 0;
    }
    case 3 {
      if(*IP && P_PX1) {
        return 1;
      }	
      return 0;
    }
    case 4 {
      if(*IP && P_PT1) {
        return 1;
      }	
      return 0;
    }
    case 5 {
      if(*IP && P_PS) {
        return 1;
      }	
      return 0;
    }
  }

  return -1;
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
