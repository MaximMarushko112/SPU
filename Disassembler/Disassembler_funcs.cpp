#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Commands.h"
#include "Disassembler_funcs.h"
#include "../Stack.h"

int disassembler_translate(const char* input_name, const char* output_name) {
    assert(input_name != NULL);
    assert(output_name != NULL);

    FILE* byte_code      = fopen(input_name, "r");
    FILE* assembler_code = fopen(output_name, "w");
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
                if (distranslate_push(byte_code, assembler_code) == 1) {
                    return 1;
                }
                break;
            case PUSHR:
                if (distranslate_pushr(byte_code, assembler_code) == 1) {
                    return 1;
                }
                break;
            case POP:
                if (distranslate_pop(byte_code, assembler_code) == 1) {
                    return 1;
                }
                break;
            case IN:
                distranslate_in(assembler_code);
                break;
            case OUT:
                distranslate_out(assembler_code);
                break;
            case HLT:
                distranslate_HLT(assembler_code);
                break;
            case ADD:
                distranslate_add(assembler_code);
                break;
            case SUB:
                distranslate_sub(assembler_code);
                break;
            case MUL:
                distranslate_mul(assembler_code);
                break;
            case DIV:
                distranslate_div(assembler_code);
                break;
            case SQRT:
                distranslate_sqrt(assembler_code);
                break;
            case SIN:
                distranslate_sin(assembler_code);
                break;
            case COS:
                distranslate_cos(assembler_code);
                break;
            default:
                wrong_command_code(command);
                return 1;
                break;
            }
        }
    }

    fclose(byte_code);
    fclose(assembler_code);

    return 0;
}

int distranslate_push(FILE* byte_code, FILE* assembler_code) {
    assert(assembler_code != NULL);
    assert(byte_code != NULL);

    Elem_t x = 0;
    if (fscanf(byte_code, "%lf", &x) == 1)
        fprintf(assembler_code, "push %lf\n", x);
    else {
        wrong_push();
        return 1;
    }

    return 0;
}

int distranslate_pushr(FILE* byte_code, FILE* assembler_code) {
    assert(assembler_code != NULL);
    assert(byte_code != NULL);

    int registr = 0;
    if (fscanf(byte_code, "%d", &registr) == 1) {
        switch (registr) {
        case A:
            fprintf(assembler_code, "pushr rax\n");
            break;
        case B:
            fprintf(assembler_code, "pushr rbx\n");
            break;
        case C:
            fprintf(assembler_code, "pushr rcx\n");
            break;
        case D:
            fprintf(assembler_code, "pushr rdx\n");
            break;
        default:
            wrong_registr(registr);
            return 1;
            break;
        }
    }
    else {
        wrong_push();
        return 1;
    }

    return 0;
}

int distranslate_pop(FILE* byte_code, FILE* assembler_code) {
    assert(assembler_code != NULL);
    assert(byte_code != NULL);

    int registr = 0;
    if (fscanf(byte_code, "%d", &registr) == 1) {
        switch (registr) {
        case A:
            fprintf(assembler_code, "pop rax\n");
            break;
        case B:
            fprintf(assembler_code, "pop rbx\n");
            break;
        case C:
            fprintf(assembler_code, "pop rcx\n");
            break;
        case D:
            fprintf(assembler_code, "pop rdx\n");
            break;
        default:
            wrong_registr(registr);
            return 1;
            break;
        }
    }
    else {
        wrong_pop();
        return 1;
    }

    return 0;
}

void distranslate_in(FILE* assembler_code) {
    assert(assembler_code != NULL);

    fprintf(assembler_code, "in\n");
}

void distranslate_out(FILE* assembler_code) {
    assert(assembler_code != NULL);

    fprintf(assembler_code, "out\n");
}

void distranslate_HLT(FILE* assembler_code) {
    assert(assembler_code != NULL);

    fprintf(assembler_code, "HLT\n");
}

void distranslate_add(FILE* assembler_code) {
    assert(assembler_code != NULL);

    fprintf(assembler_code, "add\n");
}

void distranslate_sub(FILE* assembler_code) {
    assert(assembler_code != NULL);

    fprintf(assembler_code, "sub\n");
}

void distranslate_mul(FILE* assembler_code) {
    assert(assembler_code != NULL);

    fprintf(assembler_code, "mul\n");
}

void distranslate_div(FILE* assembler_code) {
    assert(assembler_code != NULL);

    fprintf(assembler_code, "div\n");
}

void distranslate_sqrt(FILE* assembler_code) {
    assert(assembler_code != NULL);

    fprintf(assembler_code, "sqrt\n");
}

void distranslate_sin(FILE* assembler_code) {
    assert(assembler_code != NULL);

    fprintf(assembler_code, "sin\n");
}

void distranslate_cos(FILE* assembler_code) {
    assert(assembler_code != NULL);

    fprintf(assembler_code, "cos\n");
}

void wrong_command(char* str_command) {
    assert(str_command != NULL);

    fprintf(stderr, "WRONG COMMAND: %s\n", str_command);
}

void wrong_command_code(int command) {
    fprintf(stderr, "WRONG COMMAND: %d\n", command);
}

void wrong_push() {
    fprintf(stderr, "WRONG PUSH\n");
}

void wrong_pop() {
    fprintf(stderr, "WRONG POP\n");
}

void wrong_registr(int registr) {
    fprintf(stderr, "WRONG REGISTR: %d\n", registr);
}
