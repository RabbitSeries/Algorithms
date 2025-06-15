#include <bits/stdc++.h>
using namespace std;
int main() {
    string buf;  // string.push_back(0) only adds more backslash, and size will increase
    getline( cin, buf );
    cout << ( buf[0] == '+' ? "" : "-" );
    string realNumber;
    for ( char c : buf.substr( 1 ) ) {
        if ( c == 'E' ) {
            break;
        }
        if ( c != '.' ) {
            realNumber.push_back( c );
        }
    }
    int exp = stoi( buf.substr( buf.find( 'E' ) + 1 ) );
    if ( exp >= 0 ) {
        size_t i = 1;  // float point position
        for ( ; i <= (size_t)exp; i++ ) {
            realNumber += i >= realNumber.size() ? "0" : "";
        }
        if ( i == realNumber.size() ) {
            cout << realNumber;
        } else {
            cout << realNumber.substr( 0, i ) << "." << realNumber.substr( i );
        }
    } else {
        for ( int i = abs( exp ); i > 0; i-- ) {
            realNumber = "0" + realNumber;
        }
        cout << realNumber.substr( 0, 1 ) << "." << realNumber.substr( 1 );
    }
}