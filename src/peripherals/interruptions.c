#include "interruptions.h"

void init_int(Interruptions *interruptions){
  interruptions->INT0 = 1;
  interruptions->Timer0 = 1;
  interruptions->INT1 = 1;
  interruptions->Timer1 = 1;
  interruptions->Serial = 1;
  
}
