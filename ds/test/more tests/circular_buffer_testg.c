/*********************************************************
ESCRIPTION: Test functions on circular buffer.
Athor: Gal Dahan
Reviewer:---
**********************************************************/

#include <stdio.h>/*printf*/
#include <stddef.h>   /* size_t */
#include <sys/types.h>   /* size_t, ssize_t */
#include "circular_buffer.h"
#include "tests.h"

void Test(void);

int main()
{
	Test();
	return 0;
}

void Test(void)
{

	size_t capacity = 15;
	char arr[10];
	char arr2[10];
	int i = 0;
	cbuffer_t *cb = CBufferCreate(capacity);

	if (NULL != cb)
	{
		TEST("CBufferCreate", 1, 1);
	}
	else
	{
		TEST("CBufferCreate", 0, 1);
	}
	
	printf("QCreate CBufferCreate (not crashed)\n");
	
	for (i = 0; i < 10; ++i)
	{
		arr[i] = '0' + i + 2;
	}

	TEST("CBufferIsEmpty", CBufferIsEmpty(cb), 1);
	TEST("CBufferIsFull", CBufferIsFull(cb), 0);
	TEST("CBufferSize", CBufferSize(cb), 0);
	TEST("CBufferFreeSpace", CBufferFreeSpace(cb), capacity);

	TEST("CBufferWrite", CBufferWrite(cb, arr, 10), 10);
	
	TEST("CBufferIsEmpty", CBufferIsEmpty(cb), 0);
	TEST("CBufferIsFull", CBufferIsFull(cb), 0);
	TEST("CBufferSize", CBufferSize(cb), 10);
	TEST("CBufferFreeSpace", CBufferFreeSpace(cb), capacity - 10);
	
	TEST("CBufferRead", CBufferRead(cb, arr2, 5), 5);/*10, 8*//*10 , 10*/
	/*printf("\nCBufferRead %ld\n ", CBufferRead(cb, arr2, 10));*/
	
	for (i = 0; i < 5; ++i)
	{
		printf(" %c ", arr2[i]);
	}

	TEST("CBufferWrite", CBufferWrite(cb, arr, 15), 10);/*10, 7*//*15 , 15*/
	TEST("CBufferIsFull", CBufferIsFull(cb), 1);
	
	CBufferDestroy(cb);
	printf("\nCBufferDestroy SUCCSESS (not crashed)\n");
}


