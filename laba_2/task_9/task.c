#include "func.h"

int main()
{
    printf("Testing has_a_finite_representation:\n");

    // Тест 1: База 10, несколько дробей
    {
        double result[10];
        int len_ans = 0;

        if (has_a_finite_representation(10, result, &len_ans, 5, 0.5, 0.25, 0.3333, 0.2, 0.8) == OK)
        {
            printf("Base 10: Finite representations:\n");
            for (int i = 0; i < len_ans; i++)
                printf("  %.15f\n", result[i]);
        }
        else
        {
            printf("Base 10: Error in input.\n");
        }
    }

    // Тест 2: База 2, проверяем двоичные дроби
    {
        double result[10];
        int len_ans = 0;

        if (has_a_finite_representation(2, result, &len_ans, 4, 0.5, 0.25, 0.1, 0.125) == OK)
        {
            printf("Base 2: Finite representations:\n");
            for (int i = 0; i < len_ans; i++)
                printf("  %.15f\n", result[i]);
        }
        else
        {
            printf("Base 2: Error in input.\n");
        }
    }

    // Тест 3: База 16, несколько дробей
    {
        double result[10];
        int len_ans = 0;

        if (has_a_finite_representation(16, result, &len_ans, 4, 0.0625, 0.25, 0.1, 0.3333) == OK)
        {
            printf("Base 16: Finite representations:\n");
            for (int i = 0; i < len_ans; i++)
                printf("  %.15f\n", result[i]);
        }
        else
        {
            printf("Base 16: Error in input.\n");
        }
    }

    // Тест 4: Ошибочные входные данные
    {
        double result[10];
        int len_ans = 0;

        if (has_a_finite_representation(10, result, &len_ans, 3, 1.5, -0.2, 1.0) == OK)
        {
            printf("Base 10: Finite representations:\n");
            for (int i = 0; i < len_ans; i++)
                printf("  %.15f\n", result[i]);
        }
        else
        {
            printf("Base 10: Error in input.\n");
        }
    }

    return 0;
}