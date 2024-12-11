#include "func.h"

int main(int argc, char * argv[]) {
    if (argc < 2) {
        printf("InputError: Program expects flag\n");
        return InputError;
    }

    char * flag = argv[1];
    if (!(flag[0] == '-' || flag[0] == '/')) {
        printf("FlagError: Flag must be start with symbol '-' or '/'\n");
        return FlagError;
    }

    switch (flag[1]) {
    case 'r': {
        if (argc != 5) {
            printf("InputError: Program with flag '-r' expects path of file_1, file_2 and output_file\n");
            return InputError;
        }
        FILE * file_1 = fopen(argv[2], "r");
        if (file_1 == NULL) {
            printf("OpenFileError: Program failed to open file_1\n");
            return OpenFileError;
        }

        FILE * file_2 = fopen(argv[3], "r");
        if (file_2 == NULL) {
            fclose(file_1);
            printf("OpenFileError: Program failed to open file_2\n");
            return OpenFileError;
        }

        FILE * output_file = fopen(argv[4], "w");
        if (output_file == NULL) {
            fclose(file_1); fclose(file_2);
            printf("OpenFileError: Program failed to open output_file\n");
            return OpenFileError;
        }

        status_code status = flag_r(file_1, file_2, output_file);
        fclose(file_1); fclose(file_2); fclose(output_file);
        if (status != OK) {
            if (status == MemoryError) {
                printf("MemoryError: Program failed to allocate memory\n");
                return MemoryError;
            }
            if (status == PointerToNullError) {
                printf("PointerToNullError: Error with pointer\n");
                return PointerToNullError;
            }
        }
        break;
    }

    case 'a': {
        if (argc != 4) {
            printf("InputError: Program with flag '-a' expects path of input_file and output_file\n");
            return InputError;
        }

        FILE * input_file = fopen(argv[2], "r");
        if (input_file == NULL) {
            printf("OpenFileError: Program failed to open input_file\n");
            return OpenFileError;
        }

        FILE * output_file = fopen(argv[3], "w");
        if (output_file == NULL) {
            fclose(input_file);
            printf("OpenFileError: Program failed to open output_file\n");
            return OpenFileError;
        }

        status_code status = flag_a(input_file, output_file);
        fclose(input_file); fclose(output_file);
        if (status != OK) {
            if (status == MemoryError) {
                printf("MemoryError: Program failed to allocate memory\n");
                return MemoryError;
            }
            if (status == PointerToNullError) {
                printf("PointerToNullError: Error with pointer\n");
                return PointerToNullError;
            }
        }
        break;
    }

    default:
        printf("FlagError: Unknown flag\n");
        return FlagError;
    }
    return 0;
}
