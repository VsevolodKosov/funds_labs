#include "func.h"

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Ошибка ввода\n");
        return InputError;
    }

    FILE *input = fopen(argv[1], "r");
    FILE *output = fopen(argv[2], "w");
    if (input == NULL || output == NULL)
    {
        if (input != NULL)
            fclose(input);
        if (output != NULL)
            fclose(output);
        printf("Ошибка открытия файла\n");
        return OpenFileError;
    }

    char *num_random_base = malloc(CAPACITY * sizeof *num_random_base);

    if (num_random_base == NULL)
    {
        printf("Ошибка выделения памяти\n");
        fclose(input);
        fclose(output);
        return MemoryError;
    }

    int base, len_word;
    long long num_base10;

    while (!feof(input))
    {
        if (read_num_from_file(input, num_random_base, &len_word, &base) == InputError)
        {
            free(num_random_base);
            fclose(input);
            fclose(output);
            printf("Ошибка ввода\n");
            return InputError;
        }

        if (len_word > 0)
        {
            if (convert_xbase_to_ll(num_random_base, base, &num_base10) == InputError)
            {
                free(num_random_base);
                fclose(input);
                fclose(output);
                printf("Ошибка ввода\n");
                return InputError;
            }

            fprintf(output, "входное число: %s\n", num_random_base);
            fprintf(output, "минимальное основание: %d\n", base);
            fprintf(output, "число в 10сс: %lld\n", num_base10);
            fprintf(output, "\n");
        }
    }

    free(num_random_base);
    fclose(input);
    fclose(output);
    printf("Программа успешно завершила работу\n");
    return OK;
}