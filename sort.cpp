#include "sort.h"

#include <stdlib.h>
#include <string.h>

static void MySwap(void *const ptr1, void *const ptr2, size_t size) {
    void *tmp = calloc(1, size);

    memcpy(tmp, ptr1, size);
    memcpy(ptr1, ptr2, size);
    memcpy(ptr2, tmp, size);
    
    free(tmp);
}

void BubbleSort(void *const array, size_t const n, size_t const size, int (*compare)(void const *, void const *)) {
    for (size_t i = n-1; i >= 1; i--) {
        for (size_t j = 0; j < i; j++) {
            char *elem_ptr = (char *)array + j*size;
            if (compare( elem_ptr, elem_ptr + size) == 1) {
                MySwap(elem_ptr, elem_ptr + size, size); 
            }
        }
    }
}

