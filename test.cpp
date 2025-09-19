#include "test.h"

#include "sort.h"

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

static int compare(void const *ptr1, void const *ptr2) {
    int value1 = *(int const*)ptr1;
    int value2 = *(int const*)ptr2;

    if (value1 < value2)
        return -1;
    else if (value1 > value2)
        return 1;
    return 0;
}

static void GenerateTest(int **array0, size_t *n) {
    srand((unsigned int)time(NULL));

    size_t const N_MIN = 1;
    size_t const N_MAX = 1000;
    *n = N_MIN + ((size_t)rand() % (N_MAX - N_MIN + 1));

    *array0 = (int *)calloc(*n, sizeof(int));
    assert(*array0);
    
    int const VALUE_MIN = -50;
    int const VALUE_MAX =  50;
    for (size_t i = 0; i < *n; i++)
        (*array0)[i] = VALUE_MIN + (rand() % (VALUE_MAX - VALUE_MIN + 1));
}

static bool RunTest(int *array0, int **array1, int **array2, size_t n) {
    *array1 = (int *)calloc(n, sizeof(int));
    *array2 = (int *)calloc(n, sizeof(int));

    for (size_t i = 0; i < n; i++) {
        (*array1)[i] = array0[i];
        (*array2)[i] = array0[i];
    }

    qsort    (*array1, n, sizeof(int), compare);
    QuickSort(*array2, n, sizeof(int), compare);

    for (size_t i = 0; i < n; i++) {
        if ((*array1)[i] != (*array2)[i]) {
            return false;
        }
    }
    return true;
}

void Test() {
    for (size_t i = 0; i < 1000; i++) {
        //printf("%zu\n", i);

        size_t n = 0;
        int *array0 = NULL;
        int *array1 = NULL;
        int *array2 = NULL;
        GenerateTest(&array0, &n);
    
        if (!RunTest(array0, &array1, &array2, n)) {
            printf("\nERROR\n\n");
            printf("Ref\n");
            for (size_t j = 0; j < n; j++)
                printf("%d ", array0[j]);

            printf("\nqsort\n");
            for (size_t j = 0; j < n; j++)
                printf("%d ", array1[j]);

            printf("\nmysort\n");
            for (size_t j = 0; j < n; j++)
                printf("%d ", array2[j]);
            printf("\n");

            free(array0);
            free(array1);
            free(array2);
            return;
        }

        free(array0);
        free(array1);
        free(array2);
    }
}
