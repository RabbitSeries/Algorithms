#include "bits/stdc++.h"
using namespace std;

int main() {
    int cnt = 0, i = 0;
    cin >> cnt;
    getchar();
    while( i++ < cnt ) {
        string tmp;
        getline( cin, tmp );
        string newTmp = "";
        for( char c : tmp ) {
            if( isalpha( c ) )
                newTmp += tolower( c );
            else {
                newTmp += c;
            }
        }
        if( newTmp.find( "she" ) != string::npos || newTmp.find( "shi" ) != string::npos ) {
            cout << tmp << endl;
        }
    }
    return 0;
}