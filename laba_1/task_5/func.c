#include "func.h"

status_code string_to_double(const char *str, double *result) {
    if (str == NULL || result == NULL) {
        return PointerToNullError;
    }

    char *endptr;
    *result = strtod(str, &endptr);
    if (endptr == str) {
        return InputError;
    }

    if (*result == HUGE_VAL || *result == -HUGE_VAL) {
        return OverFlowError;
    }

    return OK;
}


status_code sum_a(double x, double eps, double *result)
{
    int n = 0;
    *result = 0;
    double cur = 1;
    while (fabs(cur) >= eps)
    {
        (*result) += cur;
        n++;
        cur *= x / n;
    }
    return OK;
}

status_code sum_b(double x, double eps, double *result)
{
    int n = 0;
    *result = 0;
    double cur = 1;
    while (fabs(cur) >= eps)
    {
        (*result) += cur;
        n++;
        cur *= (-1.0) * x * x / (2 * n * (2 * n - 1.0));
    }
    return OK;
}

status_code sum_c(double x, double eps, double *result)
{
    int n = 0;
    *result = 0;
    double cur = 1;
    while (fabs(cur) >= eps)
    {
        (*result) += cur;
        n++;
        cur *= (x * x * 9.0 * n * n) / (9 * n * (n - 1) + 2);
        if (cur + eps >= 1.0)
        {
            *result = INFINITY;
            return OK;
        }
    }
    return OK;
}

status_code sum_d(double x, double eps, double *result)
{
    int n = 0;
    *result = 0;
    double cur = -1.0 * x * x / 2.0;
    while(fabs(cur) > eps)
    {
        *result += cur;
        ++n;
        cur *= (-1.0 * x * x * (2.0 * n - 1.0)) / (2.0 * n);
    }
    return OK;
}
