#include "methods.h"

logical_values_array logical_values_array::add_module_2(logical_values_array const &obj){
    logical_values_array first, second;
    first = this->inversion().conjunction(obj);
    second = this->conjunction(obj.inversion());
    return first.disjunction(second);
}

bool logical_values_array::get_bit(size_t position) const{
    if (position >= sizeof(value) * 8)
        throw "Incorrect position";

    return (1ul << position) & value;
}

void logical_values_array::get_str_value(char *str_value) const{
    if (!str_value){
        throw "Null string";
    }

    short count_bits = sizeof(value) * 8;
    for (int i = 0; i < count_bits; ++i){
        str_value[count_bits - 1 - i] = ((1 << i) & value) ? '1' : '0';
    }
    str_value[count_bits] = '\0';
}
