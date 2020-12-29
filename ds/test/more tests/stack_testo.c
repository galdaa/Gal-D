/*************************************************************************** 
 * Description: Testing the bit array function implementations
 * Author: Oriel Nofekh
 * Reviewer: NONE
 *
 * Infinity Labs OL97
 ***************************************************************************/

#include <stdio.h>    /* printf, size_t */
#include "stack.h"   /* bit_array_t and all its functions */

/******************** Functions Declarations ********************/

void TestStackCreateDestroy(void);
void TestStackPush(void);
void TestStackPop(void);
void TestStackPeek(void);
void TestStackSize(void);
void TestStackIsEmpty(void);
void TestStackCapacity(void);
/*
static void PrintSuccesOrFailure(int is_success, char *function_name);
*/

/******************** main function ********************/

int main(void)
{
	
	TestStackCreateDestroy();
	
	TestStackPush();
	
	TestStackPop();
	
	TestStackPeek();
	TestStackSize();
	TestStackIsEmpty();
	TestStackCapacity();
	
	return 0;
}

/******************** Functions Implementations ********************/

void TestStackCreateDestroy(void)
{
	size_t element_size = 8;
	size_t capacity = 100;
	stack_t *stack = StackCreate(element_size, capacity);
	
	printf("Stack was created without crashing!\n");
	
	StackDestroy(stack);
	
	printf("Stack was destroyed without crashing!\n");
	
	printf("\n");
}

void TestStackPush(void)
{
	size_t element_size = 8;
	size_t capacity = 3;
	long num = 15;
	int status = 0;
	
	stack_t *stack = StackCreate(element_size, capacity);
	
	printf("Attempting to push 5 times to a stack with a capacitiy of 3:\n");
	
	status = StackPush(stack, &num);
	printf("StackPush finished with status %d\n", status);
	status = StackPush(stack, &num);
	printf("StackPush finished with status %d\n", status);
	status = StackPush(stack, &num);
	printf("StackPush finished with status %d\n", status);
	status = StackPush(stack, &num);
	printf("StackPush finished with status %d\n", status);
	status = StackPush(stack, &num);
	printf("StackPush finished with status %d\n", status);
	
	printf("\n");
	
	StackDestroy(stack);
}

void TestStackPop(void)
{
	size_t element_size = 8;
	size_t capacity = 3;
	long num = 15;
	int status = 0;
	
	stack_t *stack = StackCreate(element_size, capacity);
	
	status = StackPush(stack, &num);
	status = StackPush(stack, &num);
	status = StackPush(stack, &num);
	
	printf("Attempting to pop 5 times to a full stack with a capacitiy of 3:\n");
	
	status = StackPop(stack);
	printf("StackPop finished with status %d\n", status);
	status = StackPop(stack);
	printf("StackPop finished with status %d\n", status);
	status = StackPop(stack);
	printf("StackPop finished with status %d\n", status);
	status = StackPop(stack);
	printf("StackPop finished with status %d\n", status);
	status = StackPop(stack);
	printf("StackPop finished with status %d\n", status);
	
	printf("\n");
	
	StackDestroy(stack);
}



void TestStackPeek(void)
{
	size_t element_size = 8;
	size_t capacity = 3;
	long num1 = 15;
	long num2 = 27;
	long num3 = -101;
	
	stack_t *stack = StackCreate(element_size, capacity);
	
	StackPush(stack, &num1);
	StackPush(stack, &num2);
	StackPush(stack, &num3);
	
	printf("Stack of size 3, with values: %ld, %ld, %ld,\n"
	       "each time we Peek and then Pop:\n", num1, num2, num3);
	
	printf("StackPeek returned a pointer that points to the value: %ld\n", (*(long *) StackPeek(stack)));
	StackPop(stack);
	printf("StackPeek returned a pointer that points to the value: %ld\n", (*(long *) StackPeek(stack)));
	StackPop(stack);
	printf("StackPeek returned a pointer that points to the value: %ld\n", (*(long *) StackPeek(stack)));
	StackPop(stack);
	if (NULL == StackPeek(stack))
	{
		printf("StackPeek returned NULL, as expected\n");
	}
	else
	{
		printf("StackPeek did not return NULL, but it was expected to return NULL !!!\n");
	}
	
	printf("\n");
	
	StackDestroy(stack);
}

void TestStackSize(void)
{
	size_t element_size = 8;
	size_t capacity = 3;
	long num = 15;
	
	stack_t *stack = StackCreate(element_size, capacity);
	
	StackPush(stack, &num);
	StackPush(stack, &num);
	StackPush(stack, &num);
	
	printf("Stack of size 3, each time we get the size then we Pop:\n");
	
	printf("StackSize = %lu\n", StackSize(stack));
	StackPop(stack);
	printf("StackSize = %lu\n", StackSize(stack));
	StackPop(stack);
	printf("StackSize = %lu\n", StackSize(stack));
	StackPop(stack);
	printf("StackSize = %lu\n", StackSize(stack));
	StackPop(stack);
	printf("StackSize = %lu\n", StackSize(stack));
	
	printf("\n");
	
	StackDestroy(stack);
}

void TestStackIsEmpty(void)
{
	size_t element_size = 8;
	size_t capacity = 3;
	long num = 15;
	
	stack_t *stack = StackCreate(element_size, capacity);
	
	StackPush(stack, &num);
	StackPush(stack, &num);
	StackPush(stack, &num);
	
	printf("Stack of size 3, each time we check if empty and then we Pop:\n");
	
	printf("StackSize = %d\n", StackIsEmpty(stack));
	StackPop(stack);
	printf("StackSize = %d\n", StackIsEmpty(stack));
	StackPop(stack);
	printf("StackSize = %d\n", StackIsEmpty(stack));
	StackPop(stack);
	printf("StackSize = %d\n", StackIsEmpty(stack));
	StackPop(stack);
	printf("StackSize = %d\n", StackIsEmpty(stack));
	
	printf("\n");
	
	StackDestroy(stack);
}

void TestStackCapacity(void)
{
	size_t element_size = 8;
	size_t capacity = 122;
	long num = 15;
	
	stack_t *stack = StackCreate(element_size, capacity);
	
	printf("Stack of capacity: %lu\n", capacity);
	
	printf("StackCapacity = %lu\n", StackCapacity(stack));
	StackPush(stack, &num);
	printf("StackCapacity = %lu\n", StackCapacity(stack));
	StackPush(stack, &num);
	printf("StackCapacity = %lu\n", StackCapacity(stack));
	
	printf("\n");
	
	StackDestroy(stack);
}

/*
static void PrintSuccesOrFailure(int is_success, char *function_name)
{
	if (is_success)
	{
		printf("%s test was a SUCCESS\n", function_name);
	}
	else
	{
		printf("%s test was a FAILURE   !!!   !!!   !!!\n", function_name);
	}
}
*/












