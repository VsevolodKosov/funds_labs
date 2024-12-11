#ifndef FUNC_H
#define FUNC_H

#include "standard_libs.h"
#include "status_code.h"

status_code read_string(FILE * input, char ** buffer, int * capacity, char * c, int * idx);
status_code to_lower(char * buffer, int len_buffer);
status_code to_ASCII(char * buffer, int len_buffer, int base);
status_code flag_r(FILE * file_1, FILE * file_2, FILE * output_file);
status_code flag_a(FILE * input_file, FILE * output_file);

#endif