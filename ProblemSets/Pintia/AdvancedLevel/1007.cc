#include <bits/stdc++.h>
using namespace std;
int main() {
    int n = 0;
    cin >> n;
    vector<int> dp( 1, 0 ), s( 1, 1 ), numList( 1, 0 );
    int maxSum = -1, startNum = 0, endNum = 0;
    bool allNegative = false;
    for( int i = 1; i <= n; i++ ) {
        int curNum;
        cin >> curNum;
        numList.push_back( curNum );
        if( dp[i - 1] > 0 ) {
            dp.push_back( curNum + dp[i - 1] );
            s.push_back( s[i - 1] );
        }
        else if( dp[i - 1] == 0 ) {
            // Hack data
            // input: 
            // 3
            // 0 0 1
            // output:
            // 1 0 1 (output the one with the smallest indices i and j)
            dp.push_back( curNum );
            s.push_back( s[i - 1] );
        }
        else {
            dp.push_back( curNum );
            s.push_back( i );
        }
        if( dp[i] > maxSum ) {
            maxSum = dp[i];
            startNum = numList[s[i]];
            endNum = numList[i];
        }
    }
    if( maxSum <= -1 ) {
        cout << 0 << " " << numList[1] << " " << numList[n];
    }
    else {
        cout << maxSum << " " << startNum << " " << endNum;
    }
    return 0;
}
