#include <algorithm>
#include <ranges>
#include <vector>
int Solution( int PackSize, int ItemN, /* Index from 1 */ std::vector<int> ItemSize, /* Index from 1 */ std::vector<int> ItemValue ) {
    using namespace std;
    std::vector<std::vector<int>> dp( ItemN + 1, std::vector<int>( PackSize + 1, 0 ) );
// Init condition
#ifdef MAX_DP
    // Max dp value // accumulator std::max
    std::ranges::fill( dp[0], 0 );
#else
    // Total ways to build pack j using 1-i item
    dp[0][0] = 1;  // accumulator std::plus<>
#endif
    for ( int i : std::views::iota( 1, ItemN + 1 ) ) {
#ifdef FULL_PACK
        // Full pack, take as many as you like
        for ( int j : std::views::iota( 1, PackSize + 1 ) ) {
            dp[i][j] = dp[i - 1][j];
            if ( j >= ItemSize[i] ) {
    #ifdef MAX_DP
                // Max dp value
                dp[i][j] = max( dp[i][j - ItemSize[i]] + ItemValue[i], dp[i][j] );
    #else
                // Total ways to build pack j using 1-i item
                dp[i][j] += dp[i][j - ItemSize[i]];
    #endif
            }
        }
#else
        // 01 pack, take or leave
        for ( int j : std::views::reverse( std::views::iota( ItemSize[i], PackSize + 1 ) ) ) {
    #ifdef MAX_DP
            // Max dp value
            dp[i][j] = std::max( dp[i - 1][j - ItemSize[i]] + ItemValue[i], dp[i - 1][j] );
    #else
            // Total ways to build pack j using 1-i item
            dp[i][j] = dp[i - 1][j] + dp[i - 1][j - ItemSize[i]];
    #endif
        }
#endif
    }
    std::vector<int> roll_dp( ItemN + 1, 0 );
    // Init condition
#ifdef MAX_DP
    // Max dp value // accumulator std::max
    std::ranges::fill( roll_dp, 0 );
#else
    // Total ways to build pack j using 1-i item
    roll_dp[0] = 1;  // accumulator std::plus<>
#endif
    for ( int i : std::views::iota( 1, ItemN + 1 ) ) {
#ifdef FULL_PACK
        // Full pack, take as many as you like
        for ( int j : std::views::iota( 1, PackSize + 1 ) ) {
            if ( j >= ItemSize[i] ) {
    #ifdef MAX_DP
                // Max dp value
                roll_dp[j] = std::max( roll_dp[j - ItemSize[i]] + ItemValue[i], roll_dp[j] );
    #else
                // Total ways to build pack j using 1-i item
                roll_dp[j] += roll_dp[j - ItemSize[i]];
    #endif
            }
        }
#else
        // 01 pack, take or leave
        for ( int j : std::views::reverse( std::views::iota( ItemSize[i], PackSize + 1 ) ) ) {
    #ifdef MAX_DP
            // Max dp value
            roll_dp[j] = max( roll_dp[j - ItemSize[i]] + ItemValue[i], roll_dp[j] );
    #else
            // Total ways to build pack j using 1-i item
            roll_dp[j] = roll_dp[j] + roll_dp[j - ItemSize[i]];
    #endif
        }
#endif
    }
}
