#ifndef __PRIORITY_QUEUE_H_OL97_ILRD__
#define __PRIORITY_QUEUE_H_OL97_ILRD__

/******************************************************************************
* Header file Containing API Definitions for
* Priority Queue ADT & its interface operations and declarations.
*
* Infinity Labs - OL97                                                      
******************************************************************************/
 
/******************************************************************************/
/***                               Includes                                 ***/
/******************************************************************************/
#include <stddef.h> /* size_t */

#include "srtlst_t.h"

/******************************************************************************/
/***                               Typedefs                                 ***/
/******************************************************************************/
typedef struct pq pq_t;

/*typedef struct pq_iter pq_iter_t;*/

/*
	Inside the implementation file:
	==============================
	
	struct pq 
	{
		srtlst_t *list;
		int (*cmp_func)(const void *one, const void *other);
	};
	
	
	struct pq_iter
	{ 
		srtlst_iter_t iter;
		size_t priority;
	};

*/


/******************************************************************************/
/***                            API Declarations                            ***/
/******************************************************************************/
/*
 * Description: This function is used for Creating an empty PQ structure.
 * Return value: On success, the functions returns pointer to the alocated list 
 * structure. On failure to allocate memory, NULL will be returned.
 * Time complexity: O(1).
 */
pq_t *PQCreate(void);
 
/*
 * Description: This function is used for destroying a given PQ pointed
 * by queue (frees memory of all elements and the list itself).
 * Return value: None.
 * Time complexity: O(n).
 */
void PQDestroy(pq_t *queue);
 
 /*
 * Description: This function is used for erase a given PQ pointed
 * by queue (frees memory of all elements without the queue itself)
 * return an empty queue.
 * Time complexity: O(n).
 */
void PQClear(pq_t *queue);

/*
* Description: This function is used for remove element 
* with the same data from a given PQ pointed by queue.
* Return value: The function will return 1 on failure 
* (not found or empty queue) and 0 otherwise.
* Time complexity: O(n).
*/
int PQErase(pq_t *queue, const void *data);

/*
 * Description: This function is used for getting the size of a given PQ 
 * pointed by queue(amount of elements).
 * Return value: This function returns the number of elements in the PQ 
 * pointed to by queue.
 * Time complexity: O(n).
 */
size_t PQSize(const pq_t *queue);

/*
 * Description: This function returns whether the given PQ is empty.
 * Return value: 1 (true) if the size of PQ list pointed by queue is 0,
 * 0 (false) otherwise.
 * Time complexity: O(1).
 */ 
int PQIsEmpty(const pq_t *queue);

/*
 * Description: This function is used for getting the first valid iterator 
 * (pq_iter_t) data of the PQ pointed by queue.
 * valid iterator is first iterator which holding valid user data (not dummy).
 * UB: Trying to PQPeek from an empty queue.
 * Return value: The function will return first valid iterator.
 * Time complexity: O(1).
 */
void *PQPeek(const pq_t *queue); 

/*
 * Description: This function is used for inserting new data into the a given 
 * PQ  pointed by queue. The data will be inserted in the correct location
 * in a priority manner.. 
 * If the same priority the order is fifo.
 * Return value: The function will return 1 on failure and 0 otherwise.
 * Time complexity: O(n).
 */

/*
 * Description: This function is used for removing last valid iterator from 
 * PQ  pointed by queue. 
 * UB: Trying to dequeue from an empty queue.
 * Return value: None.
 * Time complexity: O(1).
 */
void PQDequeue(pq_t *queue);

#endif /* __PRIORITY_QUEUE_H_OL97_ILRD__ */
