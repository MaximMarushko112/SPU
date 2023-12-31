#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Commands.h"
#include "Disassembler_funcs.h"
#include "../Stack.h"
#include "../Text_funcs.h"

int disassembler_translate(const char* input_name, const char* output_name) {
    assert(input_name != NULL);
    assert(output_name != NULL);

    FILE* byte_code      = fopen(input_name, "rb");
    FILE* assembler_code = fopen(output_name, "w");
    struct bin code = {NULL, 0, 0, 0};
    code.bin_file_len = file_len(byte_code);
    code.bin_file = (char*) calloc(code.bin_file_len, sizeof(char));
    fread(code.bin_file, sizeof(char), code.bin_file_len, byte_code);

    while (code.bin_shift < code.bin_file_len) {
        Commands_t command = {0, 0, 0};
        command = *((Commands_t*) (code.bin_file + code.bin_shift));
        code.id++;
        code.bin_shift += sizeof(Commands_t);
        switch (command.command) {
        case PUSH:
            if (distranslate_push(&code, assembler_code, &command) == 1) {
                return 1;
            }
            break;
        case POP:
            if (distranslate_pop(&code, assembler_code) == 1) {
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
            wrong_command_code(&command);
            return 1;
            break;
        }
    }
    fclose(byte_code);
    fclose(assembler_code);

    return 0;
}

int distranslate_push(bin* code, FILE* assembler_code, Commands_t* command) {
    assert(assembler_code != NULL);
    assert(code != NULL);
    assert(command != NULL);

    if (command->is_number) {
        Elem_t x = 0;
        x = *((Elem_t*) (code->bin_file + code->bin_shift));
        code->id++;
        code->bin_shift += sizeof(Elem_t);
        fprintf(assembler_code, "push %lf\n", x);
    }
    else if (command->is_registr) {
        unsigned char registr = 0;
        registr = *((Registr_code_t*) (code->bin_file + code->bin_shift));
        code->id++;
        code->bin_shift += sizeof(Registr_code_t);
        switch (registr) {
            case A:
                fprintf(assembler_code, "push rax\n");
                break;
            case B:
                fprintf(assembler_code, "push rbx\n");
                break;
            case C:
                fprintf(assembler_code, "push rcx\n");
                break;
            case D:
                fprintf(assembler_code, "push rdx\n");
                break;
            default:
                wrong_registr(registr);
                return 1;
                break;
        }
    }

    return 0;
}

int distranslate_pop(bin* code, FILE* assembler_code) {
    assert(assembler_code != NULL);
    assert(code != NULL);

    unsigned char registr = 0;
    registr = *((Registr_code_t*) (code->bin_file + code->bin_shift));
    code->id++;
    code->bin_shift += sizeof(Registr_code_t);
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

    return 0;
}

#define SIMPLE_DISTRANSLATE(name, command)            \
    void distranslate_##name(FILE* assembler_code) {  \
        assert(assembler_code != NULL);               \
                                                      \
        fprintf(assembler_code, "%s\n", command);     \
    }

SIMPLE_DISTRANSLATE(in, "in")

SIMPLE_DISTRANSLATE(out, "out")

SIMPLE_DISTRANSLATE(HLT, "HLT")

SIMPLE_DISTRANSLATE(add, "add")

SIMPLE_DISTRANSLATE(sub, "sub")

SIMPLE_DISTRANSLATE(mul, "mul")

SIMPLE_DISTRANSLATE(div, "div")

SIMPLE_DISTRANSLATE(sqrt, "sqrt")

SIMPLE_DISTRANSLATE(sin, "sin")

SIMPLE_DISTRANSLATE(cos, "cos")

void wrong_command_code(Commands_t* command) {
    assert(command != NULL);

    fprintf(stderr, "WRONG COMMAND: %d\n", command->command);
}

void wrong_registr(unsigned char registr) {
    fprintf(stderr, "WRONG REGISTR: %d\n", registr);
}
