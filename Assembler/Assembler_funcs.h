#ifndef ASSEMBLER_FUNCS_H_INCLUDED
#define ASSEMBLER_FUNCS_H_INCLUDED

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

int assembler_translate(const char* input_name, const char* output_name);

int translate_push(FILE* assembler_code, FILE* byte_code);

void translate_in(FILE* byte_code);

void translate_out(FILE* byte_code);

void translate_HLT(FILE* byte_code);

void translate_add(FILE* byte_code);

void translate_sub(FILE* byte_code);

void translate_mul(FILE* byte_code);

void translate_div(FILE* byte_code);

void translate_sqrt(FILE* byte_code);

void translate_sin(FILE* byte_code);

void translate_cos(FILE* byte_code);

void wrong_command(const char* command);

void wrong_push();

#endif // ASSEMBLER_FUNCS_H_INCLUDED
