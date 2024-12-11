#include "func.h"

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


double fast_pow(double base, int exponent) { 
    if (exponent < 0) {
        return 1.0 / fast_pow(base, -exponent); 
    }

    if (exponent == 0) {
        return 1.0;
    }

    double half_pow = fast_pow(base, exponent / 2);  

    if (exponent % 2 == 0) {
        return half_pow * half_pow;  
    } 
    else {
        return half_pow * half_pow * base;  
    }
}

int is_prime(int n) {
    if (n <= 1) return 0;
    for (int i = 2; i * i <= n; ++i) {
        if (n % i == 0) return 0;
    }
    return 1;
}



double sum(int n){
    double sum = 1;

    for (int i = 2; i <= n; i++){
        sum += 1.0 / i;
    }

    return sum;
}

double limit_e(double eps){
    double exponent = 1;
    double current = 0;
    double previous = 0;

    do{
        previous = current;
        exponent *= 2;
        current = fast_pow((1.0 + 1.0 / exponent) , exponent);
    } while (fabs(previous - current) >= eps);

    return current;
}


double sequence_e(double eps) {
    double current = 1.0; 
    double previous = 0.0;
    double factorial = 1.0;
    int n = 1;

    while (fabs(current - previous) >= eps) {
        factorial *= n;  
        previous = current;  
        current += 1.0 / factorial;  
        ++n; 
    }
    return current;
}

double equation_e(double eps){
    double x = 3;
    double f = 1, df;
    while (fabs(f) > eps){
        f = log(x) - 1;
        df = 1.0 / x;
        x = x - f / df;
    }
    return x;
}

double limit_pi(double eps){
    int n = 2;
    double current = 4.0;
    double previous = 0;

    do{
        previous = current;
        current *= (4.0 * n * ( n - 1.0)) / fast_pow(2.0 * n - 1.0, 2);
        n++;
    } while (fabs(previous - current) >= eps);

    return current;
}

double sequence_pi(double eps){
    int n = 1;
    double current = 1.0;
    double previous = 0;

    do{
        previous = current;
        n++;
        current -= 1.0/(2.0 * n - 1.0);
        n++;
        current += 1.0/(2.0 * n - 1.0);
    } while (fabs(previous - current) >= eps);
    
    return current * 4;
}

double equation_pi(double eps){
    double x = 1;
    double f = 1;
    double df;

    while (fabs(f) > eps){
        f = cos(x) + 1;
        df = -sin(x);
        x = x - f / df;
    }

    return x;
}

double limit_ln2(double eps) {
    double n = 1;
    double term;
    double result = 0.0;

    do {
        term = pow(2, 1/n) - 1;
        result = n * term;
        n++;
    } while (fabs(term) >= eps); 

    return result;
}

double sequence_ln2(double eps){
    int n = 1;
    double current = 1.0;
    double previous = 0;

    do{
        previous = current;
        n++;
        current -= 1.0/n;
        n++;
        current += 1.0/n;
    } while (fabs(previous - current) >= eps);

    return current;
}

double equation_ln2(double eps){
    double x = 1;
    double f = 1; 
    double df;

    while (fabs(f) > eps){
        f = exp(x) - 2;
        df = exp(x);
        x = x - f / df;
    }

    return x;
}

double limit_sqrt2(double eps) {
    double current = -0.5;  
    double x_next = 0;  
    double diff = 1.0;  
    
    while (diff >= eps) {
        x_next = current - (fast_pow(current, 2) / 2) + 1;
        diff = fabs(x_next - current);  
        current = x_next;  
    }

    return current;  
}

double sequence_sqrt2(double eps)
{
    int k = 2;
    double current = pow(2.0, 1.0/4.0), previous = 0;
    do
    {
        previous = current;
        ++k;
        current *= pow(2,1.0/pow(2,k));
    } while (fabs(previous - current) >= eps);
    return current;
}


double equation_sqrt2(double eps){
    double x = 1;
    double f = 1;
    double df;

    while (fabs(f) > eps){
        f = x * x - 2;
        df = 2 * x;
        x = x - f / df;
    }

    return x;
}

double limit_y(double eps)
{
    double previous = 0;
    double current = 1;
    int n = 1;

    do{
        previous = current;
        n *= 2;
        current = sum(n) - log(n);
    } while (fabs(previous - current) >= eps);

    return current;
}

double sequence_y(double eps){
    double previous = 0;
    double current = 0.5;
    int k = 2;
    double l = 0;

    do{
        previous = current;
        k++;
        l = sqrt(k);
        if (fmod(l, 1.0) == 0){
            k++;
            l = (int)pow(k, 1.0/2.0);
        }
        current += 1.0/pow((int)l, 2.0) - 1.0/k;
    } while (fabs(previous - current) >= eps);

    return (current - pow(sequence_pi(eps), 2) / 6);
}

double equation_y(double epsilon) {
    double current_iteration = log(2) * 0.5, last_iteration;
    double number = 0.5;
    int p = 2;

    do {
        last_iteration = current_iteration;
        do {
            ++p;
        } while (!is_prime(p));  

        number *= (p - 1.0) / p;
        current_iteration = log(p) * number;

    } while (fabs(last_iteration - current_iteration) >= epsilon);

    return (-log(current_iteration));
}

void print_result(const char *method, double computed) {
    printf("%s: %.12f\n", method, computed);
}








