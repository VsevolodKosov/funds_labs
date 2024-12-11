#ifndef METHODS_H_
#define METHODS_H_

#include <iostream>
#include <stdexcept>
#include <string.h>

class logical_values_array final{
    unsigned int value;

public:
    logical_values_array(unsigned int x = 0): value(x)
        {}
    
    unsigned int get_value() const {return value;}
    logical_values_array inversion() const {return logical_values_array(~value);}
    logical_values_array conjunction(logical_values_array const &obj) const  {return logical_values_array(value & obj.value);}
    logical_values_array disjunction(logical_values_array const &obj) const {return logical_values_array(value | obj.value);}
    logical_values_array implication(logical_values_array const &obj) const {return this->inversion().disjunction(obj);}
    logical_values_array coimplication(logical_values_array const &obj) const {return this->implication(obj).inversion();}
    logical_values_array add_module_2(logical_values_array const &obj);
    logical_values_array equal(logical_values_array const &obj) {return this->add_module_2(obj).inversion();}
    logical_values_array Pirs(logical_values_array const &obj) {return this->disjunction(obj).inversion();}
    logical_values_array Sheffer(logical_values_array const &obj) {return this->conjunction(obj).inversion();}
    static bool equals(logical_values_array const &obj_1, logical_values_array const &obj_2) { return obj_1.get_value() == obj_2.get_value();}
    bool get_bit(size_t position) const;
    void get_str_value(char *str_value) const;
};

#endif