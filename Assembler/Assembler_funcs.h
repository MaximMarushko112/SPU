#ifndef ASSEMBLER_FUNCS_H_INCLUDED
#define ASSEMBLER_FUNCS_H_INCLUDED

#include <stdio.h>

int assembler_translate(const char* input_name, const char* output_name);

int translate_push(FILE* assembler_code, FILE* byte_code);

int translate_pushr(FILE* assembler_code, FILE* byte_code);

int translate_pop(FILE* assembler_code, FILE* byte_code);

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

void wrong_pushr();

void wrong_pop();

#endif // ASSEMBLER_FUNCS_H_INCLUDED
