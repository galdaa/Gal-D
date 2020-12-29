#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "scheduler.h"

#define CHECK(test, str) ( (test) ? printf("passed %s tests\n", (str)) : printf("failed %s tests in line %d\n", (str), __LINE__))
#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))

int ExFunc(void *params);
int StopFunc(void *params);
int DestroyFunc(void *params);
void InitTest(void);
void AddTaskTest(void);
void RemoveTaskTest(void);
void RunTest(void);
void StopTest(void);

int main()
{
	InitTest();
	AddTaskTest();
	RemoveTaskTest();
	RunTest();
	StopTest();

	return 0;
}


void InitTest(void)
{
	sched_t *sched = SchedCreate();

	CHECK(SchedIsEmpty(sched), "empty");
	CHECK(0 == SchedSize(sched), "size");

	SchedDestroy(sched);
}

void AddTaskTest(void)
{
	sched_t *sched = SchedCreate();

	int *params = malloc(2 * sizeof(int));
	*params = 0;
	*(params + 1) = 0;

	SchedAddTask(sched, &ExFunc, params, 5, 5, &DestroyFunc);

	CHECK(!SchedIsEmpty(sched), "not empty");
	CHECK(1 == SchedSize(sched), "size");

	SchedDestroy(sched);
	
}

void RemoveTaskTest(void)
{
	sched_t *sched = SchedCreate();
	int flag = 0;
	ilrd_uid_t uid;
	int *params = malloc(2 * sizeof(int));
	*params = 0;
	*(params + 1) = 0;

	uid = SchedAddTask(sched, &ExFunc, params, 5, 5, &DestroyFunc);

	flag = (0 != SchedRemoveTask(sched, UIDCreate())); /*search for uid that isnt in list*/
	CHECK(flag, "uid not in q");

	CHECK(!SchedIsEmpty(sched), "not empty");
	CHECK(1 == SchedSize(sched), "size");

	flag = (0 == SchedRemoveTask(sched, uid)); /*search for uid that is in list*/
	CHECK(flag, "uid in q");

	CHECK(SchedIsEmpty(sched), "empty");
	CHECK(0 == SchedSize(sched), "size");

	SchedDestroy(sched);
	
}

void RunTest(void)
{
	sched_t *sched = SchedCreate();
	int *params = malloc(2 * sizeof(int));
	*params = 0;
	*(params + 1) = 0;

	SchedAddTask(sched, &ExFunc, params, 2, 5, &DestroyFunc);

	params = malloc(2 * sizeof(int));
	*params = 1;
	*(params + 1) = 0;

	SchedAddTask(sched, &ExFunc, params, 2, 2, &DestroyFunc);
	SchedRun(sched);	

	SchedDestroy(sched);	

}

void StopTest(void)
{
	sched_t *sched = SchedCreate();
	int *params = malloc(2 * sizeof(int));
	*params = 0;
	*(params + 1) = 0;

	SchedAddTask(sched, &ExFunc, params, 2, 5, &DestroyFunc);

	SchedAddTask(sched, &StopFunc, sched, 2, 7, NULL);

	SchedRun(sched);	

	SchedDestroy(sched);	

}

int ExFunc(void *params) /*first paramater is the task #, second is the round #*/
{
	int task_number = *(int*)params;
	int round_number = *((int*)params + 1);

	printf("task number: %d, round number: %d\n", task_number, round_number);

	return 3 > ++(*((int*)params + 1)) ? 1 : 0; /* if executed 3 times stop repeating */ 
}

int DestroyFunc(void *params)
{
	free(params);
	return 0;
}


int StopFunc(void *params) /*first paramater is the task #, second is the round #*/
{
	SchedStop(params);
	return 0;
}



