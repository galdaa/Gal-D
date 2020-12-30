/******************************************
DESCRIPTION: Solution of josephus problem.
Athor: Gal Dahan
Reviewer: Arie Charfnadel
*******************************************/

#include <stdio.h>/*for print*/
#include <stdlib.h>/*for malloc,free*/

int FreeListSol(int soldiers_num);
int LoopSol(int soldiers_num);

int main()
{
	int num = 0;
	
	printf("Enter num of soldiers:");
	scanf("%d", &num);
	printf("The last by Loop solution is:%d\n", LoopSol(num));
	printf("By 'Free list' solution The last is:%d\n",
		 FreeListSol(num));
		 
	return 0;
}

/*compute the last using loops*/
int LoopSol(int soldiers_num)
{
	char* soldiers = NULL;
	int i = 0;
	int count = 0;
	int lives = 0;/*how nuch lives in that round*/
	int last = 1;
	
	soldiers = (char *) malloc(soldiers_num + 1);
	lives = soldiers_num;
	
	/*all lives*/
	for (i = 0; i < soldiers_num; i++)
	{
		*(soldiers + i) = 'L';
	}
	
	while(lives > 1)
	{
		lives = 0;
		
		for (i = 0; i < soldiers_num; i++)
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
		-becouse the next now dead*/
	while( soldiers[soldiers[i]] != soldiers[i])
	{
		soldiers[i] = soldiers[soldiers[i]];
		i = soldiers[i];
	}
	
	free(soldiers);
	return i - 1;
}
