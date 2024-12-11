#include "methods.h"

int main() {
    Complex c1(3.0, 4.0);
    Complex c2(1.0, 2.0);
    Complex c_zero(0.0, 0.0);

    Complex sum = c1.add(c2);
    std::cout << "c1 + c2 = ";
    sum.print();
    std::cout << std::endl;

    Complex diff = c1.sub(c2);
    std::cout << "c1 - c2 = ";
    diff.print();
    std::cout << std::endl;

    Complex prod = c1.mult(c2);
    std::cout << "c1 * c2 = ";
    prod.print();
    std::cout << std::endl;

    try {
        Complex quot = c1.div(c_zero);
        std::cout << "c1 / c_zero = ";
        quot.print();
        std::cout << std::endl;
    } catch (const std::overflow_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    std::cout << "Modulus of c1 = " << c1.complex_abs() << std::endl;
    std::cout << "Argument of c1 = " << c1.argument() << " degrees" << std::endl;

    return 0;
}
