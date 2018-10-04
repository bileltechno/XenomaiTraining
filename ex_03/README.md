# Introduction
Semaphores are useful to coordinate the activities of multitasking applications. The most obvious way for tasks to communicate is via various shared data structures. Because all tasks inside a single process exist in a single linear address space, sharing data structures between tasks is trivial. Global variables, linear buffers, ring buffers, link lists, and pointers can be referenced directly by code running in a different task context. However, while shared address space simplifies the exchange of data, interlocking access to memory is crucial to avoid data corruption. One of the methods to ensure exclusive access to shared resources is the semaphore mechanism. In addition, semaphores can be used for task synchronization.

# Objectives
The following are the primary objectives of this exercise:

To get some experience with the use of semaphores in Xenoma

# Description
The semaphores in Xenomai provide fast intertask communication. Semaphores are the primary means for addressing the requirements of both mutual exclusion and task synchronization. In general we can say: 

The interface of a semaphore consists of two atomic operations, V and P, which affect an internal counter associated with the semaphore. V comes from the Dutch word "Verhogen" meaning  "increment"; P from the Dutch word "Proberen" meaning "try-to-decrease".
The 'V' (signal, release, give) operation increments the counter and returns immediately.
The 'P' operation (wait, acquire, take) decrements the counter and returns immediately, unless the counter is already zero and the operation blocks until another process releases the semaphore. 
A semaphore in Xenomai is counting semaphore which can be used to guard multiple instances of a resource, this in contrast to a binary semaphore which only uses the values 0 and 1. A binary semaphore is called "mutex" in Xenomai and has a separate API which will be treated in exercise 6.
Semaphore API

See the semaphore services of the Alchemy API.

Create a counting semaphore:
int rt_sem_create(RT_SEM *sem, const char *name, unsigned long icount, int mode) 
where icount is the initial value of the counter and mode can, for instance, be S_FIFO or S_PRIO which makes tasks pend on the semaphore in FIFO order or in priority order, respectively. (See the Xenomai API for more details.)
Take a semaphore using an optional timeout:
int rt_sem_p(RT_SEM *sem, RTIME timeout)
Give or signal a semaphore:
int rt_sem_v(RT_SEM *sem)
Broadcast a semaphore, i.e., signaling a semaphore, unblocks all tasks waiting on it:
int rt_sem_broadcast(RT_SEM *sem)
Delete a semaphore:
int rt_sem_delete(RT_SEM *sem)
