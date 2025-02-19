#include <bits/stdc++.h>
using namespace std;

void convert( int num ) {
    string res = "";
    while( num != 0 ) {
        char curDigit;
        stringstream ss;
        ss << hex << ( num % 13 );
        ss >> curDigit;
        res = string( 1, toupper( curDigit ) ) + res;
        num /= 13;
    }
    cout << setw( 2 ) << setfill( '0' ) << res;
}

int main() {
    int r, g, b;
    cin >> r >> g >> b;
    cout << "#";
    convert( r );
    convert( g );
    convert( b );
    return 0;
}