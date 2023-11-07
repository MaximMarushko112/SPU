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

    while (fscanf(assembler_code, "%s", command) != EOF) { //заdefinить копипаст
        struct Commands_t instruction = {0, 0, 0};
        if (strcmp(command, "push") == 0) {
            instruction.command = PUSH;
            if (translate_push(assembler_code, byte_code, &instruction) == 1) {
                return 1;
            }
        }
        else if (strcmp(command, "pop") == 0) {
            instruction.command = POP;
            if (translate_pop(assembler_code, byte_code, &instruction) == 1) {
                return 1;
            }
        }

        else if (strcmp(command, "in") == 0) {
            instruction.command = IN;
            command_translate(byte_code, &instruction);
        }
        else if (strcmp(command, "out") == 0) {
            instruction.command = OUT;
            command_translate(byte_code, &instruction);
        }
        else if (strcmp(command, "HLT") == 0) {
            instruction.command = HLT;
            command_translate(byte_code, &instruction);
        }

        else if (strcmp(command, "add") == 0) {
            instruction.command = ADD;
            command_translate(byte_code, &instruction);
        }
        else if (strcmp(command, "sub") == 0) {
            instruction.command = SUB;
            command_translate(byte_code, &instruction);
        }
        else if (strcmp(command, "mul") == 0) {
            instruction.command = MUL;
            command_translate(byte_code, &instruction);
        }
        else if (strcmp(command, "div") == 0) {
            instruction.command = DIV;
            command_translate(byte_code, &instruction);
        }

        else if (strcmp(command, "sqrt") == 0) {
            instruction.command = SQRT;
            command_translate(byte_code, &instruction);
        }
        else if (strcmp(command, "sin") == 0) {
            instruction.command = SIN;
            command_translate(byte_code, &instruction);
        }
        else if (strcmp(command, "cos") == 0) {
            instruction.command = COS;
            command_translate(byte_code, &instruction);
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

int translate_push(FILE* assembler_code, FILE* byte_code, Commands_t* command) {
    assert(assembler_code != NULL);
    assert(byte_code != NULL);
    assert(command != NULL);

    Elem_t x = 0;
    if (fscanf(assembler_code, "%lf", &x) == 1) {
        command->is_number = 1;
        fwrite(command, sizeof(Commands_t), 1, byte_code);
        fwrite(&x, sizeof(Elem_t), 1, byte_code);
    }
    else {
        char registr[4] = "";
        fscanf(assembler_code, "%s", registr);
        if (registr[0] == 'r' && registr[2] == 'x' && registr[3] == '\0'
            && 'a' <= registr[1] && registr[1] <= 'd') {
            Registr_code_t registr_code = registr[1] - 'a';
            command->is_registr = 1;
            fwrite(command, sizeof(Commands_t), 1, byte_code);
            fwrite(&registr_code, sizeof(Registr_code_t), 1, byte_code);
        }
        else {
            wrong_push();
            return 1;
        }
    }

    return 0;
}

int translate_pop(FILE* assembler_code, FILE* byte_code, Commands_t* command) {
    assert(assembler_code != NULL);
    assert(byte_code != NULL);
    assert(command != NULL);

    char registr[4] = "";
    fscanf(assembler_code, "%s", registr);
    if (registr[0] == 'r' && registr[2] == 'x' && registr[3] == '\0'
        && 'a' <= registr[1] && registr[1] <= 'd') {
        Registr_code_t registr_code = registr[1] - 'a';
        fwrite(command, sizeof(Commands_t), 1, byte_code);
        fwrite(&registr_code, sizeof(Registr_code_t), 1, byte_code);
    }
    else {
        wrong_pop();
        return 1;
    }

    return 0;
}

void command_translate(FILE* byte_code, Commands_t* command) {
    assert(byte_code != NULL);
    assert(command != NULL);

    fwrite(command, sizeof(Commands_t), 1, byte_code);
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

WRONG(pop, POP)
