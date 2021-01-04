/*********************************************************
ESCRIPTION: Inplement functions on Task.
Athor: Gal Dahan
Reviewer: Noa Efrati
**********************************************************/

#include <stdlib.h> 			/* malloc , free */
#include <assert.h>			/* assert */
#include <unistd.h>			/* sleep */
#include "task.h" 			/* rask API */  
#include "priority_queue.h"		/* priority_queue API 	*/
#include "scheduler.h"			/* scheduler API 	*/

struct scheduler
{
	pq_t *pq;
	int stop_flag;
};

static int Cmp(const void *lhs, const void *rhs)
{
	return (int) (TaskGetTimeToExec((task_t *)lhs) - 
						TaskGetTimeToExec((task_t *)rhs));
}

static int UidCmp(const void *lhs, const void *rhs)
{
	return UIDIsSame(*(ilrd_uid_t *)lhs, TaskGetUid((task_t *)rhs));
}

sched_t *SchedCreate(void)
{
	sched_t *new_sched = (sched_t *) malloc(sizeof(sched_t));
	
	if (NULL != new_sched)
	{
		new_sched->pq = PQCreate(&Cmp);
		
		if (NULL == new_sched->pq)
		{
			free(new_sched); new_sched = NULL;
			
			return NULL;
		}
		
		new_sched->stop_flag = 0;
	}
	
	return new_sched;
}
 
void SchedDestroy(sched_t *sch)
{
	assert(NULL != sch);
	
	SchedClear(sch);
	PQDestroy(sch->pq); sch->pq = NULL;
	free(sch); sch = NULL;
}
 
size_t SchedSize(const sched_t *sch)
{
	assert(NULL != sch);
	
	return PQSize(sch->pq);
}
 
int SchedIsEmpty(const sched_t *sch)
{
	assert(NULL != sch);
	
	return PQIsEmpty(sch->pq);
}

void SchedClear(sched_t *sch)
{
	assert(NULL != sch);
	
	while(!PQIsEmpty(sch->pq))
	{
		TaskDestroy(PQDequeue(sch->pq));
	}
	
}

ilrd_uid_t SchedAddTask(sched_t *sch, 
					int (*func_to_execute)(void *params),
			 		void *params, 
			 		size_t freq, 
			 		size_t time_to_exec,
			 		int (*destroy_params)(void *params))
{
	task_t *new_task = NULL;
	ilrd_uid_t new_uid = UIDGetBadUid();
	time_t new_time = 0;
	
	assert(NULL != sch);
		
	new_time = time(NULL) + time_to_exec;
	new_task = TaskCreate(func_to_execute, params, freq, 
                   new_time, destroy_params);
                   
        if (NULL != new_task)
        {
              
		if (0 != PQEnqueue(sch->pq, new_task))
		{
			TaskDestroy(new_task);
		}
		else
		{
			new_uid = TaskGetUid(new_task);
		}
		
	}
        
        return new_uid;            	
}

int SchedRemoveTask(sched_t *sch, ilrd_uid_t uid)
{
	task_t *catch_task = NULL;
	
	assert(NULL != sch);
	
	catch_task = (task_t *) PQErase(sch->pq, &UidCmp, &uid);
	
	if (NULL != catch_task)
	{
		TaskDestroy(catch_task);
		
		return 0;
	}
	
	return -1;
}
				 
void SchedRun(sched_t *sch)
{
	task_t *catch_task = NULL;
	
	assert(NULL != sch);
	
	sch->stop_flag = 0;
	
	while (!sch->stop_flag && !PQIsEmpty(sch->pq))
	{
		
		catch_task = PQDequeue(sch->pq);
		
		if (TaskGetTimeToExec(catch_task) > time(NULL))
		{
			sleep(TaskGetTimeToExec(catch_task) - time(NULL));
		}
		
		if (1 == TaskExecute(catch_task))
		{
			TaskSetNextExecTime(catch_task,
				time(NULL) + TaskGetFreq(catch_task));
			
			if (1 == PQEnqueue(sch->pq, catch_task))
			{
				TaskDestroy(catch_task);
			}
		}
		else
		{
			TaskDestroy(catch_task);
		}

	}
	
	SchedStop(sch);
}


void SchedStop(sched_t *sch)
{
	assert(NULL != sch);
	
	sch->stop_flag = 1;
	
}

