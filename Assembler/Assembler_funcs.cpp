#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Assembler_funcs.h"
#include "../Commands.h"
#include "../Stack.h"

int assembler_translate(const char* input_name, const char* output_name) {
    assert(input_name != NULL);
    assert(output_name != NULL);

    FILE* assembler_code = fopen(input_name, "r");
    FILE* byte_code      = fopen(output_name, "wb");
    char command[10] = "";

    while (fscanf(assembler_code, "%s", command) != EOF) {
        if (strcmp(command, "push") == 0) {
            if (translate_push(assembler_code, byte_code, PUSH) == 1) {
                return 1;
            }
        }
        else if (strcmp(command, "pushr") == 0) {
            if (translate_pushr(assembler_code, byte_code, PUSHR) == 1) {
                return 1;
            }
        }
        else if (strcmp(command, "pop") == 0) {
            if (translate_pop(assembler_code, byte_code, POP) == 1) {
                return 1;
            }
        }

        else if (strcmp(command, "in") == 0) {
            command_translate(byte_code, IN);
        }
        else if (strcmp(command, "out") == 0) {
            command_translate(byte_code, OUT);
        }
        else if (strcmp(command, "HLT") == 0) {
            command_translate(byte_code, HLT);
        }

        else if (strcmp(command, "add") == 0) {
            command_translate(byte_code, ADD);
        }
        else if (strcmp(command, "sub") == 0) {
            command_translate(byte_code, SUB);
        }
        else if (strcmp(command, "mul") == 0) {
            command_translate(byte_code, MUL);
        }
        else if (strcmp(command, "div") == 0) {
            command_translate(byte_code, DIV);
        }

        else if (strcmp(command, "sqrt") == 0) {
            command_translate(byte_code, SQRT);
        }
        else if (strcmp(command, "sin") == 0) {
            command_translate(byte_code, SIN);
        }
        else if (strcmp(command, "cos") == 0) {
            command_translate(byte_code, COS);
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

int translate_push(FILE* assembler_code, FILE* byte_code, Commands_t command) {
    assert(assembler_code != NULL);
    assert(byte_code != NULL);

    Elem_t x = 0;
    if (fscanf(assembler_code, "%lf", &x) == 1) {
        fwrite(&command, sizeof(Commands_t), 1, byte_code);
        fwrite(&x, sizeof(Elem_t), 1, byte_code);
    }
    else {
        wrong_push();
        return 1;
    }

    return 0;
}

#define REGISTR_FUNC(name)                                                              \
    int translate_##name(FILE* assembler_code, FILE* byte_code, Commands_t command) {   \
        assert(assembler_code != NULL);                                                 \
        assert(byte_code != NULL);                                                      \
                                                                                        \
        char registr[4] = "";                                                           \
        fscanf(assembler_code, "%s", registr);                                          \
        if (strcmp(registr, "rax") == 0) {                                              \
            Registr_code_t registr_code = A;                                            \
            fwrite(&command, sizeof(Commands_t), 1, byte_code);                         \
            fwrite(&registr_code, sizeof(Registr_code_t), 1, byte_code);                \
        }                                                                               \
        else if (strcmp(registr, "rbx") == 0) {                                         \
            Registr_code_t registr_code = B;                                            \
            fwrite(&command, sizeof(Commands_t), 1, byte_code);                         \
            fwrite(&registr_code, sizeof(Registr_code_t), 1, byte_code);                \
        }                                                                               \
        else if (strcmp(registr, "rcx") == 0) {                                         \
            Registr_code_t registr_code = C;                                            \
            fwrite(&command, sizeof(Commands_t), 1, byte_code);                         \
            fwrite(&registr_code, sizeof(Registr_code_t), 1, byte_code);                \
        }                                                                               \
        else if (strcmp(registr, "rdx") == 0) {                                         \
            Registr_code_t registr_code = D;                                            \
            fwrite(&command, sizeof(Commands_t), 1, byte_code);                         \
            fwrite(&registr_code, sizeof(Registr_code_t), 1, byte_code);                \
        }                                                                               \
        else {                                                                          \
            wrong_##name();                                                             \
            return 1;                                                                   \
        }                                                                               \
                                                                                        \
        return 0;                                                                       \
    }


REGISTR_FUNC(pushr)

REGISTR_FUNC(pop)

void command_translate(FILE* byte_code, Commands_t command) {
    assert(byte_code != NULL);

    fwrite(&command, sizeof(Commands_t), 1, byte_code);
}

void wrong_command(const char* command) {
    assert(command != NULL);

    printf("WRONG COMMAND: %s\n", command);
}

#define WRONG(name, text)                 \
    void wrong_##name() {                 \
        fprintf(stderr, "WRONG ##text\n");\
    }

WRONG(push, PUSH)

WRONG(pushr, PUSHR)

WRONG(pop, POP)
