/*********************************************************
ESCRIPTION: Implementation functions of vector.
Athor: Gal Dahan
Reviewer: Carolina Kats
**********************************************************/

#include <stddef.h>   /* size_t */
#include <stdlib.h> 	/* malloc, free */
#include <string.h> 	/* memcpy */
#include <assert.h>  	/* for asserts */
#include "vector.h"   	/* vector */

#define GROWTH_FACTOR 2
#define SHRINK_FACTOR 4

struct vector
{
	size_t element_size;
	size_t capacity;
	size_t size;   /* index to next place for insert the stack */
	char *buffer; /* address of the bottom of the stack */
};

/*initialization + 
	realloc for sizeof(vector) + 
	realloc for buf with cap'*element size*/
vector_t *VectorCreate(size_t element_size,  size_t initial_capacity)
{
	vector_t *new_vector = (vector_t *) malloc(sizeof(vector_t));
	char *buff = NULL;
	
	assert(0 != element_size);
	assert(0 != initial_capacity);
	
	if (NULL == new_vector)
	{
		return new_vector;
	}
	
	buff = (char *) malloc(initial_capacity * element_size);
	
	if (NULL == buff)
	{
		free(new_vector);
		new_vector = NULL;
		return NULL;
	}
	
	new_vector->element_size = element_size;
	new_vector->capacity = initial_capacity;
	new_vector->buffer = buff;
	new_vector->size = 0;
	
	return new_vector;
}

/*free- first buff then vector*/
void VectorDestroy(vector_t *vector)
{
	assert(NULL != vector);
	free(vector->buffer);
	vector->buffer = NULL;
	free(vector);
	vector = NULL;
}

/*return size*/
size_t VectorSize(const vector_t *vector)
{
	assert(NULL != vector);
	
	return vector->size;
}			

/*return buffer + index * element_size*/
void *VectorGetAccessToElementAt(const vector_t *vector , size_t index)
{
	assert(NULL != vector);
	assert(vector->size >= index);
	
	return vector->buffer + (index * vector->element_size);
}

/*if aize<cap': insert to buss+size*elemen size 
	else realloc for new size: cap'*growt factor(2) cap*=growth factor(2),
	++size*/						 			
int VectorPushBack(vector_t *vector , const void *element)
{
	assert(NULL != vector);
	assert(NULL != element);
	
	if (vector->size >= vector->capacity)
	{
		/*try realloc for new size*/
		if (1 == VectorReserve(vector, 
			 vector->capacity * GROWTH_FACTOR))
		{
			return 1;
		}
		
	}

	memcpy(vector->buffer + (vector->element_size * vector->size), 
		element, vector->element_size);
	++(vector->size);
	
	return 0;
}

/*if size>0 --size, if size<cap'/shrink factor(4): 
	realloc for new size: cap'/=growth factor(2)*/ 
int VectorPopBack(vector_t *vector)
{
	assert(NULL != vector);
	
	if (0 >= vector->size)
	{
		return 1;
	}
	
	--(vector->size);
	
	if ((size != 0) && (vector->size <= (vector->capacity)/SHRINK_FACTOR))
	{
		/*try realloc for new size*/
		if (1 == VectorReserve(vector, 
			 vector->capacity / GROWTH_FACTOR))
		{
			return 1;
		}
		
	}

	return 0;

}

/*realoc for new * element size, 
	if fail return 1 else 
	free the old storage and update the new and the new cap'
	if the new cap' < size cat it to new full cap' and return 0 */
int VectorReserve(vector_t *vector, size_t new_capacity)
{
	/*get the old values to new size malloc*/
	char *temp_buffer = NULL;
		
	assert(NULL != vector);
	assert(0 < new_capacity);
	
	temp_buffer = (char *) realloc(vector->buffer,
		new_capacity * vector->element_size);
		
	if (NULL == temp_buffer)
	{
		return 1;
	}
	
	/*old buffer free by realloc*/
	vector->buffer = temp_buffer;
	vector->capacity = new_capacity;
	
	if (vector->size > vector->capacity)
	{
		vector->size = vector->capacity;
	}
	
	return 0;
}

