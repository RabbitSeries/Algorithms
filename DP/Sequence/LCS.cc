// Longest Common Sequence
#include <string>
#include <vector>
std::string LCS( std::string const& A, std::string const& B ) {
    std::vector dp( A.size() + 1, std::vector( B.size() + 1, 0 ) );
    for ( size_t i = 1; i <= A.size(); i++ ) {
        for ( size_t j = 1; j <= B.size(); j++ ) {
            if ( A[i - 1] == B[j - 1] ) {
                dp[i][j] = dp[i - 1][j - 1] + 1;  // If use dp[i-1][j] then B[j-1] will be counted twice, samee for dp[i][j-1] where A[i-1] will be counted twice
                // State machine should be A==B then move i to i+1, j to j+1
            } else if ( j ) {
                dp[i][j] = std::max( dp[i - 1][j], dp[i][j - 1] );
            }
        }
    }
    std::string lcs_str;
    int i = A.size(), j = B.size();
    while ( i && j ) {
        if ( A[i - 1] == B[j - 1] ) {
            lcs_str = A[i - 1] + lcs_str;
            i--;
            j--;
        } else if ( dp[i - 1][j] > dp[i][j - 1] ) {
            i--;  // minus i will produce longer common sequence
        } else {
            j--;
        }
    }
    return lcs_str;
}
