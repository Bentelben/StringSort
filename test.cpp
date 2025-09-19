#include "test.h"

#include "sort.h"

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/time.h>

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

    size_t const N_MIN = 1000;
    size_t const N_MAX = 1000;
    *n = N_MIN + ((size_t)rand() % (N_MAX - N_MIN + 1));

    *array0 = (int *)calloc(*n, sizeof(int));
    assert(*array0);
    
    int const VALUE_MIN = -50;
    int const VALUE_MAX =  50;
    for (size_t i = 0; i < *n; i++)
        (*array0)[i] = VALUE_MIN + (rand() % (VALUE_MAX - VALUE_MIN + 1));
}

static void PrintArr(int const *const array, size_t n) {
    for (size_t i = 0; i < n; i++)
        printf("%d ", array[i]);
    printf("\n");
}

static void PrintTest(int const *const array0, int const *const array1, int const *const array2, size_t n) {
    printf("ref\n");
    PrintArr(array0, n);
    printf("qsort\n");
    PrintArr(array1, n);
    printf("mysort\n");
    PrintArr(array2, n);
}

static bool RunTest(int *const array0, size_t n, suseconds_t *qsort_time, suseconds_t *mysort_time) {
    int *const array1 = (int *)calloc(n, sizeof(int));
    int *const array2 = (int *)calloc(n, sizeof(int));

    for (size_t i = 0; i < n; i++) {
        array1[i] = array0[i];
        array2[i] = array0[i];
    }

    struct timeval start, stop;
    gettimeofday(&start, NULL);
    qsort(array1, n, sizeof(int), compare);
    gettimeofday(&stop, NULL);
    *qsort_time = stop.tv_usec - start.tv_usec + (stop.tv_sec - start.tv_sec)*1000000;

    gettimeofday(&start, NULL);
    QuickSort(array2, n, sizeof(int), compare);
    gettimeofday(&stop, NULL);
    *mysort_time = stop.tv_usec - start.tv_usec + (stop.tv_sec - start.tv_sec)*1000000;

    for (size_t i = 0; i < n; i++) {
        if (array1[i] != array2[i]) {
            PrintTest(array0, array1, array2, n);
            free(array1);
            free(array2);
            return false;
        }
    }
    free(array1);
    free(array2);
    return true;
}

void Test() {
    printf("testing...\n");

    size_t const TEST_COUNT = 1000;

    suseconds_t qsort_time = 0;
    suseconds_t mysort_time = 0;

    for (size_t i = 0; i < TEST_COUNT; i++) {
        //printf("%zu\n", i);

        size_t n = 0;
        int *array0 = NULL;
        GenerateTest(&array0, &n);

        suseconds_t qsort_deltatime = 0;
        suseconds_t mysort_deltatime = 0;
        bool result = RunTest(array0, n, &qsort_deltatime, &mysort_deltatime);
        qsort_time += qsort_deltatime;
        mysort_time += mysort_deltatime;

        free(array0);
        if (!result) {
            printf("\nERROR\n\n");
            return;
        }
    }
    printf("done testing\n");
    printf("qsort time:  %lf\n", (double)qsort_time / TEST_COUNT);
    printf("mysort time: %lf\n\n", (double)mysort_time / TEST_COUNT);

}
