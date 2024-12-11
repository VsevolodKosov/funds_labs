#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    OK,
    InputError,
    MemoryError,
    OpenFileError
} status_code;

typedef struct {
    int id;
    char name[50];
    char surname[50];
    double salary;
} Employee;

#define EPSILON 1e-10

status_code validate_name(const char *name, size_t length_name) {
    for (size_t i = 0; i < length_name; ++i) {
        if (!((name[i] >= 'A' && name[i] <= 'Z') || (name[i] >= 'a' && name[i] <= 'z'))) {
            return InputError;
        }
    }
    return OK;
}

status_code read_from_file(FILE *input, Employee **array, int *size, int *capacity) {
    *array = (Employee *)malloc(*capacity * sizeof(Employee));
    if (*array == NULL) {
        return MemoryError;
    }

    int check;
    while ((check = fscanf(input, "%d%s%s%lf", &(*array)[*size].id, (*array)[*size].name, (*array)[*size].surname, &(*array)[*size].salary)) == 4) {
    
        if ((*array)[*size].id < 0 || 
            validate_name((*array)[*size].name, strlen((*array)[*size].name)) != OK || 
            validate_name((*array)[*size].surname, strlen((*array)[*size].surname)) != OK || 
            (*array)[*size].salary < 0) {
            free(*array);
            *array = NULL;
            return InputError;
        }

        (*size)++;

        if (*size >= *capacity) {
            *capacity *= 2;
            Employee *temp = (Employee *)realloc(*array, *capacity * sizeof(Employee));
            if (temp == NULL) {
                free(*array);
                *array = NULL;
                return MemoryError;
            }
            *array = temp;
        }
    }

    if (check < 4 && check > 0) {
        return InputError;
    }
    return OK;
}


void write_in_file(FILE *output, const Employee *array, const int size) {
    for (int i = 0; i < size; ++i) {
        fprintf(output, "%d %s %s %.2lf\n", array[i].id, array[i].name, array[i].surname, array[i].salary);
    }
}

int compare_ascending(const void *a, const void *b) {
    const Employee *emp_a = (const Employee *)a;
    const Employee *emp_b = (const Employee *)b;

    double diff = emp_a->salary - emp_b->salary;
    if (diff > EPSILON) return 1;
    if (diff < -EPSILON) return -1;

    int surname = strcmp(emp_a->surname, emp_b->surname);
    if (surname != 0) return surname;

    int name = strcmp(emp_a->name, emp_b->name);
    return name != 0 ? name : emp_a->id - emp_b->id;
}

int compare_descending(const void *a, const void *b) {
    const Employee *emp_a = (const Employee *)a;
    const Employee *emp_b = (const Employee *)b;

    double diff = emp_a->salary - emp_b->salary;
    if (diff > EPSILON) return -1;
    if (diff < -EPSILON) return 1;

    int surname = strcmp(emp_a->surname, emp_b->surname);
    if (surname != 0) return surname;

    int name = strcmp(emp_a->name, emp_b->name);
    return name != 0 ? name : emp_a->id - emp_b->id;
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("InputError: The program expects the path of the input file, the flag, the path of the output file\n");
        return InputError;
    }

    if (strcmp(argv[1], argv[3]) == 0) {
        printf("InputError: The input and output file paths cannot be the same\n");
        return InputError;
    }

    if (!((argv[2][0] == '-' || argv[2][0] == '/') && (argv[2][1] == 'a' || argv[2][1] == 'd'))) {
        printf("InputError: The programm wait a flag on second argument, which start with '-' or '/', followed by 'a' or 'd' without delimiters\n");
        return InputError;
    }

    FILE *input = fopen(argv[1], "r");
    if (input == NULL) {
        printf("OpenFileError: Unable to open input file %s\n", argv[1]);
        return OpenFileError;
    }

    FILE *output = fopen(argv[3], "w");
    if (output == NULL) {
        fclose(input);
        printf("OpenFileError: Unable to open output file %s\n", argv[3]);
        return OpenFileError;
    }

    Employee *input_array = NULL;
    int size = 0, capacity_array = 2;

    status_code result = read_from_file(input, &input_array, &size, &capacity_array);
    if (result != OK) {
        if (result == InputError) {
            printf("InputError: The program could not read the file. The problem is in the file data format\n");
        } else if (result == MemoryError) {
            printf("MemoryError: The program failed to allocate memory\n");
        }
        fclose(input);
        fclose(output);
        return result;
    }

    if (argv[2][1] == 'a') {
        qsort(input_array, size, sizeof(Employee), compare_ascending);
    } else {
        qsort(input_array, size, sizeof(Employee), compare_descending);
    }

    write_in_file(output, input_array, size);
    free(input_array);
    input_array = NULL;
    fclose(input);
    fclose(output);

    return OK;
}


