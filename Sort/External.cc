#include <iostream>
#include <memory>
#include <random>
#include <ranges>
#include <vector>
struct Stream {
    using Node = std::shared_ptr<Stream>;
    // static inline std::binomial_distribution bio_gen = std::binomial_distribution( 1, 0.5 ); // 0.5 probability to generate end next()
    Stream( int value ) : init_value{ value } {}
    int init_value;
    int value() {
        return init_value;
    }
    bool empty() {
        return init_value == INT_MAX;
    }
    bool next() {
        init_value = INT_MAX;
        return false;
    }
};
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
// TODO swap select sorting
// TODO best merge tree
int main() {
    std::random_device rdv;
    std::mt19937 gen( rdv() );
    std::uniform_int_distribution u_dis( 0, 50 );
    // std::vector<int> test{ 27, 23, 46, 13};
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
    std::cout << "Original " << original.size() << " items:\n";
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
