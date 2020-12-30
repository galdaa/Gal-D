/* *************************************************
DESCRIPTION: 
	
	Implemets of:	
		Swap functions: 
			Int by poiners. 
			Values by size_t pointers.
			Pointers by size_t **.
Athor: Gal Dahan
***************************************************/

#include <stdlib.h> /* for size_t */

void SwapSizeT (size_t *a, size_t *b);
void SwapSizeTPointers (size_t **a, size_t **b);
void SwapInt (int *a, int *b);

/* Swap values of 2 size_t variables */
void SwapSizeT(size_t *a, size_t *b)
{
	size_t temp;
	
	temp = *a;
	*a = *b;
	*b = temp;
}

/* Swap values of 2 size_t* variables */
void SwapSizeTPointers(size_t **a, size_t **b)
{
	size_t *temp;
	
	temp = *a;
	*a = *b;
	*b = temp;
}

/* Swap values of 2 int variables */
void SwapInt(int *a, int *b)
{
	int temp;
	
	temp = *a;
	*a = *b;
	*b = temp;
}
