#Objectives
The following are the primary objectives of this exercise:

To learn how to build and execute a Xenomai program which creates and starts a real-time task.
To be able to use error codes.
The exercises are based on Xenomai 3 using the Alchemy API.

The example program below creates and starts a task, see also the task management services of the Alchemy API.

#Creating a task
When you create a real-time task in Xenomai the RT_TASK structure is used as the descriptor to refer to this task.
An RT_TASK data structure is used to hold all the information about a task:
the task function to be executed by the real-time task,
any initial argument passed to it,
the size of the stack allocated for its variables,
its priority,
whether or not it uses floating-point math,
and a "signal handler" that will be called when the task becomes active.
The task is created by calling rt_task_create:
int rt_task_create (RT_TASK *task, const char *name, int stack_size, int priority, int mode)
'task' is a pointer to an RT_TASK type structure which must have been declared before and whose structure is filled.
'name'  is an  ASCII string standing for the symbolic name of the task. This symbolic name you can use to retrieve the task structure anywhere else in your code by calling the rt_task_bind() function.
'stack_size' is the size of the stack to be used by the new task.
'priority' is the priority to be given the task. The highest priority is 99, while the lowest is 0.
'mode' is a set of flags which affect the task, for instance:
T_JOINABLE allows another task to wait on the termination of the new task. This implies that rt_task_join() is actually called for this task to clean up any user-space located resources after its termination.

#Starting a task
A task can be started by calling rt_task_start:
int rt_task_start (RT_TASK *task, void(*)(void *arg) entry, void *arg)
    
'task' is a pointer to an RT_TASK type structure which must be already initialized by a call to rt_task_create().
'entry' is the address of the task function to be executed by this real-time task.
'arg' is the void pointer argument given to the task function.

#Error handling
Xenomai uses the standard errors defined in the headers:
/usr/include/asm-generic/errno-base.h  for error numbers 1-34
/usr/include/asm-generic/errno.h  for error numbers 35-131
The Xenomai API specifies for each function is specified which specific errors are generated when an error happens. However the more general errors like passing the wrong value to a function are not specified by the API. Hence, it is possible to obtain an error code not specified in the API documentation.

The strerror function provides a convenient way to stop a program and print the error. The following example demonstrates this

  #include <errno.h>
   ...

  /* send message */
  retval = rt_task_send(&task_struct[1], &task_mcb , NULL, TM_INFINITE); 
  if (retval < 0 ) 
  {
      rt_printf("Sending error %d : %s\n",-retval,strerror(-retval));
  } else {
      rt_printf("taskOne sent message to taskTwo\n");
  }

#Exercises
Exercise 1a.
Compile and run program ex01a.c as described above, using the files ex01a.c and Makefile.

Exercise 1b.
Copy file ex01a.c to ex01b.c and introduce an error by changing

rt_task_start(&hello_task, &helloWorld, 0);
into
rt_task_start(NULL, &helloWorld, 0);
Add ex01b to the EXECUTABLE list in the Makefile by

EXECUTABLE := ex01a ex01b
Next build and run this program; observe the result.
Next introduce a return value for the 'rt_task_start' call and print the error code as described above.

Rebuild and rerun the new version of the program, observe the different output.
