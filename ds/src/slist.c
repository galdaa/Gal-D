/*********************************************************
ESCRIPTION: Implementation functions of 
	singly link list.
Athor: Gal Dahan
Reviewer: Galit Vaknin
**********************************************************/

#include <stddef.h>   /* size_t */
#include <assert.h>  /*for asserts*/
#include <stdlib.h> /*malloc, free */
#include "slist.h"

/*list with pointer to head = first none, 
	tail = dummy node*/
struct sllist
{
	void *head;
	void *tail;
};

/*node with pointer to data and next node*/
struct node
{
	sllist_iter_t next;
	void *data;
};

struct sllist_iter
{
		node_t *node;
};

/* malloc sll ptr for sizeof(sllist) 
	malloc and init dummy node- his data, next = NULL
	init head & tail of the new sll to point on dummy node 
	return ptr */
sllist_t *SLLCreate(void)
{
	sllist_t *ptr = (sllist_t *) malloc(sizeof(sllist_t));
	sllist_iter_t dummy = NULL;
	
	if (NULL == ptr)
	{
		return ptr;
	}
	
	dummy = (sllist_iter_t ) malloc(sizeof(node_t));
	
	if (NULL == dummy)
	{
		free(ptr);
		ptr = NULL;
		
		return NULL;
	}
	
	dummy->next = NULL;
	dummy->data = NULL;
	ptr->head = dummy;
	ptr->tail = dummy;

	return ptr;
}

/* free(lst) in loop for all the nodes */
void SLLDestroy(sllist_t *lst)
{
	sllist_iter_t iter = lst->head;
	sllist_iter_t catch_iter = iter;
	
	assert(NULL != lst);

	while (1 != SLLIsSameIter(iter, SLLEnd(lst)))
	{
		catch_iter = iter->next;
		free(iter);	iter = NULL;
		iter = catch_iter;
	}
	
	free(iter);	iter = NULL;
	free(lst);	lst = NULL;
}

 /* malloc new node with the old value and next,
 	set the old node to data and next on the new node	
 	*** assumming the data is address! (nod a deep copy) */
sllist_iter_t SLLInsertBefore( sllist_t *lst ,sllist_iter_t iter, const void *data)
{
	sllist_iter_t new_node = (sllist_iter_t ) malloc(sizeof(node_t));
	
	assert(NULL != lst);
	assert(NULL != iter);
	assert(NULL != data);
	 		
 	if (NULL == new_node)
 	{
 		return lst->tail;
 	}
 	
 	new_node->data = iter->data;
 	
 	if (iter == lst->tail) 
 	{
 		lst->tail = new_node;
 	}
 	
 	new_node->next = iter->next;
 	iter->data = (void *) data;/*to be not const*/
 	iter->next = new_node;
 	
 	return iter;
}
 /* use SLLInsertBefore to insert before tail
 	*** assumming the data is address! (nod a deep copy) */
sllist_iter_t SLLPushBack(sllist_t *lst, const void *data)
{
	return SLLInsertBefore(lst, lst->tail, data);
}


 /*if not empty: 
 	run with sllist_iter_t from iter = head while iter->next != lst->tail
 	-find the last node before the dummy and remove him*/
void SLLPopBack(sllist_t *lst)
{
	sllist_iter_t runner = lst->head;
	
	assert (NULL != lst);
	
	if (SLLIsEmpty(lst)) 
	{
		return;
	}
	
 	for (runner = lst->head; runner->next != lst->tail;
 		runner = runner->next)
 	{
 		/*empty*/
 	}
 	
 	SLLRemove(lst, runner);
 }

 /* run frome head until one before tail, 
 	if match return the iterator else return the tail*/
sllist_iter_t SLLFind(const sllist_t *lst,
                   const void *value,
                   int (*is_match)(const void *one, const void *other))
{
	sllist_iter_t iter;
 	
 	assert (NULL != lst);
 	assert (NULL != value);
 	assert (NULL != is_match);
 	
 	iter = lst->head;	
 	
 	if (iter == lst->tail) 
 	{
 		return iter;
 	}
 	
 	while (iter != lst->tail)
 	{
 		
 		if (0 == is_match(iter->data, value))
 		{
 			return iter;
 		}
 		
 		iter = iter->next;
 	}
 	
 	return iter;
}

/* if not tail- copy the next node's values and free him
	if wase only one update the tail to empty sll*/
void SLLRemove(sllist_t *lst, sllist_iter_t iter)
{
	sllist_iter_t temp_iter = iter->next;
	 	
 	assert (NULL != lst);
 	assert (NULL != iter);
 	
  	if (iter == lst->tail) 
  	{
  		return;
  	}
  	
  	if (iter->next == lst->tail) 
  	{
  		lst->tail = iter;
  	}
  	
	iter->next = temp_iter->next;
	iter->data = temp_iter->data;
	free(temp_iter);
	temp_iter = NULL;
}

/*if head == tail*/
int SLLIsEmpty(const sllist_t *lst)
{
	assert (NULL != lst);
	
	return (lst->head == lst->tail);
}


int SLLSetData(sllist_iter_t iter, const void *data)
{
	assert (NULL != iter);
	
	iter->data = (void *) data;/*cast to be not const*/
	
	return 0;
}

void *SLLGetData(const sllist_iter_t iter)
{
	assert (NULL != iter); 
	/*assert (NULL != iter->data);*/
	
	return iter->data; 
}

sllist_iter_t SLLNext(const sllist_iter_t iter)
{
	assert (NULL != iter); 
	/*assert (NULL != iter->next);*/
	
	return iter->next;
}

sllist_iter_t SLLBegin(const sllist_t *lst)
{
	assert (NULL != lst);
	
	return lst->head;
}

sllist_iter_t SLLEnd(const sllist_t *lst)
{
	assert (NULL != lst);
	
	return lst->tail;
}

int SLLIsSameIter(const sllist_iter_t one, const sllist_iter_t other)
{
	assert (NULL != one); 
	assert (NULL != other);
	
	return (one == other);
}

/*run from 'from' to 'to' and operate the function- stop in error*/
int SLLForEach(sllist_t *lst, 
                  sllist_iter_t from, 
                  sllist_iter_t to, 
                  int (*action)(void *data, void *params), void *params)
{
	sllist_iter_t iter = from;
	
	assert (NULL != lst);
	assert (NULL != from);
	assert (NULL != to); 
	assert (NULL != action); 
  	
    	if (SLLIsEmpty(lst)) 
  	{
  		return 1;
  	}

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

/*run on sll and count the nodes not include the dummy*/
size_t SLLSize(const sllist_t *lst)
{
	sllist_iter_t iter = lst->head;
	size_t count = 0;
	
	assert (NULL != lst);
		
	if (SLLIsEmpty(lst)) 
	{
		return 0;
	}
	
	while(iter != lst->tail)
	{
		++count;
		iter = iter->next; 
	}
	
	return count;
}

/*copy the first node of src to tail of dest and update*/
sllist_t * SLLAppend(sllist_t *src_lst, sllist_t *dest_lst)
{
	if (!SLLIsEmpty(src_lst))
	{
		/*copy the first node of src*/
		SLLSetData(SLLEnd(dest_lst), SLLGetData(SLLBegin(src_lst)));
		SLLEnd(dest_lst)->next = SLLNext(SLLBegin(src_lst));
		/*update the dest tail*/
		dest_lst->tail = src_lst->tail;/*SLLEnd(dest_lst) = SLLEnd(src_lst);*/
		/*make src empty list*/
		src_lst->tail = src_lst->head;/*SLLEnd(src_lst) = SLLBegin(src_lst);*/
		SLLEnd(src_lst)->next = NULL;
	}
	
	return dest_lst;
}

