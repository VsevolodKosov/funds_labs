#ifndef FUNC_H
#define FUNC_H

#include "standard_libs.h"
#include "status_code.h"
#include <ctype.h>
#include <time.h>

#define CAPACITY 10

status_code string_to_int(const char *str, long *result);
void generate_static_array(long array[], long a, long b);
void swap_min_max(long array[]);
status_code generate_dynamic_array(int **array, int size_array);
void generate_sum_array(int *A, int *B, int *C, int size_array);

#endif 