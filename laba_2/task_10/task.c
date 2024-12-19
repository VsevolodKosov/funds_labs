#include "func.h"

int main()
{
    double *coefs = NULL;
    int i, degree, a;

    degree = 2;
    a = 2;

    switch (calculate_coefs_polinom_with_shift(a, &coefs, degree, 1., 2., 3.))
    {
    case MemoryError:
        printf("Memory error\n");
        return MemoryError;

    case InputError:
        printf("Error degree < 0\n");
        return InputError;

    case OK:
        puts("Coefs of g(x-a):");
        for (i = 0; i <= degree; i++)
        {
            printf("g_%d = %lf\n", i, coefs[i]);
        }
        free(coefs);
    }
}