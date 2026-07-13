#include "em8051_types.h"
#include "em8051_cpu.h"
#include "em8051_memory.h"
#include "em8051_timers.h"
#include "em8051_intpts.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct Mcu8051_t Mcu8051_t;

void free_mcu(Mcu8051_t *mcu) {
    if (mcu) {
        if (mcu->cpu)    free(mcu->cpu);
        if (mcu->mem)    free(mcu->mem);
        if (mcu->timers) free(mcu->timers);
        if (mcu->intpt)  free(mcu->intpt);
        free(mcu);
    }
}

int main(int argc, char *argv[]){

	if (argc < 2) {
        fprintf(stderr, "Error: No ROM file path specified.\n");
        fprintf(stderr, "Usage: make run ROM=path/to/program.bin\n");
        return 1;
    }
	
	Mcu8051_t *mcu = malloc(sizeof(Mcu8051_t));
	if (mcu == NULL) return 1;
	
	mcu->cpu = cpu_init();
    mcu->mem = memory_init();
    mcu->timers = init_timers();
    mcu->intpt = init_intpt();

	if (!mcu->cpu || !mcu->mem || !mcu->timers || !mcu->intpt) {
        free_mcu(mcu);
        return 1;
    }

	FILE *rom_file = fopen(argv[1], "rb");
    if (rom_file == NULL) {
        perror("Error opening ROM file");
        free_mcu(mcu);
        return 1;
    }

	fseek(rom_file, 0, SEEK_END);
    long file_size = ftell(rom_file);
    fseek(rom_file, 0, SEEK_SET);

	if (file_size <= 0 || file_size > INTERNAL_ROM_SIZE) {
        fprintf(stderr, "Error: Invalid ROM size (%ld bytes). Maximum limit: %d bytes.\n", 
                file_size, INTERNAL_ROM_SIZE);
        fclose(rom_file);
        free_mcu(mcu);
        return 1;
    }

	uint8_t *rom_buffer = malloc(file_size);
    if (rom_buffer == NULL) {
        fclose(rom_file);
        free_mcu(mcu);
        return 1;
    }

	size_t bytes_read = fread(rom_buffer, 1, file_size, rom_file);
    fclose(rom_file);

    if (bytes_read != (size_t)file_size) {
        fprintf(stderr, "Error reading the complete ROM file content.\n");
        free(rom_buffer);
        free_mcu(mcu);
        return 1;
    }

	if (memory_load_program(mcu->mem, rom_buffer, (uint16_t)file_size, 0x0000) != 0) {
        fprintf(stderr, "Error mapping ROM into internal memory space.\n");
        free(rom_buffer);
        free_mcu(mcu);
        return 1;
    }

	free(rom_buffer);

	free_mcu(mcu);
	
}
