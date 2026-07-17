#include "em8051_types.h"
#include "em8051_cpu.h"
#include "em8051_memory.h"
#include "em8051_timers.h"
#include "em8051_intpts.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct Mcu8051_t Mcu8051_t;

static int ends_with(const char *str, const char *suffix) {
    if (!str || !suffix) return 0;
    size_t lenstr = strlen(str);
    size_t lensuffix = strlen(suffix);
    if (lensuffix > lenstr) return 0;
    return strncmp(str + lenstr - lensuffix, suffix, lensuffix) == 0;
}

static uint8_t parse_hex_byte(const char *hex) {
    uint8_t val = 0;
    for (int i = 0; i < 2; i++) {
        char c = hex[i];
        uint8_t nibble = 0;
        if (c >= '0' && c <= '9') nibble = c - '0';
        else if (c >= 'A' && c <= 'F') nibble = c - 'A' + 10;
        else if (c >= 'a' && c <= 'f') nibble = c - 'a' + 10;
        val = (val << 4) | nibble;
    }
    return val;
}

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
        fprintf(stderr, "Error opening ROM file at path: '%s'\n", argv[1]);
		free_mcu(mcu);
        return 1;
    }

	uint8_t *rom_buffer = malloc(INTERNAL_ROM_SIZE);
    if (rom_buffer == NULL) {
        fclose(rom_file);
        free_mcu(mcu);
        return 1;
    }

	memset(rom_buffer, 0xFF, INTERNAL_ROM_SIZE);

	if (ends_with(argv[1], ".hex") || ends_with(argv[1], ".HEX")) {
        char line[256];
        int line_number = 0;

        while (fgets(line, sizeof(line), rom_file)) {
            line_number++;
            
            char *start = strchr(line, ':');
            if (!start) continue; 
            
            start++; 

            if (strlen(start) < 10) continue;

            uint8_t byte_count = parse_hex_byte(start);
            uint16_t address = (parse_hex_byte(start + 2) << 8) | parse_hex_byte(start + 4);
            uint8_t record_type = parse_hex_byte(start + 6);

            if (record_type == 0x00) {
                for (int i = 0; i < byte_count; i++) {
                    if (address + i < INTERNAL_ROM_SIZE) {
                        rom_buffer[address + i] = parse_hex_byte(start + 8 + (i * 2));
                    } else {
                        fprintf(stderr, "Warning: Address 0x%04X exceeds INTERNAL_ROM_SIZE at line %d\n", address + i, line_number);
                    }
                }
            }
            else if (record_type == 0x01) {
                break; 
            }
        }
    } else {
        size_t bytes_read = fread(rom_buffer, 1, INTERNAL_ROM_SIZE, rom_file);
        
        if (bytes_read == 0 && ferror(rom_file)) {
            fprintf(stderr, "Error reading binary ROM file.\n");
            fclose(rom_file);
            free(rom_buffer);
            free_mcu(mcu);
            return 1;
        }
        
        printf("Loaded %zu bytes from binary ROM.\n", bytes_read);
    }

    fclose(rom_file);

    if (memory_load_program(mcu->mem, rom_buffer, INTERNAL_ROM_SIZE, 0x0000) != 0) {
        fprintf(stderr, "Error mapping ROM into internal memory space.\n");
        free(rom_buffer);
        free_mcu(mcu);
        return 1;
    }

    free(rom_buffer);

    while (!mcu->cpu->halted) {
        getchar();
        cpu_step(mcu);
    }

    free_mcu(mcu);
    return 0;
}
