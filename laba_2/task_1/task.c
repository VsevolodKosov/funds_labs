#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef enum status_code {
    OK,
    MemmoryError,
    InputError,
    OverflowError
} status_code;

int string_len(const char* str) {
    int len_str = 0;
    while (*str != '\0') {
        len_str++;
        str++;
    }
    return len_str;
}

status_code reverse_string(const char *str, char **result) {
    int len_str = string_len(str);
    *result = (char *)malloc((len_str + 1) * sizeof(char));
    if (*result == NULL) return MemmoryError;

    for (int i = 0; i < len_str; i++) {
        (*result)[i] = str[len_str - 1 - i]; 
    }
    (*result)[len_str] = '\0'; 
    return OK;
}

status_code up_string(const char *str, char **result) {
    int len_str = string_len(str);
    *result = (char *)malloc((len_str + 1) * sizeof(char));
    if (*result == NULL) return MemmoryError;

    for (int i = 0; i < len_str; i++) {
        if (i % 2 == 1 && str[i] >= 'a' && str[i] <= 'z') {
            (*result)[i] = str[i] - 32;
        } else {
            (*result)[i] = str[i];
        }
    }
    (*result)[len_str] = '\0'; 
    return OK;
}

status_code sort_string(const char *str, char **result) {
    int len = string_len(str);
    *result = (char *)malloc(sizeof(char) * (len + 1));
    if (*result == NULL) {
        return MemmoryError;
    }

    int place = 0;
    for (int i = 0; i < len; ++i) {
        if (str[i] >= '0' && str[i] <= '9') {
            (*result)[place++] = str[i];
        }
    }

    for (int i = 0; i < len; ++i) {
        if ((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z')) {
            (*result)[place++] = str[i];
        }
    }

    for (int i = 0; i < len; ++i) {
        if (!(str[i] >= '0' && str[i] <= '9') &&
            !(str[i] >= 'a' && str[i] <= 'z') &&
            !(str[i] >= 'A' && str[i] <= 'Z')) {
            (*result)[place++] = str[i];
        }
    }

    (*result)[place] = '\0';
    return OK;
}

status_code string_to_unsigned_int(const char *str, unsigned int *result) {
    char *endptr; 
    unsigned long temp_result = strtoul(str, &endptr, 10);

    if (*endptr != '\0') {
        return InputError;
    }

    if (temp_result > UINT_MAX) {
        return OverflowError;
    }

    *result = (unsigned int)temp_result;
    return OK;
}

void concat_string(char * str, char ** result, int * len)
{
    for(int i = 0; str[i] != '\0'; ++i)
    {
        (*result)[(*len)++] = str[i];
    }
    (*result)[(*len)] = '\0';
}

status_code concatenate_randomly(char **strs, int count, char **result, unsigned int seed) 
{
    int total_len = 0;
    srand(seed);
    
    for (int i = 0; i < count; ++i) {
        total_len += string_len(strs[i]);
    }

    *result = (char *)malloc(sizeof(char) * (total_len + 1));
    if (*result == NULL) return MemmoryError;

    int len = 0; 

    for (int i = 0; i < count; i++) {
        int j = rand() % (i + 1);
        char *temp = strs[i];
        strs[i] = strs[j];
        strs[j] = temp;
    }

    for (int i = 0; i < count; ++i) {
        concat_string(strs[i], result, &len);
    }
    (*result)[len] = '\0'; 
    return OK;
}



int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("InputError: There must be two arguments entered - flag and string\n");
        return InputError;
    }
    
    if (argv[1][0] != '-') {
        printf("InputError: the program expects a flag along with symbol '-' after name of execution file\n");
        return InputError;
    }

    switch(argv[1][1]) {
        case 'l':
            printf("String length: %d\n", string_len(argv[2]));
            return OK;
        
        case 'r': {
            char *r_string;
            if (reverse_string(argv[2], &r_string) != OK) {
                printf("MemmoryError: Program could not allocate memory\n");
                return MemmoryError;
            }
            printf("Result: %s\n", r_string);
            free(r_string);
            return OK;
        }

        case 'u': {

            char *u_string;
            if (up_string(argv[2], &u_string) != OK) {
                printf("MemmoryError: Program could not allocate memory\n");
                return MemmoryError;
            }
            printf("Result: %s\n", u_string);
            free(u_string);
            return OK;
        }

        case 'n': {
            char *n_string;
            if (sort_string(argv[2], &n_string) != OK) {
                printf("MemmoryError: Program could not allocate memory\n");
                return MemmoryError;
            }
            printf("Result: %s\n", n_string);
            free(n_string);
            return OK;
        }

        case 'c':
            int count_str = argc - 3;
            if(count_str == 0)
            {
                printf("InputError: For the - c flag, at least one line must be entered after the number\n");
                return InputError;
            }
            unsigned int seed;
            if(string_to_unsigned_int(argv[2], &seed) != OK)
            {
                printf("InputError: The first argument after flag should be a number\n");
                return InputError;
            }
            char * result_c;
            if(concatenate_randomly((argv + 3), count_str, &result_c, seed) != OK)
            {
                printf("MemmoryError: Program could not allocate memory\n");
                return MemmoryError;
            }
            printf("%s\n", result_c);
            free(result_c);
            return OK;

        default:
            printf("InputError: Unknown flag\n");
            return InputError;
    }
}
