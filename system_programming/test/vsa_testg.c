/*********************************************************
ESCRIPTION: Test functions on  VSA.
Athor: Gal Dahan
Reviewer: ---
**********************************************************/

#include <stdio.h>		/*printf*/
#include <sys/types.h>   	/* size_t, ssize_t */
#include <string.h>
#include <stdlib.h>
#include "tests.h"
#include "vsa.h"

#define SIZE 120

void Test(void);

int main()
{
	Test();
	return 0;
}

void Test(void)
{
	int *pool = (int *) malloc(sizeof(int) * SIZE);
	size_t num_bytes = SIZE;
	size_t chunk_size = 10;
	int *ptr;
	vsa_t * vsa = VSAInit(pool, num_bytes);
	
	printf("VSAInit Sucsses\n");
	
	printf("VSAMaxFreeChunk Sucsses with:%lu\n", VSAMaxFreeChunk(vsa));
	
	NTEST("VSAAlloc", VSAAlloc(vsa, chunk_size), NULL);
	
	printf("VSAMaxFreeChunk Sucsses with:%lu\n", VSAMaxFreeChunk(vsa));
	
	NTEST("VSAAlloc", VSAAlloc(vsa, chunk_size), NULL);
	NTEST("VSAAlloc", VSAAlloc(vsa, chunk_size), NULL);
	
	chunk_size = SIZE/2;
	
	printf("VSAMaxFreeChunk Sucsses with:%lu\n", VSAMaxFreeChunk(vsa));
	
	NTEST("VSAAlloc", ptr = VSAAlloc(vsa, chunk_size), NULL);
	
	printf("VSAMaxFreeChunk Sucsses with:%lu\n", VSAMaxFreeChunk(vsa));
	
	VSAFree(ptr);
	
	printf("VSAFree Sucsses\n");
	
	printf("VSAMaxFreeChunk Sucsses with:%lu\n", VSAMaxFreeChunk(vsa));
	
	free(pool);
	
}


