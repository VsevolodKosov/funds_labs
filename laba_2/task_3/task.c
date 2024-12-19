#include "func.h"

int main()
{
    found *result, *current;
    status_code status = search_str_in_files("Everything\nremains", 1, &result,  "input.txt");
    int flag = 0;

    if (status == OpenFileError){
        printf("OpenFileError: Program failed to open file\n");
        return OpenFileError;
    }
    if (status == MemoryError){
        printf("MemoryError: Program failed to allocate memory\n");
        return MemoryError;
    }
    if (status == InputError){
        printf("InputError\n");
        return InputError;
    }
    if (status == OK){
        current = result;
            while (current) {
                found *next = current->next;
                flag = 1;
                printf("File: %s, line: %d, word: %d;\n", current->file_name, current->n_line, current->n_char);
                free(current->file_name);
                free(current);
                current = next;
            }
    }
    if (flag == 0){
        printf("Substring not found\n");
    }
    
    return 0;
}