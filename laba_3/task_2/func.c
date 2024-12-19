#include "func.h"

status_code copy_vector(const vector *sourse, vector *dest)
{
    size_t i;
    if (!sourse || !dest)
        return MemoryError;

    dest->n = sourse->n;
    dest->data = (double *)malloc(dest->n * sizeof(double));
    if (!dest->data)
        return MemoryError;

    for (i = 0; i < dest->n; ++i)
    {
        dest->data[i] = sourse->data[i];
    }
    return OK;
}

void delete_vector_arr(vector **arr, size_t size)
{
    size_t i;
    if (!arr || !*arr)
        return;

    for (i = 0; i < size; ++i)
    {
        free((*arr)[i].data);
    }
    free(*arr);
    *arr = NULL;
}

status_code search_longest_vectors(vector **res, size_t *count_res, size_t count_vectors, size_t count_norms, ...)
{
    size_t capacity, size_max_len_vector;
    vector *temp_res, *all_vectors;
    va_list args;
    size_t *max_len_vector;
    vector separator = {.data = NULL, .n = 0};
    if (!res || !count_res || !count_vectors || !count_norms)
        return MemoryError;

    capacity = count_vectors * count_norms + count_vectors;
    temp_res = (vector *)malloc(sizeof(vector) * capacity);
    if (temp_res == NULL)
        return MemoryError;

    all_vectors = (vector *)malloc(sizeof(vector) * count_vectors);
    if (!all_vectors)
    {
        free(temp_res);
        return MemoryError;
    }
    max_len_vector = (size_t *)malloc(sizeof(size_t) * count_vectors);
    if (!max_len_vector)
    {
        free(temp_res);
        free(all_vectors);
        return MemoryError;
    }

    va_start(args, count_norms);

    for (size_t i = 0; i < count_vectors; ++i)
    {
        all_vectors[i] = va_arg(args, vector);
    }
    for (size_t i = 0; i < count_norms; i++)
    {
        norm_t norma = va_arg(args, norm_t);
        void *arg = va_arg(args, void *);
        double norma_res = 0;
        double MAX = -INFINITY;
        size_max_len_vector = 0;
        for (size_t j = 0; j < count_vectors; j++)
        {
            norma_res = norma(&(all_vectors[j]), arg);
            if (norma_res < 0)
            {
                delete_vector_arr(&temp_res, *count_res);
                free(max_len_vector);
                free(all_vectors);
                va_end(args);
                return InputError;
            }
            if (norma_res > MAX)
            {
                size_max_len_vector = 0;
                MAX = norma_res;
                max_len_vector[size_max_len_vector++] = j;
            }
            else if (norma_res == MAX)
            {
                max_len_vector[size_max_len_vector++] = j;
            }
        }
        for (size_t j = 0; j < size_max_len_vector; ++j)
        {
            if (copy_vector(&all_vectors[max_len_vector[j]], &temp_res[(*count_res)++]))
            {
                delete_vector_arr(&temp_res, *count_res);
                free(max_len_vector);
                free(all_vectors);
                va_end(args);
                return InputError;
            }
        }
        temp_res[(*count_res)++] = separator;
    }
    va_end(args);

    free(all_vectors);
    free(max_len_vector);
    *res = temp_res;
    return OK;
}

double spectr_norm(vector *vec, void *args)
{
    double *matrix = (double *)args;
    double res = 0;
    if (!vec || !args)
        return -1;

    for (size_t i = 0; i < vec->n; i++)
    {
        double temp_res = 0;
        for (size_t j = 0; j < vec->n; j++)
        {
            temp_res += vec->data[j] * matrix[i * vec->n + j];
        }
        res += temp_res * vec->data[i];
    }
    if (res < 0)
        return -1;
    return sqrt(res);
}

double inf_norm(vector *vec, void *args)
{
    double res = 0;
    size_t i;
    if (!vec)
        return -1;

    for (i = 0; i < vec->n; ++i)
    {
        res = (fabs(vec->data[i]) > res) ? fabs(vec->data[i]) : res;
    }
    return res;
}

double p_norm(vector *vec, void *args)
{
    double res = 0, p;
    size_t i;
    if (!vec || !args)
        return -1;
    p = *(double *)args;
    if (p < 1)
        return -1;

    for (i = 0; i < vec->n; ++i)
    {
        res += pow(fabs(vec->data[i]), p);
    }
    return pow(res, 1 / p);
}