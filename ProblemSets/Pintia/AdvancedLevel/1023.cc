#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;

string doubleNum( string input ) {
    int carray = 0;
    string res = "";
    for( int i = input.size() - 1; i >= 0; i-- ) {
        int cur = ( carray + ( input[i] - '0' ) * 2 ) % 10;
        res = to_string( cur ) + res;
        carray = ( carray + ( input[i] - '0' ) * 2 ) / 10;
    }
    if( carray != 0 ) {
        res = to_string( carray ) + res;
    }
    return res;
}

int main() {
    string input;
    cin >> input;
    int hash[10]{ 0 };
    for( auto c : input ) {
        hash[c - '0']++;
    }
    string res = doubleNum( input );
    for( auto c : res ) {
        hash[c - '0']--;
    }
    for( int h : hash ) {
        if( h != 0 ) {
            cout << "No" << endl << res;
            return 0;
        }
    }
    cout << "Yes" << endl << res;
    return 0;
}