/*********************************************************
ESCRIPTION: Test functions on Priority Queue.
Athor: Gal Dahan
Reviewer:---
**********************************************************/

#include <stdio.h>/*printf*/
#include <stddef.h>   /* size_t */
#include <sys/types.h>   /* size_t, ssize_t */
#include <string.h>
#include <stdlib.h>
#include "tests.h"
#include "task.h"
#include "scheduler.h"

void Test(void);
int SPrint(void *params);
int SDestroy(void *params);
int SPrintC(void *params);
int SDestroyC(void *params);

int main()
{
	Test();
	return 0;
}

void Test(void)
{
	int arr[20];
	int i = 0;
	sched_t *sched = NULL;
	size_t freq = 5 * 60;/*5s*/
	size_t exe_time= 4 * 60 * 60; /*4h*/
	ilrd_uid_t save_uid1;
	ilrd_uid_t save_uid2;
	ilrd_uid_t save_uid3;
	char *c = NULL;
	
	for(i = 0; i < 20; ++i)
		arr[i] = i * 2 + 1;
	
	sched = SchedCreate();
	NTEST("SchedCreate", sched, NULL);
	printf("SchedCreate Sucsses  (not crashed)\n");

printf("===Stage 1===\n");
	TEST("SchedSize", SchedSize(sched), 0);
	TEST("SchedIsEmpty", SchedIsEmpty(sched), 1);

printf("===Stage 2===\n");
	save_uid1 = SchedAddTask(sched, &SPrint, arr + 1, freq, 
						exe_time, &SDestroy);	
	printf("SchedAddTask SUCCSESS (not crashed)\n");
	TEST("Check UID", 
		UIDIsSame(save_uid1, UIDGetBadUid()), 0);
	
	c = (char *) malloc(sizeof(char) * 5);
	c[0] = 'A'; c[1] = 'B'; c[2] = '~'; c[3] = 'Y'; c[4] = 'Z';
	
	freq = 10 * 60;/*5s*/
	exe_time= 5 * 60 * 60; /*4h*/
	
	save_uid2 = SchedAddTask(sched, &SPrintC, c, freq, 
						exe_time, &SDestroyC);		
	TEST("Check UID", 
		UIDIsSame(save_uid2, UIDGetBadUid()), 0);
	
	TEST("Check UID", 
		UIDIsSame(save_uid1, save_uid2), 0);
	
	TEST("SchedSize", SchedSize(sched), 2);
	TEST("SchedIsEmpty", SchedIsEmpty(sched), 0);	
	
	save_uid3 = SchedAddTask(sched, &SPrint, arr + 3, freq, 
						exe_time, &SDestroy);		
	TEST("SchedSize", SchedSize(sched), 3);	
	TEST("SchedRemoveTask", SchedRemoveTask(sched, save_uid3), 0);	
	TEST("SchedSize", SchedSize(sched), 2);
	
	save_uid3 = SchedAddTask(sched, &SchedStop, arr + 5, freq, 
						exe_time, &SDestroy);	
	
printf("===Stage 3===\n");	
	SchedRun(sched);
	printf("SchedClear SUCCSESS (finished)\n");

printf("===Stage 4===\n");
	SchedClear(sched);
	printf("SchedClear SUCCSESS (not crashed)\n");
	TEST("SchedSize", SchedSize(sched), 0);
	TEST("SchedIsEmpty", SchedIsEmpty(sched), 1);
	
printf("===Stage 5===\n");
	SchedDestroy(sched);
	printf("SchedDestroy SUCCSESS (not crashed)\n");
}

int IntCompare(const void *one, const void *other)
{
	return (*(int *) one - *(int *)other);
}

int IntMach(const void *one, const void *other)
{
	return (*(int *) one == *(int *)other);
}

int SPrint(void *params)
{
	printf("SPrint func' data = %d\n", *(int *)params);
	
	return 1;
}

int SDestroy(void *params)
{
	printf("~SDestroy func' data = %d\n", *(int *)params);
	
	return 0;
}

int SPrintC(void *params)
{

	int size = strlen((char*)params);
	int i = 0;
	
	printf("SPrintC func' start\n");
	
	for(i = 0; i < size; ++i)
	{
		printf("%c \n", ((char *)params)[i]);
	}
	
	printf("SPrintC func' end\n");
	
	return 1;
}

int SDestroyC(void *params)
{
	printf("~SDestroyC func' start\n");
	
	free(params);
	
	printf("~SDestroyC func' end\n");
	
	return 0;
}

			 


