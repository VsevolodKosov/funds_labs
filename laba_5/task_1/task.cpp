#include "methods.h"

int main(){
    Binary_int a(52), b, c;
    std::pair<Binary_int, Binary_int> p;

    std::cout << "a = " << a.get_value() << "; bits: " << a << std::endl;

    a = -a;
    std::cout << "(a = -a):" << std::endl;
    std::cout << "a = " << a.get_value() << "; bits: " << a << std::endl;

    b = a++;
    std::cout << "(b = a++):" << std::endl;
    std::cout << "a = " << a.get_value() << "; bits: " << a << std::endl;
    std::cout << "b = " << b.get_value() << "; bits: " << b << std::endl;

    b = ++a;
    std::cout << "(b = ++a): " << std::endl;
    std::cout << "a = " << a.get_value() << "; bits: " << a << std::endl;
    std::cout << "b = " << b.get_value() << "; bits: " << b << std::endl;

    b = a--;
    std::cout << "(b = a--) :" << std::endl;
    std::cout << "a = " << a.get_value() << "; bits: " << a << std::endl;
    std::cout << "b = " << b.get_value() << "; bits: " << b << std::endl;

    b = --a;
    std::cout << "(b = a--) :" << std::endl;
    std::cout << "a = " << a.get_value() << "; bits: " << a << std::endl;
    std::cout << "b = " << b.get_value() << "; bits: " << b << std::endl;

    b += a;
    std::cout << "(b += a) :" << std::endl;
    std::cout << "a = " << a.get_value() << "; bits: " << a << std::endl;
    std::cout << "b = " << b.get_value() << "; bits: " << b << std::endl;

    b -= a;
    std::cout << "(b -= a):" << std::endl;
    std::cout << "a = " << a.get_value() << "; bits: " << a << std::endl;
    std::cout << "b = " << b.get_value() << "; bits: " << b << std::endl;

    b *= a;
    std::cout << "(b *= a):" << std::endl;
    std::cout << "a = " << a.get_value() << "; bits: " << a << std::endl;
    std::cout << "b = " << b.get_value() << "; bits: " << b << std::endl;

    c = a + b;
    std::cout << "(c = a + b):" << std::endl;
    std::cout << "a = " << a.get_value() << "; bits: " << a << std::endl;
    std::cout << "b = " << b.get_value() << "; bits: " << b << std::endl;
    std::cout << "c = " << c.get_value() << "; bits: " << c << std::endl;

    c = a - b;
    std::cout << "(c = a - b):" << std::endl;
    std::cout << "a = " << a.get_value() << "; bits: " << a << std::endl;
    std::cout << "b = " << b.get_value() << "; bits: " << b << std::endl;
    std::cout << "c = " << c.get_value() << "; bits: " << c << std::endl;

    c = a * b;
    std::cout << "(c = a * b):" << std::endl;
    std::cout << "a = " << a.get_value() << "; bits: " << a << std::endl;
    std::cout << "b = " << b.get_value() << "; bits: " << b << std::endl;
    std::cout << "c = " << c.get_value() << "; bits: " << c << std::endl;

    std::cout << "(b <<= 2):" << std::endl;
    std::cout << "b = " << b.get_value() << "; bits: " << b << std::endl;
    b <<= 2;
    std::cout <<"b = " << b.get_value() << "; bits: " << b << std::endl;

    std::cout << "(b >>= 5):" << std::endl;
    std::cout << "b = " << b.get_value() << "; bits: " << b << std::endl;
    b >>= 5;
    std::cout << "b = " << b.get_value() << "; bits: " << b << std::endl;

    std::cout << "(b = b >> 2):" << std::endl;
    std::cout << "b = " << b.get_value() << "; bits: " << b << std::endl;
    b = b >> 2;
    std::cout << "b = " << b.get_value() << "; bits: " << b << std::endl;

    std::cout << "(b = b << 7):" << std::endl;
    std::cout << "b = " << b.get_value() << "; bits: " << b << std::endl;
    b = b << 7;
    std::cout << "b = " << b.get_value() << "; bits: " << b << std::endl;

    std::cout << "(b.get_pair()):" << std::endl;
    p = b.get_pair();
    std::cout << "b = " << b.get_value() << "; bits: " << b << std::endl;
    std::cout << "Pair b:\n"
              << p.first << '\n'
              << p.second << std::endl;

    return 0;
}