#include <bits/stdc++.h>
using namespace std;
int main() {
    using ull = unsigned long long;
    vector<vector<ull>> AB( 2, vector<ull>( 3 ) );
    scanf( "%lld.%lld.%lld", &AB[0][0], &AB[0][1], &AB[0][2] );
    scanf( "%lld.%lld.%lld", &AB[1][0], &AB[1][1], &AB[1][2] );
    ull carry = 0, nextCarry = 0;
    nextCarry = ( AB[0][2] + AB[1][2] + carry ) / 29;
    AB[0][2] = ( AB[0][2] + AB[1][2] + carry ) % 29;
    carry = nextCarry;
    nextCarry = ( AB[0][1] + AB[1][1] + carry ) / 17;
    AB[0][1] = ( AB[0][1] + AB[1][1] + carry ) % 17;
    carry = nextCarry;
    AB[0][0] = ( AB[0][0] + AB[1][0] + carry );  // AB[0][0] = ( AB[0][0] + AB[1][0] + carry ) % 10000001l; will WA at point 3, highest field requires no celing.
    cout << AB[0][0] << "." << AB[0][1] << "." << AB[0][2];
}