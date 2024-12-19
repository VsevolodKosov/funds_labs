#include "func.h"

int char_to_digit(char c) {
    if (isdigit(c)) {
        return c - '0';
    } else if (isalpha(c)) {
        return toupper(c) - 'A' + 10;
    }
    return -1;  // Неверный символ
}

// Преобразование числа в строку в базе 36
char digit_to_char(int digit) {
    if (digit < 10) {
        return '0' + digit;
    } else {
        return 'A' + (digit - 10);
    }
}

// Функция для переворота строки
void str_reverse(char *str, int len) {
    char temp;
    for (int i = 0; i < len / 2; i++) {
        temp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = temp;
    }
}

// Функция для сложения двух чисел в произвольной базе
void sum_any_base_two_numbers(char *number1_res, char *number2, int base, int *len_res, int len_number) {
    int carry = 0, i, digit1, digit2, sum;
    for (i = 0; i < len_number || i < *len_res || carry; ++i) {
        digit1 = (i < *len_res) ? char_to_digit(number1_res[i]) : 0;
        digit2 = (i < len_number) ? char_to_digit(number2[i]) : 0;
        sum = digit1 + digit2 + carry;
        carry = sum / base;
        sum = sum % base;
        number1_res[i] = digit_to_char(sum);  // Преобразуем обратно в символ
    }
    *len_res = i;
    number1_res[*len_res] = '\0';
}

// Функция для проверки правильности числа в определённой базе
status_code validate_base(char *number, int base, int len) {
    for (int i = 0; i < len; ++i) {
        int digit = char_to_digit(number[i]);
        if (digit == -1 || digit >= base) {
            return InputError;
        }
    }
    return OK;
}

// Основная функция для сложения нескольких чисел в произвольной базе
status_code sum_any_base_all_numbers(char **result, int base, int count_numbers, ...) {
    *result = NULL;
    if (base < 2 || base > 36) {
        return InputError;
    }

    char *ptr_number, *number;
    int capacity, len_num, len_res;

    va_list args;
    va_start(args, count_numbers);

    // Получаем первое число
    ptr_number = va_arg(args, char *);
    len_num = strlen(ptr_number);
    number = (char *)malloc((len_num + 1) * sizeof(char));
    if (!number) {
        va_end(args);
        return MemoryError;
    }
    strcpy(number, ptr_number);
    capacity = len_num * 2 + 1;
    len_res = len_num;
    char *res = (char *)malloc(capacity * sizeof(char));
    if (!res) {
        va_end(args);
        free(number);
        return MemoryError;
    }

    if (validate_base(number, base, len_num) != OK) {
        va_end(args);
        free(number);
        free(res);
        return InputError;
    }

    // Переворачиваем первое число
    str_reverse(number, len_num);
    strcpy(res, number);
    free(number);

    // Обрабатываем остальные числа
    for (int i = 0; i < count_numbers - 1; ++i) {
        ptr_number = va_arg(args, char *);
        len_num = strlen(ptr_number);
        number = (char *)malloc((len_num + 1) * sizeof(char));
        if (!number) {
            va_end(args);
            free(res);
            return MemoryError;
        }
        strcpy(number, ptr_number);

        if (validate_base(number, base, len_num) != OK) {
            va_end(args);
            free(number);
            free(res);
            return InputError;
        }

        // Расширяем память для результата, если необходимо
        if (len_num + 2 > capacity) {
            char *temp_realloc;
            capacity = len_num * 2 + 1;
            temp_realloc = (char *)realloc(res, capacity * sizeof(char));
            if (!temp_realloc) {
                va_end(args);
                free(number);
                free(res);
                return MemoryError;
            }
            res = temp_realloc;
        }

        // Переворачиваем следующее число и складываем
        str_reverse(number, len_num);
        sum_any_base_two_numbers(res, number, base, &len_res, len_num);
        free(number);
    }

    // Переворачиваем результат обратно
    str_reverse(res, len_res);
    *result = res;
    va_end(args);
    return OK;
}