#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys\stat.h>

#include "Text_Funcs.h"

size_t file_len(FILE* opened_file) {
    assert(opened_file != NULL);

    struct stat file_info = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    fstat(fileno(opened_file), &file_info);
    return file_info.st_size;
}

size_t str_num(const char* text) {
    assert(text != NULL);

    size_t i = 0, str_num = 1;
    while(text[i] != '\0') {
        if (text[i] == '\n')
            str_num++;
        i++;
    }
    return str_num;
}

size_t alpha_count(const char* str) {
    assert(str != NULL);

    size_t i = 0, res = 0;
    while (str[i] != '\0') {
        if (isalpha(str[i]))
            res++;
        i++;
    }
    return res;
}

void read_lines(struct line* lines, char* text) {
    assert(lines != NULL);
    assert(text != NULL);

    lines[0].start = text;
    size_t i = 0, str_num = 1, line_len = 0;
    while (text[i] != '\0') {
        if (text[i] == '\n') {
            text[i] = '\0';
            lines[str_num].start = text + i + 1;
            lines[str_num - 1].len = line_len;
            line_len = 0;
            str_num++;
        }
        else
            line_len++;
        i++;
    }
    lines[str_num - 1].len = line_len;
    for (i = 0; i < str_num; i++) {
        lines[i].alpha_count = alpha_count(lines[i].start);
    }
}

void print_lines(struct line* lines, size_t str_num, const char* filename) {
    assert(lines != NULL);
    assert(filename != NULL);

    FILE* res = fopen(filename, "w");
    for (size_t i = 0; i < str_num; i++) {
        if (lines[i].alpha_count != 0)
            fprintf(res, "%s\n", lines[i].start);
    }
    fclose(res);
}

void clear_lines(struct line* lines, size_t str_num) {
    assert(lines != NULL);

    for (size_t i = 0; i < str_num; i++) {
        free(lines[i].start);
        lines[i].start = NULL;
        lines[i].len = 0;
    }
}

void clear_text(struct text* text) {
    assert(text != NULL);

    text->open_file = NULL;
    text->len = 0;
    free(text->buffer);
    free(text->lines);
    text->str_num = 0;
}
