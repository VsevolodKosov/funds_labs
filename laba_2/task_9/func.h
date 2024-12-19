#ifndef FUNC_H
#define FUNC_H

#include "standard_libs.h"
#include "status_code.h"
#include <ctype.h>
#include <stdarg.h>
#include <math.h>
#include <string.h>
#include <float.h>

#define EPS DBL_EPSILON
status_code has_a_finite_representation(int base, double *res, int *len_ans, int count_nums, ...);
int has_representation(int base, double num);
unsigned long long gcd(unsigned long long a, unsigned long long b);

#endif

