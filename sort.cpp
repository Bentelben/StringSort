#include "sort.h"

#include <string.h>
#include <assert.h>

#define MOVEPTR(array, i, size) ( (void *)((char *)(array) + (i)*(size)) )

static void MySwap(void *const ptr1, void *const ptr2, size_t size) {
    assert(ptr1);
    assert(ptr2);

    void *tmp = calloc(1, size);
    assert(tmp);

    memcpy(tmp, ptr1, size);
    memcpy(ptr1, ptr2, size);
    memcpy(ptr2, tmp, size);
    
    free(tmp);
}

void BubbleSort(void *const array, size_t const n, size_t const size, int (*compare)(void const *, void const *)) {
    for (size_t i = n-1; i >= 1; i--) {
        for (size_t j = 0; j < i; j++) {
            void *const elem_ptr = MOVEPTR(array, i, size);
            void *const next_elem_ptr = MOVEPTR(array, i + 1, size);
            if (compare( elem_ptr, next_elem_ptr) == 1) {
                MySwap(elem_ptr, next_elem_ptr, size); 
            }
        }
    }
}


static size_t QuickSortPartition(void *middle, void *const array, size_t const n, size_t const size, int (*compare)(void const *, void const *)) {
    size_t i = 0;
    size_t j = n - 1;

    //printf("partition\n");
    //printf("m = %d\n", *(int*)middle);

    //printf("array before\n");
    //for (size_t k = 0; k < n; k++)
    //    printf("%d ", *(int *)MOVEPTR(array, k, size));
    //printf("\n");
   
    while (1) {
        while (compare(MOVEPTR(array, i, size), middle) == -1)
            i++;

        while (compare(middle, MOVEPTR(array, j, size)) == -1)
            j--;

        //printf("i = %zu j = %zu\n", i, j);

        if (i >= j)
            break;
        
        void *const i_ptr = MOVEPTR(array, i, size);
        void *const j_ptr = MOVEPTR(array, j, size);

        if (i_ptr == middle)
            middle = j_ptr;
        else if (j_ptr == middle)
            middle = i_ptr;
        MySwap(i_ptr, j_ptr, size);
        i++;
        j--;
        
        //for (size_t k = 0; k < n; k++) {
        //    printf("%d ", *(int *)MOVEPTR(array, k, size));
        //}
        //printf("\n");
    }

    //printf("array after\n");
    //for (size_t k = 0; k < n; k++)
    //    printf("%d ", *(int *)MOVEPTR(array, k, size));
    //printf("\n");

    return i;
}

void QuickSort(void *array, size_t n, size_t const size, int (*compare)(void const *, void const *)) {
    assert(array);
    //fprintf(stderr, "n = %d\n", n);

    while (1) {
        if (n <= 1)
            return;

        if (n == 2) {
            if (compare(array, MOVEPTR(array, 1, size)) == 1)
                MySwap(array, MOVEPTR(array, 1, size), size);
            return;
        }

        
        void *middle = MOVEPTR(array, n/2, size);

        //printf("m = %d\n", *(int*)middle);
        //for (size_t i = 0; i < n; i++)
        //    printf("%d ", *(int*)MOVEPTR(array, i, size));
        //printf("\n");

        size_t p = QuickSortPartition(middle, array, n, size, compare);
        assert(p < n);

        //for (size_t i = 0; i < n; i++)
        //    printf("%d ", *(int*)MOVEPTR(array, i, size));
        //printf("\n\n");
        
        //printf("n = %zu p = %zu\n", n, p);


        // TODO optimize recursion with while

        void *const left_array = array;
        size_t const left_n = p;

        void *const right_array = MOVEPTR(array, p, size);
        size_t const right_n = n - p;
        if (left_n < right_n) {
            QuickSort(left_array, left_n, size, compare);
            
            array = right_array;
            n = right_n;
        } else {
            QuickSort(right_array, right_n, size, compare);

            array = left_array;
            n = left_n;
        }
    }
}


#undef MOVEPTR
