#include "text_reader.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include <wchar.h>

wchar_t *ReadFile(FILE *const file, size_t *const line_count) {
    assert(file);

    size_t const BUFFER_SIZE = 256;

    *line_count = 0;
    size_t text_size = BUFFER_SIZE;
    wchar_t *text = (wchar_t *)calloc(text_size, sizeof(*text));
    if (text == NULL)
        return NULL;

    wint_t c = 0;
    size_t i = 0;
    do {
        if (i >= text_size) {
            //text_size += BUFFER_SIZE;
            text_size *= 2;
            text = (wchar_t *)realloc(text, text_size*sizeof(*text));
            if (text == NULL)
                return NULL;
        }

        c = fgetwc(file);

        if (c == L'\n' || c == WEOF) {
            if (i >= 1 && text[i-1] == L'\0')
                continue;

            text[i] = L'\0';
            (*line_count)++;
        } else {
            text[i] = (wchar_t)c;
        }

        i++;
    } while(c != WEOF);

    text = (wchar_t *)realloc(text, i*sizeof(*text));
    return text;
}

wchar_t **GetLineArray(wchar_t *text, size_t const line_count) {
    assert(text);
    assert(line_count != 0);

    wchar_t **lines = (wchar_t **)calloc(line_count, sizeof(*lines));
    if (lines == NULL)
        return NULL;

    for (size_t i = 0; i < line_count; i++) {
        lines[i] = text;
        text += wcslen(text) + 1;
    }

    return lines;
}




