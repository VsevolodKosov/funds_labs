#include "func.h"

status_code string_to_number(const char *str, long *result){
    if (str == NULL || result == NULL){
        return PointerToNullError;
    }

    char *endinp;
    *result = strtol(str, &endinp, 10);
    if (*endinp != '\0'){
        return InputError;
    }

    if (*result == LONG_MAX || *result == LONG_MIN){
        return OverFlowError;
    }

    return OK;
}

status_code natural_nums(const long x, int **result, int *size) {
    if (result == NULL || size == NULL) {
        return PointerToNullError;
    }

    if (x <= 0 || x > 100) {
        return InputError;
    }

    *size = 0;
    for (long i = x; i <= 100; i += x) {
        (*size)++;
    }

    *result = (int *)malloc(sizeof(int) * (*size));
    if (*result == NULL) {
        return MemoryError;
    }

    int idx = 0;
    for (long i = x; i <= 100; i += x) {
        (*result)[idx++] = (int)i;
    }

    return OK;
}


int is_prime(const long x){
    if (x <= 1)
        return 0;
    if (x == 2)
        return 2;
    if (x % 2 == 0)
        return 1;

    for (int i = 3; i * i <= x; i++){
        if (x % i == 0){
            return 1;
        }
    }
    return 2;
}

status_code sum(const long x, long long *result){
    if (result ==  NULL){
        return  PointerToNullError;
    }

    if (x < 0){
        return InputError;
    }
    
    for (long i = 1; i <= x; i++){
        if (LLONG_MAX - i < *result){
            return OverFlowError;
        }
        (*result) += i;
    }

    return OK;
}

status_code fact(const long x, long long *result){
    if (result == NULL){
        return PointerToNullError;
    }

    if (x < 0){
        return InputError;
    }

    *result = 1;

    for (long i = 2; i < x; i++){
        if (LLONG_MAX / i < *result){
            return OverFlowError;
        }

        (*result) *= i;
    }
    return OK;
}

status_code degree_table(const long x){
    if (x < 1 || x > 10){
        return InputError;
    }
    long long num;
    for (int i = 1; i <= 10; i++)
    {
        num = 1;
        printf("| %2d |", i);
        for (int j = 1; j <= x; j++){
            num *= i;
            printf("%10lld ", num);
        }
        printf("\n");
    }
    return OK;
}

status_code split_16(long x, char **result, int *size) {
    if (result == NULL || size == NULL) {
        return PointerToNullError;
    }


    int flag = 0; 
    int capacity = 16;  
    *size = 0;  
    char *resize = NULL;
    *result = malloc(capacity * sizeof(char));
    if (*result == NULL) {
        return MemoryError;
    }

  
    if (x < 0) {
        flag = 1;
        x = -x;
    }

    if (x == 0) {
        (*result)[(*size)++] = '0';
    }

    // Разделяем число на цифры в 16-ричной системе
    while (x > 0) {
        int digit = x % 16;
        (*result)[(*size)++] = (digit < 10) ? (digit + '0') : (digit - 10 + 'A');
        x /= 16;

        // Если размер достиг вместимости, увеличиваем ее
        if (*size == capacity) {
            capacity *= 2;
            resize = realloc(*result, capacity * sizeof(char));
            if (resize == NULL) {
                free(*result);  // Освобождаем память при ошибке realloc
                return MemoryError;
            }
            *result = resize;
        }
    }

    // Если число было отрицательным, добавляем минус
    if (flag) {
        (*result)[(*size)++] = '-';
    }

    // Переворачиваем строку, чтобы цифры шли от старшего разряда к младшему
    for (int i = 0; i < (*size) / 2; i++) {
        char temp = (*result)[i];
        (*result)[i] = (*result)[*size - i - 1];
        (*result)[*size - i - 1] = temp;
    }

    return OK;
}