#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ull;
string radixString( ull decimal, int radix ) {
    string res = "";
    if( decimal == 0 ) {
        return "0";
    }
    while( decimal > 0 ) {
        res = to_string( decimal % radix ) + res;
        decimal /= radix;
    }
    return res;
}

// Prime is not odd
bool isPrime( ull decimal ) {
    if( decimal == 1 || decimal == 2) {
        return false;
    }
    ull squareRoot = sqrt( decimal );
    for( int i = 2; i <= squareRoot; i++ ) {
        if( decimal % i == 0 ) {
            return false;
        }
    }
    return true;
}

ull stringToull( string s, int radix ) {
    ull res = 0;
    for( char c : s ) {
        res = res * radix + c - '0';
    }
    return res;
}

int main() {
    long long  n;
    int r;
    cin >> n;
    while( n > 0 ) {
        cin >> r;
        if( !isPrime( n ) ) {
            cout << "No" << endl;
        } else {
            string original = radixString( n, r );
            reverse( original.begin(), original.end() );
            if( isPrime( stringToull( original, r ) ) ) {
                cout << "Yes" << endl;
            } else {
                cout << "No" << endl;
            }
        }
        cin >> n;
    }
    return 0;
}