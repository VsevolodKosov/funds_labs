#ifndef FUNC_H
#define FUNC_H

#include "standard_libs.h"
#include "status_code.h"
#include <math.h>

status_code string_to_double(const char *str, double *result);
status_code sum_a(double x, double eps, double *result);
status_code sum_b(double x, double eps, double *result);
status_code sum_c(double x, double eps, double *result);
status_code sum_d(double x, double eps, double *result);


#endif 