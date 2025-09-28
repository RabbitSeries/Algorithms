#include <algorithm>
#include <iostream>
#include <numeric>
#include <ranges>
#include <vector>
int DP() {
    const int num = 53;
    std::vector<std::vector<int>> count( num + 1, std::vector<int>( num + 1, 0 ) );
    count[0][0] = 1;
    for ( int i = 1; i <= num; i++ ) {
        for ( int j = i; j <= num; j++ ) {
            for ( int k = 0; k < num; k++ ) {
                // This may outof bound, but impossible in logic, but keep k < num as a restriction anyways
                // for ( int k = 0; k <= num; k++ ) {
                // if ( count[j - i][k] != 0 ) {
                count[j][k + 1] += count[j - i][k];
                // }
            }
        }
    }
    return std::ranges::fold_left( count[num].begin() + 2, count[num].end(), 0, std::plus<>{} );
}
#include <unordered_map>
int Heuristics() {
    const int num = 53;
    std::vector<std::unordered_map<int, int>> count( num + 1 );
    count[0][0] = 1;
    for ( int i = 1; i <= num; i++ ) {
        for ( int j = i; j <= num; j++ ) {
            for ( const auto& [contains, ways] : count[j - i] ) {
                count[j][contains + 1] += ways;
            }
        }
    }
    return std::ranges::fold_left( count[num] |
                                       std::views::filter( []( const auto& K_V ) {
                                           return K_V.first >= 2;
                                       } ) |
                                       std::views::values,
                                   0, std::plus<>{} );
}
int main() {
    std::cout << "Result (DP approach): " << DP() << std::endl;
    std::cout << "Result (Heuristics approach): " << Heuristics() << std::endl;
}