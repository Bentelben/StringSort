#include "text_reader.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include <sys/stat.h>

char *ReadFile(char const *const filename, size_t *const text_size) {
    assert(filename);
    assert(text_size);

    FILE *file = fopen(filename, "r");
    if (file == NULL)
        return NULL;

    struct stat file_stat = {};
    if (stat(filename, &file_stat) == -1)
        return NULL;

    size_t file_size = (size_t)file_stat.st_size;
    printf("file_size = %zu\n", file_size);

    char *text = (char *)calloc(file_size + 1, sizeof(*text));
    if (text == NULL)
        return NULL;

    *text_size = fread(text, sizeof(*text), file_size, file);
    text[*text_size] = '\0';

    printf("text_size = %zu\n", *text_size);

    fclose(file);
    return text;
}

char **GetLineArray(char *const text, size_t *const line_count) {
    assert(text);

    *line_count = 0;
    char *iterator = text;
    while (1) {
        *line_count += 1;
        iterator = strchr(iterator + 1, '\n');
        if (iterator == NULL)
            break;
        *iterator = '\0';
    }

    char **lines = (char **)calloc(*line_count, sizeof(*lines));
    if (lines == NULL)
        return NULL;

    lines[0] = text;
    for (size_t i = 1; i < *line_count; i++) {
        lines[i] = strchr(lines[i-1], '\0') + 1;
    }
    return lines;
}


