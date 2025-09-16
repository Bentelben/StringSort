#include "text_reader.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include <locale.h>
#include <wchar.h>

int compare(void const *a, void const *b);
int compareBackwards(void const *a, void const *b);


int compare(void const *a, void const *b) {
    return wcscmp(*(wchar_t const *const *)a, *(wchar_t const *const *)b);
}

int compareBackwards(void const *a, void const *b) {
    wchar_t const *const str1 = *(wchar_t const *const *)a;
    wchar_t const *const str2 = *(wchar_t const *const *)b;

    size_t const str1_len = wcslen(str1);
    size_t const str2_len = wcslen(str2);

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
    setlocale(LC_ALL, "");
    FILE *file = fopen("output.txt", "r");
    
    size_t line_count = 0;
    wchar_t *text = ReadFile(file, &line_count);
    assert(text);
    fclose(file);

    wchar_t **const lines = GetLineArray(text, line_count);
    assert(lines);
    printf("line_count = %zu\n", line_count);

    qsort(lines, line_count, sizeof(*lines), compareBackwards);

    for (size_t i = 0; i < line_count; i++) {
        printf("`%ls`\n", lines[i]);
    }

    free(lines);
    free(text);
}


