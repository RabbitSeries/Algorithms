#include <iostream>
#include <queue>
#include <ranges>
#include <unordered_map>
#include <vector>
struct Step {
    int item, ocupied;
    bool operator==( const Step& rhs ) const {
        return this->item == rhs.item && this->ocupied == rhs.ocupied;
    }
};
template <>
struct std::hash<Step> {
    std::size_t operator()( Step const& s ) const {
        return ( static_cast<size_t>( s.item ) << 32 ) ^ static_cast<size_t>( s.ocupied );
    }
};
int PackSize = 10, ItemN = 4;
int Knapsack( /* Index from 1 */ std::vector<int> const& ItemSize, /* Index from 1 */ std::vector<int> const& ItemValue ) {
    using namespace std;
#ifdef FULL_PACK
    // Start from 1, then choose in 1, .... , ItemN
    Step begin{ 1, 0 }, end{ ItemN, PackSize };
#else  // 01 pack, start from 0, then choose in 1, ..., ItemN
    Step begin{ 0, 0 }, end{ ItemN, PackSize };
#endif
    std::queue<Step> q( { begin } );
    std::unordered_map<Step, int> maxValue( { { begin, 0 } } );
    while ( !q.empty() ) {
        Step step = q.front();
        q.pop();
#ifdef FULL_PACK
        for ( int i = step.item; i <= ItemN; i++ ) {
#else  // 01 pack
        for ( int i = step.item + 1; i <= ItemN; i++ ) {
#endif
            Step nextStep{ i, step.ocupied + ItemSize[i] };
            if ( nextStep.ocupied <= PackSize ) {
                if ( !maxValue.contains( nextStep ) ) {
                    q.emplace( nextStep );
                }
                // State transfer equation:
                maxValue[nextStep] = std::max( maxValue[nextStep], maxValue[step] + ItemValue[i] );
            } else {
                // Else move current state to final state
                maxValue[end] = std::max( maxValue[end], maxValue[step] );
                // Pre sort Items according to ItemSize, then it is possible to break here, because following sizes will definitely exceed
            }
        }
    }
    return maxValue[end];
}
int main() {
    // 3 5 2 = 10
    // 4 6 3 = 13
    std::vector<std::pair<int, int>> size_values{ { 3, 4 }, { 5, 6 }, { 2, 3 }, { 4, 5 } };
    std::sort( size_values.begin(), size_values.end() );
    do {
        std::deque<int> sizes( std::from_range_t{}, size_values | std::views::keys | std::ranges::to<std::vector<int>>() );
        sizes.emplace_front( 0 );
        std::deque<int> values{ std::from_range_t{}, size_values | std::views::values | std::ranges::to<std::vector<int>>() };
        values.emplace_front( 0 );
        std::cout << Knapsack( { std::from_range_t{}, std::move( sizes ) | std::views::as_rvalue },
                               { std::from_range_t{}, std::move( values ) | std::views::as_rvalue } )
                  << std::endl;  // 13
    } while ( std::next_permutation( size_values.begin(), size_values.end() ) );
}
