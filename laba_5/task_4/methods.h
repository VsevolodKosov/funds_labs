#ifndef METHODS_H_
#define METHODS_H_

#include <iostream>
#include <cmath>
#include <stdexcept>

class Complex final {
    double real{0.0};  
    double imag{0.0}; 

public:
    Complex(double re = 0.0, double im = 0.0) : real(re), imag(im) {}

    double getReal() const { return real; }
    double getImag() const { return imag; }

    Complex add(const Complex& right) const;
    Complex sub(const Complex& right) const;
    Complex mult(const Complex& right) const;
    Complex div(const Complex& right) const;

    double complex_abs() const { return sqrt(real * real + imag * imag); }

    double argument() const { 
        if (real == 0 && imag == 0) {
            throw std::invalid_argument("Argument is undefined for zero complex number.");
        }
        return atan(imag / real) * 180.0 / M_PI; 
    }

    void print() const {
        std::cout << real;
        if (imag >= 0) {
            std::cout << " + " << imag << "i";
        } else {
            std::cout << " - " << -imag << "i";
        }
    }
};


#endif  
