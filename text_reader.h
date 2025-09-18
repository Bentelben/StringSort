#ifndef TEXT_READER_H
#define TEXT_READER_H

#include <stdio.h>
#include <wchar.h>

char *ReadFile(char const *file, size_t *text_size);
char **GetLineArray(char *text, size_t *line_count);

#endif
