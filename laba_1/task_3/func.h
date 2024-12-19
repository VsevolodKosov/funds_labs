#ifndef FUNC_H
#define FUNC_H

#include "standard_libs.h"
#include <float.h>
#include <math.h>
#include "status_code.h"

status_code string_to_double(const char *str, double *result);
status_code string_to_int(const char *str, int *result);
void solve_quadratic(double coeff_1, double coeff_2, double coeff_3, double epsilon, char *result);
void permut_quadratic(double coeff_1, double coeff_2, double coeff_3, double epsilon, char *result);
int is_unique(double arr[3], double unique_permutations[][3], int num_permutations);
int check_right_triangle(double a, double b, double c, double epsilon);

#endif 