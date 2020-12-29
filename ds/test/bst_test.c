#include <stdio.h>/*printf*/
#include "bst.h"
#include "tests.h"

static void Test(void);
static int IntCmp(const void *data, const void *input);
int IntPrint(void *data, void *params);

int main()
{
	Test();
	return 0;
}

static int IntCmp(const void *data, const void *input)
{
	*(int *)data - *(int *)input;
}

int IntPrint(void *data, void *params)
{
	printf("%d,%d \n", *(int *) data, *(int *) params);
}

#define SIZE 15
static void Test(void)
{
	bst_t *bst = BSTCreate(&IntCmp);
	int arr[SIZE];
	int i = 0;
	bst_iter_t iter = {0};
	
	for (i = 0; i < SIZE; ++i)
	{
		arr[i] = i;
	}
	
	if (NULL != bst)
	{
		TEST("QCreate", 1, 1);
	}
	else
	{
		TEST("QCreate", 0, 1);
	}
	
	TEST("BSTSize", BSTSize(bst), 0);
	TEST("BSTIsEmpty", BSTIsEmpty(bst), 1);
	
	iter = BSTInsert(bst, arr + 2);
	TEST("BSTIsSameIter(BSTInsert,BSTBegin)", 
		BSTIsSameIter(iter, BSTBegin(bst)), 1);
	TEST("BSTIsSameIter(BSTInsert,STEnd)", 
		BSTIsSameIter(BSTInsert(bst, arr + 1), BSTEnd(bst)), 0);
	iter = BSTInsert(bst, arr + 5);
	TEST("BSTGetData", *(int *)BSTGetData(iter), *(int *)(arr + 5));
	TEST("BSTSize", BSTSize(bst), 3);
	TEST("BSTIsEmpty", BSTIsEmpty(bst), 0);
	TEST("BSTGetData-BSTFind find", 
		*(int *)BSTGetData(BSTFind(bst, arr + 2)), *(int *)(arr + 2));
	TEST("BSTIsSameIter-BSTFind not find", 
		BSTIsSameIter(BSTFind(bst, arr + 9), BSTEnd(bst)), 1);
	
	TEST("BSTForEach",BSTForEach(BSTBegin(bst),
               BSTEnd(bst),
               &IntPrint,
               arr + 10), 
               0);
               
	TEST("BSTIsSameIter-BSTNext-BSTEnd", 
		BSTIsSameIter(BSTNext(BSTEnd(bst)), BSTEnd(bst)), 1);
	TEST("BSTIsSameIter-BSTPrev-BSTBegin", 
		BSTIsSameIter(BSTPrev(BSTBegin(bst)), BSTBegin(bst)), 1);
		
	TEST("BSTIsSameIter-BSTNext-iter?", 
		BSTIsSameIter(BSTNext(iter), BSTEnd(bst)), 0);
	TEST("BSTIsSameIter-BSTPrev-iter?", 
		BSTIsSameIter(BSTPrev(iter), BSTBegin(bst)), 0);
		
	TEST("BSTRemove =>BSTSize", BSTSize(bst), 2);
	BSTGetData(bst_iter_t iter);BSTBegin(const bst_t *tree); 
	BSTRemove(iter);
	TEST("BSTRemove =>BSTSize", BSTSize(bst), 2);
	
	BSTDestroy(bst);
}
