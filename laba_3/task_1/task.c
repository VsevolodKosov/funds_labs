#include <stdio.h>
#include <limits.h>

#define LENGTH 33

typedef enum {
    InputError,
    OK
} status_code;

int sum(int a, int b) {
    while (b != 0) {
        int temp = a ^ b;
        b = (a & b) << 1;
        a = temp;
    }
    return a;
}

int negative(int a) {
    return sum(~a, 1);
}

int substraction(int a, int b) {
    return sum(a, negative(b));
}

status_code conversion_from_decimal(int num, int r, int *count, char (*result)[LENGTH], char *base) {
    int digit;
    if (r < 1 || r > 5){
        return InputError;
    }
    
    int mask = substraction((1 << r), 1);

    do {
        digit = num & mask;
        (*result)[*count] = base[digit];
        *count = sum(*count, 1);
        num >>= r;
    } while (num > 0);
    return OK;
}

void print_number(char* number, int count, int flag_negative) {
    if (flag_negative) { printf("-"); }
    
    int i = 0;
    while (i < count) {
        printf("%c", number[substraction(count, sum(i, 1))]);
        i = sum(i, 1);
    }
    printf("\n");
}

int main() {
    char* base = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int num = 5;
    int r = 1;
    char result[LENGTH];
    int count = 0;

    int flag_negative = 0;
    if (num < 0) {
        flag_negative = 1;  
        num = negative(num); 
    }
    
    if (conversion_from_decimal(num, r, &count, &result, base) == InputError){
        printf("InputError: r must be in range [1, 5]\n");
        return InputError;
    }
    printf("Result: ");
    print_number(result, count, flag_negative);

    return OK;
}
