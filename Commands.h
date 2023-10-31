#ifndef COMMANDS_H_INCLUDED
#define COMMANDS_H_INCLUDED

typedef int Commands_t;
typedef unsigned char Registr_code_t;

enum commands {
    HLT = -1,
    PUSH = 17,
    IN = 2,
    OUT = 3,
    ADD = 4,
    SUB = 5,
    MUL = 6,
    DIV = 7,
    SQRT = 8,
    SIN = 9,
    COS = 10,
    PUSHR = 33,
    POP = 43
};

enum registrs {
    A = 0,
    B = 1,
    C = 2,
    D = 3
};

const int NREG = 4;

#endif // COMMANDS_H_INCLUDED
