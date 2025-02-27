#include <bits/stdc++.h>
using namespace std;
int binaryCount( int target ) {
    vector<int> dp( target + 1, 0 );
    for ( int i = 1; i <= target; i++ ) {
        dp[i] = dp[i >> 1] + i & 1;
    }
    return dp[target];
}

int main() {
    int target;
    cin >> target;
    binaryCount( target );
    return 0;
}