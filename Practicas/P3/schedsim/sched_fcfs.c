#include "sched.h"

static task_t* pick_next_task_fcfs(runqueue_t* rq)
{
	task_t* t=head_slist(&rq->tasks);

	/* Current is not on the rq -> let's remove it */
	if (t)
		remove_slist(&rq->tasks,t);

	return t;
}

static void enqueue_task_fcfs(task_t* t,runqueue_t* rq, int runnable)
{
	//Si la tarea esta en una rq o ocupada no hacemos nada
	if (t->on_rq || is_idle_task(t))
		return;

	//Añadimos la tarea al final de la cola
	insert_slist(&rq->tasks, t);
}

static task_t* steal_task_fcfs(runqueue_t* rq)
{
	task_t* t=tail_slist(&rq->tasks);

	if (t)
		remove_slist(&rq->tasks,t);

	return t;
}

sched_class_t fcfs_sched= {
	.pick_next_task=pick_next_task_fcfs,
	.enqueue_task=enqueue_task_fcfs,
	.steal_task=steal_task_fcfs
};
