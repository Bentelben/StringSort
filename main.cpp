#include "text_reader.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

int compare(void const *a, void const *b);
int compareBackwards(void const *a, void const *b);

int compare(void const *a, void const *b) {
    return strcmp(*(char const *const *)a, *(char const *const *)b);
}

int compareBackwards(void const *a, void const *b) {
    char const *const str1 = *(char const *const *)a;
    char const *const str2 = *(char const *const *)b;

    size_t const str1_len = strlen(str1);
    size_t const str2_len = strlen(str2);

    for (size_t i = 1; i <= str1_len && i <= str2_len; i++) {
        if (str1[str1_len - i] < str2[str2_len - i])
            return -1;
   
        else if (str1[str1_len - i] > str2[str2_len - i])
            return 1;
    }
    
    if (str1_len < str2_len)
        return -1;

    else if (str1_len > str2_len)
        return 1;

    return 0;
}


int main() {
    FILE *file = fopen("output.txt", "r");
    assert(file);
    
    size_t line_count = 0;
    char *text = ReadFile(file, &line_count);
    assert(text);
    fclose(file);

    char **const lines = GetLineArray(text, line_count);
    assert(lines);

    qsort(lines, line_count, sizeof(*lines), compareBackwards);

    for (size_t i = 0; i < line_count; i++) {
        printf("%zu `%s`\n", i, lines[i]);
    }

    free(lines);
    free(text);
}


