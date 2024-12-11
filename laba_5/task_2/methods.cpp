#include "methods.h"


ostream &operator<<(ostream &os, byte b){
    return os << char(b);
}

void encoder::init(){
    for (int i = 0; i < 256; i++){
        S[i] = byte((unsigned char)i);
    }
        
    int key_length = key.size();
    int j = 0;
    for (int i = 0; i < 256; i++){
        j = (j + to_int(S[i]) + to_int(key[i % key_length])) % 256;
        swap(S[i], S[j]);
    }
}

byte encoder::get_item(){
    x = (x + 1) % 256;
    y = (y + to_int(S[x])) % 256;
    swap(S[x], S[y]);
    return S[(to_int(S[x]) + to_int(S[y])) % 256];
}

void encoder::set_key(vector<byte> const &k){
    if (key.size() == 0)
        throw std::length_error("Length key is zero");
    key = k;
}

void encoder::encode(string const &input_name, string const &output_name){
    path p1{input_name};
    path p2{output_name};
    if (equivalent(p1, p2)){
        throw runtime_error("Two identical files have been transferred");
    }

    ifstream in;
    ofstream out;
    in.open(input_name, std::ios::in);
    if (!in.is_open()){
        throw runtime_error("Couldn't open the input file");
    }

    out.open(output_name, std::ios::out);
    if (!out.is_open()){
        in.close();
        throw runtime_error("Couldn't open the output file");
    }

    init();
    x = 0, y = 0;

    byte b;
    char ch;
    while ((ch = in.get()) != EOF){
        b = byte{(unsigned char)ch};
        out << (b ^ get_item());
    }
    in.close();
    out.close();
}

vector<byte> encoder::generate_key(size_t size){
    srand((unsigned)time(NULL));
    vector<byte> key(size);
    for (int i = 0; i < size; ++i){
        key[i] = byte(rand() % 256);
    }
    return key;
}


