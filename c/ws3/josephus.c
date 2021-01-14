/*****************************************************
DESCRIPTION: Implement Solution for josephus problem.
Author: Gal Dahan
Reviewer: Arie Charfnadel

The mathematical solution is:
	If the number of soldiers = 2^a + l
	Represented as pwoer of 2 + res (= l)
	-> last = 2*l + 1
	In bits it's mean to put the MSB in LSB of l.
******************************************************/

#include <stdlib.h>/*for malloc,free*/

/*compute the last using loops*/
int LoopSol(int soldiers_num)
{
	char* soldiers = NULL;
	int i = 0;
	int count = 0;
	int lives = 0;/*how much lives in that round*/
	int last = 1;
	
	soldiers = (char *) malloc(soldiers_num + 1);
	lives = soldiers_num;
	
	/*all lives*/
	for (i = 0; i < soldiers_num; ++i)
	{
		*(soldiers + i) = 'L';
	}
	
	while(lives > 1)
	{
		lives = 0;
		
		for (i = 0; i < soldiers_num; ++i)
		{
				
			/*kill- if this is the second sol' that lives*/
			if ((1 == count) && ('L' == *(soldiers + i)))
			{
				*(soldiers + i) = 'D';
				count = 0;
			}
			
			else if ('L' == *(soldiers + i))
			{
				count = 1;
				++lives;
				last = i + 1;/*save the last sol' that lives*/
			}
			
		}
	
	}
	
	free(soldiers);
	
	return last;
}

int FreeListSol(int soldiers_num)
{
	int i = 0;
	int *soldiers = (int *) malloc(soldiers_num + 1);
	
	/*every soldier points on the next*/
	for(i = 0; i < soldiers_num; ++i)
	{
		soldiers[i] = i + 1;
	}
	
	i = 0;
	
	/*every soldier point on what his next points 
		-because the next now dead*/
	while( soldiers[soldiers[i]] != soldiers[i])
	{
		soldiers[i] = soldiers[soldiers[i]];
		i = soldiers[i];
	}
	
	free(soldiers);
	return i - 1;
}
