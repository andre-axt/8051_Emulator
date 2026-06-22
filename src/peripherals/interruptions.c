#include "interruptions.h"
#include <stdlib.h>

Interruptions_t* init_int(){
  Interruptions_t *interruptions;
  interruptions = malloc(sizeof(Interruptions_t));
  
  if(interruptions == NULL) return NULL;
  interruptions->Int0 = 1;
  interruptions->Timer0 = 1;
  interruptions->Int1 = 1;
  interruptions->Timer1 = 1;
  interruptions->Serial = 1;
  return interruptions;
  
}

int8_t get_priority(uint8_t *IP, int8_t handler) {
  if(handler == 0) return -1;
  switch(handler) {
    case 1: {
      if(*IP && IP_PX0) {
        return 1;
      }	
      return 0;
    }
    case 2: {
      if(*IP && IP_PT0) {
        return 1;
      }	
      return 0;
    }
    case 3: {
      if(*IP && IP_PX1) {
        return 1;
      }	
      return 0;
    }
    case 4: {
      if(*IP && IP_PT1) {
        return 1;
      }	
      return 0;
    }
    case 5: {
      if(*IP && IP_PS) {
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
    case 1: {
      *pc = INT0;
      return;
    }
    case 2: {
      *pc = TIMER0;
      return;
    }
    case 3: {
      *pc = INT1;
      return;
    }
    case 4: {
      *pc = TIMER1;
      return;
    }
    case 5: {
      *pc = SERIAL;
      return;
    }
  }
  return;
}

inline void set_int(Interruptions_t *interruptions, int8_t handler) {
  if(handler == 0) return;
  switch(handler) {
    case 1: {
      interruptions->Int0 = 0;
      return;
    }
    case 2: {
      interruptions->Timer0 = 0;
      return;
    }
    case 3: {
      interruptions->Int1 = 0;
      return;
    }
    case 4: {
      interruptions->Timer1 = 0;
      return;
    }
    case 5: {
      interruptions->Serial = 0;
      return;
    }
    case 6: {
      interruptions->IE = 0;
      return;
    }
  }
  return;
}
