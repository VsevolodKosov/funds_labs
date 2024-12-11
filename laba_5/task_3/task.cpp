#include "methods.h"

int main()
{
    char arr[sizeof(unsigned int)*8];
    logical_values_array a(5);
    logical_values_array b(3);
    a.get_str_value(arr);
    std::cout << "a: " << arr << std::endl;

    b.get_str_value(arr);
    std::cout << "b: " << arr << std::endl;

    logical_values_array c = a.inversion();
    c.get_str_value(arr);
    std::cout << "inversion a: " << arr << std::endl;

    c = a.conjunction(b);
    c.get_str_value(arr);
    std::cout << "conjunction: " << arr << std::endl;

    c = a.disjunction(b);
    c.get_str_value(arr);
    std::cout << "disjunction: " << arr << std::endl;

    c = a.implication(b);
    c.get_str_value(arr);
    std::cout << "implication: " << arr << std::endl;

    c = a.coimplication(b);
    c.get_str_value(arr);
    std::cout << "coimplication: " << arr << std::endl;

    c = a.add_module_2(b);
    c.get_str_value(arr);
    std::cout << "add_mod2: " << arr << std::endl;

    c = a.equal(b);
    c.get_str_value(arr);
    std::cout << "equal: " << arr << std::endl;

    c = a.Pirs(b);
    c.get_str_value(arr);
    std::cout << "pirs: " << arr << std::endl;

    c = a.Sheffer(b);
    c.get_str_value(arr);
    std::cout << "sheffer: " << arr << std::endl;

    try{
        bool bit = a.get_bit(1);
        std::cout << "a.get_bit(1) = " << bit << std::endl;
        bit = a.get_bit(10);
        std::cout << "a.get_bit(10) = " << bit << std::endl;
    }

    catch (const char *error_message){
        std::cout << error_message << std::endl;
    }

    if (logical_values_array::equals(a, b)){
        std::cout << "a == b: True" << std::endl;
    }

    else{
        std::cout << "a == b: False" << std::endl;
    }

    c = a;
    if (logical_values_array::equals(a, c)){
        std::cout << "a == c: True" << std::endl;
    }
    else{
        std::cout << "a == c: False" << std::endl;
    }
}