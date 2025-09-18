#include "text_reader.h"

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>


int Compare(void const *ptr1, void const *ptr2);
int CompareSymbols(int c1, int c2);
int AlphabetCompare(line_t const line1, line_t const line2);
int ReverseCompare(line_t const line1, line_t const line2);

int Compare(void const *ptr1, void const *ptr2) {
    line_t const line1 = *(line_t const *)ptr1;
    line_t const line2 = *(line_t const *)ptr2;
    return ReverseCompare(line1, line2);
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

int AlphabetCompare(line_t const line1, line_t const line2) {
    size_t i1 = 0, i2 = 0;
    while (i1 < line1.length && i2 < line2.length) {
        if (!isalpha(line1.str[i1]))
            i1++;
        else if (!isalpha(line2.str[i2])) 
            i2++;
        else if (CompareSymbols(line1.str[i1], line2.str[i2]) != 0)
            break;
        else {
            i1++;
            i2++;
        }
    }

    return CompareSymbols(line1.str[i1], line2.str[i2]);
}

int ReverseCompare(line_t const line1, line_t const line2) {
    size_t i1 = line1.length, i2 = line2.length;
    while (i1 >= 1 && i2 >= 1) {
        if (!isalpha(line1.str[i1]))
            i1--;
        else if (!isalpha(line2.str[i2]))
            i2--;
        else if (CompareSymbols(line1.str[i1], line2.str[i2]) != 0)
            break;
        else {
            i1--;
            i2--;
        }
    }

    return CompareSymbols(line1.str[i1], line2.str[i2]);
}

int main() {
    char const *filename = "output.txt";
    
    size_t text_size = 0;
    char *text = ReadFile(filename, &text_size);
    assert(text);

    size_t line_count = 0;
    line_t *const lines = GetLineArray(text, &line_count);
    assert(lines);

    qsort(lines, line_count, sizeof(*lines), Compare);

    //printf("line_count = %zu\n", line_count);
    for (size_t i = 0; i < line_count; i++) {
        printf("%zu `%.*s`\n", i, (int)lines[i].length, lines[i].str);
    }

    free(text);
    free(lines);
}
