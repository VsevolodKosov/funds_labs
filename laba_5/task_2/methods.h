#ifndef METHODS_H_
#define METHODS_H_

#include <iostream>
#include <vector>
#include <cstddef>
#include <string>
#include <filesystem>
#include <fstream>
#include <random>

using namespace std;
using namespace std::filesystem;


ostream &operator<<(ostream &os, byte b);

class encoder final{
    vector<byte> S, key;
    int x, y;

    static int to_int(byte b){return to_integer<int>(b);}
    void init();
    byte get_item();

public:
    encoder(vector<byte> &k): S(256), key(k), x(0), y(0){
        if (key.size() == 0){
            throw length_error("Length key is zero");
        }
    }

    void set_key(vector<byte> const &k);
    void encode(string const &input_name, string const &output_name);
    static vector<byte> generate_key(size_t size);
};

#endif