#ifndef FUNC_H
#define FUNC_H

#include "standard_libs.h"
#include "status_code.h"

status_code string_to_ll(const char *str, long long *result, int base);
void convert_to_xbase(long long num, int base, char *result);

#endif 