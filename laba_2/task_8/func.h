#ifndef FUNC_H
#define FUNC_H

#include "standard_libs.h"
#include "status_code.h"
#include <ctype.h>
#include <stdarg.h>
#include <math.h>
#include <string.h>


status_code sum_any_base_all_numbers(char **result, int base, int count_numbers, ...);
status_code validate_base(char *number, int base, int len);
void str_reverse(char *str, int len);
void sum_any_base_two_numbers(char *number1_res, char *number2, int base, int *len_res, int len_number);
#endif

