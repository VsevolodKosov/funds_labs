#include "func.h"
#include "status_code.h"

status_code string_to_double(const char *str, double *result) {
    if (str == NULL || result == NULL) {
        return PointerToNullError;
    }

    char *end;
    *result = strtod(str, &end);
    if (*end != '\0') {
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
    
    long long_value = strtol(str, &endinp, 10);
    
    if (*endinp != '\0') {
        return InputError;
    }

    if (long_value > INT_MAX || long_value < INT_MIN) {
        return OverFlowError;
    }

    *result = (int)long_value;

    return OK;
}

void solve_quadratic(double coeff_1, double coeff_2, double coeff_3, double epsilon, char *result) {
    if (fabs(coeff_1) < epsilon) {
        sprintf(result, "InvalidCoefficientsError: coeff_1 is too small\n");
        return;
    }

    double D = coeff_2 * coeff_2 - 4 * coeff_1 * coeff_3;

    if (D > epsilon) {
        double sqrt_D = sqrt(D);
        double x1 = (-coeff_2 + sqrt_D) / (2 * coeff_1);
        double x2 = (-coeff_2 - sqrt_D) / (2 * coeff_1);
        sprintf(result, "x1 = %.6f, x2 = %.6f", x1, x2);
    } else if (D == 0) {
        double x1 = -coeff_2 / (2 * coeff_1);
        sprintf(result, "x = %.6f", x1);
    } else {
        sprintf(result, "No real roots");
    }
}


int is_unique(double arr[3], double unique_permutations[][3], int num_permutations) {
    for (int i = 0; i < num_permutations; i++) {
        if (arr[0] == unique_permutations[i][0] && 
            arr[1] == unique_permutations[i][1] && 
            arr[2] == unique_permutations[i][2]) {
            return 0; 
        }
    }
    return 1;
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

    double unique_permutations[6][3]; 
    int num_permutations = 0; 

    for (int i = 0; i < 6; i++) {
        if (is_unique(permutations[i], unique_permutations, num_permutations)) {
            solve_quadratic(permutations[i][0], permutations[i][1], permutations[i][2], epsilon, result);
            printf("Permutation (%.6f, %.6f, %.6f): %s\n", permutations[i][0], permutations[i][1], permutations[i][2], result);

            memcpy(unique_permutations[num_permutations], permutations[i], sizeof(double) * 3);
            num_permutations++;
        }
    }
}

int check_right_triangle(double a, double b, double c, double epsilon) {

    double diff1 = fabs(a * a + b * b - c * c);
    double diff2 = fabs(a * a + c * c - b * b);
    double diff3 = fabs(b * b + c * c - a * a);

    if (diff1 <= epsilon || diff2 <= epsilon || diff3 <= epsilon) {
        return 1;
    }

    return -1;  
}
