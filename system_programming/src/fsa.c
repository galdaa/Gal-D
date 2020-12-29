/*********************************************************
ESCRIPTION: Implement functions on  FSA.
Athor: Gal Dahan
Reviewer: Inbal Shukrun
**********************************************************/
#include <stddef.h>   	/* size_t  */
#include <assert.h> 	/* assert  */
#include "fsa.h"	/* FSA API */

struct fsa_mng
{
    size_t first_free;  /*offset to first available block*/
};

#define WORD_SIZE sizeof(size_t)

/* compute size to add to align size */
static size_t Alignment(size_t size)
{
	size_t align = size % WORD_SIZE;
	size_t add_to_align = 0;
	
	if (0 != align)
	{
		add_to_align = WORD_SIZE - align;
	}
	
	return add_to_align;
}

size_t FSASuggestSize(size_t num_blocks, size_t block_size)
{
	block_size += Alignment(block_size);
	
	return sizeof(fsa_t) + 
		(num_blocks * block_size) + 
		WORD_SIZE; /* + WORD_SIZE in case the user malloc not align */
}

fsa_t *FSAInit(void *pool, size_t num_blocks, size_t block_size)
{
	char * runner = NULL;
	size_t i = 0;
	fsa_t *fsa = NULL;
	
	assert(pool);
	
	fsa = pool;
	fsa += Alignment((size_t) fsa);
	block_size += Alignment(block_size);
	fsa->first_free = sizeof(fsa_t);/*should be align?*/
	runner = (char *) fsa + fsa->first_free;
	
	for (i = 0; i < num_blocks - 1; runner += block_size, ++i)
	{
		*(size_t *) runner = runner - (char *) fsa + block_size;
	}
		
	*(size_t *) runner = 0;
	
	return fsa;
}

void *FSAAlloc(fsa_t *fsa)
{
 	char *mem = NULL;
 	
 	assert(fsa);
 	
 	if (0 != fsa->first_free)
 	{
 		mem = (char *) fsa + fsa->first_free; /* first free address */
 		fsa->first_free = *(size_t *) mem;
  	}
  	
  	return ((void *) mem);
}

void FSAFree(fsa_t *fsa, void *block)
{
	assert(fsa);
	assert(block);
	
	*(size_t *) block = fsa->first_free;
	fsa->first_free = (size_t) ((char *) block - (char *) fsa);
}

size_t FSACountFree(const fsa_t *fsa)
{
	char *runner = NULL;
	size_t count = 0;
	
	assert(fsa);
	
	for (runner = ((char *) fsa) + fsa->first_free; 
		runner != (char *) fsa; 
		runner = ((char *) fsa) + *(size_t *) runner, ++count)
	{
		/* empty */
	}
	
	return count;
}

