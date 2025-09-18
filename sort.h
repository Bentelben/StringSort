#ifndef SORT_H
#define SORT_H

#include <stdlib.h>

void BubbleSort(void *const array, size_t const n, size_t const size, int (*compare)(void const *, void const *));

#endif
