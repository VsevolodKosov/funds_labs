#include "methods.h"

Complex Complex::add(const Complex& right) const {
    double new_real = real + right.getReal();
    double new_imag = imag + right.getImag();
    return Complex(new_real, new_imag);
}

Complex Complex::sub(const Complex& right) const {
    double new_real = real - right.getReal();
    double new_imag = imag - right.getImag();
    return Complex(new_real, new_imag);
}

Complex Complex::mult(const Complex& right) const {
    double new_real = real * right.getReal() - imag * right.getImag();
    double new_imag = real * right.getImag() + imag * right.getReal();
    return Complex(new_real, new_imag);
}

Complex Complex::div(const Complex& right) const {
    double denominator = right.getReal() * right.getReal() + right.getImag() * right.getImag();
    if (fabs(denominator) < __DBL_EPSILON__) {
        throw std::overflow_error("Division by zero exception");
    }
    double new_real = (real * right.getReal() + imag * right.getImag()) / denominator;
    double new_imag = (imag * right.getReal() - real * right.getImag()) / denominator;
    return Complex(new_real, new_imag);
}
