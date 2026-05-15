// Given a random string with length: [1, 2000]
// You can insert any char into any place of the string.
// The object is to find the minimal insertion times to construct a palindrome string.

// Solution: find the longest palindrome sub string sequence.
// It can be proved that the minimum insertion times is len(string) - len(the sub sequence)

// The final question is how to find the longest palindrome sub sequence?
#include <iostream>
#include <string>
#include <vector>

void basic_appraoch() {
    std::string input{ "dynamicprogramming" };  // nmi [any] imn
    auto dp = std::vector( input.size(), std::vector<int>( input.size(), 0 ) );
    for ( size_t i = 0; i < input.size(); i++ ) {
        dp[i][i] = 1;  // character it self is a palindrome.
    }
    // dp[i][j] (i<=j) =   dp[i+1][j-1]+2 s[i]==s[j]
    //                     max(dp[i+1][j], dp[i][j-1]) otherwise
    // dependencies:
    //    * ⇐ *
    //      ⇙ ⇓
    //    *   *
    for ( size_t cross = 1; cross < input.size(); cross++ ) {
        for ( size_t elem = 0; elem < input.size() - cross; elem++ ) {
            int i = elem, j = cross + elem;
            if ( input[i] == input[j] ) {
                dp[i][j] = 2 + dp[i + 1][j - 1];
            } else {
                dp[i][j] = std::max( dp[i + 1][j], dp[i][j - 1] );
            }
        }
    }
    std::cout << dp[0].back() << std::endl;
}

void space_reuse() {
    std::string input{ "dynamicprogramming" };  // nmi [any] imn
    auto dp = std::vector( input.size(), 1 );
    // dp on the main diagnal line
    for ( int i = input.size() - 1; i >= 0; i-- ) {
        int lastDiag = 0;
        for ( size_t j = i + 1; j < input.size(); j++ ) {
            int prev = dp[j];
            if ( input[i] == input[j] ) {
                dp[j] = lastDiag + 2;
            } else {
                dp[j] = std::max( dp[j], dp[j - 1] );
            }
            lastDiag = prev;
        }
    }
    std::cout << dp.back() << std::endl;
}

int main() {
    basic_appraoch();
    space_reuse();
    return 0;
}
