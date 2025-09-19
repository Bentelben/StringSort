#include "sort.h"

#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define MOVEPTR(array, i, size) ( (void *)((char *)(array) + (i)*(size)) )


static void MySwap(void *const vptr1, void *const vptr2, size_t const size) {
    assert(vptr1);
    assert(vptr2);

    char *ptr1 = (char *)vptr1;
    char *ptr2 = (char *)vptr2;

    size_t i = size;
#define DOSHIT(type)                    \
    while (i >= sizeof(type)) {         \
        type tmp = *(type *)ptr1;       \
        *(type *)ptr1 = *(type *)ptr2;  \
        *(type *)ptr2 = tmp;            \
        ptr1 += sizeof(type);           \
        ptr2 += sizeof(type);           \
        i = i - sizeof(type);           \
    }

    DOSHIT(unsigned long long)
    DOSHIT(unsigned int)
    DOSHIT(unsigned short)
    DOSHIT(char)
#undef DOSHIT
}

void BubbleSort(void *const array, size_t const n, size_t const size, comparator_t const compare) {
    assert(array);

    for (size_t i = n-1; i >= 1; i--) {
        for (size_t j = 0; j < i; j++) {
            void *const elem_ptr = MOVEPTR(array, j, size);
            void *const next_elem_ptr = MOVEPTR(array, j + 1, size);
            
            if (compare( elem_ptr, next_elem_ptr) == 1)
                MySwap(elem_ptr, next_elem_ptr, size); 
        }
    }
}


static inline void *QuickSortSelectMiddle(void *const array, size_t const n, size_t const size) {
    //srand((unsigned int)time(NULL));
    //size_t middle_index = (size_t)rand() % n;
    size_t middle_index = n / 2;
    return MOVEPTR(array, middle_index, size);
}

static size_t QuickSortPartition(void *const array, size_t const n, size_t const size, comparator_t const compare) {
    assert(array);

    size_t i = 0;
    size_t j = n - 1;

    void *middle = QuickSortSelectMiddle(array, n, size);

    while (1) {
        while (compare(MOVEPTR(array, i, size), middle) == -1)
            i++;

        while (compare(middle, MOVEPTR(array, j, size)) == -1)
            j--;

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
    }

    return i;
}

void QuickSort(void *array, size_t n, size_t const size, comparator_t const compare) {
    assert(array);

    while (1) {
        if (n <= 1)
            return;

        if (n == 2) {
            if (compare(array, MOVEPTR(array, 1, size)) == 1)
                MySwap(array, MOVEPTR(array, 1, size), size);
            return;
        }

        size_t const p = QuickSortPartition(array, n, size, compare);
        assert(p < n);

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
