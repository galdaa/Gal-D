/**************************************************
DESCRIPTION: 
	Practice on struct & funcion's pointer:	
	Create array of struct of
	different values and pointer to
		function that prints.
	Using: funcions pointers, struct and array.
Athor: Gal Dahan
Reviewer: Yifat Baruch
***************************************************/

#include <stdio.h> 	/* for printf */
#include <stdlib.h>	/* for void (*ptr)(int); */

void Print(int val);

int main()
{
	int i = 0;
	
	struct print_me
	{
		int var; 
		void (*ptr)(int);
	};
	
	struct print_me arr[10] = {0};
	
	/*Initial arr with values
		and point to Print function*/
	for(i = 0; 10 > i; ++i)
	{
		arr[i].var = i;
		arr[i].ptr = Print;
	}
	
	for(i = 0; 10 > i; ++i)
	{
		arr[i].ptr(arr[i].var);
	}

	return 0;
}

void Print(int val)
{
	printf("My value is:%d\n", val);
}
