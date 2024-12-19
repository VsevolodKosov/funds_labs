#include "func.h"
#include "status_code.h"

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("InputError: Program expects at least 3 arguments (flag + 2 numbers)\n");
        return InputError;
    }

    
    if (!(argv[1][0] == '-' || argv[1][0] == '/')) {
        printf("InputError: Flag must start with '-' or '/'\n");
        return FlagError;
    }

    if (argv[1][2] != '\0') {
        printf("FlagError: Incorrect flag\n");
        return FlagError;
    }

    switch (argv[1][1]) {
        case 'q': {
            if (argc != 6) {
                printf("InputError: Program expects 5 arguments for quadratic equation (flag + epsilon + 3 coefficients)\n");
                return InputError;
            }

            double epsilon;
            status_code status = string_to_double(argv[2], &epsilon);
            if (status != OK) {
                printf("InputError: Incorrect epsilon\n");
                return InputError;
            }

            if (epsilon <= 0) {
                printf("InputError: Epsilon must be positive\n");
                return InputError;
            }

    
            double coeff_1, coeff_2, coeff_3;
            status = string_to_double(argv[3], &coeff_1);
            if (status != OK) {
                printf("InputError: Incorrect coefficient 1\n");
                return InputError;
            }

            status = string_to_double(argv[4], &coeff_2);
            if (status != OK) {
                printf("InputError: Incorrect coefficient 2\n");
                return InputError;
            }

            status = string_to_double(argv[5], &coeff_3);
            if (status != OK) {
                printf("InputError: Incorrect coefficient 3\n");
                return InputError;
            }

            if (fabs(coeff_1) <= epsilon || fabs(coeff_2) <= epsilon || fabs(coeff_3) <= epsilon) {
                printf("InputError: One of the coefficients is too small\n");
                return InputError;
            }

            char result[256];
            permut_quadratic(coeff_1, coeff_2, coeff_3, epsilon, result);
            break;
        }

        case 'm': {
            if (argc != 4) {
                printf("InputError: Program expects 3 arguments for -m flag (flag + 2 integers)\n");
                return InputError;
            }

            int num1, num2;
            status_code status = string_to_int(argv[2], &num1);
            if (status != OK) {
                printf("InputError: Incorrect first number\n");
                return InputError;
            }

            status = string_to_int(argv[3], &num2);
            if (status != OK) {
                printf("InputError: Incorrect second number\n");
                return InputError;
            }

            if (num2 == 0) {
                printf("DivisionByZero: Cannot divide by zero\n");
                return DivisionByZero;
            }

            if (num1 % num2 == 0) {
                printf("%d is divisible by %d\n", num1, num2);
            } else {
                printf("%d is not divisible by %d\n", num1, num2);
            }
            break;
        }

        case 't': {
            if (argc != 6) {
                printf("InputError: Program expects 5 arguments for triangle check (flag + epsilon + 3 sides)\n");
                return InputError;
            }

            double epsilon;
            status_code status = string_to_double(argv[2], &epsilon);
            if (status == PointerToNullError) {
                printf("PointerToNullError: Epsilon parameter is NULL\n");
                return PointerToNullError;
            }
            if (status != OK) {
                printf("InputError: Incorrect epsilon\n");
                return InputError;
            }

            if (epsilon <= 0) {
                printf("InputError: Epsilon must be positive\n");
                return InputError;
            }

            double side1, side2, side3;
            status = string_to_double(argv[3], &side1);
            if (status == PointerToNullError) {
                printf("PointerToNullError: Side 1 parameter is NULL\n");
                return PointerToNullError;
            }
            if (status != OK) {
                printf("InputError: Incorrect side 1\n");
                return InputError;
            }

            status = string_to_double(argv[4], &side2);
            if (status == PointerToNullError) {
                printf("PointerToNullError: Side 2 parameter is NULL\n");
                return PointerToNullError;
            }
            if (status != OK) {
                printf("InputError: Incorrect side 2\n");
                return InputError;
            }

            status = string_to_double(argv[5], &side3);
            if (status == PointerToNullError) {
                printf("PointerToNullError: Side 3 parameter is NULL\n");
                return PointerToNullError;
            }
            if (status != OK) {
                printf("InputError: Incorrect side 3\n");
                return InputError;
            }

            int res = check_right_triangle(side1, side2, side3, epsilon);
            if (res == 1) {
                printf("The numbers can form a right triangle\n");
            } else {
                printf("The numbers cannot form a right triangle\n");
            }
            break;
        }


        default: {
            printf("FlagError: Incorrect flag\n");
            return FlagError;
        }
    }

    return 0;
}
