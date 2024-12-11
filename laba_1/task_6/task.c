#include "func.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <epsilon>\n", argv[0]);
        return 1;
    }

    double epsilon;
    status_code status;
    if ((status = string_to_double(argv[1], &epsilon) != OK)){
        if (status == InputError){
            printf("InputError: Invalid value for epsilon");
            return InputError;
        }
        if (status == OverFlowError){
            printf("OverFlowError: Invalid value for epsilon");
            return OverFlowError;
        }
    }

    // Вычисление интегралов
    double result_a = func_integrate(epsilon, integral_a);
    double result_b = func_integrate(epsilon, integral_b);
    double result_c = func_integrate(epsilon, integral_c);
    double result_d = func_integrate(epsilon, integral_d);

    // Вывод результатов
    printf("Integral a: %.10f\n", result_a);
    printf("Integral b: %.10f\n", result_b);
    printf("Integral c: %.10f\n", result_c);
    printf("Integral d: %.10f\n", result_d);

    return 0;
}