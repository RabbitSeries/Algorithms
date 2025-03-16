#include <bits/stdc++.h>
using namespace std;
int main() {
    int segCnt;
    cin >> segCnt;
    vector<string> list( segCnt );
    for ( int i = 0; i < segCnt; i++ )
        cin >> list[i];
    sort( list.begin(), list.end(), []( const string& s1, const string& s2 ) { return s1 + s2 < s2 + s1; } );  // For num string compare cpp stl have already implemented the operator<.
    string res = accumulate( list.begin(), list.end(), string( "" ) );
    while ( res.size() && res.front() == '0' )  // string.front() stops to assert string.empty() in C++ 20 beacause string::front() is qulified with constexpr
        res = res.substr( 1 );
    cout << res;
    return 0;
}
// If the two string have no comman prefix, simply compare the first digit which is also implemented by operator<
// for ( int i = 0; i < s1.size() && i < s2.size(); i++ ) {
//     if ( s1[i] != s2[i] )
//         return s1[i] < s2[i];
// }