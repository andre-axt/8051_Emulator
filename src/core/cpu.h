#ifndef CPU_H
#define CPU_H
#include <stdint.h>


typedef struct {
	uint8_t p : 1;
	uint8_t    : 1;
	uint8_t ov : 1;
	uint8_t rs0 : 1;
	uint8_t rs1 : 1;
	uint8_t f0 : 1;
	uint8_t ac : 1;
	uint8_t cy : 1;
} psw_t;

#define PSW_TO_BYTE(psw) (*(uint8_t*)&(psw))
#define BYTE_TO_PSW(byte) (*(psw_t*)&(byte))

typedef struct {
	uint8_t acc;
	uint8_t b;
	uint16_t dptr;
        uint16_t pc;
	uint8_t sp;
	psw_t psw;
		
	union {
		uint8_t r[32];
		struct {
			uint8_t bank0[8];
			uint8_t bank1[8];
			uint8_t bank2[8];
			uint8_t bank3[8];
		};
	} regs;
	 

}
