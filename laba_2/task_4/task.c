#include "func.h"

int main() {
    printf("\nТест функции is_convex:\n");
    point p1 = {0, 0}, p2 = {2, 0}, p3 = {1, 2}, p4 = {0, 1};
    if (is_convex(4, p1, p2, p3, p4)) {
        printf("Многоугольник выпуклый\n");
    } else {
        printf("Многоугольник не выпуклый\n");
    }

    printf("\nТест функции find_polynom:\n");
    double res;
    status_code status = find_polynom(&res, 2.0, 3, 1.0, -4.0, 3.0, 2.0); 
    if (status == OK) {
        printf("Значение многочлена: %.2f\n", res);
    } else {
        printf("Ошибка вычисления многочлена\n");
    }

    printf("\nТест функции is_kaprekar:\n");
    char results[CAPACITY];
    status = is_kaprekar(3, results, 10, "9", "45", "297");
    if (status == OK) {
        printf("Результаты проверки на числа Капрекара: \n");
        printf("9: %c\n", results[0]);
        printf("45: %c\n", results[1]);
        printf("297: %c\n", results[2]);
    } else {
        printf("Ошибка проверки чисел Капрекара\n");
    }

    return 0;
}
