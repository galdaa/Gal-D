/*********************************************************
ESCRIPTION: Test functions on Sorted Linked List.
Athor: Gal Dahan
Reviewer:---
**********************************************************/

#include <stdio.h>		/*printf*/
#include <stddef.h>   		/* size_t */
#include <sys/types.h>   	/* size_t, ssize_t */
#include "dlist.h"
#include "sorted_list.h"
#include "tests.h"

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
	srtlst_t *srtl = SRTLSTCreate(&IntNCompare);
	srtlst_t *copy = SRTLSTCreate(&IntNCompare);

	for(i = 0; i < 20; ++i)
		arr[i] = i * 2 + 1;
		
	if (NULL != srtl)
	{
		TEST("SRTLSTCreate", 1, 1);
	}
	else
	{
		TEST("SRTLSTCreate", 0, 1);
	}

	printf("SRTLSTCreate Sucsses  (not crashed)\n");


	TEST("SRTLSTIsEmpty", SRTLSTIsEmpty(srtl), 1);
	TEST("SRTLSTSize", SRTLSTSize(srtl), 0);
	TEST("SRTLSTNext", SRTLSTNext(SRTLSTEnd(srtl)), SRTLSTEnd(srtl));
	TEST("SRTLSTIsSameIter",SRTLSTIsSameIter(SRTLSTEnd(srtl), SRTLSTBegin(srtl)), 0);
	NTEST("SRTLSTBegin", SRTLSTBegin(srtl), SRTLSTEnd(srtl));
	
	TEST("SRTLSTInsert", SRTLSTInsert(srtl, arr + 1), 0);
	TEST("SRTLSTInsert", SRTLSTInsert(srtl, arr), 0);
	TEST("SRTLSTPrev", SRTLSTPrev(SRTLSTBegin(srtl)), SRTLSTBegin(srtl));


	TEST("SRTLSTIsEmpty", SRTLSTIsEmpty(srtl), 0);
	TEST("SRTLSTSize", SRTLSTSize(srtl), 2);
	TEST("SRTLSTIsSameIter",SRTLSTIsSameIter(SRTLSTEnd(srtl), SRTLSTBegin(srtl)), 0);
	TEST("SRTLSTGetData", SRTLSTGetData(SRTLSTBegin(srtl)), arr);/*sorted!*/
	TEST("SRTLSTInsert", SRTLSTInsert(srtl, arr + 3), 0);
	TEST("SRTLSTInsert", SRTLSTInsert(srtl, arr + 5), 0);
	TEST("SRTLSTInsert", SRTLSTInsert(srtl, arr + 2), 0);
	
	SRTLSTRemove(SRTLSTBegin(srtl));
	printf("SRTLSTRemove SUCCSESS (not crashed)\n");  
	SRTLSTPopBack(srtl);
	printf("SRTLSTPopBack SUCCSESS (not crashed)\n");
	SRTLSTPopFront(srtl);
	printf("SRTLSTPopFront SUCCSESS (not crashed)\n");
	TEST("SRTLSTInsert", SRTLSTInsert(srtl, arr), 0);
	TEST("SRTLSTForEach", SRTLSTForEach(SRTLSTBegin(srtl), SRTLSTEnd(srtl), &Print, arr), 0);	
	TEST("SRTLSTFind", SRTLSTIsSameIter(SRTLSTFind(srtl, SRTLSTBegin(srtl),SRTLSTEnd(srtl), arr + 5), SRTLSTEnd(srtl)), 1);
	TEST("SRTLSTFind", SRTLSTIsSameIter(SRTLSTFind(srtl, SRTLSTBegin(srtl),SRTLSTEnd(srtl), arr), SRTLSTBegin(srtl)), 1);
	
	TEST("SRTLSTFind", SRTLSTIsSameIter(SRTLSTFind(SRTLSTBegin(srtl),SRTLSTEnd(srtl), &IntNCompare, arr + 5), SRTLSTEnd(srtl)), 1);
	TEST("SRTLSTFind", SRTLSTIsSameIter(SRTLSTFind(SRTLSTBegin(srtl),SRTLSTEnd(srtl), &IntNCompare, arr), SRTLSTBegin(srtl)), 1);	
		
	TEST("SRTLSTInsert", SRTLSTInsert(copy, arr + 13), 0);
	TEST("SRTLSTInsert", SRTLSTInsert(copy, arr + 10), 0);
	TEST("SRTLSTInsert", SRTLSTInsert(copy, arr + 11), 0);	
	TEST("SRTLSTIsEmpty", SRTLSTIsEmpty(copy), 0);
	TEST("SRTLSTSize", SRTLSTSize(copy), 3);
	
	SRTLSTMerge(srtl, copy);
	TEST("SRTLSTIsEmpty", SRTLSTIsEmpty(copy), 1);
	TEST("SRTLSTInsert", SRTLSTInsert(copy, arr + 11), 0);
	
	SRTLSTDestroy(copy);     
	printf("SRTLSTDestroy SUCCSESS (not crashed)\n");
	
	TEST("SRTLSTForEach", SRTLSTForEach(SRTLSTBegin(srtl), SRTLSTEnd(srtl), &Print, arr), 0);

	
	SRTLSTDestroy(srtl);
	printf("SRTLSTDestroy SUCCSESS (not crashed)\n");
}

int IntNCompare(const void *one, const void *other)
{
	return (*(int *) one - *(int *)other);
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


