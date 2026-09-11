#ifndef __CONFIG_h
#define __CONFIG_h

#include <bsp.h>

/**************** START OF CONFIGURATION INFORMATION ****************/

#define CONFIGURE_APPLICATION_NEEDS_CONSOLE_DRIVER
#define CONFIGURE_APPLICATION_NEEDS_CLOCK_DRIVER

#define CONFIGURE_MAXIMUM_TASKS             11
#define CONFIGURE_MAXIMUM_MESSAGE_QUEUES    9
#define CONFIGURE_MESSAGE_BUFFER_MEMORY \
         CONFIGURE_MESSAGE_BUFFERS_FOR_QUEUE(3, sizeof(uint32_t)) + \
         CONFIGURE_MESSAGE_BUFFERS_FOR_QUEUE(1, sizeof(uint32_t)) + \
         CONFIGURE_MESSAGE_BUFFERS_FOR_QUEUE(1, sizeof(uint32_t)) + \
         CONFIGURE_MESSAGE_BUFFERS_FOR_QUEUE(1, sizeof(uint32_t)) + \
         CONFIGURE_MESSAGE_BUFFERS_FOR_QUEUE(1, sizeof(uint32_t)) + \
         CONFIGURE_MESSAGE_BUFFERS_FOR_QUEUE(1, sizeof(uint32_t)) + \
         CONFIGURE_MESSAGE_BUFFERS_FOR_QUEUE(1, sizeof(uint32_t)) + \
         CONFIGURE_MESSAGE_BUFFERS_FOR_QUEUE(1, sizeof(uint32_t)) + \
         CONFIGURE_MESSAGE_BUFFERS_FOR_QUEUE(1, sizeof(uint32_t))

#define CONFIGURE_RTEMS_INIT_TASKS_TABLE

#define CONFIGURE_INIT
#include <rtems/confdefs.h>

/****************  END OF CONFIGURATION INFORMATION  ****************/

#endif