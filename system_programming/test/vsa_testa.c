#include <stdio.h>
#include <stdlib.h>

#include "vsa.h"

#define CHECK(test, str) ( (test) ? printf("passed %s tests\n", (str)) : printf("failed %s tests in line %d\n", (str), __LINE__))

#define WORD_SIZE sizeof(size_t)
#define ALLIGN(size) ((size) + (WORD_SIZE - (size) % WORD_SIZE) % WORD_SIZE)


struct vsa_mng
{
    size_t pool_size;
};

struct header
{
	size_t chunk_size;
	#ifndef NDEBUG
	size_t magic_number; 
	#endif
};


void InitTest(void);
void AllocTest(void);
void FreeTest(void);
void OperationTest(void);

int main()
{
	InitTest();
	AllocTest();
	FreeTest();
	OperationTest();
	return 0;
}

void InitTest(void)
{
	int flag = 0;
	void *pool = malloc(105);
	
	vsa_t *vsa = VSAInit((char*)pool + 5, 100);

	flag = ( 96 - sizeof(vsa_t) - sizeof(struct header) == VSAMaxFreeChunk(vsa)); /*100 - 5 (address allignment)*/ 
	CHECK(flag, "correct free space");   					      /*- 1 (block allignment - sizeof(structs))*/

	free(pool);
}


void AllocTest(void)
{
	int flag = 0;
	void *pool = malloc(105);
	
	vsa_t *vsa = VSAInit((char*)pool + 5, 100);
	size_t init_free = VSAMaxFreeChunk(vsa);

	VSAAlloc(vsa, 29);

	flag = ( init_free - 32 -  sizeof(struct header) == VSAMaxFreeChunk(vsa)); 
	CHECK(flag, "correct free space");

	VSAAlloc(vsa, VSAMaxFreeChunk(vsa));

	flag = ( 0 == VSAMaxFreeChunk(vsa));
 
	CHECK(flag, "correct free space");  					  

	free(pool);	
}

void FreeTest(void)
{
	int flag = 0;
	void *pool = malloc(105);
	void *chunk = NULL;
	vsa_t *vsa = VSAInit((char*)pool + 5, 100);
	size_t init_free = VSAMaxFreeChunk(vsa);

	chunk = VSAAlloc(vsa, 29);
	flag = ( init_free - 32 -  sizeof(struct header) == VSAMaxFreeChunk(vsa)); 
	CHECK(flag, "correct free space");



	VSAFree(chunk);
	flag = ( init_free == VSAMaxFreeChunk(vsa)); 
	CHECK(flag, "correct free space");

	free(pool);
	
}

void OperationTest(void)
{
	int flag = 0;
	void *pool = malloc(105);
	vsa_t *vsa = VSAInit((char*)pool + 5, 100);
	size_t init_free = VSAMaxFreeChunk(vsa);

	void *chunk1 = VSAAlloc(vsa, 29);
	void *chunk2 = VSAAlloc(vsa, 31);
	void *chunk3 = VSAAlloc(vsa, 8);

	printf("%d\n", init_free);

	flag = (NULL == chunk3);
	CHECK(flag, "no room");

	VSAFree(chunk1);
	
	printf("%d\n", VSAMaxFreeChunk(vsa));

	VSAFree(chunk2);
	
	printf("%d\n", VSAMaxFreeChunk(vsa));

	free(pool);
	
}


#if 0
void FreeTest(void)
{
	int flag = 0;
	void *pool = malloc(VSASuggestSize(5, 7)); /*will return 5 blocks of 8*/
	
	vsa_t *vsa = VSAInit((char*)pool + 3, 5, 7);

	void *ptr1 = VSAAlloc(vsa);
	void *ptr2 = VSAAlloc(vsa);
	void *ptr3 = VSAAlloc(vsa);
	void *ptr4 = VSAAlloc(vsa);
	void *ptr5 = VSAAlloc(vsa);

	VSAFree(vsa, ptr3);
	flag = ( 1 == VSACountFree(vsa));
	CHECK(flag, "correct free space");

	VSAFree(vsa, ptr1);
	flag = ( 2 == VSACountFree(vsa));
	CHECK(flag, "correct free space");

	VSAFree(vsa, ptr5);
	flag = ( 3 == VSACountFree(vsa));
	CHECK(flag, "correct free space");

	VSAFree(vsa, ptr2);
	flag = ( 4 == VSACountFree(vsa));
	CHECK(flag, "correct free space");

	VSAFree(vsa, ptr4);
	flag = ( 5 == VSACountFree(vsa));
	CHECK(flag, "correct free space");

	free(pool);

}

#endif





