#include <stdio.h>
void PrintAdreeses ()
{
	static int s_i = 7;
	int i = 7;
	int *ptr = &i;
	int *ptr2 = (int *)malloc(sizeof(int));
	
	if(ptr)
	{
		&ptr;
	}
	
	free(ptr2);
	
	//print
	printf(" s_i: %d i:%d ptr:%d ptr2:%d \n ", &si , &i , &ptr , &ptr2 );
} 
