#include <stdio.h>
#include <signal.h>
#include <unistd.h>

#include <alchemy/task.h>

static RT_TASK  task1;
static RT_TASK  task2;
static RT_TASK  task3;
static RT_TASK  task4;
static RT_TASK  task5;

void demo(void *arg) {
    RT_TASK_INFO curtaskinfo;
    rt_task_inquire(NULL,&curtaskinfo);
    rt_printf("Task name: %s, Task priority : %d, Task pid : %d \n", 
        curtaskinfo.name, curtaskinfo.prio, curtaskinfo.pid);
}

int main(int argc, char* argv[]) {

    // Create Tasks
    rt_task_create(&task1, "task1", 0, 50, 0);
    rt_task_create(&task2, "task2", 0, 50, 0);
    rt_task_create(&task3, "task3", 0, 50, 0);
    rt_task_create(&task4, "task4", 0, 50, 0);
    rt_task_create(&task5, "task5", 0, 50, 0);
    // Start Tasks
    rt_task_start(&task1, &demo, 0);
    rt_task_start(&task2, &demo, 0);
    rt_task_start(&task3, &demo, 0);
    rt_task_start(&task4, &demo, 0);
    rt_task_start(&task5, &demo, 0);

    return 0;
}
