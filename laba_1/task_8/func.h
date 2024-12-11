#ifndef FUNC_H
#define FUNC_H

#include "standard_libs.h"
#include "status_code.h"
#include <ctype.h>

#define CAPACITY 70

status_code read_num_from_file(FILE *file, char *word, int *len_word, int *base);
status_code convert_xbase_to_ll(const char *const word, int base, long long *result);

#endif 