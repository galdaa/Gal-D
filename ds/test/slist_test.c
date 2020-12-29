/*********************************************************
ESCRIPTION: Test of implementation functions of 
	singly link list.
Athor: Gal Dahan
Reviewer:---
**********************************************************/

#include <stdio.h>/*printf*/
#include <stddef.h>   /* size_t */
#include "slist.h"

void SLLCreateAndDestroyTest(void);
void SLLInsertBeforeTest(void);
void SLLPushBackTest(void);
void SLLPopBackTest(void);
void SLLFindTest(void);
int IntNCompare(const void *one, const void *other);
void SLLRemoveTest(void);
void SLLIsEmptyTest(void);
void SLLSetAndGetData(void);
void SLLNextTest(void);
void SLLBeginTest(void);
void SLLEndTest(void);
void SLLIsSameIterTest(void);
void SLLForEachTest(void);
int Print(void *data, void *params);
void SLLSizeTest(void);

int main()
{
	SLLCreateAndDestroyTest();
	SLLInsertBeforeTest();
	SLLPushBackTest();
	SLLPopBackTest();
	SLLFindTest();
	SLLRemoveTest();
	SLLIsEmptyTest();
	SLLSetAndGetData();
	SLLNextTest();
	SLLBeginTest();
	SLLEndTest();
	SLLIsSameIterTest();
	SLLForEachTest();
	SLLSizeTest();
	
	return 0;
}

void SLLCreateAndDestroyTest(void)
{
	sllist_t *ptr = SLLCreate();
	
	if (NULL == ptr)
	{	
		printf("SLLCreateTest FAILED***\n");
	}
	
	printf("SLLCreateTest SUCCESS\n");
	SLLDestroy(ptr);
	printf("SLLDestroyTest SUCCESS (not crashed)\n");
}


void SLLInsertBeforeTest(void)
{
	sllist_t *ptr = SLLCreate();
	sllist_iter_t node;
	int num = 5;
	int num2 = 4;
	SLLPushBack(ptr, &num);
	SLLPushBack(ptr, &num2);
	num = 3;
	SLLPushBack(ptr, &num);
	node = SLLFind(ptr, &num2, &IntNCompare);
	num = 9;
	
	if (SLLEnd(ptr) == SLLInsertBefore(ptr, node, &num))
	{
		printf("SLLInsertBeforeTest FAILED***\n");
	}
	else
	{
		printf("SLLInsertBeforeTest SUCCESS\n");
	}
	
	SLLDestroy(ptr);
}

void SLLPushBackTest(void)
{
	sllist_t *ptr = SLLCreate();
	int num = 5;
	sllist_iter_t new_node = SLLPushBack(ptr, &num);
	
	if (SLLEnd(ptr) == new_node)
	{
		printf("SLLPushBackTest FAILED***\n");
	}
	else
	{
		printf("SLLPushBackTest SUCCESS\n");
	}
	
	SLLDestroy(ptr);
}

void SLLPopBackTest(void)
{
	sllist_t *ptr = SLLCreate();
	int num = 5;
	SLLPushBack(ptr, &num);
	SLLPopBack(ptr);
	printf("SLLPopBackTest SUCCESS (not crashed)\n");
	SLLDestroy(ptr);
}

void SLLFindTest(void)
{
	sllist_t *ptr = SLLCreate();
	int num = 5;
	
	SLLPushBack(ptr, &num);
	num = 3;
	SLLPushBack(ptr, &num);
	
	if (SLLEnd(ptr) == SLLFind(ptr, &num, &IntNCompare))
	{
		printf("SLLFindTest FAILED***\n");
	}
	else
	{
		printf("SLLFindTest SUCCESS\n");
	}
	
	SLLDestroy(ptr);
}

int IntNCompare(const void *one, const void *other)
{
	return (*(int *) one != *(int *)other);
}

void SLLRemoveTest(void)
{
	sllist_t *ptr = SLLCreate();
	sllist_iter_t node;
	int num = 5;
	int num2 = 4;
	SLLPushBack(ptr, &num);
	SLLPushBack(ptr, &num2);
	num = 3;
	SLLPushBack(ptr, &num);
	node = SLLFind(ptr, &num2, &IntNCompare);
	SLLRemove(ptr, node);
	printf("SLLRemoveTest SUCCESS(not crashed)\n");
	SLLDestroy(ptr);
}

void SLLIsEmptyTest(void)
{	
	sllist_t *ptr = SLLCreate();
	int num = 5;
	
	if (1 == SLLIsEmpty(ptr))
	{
		printf("SLLIsEmptyTest SUCCESS (empty)\n");
	}
	else
	{
		printf("SLLIsEmptyTest FAILED (empty) ***\n");
	}
	
	SLLPushBack(ptr, &num);
	
	if (0 == SLLIsEmpty(ptr))
	{
		printf("SLLIsEmptyTest SUCCESS (non empty)\n");
	}
	else
	{
		printf("SLLIsEmptyTest FAILED (non empty) ***\n");
	}
	 
	SLLDestroy(ptr);
}

void SLLSetAndGetData(void)
{
	sllist_t *ptr = SLLCreate();
	sllist_iter_t node = NULL;
	int num = 5;
	
	SLLPushBack(ptr, &num);
	node = SLLFind(ptr, &num, &IntNCompare);

	
	if(0 == SLLSetData(node, &num))
	{
		printf("SLLSetData SUCCESS\n");
		
		if (num == *(int *) SLLGetData(node))
		{
			printf("SLLGetData SUCCESS\n");
		}
		else
		{
			printf("SLLGetData FAILED***\n");
		}
	}
	else
	{
		printf("SLLSetData FAILED***\n");
		printf("SLLGetData uncheck**\n");
	}
	
	SLLDestroy(ptr);
}

void SLLNextTest(void)
{ /*assumming every push in defrent assress!*/
	sllist_t *ptr = SLLCreate();
	sllist_iter_t node = NULL;
	int num = 5;
	int num2 = 4;
	int num3 = 3;
	SLLPushBack(ptr, &num);
	SLLPushBack(ptr, &num2);
	SLLPushBack(ptr, &num3);
	/* 5 -> 4 -> 3 -> end */
	node = SLLFind(ptr, &num2, &IntNCompare);

	if (SLLEnd(ptr) == SLLNext(node))
	{
		printf("SLLNextTest FAILED***\n");
	}
	else
	{
		printf("SLLNextTest SUCCESS\n");
	}
	
	num3 = 3;
	node = SLLFind(ptr, &num3, &IntNCompare);

	if (SLLEnd(ptr) != SLLNext(node))
	{
		printf("SLLNextTest FAILED (last)***\n");
	}
	else
	{
		printf("SLLNextTest SUCCESS (last)\n");
	}
	
	SLLDestroy(ptr);
}

void SLLBeginTest(void)
{
	sllist_t *ptr = SLLCreate();
	int num = 5;
	sllist_iter_t head = NULL;
	head = SLLBegin(ptr);
	
	if (SLLEnd(ptr) == SLLBegin(ptr))
	{
		printf("SLLBeginTest SUCCESS (empty)\n");
	}
	else
	{
		printf("SLLBeginTest FAILED (empty) ***\n");
	}
	
	SLLPushBack(ptr, &num);
	
	if (head == SLLBegin(ptr))
	{
		printf("SLLBeginTest SUCCESS (non empty)\n");
	}
	else
	{
		printf("SLLBeginTest FAILED (non empty) ***\n");
	}
	 
	SLLDestroy(ptr);
}

void SLLEndTest(void)
{
	sllist_t *ptr = SLLCreate();
	int num = 5;
	sllist_iter_t end = NULL;
	end = SLLEnd(ptr);
	
	if (NULL != end)
	{
		printf("SLLEndTest SUCCESS (empty)\n");
	}
	else
	{
		printf("SLLEndTest FAILED (empty) ***\n");
	}
	
	SLLPushBack(ptr, &num);
	
	if (end != SLLEnd(ptr))
	{
		printf("SLLEndTest SUCCESS (non empty)\n");
	}
	else
	{
		printf("SLLEndTest FAILED (non empty) ***\n");
	}
	 
	SLLDestroy(ptr);
}

void SLLIsSameIterTest(void)
{
	sllist_t *ptr = SLLCreate();
	sllist_iter_t node1 = NULL;
	sllist_iter_t node2 = NULL;
	int num = 3;
	int num1 = 5;
	int num2 = 15;
	SLLPushBack(ptr, &num1);
	SLLPushBack(ptr, &num2);
	node1 = SLLFind(ptr, &num1, &IntNCompare);
	node2 = SLLFind(ptr, &num2, &IntNCompare);

	SLLSetData(node1, &num);
	SLLSetData(node2, &num);
	
	if(1 == SLLIsSameIter(node1, node1))
	{
		printf("SLLIsSameIterTest SUCCESS (same)\n");
	}
	else
	{
		printf("SLLIsSameIterTest FAILED (same)***\n");
	}
	
	if(0 == SLLIsSameIter(node1, node2))
	{
		printf("SLLIsSameIterTest SUCCESS\n");
	}
	else
	{
		printf("SLLIsSameIterTest FAILED***\n");
	}
	
	SLLDestroy(ptr);
}

void SLLForEachTest(void)
{
	sllist_t *ptr = SLLCreate();
	sllist_iter_t from;
	sllist_iter_t to;
	int num = 5;
	SLLPushBack(ptr, &num);
	num = 4;
	SLLPushBack(ptr, &num);
	num = 3;
	SLLPushBack(ptr, &num);
	to = SLLFind(ptr, &num, &IntNCompare);
	num = 5;
	from = SLLFind(ptr, &num, &IntNCompare);

	if (0 != SLLForEach(ptr, from, to, &Print, &num))
	{
		printf("SLLForEachTest FAILED***\n");
	}
	else
	{
		printf("SLLForEachTest SUCCESS\n");
	}
	
	SLLDestroy(ptr);
}

int Print(void *data, void *params)
{
	if(NULL == data || NULL == params)
	{
		return 1;
	}
	
	printf("%d + %d = %d \n", *(int *)data, *(int *)params, *(int *)data + *(int *)params);
	return 0;
}

void SLLSizeTest(void)
{
	sllist_t *ptr = SLLCreate();
	int num = 5;
	
	if (0 == SLLSize(ptr)) 
	{
		printf("SLLSizeTest SUCCESS (empty)\n");
	}
	else
	{
		printf("SLLSizeTest FAILED (empty)***\n");
	}
	
	SLLPushBack(ptr, &num);
	
	if (1 == SLLSize(ptr))
	{
		printf("SLLSizeTest SUCCESS %d\n", (int ) SLLSize(ptr));
	}
	else
	{
		printf("SLLSizeTest FAILED %d***\n", (int ) SLLSize(ptr));
	}
	
	SLLDestroy(ptr);
}


