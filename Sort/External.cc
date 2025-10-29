#include <iostream>
#include <memory>
#include <random>
#include <ranges>
#include <vector>
struct Stream {
    using Node = std::shared_ptr<Stream>;
    Stream( int value ) : init_value{ value } {}
    int init_value;
    int value() {
        return init_value;
    }
    bool next() {
        init_value = INT_MAX;
        return false;
    }
};
std::vector<int> loser_tree_sort( std::vector<Stream::Node>& segments ) {
    int k = segments.size();
    // pair<loser segment id (not tree id), loser's value>
    // tree[0] is winner, the rest of k-1 is in complete binary tree
    std::vector<std::pair<int, int>> tree( k, { -1, INT_MAX } );
    // Winner + k - 1 internal nodes, k in total:
    // If height is h, total leaves is 2^(h-1), let it go up but below k, then there will be k-2^(h-1) extra leaves.
    // Take k-2^(h-1) leaves down, then each hole can connect two extra leaves, then the tree is able to have 2k-2^h leaves.
    // This is extactly the amount of k-2^(h-1) extra leaves and the taken down k-2^(h-1) leaves.
    // So in total there will be 2^(h) - 1 nodes in h layer plus 2k-2^h leaves in last layer, 2k-1 in total nodes,
    // in which k-1 is internal loser tree nodes for loser recording, and h leaves for data reading.
    std::vector<int> merged;
    // Initialize
    for ( int i = k - 1; i >= 0; i-- ) {
        int w = i;                                                               // Winner in this tournament.
        int p = ( w + 1 + k - 1 ) / 2;                                           /* segment id in tree, w+i to index from 1 (0 is for winner),
                                                                                    then skip k - 1 internal node, we will have the index of this node.
                                                                                  */
        while ( p && w >= 0 ) {                                                  // p == 0, reach winner.
            if ( tree[p].first < 0 || tree[p].second < segments[w]->value() ) {  // Empty parent is winner, let loser be the child.
                int winner = tree[p].first;
                tree[p] = { w, segments[w]->value() };
                w = winner;
            }
            p /= 2;                                                              // Go to the parent.
        }
        if ( w >= 0 ) {
            tree[0] = { w, segments[w]->value() };                               // w>=0, then winner is a valid winner
        }
    }
    // TODO change this to yield -1 when segments[w]->value is INT_MAX or segements[w]->isEmpty()...
    while ( tree[0].second != INT_MAX ) {                   // While the winner is valid, take its value out, and adjust the tree
        merged.emplace_back( tree[0].second );
        segments[tree[0].first]->next();
        int w = tree[0].first;                              // Winner in this tournament
        int p = ( w + 1 + k - 1 ) / 2;                      // Segment id in tree
        while ( p ) {                                       // p == 0, reach winner
            if ( tree[p].second < segments[w]->value() ) {  // Order: 1 <= 2 <=
                int winner = tree[p].first;
                tree[p] = { w, segments[w]->value() };
                w = winner;                                 // New winner
            }
            p /= 2;                                         // parent
        }
        tree[0] = { w, segments[w]->value() };
    }
    return merged;
}
// TODO swap select sorting
// TODO best merge tree
int main() {
    std::random_device rdv;
    std::mt19937 gen( rdv() );
    std::uniform_int_distribution u_dis( 0, 50 );
    // std::vector<int> test{ 27, 23, 46, 13 };
    // std::vector<int> test{ 0, 0, 0, 0 };
    std::vector<Stream::Node> segments;
    for ( int i = 0; i < 80; i++ ) {
        segments.push_back( std::make_shared<Stream>( u_dis( gen ) ) );
        if ( i % 17 == 0 ) {  // Empty segments test
            segments.back()->next();
        }
        // segments.push_back( std::make_shared<Stream>( tesst[i] ) );
    }
    auto original = segments |
                    std::views::transform( []( Stream::Node s ) { return s->value(); } ) |
                    std::views::filter( []( int num ) {
                        return num != INT_MAX;
                    } ) |
                    std::ranges::to<std::vector<int>>();
    std::cout << "Original: " << original.size() << "\n";
    for ( int n : original ) {
        std::cout << n << " ";
    }
    std::cout << "\n";
    std::sort( original.begin(), original.end() );
    for ( int n : original ) {
        std::cout << n << " ";
    }
    std::cout << "\n";
    auto result = loser_tree_sort( segments );
    std::cout << "Result:\n";
    std::cout << ( std::is_sorted( result.begin(), result.end() ) ? "√" : "X" ) << "\n";
    for ( int num : result ) {
        std::cout << num << " ";
    }
    std::cout << "\n";
}
// Another impl:
// #include <iostream>
// #include <memory>
// #include <random>
// #include <ranges>
// #include <vector>
// struct Stream {
//     using Node = std::shared_ptr<Stream>;
//     Stream( int value ) : init_value{ value } {}
//     int init_value;
//     int value() {
//         return init_value;
//     }
//     bool next() {
//         init_value = INT_MAX;
//         return false;
//     }
// };
// void adjust( std::vector<int>& tree, std::vector<Stream::Node>& segments, int w, int segLen ) {
//     int p = ( w + segLen ) / 2;
//     while ( p ) {
//         if ( segments[tree[p]]->value() < segments[w]->value() ) {
//             std::swap( w, tree[p] );
//         }
//         p /= 2;
//     }
//     tree[0] = w;  // There is definitely a winner
// }
// std::vector<int> loser_tree_sort( std::vector<Stream::Node>& segments ) {
//     int segLen = segments.size();
//     std::vector<int> tree( segLen, -1 );
//     std::vector<int> merged;
//     // Let every node fail when compare to empty parent, fill parent with node id
//     segments.push_back( std::make_shared<Stream>( INT_MIN ) );
//     for ( int i : std::views::iota( 0, segLen ) ) {    // Initialize to that foo node/sentinel
//         tree[i] = segLen;
//     }
//     for ( int i = segLen - 1; i >= 0; i-- ) {
//         adjust( tree, segments, i, segLen );
//     }
//     while ( segments[tree[0]]->value() != INT_MAX ) {  // While the winner is valid, take its value out, and adjust the tree
//         merged.emplace_back( segments[tree[0]]->value() );
//         segments[tree[0]]->next();
//         adjust( tree, segments, tree[0], segLen );
//     }
//     return merged;
// }
// void test() {
//     std::random_device rdv;
//     std::mt19937 gen( rdv() );
//     std::uniform_int_distribution u_dis( 0, 50 );
//     // std::vector<int> test{ 27, 23, 46, 13 };
//     // std::vector<int> test{ 0, 0, 0, 0 };
//     std::vector<Stream::Node> segments;
//     for ( int i = 0; i < 80; i++ ) {
//         segments.push_back( std::make_shared<Stream>( u_dis( gen ) ) );
//         if ( i % 17 == 0 ) {  // Empty segments test
//             segments.back()->next();
//         }
//         // segments.push_back( std::make_shared<Stream>( tesst[i] ) );
//     }
//     auto original = segments |
//                     std::views::transform( []( Stream::Node s ) { return s->value(); } ) |
//                     std::views::filter( []( int num ) {
//                         return num != INT_MAX;
//                     } ) |
//                     std::ranges::to<std::vector<int>>();
//     std::cout << "Original: " << original.size() << "\n";
//     for ( int n : original ) {
//         std::cout << n << " ";
//     }
//     std::cout << "\n";
//     std::sort( original.begin(), original.end() );
//     for ( int n : original ) {
//         std::cout << n << " ";
//     }
//     std::cout << "\n";
//     auto result = loser_tree_sort( segments );
//     std::cout << "Result:\n";
//     std::cout << ( std::is_sorted( result.begin(), result.end() ) ? "√" : "X" ) << "\n";
//     for ( int num : result ) {
//         std::cout << num << " ";
//     }
//     std::cout << "\n";
// }
// int main() {
//     for ( int i = 0; i < 5; i++ ) {
//         test();
//         std::cout << "\n";
//     }
// }
