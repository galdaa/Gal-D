/*************************************************************************** 
 * Description: Testing for singly linked list functions
 * Author: Oriel Nofekh
 * Reviewer: 
 *
 * Infinity Labs OL97
 ***************************************************************************/

#include <stdio.h>    /* printf */
#include <stdlib.h>   /* malloc, free */
#include <assert.h>   /* assert */
#include "slist.h"    /* sllist_t, node_t and sllist_iter_t 
                                  and declarations of all its functions */

/* Used as "action" for the ForEach function */
int Print(void *data, void *params)
{
	(void) params;
	printf("Data = %d\n", *(int *) data);
	return 0;
}

/* Used as "action" for the ForEach function */
int Power3Times(void *data, void *params)
{
	*(int *) data = (*(int *) params) * 
	                (*(int *) data) * (*(int *) data) * (*(int *) data);
	return 0;
}

/* Used as "action" for the ForEach function */
int IsNegative(void *data, void *params)
{
	(void) params;
	if (0 > (*(int *) data))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

/* Used as "is_match" for the Find function */
int IsMatchValue(const void *one, const void *other)
{
	if ((*(int *) one) == (*(int *) other))
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

/* Used as "is_match" for the Find function */
int IsSameAddress(const void *one, const void *other)
{
	if ((*(int *) one) == (*(int *) other))
	{
		return 0;
	}
	else
	{
		return 1;
	}
}



/* Testing super-mega-gigantic function */
void TestSLList(void)
{
	static int data_arr1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
	static int data_arr2[] = {-1, -2, -3, -4, -5, -6, -7, -8, -9, -10, -11, -12, -13, -14, -15, -16};
	static int data_arr3[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
	int *data_arr_temp = NULL;
	size_t arr1_len = sizeof(data_arr1) / sizeof(data_arr1[0]);
	int *data = NULL;
	int value = 0;
	int mul = 0;
	size_t i = 0;
	int test_success = 0;
	int status = 0;
	int is_empty = 0;
	size_t size = 0;
	size_t size_expected = 0;
	sllist_t *lst = NULL;
	sllist_iter_t iter = NULL;
	
	/* create a list */
	lst = SLLCreate();
	printf("List was successfully Created!\n\n");
	
	
	
	/* check is empty and list size */
	is_empty = SLLIsEmpty(lst);
	if (!is_empty)
	{
		printf("    Error! --- --- --- --- --- --- --- --- --- --- --- ---\n"
		       "    List is empty, but SLLIsEmpty returned FALSE!\n\n");
	}
	
	size = SLLSize(lst);
	size_expected = 0;
	if (size_expected != size)
	{
		printf("    Error! --- --- --- --- --- --- --- --- --- --- --- ---\n"
		       "    List size is %lu, but SLLSize returned %lu !\n\n", size_expected, size);
	}
	
	
	
	/* PushBack 16 times */
	for (i = 0; i < arr1_len; ++i)
	{
		data = data_arr1 + i; 
		iter = SLLPushBack(lst, data);
		
		if (SLLIsSameIter(SLLEnd(lst), iter))   /*(SLLEnd(lst) == iter)*/
		{
			/* it failed */
			printf("In iteration %lu, PushBack failed.\n"
			       "Exiting Test.\n\n", i);
			return;
		}
	}
	
	printf("List was PushedBack 16 times!\n"
	       "Entered integers from 1 to 16.\n\n");
	
	/* list looks like this now:
	 * 1, 2, 3, 4, ..., 15, 16 */
	
	/* go over the list, and make sure all values are correct */
	test_success = 1;
	for (iter =  SLLBegin(lst), i = 0;
	     !SLLIsSameIter(SLLEnd(lst), iter);   /* SLLEnd(lst) != iter;*/
	     iter = SLLNext(iter), ++i)
	{
		data = (int *) SLLGetData(iter);
		if (*data != data_arr1[i])
		{
			test_success = 0;
			printf("    Error! --- --- --- --- --- --- --- --- --- --- --- ---\n"
			       "    In iteration %lu, value stored in list was %d, "
			       "    while it should have been %d.\n", i, *data, data_arr1[i]);
		}
	}
	if (test_success)
	{
		printf("All 16 integers were correctly placed in the list!\n");
	}
	printf("\n");
	
	
	
	/* check is empty and list size */
	is_empty = SLLIsEmpty(lst);
	if (is_empty)
	{
		printf("    Error! --- --- --- --- --- --- --- --- --- --- --- ---\n"
		       "    List is not empty, but SLLIsEmpty returned TRUE!\n\n");
	}
	
	size = SLLSize(lst);
	size_expected = 16;
	if (size_expected != size)
	{
		printf("    Error! --- --- --- --- --- --- --- --- --- --- --- ---\n"
		       "    List size is %lu, but SLLSize returned %lu !\n\n", size_expected, size);
	}
	
	
	
	/* use InsertBefore to put the minus of each integer before it */
	for (iter =  SLLBegin(lst), i = 0;
	     !SLLIsSameIter(SLLEnd(lst), iter);   /* SLLEnd(lst) != iter;*/
	     iter = SLLNext(iter), ++i)
	{
		data = data_arr2 + i;
		iter = SLLInsertBefore(lst, iter, data);
		if (SLLIsSameIter(SLLEnd(lst), iter))   /*(SLLEnd(lst) == iter)*/
		{
			/* it failed */
			printf("    In iteration %lu, InsertBefore failed.\n"
			       "    Exiting Test.\n\n", i);
			return;
		}
		if (data != (int *) SLLGetData(iter))
		{
			printf("    Error! --- --- --- --- --- --- --- --- --- --- --- ---\n"
			       "    InsertBefore should return a pointer to the node with the new data !!!\n"
			       "    (in iteration %lu\n", i);
		}
		iter = SLLNext(iter);
	}
	printf("Entered integers from -1 to -16, e.g. -4 was entered before 4.\n"
	       "Was done using InsertBefore.\n\n");
	
	/* list looks like this now:
	 * -1, 1, -2, 2, -3, 3, ..., -15, 15, -16, 16 */
	
	/* go over the list, and make sure all values are correct */
	test_success = 1;
	for (iter =  SLLBegin(lst), i = 0;
	     !SLLIsSameIter(SLLEnd(lst), iter);   /* SLLEnd(lst) != iter;*/
	     iter = SLLNext(iter), ++i)
	{
		data = (int *) SLLGetData(iter);
		data_arr_temp = (1 == i % 2) ? data_arr1 : data_arr2; 
		if (*data != data_arr_temp[i/2])
		{
			test_success = 0;
			printf("    Error! --- --- --- --- --- --- --- --- --- --- --- ---\n"
			       "    In iteration %lu, value stored in list was %d, "
			       "    while it should have been %d.\n", i, *data, data_arr_temp[i/2]);
		}
	}
	if (test_success)
	{
		printf("All 32 integers were correctly placed in the list!\n");
	}
	printf("\n");
	
	
	
	/* check is empty and list size */
	is_empty = SLLIsEmpty(lst);
	if (is_empty)
	{
		printf("    Error! --- --- --- --- --- --- --- --- --- --- --- ---\n"
		       "    List is not empty, but SLLIsEmpty returned TRUE!\n\n");
	}
	
	size = SLLSize(lst);
	size_expected = 32;
	if (size_expected != size)
	{
		printf("    Error! --- --- --- --- --- --- --- --- --- --- --- ---\n"
		       "    List size is %lu, but SLLSize returned %lu !\n\n", size_expected, size);
	}
	
	
	
	/* use GetData and SetData to flip each two consecutive elements */
	for (iter =  SLLBegin(lst), i = 0;
	     !SLLIsSameIter(SLLEnd(lst), iter);   /* SLLEnd(lst) != iter;*/
	     iter = SLLNext(iter), ++i)
	{
		data_arr_temp = (1 == i % 2) ? data_arr2 : data_arr1; 
		data = data_arr_temp + i/2;
		status = SLLSetData(iter, data);
		if (0 != status)
		{
			/* it failed */
			printf("    In iteration %lu, SLLSetData failed.\n"
			       "    Exiting Test.\n\n", i);
			return;
		}
	}
	printf("Integers in the list were set this way: 1,-1, 2,-2, ...\n"
	       "Was done using SetData.\n\n");
	
	/* list looks like this now:
	 * 1, -1, 2, -2, 3, -3, ..., 15, -15, 16, -16 */
	
	/* go over the list, and make sure all values are correct */
	test_success = 1;
	for (iter =  SLLBegin(lst), i = 0;
	     !SLLIsSameIter(SLLEnd(lst), iter);   /* SLLEnd(lst) != iter;*/
	     iter = SLLNext(iter), ++i)
	{
		data = (int *) SLLGetData(iter);
		data_arr_temp = (1 == i % 2) ? data_arr2 : data_arr1; 
		if (*data != data_arr_temp[i/2])
		{
			test_success = 0;
			printf("    Error! --- --- --- --- --- --- --- --- --- --- --- ---\n"
			       "    In iteration %lu, value stored in list was %d, "
			       "    while it should have been %d.\n", i, *data, data_arr_temp[i/2]);
		}
	}
	if (test_success)
	{
		printf("All 32 integers were correctly placed in the list!\n");
	}
	printf("\n");
	
	
	
	/* remove last 24 elements */
	for (i = 0; i < 24; ++i)
	{
		SLLPopBack(lst);
		
		size = SLLSize(lst);
		size_expected = 32 - i - 1;
		if (size_expected != size)
		{
			printf("    Error! --- --- --- --- --- --- --- --- --- --- --- ---\n"
			       "    List size is %lu, but SLLSize returned %lu !\n\n", size_expected, size);
		}
	}
	printf("Removed last 24 elements, 8 elements remained.\n"
	       "Was done using PopBack.\n\n");
	       
	/* list looks like this now:
	 * 1, -1, 2, -2, 3, -3, 4, -4 */
	
	
	
	/* remove all elements that contain negative data */
	for (iter =  SLLBegin(lst);
	     !SLLIsSameIter(SLLEnd(lst), iter);   /* SLLEnd(lst) != iter;*/
	     )
	{
		sllist_iter_t iter_temp = NULL;
		if (0 > *(int *) SLLGetData(iter))
		{
			iter_temp = iter;
			/* iter = SLLNext(iter); */
			SLLRemove(lst, iter_temp);
		}
		else
		{
			iter = SLLNext(iter);
		}
	}
	
	/* list looks like this now:
	 * 1, 2, 3, 4 */
	
	/* go over the list, and make sure all values are correct */
	test_success = 1;
	for (iter =  SLLBegin(lst), i = 0;
	     !SLLIsSameIter(SLLEnd(lst), iter);   /* SLLEnd(lst) != iter;*/
	     iter = SLLNext(iter), ++i)
	{
		data = (int *) SLLGetData(iter);
		if (*data != data_arr1[i])
		{
			test_success = 0;
			printf("    Error! --- --- --- --- --- --- --- --- --- --- --- ---\n"
			       "    In iteration %lu, value stored in list was %d, "
			       "    while it should have been %d.\n", i, *data, data_arr1[i]);
		}
	}
	if (test_success)
	{
		printf("All 4 integers were correctly placed in the list!\n");
	}
	printf("\n");
	
	
	
	/* check is empty and list size */
	is_empty = SLLIsEmpty(lst);
	if (is_empty)
	{
		printf("    Error! --- --- --- --- --- --- --- --- --- --- --- ---\n"
		       "    List is not empty, but SLLIsEmpty returned TRUE!\n\n");
	}
	
	size = SLLSize(lst);
	size_expected = 4;
	if (size_expected != size)
	{
		printf("    Error! --- --- --- --- --- --- --- --- --- --- --- ---\n"
		       "    List size is %lu, but SLLSize returned %lu !\n\n", size_expected, size);
	}
	
	
	
	printf("Now print the data stored in the list, using ForEach\n(should be: 1, 2, 3, 4):\n");
	status = SLLForEach(lst, SLLBegin(lst), SLLEnd(lst), &Print, NULL);
	
	
	
	printf("Now raise all data to the power of three, and multiply by 5,\n"
	       "also using ForEach:\n");
	mul = 5;
	status = SLLForEach(lst, SLLBegin(lst), SLLEnd(lst), &Power3Times, (void *) &mul);
	
	/* go over the list, and make sure all values are correct */
	test_success = 1;
	for (iter =  SLLBegin(lst), i = 0;
	     !SLLIsSameIter(SLLEnd(lst), iter);   /* SLLEnd(lst) != iter;*/
	     iter = SLLNext(iter), ++i)
	{
		int expected_val = mul * data_arr3[i] * data_arr3[i] * data_arr3[i];
		
		data = (int *) SLLGetData(iter);
		if (*data != expected_val)
		{
			test_success = 0;
			printf("    Error! --- --- --- --- --- --- --- --- --- --- --- ---\n"
			       "    In iteration %lu, value stored in list was %d, "
			       "    while it should have been %d.\n", i, *data, expected_val);
		}
	}
	if (test_success)
	{
		printf("All 4 integers in the list had the correct values!\n");
	}
	printf("\n");
	
	
	
	/* use ForEach to check if the list contain a negative number in the data */
	printf("Now check if any of the data is negative, using ForEach:\n");
	status = SLLForEach(lst, SLLBegin(lst), SLLEnd(lst), &IsNegative, NULL);
	if (1 == status)
	{
		printf("    Error! --- --- --- --- --- --- --- --- --- --- --- ---\n"
		       "    ForEach concluded that there is a negative data, but there isn't!\n");
	}
	else
	{
		printf("ForEach concluded correctly that there is no negative data!\n");
	}
	printf("\n");
	
	printf("Now add a negative data using PushBack, and check again:\n");
	data = data_arr2 + 3;
	SLLPushBack(lst, data);
	status = SLLForEach(lst, SLLBegin(lst), SLLEnd(lst), &IsNegative, NULL);
	if (0 == status)
	{
		printf("    Error! --- --- --- --- --- --- --- --- --- --- --- ---\n"
		       "    ForEach concluded that there isn't any negative data, but there is!\n");
	}
	else
	{
		printf("ForEach concluded correctly that there is a negative data!\n");
	}
	printf("\n");
	
	
	
	/* use Find to check which of the elements hold the given value */
	printf("Now use Find to check if a certain data exists in the list or not.\n"
	       "we first check it when it's there (using two different functions),\n"
	       "then we PopBack it out and check it again:\n");
	test_success = 1;
	value = *data;
	iter = SLLFind(lst, (void*) &value, &IsMatchValue);
	if (SLLIsSameIter(SLLEnd(lst), iter) || *(int *) SLLGetData(iter) != value)
	{
		test_success = 0;
		printf("    Error! --- --- --- --- --- --- --- --- --- --- --- ---\n"
		       "    Find failed to find a data that was in the list!\n");
	}
	iter = SLLFind(lst, (void*) &value, &IsSameAddress);
	if (SLLIsSameIter(SLLEnd(lst), iter) || *(int *) SLLGetData(iter) != value)
	{
		test_success = 0;
		printf("    Error! --- --- --- --- --- --- --- --- --- --- --- ---\n"
		       "    Find failed to find a data that was in the list!\n");
	}
	SLLPopBack(lst);
	iter = SLLFind(lst, (void*) &value, &IsMatchValue);
	if (!SLLIsSameIter(SLLEnd(lst), iter))
	{
		test_success = 0;
		printf("    Error! --- --- --- --- --- --- --- --- --- --- --- ---\n"
		       "    Find did not return a pointer to the tail,\n"
		       "    despite the fact that the data wasn't in the list!\n");
	}
	iter = SLLFind(lst, (void*) &value, &IsSameAddress);
	if (!SLLIsSameIter(SLLEnd(lst), iter))
	{
		test_success = 0;
		printf("    Error! --- --- --- --- --- --- --- --- --- --- --- ---\n"
		       "    Find did not return a pointer to the tail,\n"
		       "    despite the fact that the data wasn't in the list!\n");
	}
	if (test_success)
	{
		printf("All tests of Find were successful!\n\n");
	}
	
	
	/* destroy the list */
	SLLDestroy(lst);
	lst = NULL;
	printf("List was successfully Destroyed!\n\n");
}

/*
still need to test:

sllist_iter_t SLLFind(const sllist_t *lst,
                   const void *value,
                   int (*is_match)(const void *one, const void *other));
*/


int main(void)
{
	TestSLList();
	
	return 0;
}




