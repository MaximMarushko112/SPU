#ifndef PROCESSOR_FUNCS_H_INCLUDED
#define PROCESSOR_FUNCS_H_INCLUDED

#include "../Commands.h"
#include "../Stack.h"

struct SPU {
    struct Stack stack;
    Elem_t registrs[NREG];
    size_t instructions_len;
    char* instructions;
    size_t id;
    size_t bin_shift;        //ip
};

int processing(char* byte_code);

int processor_push(FILE* byte_code, struct SPU* SPU, Commands_t* command);

int processor_pop(FILE* byte_code, struct SPU* SPU);

void processor_in(struct SPU* SPU);

void processor_out(struct SPU* SPU);

void processor_add(struct SPU* SPU);

void processor_sub(struct SPU* SPU);

void processor_mul(struct SPU* SPU);

void processor_div(struct SPU* SPU);

void processor_sqrt(struct SPU* SPU);

void processor_sin(struct SPU* SPU);

void processor_cos(struct SPU* SPU);

void wrong_command_code(Commands_t* command);

#endif // PROCESSOR_FUNCS_H_INCLUDED
