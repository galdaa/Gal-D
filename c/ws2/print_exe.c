/* *************************************************
DESCRIPTION: 
	
	Implemets of:
		PrintAdresses exe.

Athor: Gal Dahan
***************************************************/

#include <stdio.h> 	/*printf */
#include <stdlib.h> 	/* malloc, free */


void PrintAdresses()
{
	static int s_i = 7;
	int i = 7;
	int *ptr = &i;
	int *ptr2 = (int *) malloc(sizeof(int));
	
	if (ptr)
	{
		&ptr;
	}
	
	free(ptr2);
	
	/*print by using (void*) to hold any kind of pointer */
	printf("s_i: %p \ni:   %p \nptr: %p \nptr2:%p \n",
		 (void*) &s_i, (void*) &i, (void*) &ptr, (void*) &ptr2);
} 

