#ifndef DISASSEMBLER_FUNCS_H_INCLUDED
#define DISASSEMBLER_FUNCS_H_INCLUDED

#include <stdio.h>
#include "../Commands.h"

struct bin {
    char* bin_file;
    size_t bin_file_len;
    size_t id;
    size_t bin_shift;
};

int disassembler_translate(const char* input_name, const char* output_name);

int distranslate_push(bin* code, FILE* assembler_code, Commands_t* command);

int distranslate_pop(bin* code, FILE* assembler_code);

void distranslate_in(FILE* assembler_code);

void distranslate_out(FILE* assembler_code);

void distranslate_HLT(FILE* assembler_code);

void distranslate_add(FILE* assembler_code);

void distranslate_sub(FILE* assembler_code);

void distranslate_mul(FILE* assembler_code);

void distranslate_div(FILE* assembler_code);

void distranslate_sqrt(FILE* assembler_code);

void distranslate_sin(FILE* assembler_code);

void distranslate_cos(FILE* assembler_code);

void wrong_command_code(Commands_t* command);

void wrong_registr(unsigned char registr);

#endif // DISASSEMBLER_FUNCS_H_INCLUDED
