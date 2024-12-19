#ifndef FUNC_H
#define FUNC_H


#include "standard_libs.h"
#include <ctype.h>
#include <stdarg.h>
#include <math.h>
#include <string.h>

typedef enum{
    OK,
    MemoryError,
    InputError
}status_code;


typedef struct Vector
{
    double *data;
    size_t n;
} vector;

typedef double (*norm_t)(vector *, void *);

void delete_vector_arr(vector **arr, size_t size);
double spectr_norm(vector *vec, void *args);
double inf_norm(vector *vec, void *args);
double p_norm(vector *vec, void *args);
status_code search_longest_vectors(vector **res, size_t *count_res, size_t vectors_cnt, size_t count_norms, ...);

#endif

