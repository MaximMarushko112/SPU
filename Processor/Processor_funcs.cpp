#include <assert.h>
#include <math.h>
#include <stdio.h>
#include "../Commands.h"
#include "Processor_funcs.h"
#include "../Stack.h"

int processing(char* input_name) {
    assert(input_name != NULL);

    FILE* byte_code = fopen(input_name, "r");
    struct SPU SPU = {{0, NULL, 0, 0, NULL, 0, NULL, NULL, 0, 0, 0}, {}};
    STACK_CTOR(&SPU.stack);
    int command = 0;
    int scan = 0;

    while ((scan = fscanf(byte_code, "%d", &command)) != EOF) {
        if (scan == 0) {
            char str_command[100] = {};
            fscanf(byte_code, "%s", str_command);
            wrong_command(str_command);
            return 1;
        }
        else {
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
    }
    stack_dtor(&SPU.stack);
    for (int registr = 0; registr < NREG; registr++)
        SPU.registrs[registr] = 0;
    return 0;
}

int processor_push(FILE* byte_code, struct SPU* SPU) {
    assert(byte_code != NULL);
    assert(SPU != NULL);

    Elem_t x = 0;
    if (fscanf(byte_code, "%lf", &x) == 1)
        stack_push(&SPU->stack, x);
    else {
        wrong_push();
        return 1;
    }

    return 0;
}

int processor_pushr(FILE* byte_code, struct SPU* SPU) {
    assert(byte_code != NULL);
    assert(SPU != NULL);

    int registr = 0;
    if (fscanf(byte_code, "%d", &registr) == 1 && 0 <= registr && registr < NREG)
        stack_push(&SPU->stack, SPU->registrs[registr]);
    else {
        wrong_pushr();
        return 1;
    }

    return 0;
}

int processor_pop(FILE* byte_code, struct SPU* SPU) {
    assert(byte_code != NULL);
    assert(SPU != NULL);

    int registr = 0;
    if (fscanf(byte_code, "%d", &registr) == 1 && 0 <= registr && registr < NREG)
        stack_pop(&SPU->stack, &SPU->registrs[registr]);
    else {
        wrong_pop();
        return 1;
    }

    return 0;
}

void processor_in(struct SPU* SPU) {
    assert(SPU != NULL);

    Elem_t x = 0;
    scanf("%lf", &x);
    stack_push(&SPU->stack, x);
}

void processor_out(struct SPU* SPU) {
    assert(SPU != NULL);

    Elem_t x = 0;
    stack_pop(&SPU->stack, &x);
    printf("%lf", x);
    stack_push(&SPU->stack, x);
}

void processor_add(struct SPU* SPU) {
    assert(SPU != NULL);

    Elem_t first = 0, second = 0;
    stack_pop(&SPU->stack, &second);
    stack_pop(&SPU->stack, &first);
    stack_push(&SPU->stack, first + second);
}

void processor_sub(struct SPU* SPU) {
    assert(SPU != NULL);

    Elem_t first = 0, second = 0;
    stack_pop(&SPU->stack, &second);
    stack_pop(&SPU->stack, &first);
    stack_push(&SPU->stack, first - second);
}

void processor_mul(struct SPU* SPU) {
    assert(SPU != NULL);

    Elem_t first = 0, second = 0;
    stack_pop(&SPU->stack, &second);
    stack_pop(&SPU->stack, &first);
    stack_push(&SPU->stack, first * second);
}

void processor_div(struct SPU* SPU) {
    assert(SPU != NULL);

    Elem_t first = 0, second = 0;
    stack_pop(&SPU->stack, &second);
    stack_pop(&SPU->stack, &first);
    stack_push(&SPU->stack, first / second);
}

void processor_sqrt(struct SPU* SPU) {
    assert(SPU != NULL);

    Elem_t first = 0;
    stack_pop(&SPU->stack, &first);
    stack_push(&SPU->stack, sqrt(first));
}

void processor_sin(struct SPU* SPU) {
    assert(SPU != NULL);

    Elem_t first = 0;
    stack_pop(&SPU->stack, &first);
    stack_push(&SPU->stack, sin(first));
}

void processor_cos(struct SPU* SPU) {
    assert(SPU != NULL);

    Elem_t first = 0;
    stack_pop(&SPU->stack, &first);
    stack_push(&SPU->stack, cos(first));
}

void wrong_command(char* str_command) {
    assert(str_command != NULL);

    printf("WRONG COMMAND: %s\n", str_command);
}

void wrong_command_code(int command) {
    assert(command != 0);

    printf("WRONG COMMAND: %d\n", command);
}

void wrong_push() {
    fprintf(stderr, "WRONG PUSH\n");
}

void wrong_pushr() {
    fprintf(stderr, "WRONG PUSHR\n");
}

void wrong_pop() {
    fprintf(stderr, "WRONG POP\n");
}
