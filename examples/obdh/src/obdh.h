#ifndef __SADF_h
#define __SADF_h

#include <bsp.h>

extern rtems_id i_tc;
extern rtems_id i_ev;
extern rtems_id s_scen;
extern rtems_id s_a1;
extern rtems_id s_a2;
extern rtems_id s_a3;
extern rtems_id o_a1;
extern rtems_id o_a2;
extern rtems_id o_a3;

#define DETECTOR_IN_CONS_RATE 1
#define DETECTOR_OUT_PROD_RATE 1

#define SCEN1_KERNEL_IN1_CONS_RATE 3
#define SCEN1_KERNEL_OUT1_PROD_RATE 1
#define SCEN1_KERNEL_OUT2_PROD_RATE 1
#define SCEN1_KERNEL_OUT3_PROD_RATE 1

#define SCEN2_KERNEL_IN1_CONS_RATE 3
#define SCEN2_KERNEL_OUT1_PROD_RATE 1
#define SCEN2_KERNEL_OUT2_PROD_RATE 1
#define SCEN2_KERNEL_OUT3_PROD_RATE 0

#define SCEN3_KERNEL_IN1_CONS_RATE 3
#define SCEN3_KERNEL_OUT1_PROD_RATE 1
#define SCEN3_KERNEL_OUT2_PROD_RATE 0
#define SCEN3_KERNEL_OUT3_PROD_RATE 0

#define KERNEL1_IN1_BUFFER_SIZE 3
#define KERNEL1_OUT1_BUFFER_SIZE 1
#define KERNEL1_OUT2_BUFFER_SIZE 1
#define KERNEL1_OUT3_BUFFER_SIZE 1

#define ACTOR1_IN1_CONSUMPT_RATE 1
#define ACTOR1_OUT1_PRODUCT_RATE 1
#define ACTOR2_IN1_CONSUMPT_RATE 1
#define ACTOR2_OUT1_PRODUCT_RATE 1
#define ACTOR3_IN1_CONSUMPT_RATE 1
#define ACTOR3_OUT1_PRODUCT_RATE 1

void f_dispatchAllTC(const uint32_t *in1, uint32_t *out1, uint32_t *out2, uint32_t *out3);
void f_dispatchTwoTC(const uint32_t *in1, uint32_t *out1, uint32_t *out2, uint32_t *out3);
void f_dispatchOneTC(const uint32_t *in1, uint32_t *out1, uint32_t *out2, uint32_t *out3);
void f_times1(const uint32_t *in1, uint32_t *out1);
void f_times2(const uint32_t *in1, uint32_t *out1);
void f_times3(const uint32_t *in1, uint32_t *out1);
void f_scenario(const uint32_t *in1, uint32_t *out1);

#endif