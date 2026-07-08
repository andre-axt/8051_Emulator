#ifdef EM8051_BITOPS_H 
#define EM8051_BITOPS_H

#include <stdint.h>

typedef struct Mcu8051_t Mcu8051_t;

int8_t get_bit(Mcu8051_t *mcu, uint8_t bit_addr);
void set_bit(Mcu8051_t *mcu, uint8_t bit_addr, uint8_t value);
uint8_t fetch_byte(Mcu8051_t *mcu);

#endif
