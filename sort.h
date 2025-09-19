#ifndef SORT_H
#define SORT_H

#include <stddef.h>

typedef int (*comparator_t)(void const *, void const *);

void BubbleSort(void *const array, size_t const n, size_t const size, comparator_t const compare); 
void QuickSort(void *const array, size_t const n, size_t const size, comparator_t const compare);

#endif
