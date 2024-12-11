#ifndef FUNC_H
#define FUNC_H

#include "standard_libs.h"
#include <float.h>
#include <math.h>
#include "status_code.h"

status_code string_to_double(const char *str, double *result);
double fast_pow(double base, int exponent);
double sum(int n);
void print_result(const char *method, double computed);

double limit_e(double eps);
double sequence_e(double eps);
double equation_e(double esp);

double limit_pi(double eps);
double sequence_pi(double eps);
double equation_pi(double esp);

double limit_ln2(double eps);
double sequence_ln2(double eps);
double equation_ln2(double esp);

double limit_sqrt2(double eps);
double sequence_sqrt2(double eps);
double equation_sqrt2(double esp);

double limit_y(double eps);
double sequence_y(double eps);
double equation_y(double esp);

#endif 