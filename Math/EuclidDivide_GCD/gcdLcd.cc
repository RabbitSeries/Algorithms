#include <iostream>
int gcd( int a, int b ) {
    return b == 0 ? a : gcd( b, a % b );
}
int lcd( int a, int b ) {
    return a / gcd( a, b ) * b;
}
int main() {
    std::cout << gcd( 24, 64 ) << std::endl;
    std::cout << lcd( 60, 30 ) << std::endl;
    return 0;
}