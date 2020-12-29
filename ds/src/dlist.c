/*********************************************************
ESCRIPTION: Implementation functions on 
				Doubly Linked List.
Athor: Gal Dahan
Reviewer: Amir Tamir
**********************************************************/

#include <stddef.h>   	/* size_t */
#include <assert.h>  	/*for asserts*/
#include <stdlib.h> 	/*malloc, free */
#include "dlist.h"	/*dlist API*/

/*head & tail are dummies wich 
point ech other in empty list*/
struct node
{ 
	void *data;
	struct node *next;
	struct node *prev;
};

struct dllist 
{
	struct node head;
	struct node tail;
};

dllist_t *DLLCreate(void)
{
	dllist_t *new_dll = (dllist_t *) malloc(sizeof(dllist_t));
	
	if (NULL == new_dll)
	{
		return new_dll;
	}
	
	new_dll->tail.next = NULL;
	new_dll->tail.data = NULL;
	new_dll->tail.prev = &(new_dll->head);
	new_dll->head.next = &(new_dll->tail);
	new_dll->head.prev = NULL;
	new_dll->head.data = NULL;
	
	return new_dll;
}

void DLLDestroy(dllist_t *lst)
{
	dllist_iter_t iter = NULL;
	dllist_iter_t catch_iter = NULL;
	
	assert(NULL != lst);
	
	iter = lst->head.next;
	catch_iter = iter;
	
	while (1 != DLLIsSameIter(iter, DLLEnd(lst)))
	{
		catch_iter = iter->next;
		free(iter); iter = NULL;
		iter = catch_iter;
	}
	
	free(lst); lst = NULL;
}

size_t DLLSize(const dllist_t *lst)
{
	dllist_iter_t iter = NULL;
	size_t count = 0;
	
	assert (NULL != lst);
	
	if (DLLIsEmpty(lst)) 
	{
		return 0;
	}
	
	iter = DLLBegin(lst);
		
	while(iter != DLLEnd(lst))
	{
		++count;
		iter = iter->next; 
	}
	
	return count;
}

int DLLIsEmpty(const dllist_t *lst)
{
	assert (NULL != lst);
	
	return (((lst->head).next == DLLEnd(lst)) && 
		(DLLEnd(lst)->prev == &(lst->head)));
}

int DLLIsSameIter(const dllist_iter_t one, const dllist_iter_t other)
{
	assert (NULL != one); 
	assert (NULL != other);
		
	return (one == other);
}

dllist_iter_t DLLNext(const dllist_iter_t iter)
{
	if (NULL == iter->next)
		return iter;
		
	return iter->next;
}
 
dllist_iter_t DLLPrev(const dllist_iter_t iter)
{

	if (NULL == (iter->prev)->prev)
		return iter;
		
	return iter->prev;
}

dllist_iter_t DLLBegin(const dllist_t *lst)
{
	assert (NULL != lst);
	
	return (lst->head).next;
}

dllist_iter_t DLLEnd(const dllist_t *lst)
{
	assert (NULL != lst);
	
	return (dllist_iter_t) &(lst->tail);
} 

void *DLLGetData(const dllist_iter_t iter)
{
	assert (NULL != iter); 
	
	if (NULL == iter->next)
		return NULL;
	
	return iter->data; 
}

void DLLSetData(dllist_iter_t iter, const void *data)
{
	assert (NULL != iter);
	
	iter->data = (void *) data;/*cast to be not const*/
}

int DLLInsertBefore(dllist_iter_t iter, const void *data)
{
	dllist_iter_t new_node = NULL;
	
	assert(NULL != iter);
	assert(NULL != data);
	
	new_node = (dllist_iter_t) malloc(sizeof(node_t));
			
 	if (NULL == new_node)
 	{
 		return 1;
 	}
 	
 	new_node->data = (void *) data;/*to be not const*/
  	new_node->next = iter;
 	new_node->prev = iter->prev;
 	(iter->prev)->next = new_node;
 	iter->prev = new_node;
 	
 	return 0;	
}

dllist_iter_t DLLPushBack(dllist_t *lst, const void *data)
{
	assert (NULL != lst);
	assert(NULL != data);
		
	return (0 == DLLInsertBefore(DLLEnd(lst), data)) ?
	DLLEnd(lst)->prev : DLLEnd(lst);
}

/*
 insert befor begin
 */
dllist_iter_t DLLPushFront(dllist_t *lst, const void *data)
{
	assert (NULL != lst);
	assert(NULL != data);
		
	return (0 == DLLInsertBefore(DLLBegin(lst), data)) ?
						DLLEnd(lst)->prev : DLLEnd(lst);
}

void DLLRemove(dllist_iter_t iter)
{
	dllist_iter_t temp_iter = NULL;
	 	
 	assert (NULL != iter);
 	 	  	
  	if (NULL != iter->prev) 
  	{
 		temp_iter = iter->prev;
 		temp_iter->next = iter->next;
 		(iter->next)->prev = temp_iter;

		free(iter); iter = NULL;
	}
}

void DLLPopBack(dllist_t *lst)
{
	assert (NULL != lst);

 	DLLRemove(DLLEnd(lst)->prev);
}

void DLLPopFront(dllist_t *lst)
{
	assert (NULL != lst);

 	DLLRemove(DLLBegin(lst));
}

int DLLForEach(dllist_iter_t from, 
               dllist_iter_t to,
               int (*action)(void *data, void *params),
               void *params)
{
	dllist_iter_t iter = NULL;
	
	assert (NULL != from);
	assert (NULL != to); 
	assert (NULL != action); 
  	
  	iter = from;

	while(iter != to) 
	{
		
		if (1 == action(iter->data, params)) 
		{
			return 1;
		}
		
		iter = iter->next;
	}
	
	return 0;
}

dllist_iter_t DLLFind(const dllist_iter_t from,
                      const dllist_iter_t to,
                      const void *value,
                      int (*is_match)(const void *data, const void *against))
{
	dllist_iter_t iter;
 	
 	assert (NULL != value);
 	assert (NULL != is_match);
 	
 	iter = from;	
 	
 	while (iter != to)
 	{
 	
 		if (1 == is_match(iter->data, value))
 		{
 			return iter;
 		}
 		
 		iter = iter->next;
 	}
 	
 	return iter;
}


int DLLMultiFind(const dllist_iter_t from,
                 const dllist_iter_t to,
                 dllist_t *dest,
				 const void *value,
                 int (*is_match)(const void *data, const void *against))
{
	dllist_iter_t iter;
 	
  	assert (NULL != value);
 	assert (NULL != is_match);
 	
 	iter = from;	
 	
 	while (iter != to)
 	{
 		
 		if (1 == is_match(iter->data, value))
 		{
 			if(DLLPushBack(dest, iter->data) == DLLEnd(dest))
 				return 1;
 		}
 		
 		iter = iter->next;
 	}
 	
 	return 0;
}

                     
void DLLSplice(dllist_iter_t from,
               dllist_iter_t to,
               dllist_iter_t target)
{
	dllist_iter_t to_prev_hold = to->prev;
	to->prev->next = target;
	target->prev->next = from;
	from->prev->next = to;
	to->prev= from->prev;
	from->prev = target->prev;
	target->prev = to_prev_hold;
}
           

