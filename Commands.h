#ifndef COMMANDS_H_INCLUDED
#define COMMANDS_H_INCLUDED

typedef unsigned char Registr_code_t;

struct Commands_t {
    unsigned char is_registr : 1;
    unsigned char is_number : 1;
    unsigned char command : 5;
};

enum commands {
    HLT = 31,
    PUSH = 1,
    IN = 2,
    OUT = 3,
    ADD = 4,
    SUB = 5,
    MUL = 6,
    DIV = 7,
    SQRT = 8,
    SIN = 9,
    COS = 10,
    POP = 11
};

enum registrs {
    A = 0,
    B = 1,
    C = 2,
    D = 3
};

const int NREG = 4;

#endif // COMMANDS_H_INCLUDED
