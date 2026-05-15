// Longest Consecutive Sum of Sequence
#include <bits/stdc++.h>
std::pair<int, int> LCSS( std::vector<int> const& input ) {
    std::vector<int> dp( input.size() );
    std::vector<int> dpStart( input.size(), -1 );
    dp[0] = input[0];
    dpStart[0] = 0;
    int maxSum = INT_MIN, maxLen = 0;
    for ( int i = 1; i < dp.size(); i++ ) {
        if ( dp[i - 1] + input[i] > input[i] ) {
            dp[i] = dp[i - 1] + input[i];
            dpStart[i] = dpStart[i - 1];
        } else {
            dp[i] = input[i];
            dpStart[i] = i;
        }
        int len = i - dpStart[i] + 1;
        if ( dp[i] >= maxSum ) {
            if ( dp[i] == maxSum ) {
                maxLen = std::max( maxLen, len );
            }
            maxSum = dp[i];
        }
    }
    return { maxSum, maxLen };
}
