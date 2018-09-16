#include <stdio.h>
#include <signal.h>
#include <unistd.h>

#include <alchemy/task.h>

static RT_TASK  task1;
static RT_TASK  task2;
static RT_TASK  task3;

void demo(void *arg) {
    int num = * (int *)arg;
    RT_TASK_INFO curtaskinfo;
    rt_task_inquire(NULL,&curtaskinfo);
    rt_printf("Task name: %s, Task priority : %d, num : %d \n", 
        curtaskinfo.name, curtaskinfo.prio, num);
}

int main(int argc, char* argv[]) {
    
    int taskArg = 5;
    // Create Tasks
    rt_task_create(&task1, "task1", 0, 50, 0);
    rt_task_create(&task2, "task2", 0, 50, 0);
    rt_task_create(&task3, "task3", 0, 50, 0);

    // Start Tasks
    rt_task_start(&task1, &demo, (void *) &taskArg);
    rt_task_start(&task2, &demo, (void *) &taskArg);
    rt_task_start(&task3, &demo, (void *) &taskArg);

    return 0;
}
