#include "func.h"

double calculation_of_polynomial(double *coefs, double a, int max_degree)
{
    double multiplier = 1, result = 0;
    int i;

    for (i = 0; i <= max_degree; ++i)
    {
        result += multiplier * coefs[i];
        multiplier *= a;
    }
    return result;
}

// По Биному Ньютона:
// g0 = f(a)
// g1 = f`(a)
// g2 = f``(a)/2!
// ...
status_code calculate_coefs_polinom_with_shift(double a, double **coefs, int degree, ...)
{
    if (degree < 0)
        return InputError;

    // Массив начальных коэффициентов
    double *start_coefs = (double *)malloc((degree + 1) * sizeof(double));
    if (!start_coefs)
        return MemoryError;

    // Массив для новых коэффициентов
    double *new_coefs = (double *)malloc((degree + 1) * sizeof(double));
    if (!new_coefs)
    {
        free(start_coefs);
        return MemoryError;
    }

    // Чтение коэффициентов полинома
    va_list args;
    va_start(args, degree);
    for (int i = 0; i <= degree; ++i)
    {
        start_coefs[i] = va_arg(args, double);
    }
    va_end(args);

    // Вычисление коэффициентов для (x - a)
    for (int i = 0; i <= degree; ++i)
    {
        double derivative_value = 0;
        double multiplier = 1;

        for (int j = i; j <= degree; ++j)
        {
            derivative_value += start_coefs[j] * multiplier;
            multiplier *= (j - i); // Производные старших степеней
        }

        // Нормализация коэффициента (деление на i!)
        new_coefs[i] = derivative_value / tgamma(i + 1); // tgamma(i+1) = i!
    }

    free(start_coefs);
    *coefs = new_coefs;
    return OK;
}