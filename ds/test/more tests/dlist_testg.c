/*********************************************************
ESCRIPTION: Test functions on Doubly Linked List.
Athor: Gal Dahan
Reviewer:---
**********************************************************/

#include <stdio.h>/*printf*/
#include <stddef.h>   /* size_t */
#include <sys/types.h>   /* size_t, ssize_t */
#include "tests.h"
#include "dlist.h"

void Test(void);
int IntNCompare(const void *one, const void *other);
int Print(void *data, void *params);

int main()
{
	Test();
	return 0;
}

void Test(void)
{
	int arr[20];
	int i = 0;
	dllist_t *dll = PQCreate(&);
	dllist_t *copy = DLLCreate();

	for(i = 0; i < 20; ++i)
		arr[i] = i * 2 + 1;
		
	if (NULL != dll)
	{
		TEST("DLLCreate", 1, 1);
	}
	else
	{
		TEST("DLLCreate", 0, 1);
	}

	printf("DLLCreate Sucsses  (not crashed)\n");

	TEST("DLLIsEmpty", DLLIsEmpty(dll), 1);
	TEST("DLLSize", DLLSize(dll), 0);
	TEST("DLLBegin", DLLBegin(dll), DLLEnd(dll));
	TEST("DLLIsSameIter",DLLIsSameIter(DLLEnd(dll), DLLBegin(dll)), 1);

	NTEST("DLLPushBack", DLLPushBack(dll, arr + 1 ), DLLEnd(dll));
	NTEST("DLLPushFront", DLLPushFront(dll, arr), DLLEnd(dll));

	TEST("DLLIsEmpty", DLLIsEmpty(dll), 0);
	TEST("DLLSize", DLLSize(dll), 2);
	NTEST("DLLBegin", DLLBegin(dll), DLLEnd(dll));
	TEST("DLLIsSameIter",DLLIsSameIter(DLLEnd(dll), DLLBegin(dll)), 0);

	TEST("DLLGetData", DLLGetData(DLLBegin(dll)), arr);
	DLLSetData(DLLBegin(dll), arr + 2);
	printf("DLLSetData Sucsses  (not crashed)\n");
	TEST("DLLGetData", DLLGetData(DLLBegin(dll)), arr + 2);
	DLLSetData(DLLBegin(dll), arr + 3);
	printf("DLLSetData Sucsses  (not crashed)\n");
	TEST("DLLGetData", DLLGetData(DLLEnd(dll)), NULL);

	DLLSetData(DLLNext(DLLBegin(dll)), arr + 4);
	printf("DLLSetData Sucsses  (not crashed)\n");
	TEST("DLLNext", DLLNext(DLLEnd(dll)), DLLEnd(dll));
	TEST("DLLPrev-DLLNext", DLLPrev(DLLNext(DLLBegin(dll))), DLLBegin(dll));
	TEST("DLLPrev", DLLPrev(DLLBegin(dll)), DLLBegin(dll));

	NTEST("DLLPushBack", DLLPushBack(dll, arr + 2), DLLEnd(dll));
	NTEST("DLLPushBack", DLLPushBack(dll, arr + 3), DLLEnd(dll));

	NTEST("DLLFind", DLLFind(DLLBegin(dll),
		      DLLEnd(dll),
		      arr + 2,
		      &IntNCompare), DLLEnd(dll));
		      
	TEST("DLLInsertBefore", DLLInsertBefore(
		DLLFind(DLLBegin(dll), DLLEnd(dll), arr + 1,&IntNCompare),
		 arr + 1),
		       0);          

	DLLRemove(DLLFind(DLLBegin(dll), DLLEnd(dll), arr + 2,&IntNCompare));
	printf("DLLRemove SUCCSESS (not crashed)\n");      

	TEST("DLLForEach", DLLForEach(DLLBegin(dll), DLLEnd(dll),
	       &Print,
	       arr + 10) , 0);

	TEST("DLLMultiFind", DLLMultiFind(DLLBegin(dll), DLLEnd(dll), copy,
				 arr + 1,
		 &IntNCompare), 0);

	NTEST("DLLPushBack", DLLPushBack(copy, arr + 4), DLLEnd(copy));

	DLLSplice(DLLBegin(copy), DLLEnd(copy), DLLEnd(dll));
	printf("DLLSplice SUCCSESS (not crashed)\n");

	TEST("DLLForEach", DLLForEach(DLLBegin(dll), DLLEnd(dll),
	&Print,
	arr + 11) , 0);

	NTEST("DLLPushBack", DLLPushBack(copy, arr + 5), DLLEnd(copy));
	DLLDestroy(copy);     

	DLLPopBack(dll);
	printf("DLLPopBack SUCCSESS (not crashed)\n");
	DLLPopFront(dll);
	printf("DLLPopFront SUCCSESS (not crashed)\n");
	TEST("DLLIsEmpty", DLLIsEmpty(dll), 0);
	DLLDestroy(dll);
	printf("DLLCreate SUCCSESS (not crashed)\n");
}

int IntCompare(const void *l, const void *r)
{
	return (*(int *) l - *(int *)r);
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


