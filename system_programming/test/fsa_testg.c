/*********************************************************
ESCRIPTION: Test functions on  FSA.
Athor: Gal Dahan
Reviewer: ---
**********************************************************/

#include <stdio.h>/*printf*/
#include <sys/types.h>   /* size_t, ssize_t */
#include <string.h>
#include <stdlib.h>
#include "tests.h"
#include "fsa.h"

void Test(void);

int main()
{
	Test();
	return 0;
}

void Test(void)
{
	size_t num_blocks = 20, block_size = 8, size = 0;
	int *pool = NULL;
	int *ptr = NULL;
	fsa_t *fsa = NULL;
	
	size = FSASuggestSize(num_blocks, block_size);
	
	printf("FSASuggestSize Sucsses with:%lu\n", size);
	pool = (int *) malloc(sizeof(int) * size);
	
	fsa = FSAInit(pool, num_blocks, sizeof(int));
	printf("FSAInit Sucsses\n");
	
	printf("FSACountFree Sucsses with:%lu\n", FSACountFree(fsa));
	ptr = (int *) FSAAlloc(fsa);
	*ptr = 9;
	printf("FSAAlloc Sucsses with:%d\n", *(int *)ptr);
	printf("FSACountFree Sucsses with:%lu\n", FSACountFree(fsa));
	FSAFree(fsa, ptr);
	printf("FSAFree Sucsses\n");
	printf("FSACountFree Sucsses with:%lu\n", FSACountFree(fsa));
	
	free(pool);
}


