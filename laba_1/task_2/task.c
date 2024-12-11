#include "func.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <epsilon>\n", argv[0]);
        return InputError;
    }

    double eps;
    status_code status = string_to_double(argv[1], &eps);
    
    if (status == InputError || eps <= 0) {
        printf("InputError: Invalid input for epsilon\n");
        return InputError;
    }
    if (status == OverFlowError) {
        printf("OverFlowError: Invalid input for epsilon\n");
        return InputError;
    }

    
    printf("Results for e:\n");
    double e_limit = limit_e(eps);
    print_result("Limit method", e_limit);

    double e_sequence = sequence_e(eps);
    print_result("Sequence method", e_sequence);

    double e_equation = equation_e(eps);
    print_result("Equation method", e_equation);


    printf("\nResults for pi:\n");
    double pi_limit = limit_pi(eps);
    print_result("Limit method", pi_limit);

    double pi_sequence = sequence_pi(eps);
    print_result("Sequence method", pi_sequence);

    double pi_equation = equation_pi(eps);
    print_result("Equation method", pi_equation);

    printf("\nResults for ln(2):\n");
    double ln2_limit = limit_ln2(eps);
    print_result("Limit method", ln2_limit);

    double ln2_sequence = sequence_ln2(eps);
    print_result("Sequence method", ln2_sequence);

    double ln2_equation = equation_ln2(eps);
    print_result("Equation method", ln2_equation);

    printf("\nResults for sqrt(2):\n");
    double sqrt2_limit = limit_sqrt2(eps);
    print_result("Limit method", sqrt2_limit);

    double sqrt2_sequence = sequence_sqrt2(eps);
    print_result("Sequence method", sqrt2_sequence);

    double sqrt2_equation = equation_sqrt2(eps);
    print_result("Equation method", sqrt2_equation);

    printf("\nResults for y:\n");
    double y_limit = limit_y(eps);
    print_result("Limit method", y_limit);

    double y_sequence = sequence_y(eps);
    print_result("Sequence method", y_sequence);

    double y_equation = equation_y(eps);
    print_result("Equation method", y_equation);

    return 0;
}
