#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

#include <alchemy/task.h>
#include <alchemy/timer.h>
#include <alchemy/sem.h>

#define ITER 10

static RT_TASK  t1;
static RT_TASK  t2;
static RT_SEM sem;
int global = 0;

void task_0(void *arg)
{
    int i = 0;
    rt_sem_p(&sem, TM_INFINITE);
    for (i=0; i < ITER; i++)
    {
        global = 0;
        printf("I am task_0 and global = %d ................\n", global);
    }
    rt_sem_v(&sem);
}

void task_1(void *arg)
{
   int i = 0;
    rt_sem_p(&sem, TM_INFINITE);
    for (i=0; i < ITER; i++) 
    {
        global = 1;
        printf("I am task_1 and global = %d ----------------\n", global);
    }
    rt_sem_v(&sem);
}

int main(int argc, char* argv[])
{
    rt_task_create(&t1, "task_0", 0, 1, 0);
    rt_task_create(&t2, "task_1", 0, 1, 0);
    rt_sem_create(&sem, "semaphore", 0, S_PRIO);
    rt_task_start(&t1, &task_0, 0);
    rt_task_start(&t2, &task_1, 0);
    rt_sem_delete(&sem);
    return EXIT_SUCCESS;
}
