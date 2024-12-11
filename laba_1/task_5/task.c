#include "func.h"

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <epsilon> <x>\n", argv[0]);
        return 1;
    }

    double epsilon;
    double x;
    double result_a, result_b, result_c, result_d;
    status_code status;

    // Преобразование строки в число для epsilon
    status = string_to_double(argv[1], &epsilon);
    if (status != OK) {
        if (status == InputError) {
            printf("InputError: Invalid value for epsilon\n");
        } else if (status == OverFlowError) {  // Правильная конструкция else if
            printf("OverFlowError: Invalid value for epsilon\n");
        }
        return status;
    }   

    // Преобразование строки в число для x
    status = string_to_double(argv[2], &x);
    if (status != OK) {
        if (status == InputError) {
            printf("InputError: Invalid value for x\n");
        } else if (status == OverFlowError) {  // Правильная конструкция else if
            printf("OverFlowError: Invalid value for x\n");
        }
        return status;
    }

    // Вычисление сумм для всех рядов
    sum_a(x, epsilon, &result_a);
    sum_b(x, epsilon, &result_b);
    sum_c(x, epsilon, &result_c);
    sum_d(x, epsilon, &result_d);
 

    // Вывод результатов
    printf("Sum_a: %f\n", result_a);
    printf("Sum_b: %f\n", result_b);
    printf("Sum_c: %f\n", result_c);
    printf("Sum_d: %f\n", result_d);

    return 0;
}
