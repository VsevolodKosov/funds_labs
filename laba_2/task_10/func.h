#ifndef FUNC_H
#define FUNC_H

#include "standard_libs.h"
#include <ctype.h>
#include <stdarg.h>
#include <math.h>
#include <string.h>

typedef enum{
    OK,
    InputError,
    MemoryError,
}status_code;

double calculation_of_polynomial(double *coefs, double a, int max_degree);
status_code calculate_coefs_polinom_with_shift(double a, double **coefs, int degree, ...);

#endif

