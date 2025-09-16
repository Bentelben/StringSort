#ifndef TEXT_READER_H
#define TEXT_READER_H

#include <stdio.h>
#include <wchar.h>

wchar_t *ReadFile(FILE *const file, size_t *line_count);
wchar_t **GetLineArray(wchar_t *text, size_t line_count);

#endif
