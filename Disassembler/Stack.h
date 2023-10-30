#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

#include <stdint.h>

const long long Canary_val = 11111111;

typedef int Elem_t;
typedef long long Canary_t;

struct Stack {
    Canary_t left_canary;
    Elem_t* data;
    size_t size;
    size_t capacity;
    const char* name;
    int line;
    const char* file;
    const char* func;
    uint32_t data_hash;
    uint32_t stack_hash;
    Canary_t right_canary;
};

#define STACK_CTOR(stk) stack_ctor(stk, #stk, __LINE__, __FILE__, __func__)

#define STACK_DUMP(stk) stk_dump(stk, __LINE__, __FILE__, __func__)

int stack_ctor(Stack* stk, const char* name, const int line, const char* file, const char* func);

int stack_dtor(Stack* stk);

int stack_push(Stack* stk, Elem_t value);

int stack_pop(Stack* stk, Elem_t* ret_value);

int stack_realloc(Stack* stk);

unsigned int stack_ok(const Stack* stk);

int stk_dump(const Stack* stk, const int line, const char* file, const char* func);

uint32_t hash_count(const char* s, size_t len);

#endif // STACK_H_INCLUDED
