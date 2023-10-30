#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Disassembler_funcs.h"
#include "Stack.h"

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
                    wrong_push();
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
        fprintf(assembler_code, "%s %lf\n", "push", x);
    else {
        wrong_push();
        return 1;
    }

    return 0;
}

void distranslate_in(FILE* assembler_code) {
    assert(assembler_code != NULL);

    fprintf(assembler_code, "%s\n", "in");
}

void distranslate_out(FILE* assembler_code) {
    assert(assembler_code != NULL);

    fprintf(assembler_code, "%s\n", "out");
}

void distranslate_HLT(FILE* assembler_code) {
    assert(assembler_code != NULL);

    fprintf(assembler_code, "%s\n", "HLT");
}

void distranslate_add(FILE* assembler_code) {
    assert(assembler_code != NULL);

    fprintf(assembler_code, "%s\n", "add");
}

void distranslate_sub(FILE* assembler_code) {
    assert(assembler_code != NULL);

    fprintf(assembler_code, "%s\n", "sub");
}

void distranslate_mul(FILE* assembler_code) {
    assert(assembler_code != NULL);

    fprintf(assembler_code, "%s\n", "mul");
}

void distranslate_div(FILE* assembler_code) {
    assert(assembler_code != NULL);

    fprintf(assembler_code, "%s\n", "div");
}

void distranslate_sqrt(FILE* assembler_code) {
    assert(assembler_code != NULL);

    fprintf(assembler_code, "%s\n", "sqrt");
}

void distranslate_sin(FILE* assembler_code) {
    assert(assembler_code != NULL);

    fprintf(assembler_code, "%s\n", "sin");
}

void distranslate_cos(FILE* assembler_code) {
    assert(assembler_code != NULL);

    fprintf(assembler_code, "%s\n", "cos");
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
    printf("WRONG PUSH\n");
}