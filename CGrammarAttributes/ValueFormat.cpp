#include "iostream"
union storage_endianness{
    unsigned int _4bytes = 0x01020304;
    char byteArray[4];
};
union float_binary {
    float_binary( const unsigned long _digits ) : digits( _digits ) {};
    unsigned int digits;
    float val;
};
union double_binary {
    double_binary( const unsigned long long _digits ) : digits( _digits ) {};
    unsigned long long digits;
    double val;
};
int main() {
    // singed, two's 
    int int_min = 0x80000000;
    int int_max = 0x7FFFFFFF;
    std::cout << "int_min:" << int_min << "\n" << "int_max:" << int_max << "\n";
    // unsigned
    unsigned uint_max = 0xFFFFFFFF;
    std::cout << "uint_max:" << uint_max << "\n";

    // floating point type
    float_binary float_min_normal( 0x00800000 );
    std::cout << "float_min_normal:±" << float_min_normal.val << "\n";
    double_binary double_min_normal( 0x0010000000000000 );
    std::cout << "double_min_normal:±" << double_min_normal.val << "\n";


    return 0;
}