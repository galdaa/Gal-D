#include <stddef.h>   /* size_t */
#include <assert.h>  	/*for asserts*/
#include "slist.h"

struct sllist
{
	void *head;
	void *tail;
};

struct node
{
	void *next;
	void *data;
};



/* malloc sllist ptr for sizeof(sllist) 
	malloc and init dummy node- his data, next = NULL
	malloc and init head & tail of ptr to point on dummy node 
	return ptr */
sllist_t *SLLCreate(void);

/* assert(NULL != lst) 
	free(lst)  ***********************in loop of all the nodes */
void SLLDestroy(sllist_t *lst);

 /* assert(NULL != lst) assert(NULL != iter) assert(NULL != data) 
 	sllist_iter_t new malloc
 	if NULL == new (malloc failed) return lst->tail
 	new->data = iter->data
 	if (iter == lst->tail) lst->tail = new
 	new->next = iter->next
 	iter->data = *data
 	iter->next = new
 	return new	*/
sllist_iter_t SLLInsertBefore( sllist_t *lst ,sllist_iter_t iter, const void *data);

 /* use SLLInsertBefore lst->tail*/
sllist_iter_t SLLPushBack(sllist_t *lst, const void *data);


 /*if not empty: 
 	run with sllist_iter_t from iter = head while iter->next->next != lst->tail
 	free(iter->next)
 	iter->next = lst->tail */
void SLLPopBack(sllist_t *lst);

 /* sllist_iter_t iter = lst->head
 	if (iter == lst->tail) return iter
 	while (iter->next != lst->tail)
 		if (0 == is_match(iter->data, value)) return iter
 		iter = iter->next
 	return iter */
sllist_iter_t SLLFind(const sllist_t *lst,
                   const void *value,
                   int (*is_match)(const void *one, const void *other));

/* sllist_iter_t new_iter = lst->head
 	sllist_iter_t temp
 	if (new_iter == lst->tail)||(iter == lst->tail) return
 	if (iter == lst->head) 
 		temp = lst->head 
 		lst->head = lst->head->next
 		free(temp) return 
 	while (new_iter->next != lst->tail)
 		if (new_iter->next == iter)
 			temp = new_iter->next 
	 		new_iter->next = new_iter->next->next
	 		free(temp) return ***************reduce duplicate- only one free!*/
void SLLRemove(sllist_t *lst, sllist_iter_t iter);

/*assert (NULL != lst)
return (lst->head == lst->tail) */
int SLLIsEmpty(const sllist_t *lst);

/* assert (NULL != iter)
	//if (NULL == iter->0) return 1???dont care
	iter->data = *data
	return 0 */
int SLLSetData(sllist_iter_t iter, const void *data);

/* assert (NULL != iter) assert (NULL != iter->data)
	return iter->data */
void *SLLGetData(const sllist_iter_t iter);

/* assert (NULL != iter) assert (NULL != iter->next)
	return iter->next */
sllist_iter_t SLLNext(const sllist_iter_t iter);

/* assert (NULL != lst)
	return lst->head */[[[
sllist_iter_t SLLBegin(const sllist_t *lst);

/* assert (NULL != lst)
	return lst->tail */
sllist_iter_t SLLEnd(const sllist_t *lst);

/* assert (NULL != one) assert (NULL != other)
	return (one == other) */
int SLLIsSameIter(const sllist_iter_t one, const sllist_iter_t other);


 /* assert (NULL != from) assert (NULL != to) assert (NULL != action) assert (NULL != params)
  	sllist_iter_t iter = lst->head 
  	if(SLLIsEmpty) return 1
	while(iter != from)/**************************start from from
		iter = iter->next
	while(iter != to) 
		if (1 == action(data, params)) return 1
		iter = iter->next
 */
int SLLForEach(sllist_t *lst, 
                  sllist_iter_t from, 
                  sllist_iter_t to, 
                  int (*action)(void *data, void *params), void *params);


/*sllist_iter_t iter = lst->head size_t count = 0
	if(SLLIsEmpty) return 0
	while(iter->next != lst->tail)
		++count
		iter = iter->next 
	return iter */
size_t SLLSize(const sllist_t *lst);


