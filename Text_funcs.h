#ifndef READ_STRS5_H_INCLUDED
#define READ_STRS5_H_INCLUDED

#include <stdio.h>

struct line {
    char* start;
    size_t len;
    size_t alpha_count;
};

struct text {
    char* buffer;
    size_t len;
    FILE* open_file;
    struct line* lines;
    size_t str_num;
};

size_t file_len(FILE* read);

size_t str_num(const char* text);

size_t alpha_count(const char* str);

void read_lines(struct line* lines, char* text);

void print_lines(struct line* lines, size_t str_num, const char* filename);

void clear_lines(struct line* lines, size_t str_num);

void clear_text(struct text* text);

#endif // READ_STRS5_H_INCLUDED
