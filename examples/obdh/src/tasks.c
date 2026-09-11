#include <stdio.h>
#include "obdh.h"

rtems_task Sender(rtems_task_argument arg)
{
   rtems_status_code stat;
   rtems_interval sec = rtems_clock_get_ticks_per_second();
   uint32_t i = 1;
   uint32_t scen = 1;

   while(1) 
   {
      if (i < 13) 
      {
         stat = rtems_message_queue_send(i_tc, &i, sizeof(uint32_t));
         if (i == 1) scen = 1;
         if (i == 4) scen = 1;
         if (i == 7) scen = 3;
         if (i == 10) scen = 3;
      }
      // 
      if (i == 1 || i == 4 || i == 7 || i == 10) stat = rtems_message_queue_send(i_ev, &scen, sizeof(uint32_t));

      i++;
      rtems_task_wake_after(sec);
   }

   rtems_task_delete(RTEMS_SELF);
}

rtems_task DetectorTask(rtems_task_argument arg)
{
   uint32_t in[DETECTOR_IN_CONS_RATE];
   uint32_t out[DETECTOR_OUT_PROD_RATE];
   size_t msg_size;
   rtems_status_code stat;

   while(1) 
   {
      for (uint8_t t = 0; t < DETECTOR_IN_CONS_RATE; t++)
      {
         stat = rtems_message_queue_receive(i_ev, 
                                            &in[t], 
                                            &msg_size, 
                                            RTEMS_DEFAULT_OPTIONS, 
                                            RTEMS_NO_TIMEOUT); 
      }

      if(stat == RTEMS_SUCCESSFUL) printf("Detector Firing\n");
      else printf("Error: %i\n", (int) stat);

      f_scenario(in, out);

      for (uint8_t t = 0; t < DETECTOR_OUT_PROD_RATE; t++)
      {
         rtems_message_queue_send(s_scen, &out[t], sizeof(uint32_t));
      }
   }

   rtems_task_delete(RTEMS_SELF);
}

rtems_task KernelTask(rtems_task_argument arg)
{
   uint32_t in1[KERNEL1_IN1_BUFFER_SIZE];
   uint32_t out1[KERNEL1_OUT1_BUFFER_SIZE];
   uint32_t out2[KERNEL1_OUT2_BUFFER_SIZE];
   uint32_t out3[KERNEL1_OUT3_BUFFER_SIZE];
   uint8_t kernel_in1_consumption_rate = 0;
   uint8_t kernel_out1_production_rate = 0;
   uint8_t kernel_out2_production_rate = 0;
   uint8_t kernel_out3_production_rate = 0;
   uint32_t scen;
   size_t msg_size;
   rtems_status_code stat;
   void (*f) (const uint32_t*, uint32_t*, uint32_t*, uint32_t*);

   while(1) 
   {
      stat = rtems_message_queue_receive(s_scen, 
                                         &scen, 
                                         &msg_size, 
                                         RTEMS_DEFAULT_OPTIONS, 
                                         RTEMS_NO_TIMEOUT);

      printf("Kernel Firing! Scenario: %u\n", scen);

      switch(scen)
      {
         case 1: 
            kernel_in1_consumption_rate = SCEN1_KERNEL_IN1_CONS_RATE;
            kernel_out1_production_rate = SCEN1_KERNEL_OUT1_PROD_RATE;
            kernel_out2_production_rate = SCEN1_KERNEL_OUT2_PROD_RATE;
            kernel_out3_production_rate = SCEN1_KERNEL_OUT3_PROD_RATE;
            f = &f_dispatchAllTC;
            break;
         case 2: 
            kernel_in1_consumption_rate = SCEN2_KERNEL_IN1_CONS_RATE;
            kernel_out1_production_rate = SCEN2_KERNEL_OUT1_PROD_RATE;
            kernel_out2_production_rate = SCEN2_KERNEL_OUT2_PROD_RATE;
            kernel_out3_production_rate = SCEN2_KERNEL_OUT3_PROD_RATE;
            f = &f_dispatchTwoTC;
            break;
         case 3: 
            kernel_in1_consumption_rate = SCEN3_KERNEL_IN1_CONS_RATE;
            kernel_out1_production_rate = SCEN3_KERNEL_OUT1_PROD_RATE;
            kernel_out2_production_rate = SCEN3_KERNEL_OUT2_PROD_RATE;
            kernel_out3_production_rate = SCEN3_KERNEL_OUT3_PROD_RATE;
            f = &f_dispatchOneTC;
            break;
         default:
            break;
      }

      for (uint8_t t = 0; t < kernel_in1_consumption_rate; t++)
      {
         stat = rtems_message_queue_receive(i_tc, 
                                            &in1[t], 
                                            &msg_size, 
                                            RTEMS_DEFAULT_OPTIONS, 
                                            RTEMS_NO_TIMEOUT);
      }

      f(in1, out1, out2, out3);

      for (uint8_t t = 0; t < kernel_out1_production_rate; t++)
      {
         rtems_message_queue_send(s_a1, &out1[t], sizeof(uint32_t));
      }

      for (uint8_t t = 0; t < kernel_out2_production_rate; t++)
      {
         rtems_message_queue_send(s_a2, &out2[t], sizeof(uint32_t));
      }

      for (uint8_t t = 0; t < kernel_out3_production_rate; t++)
      {
         rtems_message_queue_send(s_a3, &out3[t], sizeof(uint32_t));
      }
   }

   rtems_task_delete(RTEMS_SELF);
}

rtems_task Actor1Task(rtems_task_argument arg)
{
   size_t msg_size;
   uint32_t in1[ACTOR1_IN1_CONSUMPT_RATE];
   uint32_t out1[ACTOR1_OUT1_PRODUCT_RATE];
   rtems_status_code stat;

   while(1) 
   {
      for (uint8_t t = 0; t < ACTOR1_IN1_CONSUMPT_RATE; t++)
      {
         stat = rtems_message_queue_receive(s_a1, 
                                            &in1[t], 
                                            &msg_size, 
                                            RTEMS_DEFAULT_OPTIONS, 
                                            RTEMS_NO_TIMEOUT); 
      }

      if(stat == RTEMS_SUCCESSFUL) printf("Actor 1 Firing\n");
      else printf("Error: %i\n", (int) stat);

      f_times1(in1, out1);

      for (uint8_t t = 0; t < ACTOR1_OUT1_PRODUCT_RATE; t++)
      {
         rtems_message_queue_send(o_a1, &out1[t], sizeof(uint32_t));
      }
   }

   rtems_task_delete(RTEMS_SELF);
}

rtems_task Actor2Task(rtems_task_argument arg)
{
   size_t msg_size;
   uint32_t in1[ACTOR2_IN1_CONSUMPT_RATE];
   uint32_t out1[ACTOR2_OUT1_PRODUCT_RATE];
   rtems_status_code stat;

   while(1) 
   {
      for (uint8_t t = 0; t < ACTOR2_IN1_CONSUMPT_RATE; t++)
      {
         stat = rtems_message_queue_receive(s_a2, 
                                            &in1[t], 
                                            &msg_size, 
                                            RTEMS_DEFAULT_OPTIONS, 
                                            RTEMS_NO_TIMEOUT); 
      }

      if(stat == RTEMS_SUCCESSFUL) printf("Actor 2 Firing\n");
      else printf("Error: %i\n", (int) stat);

      f_times2(in1, out1);

      for (uint8_t t = 0; t < ACTOR2_OUT1_PRODUCT_RATE; t++)
      {
         rtems_message_queue_send(o_a2, &out1[t], sizeof(uint32_t));
      }
   }

   rtems_task_delete(RTEMS_SELF);
}

rtems_task Actor3Task(rtems_task_argument arg)
{
   size_t msg_size;
   uint32_t in1[ACTOR3_IN1_CONSUMPT_RATE];
   uint32_t out1[ACTOR3_OUT1_PRODUCT_RATE];
   rtems_status_code stat;

   while(1) 
   {
      for (uint8_t t = 0; t < ACTOR3_IN1_CONSUMPT_RATE; t++)
      {
         stat = rtems_message_queue_receive(s_a3, 
                                            &in1[t], 
                                            &msg_size, 
                                            RTEMS_DEFAULT_OPTIONS, 
                                            RTEMS_NO_TIMEOUT); 
      }

      if(stat == RTEMS_SUCCESSFUL) printf("Actor 3 Firing\n");
      else printf("Error: %i\n", (int) stat);

      f_times3(in1, out1);

      for (uint8_t t = 0; t < ACTOR3_OUT1_PRODUCT_RATE; t++)
      {
         rtems_message_queue_send(o_a3, &out1[t], sizeof(uint32_t));
      }
   }

   rtems_task_delete(RTEMS_SELF);
}

rtems_task Reader1(rtems_task_argument arg)
{
   uint32_t msg;
   size_t msg_size;
   rtems_status_code stat;

   while(1) 
   {
      stat = rtems_message_queue_receive(o_a1, 
                                         &msg, 
                                         &msg_size, 
                                         RTEMS_DEFAULT_OPTIONS, 
                                         RTEMS_NO_TIMEOUT); 

      if(stat == RTEMS_SUCCESSFUL) printf("Output1 Token: %i\n", (int) msg);
      else printf("Error: %i\n", (int) stat);
   }

   rtems_task_delete(RTEMS_SELF);
}

rtems_task Reader2(rtems_task_argument arg)
{
   uint32_t msg;
   size_t msg_size;
   rtems_status_code stat;

   while(1) 
   {
      stat = rtems_message_queue_receive(o_a2, 
                                         &msg, 
                                         &msg_size, 
                                         RTEMS_DEFAULT_OPTIONS, 
                                         RTEMS_NO_TIMEOUT); 

      if(stat == RTEMS_SUCCESSFUL) printf("Output2 Token: %i\n", (int) msg);
      else printf("Error: %i\n", (int) stat);
   }

   rtems_task_delete(RTEMS_SELF);
}

rtems_task Reader3(rtems_task_argument arg)
{
   uint32_t msg;
   size_t msg_size;
   rtems_status_code stat;

   while(1) 
   {
      stat = rtems_message_queue_receive(o_a3, 
                                         &msg, 
                                         &msg_size, 
                                         RTEMS_DEFAULT_OPTIONS, 
                                         RTEMS_NO_TIMEOUT); 

      if(stat == RTEMS_SUCCESSFUL) printf("Output3 Token: %i\n", (int) msg);
      else printf("Error: %i\n", (int) stat);
   }

   rtems_task_delete(RTEMS_SELF);
}