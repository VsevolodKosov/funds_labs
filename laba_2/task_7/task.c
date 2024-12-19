#include "func.h"

int main()
{
    double result;
    status_code status;

    printf("Testing dichotomy method:\n");

    // Test for func1
    status = dichotomy_method(&result, 0, 20, 0.000001, func1);
    if (status == OK)
        printf("Root of func1 in [0, 20] with eps = 0.000001: %.6f\n", result);
    else
        printf("func1: No root found or invalid input.\n");

    // Test for func2
    status = dichotomy_method(&result, 0.1, 2, 0.000001, func2);
    if (status == OK)
        printf("Root of func2 in [0.1, 2] with eps = 0.000001: %.6f\n", result);
    else
        printf("func2: No root found or invalid input.\n");

    // Test for func3
    status = dichotomy_method(&result, -5, 1, 0.000001, func3);
    if (status == OK)
        printf("Root of func3 in [-5, 1] with eps = 0.000001: %.6f\n", result);
    else
        printf("func3: No root found or invalid input.\n");

    // Test for func4
    status = dichotomy_method(&result, -2, 0, 0.000001, func4);
    if (status == OK)
        printf("Root of func4 in [-2, 0] with eps = 0.000001: %.6f\n", result);
    else
        printf("func4: No root found or invalid input.\n");

    // Test for func5
    status = dichotomy_method(&result, 0, 30, 0.000001, func5);
    if (status == OK)
        printf("Root of func5 in [0, 30] with eps = 0.000001: %.6f\n", result);
    else
        printf("func5: No root found or invalid input.\n");

    return 0;
}