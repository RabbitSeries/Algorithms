#include <vector>
int lowbit( int x ) {
    return x & -x;  // -x = ~x + 1 % 2^n
}
// 49 = 1..32 (max 2^k) + 33..48 (16) (next 2^k) + 49 (1), **2^k's sum**, leave the last group: 1<= len <=2, so 49 only manage 49
// 49 -
// 1 = 1
// 2 = 1+2, then 2
// 3 = 1..2 + 3, then 4
// 4 = 1..2 + 3 + 4 , then 3..4
// 5 = 1..4 + 5, then 5
// 10 = 0..8 + 9..10, 0..8 exists, 10 = 9..10, in binary 10 = 1010b = 1000b + 10b (last split, last 1), and produce to
// 11 = 0..8 + 9..10 + 11
// ... 9 -> 10 -> 12 -> 16 -> ... **nearest 2^k's sum**
void update( size_t i, int delta, std::vector<int>& tree ) {
    i++;
    while ( i - 1 < tree.size() ) {
        tree[i - 1] += delta;
        i += lowbit( i );
    }
}
std::vector<int> build_tree( std::vector<int> const& init ) {
    std::vector<int> tree( init.size(), 0 );
    for ( int i = 0; int v : init ) {
        update( i, v, tree );
        i++;
    }
    return tree;
}
int prefix_sum( int i, std::vector<int> const& tree ) {
    int res = 0;
    i++;
    while ( i ) {
        res += tree[i - 1];
        i -= lowbit( i );
    }
    return res;
}
int range_sum( int l, int r, std::vector<int> const& tree ) {
    return prefix_sum( r, tree ) - prefix_sum( l - 1, tree );
}
