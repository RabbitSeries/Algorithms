#include <algorithm>
#include <functional>
#include <ranges>
#include <vector>
int Transfor( int PackSize, int ItemN, /* Index from 1 */ std::vector<int> ItemSize, /* Index from 1 */ std::vector<int> ItemValue ) {
    int newPackSize = std::ranges::fold_left( ItemValue, 0, std::plus<>{} );
    return Solution( newPackSize, ItemN, ItemValue, ItemSize, []( int a, int b ) { return std::min( a, b ); }, PackSize );
}
#define MIN_DP
int Solution( int PackSize, int ItemN, /* Index from 1 */ std::vector<int> ItemSize, /* Index from 1 */ std::vector<int> ItemValue, std::function<int( int, int )> f, int sideEffect = 0 ) {
    // Init condition
    std::vector<std::vector<int>> dp( ItemN + 1, std::vector<int>( PackSize + 1, 0 ) );
    // Min dp value // accumulator std::Min
    std::ranges::fill( dp[0], 0 );
    int maxVal = 0;
    for ( int i : std::views::iota( 1, ItemN + 1 ) ) {
        for ( int j : std::views::reverse( std::views::iota( ItemSize[i], PackSize + 1 ) ) ) {
            dp[i][j] = f( dp[i - 1][j - ItemSize[i]] + ItemValue[i], dp[i - 1][j] );
            if ( dp[i][j] <= sideEffect ) {
                maxVal = std::max( j, maxVal );
            }
        }
    }
    std::vector<int> roll_dp( ItemN + 1, 0 );
    std::ranges::fill( roll_dp, 0 );
    for ( int i : std::views::iota( 1, ItemN + 1 ) ) {
        for ( int j : std::views::reverse( std::views::iota( ItemSize[i], PackSize + 1 ) ) ) {
            roll_dp[j] = f( roll_dp[j - ItemSize[i]] + ItemValue[i], roll_dp[j] );
        }
    }
    *std::ranges::find_if( std::views::reverse( std::views::iota( 0, PackSize + 1 ) ), [&]( int i ) { return roll_dp[i] <= sideEffect; } );
}