/*********************************************************
ESCRIPTION: Implementation 3 alogrithms on 
	singly link list.
Athor: Gal Dahan
Reviewer: Galit Vaknin
**********************************************************/

#include <stdio.h>/*printf*/
#include <stddef.h>/*typedef*/
#include <stdlib.h>/*malloc,free*/
#include <assert.h>/*assert*/

/* dummy is NULL */

typedef struct node
{
    void *data;
    struct node *next;
} node_t;

/* Reverse the order of a given slist. */
node_t *Flip(node_t *head);

/* Tells whether a given slist has loop. */
int HasLoop(const node_t *head);

/* Returns a pointer to a first bode mutual to both slists, if any. */
node_t *FindIntersection(const node_t *head_1, const node_t *head_2);

/*help functions:*/

/*return size of list*/
static int ListSize(const node_t *head);

/*return the n'th node*/
static node_t *RunNOnList(const node_t *head, int n);


/*TEST*/
int main()
{
	node_t *h1 = (node_t *) malloc(sizeof(node_t));
	node_t *h2 = (node_t *) malloc(sizeof(node_t));
	node_t *a = (node_t *) malloc(sizeof(node_t));
	node_t *b = (node_t *) malloc(sizeof(node_t));
	node_t *c = (node_t *) malloc(sizeof(node_t));
	node_t *d = (node_t *) malloc(sizeof(node_t));
	node_t *e = (node_t *) malloc(sizeof(node_t));
	node_t *f = (node_t *) malloc(sizeof(node_t));
	
	/* c->b->a->h1->NULL */
	c->next = b;
	b->next = a;
	a->next = h1;
	h1->next = NULL;
	
	/* exsepct to h1->a->b->c->NULL */
	if (h1 == Flip(c))
	{
		printf("Flip sucsess\n");
	}
	else
	{
		printf("Flip failed\n");
	}
	
	h2->next = b;
	/* h1->a->b->c->NULL , h2->b->c->NULL*/
	if (b == FindIntersection(h1, h2))
	{
		printf("FindIntersection find sucsess\n");
	}
	else
	{
		printf("FindIntersection find failed\n");
	}
	
	h2->next = d;
	d->next = NULL;
	/* h1->a->b->c->NULL , h2->d->NULL*/
	if (NULL == FindIntersection(h1, h2))
	{
		printf("FindIntersection sucsess\n");
	}
	else
	{
		printf("FindIntersection failed\n");
	}
	
	/* h1->a->b->c->NULL */
	if (0 == HasLoop(h1))
	{
		printf("HasLoop sucsess\n");
	}
	else
	{
		printf("HasLoop failed\n");
	}
	
	c->next = d;
	d->next = b;
	/* h1->a->b->c->d->b... */
	if (1 == HasLoop(h1))
	{
		printf("HasLoop loop sucsess\n");
	}
	else
	{
		printf("HasLoop loop failed\n");
	}
	
	free(h1);
	free(h2);
	free(a);
	free(b);
	free(c);
	free(d);
	free(e);
	free(f);

	return 0;
}

node_t *Flip(node_t *head)
{
	node_t *prev;
	node_t *curr;
	node_t *next;
	
	/* empty or one node */
	if (NULL == head && NULL == head->next)
	{
		return head;
	}
	
	prev = NULL;
	curr = head;
	next = curr;
	
	while (NULL != curr)
	{
		next = curr->next;
		curr->next = prev;
		prev = curr;
		curr = next;
	}
	
	return prev;
	
}

int HasLoop(const node_t *head)
{
    node_t *slow = (node_t *) head;
    node_t *fast;
    
    assert(head);
    
    /*one node*/
    if (NULL == head->next)
    {
        return 0;
    }
    
    fast = head->next;
    
    while (NULL != fast && NULL != fast->next && NULL != slow )
    {
    
        if (slow == fast)
        {
            return 1;
        }
        
        slow = slow->next;
        fast = fast->next->next;
    }
    
    return 0;
}

static int ListSize(const node_t *head)
{
	int size = 0;
	node_t *iter = (node_t *) head;
	
	assert(head);
	
	for (size = 0; NULL != iter; iter = iter->next , ++size)
	{
		/*empty*/
	}
	
	return size;
}

static node_t *RunNOnList(const node_t *head, int n)
{
	node_t *iter = (node_t *) head;
	
	for ( ; n > 0; --n, iter = iter->next)
	{
		/*empty*/
	}
	
	return iter;
}

node_t *FindIntersection(const node_t *head_1, const node_t *head_2)
{
	node_t *iter1 = (node_t *) head_1;
	node_t *iter2 = (node_t *) head_2;
	int size1 = ListSize(head_1);
	int size2 = ListSize(head_2);
	
	/* promote the long list the diff' */
	if (size1 > size2)
	{
		int def = size1 - size2;
		iter1 = RunNOnList(head_1, def);
	}
	else
	{
		int def = size2 - size1;
		iter2 = RunNOnList(head_2, def);
	}
	
	/* run & compare yntil end */
	while (NULL != iter1 && NULL != iter2)
	{
		
		if (iter1 == iter2)
		{
			return iter1;
		}
		
		iter1 = iter1->next;
		iter2 = iter2->next;
	}
	
	return NULL;
}



