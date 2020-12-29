/******************************************************************************
*Description: 
*Author: Galit Vaknin
*Reviewer: 
*Date:
*Infinity Labs OL97
******************************************************************************/

#include <stdio.h> /* printf, scanf */
#include <stdlib.h> /* malloc,free */
#include <time.h>
#include "sort.h"
#define ARRAY_SIZE 5000
#define DEF     "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */
typedef void  (*sort_function)(int *array, size_t len);
static  void SortCmp(sort_function sort_algo1,sort_function sort_algo2 ,
int *array ,size_t len );
static void RunClock(sort_function sort_algo ,int *array ,size_t len);

int main()
{
	int *big_array =(int *) malloc(sizeof(int) * ARRAY_SIZE);
	if(big_array )
	{
		int i =0 ;
		for (; i < ARRAY_SIZE ; ++i)
		{
			big_array[i] = rand(); 
		}
		printf( BOLDGREEN "BubbleSort\n");
		printf(  BOLDBLUE "SelectionSort\n");
		SortCmp( BubbleSort,SelectionSort ,big_array,ARRAY_SIZE);
		printf( BOLDGREEN "BubbleSort\n");
		printf(  BOLDBLUE "InsertionSort ,\n");
		SortCmp(BubbleSort ,InsertionSort ,big_array,ARRAY_SIZE);
		printf(  BOLDGREEN "InsertionSort ,\n");
		printf(  BOLDBLUE "SelectionSort\n");
		SortCmp(InsertionSort ,SelectionSort ,big_array,ARRAY_SIZE);
		free(big_array);
	}
	return 0;
}

static  void SortCmp(sort_function sort_algo1,sort_function sort_algo2 
,int *array ,size_t len )
{
	printf( BOLDGREEN "Starting of algo1\n");
	RunClock(sort_algo1, array ,  len);
	printf(  BOLDBLUE "Starting of algo2\n");
	RunClock(sort_algo2, array ,  len);
	printf( DEF" end\n");
}

static void RunClock(sort_function sort_algo ,int *array ,size_t len)
{
	clock_t start_t, end_t, total_t;
	size_t i;
	int *cpy_array = (int *)malloc(sizeof(int) * len);
	if(!cpy_array)
	{
		return;
	}
	for(i = 0; i<len; ++i)
	{
		cpy_array[i] = array[i];
	}
	start_t = clock();
	
	printf("Starting of the program, start_t = %ld\n", start_t);
	printf("Run sort_algo, start_t = %ld\n", start_t);
	sort_algo(cpy_array, len);
	 end_t = clock();
	printf("End sort_algo1, end_t = %ld\n", end_t);
	total_t = (end_t - start_t) ;
	printf("Total time taken by CPU: %ld\n", total_t  );
	for(i = 0; i<len-1; ++i)
	{
		if(cpy_array[i]  > cpy_array[i+1])
		{
			printf(RED"sortfail in i=%ld arr[i]=%d arr[i+1]= %d\n"
			,i,cpy_array[i],cpy_array[i+1] );
		}
	}
	free(cpy_array);
}



