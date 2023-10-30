#ifndef DISASSEMBLER_FUNCS_H_INCLUDED
#define DISASSEMBLER_FUNCS_H_INCLUDED

#include <stdio.h>

enum commands {
    HLT = -1,
    PUSH = 1,
    IN = 2,
    OUT = 3,
    ADD = 4,
    SUB = 5,
    MUL = 6,
    DIV = 7,
    SQRT = 8,
    SIN = 9,
    COS = 10
};

int disassembler_translate(const char* input_name, const char* output_name);

int distranslate_push(FILE* byte_code, FILE* assembler_code);

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

#endif // DISASSEMBLER_FUNCS_H_INCLUDED
