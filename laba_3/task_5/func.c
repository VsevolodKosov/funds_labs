#include "func.h"

void print_menu()
{
    puts("____________________________");
    puts("Select an action:");
    puts("1) Search by ID;\n2) Search by surname/name/group;\n3) Sort by ID;\n4) Sort by surname;");
    puts("5) Sort by name;\n6) Sort by group;\n7) More average to trace;\n8) Student to trace;");
    puts("9) Copy input file to trace;\n0) End dialog;");
    puts("____________________________\n");
    printf(">>> ");
}

void free_buf()
{
    while (getchar() != '\n')
        ;
}

status_code student_init(Student *student)
{
    if (!student)
        return MemoryError;
    student->group[0] = '\0';
    student->name[0] = '\0';
    student->surname[0] = '\0';
    student->id = 0;
    student->marks = (unsigned char *)malloc(5 * sizeof(unsigned char));
    if (!student->marks)
        return MemoryError;
    return OK;
}

status_code string_to_ull(const char *str, unsigned long long *result)
{
    char *endinp;
    if (str[0] == '-')
        return InputError;
    *result = strtoull(str, &endinp, 10);
    if (*result == ULLONG_MAX)
        return InputError;
    if (*endinp != '\0')
        return InputError;
    return OK;
}

status_code validate_name(const char *str)
{
    size_t len = strlen(str), i;
    if (!len)
        return InputError;
    for (i = 0; i < len; ++i)
    {
        if (!isalpha(str[i]))
            return InputError;
    }
    return OK;
}

void delete_student_arr(Student *arr, size_t size)
{
    if (!arr)
        return;
    size_t i;
    for (i = 0; i < size; ++i)
    {
        free(arr[i].marks);
        arr[i].marks = NULL;
    }
    free(arr);
}

void student_file_print(const Student *student, FILE *output)
{
    size_t sum = 0, i;
    for (i = 0; i < 5; ++i)
        sum += student->marks[i];
    fputs("_______________________________________________\n", output);
    fprintf(output, "Surname: %s;\n", student->surname);
    fprintf(output, "Name: %s;\n", student->name);
    fprintf(output, "Group: %s;\n", student->group);
    fprintf(output, "Avg marks: %.3lf;\n", (double)sum / 5.);
    fputs("_______________________________________________\n", output);
}

void student_print(const Student *student)
{
    puts("_______________________________________________\n");
    printf("ID: %llu;\n", student->id);
    printf("Surname: %s;\n", student->surname);
    printf("Name: %s;\n", student->name);
    printf("Group: %s;\n", student->group);
    printf("Marks: %hhu %hhu %hhu %hhu %hhu;\n", student->marks[0], student->marks[1], student->marks[2], student->marks[3], student->marks[4]);
    puts("_______________________________________________\n");
}

status_code list_file_scan(Student **student_arr, FILE *file, size_t *size, double *average)
{
    size_t  idx = 0, i, capacity = 2, sum = 0;
    double cur_average = 0;
    char surname[BUFF_SIZE], name[BUFF_SIZE], group[BUFF_SIZE], _id[BUFF_SIZE];
    unsigned char marks[5];
    ull id;
    char non_unique_id;
    Student *for_realloc;

    if (!student_arr || !file || !size || !average)
        return MemoryError;

    *average = 0;

    *student_arr = (Student *)malloc(sizeof(Student) * capacity);
    if (!student_arr)
        return MemoryError;

    while (1)
    {
        non_unique_id = 0;
        if (fscanf(file, "ID: %[^;]255s", _id) != 1)
            break;
        getc(file);
        getc(file);
        if (fscanf(file, "Surname: %[^;]255s", surname) != 1)
            break;
        getc(file);
        getc(file);
        if (fscanf(file, "Name: %[^;]255s", name) != 1)
            break;
        getc(file);
        getc(file);
        if (fscanf(file, "Group: %[^;]255s", group) != 1)
            break;
        getc(file);
        getc(file);
        if (fscanf(file, "Marks: %hhu %hhu %hhu %hhu %hhu;\n", &marks[0], &marks[1], &marks[2], &marks[3], &marks[4]) != 5)
            break;
        for (i = 0; i < 5; ++i)
        {
            if (marks[i] < 2 || marks[i] > 5)
            {
                non_unique_id = '1';
                break;
            }
        }
        if (non_unique_id)
            continue;
        if (string_to_ull(_id, &id))
            continue;
        for (i = 0; i < idx; ++i)
        {
            if ((*student_arr)[i].id == id)
            {
                non_unique_id = '1';
                break;
            }
        }
        if (non_unique_id)
            continue;
        if (validate_name(name) || validate_name(surname))
            continue;

        if (idx == capacity)
        {
            capacity *= 2;
            for_realloc = (Student *)realloc(*student_arr, capacity * sizeof(Student));
            if (!for_realloc)
            {
                delete_student_arr(*student_arr, idx);
                *student_arr = NULL;
                return MemoryError;
            }
            *student_arr = for_realloc;
        }
        if (student_init(&(*student_arr)[idx]) == MemoryError)
        {
            delete_student_arr(*student_arr, idx);
            *student_arr = NULL;
            return MemoryError;
        }
        strcpy((*student_arr)[idx].group, group);
        strcpy((*student_arr)[idx].surname, surname);
        strcpy((*student_arr)[idx].name, name);
        (*student_arr)[idx].id = id;
        sum = 0;
        for (i = 0; i < 5; ++i)
        {
            (*student_arr)[idx].marks[i] = marks[i];
            sum += marks[i];
        }
        idx++;
        cur_average += (double)sum / 5.;
    }
    *average = cur_average / idx;
    *size = idx;
    return OK;
}

status_code id_search(Student *student_arr, size_t size, ull id, Student **found)
{
    size_t i;
    if (!student_arr || !found)
        return MemoryError;

    for (i = 0; i < size; ++i)
    {
        if (student_arr[i].id == id)
        {
            *found = &student_arr[i];
            return OK;
        }
    }
    return Missing;
}

status_code surname_or_name_search(Student *student_arr, size_t size, const char *key, Student ***found_arr, size_t *found_size, char mod)
{
    size_t i = 0, capacity = 2;
    Student **for_realloc = NULL;
    if (!student_arr || !key || !found_arr)
        return MemoryError;

    *found_size = 0;
    *found_arr = (Student **)malloc(sizeof(Student *) * capacity);
    if (!found_arr)
        return MemoryError;

    for (i = 0; i < size; ++i)
    {
        if ((!strcmp(student_arr[i].surname, key) && mod == 's') ||
            (!strcmp(student_arr[i].name, key) && mod == 'n') ||
            (!strcmp(student_arr[i].group, key) && mod == 'g'))
        {
            if (*found_size == capacity)
            {
                capacity *= 2;
                for_realloc = (Student **)realloc(*found_arr, sizeof(Student *) * capacity);
                if (!for_realloc)
                {
                    free(*found_arr);
                    return MemoryError;
                }
                *found_arr = for_realloc;
            }
            (*found_arr)[*found_size] = &student_arr[i];
            (*found_size)++;
        }
    }
    if (*found_size == 0)
    {
        return Missing;
    }
    return OK;
}

status_code avg_search_print_to_trace_file(const Student *student_arr, size_t size, double avg, FILE *output)
{
    size_t i = 0, marks_sum, j;
    if (!student_arr || !output)
        return MemoryError;

    for (i = 0; i < size; ++i)
    {
        marks_sum = 0;
        for (j = 0; j < 5; ++j)
        {
            marks_sum += student_arr[i].marks[j];
        }
        if (((double)marks_sum / 5. - avg) <= EPS)
            continue;

        fprintf(output, "%s %s\n", student_arr[i].surname, student_arr[i].name);
    }
    return OK;
}

int id_cmp(const void *a, const void *b)
{
    return ((const Student *)a)->id - ((const Student *)b)->id;
}

int surname_cmp(const void *a, const void *b)
{
    return strcmp(((const Student *)a)->surname, ((const Student *)b)->surname);
}

int name_cmp(const void *a, const void *b)
{
    return strcmp(((const Student *)a)->name, ((const Student *)b)->name);
}

int group_cmp(const void *a, const void *b)
{
    return strcmp(((const Student *)a)->group, ((const Student *)b)->group);
}

status_code copy_sorted_to_trace(const Student *sorted_arr, size_t size, const char *trace_filename)
{
    FILE *output = fopen(trace_filename, "w");
    if (!output)
        return MemoryError;

    for (size_t i = 0; i < size; ++i)
    {
        fprintf(output, "ID: %llu;\n", sorted_arr[i].id);
        fprintf(output, "Surname: %s;\n", sorted_arr[i].surname);
        fprintf(output, "Name: %s;\n", sorted_arr[i].name);
        fprintf(output, "Group: %s;\n", sorted_arr[i].group);
        fprintf(output, "Marks: %hhu %hhu %hhu %hhu %hhu;\n\n",
                sorted_arr[i].marks[0],
                sorted_arr[i].marks[1],
                sorted_arr[i].marks[2],
                sorted_arr[i].marks[3],
                sorted_arr[i].marks[4]);
    }

    fclose(output);
    return OK;
}