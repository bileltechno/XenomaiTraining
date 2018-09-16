# Scheduling the Task
A task can be scheduled in two ways.

## one-shot mode
One-shote mode is the default when a task is started by the 'rt_task_start' function, as introduced in exercise 1.

## periodic mode
* A periodic task is also started by the 'rt_task_start' function, but it made periodic executing the command:
    `int rt_task_set_periodic(RT_TASK *task,
                         RTIME start_time,
                         RTIME period);`
    * 'task' is the descriptor of the affected task. This task is immediately delayed until the first periodic release point is reached. If task is NULL, the current task is set periodic.
    * 'start_time' is the absolute time, expressed in clock ticks ( nanoseconds or jiffies), when the task should begin execution. If 'start_time' is equal to TM_NOW, the current system date is used, and no initial delay takes place.
    * 'period' is the task's period, in clock ticks, which will be rounded to the nearest multiple of the period of the system timer in periodic mode. 
* When a period task has perfomed its functionality, it releases the processor and starts waiting for the next period with the command:
void rt_task_wait_period(NULL);
* It is important that timing parameters have time RTIME (unsigned long long).
* rt_task_set_periodic can be place in demo task (WITH NULL as parameter) or in main (before start of task) but then with task as parameter.

As an example, consider a task function which executes an infinite loop which typically reads some inputs, computes some outputs and waits for the next period. Typical code looks like this:

`void task_function(void *arg)
{
  rt_task_set_periodic(NULL, TM_NOW, period_ns);
  while (1) {
    /*
      Do your thing here
     */
    rt_task_wait_period(NULL);
  }
  return;
}`
