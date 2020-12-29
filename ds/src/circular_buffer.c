/*********************************************************
ESCRIPTION: Implementation functions of circular buffer.
Athor: Gal Dahan
Reviewer Oryan Shimoni
**********************************************************/

#include <stddef.h>    	/* size_t */
#include <assert.h>   		/* for asserts */
#include <stdlib.h>  		/* malloc, free */
#include <string.h>		/* memcpy */
#include "circular_buffer.h" 	/* circular buffer API */

#define MIN2(a, b) ((a < b) ? (a) : (b))

struct cbuffer
{
	size_t size; 
	size_t write_index;
	size_t capacity;
	char buffer[1];
	/* read_index = (write_index - size) % capacity */
};


cbuffer_t *CBufferCreate(size_t capacity)
{
	cbuffer_t *new_cbuff = (cbuffer_t *) malloc (sizeof(cbuffer_t) - 1 + capacity);

	if (NULL == new_cbuff)
	{
		return NULL;
	}
	
	new_cbuff->size = 0; 
	new_cbuff->write_index = 0;
	new_cbuff->capacity = capacity;
	
	return new_cbuff;
}

void CBufferDestroy(cbuffer_t *buffer)
{
	assert(NULL != buffer);
	
	free(buffer); buffer = NULL;
}

ssize_t CBufferRead(cbuffer_t *buffer, void *dest, size_t count)
{
	size_t byets_num = 0;
	size_t  i = 0;
	
	assert(NULL != buffer);
 	assert(NULL != dest);
 	
	byets_num = MIN2(count, buffer->size);
	
	/* read byte by byte */
  	for (i = 0; i < byets_num; ++i)
  	{
  		((char *) dest)[i] = 
  			((char *) buffer->buffer)
  			[(buffer->capacity + buffer->write_index - buffer->size) 
  			% buffer->capacity];
  		--(buffer->size);
  	}
  	
 	return byets_num;
}

ssize_t CBufferWrite(cbuffer_t *buffer, const void *src, size_t count)
{
	size_t byets_num = 0;
 	size_t  i = 0;
 
  	assert(NULL != buffer);
 	assert(NULL != src);
 	
 	byets_num = MIN2(count, CBufferFreeSpace(buffer));
  	
  	/* write byte by byte */
  	for (i = 0; i < byets_num; ++i)
  	{
  		buffer->buffer[buffer->write_index] = 
  			((char *) ((void *)src))[i];
  		++(buffer->size);
  		buffer->write_index =
  			(buffer->write_index + 1) % buffer->capacity;
  	}
  	
  	return byets_num;
}

int CBufferIsEmpty(const cbuffer_t *buffer)
{
	assert(NULL != buffer);
	
	return (0 == buffer->size);
}

int CBufferIsFull(const cbuffer_t *buffer)
{
	assert(NULL != buffer);
	
	return (buffer->capacity == buffer->size);
}

size_t CBufferSize(const cbuffer_t *buffer)
{
	assert(NULL != buffer);
	
	return buffer->size;
}

size_t CBufferFreeSpace(const cbuffer_t *buffer)
{
	assert(NULL != buffer);
	
	return buffer->capacity - buffer->size;
}

