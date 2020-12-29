/*********************************************************
ESCRIPTION: Test functions on Sorted Linked List.
Athor: Gal Dahan
Reviewer: Roi Peretz
**********************************************************/

#include <stddef.h>   		/* size_t */
#include <assert.h>  		/*for asserts*/
#include <stdlib.h> 		/*malloc, free */
#include "dlist.h"		/*dlist API*/
#include "sorted_list.h"	/*Sorted list API*/

struct srtlst 
{
	dllist_t *list;
	int (*cmp_func)(const void *one, const void *other);
};

srtlst_t *SRTLSTCreate(int (*cmp_func)(const void *one, const void *other))
{
	srtlst_t *new_srtl = NULL;
	
	assert(NULL != cmp_func);
	
	new_srtl = (srtlst_t *) malloc(sizeof(srtlst_t));
	
	if (NULL != new_srtl)
	{
		new_srtl->list = DLLCreate();
		
		if (NULL == new_srtl->list)
		{
			free(new_srtl); new_srtl = NULL;
			
			return NULL;
		}
		
		new_srtl->cmp_func = cmp_func;
	}
	
	return new_srtl;
}

void SRTLSTDestroy(srtlst_t *lst)
{
	assert(NULL != lst);
	
	DLLDestroy(lst->list); lst->list = NULL;
	free(lst); lst = NULL;
} 

size_t SRTLSTSize(const srtlst_t *lst)
{
	assert(NULL != lst);
	
	return DLLSize(lst->list);
}

int SRTLSTIsEmpty(const srtlst_t *lst)
{
	assert(NULL != lst);
	
	return DLLIsEmpty(lst->list);
}


int SRTLSTIsSameIter(srtlst_iter_t one, srtlst_iter_t other)
{
	assert (NULL != one.iter); 
	assert (NULL != other.iter);
	
	return DLLIsSameIter(one.iter, other.iter);
}

srtlst_iter_t SRTLSTNext(srtlst_iter_t iter)
{
	assert (NULL != iter.iter);
	
	iter.iter = DLLNext(iter.iter);
	
	return iter;
}
 
srtlst_iter_t SRTLSTPrev(srtlst_iter_t iter)
{
	assert (NULL != iter.iter);
	
	iter.iter = DLLPrev(iter.iter);
	
	return iter;
}

srtlst_iter_t SRTLSTBegin(const srtlst_t *lst)
{
	srtlst_iter_t begin;
	
	assert (NULL != lst);

	begin.iter = DLLBegin(lst->list);
	#ifndef NDEBUG		
	begin.list = (srtlst_t *) lst;
	#endif	
	
	return begin;
}

srtlst_iter_t SRTLSTEnd(const srtlst_t *lst)
{
	srtlst_iter_t end;
	
	assert (NULL != lst);
	
	end.iter = DLLEnd(lst->list);
	#ifndef NDEBUG		
	end.list = (srtlst_t *) lst;
	#endif	
	
	return end;
}

void *SRTLSTGetData(srtlst_iter_t iter)
{
	assert (NULL != iter.iter);
	
	return DLLGetData(iter.iter);	
}

int SRTLSTInsert(srtlst_t *lst, const void *data)
{
	srtlst_iter_t runner;
	
	assert (NULL != lst);
	
	runner = SRTLSTBegin(lst);
	
	for ( ;0 == SRTLSTIsSameIter(SRTLSTEnd(lst), runner)  && 
		0 >= lst->cmp_func(SRTLSTGetData(runner), data);
		runner = SRTLSTNext(runner))
	{
		/* empty */
	}
	
	return DLLInsertBefore(runner.iter, data);
}

void SRTLSTRemove(srtlst_iter_t iter)
{
	assert (NULL != iter.iter);
	
	DLLRemove(iter.iter);
}

void SRTLSTPopBack(srtlst_t *lst)
{
	assert (NULL != lst);
	
	DLLPopBack(lst->list);
}

void SRTLSTPopFront(srtlst_t *lst)
{
	assert (NULL != lst);
	
	DLLPopFront(lst->list);
}

int SRTLSTForEach(srtlst_iter_t from, 
               srtlst_iter_t to,
               int (*action)(void *data, void *params),
               void *params)
{
	assert (from.list == to.list);
	assert (NULL != from.iter);
	assert (NULL != to.iter); 
	assert (NULL != action); 
	
	return DLLForEach(from.iter, to.iter, action, params);
}

srtlst_iter_t SRTLSTFind(const srtlst_t *lst,
                         srtlst_iter_t from, 
                         srtlst_iter_t to,
                         const void *value)
{
	srtlst_iter_t runner;
	
	assert (NULL != lst);
	assert (from.list == to.list);
	assert (NULL != from.iter);
	assert (NULL != to.iter); 
	
	runner = from;
	
	for ( ; !SRTLSTIsSameIter(runner,to) && 
		0 > lst->cmp_func(SRTLSTGetData(runner), value);
		runner = SRTLSTNext(runner))
	{
		/* empty */
	}
	
	
	if (!SRTLSTIsSameIter(runner,to) && 0 == lst->cmp_func(SRTLSTGetData(runner), value))
		return runner;
	 	
 	return to;
}

srtlst_iter_t SRTLSTFindIf(srtlst_iter_t from,
                           srtlst_iter_t to,
                           int (*is_match)(const void *data, 
                                           const void *against),
                           const void *against)
{
	assert (from.list == to.list);
	assert (NULL != from.iter);
	assert (NULL != to.iter); 
	assert (NULL != is_match); 

	to.iter = DLLFind(from.iter, to.iter, against, is_match); 	
 	
 	return to;
}


void SRTLSTMerge(srtlst_t *dest, srtlst_t *src)
{
	srtlst_iter_t dest_runner;
	srtlst_iter_t src_runner;
	srtlst_iter_t hold_runner;
	
	assert (NULL != dest);
	assert (NULL != src); 
	
	dest_runner = SRTLSTBegin(dest);
	src_runner = SRTLSTBegin(src);
	
  	if (!SRTLSTIsEmpty(dest) && !SRTLSTIsEmpty(src)&&
  		0 > dest->cmp_func(SRTLSTGetData(SRTLSTPrev(SRTLSTEnd(src))),
  		SRTLSTGetData(dest_runner)))
	{
		DLLSplice(src_runner.iter, SRTLSTEnd(src).iter, dest_runner.iter);
	}
	else
  	{	
		while (!SRTLSTIsSameIter(dest_runner,SRTLSTEnd(dest)) &&
			!SRTLSTIsSameIter(src_runner,SRTLSTEnd(src)))
		{
		  	if (0 > dest->cmp_func(SRTLSTGetData(src_runner),
		  		 SRTLSTGetData(dest_runner)))
	  		{
	  			hold_runner = SRTLSTNext(src_runner);
	  			
	  			DLLSplice(src_runner.iter,
	  				SRTLSTNext(src_runner).iter, 
	  				dest_runner.iter);
	  				
				src_runner = hold_runner;
	  		}
	  		else
	  			dest_runner = SRTLSTNext(dest_runner);
		}
		
		if (SRTLSTIsSameIter(dest_runner,SRTLSTEnd(dest))  && 
			!SRTLSTIsSameIter(src_runner,SRTLSTEnd(src)))
		{
			DLLSplice(src_runner.iter, SRTLSTEnd(src).iter,
				dest_runner.iter);
		}
	}
}

