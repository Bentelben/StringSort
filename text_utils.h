#ifndef TEXT_UTILS_H
#define TEXT_UTILS_H

#include <stdio.h>

typedef struct _line_t {
    char *str;
    size_t length;
} line_t;

char *ReadFile(char const *file, size_t *text_size);
line_t *GetLineArray(char *text, size_t *line_count);
void FPrintLineArray(FILE *file, const line_t *const lines, size_t const line_count);
void PrintLineArray(const line_t *const lines, size_t const line_count);

#endif
