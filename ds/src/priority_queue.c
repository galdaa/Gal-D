/*********************************************************
ESCRIPTION: Test functions on Priority Queue.
Athor: Gal Dahan
Reviewer: Arie Charfnadel
**********************************************************/

#include <stddef.h> 			/* size_t 		*/
#include <assert.h>  			/* for asserts		*/
#include <stdlib.h>			/* malloc, free	*/
#include "sorted_list.h"		/* sorted_list API 	*/
#include "priority_queue.h"		/* priority_queue API 	*/

struct pq
{
	srtlst_t *list;
};

pq_t *PQCreate(int (*cmp_func)(const void *lhs, const void *rhs))
{
	pq_t *new_q = NULL;
	
	assert(NULL != cmp_func);
	
	new_q = (pq_t *) malloc(sizeof(pq_t));
	
	if (NULL != new_q)
	{
		new_q->list = SRTLSTCreate(cmp_func);
		
		if (NULL == new_q->list)
		{
			free(new_q); new_q = NULL;
			
			return NULL;
		}
		
	}
	
	return new_q;
}
 
void PQDestroy(pq_t *que)
{
	assert(NULL != que);
	
	SRTLSTDestroy(que->list); que->list = NULL;
	free(que); que = NULL;
}
 
size_t PQSize(const pq_t *que)
{
	assert(NULL != que);
	
	return  SRTLSTSize(que->list);
}

int PQIsEmpty(const pq_t *que)
{
	assert(NULL != que);
	
	return  SRTLSTIsEmpty(que->list);
}

int PQEnqueue(pq_t *que, const void *data)
{
	assert(NULL != que);
	
	return SRTLSTInsert(que->list, data);
}
 
void *PQDequeue(pq_t *que)
{
	void *data = NULL;
	
	assert(NULL != que);
	
	data = PQPeek(que);
	SRTLSTPopFront(que->list);
	
	return data;
}

void *PQPeek(pq_t *que)
{
	assert(NULL != que);
	
	return  SRTLSTGetData(SRTLSTBegin(que->list));
}

void *PQErase(pq_t *que, 
              int (*is_match)(const void *data, const void *to_erase),
              const void *to_erase)
{
	void *data = NULL;
	srtlst_iter_t iter;
	
	assert(NULL != que);
	assert(NULL != is_match);
	
	iter = SRTLSTFindIf(SRTLSTBegin(que->list) 
			,SRTLSTEnd(que->list) , is_match, to_erase);
			
	if (0 == SRTLSTIsSameIter(iter, SRTLSTEnd(que->list)))
	{	
		data = SRTLSTGetData(iter);
		SRTLSTRemove(iter);
	}
	
	return data;
}

void PQClear(pq_t *que)
{
	assert(NULL != que);
	
	while(!PQIsEmpty(que))
 	{
 		PQDequeue(que);
 	}
}

