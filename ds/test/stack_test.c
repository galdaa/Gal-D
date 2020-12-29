/*********************************************************
ESCRIPTION: Test of implementation functions of stack.
Athor: Gal Dahan
Reviewer:---
**********************************************************/

#include <stdio.h>/*printf*/
#include <stddef.h>   /* size_t */
#include <stdlib.h>

#include "../include/stack.h"   

void StackCreateDestroyTest(void);
void StackPushPopTest(void);
void StackPeekTest(void);
void StackSizeTest(void);
void StackIsEmptyTest(void);
void StackCapacityTest(void);

int main()
{
	StackCreateDestroyTest();
	StackPushPopTest();
	StackPeekTest();
	StackSizeTest();
	StackIsEmptyTest();
	StackCapacityTest();
	
	return 0;
}

void StackCreateDestroyTest(void)
{
	size_t size = 11;
	size_t cap = 50;
	stack_t *ptr;
	
	ptr = StackCreate(size, cap);
	
	if(NULL == ptr)
	{
		printf("StackCreate FAILED***\n");
	}
	else
	{
		printf("StackCreate SUCCESS\n");
		StackDestroy(ptr);
		printf("StackDestroy SUCCESS (not crashed)\n");
		ptr = NULL;
	}
}

void StackPushPopTest(void)
{
	size_t size = sizeof(int);
	size_t cap = 50;
	stack_t *ptr;
	int element = 0;
	ptr = StackCreate(size, cap);
	
 	/*push * 4*/
 	element = 5;
 	
 	if(0 != StackPush(ptr, &element))
 	{
 		printf("StackPush FAILED***\n");
 	}
 	else
 	{
 		printf("StackPush SUCCESS\n");
 	}
 	
 	element = 4;
 	
 	if(0 != StackPush(ptr, &element))
 	{
 		printf("StackPush FAILED***\n");
 	}
 	else
 	{
 		printf("StackPush SUCCESS\n");
 	}
 	
 	element = 3;
 	
 	if(0 != StackPush(ptr, &element))
 	{
 		printf("StackPush FAILED***\n");
 	}
 	else
 	{
 		printf("StackPush SUCCESS\n");
 	}
 	 
 	element = 2;
 	
 	if(0 != StackPush(ptr, &element))
 	{
 		printf("StackPush FAILED***\n");
 	}
 	else
 	{
 		printf("StackPush SUCCESS\n");
 	}
 	
	/*pop * 4*/
	if(0 != StackPop(ptr))
 	{
 		printf("StackPop FAILED***\n");
 	}
 	else
 	{
 		printf("StackPop SUCCESS\n");
 	}
 	
 	if(0 != StackPop(ptr))
 	{
 		printf("StackPop FAILED***\n");
 	}
 	else
 	{
 		printf("StackPop SUCCESS\n");
 	}
 	
 	if(0 != StackPop(ptr))
 	{
 		printf("StackPop FAILED***\n");
 	}
 	else
 	{
 		printf("StackPop SUCCESS\n");
 	}
 	
 	if(0 != StackPop(ptr))
 	{
 		printf("StackPop FAILED***\n");
 	}
 	else
 	{
 		printf("StackPop SUCCESS\n");
 	}

	StackDestroy(ptr);

}

void StackPeekTest(void)
{
	size_t size = sizeof(int);
	size_t cap = 50;
	stack_t *ptr;
	int element = 0;
	ptr = StackCreate(size, cap);
	
 	/*push * 4*/
 	element = 5;
 	StackPush(ptr, &element);
 	element = 4;
 	StackPush(ptr, &element);
 	
 	if(4 == *(int *) StackPeek(ptr))
  	{
 		printf("StackPeek SUCCESS\n");
 	}
 	else
 	{
 		printf("StackPeek FAILED***\n");
 	}
 	 	
	StackPop(ptr);
	
	if(5 == *(int *) StackPeek(ptr))
  	{
 		printf("StackPeek SUCCESS\n");
 	}
 	else
 	{
 		printf("StackPeek FAILED***\n");
 	}
 	
 	StackPop(ptr);
 	
 	if(NULL == StackPeek(ptr))
  	{
 		printf("StackPeek SUCCESS\n");
 	}
 	else
 	{
 		printf("StackPeek (empty) FAILED***\n");
 	}

 

	StackDestroy(ptr);

}

void StackSizeTest(void)
{
	size_t size = sizeof(int);
	size_t cap = 50;
	stack_t *ptr;
	int element = 19;
	ptr = StackCreate(size, cap);
	
	if(0 == StackSize(ptr))
	{
 		printf("StackSize SUCCESS\n");
 	}
 	else
 	{
 		printf("StackSize (empty) FAILED***\n");
 	}
 	
 	StackPush(ptr, &element);
 	
 	if(1 == StackSize(ptr))
	{
 		printf("StackSize SUCCESS\n");
 	}
 	else
 	{
 		printf("StackSize FAILED***\n");
 	}
 	
	StackDestroy(ptr);
}

void StackIsEmptyTest(void)
{
	size_t size = sizeof(int);
	size_t cap = 50;
	stack_t *ptr;
	int element = 19;
	ptr = StackCreate(size, cap);
	
	if (StackIsEmpty(ptr))
	{
 		printf("StackIsEmpty (empty) SUCCESS\n");
 	}
 	else
 	{
 		printf("StackIsEmpty (empty) FAILED***\n");
 	}
 	
 	StackPush(ptr, &element);
 	
 	if (!StackIsEmpty(ptr))
	{
 		printf("StackIsEmpty SUCCESS\n");
 	}
 	else
 	{
 		printf("StackIsEmpty FAILED***\n");
 	}
 	
	StackDestroy(ptr);
}

void StackCapacityTest(void)
{
	size_t size = sizeof(int);
	size_t cap = 50;
	stack_t *ptr;
	ptr = StackCreate(size, cap);
	
	if(cap == StackCapacity(ptr))
	{
 		printf("StackCapacity SUCCESS\n");
 	}
 	else
 	{
 		printf("StackCapacity FAILED***\n");
 	}
 	
 	StackDestroy(ptr);
}


















