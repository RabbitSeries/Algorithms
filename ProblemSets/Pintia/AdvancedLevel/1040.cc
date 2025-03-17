#include <bits/stdc++.h>
using namespace std;
int main() {
    string input;
    getline( cin, input );
    string res = "";  // int res = 0;
    for ( size_t i = 0; i < input.size(); i++ ) {
        for ( size_t halfLen = 0; ( i - halfLen ) >= 0 && ( i + halfLen ) < input.length(); halfLen++ ) {
            if ( input[i - halfLen] != input[i + halfLen] ) break;
            if ( res.empty() || ( halfLen * 2 + 1 ) > res.length() ) res = input.substr( i - halfLen, halfLen * 2 + 1 );
        }
        for ( size_t halfLen = 0; ( i - halfLen ) >= 0 && ( i + 1 + halfLen ) < input.length(); halfLen++ ) {
            if ( input[i - halfLen] != input[i + 1 + halfLen] ) break;
            if ( res.empty() || ( halfLen * 2 + 2 ) > res.length() ) res = input.substr( i - halfLen, halfLen * 2 + 2 );
        }
    }
    cout << res.length();
}