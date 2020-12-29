
#include <stdio.h>
#include <stdlib.h>     /* malloc, free, size_t, rand, qsort, itoa */
#include <time.h>       /* time, clock_t, CLOCKS_PER_SEC */
#include "sort.h"

#define SIZE 5000
#define MAX_MOD 10000

void Test(void);
int Cmp(const void *a, const void *b);
void Qsort(int *arr, size_t size);
void Rsort(int *arr, size_t size);
void Csort(int *arr, size_t size);
double TestSort(int *arr, void (*sort)(int *arr, size_t size));
void ArrCopy(int *dest, int *src, size_t size);
int ArrCmp(int *dest, int *src, size_t size);

int main()
{
	Test();
	
	return 0;
}

/*void TimeComper(int *arr, size_t size, void (*sort_func)(int *arr, size_t size));*/
void Test(void)
{
	size_t size = SIZE;
	int *arr = (int *) malloc(sizeof(int) * size);
	int *copy = (int *) malloc(sizeof(int) * size);
	int *copy_sorted = (int *) malloc(sizeof(int) * size);
	size_t i = 0;
	
	/* initialization */
	/* Use current time for random generator */
	srand(time(NULL)); 
	
	for(i = 0 ; i < size; ++i)
	{
		arr[i] = rand() % MAX_MOD;
	}
	
	/* qsort */
	ArrCopy(copy, arr, size);	
	printf("Qsort time:        %f\n", TestSort(copy, Qsort));
	
	ArrCopy(copy_sorted, copy, size);
	if (!ArrCmp(copy_sorted, copy, size))
	{
		printf("Qsort Not Same!\n");
	}
	
	/* bubble sort */
	ArrCopy(copy, arr, size);
	printf("Bubble time:       %f\n", TestSort(copy, BubbleSort));
	
	if (!ArrCmp(copy_sorted, copy, size))
	{
		printf("Bubble Not Same!\n");
	}
	
	/* selection sort */
	ArrCopy(copy, arr, size);
	printf("Selection time:    %f\n", TestSort(copy, SelectionSort));
	
	if (!ArrCmp(copy_sorted, copy, size))
	{
		printf("Selection Not Same!\n");
	}
	
	/* insertion sort */
	ArrCopy(copy, arr, size);
	printf("Insertion time:    %f\n", TestSort(copy, InsertionSort));
	
	if (!ArrCmp(copy_sorted, copy, size))
	{
		printf("Insertion Not Same!\n");
	}
	
	/* counting sort */
	ArrCopy(copy, arr, size);
	printf("CountingSort time: %f\n", TestSort(copy, Csort));
	
	if (!ArrCmp(copy_sorted, copy, size))
	{
		/*int i = 0;

		for(i = 0; i < 5; ++i)
			printf("%d ",copy[i]);
		printf("\n");	
		
		for(i = 0; i < 5; ++i)
			printf("%d ",copy_sorted[i]);
		printf("\n");*/
		
		printf("CountingSort Not Same!\n");
		
	}
	
	/* radix sort */
	ArrCopy(copy, arr, size);
	printf("RadixSort time:    %f\n", TestSort(copy, Rsort));
	
	if (!ArrCmp(copy_sorted, copy, size))
	{	
		printf("RadixSort Not Same!\n");
	}
	
	free(arr);
	free(copy);
	free(copy_sorted); 

}

void ArrCopy(int *dest, int *src, size_t size)
{
	size_t i = 0;
	
	for(i = 0 ; i < size; ++i)
	{
		dest[i] = src[i];
	}
}

int ArrCmp(int *dest, int *src, size_t size)
{
	int is_same = 1;
	size_t i = 0;
		
	for(i = 0 ; i < size; ++i)
	{
		if (dest[i] != src[i])
		{
			is_same = 0;
			break;
		}
	}
	
	return is_same;
}

void Qsort(int *arr, size_t size)
{
   	qsort(arr, size, sizeof(int), &Cmp);
}

void Rsort(int *arr, size_t size)
{
   	RadixSort(arr, size, 2);
}

void Csort(int *arr, size_t size)
{
   	CountingSort(arr, size);
}
double TestSort(int *arr, void (*sort)(int *arr, size_t size))
{
	clock_t start;
	start = clock();
	sort(arr, SIZE);
	return (double)(clock() - start);
}

int Cmp(const void *a, const void *b)
{
	return *(int *) a - *(int *) b;
}
