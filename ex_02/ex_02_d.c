#include <stdio.h>
#include <signal.h>
#include <unistd.h>

#include <alchemy/task.h>

#define ONE_SECOND 1000000u

static RT_TASK task1;
static RT_TASK task2;
static RT_TASK task3;

void task1_function(void *arg)
{
    rt_task_set_periodic(NULL, TM_NOW, ONE_SECOND);
    int num = * (int *)arg;
    RT_TASK_INFO curtaskinfo;
    rt_task_inquire(NULL, &curtaskinfo);
    rt_task_sleep(ONE_SECOND);

    while(1){
        rt_printf("Task name: %s, Task priority : %d, num : %d \n",
        curtaskinfo.name, curtaskinfo.prio, num);
        rt_task_wait_period(NULL);
    }
  return;
}

void task2_function(void *arg)
{
    rt_task_set_periodic(NULL, TM_NOW, 2 * ONE_SECOND);
    int num = * (int *)arg;
    RT_TASK_INFO curtaskinfo;
    rt_task_inquire(NULL, &curtaskinfo);
    rt_task_sleep(ONE_SECOND);

    while(1){
        rt_printf("Task name: %s, Task priority : %d, num : %d \n",
        curtaskinfo.name, curtaskinfo.prio, num);
        rt_task_wait_period(NULL);
    }
  return;
}

void task3_function(void *arg)
{
    rt_task_set_periodic(NULL, TM_NOW, 3 * ONE_SECOND);
    int num = * (int *)arg;
    RT_TASK_INFO curtaskinfo;
    rt_task_inquire(NULL, &curtaskinfo);
    rt_task_sleep(ONE_SECOND);

    while(1){
        rt_printf("Task name: %s, Task priority : %d, num : %d \n",
        curtaskinfo.name, curtaskinfo.prio, num);
        rt_task_wait_period(NULL);
    }
  return;
}

int main(int argc, char* argv[]) {

    int taskArg = 5;
    // Create Tasks
    rt_task_create(&task1, "task1", 0, 50, 0);
    rt_task_create(&task2, "task2", 0, 50, 0);
    rt_task_create(&task3, "task3", 0, 50, 0);

    // Start Tasks
    rt_task_start(&task1, &task1_function, (void *) &taskArg);
    rt_task_start(&task2, &task2_function, (void *) &taskArg);
    rt_task_start(&task3, &task3_function, (void *) &taskArg);

    // Avoid termination when the main loop stops
    rt_printf("end program by CTRL-C\n");
    pause();
    return 0;
}
