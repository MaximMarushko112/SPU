#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "../Commands.h"
#include "Processor_funcs.h"
#include "../Stack.h"
#include "../Text_funcs.h"

int processing(char* input_name) {
    assert(input_name != NULL);

    FILE* byte_code = fopen(input_name, "rb");
    struct SPU SPU = {{0, NULL, 0, 0, NULL, 0, NULL, NULL, 0, 0, 0}, {}, 0, NULL, 0, 0};
    STACK_CTOR(&SPU.stack);
    SPU.instructions_len = file_len(byte_code);
    SPU.instructions = (char*) calloc(SPU.instructions_len, sizeof(char));
    fread(SPU.instructions, sizeof(char), SPU.instructions_len, byte_code);
    int command = 0;

    while (SPU.bin_shift < SPU.instructions_len) {
        command = *((Commands_t*) (SPU.instructions + SPU.bin_shift));
        SPU.id++;
        SPU.bin_shift += sizeof(Commands_t);
        switch (command) {
            case PUSH:
                if (processor_push(byte_code, &SPU) == 1) {
                    return 1;
                }
                break;
            case PUSHR:
                if (processor_pushr(byte_code, &SPU) == 1) {
                    return 1;
                }
                break;
            case POP:
                if (processor_pop(byte_code, &SPU) == 1) {
                    return 1;
                }
                break;
            case IN:
                processor_in(&SPU);
                break;
            case OUT:
                processor_out(&SPU);
                break;
            case HLT:
                return 0;
                break;
            case ADD:
                processor_add(&SPU);
                break;
            case SUB:
                processor_sub(&SPU);
                break;
            case MUL:
                processor_mul(&SPU);
                break;
            case DIV:
                processor_div(&SPU);
                break;
            case SQRT:
                processor_sqrt(&SPU);
                break;
            case SIN:
                processor_sin(&SPU);
                break;
            case COS:
                processor_cos(&SPU);
                break;
            default:
                wrong_command_code(command);
                return 1;
                break;
        }
    }
    stack_dtor(&SPU.stack);
    free(SPU.instructions);
    return 0;
}

int processor_push(FILE* byte_code, struct SPU* SPU) {
    assert(byte_code != NULL);
    assert(SPU != NULL);

    Elem_t x = 0;
    x = *((Elem_t*) (SPU->instructions + SPU->bin_shift));
    SPU->id++;
    SPU->bin_shift += sizeof(Elem_t);
    stack_push(&SPU->stack, x);

    return 0;
}

int processor_pushr(FILE* byte_code, struct SPU* SPU) {
    assert(byte_code != NULL);
    assert(SPU != NULL);

    unsigned char registr = 0;
    registr = *((Registr_code_t*) (SPU->instructions + SPU->bin_shift));
    SPU->id++;
    SPU->bin_shift += sizeof(Registr_code_t);
    stack_push(&SPU->stack, SPU->registrs[registr]);

    return 0;
}

int processor_pop(FILE* byte_code, struct SPU* SPU) {
    assert(byte_code != NULL);
    assert(SPU != NULL);

    unsigned char registr = 0;
    registr = *((Registr_code_t*) (SPU->instructions + SPU->bin_shift));
    SPU->id++;
    SPU->bin_shift += sizeof(Registr_code_t);
    stack_pop(&SPU->stack, &SPU->registrs[registr]);

    return 0;
}

void processor_in(struct SPU* SPU) {
    assert(SPU != NULL);

    Elem_t x = 0;
    printf("ENTER YOUR NUMBER: ");
    scanf("%lf", &x);
    stack_push(&SPU->stack, x);
}

void processor_out(struct SPU* SPU) {
    assert(SPU != NULL);

    Elem_t x = 0;
    stack_pop(&SPU->stack, &x);
    printf("RESULT: %lg\n", x);
    stack_push(&SPU->stack, x);
}

#define BINARY_OPERATION(name, symbol)                  \
    void processor_##name(struct SPU* SPU) {            \
        assert(SPU != NULL);                            \
                                                        \
        Elem_t first = 0, second = 0;                   \
        stack_pop(&SPU->stack, &second);                \
        stack_pop(&SPU->stack, &first);                 \
        stack_push(&SPU->stack, first symbol second);   \
    }

BINARY_OPERATION(add, +)

BINARY_OPERATION(sub, -)

BINARY_OPERATION(mul, *)

BINARY_OPERATION(div, /)

#define UNARY_OPERATION(name)                   \
    void processor_##name(struct SPU* SPU) {    \
        assert(SPU != NULL);                    \
                                                \
        Elem_t first = 0;                       \
        stack_pop(&SPU->stack, &first);         \
        stack_push(&SPU->stack, name(first));   \
    }

UNARY_OPERATION(sqrt)

UNARY_OPERATION(sin)

UNARY_OPERATION(cos)

void wrong_command_code(int command) {
    assert(command != 0);

    printf("WRONG COMMAND: %d\n", command);
}
