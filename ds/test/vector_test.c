/*********************************************************
ESCRIPTION: Test of implementation functions of vector.
Athor: Gal Dahan
Reviewer:---
**********************************************************/

#include <stdio.h>/*printf*/
#include <stddef.h>   /* size_t */
/*#include <stdlib.h>*/

#include "vector.h"   

void VectorCreateDestroyTest(void);
void VectorSizeTest(void);
void VectorGetAccessToElementAtTest(void);
void VectorPushBackTest(void);
void VectorPopBackTest(void);
void VectorReserveTest(void);

int main()
{
	VectorCreateDestroyTest();
	VectorSizeTest();
	VectorGetAccessToElementAtTest();
	VectorPushBackTest();
	VectorPopBackTest();
	VectorReserveTest();
	printf("***Finished***\n");
	
	return 0;
}


void VectorCreateDestroyTest(void)
{
	size_t size = 8;
	size_t cap = 5;
	vector_t *ptr;
	ptr = (vector_t *) VectorCreate(size , cap);
	
	if(NULL == ptr)
	{
		printf("VectorCreateTest FAILED***\n");
	}
	else
	{
		printf("VectorCreateTest SUCCESS\n");
		VectorDestroy(ptr);
		printf("VectorDestroy SUCCESS (not crashed)\n");
		ptr = NULL;
	}
}

void VectorSizeTest(void)
{
	size_t size = 8;
	size_t cap = 5;
	int element = 5;
	vector_t *ptr;
	ptr = (vector_t *) VectorCreate(size , cap);
	
	if(0 == VectorSize(ptr))
	{
		printf("VectorSizeTest (empty) SUCCESS\n");
	}
	else
	{
		printf("VectorSizeTest (empty) FAILED***\n");
	}
	
	VectorPushBack(ptr, &element);
	
	if(1 == VectorSize(ptr))
	{
		printf("VectorSizeTest SUCCESS\n");
	}
	else
	{
		printf("VectorSizeTest FAILED***\n");
	}
	
	VectorDestroy(ptr);
	ptr = NULL;
}
					
void VectorGetAccessToElementAtTest(void)
{
	size_t size = sizeof(int);
	size_t cap = 5;
	vector_t *ptr;
	int element = 5;
	size_t index = 0;
	ptr = (vector_t *) VectorCreate(size , cap);
	
	element = 5;
	index = 0;
	VectorPushBack(ptr, &element);
	
	if(element == *(int *) VectorGetAccessToElementAt(ptr, index))
	{
		printf("VectorGetAccessToElementAtTest SUCCESS\n");
	}
	else
	{
		printf("VectorGetAccessToElementAtTest FAILED***\n");
	}
	
	element = 4;
	++index;
	VectorPushBack(ptr, &element);
	
	if(element == *(int *) VectorGetAccessToElementAt(ptr, index))
	{
		printf("VectorGetAccessToElementAtTest SUCCESS\n");
	}
	else
	{
		printf("VectorGetAccessToElementAtTest FAILED***\n");
	}
	
	element = 3;
	++index;
	*(int *) VectorGetAccessToElementAt(ptr, index) = element;

	if(element == *(int *) VectorGetAccessToElementAt(ptr, index))
	{
		printf("VectorGetAccessToElementAtTest (by self) SUCCESS\n");
	}
	else
	{
		printf("VectorGetAccessToElementAtTest (by self) FAILED***\n");
	}
	
	element = 2;
	VectorPushBack(ptr, &element);
	
	if(element == *(int *) VectorGetAccessToElementAt(ptr, index))
	{
		printf("VectorGetAccessToElementAtTest SUCCESS\n");
	}
	else
	{
		printf("VectorGetAccessToElementAtTest FAILED***\n");
	}
	
	VectorDestroy(ptr);
	ptr = NULL;
}

void VectorPushBackTest(void)
{
	size_t size = sizeof(int);
	size_t cap = 2;
	vector_t *ptr;
	int element = 5;
	ptr = (vector_t *) VectorCreate(size , cap);
	
	if(0 == VectorPushBack(ptr, &element))
	{
		printf("VectorPushBackTest SUCCESS\n");
	}
	else
	{
		printf("VectorPushBackTest FAILED***\n");
	}
	
	if(0 == VectorPushBack(ptr, &element))
	{
		printf("VectorPushBackTest SUCCESS\n");
	}
	else
	{
		printf("VectorPushBackTest FAILED***\n");
	}
	
	if(0 == VectorPushBack(ptr, &element))
	{
		printf("VectorPushBackTest SUCCESS\n");
	}
	else
	{
		printf("VectorPushBackTest (full) FAILED***\n");
	}
	
	VectorDestroy(ptr);
	ptr = NULL;
}


void VectorPopBackTest(void)
{
	size_t size = sizeof(int);
	size_t cap = 3;
	vector_t *ptr;
	int element = 5;
	ptr = (vector_t *) VectorCreate(size , cap);
	VectorPushBack(ptr, &element);
	VectorPushBack(ptr, &element);
	VectorPushBack(ptr, &element);

	if(0 == VectorPopBack(ptr))
	{
		printf("VectorPopBackTest SUCCESS\n");
	}
	else
	{
		printf("VectorPopBackTest FAILED***\n");
	}
	
	if(0 == VectorPopBack(ptr))
	{
		printf("VectorPopBackTest SUCCESS\n");
	}
	else
	{
		printf("VectorPopBackTest FAILED***\n");
	}
	
	if(0 == VectorPopBack(ptr))
	{
		printf("VectorPopBackTest SUCCESS\n");
	}
	else
	{
		printf("VectorPopBackTest FAILED***\n");
	}
	
	if(1 == VectorPopBack(ptr))
	{
		printf("VectorPopBackTest (empty) SUCCESS\n");
	}
	else
	{
		printf("VectorPopBackTest (empty) FAILED***\n");
	}
	
	VectorDestroy(ptr);
	ptr = NULL;
}

void VectorReserveTest(void)
{
	size_t size = 8;
	size_t cap = 5;
	vector_t *ptr;
	ptr = (vector_t *) VectorCreate(size , cap);
	cap = 15;
	
	if(1 == VectorReserve(ptr, cap))
	{
		printf("VectorReserveTest FAILED***\n");
	}
	else
	{
		printf("VectorReserveTest SUCCESS\n");
	}
	
	if(NULL == ptr)
	{
		printf("VectorReserveTest FAILED***\n");
	}
	else
	{
		printf("VectorReserveTest SUCCESS\n");
	}
	
	VectorDestroy(ptr);
	ptr = NULL;
}

















