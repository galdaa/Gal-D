/*************************************************************************** 
 * Description: Testing for circular buffer functions
 * Author: Oriel Nofekh
 * Reviewer: 
 *
 * Infinity Labs OL97
 ***************************************************************************/

#include <stdio.h>    /* printf */
#include <stdlib.h>   /* malloc, free */
#include <string.h>   /* strcmp */
#include <assert.h>   /* assert */
#include "circular_buffer.h"    /* cbuffer_t and declarations of all its functions */
#include "tests.h"              /* tools for easy and nicely styled testing */

static void TestCBufferCreateDestroy(void)
{
	size_t capacity = 256;
	cbuffer_t *buffer = CBufferCreate(capacity);
	
	CBufferDestroy(buffer);
}

static void Test1(void)
{
	char src[] = "hello world";
	char dest1[] = "\0\0\0\0\0\0\0\0\0\0\0\0";
	char dest2[] = "\0\0\0\0\0\0\0\0\0\0\0\0";
	size_t count = 0;
	
	size_t capacity = 5;
	cbuffer_t *buffer = CBufferCreate(capacity);
	
	TEST("IsEmpty", CBufferIsEmpty(buffer), 1);
	TEST("IsFull", CBufferIsFull(buffer), 0);
	TEST("Size", CBufferSize(buffer), 0);
	TEST("FreeSpace", CBufferFreeSpace(buffer), capacity);
	
	
	
	count = 12;
	
	CBufferWrite(buffer, src, count);
	
	TEST("IsEmpty", CBufferIsEmpty(buffer), 0);
	TEST("IsFull", CBufferIsFull(buffer), 1);
	TEST("Size", CBufferSize(buffer), capacity);
	TEST("FreeSpace", CBufferFreeSpace(buffer), 0);
	
	CBufferRead(buffer, dest1, count);
	
	TEST("IsEmpty", CBufferIsEmpty(buffer), 1);
	TEST("IsFull", CBufferIsFull(buffer), 0);
	TEST("Size", CBufferSize(buffer), 0);
	TEST("FreeSpace", CBufferFreeSpace(buffer), capacity);
	
	TEST("Write and Read", 0 == strcmp(dest1, "hello"), 1);
	
	
	
	count = 3;
	
	CBufferWrite(buffer, src, count);
	
	TEST("IsEmpty", CBufferIsEmpty(buffer), 0);
	TEST("IsFull", CBufferIsFull(buffer), 0);
	TEST("Size", CBufferSize(buffer), 3);
	TEST("FreeSpace", CBufferFreeSpace(buffer), capacity-3);
	
	CBufferRead(buffer, dest2, count);
	
	TEST("IsEmpty", CBufferIsEmpty(buffer), 1);
	TEST("IsFull", CBufferIsFull(buffer), 0);
	TEST("Size", CBufferSize(buffer), 0);
	TEST("FreeSpace", CBufferFreeSpace(buffer), capacity);
	
	TEST("Write and Read", 0 == strcmp(dest2, "hel"), 1);
	
	
	
	CBufferDestroy(buffer);
}

static void Test2(void)
{
	char src[] = "You are wrong";
	char dest1[] = "\0\0\0\0\0\0\0\0\0\0\0\0";
	char dest2[] = "\0\0\0\0\0\0\0\0\0\0\0\0";
	size_t count = 0;
	
	size_t capacity = 7;
	cbuffer_t *buffer = CBufferCreate(capacity);
	
	TEST("IsEmpty", CBufferIsEmpty(buffer), 1);
	TEST("IsFull", CBufferIsFull(buffer), 0);
	TEST("Size", CBufferSize(buffer), 0);
	TEST("FreeSpace", CBufferFreeSpace(buffer), capacity);
	
	
	
	count = 3;
	CBufferWrite(buffer, src, count);
	CBufferWrite(buffer, src, count);
	
	TEST("IsEmpty", CBufferIsEmpty(buffer), 0);
	TEST("IsFull", CBufferIsFull(buffer), 0);
	TEST("Size", CBufferSize(buffer), capacity-1);
	TEST("FreeSpace", CBufferFreeSpace(buffer), 1);
	
	count = 6;
	CBufferRead(buffer, dest1, count);
	
	TEST("IsEmpty", CBufferIsEmpty(buffer), 1);
	TEST("IsFull", CBufferIsFull(buffer), 0);
	TEST("Size", CBufferSize(buffer), 0);
	TEST("FreeSpace", CBufferFreeSpace(buffer), capacity);
	
	TEST("Write and Read", 0 == strcmp(dest1, "YouYou"), 1);
	
	
	
	count = 23;
	CBufferWrite(buffer, src, count);
	count = 4;
	CBufferRead(buffer, dest1, count);
	count = 3;
	CBufferWrite(buffer, src, count);
	
	TEST("IsEmpty", CBufferIsEmpty(buffer), 0);
	TEST("IsFull", CBufferIsFull(buffer), 0);
	TEST("Size", CBufferSize(buffer), 6);
	TEST("FreeSpace", CBufferFreeSpace(buffer), capacity-6);
	
	count = 13;
	CBufferRead(buffer, dest2, count);
	
	TEST("IsEmpty", CBufferIsEmpty(buffer), 1);
	TEST("IsFull", CBufferIsFull(buffer), 0);
	TEST("Size", CBufferSize(buffer), 0);
	TEST("FreeSpace", CBufferFreeSpace(buffer), capacity);
	
	TEST("Write and Read", 0 == strcmp(dest2, "areYou"), 1);
	
	
	
	CBufferDestroy(buffer);
}

static void Test3(void)
{
	/* this test is specific for the case of a buffer with a capacity of 1 */
	
	char src[] = "hello world";
	char dest1[] = "\0\0\0\0\0\0\0\0\0\0\0\0";
	size_t count = 0;
	
	size_t capacity = 1;
	cbuffer_t *buffer = CBufferCreate(capacity);
	
	TEST("IsEmpty", CBufferIsEmpty(buffer), 1);
	TEST("IsFull", CBufferIsFull(buffer), 0);
	TEST("Size", CBufferSize(buffer), 0);
	TEST("FreeSpace", CBufferFreeSpace(buffer), capacity);
	
	
	
	count = 12;
	
	CBufferWrite(buffer, src, count);
	
	TEST("IsEmpty", CBufferIsEmpty(buffer), 0);
	TEST("IsFull", CBufferIsFull(buffer), 1);
	TEST("Size", CBufferSize(buffer), capacity);
	TEST("FreeSpace", CBufferFreeSpace(buffer), 0);
	
	CBufferRead(buffer, dest1, count);
	
	TEST("IsEmpty", CBufferIsEmpty(buffer), 1);
	TEST("IsFull", CBufferIsFull(buffer), 0);
	TEST("Size", CBufferSize(buffer), 0);
	TEST("FreeSpace", CBufferFreeSpace(buffer), capacity);
	
	TEST("Write and Read", 0 == strcmp(dest1, "h"), 1);
	
	
	
	CBufferDestroy(buffer);
}

static void Test4(void)
{
	/* this test focuses on the return values of CBufferWrite and CBufferRead */
	
	char src[] = "hello world";
	char dest1[] = "\0\0\0\0\0\0\0\0\0\0\0\0";
	size_t count = 0;
	
	size_t capacity = 10;
	cbuffer_t *buffer = CBufferCreate(capacity);
	
	TEST("Size", CBufferSize(buffer), 0);
	TEST("FreeSpace", CBufferFreeSpace(buffer), capacity);
	
	
	
	count = 16;
	count = CBufferWrite(buffer, src, count);
	TEST("CBufferWrite", count, 10);
	
	count = 3;
	count = CBufferRead(buffer, dest1, count);
	TEST("CBufferRead", count, 3);
	
	count = 5;
	count = CBufferRead(buffer, dest1, count);
	TEST("CBufferRead", count, 5);
	
	count = 7;
	count = CBufferRead(buffer, dest1, count);
	TEST("CBufferRead", count, 2);
	
	count = 7;
	count = CBufferRead(buffer, dest1, count);
	TEST("CBufferRead", count, 0);
	
	count = 5;
	count = CBufferWrite(buffer, src, count);
	TEST("CBufferWrite", count, 5);
	
	count = 1;
	count = CBufferWrite(buffer, src, count);
	TEST("CBufferWrite", count, 1);
	
	count = 5;
	count = CBufferWrite(buffer, src, count);
	TEST("CBufferWrite", count, 4);
	
	
	
	CBufferDestroy(buffer);
	
}



static void TestCBuffer(void)
{
	TestCBufferCreateDestroy();
	
	Test1();
	
	Test2();
	
	Test3();
	
	Test4();
	
	PASS;
}



int main(void)
{
	TestCBuffer();
	
	return 0;
}



