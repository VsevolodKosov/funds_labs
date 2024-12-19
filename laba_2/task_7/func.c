#include "func.h"

status_code dichotomy_method(double *res, double left, double right, double eps, double (*f)(double))
{
    if (eps <= 0.)
        return InputError;
    double fl = f(left);
    double mid;

    while (fabs(right - left) >= eps)
    {
        mid = (left + right) / 2;
        if (fl * f(mid) <= 0.)
            right = mid;
        else
            left = mid;
    }
    *res = (right + left) / 2;
    return OK;
}

double func1(double x)
{
    return (x-1)*(x-1);
}

double func2(double x)
{
    return sin(x) - 1 / x;
}

double func3(double x)
{
    return x * x + 10 * x - 4;
}

double func4(double x)
{
    return x + x * x + 3 * x * x * x + 1;
}

double func5(double x)
{
    return sqrt(x) - 4.4;
}