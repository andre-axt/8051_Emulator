#ifndef EM8051_TYPES_H
#define EM8051_TYPES_H

typedef struct Cpu_t Cpu_t;
typedef struct Interruptions_t Interruptions_t;
typedef struct Memory_t Memory_t;
typedef struct Timers_system_t Timers_system_t;

typedef struct Mcu8051_t {
    Cpu_t *cpu;
    Memory_t *mem;
    Timers_system_t *timers;
    Interruptions_t *intpt;
} Mcu8051_t;

#endif
