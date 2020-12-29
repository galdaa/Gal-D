/*********************************************************
ESCRIPTION: Implementation functions of stack.
Athor: Gal Dahan
Reviewer: Amir Tamir
**********************************************************/

#include <stddef.h>  	/*size_t*/
#include <stdlib.h> 	/*malloc, free*/
#include <string.h> 	/*memcpy*/
#include <assert.h>  	/*for asserts*/
#include "stack.h"

struct stack
{
	size_t element_size;
	size_t capacity;
	size_t top;   /* index to next place for insert the stack */
	char *bottom; /* address of the bottom of the stack */
};

stack_t *StackCreate(size_t element_size, size_t capacity);
void StackDestroy(stack_t *stack);
int StackPop(stack_t *stack);
int StackPush(stack_t *stack, const void *element);
void *StackPeek(const stack_t *stack);
size_t StackSize(const stack_t *stack);
int StackIsEmpty(const stack_t *stack);
size_t StackCapacity(const stack_t *stack);

/*Create an empty stack with malloc for stack size and initial the members.*/
stack_t *StackCreate(size_t element_size, size_t capacity)
{
	stack_t *ptr = (stack_t *) malloc(sizeof(stack_t) + (element_size * capacity));
	
	assert(0 != element_size);
	assert(0 != capacity);
	
	if (NULL == ptr)
	{
		return ptr;
	}
	
	ptr->element_size = element_size;
	ptr->capacity = capacity;
	ptr->bottom = (char *) ptr + sizeof(stack_t);
	ptr->top = 0;
	
	return ptr;
}

/*Free ptr*/
void StackDestroy(stack_t *stack)
{
	assert(NULL != stack);
	free(stack);
}

/*if the stack isn't empty --top*/
int StackPop(stack_t *stack)
{
	assert(NULL != stack);
	
	if (0 < stack->top)
	{
		--(stack->top);
		return 0;
	}
	
	return 1;
}
	
/*If the stack isn't full add to next place and ++top.*/
int StackPush(stack_t *stack, const void *element)
{
	assert(NULL != stack);
	assert(NULL != element);
	
	if (stack->top < stack->capacity)
	{
		memcpy((stack->bottom + (stack->top * stack->element_size)), element , stack->element_size);
		++(stack->top);
		return 0;
	}
	
	return 1;
}
	

/*If the stack isn't empty return the last value that enter*/
void *StackPeek(const stack_t *stack)
{
	assert(NULL != stack);
	
	if (0 < stack->top)
	{
		return stack->bottom + ((stack->top - 1) * stack->element_size);
	}
	
	return NULL;
	
}

/*Return the current size of the stack*/
size_t StackSize(const stack_t *stack)
{
	assert(NULL != stack);
	
	return stack->top;
}

int StackIsEmpty(const stack_t *stack)
{
	assert(NULL != stack);
	
	return (0 == stack->top);
}

size_t StackCapacity(const stack_t *stack)
{
	assert(NULL != stack);
	
	return stack->capacity;
}



