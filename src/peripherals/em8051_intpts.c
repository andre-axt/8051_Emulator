#include "em8051_types.h"
#include "em8051_cpu.h"
#include "em8051_intpts.h"
#include "em8051_memory.h"
#include <stdlib.h>

Interruptions_t* init_intpt(){
  Interruptions_t *interruptions;
  interruptions = malloc(sizeof(Interruptions_t));
  
  if(interruptions == NULL) return NULL;
  interruptions->intpts = 0;
  interruptions->debug_mode = 0;
  return interruptions;
  
}

int8_t check_intpt(Mcu8051_t *mcu) {
  if(mcu == NULL) return -1;

  uint8_t ip = mcu->mem->sfr.IP; 
  uint8_t ie = mcu->mem->sfr.IE;

  if (!(ie & IE_EA)) return 0;
  
  for (int i = 0; i <= 4; i++) {
    if(ip & (1 << i)) {
      return i + 1;
    }
  } 
  return 0;
  
}

int8_t get_priority_from_intpt(Mcu8051_t *mcu, int8_t handler) {
  if (handler == 0 || mcu == NULL) return -1;
    
  uint8_t ip = mcu->mem->sfr.IP;

  switch(handler) {
      case 1: return (ip & IP_PX0) ? 1 : 0;
      case 2: return (ip & IP_PT0) ? 1 : 0;
      case 3: return (ip & IP_PX1) ? 1 : 0;
      case 4: return (ip & IP_PT1) ? 1 : 0;
      case 5: return (ip & IP_PS)  ? 1 : 0;
  }
  return -1;
}

void lock_intpt(Mcu8051_t *mcu, int8_t handler) {
  if (handler == 0 || mcu == NULL) return;
  
  switch(handler) {
      case 1: mcu->cpu->PC = INT0;   return;
      case 2: mcu->cpu->PC = TIMER0; return;
      case 3: mcu->cpu->PC = INT1;   return;
      case 4: mcu->cpu->PC = TIMER1; return;
      case 5: mcu->cpu->PC = SERIAL; return;
  }

  return;
}

void set_intpt(Mcu8051_t *mcu, int8_t handler, uint8_t value) {
  if(handler == 0) return;
  if(value != 1 && value != 0) return;
  
  switch(handler) {
    case 1: mcu->intpt->intpts = (intpts & ~INTPTS_INT0) | (value & INTPTS_INT0) return;
    case 2: mcu->intpt->intpts = (intpts & ~INTPTS_TIMER0) | (value & INTPTS_TIMER0) return;
    case 3: mcu->intpt->intpts = (intpts & ~INTPTS_INT1) | (value & INTPTS_INT1) return;
    case 4: mcu->intpt->intpts = (intpts & ~INTPTS_TIMER1) | (value & INTPTS_TIMER1) return;
    case 5: mcu->intpt->intpts = (intpts & ~INTPTS_SERIAL) | (value & INTPTS_SERIAL) return;
    default: return;
      
  }
  
  return;
}
