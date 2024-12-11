#include "func.h"
#include "status_code.h"

status_code string_to_double(const char *str, double *result) {
    if (str == NULL || result == NULL) {
        return PointerToNullError;
    }

    char *endptr;
    *result = strtod(str, &endptr);
    if (endptr == str) {
        return InputError;
    }

    if (*result == HUGE_VAL || *result == -HUGE_VAL) {
        return OverFlowError;
    }

    return OK;
}

status_code string_to_int(const char *str, int *result) {
    if (str == NULL || result == NULL) {
        return PointerToNullError;
    }

    char *endinp;
    // strtol преобразует строку в long, но мы будем проверять, влезает ли результат в int
    long long_value = strtol(str, &endinp, 10);
    
    // Проверка на корректность ввода: если после числа есть дополнительные символы
    if (*endinp != '\0') {
        return InputError;
    }

    // Проверка на переполнение или выход за пределы диапазона int
    if (long_value > INT_MAX || long_value < INT_MIN) {
        return OverFlowError;
    }

    // Преобразуем в int, так как переполнение не произошло
    *result = (int)long_value;

    return OK;
}

void solve_quadratic(double coeff_1, double coeff_2, double coeff_3, double epsilon, char *result) {
    // Проверка на нулевые коэффициенты (деление на 0)
    if (fabs(coeff_1) < epsilon) {
        sprintf(result, "InvalidCoefficientsError: coeff_1 is too small\n");
        return;
    }

    // Дискриминант уравнения
    double D = coeff_2 * coeff_2 - 4 * coeff_1 * coeff_3;

    // Проверка дискриминанта
    if (D > epsilon) {
        // Два различных корня
        double sqrt_D = sqrt(D);
        double x1 = (-coeff_2 + sqrt_D) / (2 * coeff_1);
        double x2 = (-coeff_2 - sqrt_D) / (2 * coeff_1);
        sprintf(result, "x1 = %.6f, x2 = %.6f", x1, x2);
    } else if (D == 0) {
        // Один корень (дискриминант равен нулю)
        double x1 = -coeff_2 / (2 * coeff_1);
        sprintf(result, "x = %.6f", x1);
    } else {
        // Нет корней (дискриминант отрицателен)
        sprintf(result, "No real roots");
    }
}


int is_unique(double arr[3], double unique_permutations[][3], int num_permutations) {
    for (int i = 0; i < num_permutations; i++) {
        if (arr[0] == unique_permutations[i][0] && 
            arr[1] == unique_permutations[i][1] && 
            arr[2] == unique_permutations[i][2]) {
            return 0; // Если перестановка уже существует, вернуть 0
        }
    }
    return 1; // Если уникальная, вернуть 1
}

void permut_quadratic(double coeff_1, double coeff_2, double coeff_3, double epsilon, char *result) {
    double permutations[6][3] = {
        {coeff_1, coeff_2, coeff_3},
        {coeff_1, coeff_3, coeff_2},
        {coeff_2, coeff_1, coeff_3},
        {coeff_2, coeff_3, coeff_1},
        {coeff_3, coeff_1, coeff_2},
        {coeff_3, coeff_2, coeff_1}
    };

    double unique_permutations[6][3]; // Массив для уникальных перестановок
    int num_permutations = 0; // Счётчик уникальных перестановок

    // Перебор всех перестановок
    for (int i = 0; i < 6; i++) {
        // Проверка на уникальность
        if (is_unique(permutations[i], unique_permutations, num_permutations)) {
            solve_quadratic(permutations[i][0], permutations[i][1], permutations[i][2], epsilon, result);
            printf("Permutation (%.6f, %.6f, %.6f): %s\n", permutations[i][0], permutations[i][1], permutations[i][2], result);

            // Добавляем перестановку в список уникальных
            memcpy(unique_permutations[num_permutations], permutations[i], sizeof(double) * 3);
            num_permutations++;
        }
    }
}

int check_right_triangle(double a, double b, double c, double epsilon) {
    // Для теоремы Пифагора: a^2 + b^2 = c^2
    double diff1 = fabs(a * a + b * b - c * c);
    double diff2 = fabs(a * a + c * c - b * b);
    double diff3 = fabs(b * b + c * c - a * a);

    if (diff1 <= epsilon || diff2 <= epsilon || diff3 <= epsilon) {
        return 1;
    }

    return -1;  // Если ни одно условие не выполняется, это не прямоугольный треугольник
}
