#ifndef __SORT_H_OL97_ILRD__
#define __SORT_H_OL97_ILRD__

#include <stddef.h>   /* size_t */

/* o(n^2) */
void BubbleSort(int *arr, size_t size);

/* o(n^2) */
void SelectionSort(int *arr, size_t size);

/* o(n^2) */
void InsertionSort(int *arr, size_t size);

/* Non compare */

int CountingSort(int *arr, size_t size);

int RadixSort(int *arr, size_t size, size_t nbits);

#endif   /* __SORT_H_OL97_ILRD__ */
