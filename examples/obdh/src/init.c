#include <stdio.h>
#include "config.h"
#include "tasks.h"
#include "obdh.h"

rtems_id Task_ids[11];

rtems_task Init(rtems_task_argument argument)
{
   printf("********************************************\n");
   printf("*** OBDH testing program                 ***\n");
   printf("********************************************\n");

   rtems_task_create(rtems_build_name('P','R','O','D'), 
                     20, 
                     RTEMS_MINIMUM_STACK_SIZE, 
                     RTEMS_DEFAULT_MODES,
                     RTEMS_DEFAULT_ATTRIBUTES, 
                     &Task_ids[0]);

   rtems_task_create(rtems_build_name('A','C','T','1'), 
                     20, 
                     RTEMS_MINIMUM_STACK_SIZE, 
                     RTEMS_DEFAULT_MODES,
                     RTEMS_DEFAULT_ATTRIBUTES, 
                     &Task_ids[1]);

   rtems_task_create(rtems_build_name('A','C','T','2'), 
                     20, 
                     RTEMS_MINIMUM_STACK_SIZE, 
                     RTEMS_DEFAULT_MODES,
                     RTEMS_DEFAULT_ATTRIBUTES, 
                     &Task_ids[2]);

   rtems_task_create(rtems_build_name('A','C','T','3'), 
                     20, 
                     RTEMS_MINIMUM_STACK_SIZE, 
                     RTEMS_DEFAULT_MODES,
                     RTEMS_DEFAULT_ATTRIBUTES, 
                     &Task_ids[3]);

   rtems_task_create(rtems_build_name('K','E','R','1'), 
                     20, 
                     RTEMS_MINIMUM_STACK_SIZE, 
                     RTEMS_DEFAULT_MODES,
                     RTEMS_DEFAULT_ATTRIBUTES, 
                     &Task_ids[4]);

   rtems_task_create(rtems_build_name('D','E','T','1'), 
                     20, 
                     RTEMS_MINIMUM_STACK_SIZE, 
                     RTEMS_DEFAULT_MODES,
                     RTEMS_DEFAULT_ATTRIBUTES, 
                     &Task_ids[5]);

   rtems_task_create(rtems_build_name('R','E','A','1'), 
                     20, 
                     RTEMS_MINIMUM_STACK_SIZE, 
                     RTEMS_DEFAULT_MODES,
                     RTEMS_DEFAULT_ATTRIBUTES, 
                     &Task_ids[6]);

   rtems_task_create(rtems_build_name('R','E','A','2'), 
                     20, 
                     RTEMS_MINIMUM_STACK_SIZE, 
                     RTEMS_DEFAULT_MODES,
                     RTEMS_DEFAULT_ATTRIBUTES, 
                     &Task_ids[7]);

   rtems_task_create(rtems_build_name('R','E','A','3'), 
                     20, 
                     RTEMS_MINIMUM_STACK_SIZE, 
                     RTEMS_DEFAULT_MODES,
                     RTEMS_DEFAULT_ATTRIBUTES, 
                     &Task_ids[8]);

   rtems_message_queue_create(rtems_build_name('K','1','i','n'),
                              3,
                              sizeof(uint32_t),
                              RTEMS_DEFAULT_ATTRIBUTES,
                              &i_tc);

   rtems_message_queue_create(rtems_build_name('D','1','i','n'),
                              1,
                              sizeof(uint32_t),
                              RTEMS_DEFAULT_ATTRIBUTES,
                              &i_ev);

   rtems_message_queue_create(rtems_build_name('D','1','o','t'),
                              1,
                              sizeof(uint32_t),
                              RTEMS_DEFAULT_ATTRIBUTES,
                              &s_scen);

   rtems_message_queue_create(rtems_build_name('A','1','i','n'),
                              1,
                              sizeof(uint32_t),
                              RTEMS_DEFAULT_ATTRIBUTES,
                              &s_a1);

   rtems_message_queue_create(rtems_build_name('A','2','i','n'),
                              1,
                              sizeof(uint32_t),
                              RTEMS_DEFAULT_ATTRIBUTES,
                              &s_a2);

   rtems_message_queue_create(rtems_build_name('A','3','i','n'),
                              1,
                              sizeof(uint32_t),
                              RTEMS_DEFAULT_ATTRIBUTES,
                              &s_a3);

   rtems_message_queue_create(rtems_build_name('A','1','o','t'),
                              1,
                              sizeof(uint32_t),
                              RTEMS_DEFAULT_ATTRIBUTES,
                              &o_a1);

   rtems_message_queue_create(rtems_build_name('A','2','o','t'),
                              1,
                              sizeof(uint32_t),
                              RTEMS_DEFAULT_ATTRIBUTES,
                              &o_a2);

   rtems_message_queue_create(rtems_build_name('A','3','o','t'),
                              1,
                              sizeof(uint32_t),
                              RTEMS_DEFAULT_ATTRIBUTES,
                              &o_a3);

   rtems_task_start(Task_ids[0], Sender, 0);
   rtems_task_start(Task_ids[1], Actor1Task, 0);
   rtems_task_start(Task_ids[2], Actor2Task, 0);
   rtems_task_start(Task_ids[3], Actor3Task, 0);
   rtems_task_start(Task_ids[4], KernelTask, 0);
   rtems_task_start(Task_ids[5], DetectorTask, 0);
   rtems_task_start(Task_ids[6], Reader1, 0);
   rtems_task_start(Task_ids[7], Reader2, 0);
   rtems_task_start(Task_ids[8], Reader3, 0);

   rtems_task_delete(RTEMS_SELF);
}