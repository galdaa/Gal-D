/*********************************************************
ESCRIPTION: Test functions on Task.
Athor: Gal Dahan
Reviewer:---
**********************************************************/

#include <stdio.h>		/* printf */
#include <stddef.h>   		/* size_t */
#include <sys/types.h>   	/* size_t, ssize_t */
#include "tests.h"
#include "task.h"

void Test(void);
int Print(void *params);
int Destroy(void *params);

int main()
{
	Test();
	return 0;
}

void Test(void)
{
	int arr[20];
	int i = 0;
	task_t *task = NULL;
	task_t *task2 = NULL;
	size_t freq = 0;
	time_t exe_time= 4 * 60 * 60; /*4h*/
	time_t time_ref= 5 * 60 * 60; /*5h*/
	
	for(i = 0; i < 20; ++i)
		arr[i] = i * 2 + 1;
		
	task = TaskCreate(&Print, arr, freq, exe_time, &Destroy);
	freq = 5;
	task2 = TaskCreate(&Print, arr, freq, exe_time, &Destroy);           
	
	if (NULL != task)
	{
		TEST("TaskCreate", 1, 1);
	}
	else
	{
		TEST("TaskCreate", 0, 1);
	}

	printf("TaskCreate Sucsses  (not crashed)\n");
printf("===Stage 1===\n");

	TEST("TaskExecute", TaskExecute(task), 0);
	TEST("TaskExecute", TaskExecute(task2), 0);
	
printf("===Stage 2===\n");
	freq = 0;
	TEST("TaskGetFreq", TaskGetFreq(task), freq);
	freq = 5;
	TEST("TaskGetFreq", TaskGetFreq(task2), freq);
	
printf("===Stage 3===\n");	

	TEST("UIDIsSame(TaskGetUid)", 
		UIDIsSame(TaskGetUid(task), UIDGetBadUid()), 0);

	TEST("UIDIsSame(TaskGetUid)", 
		UIDIsSame(TaskGetUid(task), TaskGetUid(task2)), 0);
		
printf("===Stage 4===\n");
	
	TEST("TaskGetTimeToExec", TaskGetTimeToExec(task) == exe_time, 1);
	
	TaskSetNextExecTime(task, time_ref);
	printf("TaskSetNextExecTime SUCCSESS (not crashed)\n");

printf("===Stage 5===\n");
	TEST("TaskDestroy", TaskDestroy(task), 0);
	printf("TaskDestroy SUCCSESS (not crashed)\n");
}

int IntCompare(const void *one, const void *other)
{
	return (*(int *) one - *(int *)other);
}

int IntMach(const void *one, const void *other)
{
	return (*(int *) one == *(int *)other);
}

int Print(void *params)
{
	printf("Print func' data = %d\n", *(int *)params);
	
	return 0;
}

int Destroy(void *params)
{
	printf("~Destroy func' data = %d\n", *(int *)params);
	
	return 0;
}

