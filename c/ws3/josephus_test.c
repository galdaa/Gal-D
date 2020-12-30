/******************************************
DESCRIPTION: Test for josephus problem.
Athor: Gal Dahan
Reviewer: Arie Charfnadel
*******************************************/

#include <stdio.h>/*for print*/

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
