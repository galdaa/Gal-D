/*********************************************************
ESCRIPTION: Implementation functions of queue.
Athor: Gal Dahan
Reviewer Oryan Shimoni
**********************************************************/

#include <stddef.h>    /* size_t */
#include <assert.h>   /*for asserts*/
#include <stdlib.h>  /* malloc, free */
#include "slist.h"  /*slist*/
#include "queue.h" /*queue*/

struct queue
{
	sllist_t *list;
};


queue_t *QCreate(void)
{
	queue_t *new_queue = (queue_t *) malloc(sizeof(queue_t));
	
	if (NULL == new_queue)
	{
		return NULL;
	}
	
	new_queue->list = SLLCreate();
	
	if (NULL == new_queue->list)
	{
		free(new_queue); new_queue = NULL;
		
		return NULL;
	}
	
	return new_queue;
}

void QDestroy(queue_t *queue)
{
	assert(NULL != queue);
	
	SLLDestroy(queue->list);
	queue->list = NULL;
	free(queue); queue = NULL;
}

/* insert before end*/
int QEnqueue(queue_t *queue, const void *value)
{
	assert(NULL != queue);
	
	return (SLLPushBack(queue->list, value) == SLLEnd(queue->list));
}

/* get begin, remove him, return begin*/
void *QDequeue(queue_t *queue)
{
	void *data = NULL;
	assert(NULL != queue);
	
	if (QIsEmpty(queue))
	{
		return NULL;
	}
	
	data = SLLGetData(SLLBegin(queue->list));
	SLLRemove(queue->list, SLLBegin(queue->list));
	
	return data;
}

int QIsEmpty(const queue_t *queue)
{
	assert(NULL != queue);
	
	return SLLIsEmpty(queue->list);
}

size_t QSize(const queue_t *queue)
{
	assert(NULL != queue);
	
	if (QIsEmpty(queue))
	{
		return 0;
	}
	
	return SLLSize(queue->list);
}

void *QPeek(const queue_t *queue)
{ 
	if (QIsEmpty(queue))
	{
		return NULL;
	}
	
	return SLLGetData(SLLBegin(queue->list));
}

/*use SLLAppend*/
queue_t *QAppend(queue_t *src_q, queue_t *dest_q)
{
	assert(NULL != src_q);
	assert(NULL != dest_q);
	
	if (!QIsEmpty(src_q))
	{
		SLLAppend(src_q->list, dest_q->list);
	}
	
	return dest_q;
}


