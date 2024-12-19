#ifndef FUNC_H
#define FUNC_H

#include "standard_libs.h"
#include "status_code.h"
#include <ctype.h>
#include <stdarg.h>
#include <math.h>
#include <string.h>

#define CAPACITY 100

typedef struct Point
{
    double x;
    double y;
} point;

int is_convex(int count_corners, ...);
status_code find_polynom(double *res, double x, int n, ...);
status_code is_kaprekar(int count_numbers, char *ans, int base, ...);

#endif 