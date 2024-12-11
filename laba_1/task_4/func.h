#ifndef FUNC_H
#define FUNC_H
#include "standard_libs.h"
#include "status_code.h"
#include <ctype.h>

status_code remove_digits(FILE *input, FILE *output);
status_code count_latin_letters(FILE *input, FILE *output);
status_code count_non_alphanumeric(FILE *input, FILE *output);
status_code replace_with_ascii(FILE *input, FILE *output);
status_code generate_output_filename(const char *input_filename, char **output_filename);

#endif