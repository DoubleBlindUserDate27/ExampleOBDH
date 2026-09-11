#ifndef __TASKS_h
#define __TASKS_h

#include <rtems.h>
#include <bsp.h>

rtems_task Sender(rtems_task_argument arg);
rtems_task DetectorTask(rtems_task_argument arg);
rtems_task KernelTask(rtems_task_argument arg);
rtems_task Actor1Task(rtems_task_argument arg);
rtems_task Actor2Task(rtems_task_argument arg);
rtems_task Actor3Task(rtems_task_argument arg);
rtems_task Reader1(rtems_task_argument arg);
rtems_task Reader2(rtems_task_argument arg);
rtems_task Reader3(rtems_task_argument arg);

#endif