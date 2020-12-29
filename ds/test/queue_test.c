/*********************************************************
ESCRIPTION: Test functions on queue.
Athor: Gal Dahan
Reviewer:---
**********************************************************/

#include <stdio.h>/*printf*/
#include <stddef.h>   /* size_t */
#include "slist.h"
#include "queue.h"
#include "tests.h"

    
void Test(void);

int main()
{
	Test();
	return 0;
}

void Test(void)
{
	queue_t *queue = QCreate();
	queue_t *src_queue = NULL;
	int value = 5;
	int arr[5];
	int i = 0;
	
	for (i = 0; i < 5; ++i)
	{
		arr[i] = i;
	}
	
	if (NULL != queue)
	{
		TEST("QCreate", 1, 1);
	}
	else
	{
		TEST("QCreate", 0, 1);
	}
	printf("QCreate SUCCSESS (not crashed)\n");
	
	TEST("QIsEmpty", QIsEmpty(queue), 1);
	TEST("QPeek", QPeek(queue), NULL);
	TEST("QSize", QSize(queue), 0);
	TEST("QEnqueue", QEnqueue(queue, &value), 0);
	TEST("QIsEmpty", QIsEmpty(queue), 0);
	TEST("QSize", QSize(queue), 1);
	TEST("QPeek", QPeek(queue), &value);
	TEST("QDequeue", QDequeue(queue), &value);
	TEST("QIsEmpty", QIsEmpty(queue), 1);
	
	src_queue = QCreate();
	TEST("QEnqueue", QEnqueue(queue, arr), 0);
	TEST("QEnqueue", QEnqueue(queue, arr + 1), 0);
	TEST("QEnqueue", QEnqueue(src_queue, arr + 2), 0);
	TEST("QEnqueue", QEnqueue(src_queue, arr + 3), 0);
	TEST("QEnqueue", QEnqueue(src_queue, arr + 4), 0);
	TEST("QSize", QSize(src_queue), 3);
	TEST("QPeek", QPeek(src_queue), arr + 2);
	TEST("QAppend", QAppend(src_queue, queue), queue);
	TEST("QIsEmpty", QIsEmpty(src_queue), 1);
	
	QDestroy(queue);
	printf("QDestroy SUCCSESS (not crashed)\n");
	QDestroy(src_queue);
	printf("QDestroy SUCCSESS (not crashed)\n");
}
