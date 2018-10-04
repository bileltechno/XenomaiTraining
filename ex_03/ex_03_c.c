#include <stdio.h>
#include <signal.h>
#include <unistd.h>

#include <alchemy/task.h>
#include <alchemy/timer.h>
#include <alchemy/sem.h>

static RT_TASK  task1;
static RT_TASK  task2;
static RT_TASK  task3;
static RT_TASK  task4;
static RT_TASK  task5;
static RT_SEM sem;
int global = 0;

void demo(void *arg) {
    rt_sem_p(&sem, TM_INFINITE);
    int num = * (int *)arg;
    RT_TASK_INFO curtaskinfo;
    rt_task_inquire(NULL,&curtaskinfo);
    global++;
    printf("I am %s and global = %d ----------------\n", curtaskinfo.name, global);
    rt_printf("Task name: %s, Task priority : %d, num : %d \n", 
        curtaskinfo.name, curtaskinfo.prio, num);
    rt_sem_v(&sem);
}

int main(int argc, char* argv[]) {

    int taskArg = 5;
    // Create Tasks
    rt_task_create(&task1, "task1", 0, 4, 0);
    rt_task_create(&task2, "task2", 0, 30, 0);
    rt_task_create(&task3, "task3", 0, 17, 0);
    rt_task_create(&task4, "task4", 0, 50, 0);
    rt_task_create(&task5, "task5", 0, 2, 0);

    // Create Semaphore
    rt_sem_create(&sem, "semaphore", 0, S_PRIO);

    // Start Tasks
    rt_task_start(&task1, &demo, (void *) &taskArg);
    rt_task_start(&task2, &demo, (void *) &taskArg);
    rt_task_start(&task3, &demo, (void *) &taskArg);
    rt_task_start(&task4, &demo, (void *) &taskArg);
    rt_task_start(&task5, &demo, (void *) &taskArg);

    rt_sem_delete(&sem);
    return 0;
}
