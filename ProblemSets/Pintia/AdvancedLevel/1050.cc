#include <bits/stdc++.h>
using namespace std;
int main() {
    string s1, s2;
    getline( cin, s1 );
    getline( cin, s2 );
    set<char> exclude;
    for ( const char& c : s2 ) exclude.insert( c );
    stringstream buf;
    for ( int i = 0; i < s1.size(); i++ ) {
        if ( !exclude.contains( s1[i] ) )
            buf << s1[i];
    }
    cout << buf.str();
}