#include "methods.h"

int main(){
    
        vector<byte> key;
        key = encoder::generate_key(100);

        encoder encdr(key);
        string a{"input.txt"}, b{"encode.txt"}, c{"decode.txt"}, d{"decode_for_new_key.txt"}, e{"encode_for_new_key.txt"};

        encdr.set_key(encoder::generate_key(256));
        encdr.encode(a, e);
        encdr.encode(e, d); 
    
    try{
        encdr.encode(a, b);
    }
    catch (const runtime_error& e){
        std::cerr << "Error: " << e.what() << std::endl;
    }

    try{
        encdr.encode(b, c);
    }
    catch (const runtime_error& e){
        std::cerr << "Error: " << e.what() << std::endl;
    }

}