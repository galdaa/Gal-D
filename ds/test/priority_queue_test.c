/*********************************************************
ESCRIPTION: Test functions on Priority Queue.
Athor: Gal Dahan
Reviewer:---
**********************************************************/

#include <stdio.h>/*printf*/
#include <stddef.h>   /* size_t */
#include <sys/types.h>   /* size_t, ssize_t */
#include "tests.h"
#include "sorted_list.h"
#include "priority_queue.h"

void Test(void);
int IntCompare(const void *l, const void *r);
int Print(void *data, void *params);
int IntMach(const void *one, const void *other);

int main()
{
	Test();
	return 0;
}

void Test(void)
{
	int arr[20];
	int i = 0;
	pq_t *que = PQCreate(&IntCompare);

	for(i = 0; i < 20; ++i)
		arr[i] = i * 2 + 1;
		
	if (NULL != que)
	{
		TEST("PQCreate", 1, 1);
	}
	else
	{
		TEST("PQCreate", 0, 1);
	}

	printf("PQCreate Sucsses  (not crashed)\n");
printf("===Stage 1===\n");

	TEST("PQIsEmpty", PQIsEmpty(que), 1);
	TEST("PQSize", PQSize(que), 0);

printf("===Stage 2===\n");	
	TEST("PQEnqueue", PQEnqueue(que, arr), 0);
	TEST("PQIsEmpty", PQIsEmpty(que), 0);
	TEST("PQPeek", PQPeek(que), arr);
	TEST("PQDequeue", *(int *) PQDequeue(que), arr[0]);
	TEST("PQIsEmpty", PQIsEmpty(que), 1);

printf("===Stage 3===\n");
	TEST("PQEnqueue", PQEnqueue(que, arr + 3), 0);
	TEST("PQEnqueue", PQEnqueue(que, arr + 2), 0);
	TEST("PQEnqueue", PQEnqueue(que, arr + 5), 0);
	TEST("PQSize", PQSize(que), 3);
	TEST("PQErase", *(int *) PQErase(que, &IntMach, arr + 2), arr[2]);
printf("===Stage 4===\n");
	TEST("PQErase", PQErase(que, &IntMach, arr + 7), NULL);
	PQClear(que);
	TEST("PQIsEmpty after PQClear", PQIsEmpty(que), 1);

printf("===Stage 5===\n");
	PQDestroy(que);
	printf("PQDestroy SUCCSESS (not crashed)\n");
}

int IntCompare(const void *one, const void *other)
{
	return (*(int *) one - *(int *)other);
}

int IntMach(const void *one, const void *other)
{
	return (*(int *) one == *(int *)other);
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
