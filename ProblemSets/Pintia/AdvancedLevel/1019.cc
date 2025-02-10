#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
pair<bool, vector<ull>> judgePalindromic( ull decimal, ull  base ) {
    if( decimal < base ) {
        return { true,{decimal} };
    }
    vector<ull> baseInteger;
    while( decimal != 0 ) {
        baseInteger.push_back( decimal % base );
        decimal /= base;
    }
    size_t numLength = baseInteger.size();
    for( size_t i = 0; i < numLength / 2; i++ ) {
        if( baseInteger[i] != baseInteger[numLength - 1 - i] ) {
            return { false,baseInteger };
        }
    }
    return { true,baseInteger };
}

int main() {
    ull decimal, base;
    cin >> decimal >> base;
    auto res = judgePalindromic( decimal, base );
    cout << ( res.first ? "Yes" : "No" ) << endl;
    for( int i = res.second.size() - 1; i >= 0; i-- ) {
        cout << res.second[i] << ( i == 0 ? "" : " " );
    }
    return 0;
}