/*********************************************************
ESCRIPTION: Implementation functions of sorts algorhitms.
Athor: Gal Dahan
Reviewer:---
**********************************************************/

#include <stdlib.h>     /* malloc, free*/
#include "sort.h" 	/* sort API */

static void swap(int *a, int *b);

static void CountingSortImpl(int *arr, int *histogram, int *dest, 
	size_t size,size_t histogram_size, int min, int bits_index, size_t nbits);
	
static void RadixSortImpl(int *arr, int *histogram, int *dest, 
			size_t size, size_t histogram_size, size_t nbits);
static int GetIndex(int elem, int round, size_t nbits);

static void ArrCopy(int *dest, int *src, size_t size);

static void ArrClr(int *arr, size_t size);

static void swap(int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

void BubbleSort(int *arr, size_t size)
{
	size_t i = 0;
	
	for (i = 0; i < size; ++i)
	{
		size_t flag = 0, j = 0;
		
		for (j = 0; j < size - i - 1; ++j)
		{
			
			if (arr[j] > arr[j+1])
			{
				swap(&arr[j] ,&arr[j+1]);
				flag = 1;
			}		
		
		}
	
		if (0 == flag)
		{
			break;
		}
	}
}

void SelectionSort(int *arr, size_t size)
{
	size_t i = 0;
	
	for (i = 0; i < size - 1; ++i)
	{
		size_t min_i = i, j = i + 1;
		
		for (j = i + 1 ; j < size; ++j)
		{
			if (arr[j] < arr[min_i])
			{
				min_i = j;
			}
		}
		
		swap(&arr[i], &arr[min_i]);
	}
}

void InsertionSort(int *arr, size_t size)
{
	size_t i = 1;
	
	for (i = 1; i < size; ++i)
	{
		size_t j = i;
		
		for (j = i; j > 0 && arr[j] < arr [j - 1]; --j)
		{
			swap(&arr[j], &arr[j - 1]);
		}
			
	}
}

#define BITS_IN_BYTE 8	
#define BITS_IN_NUM sizeof(int) * BITS_IN_BYTE

int CountingSort(int *arr, size_t size)
{
	int *dest = (int *) malloc(sizeof(int) * size);
	int *histogram = NULL;
	int min = 0, max = 0;
	size_t i = 0;
	
	if (NULL == dest)
	{
		return 1;
	}
	
	for(i = 1, min = arr[0], max = arr[0];
		i < size;
		++i)
	{
		min = ((arr[i] < min) ? arr[i] : min);
		max = ((arr[i] > max) ? arr[i] : max);
	}

	histogram = (int *) calloc((max - min + 1), sizeof(int));
	
	if (NULL != histogram)
	{

		CountingSortImpl(arr, histogram, dest, 
				size, (max - min + 1), min,
				0, BITS_IN_NUM);

		free(dest); dest = NULL;
		free(histogram); histogram = NULL;
		
		return 0;
	}
	
	free(dest); dest = NULL;
	
	return 1;
}

static void ArrCopy(int *dest, int *src, size_t size)
{
	size_t i = 0;
	
	for(i = 0 ; i < size; ++i)
	{
		dest[i] = src[i];
	}
}

static void ArrClr(int *arr, size_t size)
{
	size_t i = 0;
	
	for(i = 0 ; i < size; ++i)
	{
		arr[i] = 0;
	}
}

static void CountingSortImpl(int *arr, int *histogram, int *dest, 
				size_t size, size_t histogram_size, 
				int min, int bits_index, size_t nbits)
{
	int i = 0;
	
	for(i = 0; i < (int) size; ++i)
	{
		++histogram[GetIndex(arr[i], bits_index, nbits) - min];
	}
	
	for(i = 1; i < (int) histogram_size; ++i)
	{	
		histogram[i] += histogram[i - 1];
	}
	
	for(i = size - 1; i >= 0; --i)
	{
		dest[histogram[
			GetIndex(arr[i], bits_index, nbits) - min] - 1
			] = arr[i];
			
		--(histogram[GetIndex(arr[i], bits_index, nbits) - min]);
	}
	
	ArrCopy(arr, dest, size);
}

static int GetIndex(int elem, int round, size_t nbits)
{
    return (((size_t)elem >> (round * nbits)) & ((1UL << nbits) - 1UL));
}

int RadixSort(int *arr, size_t size, size_t nbits)
{
		
	int *dest = (int *) malloc(sizeof(int) * size); 
	int *histogram = NULL;
	
	if (NULL == dest)
	{
		return 1;
	}
	
	histogram = (int *) calloc((1 << nbits), sizeof(int));
	
	if (NULL != dest)
	{
		RadixSortImpl(arr, histogram, dest, size, (1 << nbits), nbits);
		
		free(dest); dest = NULL;
		free(histogram); histogram = NULL;
		
		return 0;
	}
	
	free(dest); dest = NULL;
	
	return 1;
}

static void RadixSortImpl(int *arr, int *histogram, int *dest, 
			size_t size, size_t histogram_size, size_t nbits)
{
	size_t i = 0;
	
	for (i = 0; nbits * i < BITS_IN_NUM; ++i)
	{
		CountingSortImpl(arr, histogram, dest, size, 
						histogram_size, 0, i, nbits);
		ArrClr(histogram, histogram_size);
	}
}
