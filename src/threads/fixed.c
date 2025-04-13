#include "fixed.h"

#define IS_NEGATIVE(N, TYPE) (N >> ((sizeof(TYPE) << 3) - 1))

/* The constants below are for fixed-point numbers using the 17.14 format. */
#define INTEGER_BITS 17
#define POINT_BITS   14
#define F ((fixed)(1 << POINT_BITS))

fixed convert_to_fixed (int n)
{
    // return n * F;
    return n << POINT_BITS;
}

int32_t convert_to_int (fixed x)
{
    return x / F;
}

int32_t convert_to_int_round (fixed x)
{
    // const int32_t bias = IS_NEGATIVE(x, fixed) * F - F / 2;
    const int32_t bias = (IS_NEGATIVE(x, fixed) << POINT_BITS) - (F >> 1);
    return (x + bias) / F;
}

fixed add_fixed (fixed x, fixed y)
{
    return x + y;
}

fixed add_fixed_int (fixed x, int32_t n)
{
    // return x + n * F;
    return x + (n << POINT_BITS);
}

fixed sub_fixed (fixed x, fixed y)
{
    return x - y;
}

fixed sub_fixed_int (fixed x, int32_t n)
{
    // return x - n * F;
    return x - (n << POINT_BITS);
}

fixed mul_fixed (fixed x, fixed y)
{
    return ((int64_t)x) * y / F;
}

fixed mul_fixed_int (fixed x, int32_t n)
{
    return x * n;
}

fixed div_fixed (fixed x, fixed y)
{
    // return ((int64_t)x) * F / y;
    return (((int64_t)x) << POINT_BITS) / y;
}

fixed div_fixed_int (fixed x, int32_t n)
{
    return x / n;
}
