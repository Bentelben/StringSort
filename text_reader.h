#ifndef TEXT_READER_H
#define TEXT_READER_H

#include <stdio.h>

typedef struct _line_t {
    char *str;
    size_t length;
} line_t;

char *ReadFile(char const *file, size_t *text_size);
line_t *GetLineArray(char *text, size_t *line_count);

#endif
