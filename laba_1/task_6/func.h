#ifndef FUNC_H
#define FUNC_H

#include "standard_libs.h"
#include "status_code.h"
#include <math.h>

status_code string_to_double(const char *str, double *result);
double integral_a(double x);
double integral_b(double x);
double integral_c(double x);
double integral_d(double x);
double rectangle_method(int n, double epsilon, double (*function)(double));
double func_integrate(double epsilon, double (*function)(double));

#endif 