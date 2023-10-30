#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#include "Stack.h"

int stack_ctor(Stack* stk, const char* name, const int line, const char* file, const char* func) {
    assert(stk!= NULL);

    stk->left_canary = Canary_val;
    stk->data = (Elem_t*) ((Canary_t*) calloc(16 * sizeof(Elem_t) + 2 * sizeof(Canary_t), sizeof(char)) + 1);
    *((Canary_t*) stk->data - 1) = Canary_val;
    stk->size = 0;
    stk->capacity = 16;
    *((Canary_t*) (stk->data + stk->capacity)) = Canary_val;
    stk->name = name;
    stk->line = line;
    stk->file = file;
    stk->func = func;
    stk->data_hash = hash_count((char*) (stk->data), stk->capacity * sizeof(Elem_t));
    stk->stack_hash = 0;
    stk->stack_hash = hash_count((char*) stk, sizeof(Canary_t) + sizeof(Elem_t*) + sizeof(int) + sizeof(size_t) * 2 + sizeof(char*) * 3 + sizeof(uint32_t));
    stk->right_canary = Canary_val;
    return 0;
}

int stack_dtor(Stack* stk) {
    free(stk->data);
    stk->left_canary = -1;
    stk->size = 0;
    stk->capacity = 0;
    stk->name = NULL;
    stk->line = -1;
    stk->file = NULL;
    stk->func = NULL;
    stk->data_hash = 0;
    stk->stack_hash = 0;
    stk->right_canary = -1;
    return 0;
}

int stack_push(Stack* stk, Elem_t value) {
    if (stack_ok(stk) != 0)
        STACK_DUMP(stk);
    else {
        if (stk->size == stk->capacity)
            stack_realloc(stk);
        *(stk->data + stk->size) = value;
        stk->size++;
        stk->data_hash = hash_count((char*) stk->data, stk->capacity * sizeof(Elem_t));
        stk->stack_hash = hash_count((char*) stk, sizeof(Canary_t) + sizeof(Elem_t*) + sizeof(int) + sizeof(size_t) * 2 + sizeof(char*) * 3 + sizeof(uint32_t));
    }
    return 0;
}

int stack_pop(Stack* stk, Elem_t* ret_value) {
    if (stack_ok(stk) != 0)
        STACK_DUMP(stk);
    else {
        stk->size--;
        *ret_value = *(stk->data + stk->size);
        *(stk->data + stk->size) = 0;
        if (stk->size <= stk->capacity / 4)
            stack_realloc(stk);
        stk->data_hash = hash_count((char*) stk->data, stk->capacity * sizeof(Elem_t));
        stk->stack_hash = hash_count((char*) stk, sizeof(Canary_t) + sizeof(Elem_t*) + sizeof(int) + sizeof(size_t) * 2 + sizeof(char*) * 3 + sizeof(uint32_t));
    }
    return 0;
}

int stack_realloc(Stack* stk) {
    if (stk->size == stk->capacity) {
        stk->data = (Elem_t*) ((Canary_t*) realloc((char*) ((Canary_t*) stk->data - 1), stk->capacity * 2 * sizeof(Elem_t) + 2 * sizeof(Canary_t)) + 1);
        *((Canary_t*) (stk->data + stk->capacity)) = 0;
        for (size_t i = stk->capacity * sizeof(Elem_t) + sizeof(Canary_t); i < stk->capacity * 2 * sizeof(Elem_t) + sizeof(Canary_t); i++)
            *((char*) stk->data + i) = 0;
        stk->capacity *= 2;
        *((Canary_t*) (stk->data + stk->capacity)) = Canary_val;
    }

    else if (stk->size <= stk->capacity / 4 && stk->capacity > 16) {
        stk->data = (Elem_t*) ((Canary_t*) realloc((char*) ((Canary_t*) stk->data - 1), stk->capacity / 2 * sizeof(Elem_t) + 2 * sizeof(Canary_t)) + 1);
        stk->capacity /= 2;
        *((Canary_t*) (stk->data + stk->capacity)) = Canary_val;
    }

    return 0;
}

unsigned int stack_ok(const Stack* stk) {
    unsigned int error = 0;

    if (stk == NULL) {
        error += 1;
        return error;
    }

    if (stk->data == NULL) {
        error += 2;
        return error;
    }

    if (stk->size < 0)
        error += 4;

    if (stk->capacity < 0)
        error += 8;

    if (stk->size > stk->capacity)
        error += 16;

    if (stk->name == NULL)
        error += 32;

    if (stk->line < 0)
        error += 64;

    if (stk->file == NULL)
        error += 128;

    if (stk->file == NULL)
        error += 256;

    if (stk->left_canary != Canary_val)
        error += 512;

    if (stk->right_canary != Canary_val)
        error += 1024;

    if (*((Canary_t*) stk->data - 1) != Canary_val)
        error += 2048;

    if (*((Canary_t*) (stk->data + stk->capacity)) != Canary_val)
        error += 4096;

    if (stk->data_hash != hash_count((char*) (stk->data), stk->capacity * sizeof(Elem_t)))
        error += 8192;

    if (stk->stack_hash != hash_count((char*) stk, sizeof(Canary_t) + sizeof(Elem_t*) + sizeof(int) + sizeof(size_t) * 2 + sizeof(char*) * 3 + sizeof(uint32_t)))
        error += 16384;

    return error;
}

int stk_dump(const Stack* stk, const int line, const char* file, const char* func) {
    unsigned int error = stack_ok(stk);

    if (error % 2 == 1) {
        printf("ERROR: NULL Stack pointer\n");
        printf("Stack [%p] \"%s\" from %s(%d) %s\n", stk->data, stk->name, stk->file, stk->line, stk->func);
        printf("\t\t called from %s(%d) %s\n", file, line, func);
        printf("{ size = %u\n  capacity = %u\n  data[NULL]\n}", stk->size, stk->capacity);
        return 0;
    }
    error /= 2;

    if (error % 2 == 1) {
        printf("ERROR: NULL data pointer\n");
        return 0;
    }
    error /= 2;

    if (error % 2 == 1)
        printf("ERROR: size < 0\n");
    error /= 2;

    if (error % 2 == 1)
        printf("ERROR: capacity < 0\n");
    error /= 2;

    if (error % 2 == 1)
        printf("ERROR: size > capacity\n");
    error /= 2;

    if (error % 2 == 1)
        printf("ERROR: NULL name pointer\n");
    error /= 2;

    if (error % 2 == 1)
        printf("ERROR: wrong line\n");
    error /= 2;

    if (error % 2 == 1)
        printf("ERROR: NULL file_name pointer\n");
    error /= 2;

    if (error % 2 == 1)
        printf("ERROR: NULL func_name pointer\n");
    error /= 2;

    if (error % 2 == 1)
        printf("ERROR: left_canary died\n");
    error /= 2;

    if (error % 2 == 1)
        printf("ERROR: right_canary died\n");
    error /= 2;

    if (error % 2 == 1)
        printf("ERROR: left_guard died\n");
    error /= 2;

    if (error % 2 == 1)
        printf("ERROR: right_guard died\n");
    error /= 2;

    if (error % 2 == 1)
        printf("ERROR: wrong data_hash\n");
    error /= 2;

    if (error % 2 == 1)
        printf("ERROR: wrong stack_hash\n");
    error /= 2;

    printf("Stack [%p] \"%s\" from %s(%d) %s\n", stk, stk->name, stk->file, stk->line, stk->func);
    printf("\t\t called from %s(%d) %s\n", file, line, func);
    printf("left_canary = %ld\n", stk->left_canary);
    printf("{ size = %u\n  capacity = %u\n  left_guard = %ld\n  ", stk->size, stk->capacity, *((Canary_t*) stk->data - 1));
    printf("data[%p]\n\t{", stk->data);
    for (size_t i = 0; i < stk->capacity; i++)
        printf("\n\t [%d] = %d", i, stk->data[i]);
    printf("\n\t}\n  right_guard = %ld\n}\n", *((Canary_t*) (stk->data + stk->capacity)));
    printf("data_hash = %u\n", stk->data_hash);
    printf("want data_hash = %u\n", hash_count((char*) (stk->data), stk->capacity * sizeof(Elem_t)));
    printf("stack_hash = %u\n", stk->stack_hash);
    printf("want stack_hash = %u\n", hash_count((char*) stk, sizeof(Canary_t) + sizeof(Elem_t*) + sizeof(int) + sizeof(size_t) * 2 + sizeof(char*) * 3 + sizeof(uint32_t)));
    printf("right_canary = %ld\n", stk->right_canary);
    return 0;
}

uint32_t hash_count(const char* s, size_t len) {
    uint32_t hash_data = 5381;
    for (size_t i = 1; i < len; i++) {
        hash_data = hash_data * 33 + (unsigned char) *(s + i);
    }
    return hash_data;
}
