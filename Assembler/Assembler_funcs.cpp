#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Assembler_funcs.h"

int assembler_translate(const char* input_name, const char* output_name) {
    assert(input_name != NULL);
    assert(output_name != NULL);

    FILE* assembler_code = fopen(input_name, "r");
    FILE* byte_code      = fopen(output_name, "w");
    char command[10] = "";

    while (fscanf(assembler_code, "%s", command) != EOF) {
        if (strcmp(command, "push") == 0) {
            if (translate_push(assembler_code, byte_code) == 1) {
                return 1;
            }
        }
        else if (strcmp(command, "in") == 0) {
            translate_in(byte_code);
        }
        else if (strcmp(command, "out") == 0) {
            translate_out(byte_code);
        }
        else if (strcmp(command, "HLT") == 0) {
            translate_HLT(byte_code);
        }

        else if (strcmp(command, "add") == 0) {
            translate_add(byte_code);
        }
        else if (strcmp(command, "sub") == 0) {
            translate_sub(byte_code);
        }
        else if (strcmp(command, "mul") == 0) {
            translate_mul(byte_code);
        }
        else if (strcmp(command, "div") == 0) {
            translate_div(byte_code);
        }

        else if (strcmp(command, "sqrt") == 0) {
            translate_sqrt(byte_code);
        }
        else if (strcmp(command, "sin") == 0) {
            translate_sin(byte_code);
        }
        else if (strcmp(command, "cos") == 0) {
            translate_cos(byte_code);
        }

        else {
            wrong_command(command);
            return 1;
        }
    }

    fclose(assembler_code);
    fclose(byte_code);

    return 0;
}

int translate_push(FILE* assembler_code, FILE* byte_code) {
    assert(assembler_code != NULL);
    assert(byte_code != NULL);

    long x = 0;
    if (fscanf(assembler_code, "%ld", &x) == 1)
        fprintf(byte_code, "%d %ld\n", PUSH, x);
    else {
        wrong_push();
        return 1;
    }

    return 0;
}

void translate_in(FILE* byte_code) {
    assert(byte_code != NULL);

    fprintf(byte_code, "%d\n", IN);
}

void translate_out(FILE* byte_code) {
    assert(byte_code != NULL);

    fprintf(byte_code, "%d\n", OUT);
}

void translate_HLT(FILE* byte_code) {
    assert(byte_code != NULL);

    fprintf(byte_code, "%d\n", HLT);
}

void translate_add(FILE* byte_code) {
    assert(byte_code != NULL);

    fprintf(byte_code, "%d\n", ADD);
}

void translate_sub(FILE* byte_code) {
    assert(byte_code != NULL);

    fprintf(byte_code, "%d\n", SUB);
}

void translate_mul(FILE* byte_code) {
    assert(byte_code != NULL);

    fprintf(byte_code, "%d\n", MUL);
}

void translate_div(FILE* byte_code) {
    assert(byte_code != NULL);

    fprintf(byte_code, "%d\n", DIV);
}

void translate_sqrt(FILE* byte_code) {
    assert(byte_code != NULL);

    fprintf(byte_code, "%d\n", SQRT);
}

void translate_sin(FILE* byte_code) {
    assert(byte_code != NULL);

    fprintf(byte_code, "%d\n", SIN);
}

void translate_cos(FILE* byte_code) {
    assert(byte_code != NULL);

    fprintf(byte_code, "%d\n", COS);
}

void wrong_command(const char* command) {
    assert(command != NULL);

    printf("WRONG COMMAND: %s\n", command);
}

void wrong_push() {
    printf("WRONG PUSH\n");
}
