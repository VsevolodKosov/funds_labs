#include "func.h"

int main() {
    char *result = NULL;

    printf("Testing sum_any_base_all_numbers function:\n");

    // Test 1: Base 10, normal numbers
    if (sum_any_base_all_numbers(&result, 10, 3, "123", "456", "789") == OK) {
        printf("Sum of {123, 456, 789} in base 10: %s\n", result);
        free(result);
    } else {
        printf("Test 1 failed.\n");
    }

    // Test 2: Base 16, large numbers
    if (sum_any_base_all_numbers(&result, 16, 2, "1A3F", "2BCD") == OK) {
        printf("Sum of {1A3F, 2BCD} in base 16: %s\n", result);
        free(result);
    } else {
        printf("Test 2 failed.\n");
    }

    // Test 3: Base 2, binary numbers
    if (sum_any_base_all_numbers(&result, 2, 3, "1101", "1011", "111") == OK) {
        printf("Sum of {1101, 1011, 111} in base 2: %s\n", result);
        free(result);
    } else {
        printf("Test 3 failed.\n");
    }


    // Test 4: Test: Base 36, numbers "1Z" and "A2"
    if (sum_any_base_all_numbers(&result, 36, 2, "1Z", "A2") == OK) {
        printf("Sum of {1Z, A2} in base 36: %s\n", result); // Expected: B1
        free(result);
    } else {
        printf("Test 5 failed.\n");
    }

    // Test 5: Input error, invalid characters
    if (sum_any_base_all_numbers(&result, 10, 2, "123", "45X") == OK) {
        printf("Sum of {123, 45X} in base 10: %s\n", result);
        free(result);
    } else {
        printf("Test 5: Invalid input handled correctly.\n");
    }

    return 0;
}