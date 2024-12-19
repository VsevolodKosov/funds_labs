#ifndef FUNC_H
#define FUNC_H

#include "standard_libs.h"
#include "status_code.h"
#include <string.h>
#include <ctype.h>
#include <math.h>


double func1(double x);
double func2(double x);
double func3(double x);
double func4(double x);
double func5(double x);
status_code dichotomy_method(double *res, double left, double right, double eps, double (*f)(double));

#endif 