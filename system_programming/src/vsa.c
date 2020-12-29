/*********************************************************
ESCRIPTION: Implement functions of  VSA.
Athor: Gal Dahan
Reviewer: Noa Efrati
**********************************************************/
#include <assert.h> 	/* assert  */
#include "vsa.h"	/* VSA API */

struct vsa_mng
{
    size_t pool_size;
};

typedef struct header
{
	size_t chunk_size;
	#ifndef NDEBUG
	size_t magic_number; 
	#endif
}header_t;

#define WORD_SIZE sizeof(size_t)
#define ADD_ADDRESS(PTR, ADD) ((char *) (PTR) + (ADD))
#define MAGIC_NUMBER 0xFEE1DEAD

static void *ChunkAlloc(header_t *runner, size_t chunk_size);
static size_t Alignment(size_t size);
static void VSAMrege(vsa_t *vsa);
static void MregeChuncks(vsa_t *vsa, header_t *runner, size_t count);

/* compute size to add to get align size */
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

/*
	run on given vsa to find and merge adjacent free chunks.
	run from free chunk until not free chunk (or end of vsa) 
	and update the size of the current chunk size.	O(n)
*/
static void VSAMrege(vsa_t *vsa)
{
	size_t count = 0;
	header_t *runner = NULL;
	
	assert(vsa);
	
	runner = (header_t *) ADD_ADDRESS(vsa, sizeof(vsa_t));
	count += sizeof(vsa_t);
	
	while (count < vsa->pool_size)
	{
		size_t offset = 0;
		
		if (0 == (runner->chunk_size) % 2)
		{
			MregeChuncks(vsa, runner, count);		
		}

		offset = (0 == (runner->chunk_size) % 2) ? 
			runner->chunk_size : runner->chunk_size - 1;
		count += offset;
		runner = (header_t *) (ADD_ADDRESS(runner, offset));
	}
	
}

static void MregeChuncks(vsa_t *vsa, header_t *runner, size_t count)
{
	size_t run_count = count + runner->chunk_size;
	header_t *next_runner = NULL;
	size_t size = runner->chunk_size;
	
	next_runner = (header_t *) (ADD_ADDRESS(runner, runner->chunk_size));
		
	while (run_count < vsa->pool_size &&
		0 == (next_runner->chunk_size) % 2)
	{
		size += next_runner->chunk_size;
		run_count += next_runner->chunk_size;
		next_runner = (header_t *) (ADD_ADDRESS(next_runner, 
			next_runner->chunk_size));
	}

	(runner->chunk_size) = size;		
}

vsa_t *VSAInit(void *pool, size_t pool_size)
{
	vsa_t *vsa = pool;
	size_t head_align = Alignment((size_t) vsa);
	size_t tail_align = 0;
	header_t *first_chunk = {0};
	
	vsa += head_align;
	tail_align = (size_t) (ADD_ADDRESS(pool, pool_size)) % WORD_SIZE;
	vsa->pool_size = pool_size - head_align - tail_align;

	first_chunk = (header_t *) ADD_ADDRESS(vsa, sizeof(vsa_t));	/*first block*/
	first_chunk->chunk_size = vsa->pool_size - sizeof(vsa_t);	/*one big block*/
	
	#ifndef NDEBUG
	first_chunk->magic_number = MAGIC_NUMBER; 			/*this vsa sign*/
	#endif
	
	return vsa;
}
	
void *VSAAlloc(vsa_t *vsa, size_t chunk_size)
{
	
	size_t count = 0;
	header_t *runner =  NULL;
	
	assert(vsa);
	
	runner = (header_t *) ADD_ADDRESS(vsa, sizeof(vsa_t));
	chunk_size += Alignment(chunk_size);
	
	if (chunk_size <= VSAMaxFreeChunk(vsa))
	{	
		count = sizeof(vsa_t);
		
		while (count < vsa->pool_size)
		{
			size_t offset = 0;
			
			if (0 == (runner->chunk_size) % 2 &&
				(runner->chunk_size - sizeof(struct header)) 
				>= chunk_size)
			{	
				return ChunkAlloc(runner, chunk_size);
			}
			
			offset = (0 == (runner->chunk_size) % 2) ?
				runner->chunk_size : runner->chunk_size - 1;
			count += offset;
			runner = (header_t *) ((char *) runner + offset);
		}
	}
	
	return NULL;
}

static void *ChunkAlloc(header_t *runner, size_t chunk_size)
{
	size_t res = runner->chunk_size - (chunk_size + sizeof(struct header));
								
	if (res >= 1)
	{
		header_t *new_header = NULL;
		runner->chunk_size = chunk_size + sizeof(struct header);
		new_header = (header_t *) ADD_ADDRESS(runner, runner->chunk_size);
		new_header->chunk_size = res;
		#ifndef NDEBUG
		new_header->magic_number = MAGIC_NUMBER; 	/*this vsa sign*/
		#endif
	}

	++(runner->chunk_size);  				/*sign as occupied*/		

	return	runner + 1;
}

void VSAFree(void *chunk)
{
	header_t *chunk_header = 
		(header_t *) ADD_ADDRESS(chunk, -sizeof(struct header));
	
	assert(1 == (chunk_header->chunk_size) % 2);
	assert(MAGIC_NUMBER == chunk_header->magic_number);
	
	--(chunk_header->chunk_size);	/*sign as free*/
}

/* return max free chunk size for user! */
size_t VSAMaxFreeChunk(const vsa_t *vsa)
{
	size_t count = 0;
	size_t max_size = 0;
	header_t *runner =  NULL;
	
	assert(vsa);
	
	VSAMrege((vsa_t *) vsa);
	runner = (header_t *) ADD_ADDRESS(vsa, sizeof(vsa_t));
	count = sizeof(vsa_t);
	
	while (count < vsa->pool_size)
	{
		size_t offset = 0;
		
		if (0 == (runner->chunk_size) % 2 && 
			runner->chunk_size > max_size)
		{
			max_size = runner->chunk_size;
		}
		/* offset is the chunk size regardless the last bit*/
		offset = (0 == (runner->chunk_size) % 2) ?
				runner->chunk_size : runner->chunk_size - 1;
		count += offset;
		runner = (header_t *) ((char *)runner + offset);
	}
	
	return (0 == max_size) ? 0 : (max_size - sizeof(struct header));
}
