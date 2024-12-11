#include "func.h"

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("InputError: The program expects a flag and a file name\n");
        return InputError;
    }

    if (!((argv[1][0] == '-' || argv[1][0] == '/') && (argv[1][2] == '\0' || argv[1][3] == '\0'))) {
        printf("InputError: Incorrect flag\n");
        return InputError;
    }

    FILE *input = fopen(argv[2], "r");
    if (input == NULL) {
        printf("OpenFileError: Failed to open input file\n");
        return OpenFileError;
    }

    FILE *output = NULL;
    char *outfile_path = NULL;
    int len_flag = strlen(argv[1]);

    if (len_flag == 3) {
        if (argc != 4) {
            fclose(input);
            printf("InputError: With the 'n' flag, the program also expects the name of the output file\n");
            return InputError;
        } else if (argv[1][1] == 'n') {
            outfile_path = (char *)malloc((strlen(argv[3]) + 1) * sizeof(char)); 
            if (outfile_path == NULL) {
                fclose(input);
                printf("MemoryError\n");
                return MemoryError;
            }

            strcpy(outfile_path, argv[3]);  
            output = fopen(outfile_path, "w");
            if (output == NULL) {
                free(outfile_path);  
                fclose(input);
                printf("OpenFileError: Failed to open output file\n");
                return OpenFileError;
            }
        } else {
            fclose(input);
            return InputError;
        }
    } else {
        if (argc != 3) {
            fclose(input);
            return InputError;
        }

        status_code status = generate_output_filename(argv[2], &outfile_path);
        if (status != OK) {
            fclose(input);
            return status;
        }

        output = fopen(outfile_path, "w");
        if (output == NULL) {
            free(outfile_path);
            fclose(input);
            return OpenFileError;
        }
    }


    switch (argv[1][len_flag - 1]) {
    case 'd':
        remove_digits(input, output);
        break;

    case 'i':
        count_latin_letters(input, output);
        break;

    case 's':
        count_non_alphanumeric(input, output);
        break;

    case 'a':
        replace_with_ascii(input, output);
        break;

    default:
        fclose(input);
        fclose(output);
        free(outfile_path);
        printf("FlagError: Unknow flag\n");
        return FlagError;
    }

    printf("The action with the file was completed successfully\n");
    fclose(input);
    fclose(output);
    free(outfile_path);
    outfile_path = NULL;
    return OK;
}