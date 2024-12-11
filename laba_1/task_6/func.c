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


double integral_a(double x) {
    if (x == 0) return 1.0; 
    return log(1.0 + x) / x;
}

double integral_b(double x) {
    return exp(-x * x) / 2.0;
}

double integral_c(double x) {
    return log(1.0 / (1.0 - x));
}

double integral_d(double x) {
    return exp(x * log(x));
}

double rectangle_method(int n, double epsilon, double (*function)(double)) {
    double sum = 0.0, interval = 1.0 / n, x, i;

    for (i = epsilon; i < n - epsilon; i++) {
        x = interval * i;
        sum += function(x);
    }
    return sum * interval;
}

double func_integrate(double epsilon, double (*function)(double)) {
    double result = 0.0, prev_result = 1.0;
    int n = 1;

    while (fabs( result - prev_result) >= epsilon) {
        prev_result = result;
        result = rectangle_method(n, epsilon, function);
        n *= 2;
    }

    return result;
}