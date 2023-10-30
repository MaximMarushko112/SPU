#ifndef PROCESSOR_FUNCS_H_INCLUDED
#define PROCESSOR_FUNCS_H_INCLUDED

#include "Stack.h"

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

int processing(char* byte_code);

int processor_push(FILE* byte_code, struct Stack* SPU);

void processor_in(struct Stack* SPU);

void processor_out(struct Stack* SPU);

void processor_add(struct Stack* SPU);

void processor_sub(struct Stack* SPU);

void processor_mul(struct Stack* SPU);

void processor_div(struct Stack* SPU);

void processor_sqrt(struct Stack* SPU);

void processor_sin(struct Stack* SPU);

void processor_cos(struct Stack* SPU);

void wrong_command(char* str_command);

void wrong_command_code(int command);

void wrong_push();

#endif // PROCESSOR_FUNCS_H_INCLUDED
