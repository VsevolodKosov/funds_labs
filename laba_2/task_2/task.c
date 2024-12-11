#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <float.h>
#include <math.h>

typedef enum status_code {
    InputError,
    MemoryError,
    OverFlowError,
    OK
} status_code;

int check_overflow(double *number) {
    if (isnan(*number) || isinf(*number)) {
        return 1;
    }
    return 0;
}

status_code fast_pow(double base, int exponent, double *result) {
    if (exponent < 0) {
        return fast_pow(1.0 / base, -exponent, result);
    }
    if (exponent == 0) {
        *result = 1.0;
        return OK;
    }
    status_code status;
    double half_pow;
    if (exponent % 2 == 0) {
        status = fast_pow(base, exponent / 2, &half_pow);
        if (status != OK) {
            return status;
        }
        *result = half_pow * half_pow;
    } else {
        status = fast_pow(base, exponent - 1, result);
        if (status != OK) {
            return status;
        }
        *result *= base;
    }
    return status;
}

status_code geom_mean(double *result, int count, ...) 
{
    if(count <= 0)
    {
        return InputError;
    }
    *result = 1;
    va_list args;
    va_start(args, count);
    for(int i = 0; i < count; ++i)
    {
        *result *= va_arg(args, double);
        if(check_overflow(result))
        {
            va_end(args);
            return OverFlowError;
        }
    }
    *result = pow(*result, 1. / count);
    va_end(args);
    return OK;
}


int main() {
    double result_geom_mean;
    status_code status_geom_mean = geom_mean(&result_geom_mean, 4, 2.0, 8.0, 32.0, 128.0);
    if (status_geom_mean == OK) {
        printf("Geometric Mean: %lf\n", result_geom_mean);
    } else if (status_geom_mean == InputError) { 
        printf("InputError: Incorrect number of arguments\n");
    } else {
        printf("OverFlowError: Overflow occurred\n");
    }

    double result_pow;
    double base_pow = 4;
    int exponent = -2;
    status_code status_pow = fast_pow(base_pow, exponent, &result_pow);
    if (status_pow == OK) {
        printf("%lf^%d = %lf\n", base_pow, exponent, result_pow);
    } else {
        printf("OverFlowError: Overflow occurred\n");
    }
    return 0;
}
