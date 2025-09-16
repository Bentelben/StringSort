#include "text_reader.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>


char *ReadFile(FILE *const file, size_t *const line_count) {
    assert(file);

    size_t const BUFFER_SIZE = 3;

    *line_count = 0;
    size_t text_size = BUFFER_SIZE;
    char *text = (char *)calloc(text_size, sizeof(*text));
    if (text == NULL)
        return NULL;

    int c = 0;
    size_t i = 0;
    do {
        if (i >= text_size) {
            //text_size += BUFFER_SIZE;
            text_size *= 2;
            text = (char *)realloc(text, text_size*sizeof(*text));
            if (text == NULL)
                return NULL;
        }

        c = fgetc(file);

        if (c == '\n' || c == EOF) {
            if (i >= 1 && text[i-1] == '\0')
                continue;

            text[i] = '\0';
            (*line_count)++;
        } else {
            text[i] = (char)c;
        }

        i++;
    } while(c != EOF);

    text = (char *)realloc(text, i*sizeof(*text));
    return text;
}

char **GetLineArray(char *text, size_t const line_count) {
    assert(text);
    assert(line_count != 0);

    char **lines = (char **)calloc(line_count, sizeof(*lines));
    if (lines == NULL)
        return NULL;

    for (size_t i = 0; i < line_count; i++) {
        lines[i] = text;
        text += strlen(text) + 1;
    }

    return lines;
}




