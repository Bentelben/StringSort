#include "text_reader.h"

#include <stdio.h>
#include <assert.h>
#include <string.h>

int compare(void const *a, void const *b) {
    return strcmp(*(char const **)a, *(char const **)b);
}

int compare(void const *a, void const *b) {
    return 
}


int main() {
    FILE *file = fopen("text.txt", "r");
    
    size_t line_count = 0;
    char *text = ReadFile(file, &line_count);
    fclose(file);

    char **const lines = GetLineArray(text, line_count);

    qsort(lines, line_count, sizeof(*lines), compare);


    for (size_t i = 0; i < line_count; i++) {
        printf("`%s`\n", lines[i]);
    }

    free(lines);
    free(text);
}


