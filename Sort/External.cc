#include <iostream>
#include <memory>
#include <queue>
#include <random>
#include <ranges>
#include <vector>
struct Stream {
    using Node = std::shared_ptr<Stream>;
    // static inline std::binomial_distribution bio_gen = std::binomial_distribution( 1, 0.5 ); // 0.5 probability to generate end next()
    std::vector<int> values;
    std::vector<int>::iterator itr = values.begin();
    Stream() {}
    Stream( int value ) : values{ { value } } {}
    Stream( std::vector<int>&& value ) : values( std::move( value ) ) {}
    int value() {
        return *itr;
    }
    bool empty() {
        return itr == values.end();
    }
    void next() {
        if ( itr != values.end() ) {
            itr++;
        }
    }
};
auto random_segments() {
    std::random_device rdv;
    std::mt19937 gen( rdv() );
    std::uniform_int_distribution u_dis( 0, 50 );
    // std::vector<int> test{ 27, 23, 46, 13};
    // std::vector<int> test{ 0, 0, 0, 0 };
    std::vector<Stream::Node> segments;
    for ( int i = 0; i < 76; i++ ) {
        if ( i % 17 == 0 ) {  // Empty segments test
            segments.push_back( std::make_shared<Stream>() );
        } else {
            segments.push_back( std::make_shared<Stream>( u_dis( gen ) ) );
        }
    }
    return segments;
}
void print_segments( std::vector<Stream::Node>& segments, const char* msg ) {
    auto original = segments |
                    std::views::filter( []( Stream::Node s ) {
                        return !s->empty();
                    } ) |
                    std::views::transform( []( Stream::Node s ) { return s->value(); } ) |
                    std::ranges::to<std::vector<int>>();
    std::cout << msg << "\nOriginal " << original.size() << " items:\n";
    for ( int n : original ) {
        std::cout << n << " ";
    }
    std::cout << "\n";
    std::sort( original.begin(), original.end() );
    for ( int n : original ) {
        std::cout << n << " ";
    }
    std::cout << "\n";
}
void print_result( std::vector<int> const& result, const char* msg ) {
    std::cout << msg << "\nResult sorted: " << ( std::is_sorted( result.begin(), result.end() ) ? "√" : "X" ) << "\n";
    for ( int num : result ) {
        std::cout << num << " ";
    }
    std::cout << "\n";
}
std::vector<int> loser_tree_sort( std::vector<Stream::Node>& segments ) {
    int k = segments.size();
    std::vector tree( k, -1 );  // win order: -1_th segment > smaller value > bigger value > empty segment
    // Initialize, let all non empty segment fail to initialize and fill the winner tree, -1 segment will win
    auto sift_up = [&]( int i ) {
        int w = i;
        int p = ( w + 1 + k - 1 ) / 2;
        while ( p && w >= 0 ) {  // if w is -1 segment, it will always win, tree[p] will never win
            // tree[p] will win if tree[p] is -1 segment, or segment[w] is empty or segment[tree[p]] has smaller value
            if ( tree[p] < 0 || ( segments[w]->empty() || ( !segments[tree[p]]->empty() && segments[tree[p]]->value() < segments[w]->value() ) ) ) {
                std::swap( tree[p], w );
            }
            p /= 2;
        }
        return tree[0] = w;
    };
    for ( int i = k - 1; i >= 0; i-- ) {         // reverese order
        sift_up( i );
    }
    int w = tree[0];
    std::vector<int> merged;
    while ( w >= 0 && !segments[w]->empty() ) {  // There will be no more -1_th segment
        merged.emplace_back( segments[w]->value() );
        segments[w]->next();
        w = sift_up( w );
    }
    return merged;
}
std::vector<int> best_merge_tree( std::vector<Stream::Node>& segments, int roads = 16 ) {
    int len = segments.size();
    // len + N = S = roads*N + 1 =>  N = len-1 / (roads-1)
    int v_seg_len = ( ( len - 1 ) % ( roads - 1 ) ) ? roads - ( len - 1 ) % ( roads - 1 ) - 1 : -1;  // Don't add virtual segments if it's already strict k-branch-tree
    // In total: virtual segemnts: v_seg_len, inner segments: 1 + (len-1) / (roads - 1), segments: len
    std::vector<Stream::Node> merge_tree( v_seg_len + 1 + ( len - 1 ) / ( roads - 1 ), std::make_shared<Stream>() );
    merge_tree.insert( merge_tree.end(), segments.begin(), segments.end() );
    for ( int i = merge_tree.size(); i > 1; i -= roads ) {  // Merge untill 0, end with 1
        std::vector to_merge( merge_tree.begin() + i - roads, merge_tree.begin() + i );
        int parent = ( i - 2 ) / roads;                     // i's parent is i-1/k (index from 0), then it's i-2/k
        merge_tree[parent] = std::make_shared<Stream>( loser_tree_sort( to_merge ) );
        print_result( merge_tree[parent]->values, ( std::format( "Merged: [{0:d},{1:d}) to {2:d}", i - roads, i, parent ) ).c_str() );
    }
    return std::move( merge_tree[0]->values );
}
int main() {
    auto loser_sort_test = random_segments();
    print_segments( loser_sort_test, "====================================TEST LOSER_TREE_SORT====================================" );
    auto result = loser_tree_sort( loser_sort_test );
    print_result( result, "====================================TEST LOSER_TREE_SORT RESULT=============================" );
    auto best_merge_test = random_segments();
    print_segments( best_merge_test, "====================================TEST BEST_MERGE_TREE=============================" );
    result = best_merge_tree( best_merge_test );
    print_result( result, "====================================TEST BEST_MERGE_TREE RESULT======================" );
    // TODO swap select sorting
    return 0;
}
