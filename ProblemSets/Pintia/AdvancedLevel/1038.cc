#include <bits/stdc++.h>
using namespace std;
int main() {
    int segCnt;
    cin >> segCnt;
    vector<string> list( segCnt );
    for ( int i = 0; i < segCnt; i++ )
        cin >> list[i];
    sort( list.begin(), list.end(), []( const string& s1, const string& s2 ) { return s1 + s2 < s2 + s1; } );
    string res = accumulate( list.begin(), list.end(), string( "" ) );
    while ( res.size() > 1 && res.front() == '0' )  // This problem puzzled on the substr(1) segmentation error if string is empty
        res = res.substr( 1 );
    cout << res;
    return 0;
}
// for ( int i = 0; i < s1.size() && i < s2.size(); i++ ) {
//     if ( s1[i] != s2[i] )
//         return s1[i] < s2[i];
// }