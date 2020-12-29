/*************************************************************************** 
 * Description: Testing for queue functions
 * Author: Oriel Nofekh
 * Reviewer: 
 *
 * Infinity Labs OL97
 ***************************************************************************/

#include <stdio.h>    /* printf */
#include <stdlib.h>   /* malloc, free */
#include <assert.h>   /* assert */
#include "queue.h"    /* queue_t and declarations of all its functions */
#include "tests.h"    /* tools for easy and nicely styled testing */

static void TestQueueCreateDestroy(void)
{
	queue_t *queue = QCreate();
	QDestroy(queue);
	TEST("Create AND Destroy", 0, 0);
}

static void Test1(void)
{
	static int arr[] = {5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
	
	queue_t *queue = QCreate();
	TEST("TEST1 Q IS EMPTY", QIsEmpty(queue), 1);
	TEST("TEST1 Q HAS SIZE 0", QSize(queue), 0);
	
	QEnqueue(queue, arr + 10);
	TEST("TEST1 Q IS NOT EMPTY", QIsEmpty(queue), 0);
	TEST("TEST1 Q HAS SIZE 1", QSize(queue), 1);
	TEST("TEST1 PEEK", *(int *) QPeek(queue), *(int *) (arr + 10));
	
	QEnqueue(queue, arr + 8);
	TEST("TEST1 Q HAS SIZE 2", QSize(queue), 2);
	QEnqueue(queue, arr + 5);
	TEST("TEST1 Q HAS SIZE 3", QSize(queue), 3);
	TEST("TEST1 Q IS NOT EMPTY", QIsEmpty(queue), 0);
	TEST("TEST1 PEEK", *(int *) QPeek(queue), *(int *) (arr + 10));
	
	TEST("TEST1 DEQUEUE", *(int *) QDequeue(queue), *(int *) (arr + 10));
	TEST("TEST1 Q HAS SIZE 2", QSize(queue), 2);
	TEST("TEST1 DEQUEUE", *(int *) QDequeue(queue), *(int *) (arr + 8));
	TEST("TEST1 Q HAS SIZE 1", QSize(queue), 1);
	TEST("TEST1 DEQUEUE", *(int *) QDequeue(queue), *(int *) (arr + 5));
	TEST("TEST1 Q HAS SIZE 0", QSize(queue), 0);
	TEST("TEST1 Q IS EMPTY", QIsEmpty(queue), 1);
	
	TEST("TEST1 DEQUEUE EMPTY", QDequeue(queue), NULL);
	TEST("TEST1 DEQUEUE EMPTY", QDequeue(queue), NULL);
	TEST("TEST1 DEQUEUE EMPTY", QDequeue(queue), NULL);
	TEST("TEST1 Q HAS SIZE 0", QSize(queue), 0);
	TEST("TEST1 Q IS EMPTY", QIsEmpty(queue), 1);
	
	QDestroy(queue);
}

static void Test2(void)
{
	static int arr[] = {5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
	
	queue_t *queue_dest = QCreate();
	queue_t *queue_src = QCreate();
	
	QEnqueue(queue_dest, arr + 5);
	QEnqueue(queue_dest, arr + 7);
	QEnqueue(queue_dest, arr + 9);
	TEST("TEST2 Q HAS SIZE 3", QSize(queue_dest), 3);
	
	QAppend(queue_src, queue_dest);
	TEST("TEST2 Q HAS SIZE 3", QSize(queue_dest), 3);
	TEST("TEST2 Q HAS SIZE 0", QSize(queue_src), 0);
	
	QDestroy(queue_dest);
	QDestroy(queue_src);
}

static void Test3(void)
{
	static int arr[] = {5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
	
	queue_t *queue_dest = QCreate();
	queue_t *queue_src = QCreate();
	
	QEnqueue(queue_dest, arr + 0);
	QEnqueue(queue_dest, arr + 1);
	QEnqueue(queue_dest, arr + 2);
	TEST("TEST3 Q HAS SIZE 3", QSize(queue_dest), 3);
	
	QEnqueue(queue_src, arr + 3);
	QEnqueue(queue_src, arr + 4);
	QEnqueue(queue_src, arr + 5);
	QEnqueue(queue_src, arr + 6);
	TEST("TEST3 Q HAS SIZE 4", QSize(queue_src), 4);
	
	QAppend(queue_src, queue_dest);
	TEST("TEST3 Q HAS SIZE 7", QSize(queue_dest), 7);
	TEST("TEST3 Q HAS SIZE 0", QSize(queue_src), 0);
	
	TEST("TEST3 DEQUEUE", *(int *) QDequeue(queue_dest), *(int *) (arr + 0));
	TEST("TEST3 DEQUEUE", *(int *) QDequeue(queue_dest), *(int *) (arr + 1));
	TEST("TEST3 DEQUEUE", *(int *) QDequeue(queue_dest), *(int *) (arr + 2));
	TEST("TEST3 DEQUEUE", *(int *) QDequeue(queue_dest), *(int *) (arr + 3));
	TEST("TEST3 DEQUEUE", *(int *) QDequeue(queue_dest), *(int *) (arr + 4));
	TEST("TEST3 DEQUEUE", *(int *) QDequeue(queue_dest), *(int *) (arr + 5));
	TEST("TEST3 DEQUEUE", *(int *) QDequeue(queue_dest), *(int *) (arr + 6));
	
	QDestroy(queue_dest);
	QDestroy(queue_src);
}

static void Test4(void)
{
	static int arr[] = {5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
	
	queue_t *queue_dest = QCreate();
	queue_t *queue_src = QCreate();
	
	QEnqueue(queue_src, arr + 5);
	QEnqueue(queue_src, arr + 7);
	QEnqueue(queue_src, arr + 9);
	QEnqueue(queue_src, arr + 11);
	TEST("TEST4 Q HAS SIZE 3", QSize(queue_src), 4);
	
	QAppend(queue_src, queue_dest);
	TEST("TEST4 Q HAS SIZE 3", QSize(queue_dest), 4);
	TEST("TEST4 Q HAS SIZE 0", QSize(queue_src), 0);
	
	TEST("TEST3 DEQUEUE", *(int *) QDequeue(queue_dest), *(int *) (arr + 5));
	TEST("TEST3 DEQUEUE", *(int *) QDequeue(queue_dest), *(int *) (arr + 7));
	TEST("TEST3 DEQUEUE", *(int *) QDequeue(queue_dest), *(int *) (arr + 9));
	TEST("TEST3 DEQUEUE", *(int *) QDequeue(queue_dest), *(int *) (arr + 11));
	
	QDestroy(queue_dest);
	QDestroy(queue_src);
}



static void TestQueue(void)
{
	TestQueueCreateDestroy();
	
	Test1();
	
	Test2();
	
	Test3();
	
	Test4();
	
	PASS;
}



int main(void)
{
	TestQueue();
	
	return 0;
}



