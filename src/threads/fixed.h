#ifndef THREADS_FIXED_H
#define THREADS_FIXED_H

#include <stdint.h>

typedef int32_t fixed;

fixed convert_to_fixed (int n);
int32_t convert_to_int (fixed x);
int32_t convert_to_int_round (fixed x);
fixed add_fixed (fixed x, fixed y);
fixed add_fixed_int (fixed x, int32_t n);
fixed sub_fixed (fixed x, fixed y);
fixed sub_fixed_int (fixed x, int32_t n);
fixed mul_fixed (fixed x, fixed y);
fixed mul_fixed_int (fixed x, int32_t n);
fixed div_fixed (fixed x, fixed y);
fixed div_fixed_int (fixed x, int32_t n);

#endif /* threads/fixed.h */
