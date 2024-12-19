#ifndef FUNC_H
#define FUNC_H
#include "standard_libs.h"
#include "status_code.h"
#include <ctype.h>
#include <stdarg.h>

typedef struct Found
{
    char *file_name;
    int n_line;
    int n_char;
    struct Found *next;
} found;

int my_strlen(const char *str);

status_code add_new_found(found **head, char *file_name, int len_filename, int n_line, int n_char);

status_code search_str_in_files(char *substring, int count_files, found **result, ...);

#endif

