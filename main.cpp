#include "text_reader.h"

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>


int Compare(void const *ptr_1, void const *ptr_2);
int CompareSymbols(int c1, int c2);
int AlphabetCompare(const char *str1, const char *str2);
int ReverseCompare(const char *str1, const char *str2);

int Compare(void const *ptr_1, void const *ptr_2) {
    const char* str1 = *(const char *const *)ptr_1;
    const char* str2 = *(const char *const *)ptr_2;
    return ReverseCompare(str1, str2);
}

int CompareSymbols(int c1, int c2) {
    c1 = tolower(c1);
    c2 = tolower(c2);
    if (c1 < c2)
        return -1;
    else if (c1 > c2)
        return 1;
    return 0;
}

int AlphabetCompare(const char *str1, const char *str2) {
    size_t i1 = 0, i2 = 0;
    while (str1[i1] != '\0' && str2[i2] != '\0') {
        if (!isalpha(str1[i1]))
            i1++;
        else if (!isalpha(str2[i2])) 
            i2++;
        else if (CompareSymbols(str1[i1], str2[i2]) != 0)
            break;
        else {
            i1++;
            i2++;
        }
    }

    return CompareSymbols(str1[i1], str2[i2]);
}

int ReverseCompare(const char *str1, const char *str2) {
    size_t const len1 = strlen(str1);
    size_t const len2 = strlen(str2);

    size_t i1 = len1, i2 = len2;
    while (i1 >= 1 && i2 >= 1) {
        if (!isalpha(str1[i1]))
            i1--;
        else if (!isalpha(str2[i2]))
            i2--;
        else if (CompareSymbols(str1[i1], str2[i2]) != 0)
            break;
        else {
            i1--;
            i2--;
        }
    }

    return CompareSymbols(str1[i1], str2[i2]);
}

int main() {
    char const *filename = "output.txt";
    
    size_t text_size = 0;
    char *text = ReadFile(filename, &text_size);
    assert(text);

    size_t line_count = 0;
    char **const lines = GetLineArray(text, &line_count);
    assert(lines);

    qsort(lines, line_count, sizeof(*lines), Compare);

    printf("line_count = %zu\n", line_count);
    for (size_t i = 0; i < line_count; i++) {
        printf("%zu `%s`\n", i, lines[i]);
    }

    free(text);
    free(lines);
}
