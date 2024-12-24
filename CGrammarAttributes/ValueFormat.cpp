#include "iostream"
int main() {
    // singed
    int int_min = 0x80000000;
    int int_max = 0x7FFFFFFF;
    std::cout << "int_min:" << int_min << "\n" << "int_max:" << int_max << "\n";
    // unsigned
    unsigned uint_max = 0xFFFFFFFF;
    std::cout << "uint_max" << uint_max << "\n";
    return 0;
}