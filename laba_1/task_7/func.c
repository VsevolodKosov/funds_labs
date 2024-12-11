#include "func.h"

status_code read_string(FILE *input, char **buffer, int *capacity, char *c, int *idx) {
    if (input == NULL || *buffer == NULL || capacity == NULL || c == NULL || idx == NULL) {
        return PointerToNullError;
    }

    *c = fgetc(input);
    while (*c == ' ' || *c == '\t' || *c == '\n') {
        *c = fgetc(input);
    }

    *idx = 0;
    while (*c != ' ' && *c != '\n' && *c != '\t' && *c != EOF) {
        if (*idx >= *capacity) {
            *capacity *= 2;
            char *new_buffer = (char *)realloc(*buffer, *capacity);
            if (new_buffer == NULL) {
                return MemoryError;
            }
            *buffer = new_buffer;
        }
        (*buffer)[*idx] = *c;
        *idx += 1;
        *c = fgetc(input);
    }
    if (*idx >= *capacity) {
        *capacity *= 2;
        char *new_buffer = (char *)realloc(*buffer, *capacity);
        if (new_buffer == NULL) {
            return MemoryError;
        }
        *buffer = new_buffer;
    }
    (*buffer)[*idx] = ' ';
    *idx += 1;
    (*buffer)[*idx] = '\0';

    return OK;
}

status_code to_lower(char * buffer, int len_buffer) {
    if (buffer == NULL) {
        return PointerToNullError;  
    }

    for (int i = 0; i < len_buffer; ++i) {
        if ('A' <= buffer[i] && buffer[i] <= 'Z') {
            buffer[i] += 32;  
        }
    }

    return OK;
}


status_code to_ASCII(char *buffer, int len_buffer, int base) {
    if (buffer == NULL) {
        return PointerToNullError;  
    }

    int index = 0;

    for (int i = 0; i < len_buffer; ++i) {
        int ascii_code = (int)(buffer[i]);

        if (ascii_code == 0) {
            continue;  
        }

        char temp[sizeof(int) * 8];  
        int temp_index = 0;

        while (ascii_code > 0) {
            int remainder = ascii_code % base;
            if (remainder < 10) {
                temp[temp_index++] = '0' + remainder;  
            } else {
                temp[temp_index++] = 'a' + (remainder - 10);  
            }
            ascii_code /= base;
        }

        for (int j = 0; j < temp_index / 2; ++j) {
            char tmp = temp[j];
            temp[j] = temp[temp_index - 1 - j];
            temp[temp_index - 1 - j] = tmp;
        }

        for (int j = 0; j < temp_index; ++j) {
            if (index >= len_buffer - 1) {
                return PointerToNullError;  
            }
            buffer[index++] = temp[j];
        }
    }

    buffer[index] = '\0'; 
    return OK;
}


status_code flag_r(FILE *file_1, FILE *file_2, FILE *output_file) {
    if (file_1 == NULL || file_2 == NULL  || output_file == NULL) {
        return PointerToNullError;
    }

    int capacity_buffer = 2;
    int len_buffer = 0;
    char *buffer = (char *)malloc(capacity_buffer * sizeof(char));
    if (buffer == NULL) {
        return MemoryError;
    }

    char symb_file_1 = 0;
    char symb_file_2 = 0;
    status_code status;
    while (symb_file_1 != EOF || symb_file_2 != EOF) {
        if (symb_file_1 != EOF) {
            status = read_string(file_1, &buffer, &capacity_buffer, &symb_file_1, &len_buffer);
            if (status != OK) {
                free(buffer); buffer = NULL;
                return status;
            }
            fwrite(buffer, sizeof(char), len_buffer, output_file);
        }
        if (symb_file_2 != EOF) {
            status = read_string(file_2, &buffer, &capacity_buffer, &symb_file_2, &len_buffer);
            if (status != OK) {
                free(buffer); buffer = NULL;
                return status;
            }
            fwrite(buffer, sizeof(char), len_buffer, output_file);
        }
    }
    free(buffer); buffer = NULL;
    return OK;
}

status_code flag_a(FILE * input_file, FILE * output_file) {
    if (input_file == NULL || output_file == NULL) {
        return PointerToNullError;
    }

    int capacity_buffer = 2;
    int len_buffer = 0;
    char * buffer = (char *)malloc(capacity_buffer * sizeof(char));
    if (buffer == NULL) {
        return MemoryError;
    }

    int number_of_string = 0;
    char symb_input_file = 0;
    status_code status;
    while (symb_input_file != EOF) {
        status = read_string(input_file, &buffer, &capacity_buffer, &symb_input_file, &len_buffer);
        if (status != OK) {
            free(buffer);
            return  status;  
        }
        number_of_string++;
        
        if (number_of_string % 2 == 0) {
            to_lower(buffer, len_buffer);
        }

        if (number_of_string % 5 == 0) {
            to_ASCII(buffer, len_buffer, 8);
        }

        if (number_of_string % 10 == 0) {
            to_lower(buffer, len_buffer);
            to_ASCII(buffer, len_buffer, 4);
        }

        fwrite(buffer, sizeof(char), len_buffer, output_file);
    }

    free(buffer);
    return OK;
}
