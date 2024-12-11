#ifndef FUNC_H
#define FUNC_H
#include "standard_libs.h"
#include "status_code.h"

status_code string_to_number(const char *str, long *result);
status_code natural_nums(const long x, int **result, int *size);
int is_prime(const long x);
status_code sum(const long x, long long *result);
status_code fact(const long x, long long *result);
status_code degree_table(const long x);
status_code split_16(long x, char **result, int *size);

#endif