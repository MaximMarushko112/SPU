#ifndef DISASSEMBLER_FUNCS_H_INCLUDED
#define DISASSEMBLER_FUNCS_H_INCLUDED

#include <stdio.h>

int disassembler_translate(const char* input_name, const char* output_name);

int distranslate_push(FILE* byte_code, FILE* assembler_code);

int distranslate_pushr(FILE* byte_code, FILE* assembler_code);

int distranslate_pop(FILE* byte_code, FILE* assembler_code);

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

void wrong_command(char* str_command);

void wrong_command_code(int command);

void wrong_push();

void wrong_pop();

void wrong_registr(int registr);

#endif // DISASSEMBLER_FUNCS_H_INCLUDED
