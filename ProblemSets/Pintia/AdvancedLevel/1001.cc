#include <bits/stdc++.h>
using namespace std;

void formatStr( string s ) {
    string cat = "";
    if( s.length() <= 3 ) {
        cout << s;
        return;
    }
    while( s.length() > 3 ) {
        cat = "," + s.substr( s.length() - 3, 3 ) + cat;
        s = s.substr( 0, s.length() - 3 );
    }
    cout << s + cat;
}

int main() {
    long long a, b;
    cin >> a >> b;
    long long sum = a + b;
    string outPut = to_string( sum );
    if( sum < 0 ) {
        cout << "-";
        formatStr( outPut.substr( 1 ) );
    }
    else {
        formatStr( outPut );
    }
    return 0;
}