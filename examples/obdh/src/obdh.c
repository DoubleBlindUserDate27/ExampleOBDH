#include "obdh.h"

rtems_id i_tc;
rtems_id i_ev;
rtems_id s_scen;
rtems_id s_a1;
rtems_id s_a2;
rtems_id s_a3;
rtems_id o_a1;
rtems_id o_a2;
rtems_id o_a3;

void f_dispatchAllTC(const uint32_t *in1, uint32_t *out1, uint32_t *out2, uint32_t *out3)
{
   out1[0] = in1[0];
   out2[0] = in1[1];
   out3[0] = in1[2];
}

void f_dispatchTwoTC(const uint32_t *in1, uint32_t *out1, uint32_t *out2, uint32_t *out3)
{
   out1[0] = in1[0];
   out2[0] = in1[1];
}

void f_dispatchOneTC(const uint32_t *in1, uint32_t *out1, uint32_t *out2, uint32_t *out3)
{
   out1[0] = in1[0];
}

void f_times1(const uint32_t *in1, uint32_t *out1)
{
   out1[0] = in1[0] * 1;
}

void f_times2(const uint32_t *in1, uint32_t *out1)
{
   out1[0] = in1[0] * 2;
}

void f_times3(const uint32_t *in1, uint32_t *out1)
{
   out1[0] = in1[0] * 3;
}

void f_scenario(const uint32_t *in1, uint32_t *out1)
{
   if (in1[0] > 0 && in1[0] < 4) out1[0] = in1[0];
   else out1[0] = 1;
}