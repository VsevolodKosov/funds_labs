#include "func.h"

int main(int argc, char *argv[])
{
    if (argc != 3){
        printf("InputError: Program excepts flag and x\n");
        return InputError;
    }

    if (!((argv[1][0] == '-' || argv[1][0] == '/') && argv[1][2] == '\0')){
        printf("FlagError: Flag must be start with '-' or '/'\n");
        return FlagError;
    }

    long num = 0;
    status_code status_int = string_to_number(argv[2], &num);
    if (status_int == InputError){
        printf("InputError: Argument x is incorrect\n");
        return InputError;
    }

    if (status_int == OverFlowError){
        printf("OverFlowError: Overflow in x\n");
        return OverFlowError;
    }

    switch (argv[1][1]){
    case 'h':
        int *res_h = NULL;
        int size = 0;
        status_code status_h = natural_nums(num, &res_h, &size);
        if (status_h == MemoryError){
            printf("MemoryError: Program failed to allocate memory\n");
            if (res_h != NULL){
                free(res_h);
                res_h = NULL;
            }
            return MemoryError;
        }

        if (status_h == InputError){
            printf("InputError: With flag '-h' x must be a natural number up to one hundred inclusive\n");
            if (res_h != NULL){
                free(res_h);
                res_h = NULL;
            }
            return InputError;
        }

        if (size == 0){
            printf("Doesn't exist\n");
        }

        else{
            printf("Result: ");
            for (int i = 0; i < size; i++){
                printf("%d ", res_h[i]);
            }
            printf("\n");
            free(res_h);
            res_h = NULL;
        }
        break;

    case 'p':
        int res_p = is_prime(num);
        if (res_p == 0){
            printf("Number isn't a prime or composite\n");
        }
        else if (res_p == 1){
            printf("Number is a composite\n");
        }
        else{
            printf("Number is a prime\n");
        }

        break;

    case 'a':
        long long res_a = 0;
        status_code status_a = sum(num, &res_a);
    
        if (status_a == InputError){
            printf("InputError: With flag '-a' x must be a natural number\n");
            return InputError;;
        }

        if (status_a == OverFlowError){
            printf("OverFlowError: OverFlow with x\n");
            return OverFlowError;
        }
        printf("Result: ");
        printf("%lld\n", res_a);

        break;

    case 'f':
        long long res_f = 1;
        status_code status_f = fact(num, &res_f);
        if (status_f == InputError){
            printf("InputError: With flag '-f' x must be not less than zero\n");
            return InputError;
        }
        if (status_f == OverFlowError){
            printf("OverFlowError: Overflow with x\n");
            return OverFlowError;
        }
        printf("Result: ");
        printf("%lld\n", res_f);

        break;

    case 'e':
        if (degree_table(num) == InputError){
            printf("InputError: x must from one to ten\n");
            return InputError;
        }
        break;

    case 's':
        int size_s;
        char *res_s = NULL;
        if (split_16(num, &res_s, &size_s) == MemoryError){
            printf("MemoryError: Program failed to allocate memory\n");
            if (res_s != NULL){
                free(res_s);
                res_s = NULL;
            }
            return MemoryError;
        }
        printf("Result: ");
        for (int i = 0; i < size_s; i++){
            printf("%c ", res_s[i]);
        }
        putchar('\n');
        free(res_s);
        res_s = NULL;
        break;

    default:
        printf("FlagError: Unknown flag\n");
        return FlagError;
    }
    return 0;
}