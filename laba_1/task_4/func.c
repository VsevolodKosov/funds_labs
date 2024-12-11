#include "func.h"

status_code remove_digits(FILE *input, FILE *output) {
    char ch;
    while ((ch = fgetc(input)) != EOF) {
        if (!isdigit(ch)) {
            fputc(ch, output);
        }
    }
    return OK;
}


status_code count_latin_letters(FILE *input, FILE *output) {
    int count = 0;
    char ch;
    while ((ch = fgetc(input)) != EOF) {
        if (isalpha(ch)) {
            count++;
        }
    }
    fprintf(output, "%d\n", count);
    return OK;
}


status_code count_non_alphanumeric(FILE *input, FILE *output) {
    int count = 0;
    char ch;
    while ((ch = fgetc(input)) != EOF) {
        if (!(isalnum(ch) || ch == ' ')) {
            count++;
        }
    }
    fprintf(output, "%d\n", count);
    return OK;
}


status_code replace_with_ascii(FILE *input, FILE *output) {
    char ch;
    while ((ch = fgetc(input)) != EOF) {
        fprintf(output, "%02X", (unsigned char)ch);
    }
    return OK;
}

status_code generate_output_filename(const char *input_filename, char **output_filename) {
    size_t len = strlen(input_filename) + 6;  
    *output_filename = (char *)malloc(len * sizeof(char));
    if (*output_filename == NULL) {
        return MemoryError;
    }

    snprintf(*output_filename, len, "out_%s", input_filename);
    return OK;
}


