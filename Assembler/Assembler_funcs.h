#ifndef ASSEMBLER_FUNCS_H_INCLUDED
#define ASSEMBLER_FUNCS_H_INCLUDED

#include <stdio.h>
#include "../Commands.h"

int assembler_translate(const char* input_name, const char* output_name);

int translate_push(FILE* assembler_code, FILE* byte_code, Commands_t* command);

int translate_pop(FILE* assembler_code, FILE* byte_code, Commands_t* command);

void command_translate(FILE* byte_code, Commands_t* command);

void wrong_command(const char* command);

void wrong_push();

void wrong_pop();

#endif // ASSEMBLER_FUNCS_H_INCLUDED
