/*********************************************************
ESCRIPTION: Inplement functions on Task.
Athor: Gal Dahan
Reviewer: Noa Efrati
**********************************************************/

#include <stdlib.h> 	/* malloc , free */
#include <assert.h>	/* assert */
#include "task.h" 	/* rask API */       
    

struct task
{
	ilrd_uid_t uid;
	int (*exec_func)(void *params);
	void *params;
	size_t freq;
	time_t time_to_exec;
	int (*destroy_params)(void *params);
};



task_t *TaskCreate(int (*exec_func)(void *params), 
                   void *params, 
                   size_t freq, 
                   time_t time_to_exec,
                   int (*destroy_params)(void *params))
{
	task_t *new_task = NULL;
	
	assert(NULL != exec_func);
	
	new_task = (task_t *) malloc(sizeof(task_t));
	
	if (NULL != new_task)
	{
		new_task->uid = UIDCreate();
		
		if (1 == UIDIsSame(UIDGetBadUid(), new_task->uid))
		{
			if (NULL != destroy_params)
			{
				destroy_params(params);
			}
			
			free(new_task); new_task = NULL;
			
			return NULL;
		}
		
		new_task->exec_func = exec_func;
		new_task->params = params;
		new_task->freq = freq;
		new_task->time_to_exec = time_to_exec;
		new_task->destroy_params = destroy_params;
	}
	else if (NULL != destroy_params)
	{
		destroy_params(params);
	}
	
	return new_task;
} 

int TaskDestroy(task_t *task)
{
	int val = 0;
	
	assert(NULL != task);
	
	if (NULL != task->destroy_params)
	{
		val = task->destroy_params(task->params);
	}
	
	free(task); task = NULL;
	
	return val;
}

ilrd_uid_t TaskGetUid(const task_t *task)
{
	assert(NULL != task);
	
	return task->uid;
}

size_t TaskGetFreq(const task_t *task)
{
	assert(NULL != task);
	
	return task->freq;
}

time_t TaskGetTimeToExec(const task_t *task)
{
	assert(NULL != task);
	
	return task->time_to_exec;
}

int TaskExecute(task_t *task)
{
	assert(NULL != task);

	return task->exec_func(task->params);
}

void TaskSetNextExecTime(task_t *task, time_t new_exec_time)
{
	assert(NULL != task);

	task->time_to_exec = new_exec_time;
}


