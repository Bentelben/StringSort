#ifndef TEXT_READER_H
#define TEXT_READER_H

#include <stdio.h>

char *ReadFile(FILE *const file, size_t *line_count);
char **GetLineArray(char *text, size_t line_count);

#endif
