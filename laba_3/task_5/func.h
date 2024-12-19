#ifndef FUNC_H
#define FUNC_H

#include "status_code.h"
#include "standard_libs.h"
#include <ctype.h>
#include <stdarg.h>
#include <math.h>
#include <string.h>
#include <float.h>

#define EPS DBL_EPSILON
#define ull unsigned long long
#define BUFF_SIZE 256

typedef struct Student
{
    ull id;
    char name[BUFF_SIZE];
    char surname[BUFF_SIZE];
    char group[BUFF_SIZE];
    unsigned char *marks;
} Student;

status_code list_file_scan(Student **student, FILE *file, size_t *size, double *average);
void delete_student_arr(Student *arr, size_t size);
status_code surname_or_name_search(Student *student_arr, size_t size, const char *key, Student ***found_arr, size_t *found_size, char mod);
status_code id_search(Student *student_arr, size_t size, ull id, Student **found);
status_code avg_search_print_to_trace_file(const Student *student_arr, size_t size, double avg, FILE *output);
int id_cmp(const void *a, const void *b);
int surname_cmp(const void *a, const void *b);
int name_cmp(const void *a, const void *b);
int group_cmp(const void *a, const void *b);
void free_buf();
void print_menu();
status_code string_to_ull(const char *str, unsigned long long *result);
void student_print(const Student *student);
void student_file_print(const Student *student, FILE *output);
status_code copy_sorted_to_trace(const Student *sorted_arr, size_t size, const char *trace_filename);


#endif

