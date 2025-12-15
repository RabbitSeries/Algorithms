#include <functional>
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
    explicit Stream( std::vector<int>&& val_gen ) : values( std::move( val_gen ) ) {}
    int value() const {
        return *itr;
    }
    bool empty() const {
        return itr == values.end();
    }
    int size() const {
        return values.size();
    }
    void next() {
        if ( itr != values.end() ) {
            itr++;
        }
    }
};
bool operator<( const Stream::Node& parent, const Stream::Node& current ) {
    // win order: -1_th segment > smaller value > bigger value > empty segment
    // tree[p] will win if tree[p] is -1 segment, or segment[w] is empty or segment[tree[p]] has smaller value
    /* new comer should lose to maintain stable sort */
    return current->empty() || ( !parent->empty() && parent->value() <= current->value() );
};
auto random_segments( int segment_len ) {
    std::mt19937 gen( std::random_device{}() );
    std::uniform_int_distribution u_dis( 0, 50 );
    std::vector<Stream::Node> segments;
    for ( int i = 0; i < segment_len; i++ ) {
        if ( i % 17 == 0 ) {  // Empty segments test
            segments.push_back( std::make_shared<Stream>() );
        } else {
            segments.push_back( std::make_shared<Stream>( u_dis( gen ) ) );
        }
    }
    return segments;
}
auto random_data( int data_len ) {
    std::mt19937 gen( std::random_device{}() );
    std::uniform_int_distribution u_dis( 0, 50 );
    std::vector<int> segments;
    for ( int i = 0; i < data_len; i++ ) {
        segments.push_back( u_dis( gen ) );
    }
    return segments;
}
void print_raw_data( std::vector<int> const& result, const char* msg, bool judgeSorted = true ) {
    std::cout << msg << "\n";
    if ( judgeSorted ) {
        std::cout << std::format( "Result sorted: {:s}\n", std::is_sorted( result.begin(), result.end() ) ? "√" : "X" );
    }
    for ( int i = 0; int num : result ) {
        std::cout << std::format( "{:02d} ", num );
        if ( ( ++i ) % 50 == 0 ) {
            std::cout << "\n";
        }
    }
    std::cout << "\n";
}
void print_segments( std::vector<Stream::Node>& segments, const char* msg ) {
    auto original = segments |
                    std::views::filter( []( Stream::Node s ) {
                        return !s->empty();
                    } ) |
                    std::views::transform( []( Stream::Node s ) { return s->value(); } ) |
                    std::ranges::to<std::vector<int>>();
    std::cout << std::format( "{:s}\nOriginal {:d} items:\n", msg, segments.size() );
    print_raw_data( original, "", false );
    std::sort( original.begin(), original.end() );
    print_raw_data( original, "", false );
}
template <class Elem>
int sift_up( int i, std::vector<int>& tree, std::vector<Elem>& leaves, std::function<bool( const Elem&, const Elem& )> parent_win ) {  // parent_win
    int buffer_size = leaves.size();
    int w = i;
    int p = ( w + 1 + buffer_size - 1 ) / 2;
    while ( p && w >= 0 ) {
        if ( tree[p] < 0 || parent_win( leaves[tree[p]], leaves[w] ) ) {
            std::swap( tree[p], w );
        }
        p /= 2;
    }
    return tree[0] = w;
};
std::vector<int> loser_tree_sort( std::vector<Stream::Node>& segments, std::function<bool( const Stream::Node&, const Stream::Node& )> parent_win = std::less<>{} ) {
    int k = segments.size();
    std::vector tree( k, -1 );
    // Initialize, let all non empty segment fail to initialize and fill the winner tree, -1 segment will win
    for ( int i = k - 1; i >= 0; i-- ) {         // reverese order
        sift_up<Stream::Node>( i, tree, segments, parent_win );
    }
    int w = tree[0];
    std::vector<int> merged;
    while ( w >= 0 && !segments[w]->empty() ) {  // There will be no more -1_th segment
        merged.emplace_back( segments[w]->value() );
        segments[w]->next();
        w = sift_up<Stream::Node>( w, tree, segments, parent_win );
    }
    return merged;
}
/* This can never be stable, unless the elements in Stream::Node have an time stamp or strict order */
std::vector<int> huffman_merge_tree( std::vector<Stream::Node>& segments, size_t roads = 16 ) {
    int len = segments.size();
    // len + N = S = roads*N + 1 =>  N = len-1 / (roads-1)
    int v_seg_len = ( ( len - 1 ) % ( roads - 1 ) ) ? roads - ( len - 1 ) % ( roads - 1 ) - 1 : 0;  // Don't add virtual segments if it's already strict k-branch-tree
    // In total: virtual segemnts: v_seg_len, inner segments: 1 + (len-1) / (roads - 1), segments: len
    std::vector<int> tree( segments.size(), -1 );
    std::vector merge_tree( v_seg_len, std::make_shared<Stream>() );
    merge_tree.insert( merge_tree.end(), segments.begin(), segments.end() );
    std::priority_queue pq( []( const Stream::Node& parent, const Stream::Node& current ) { return parent->size() > current->size(); }, merge_tree );
    while ( pq.size() > 1 ) {  // Merge untill 0, end with 1
        std::vector<Stream::Node> to_merge;
        std::cout << "Size: ";
        while ( !pq.empty() && to_merge.size() < roads ) {
            to_merge.push_back( pq.top() );
            std::cout << to_merge.back()->size() << " ";
            pq.pop();
        }
        std::cout << std::endl;
        auto sorted = loser_tree_sort( to_merge );
        print_raw_data( sorted, ( std::format( "Merged {0:d} segments", to_merge.size() ) ).c_str() );
        pq.push( std::make_shared<Stream>( std::move( sorted ) ) );
    }
    return std::move( pq.top()->values );
}
struct use_loser_tree {};
std::vector<Stream::Node> swap_select_sort( use_loser_tree, Stream::Node data_stream, size_t buffer_size = 32 ) {
    std::vector<Stream::Node> init_segments;
    using node_info = std::pair<int, int>;
    std::vector<std::pair<int, int>> leaves( buffer_size, { -1, 0 } );
    std::vector<int> tree( buffer_size, -1 );
    auto parent_win = []( const node_info& parent, const node_info& current ) {  // parent specified in tree and current winner
        // new win order: -1 segment > smaller output id > greater output id > smaller value > bigger value > -1 output id (empty segment)
        // -1 segment in tree will always win,
        // w's -1 output id will always lose,
        // both cases will make w a loser.
        // Then both segment in tree and w segment will have value, compare and take the loser to the tree.
        /* why use <=: new comer should lose the older loser should win to maintain stable sort */
        return current.first < 0 || ( parent.first >= 0 && ( parent.first < current.first || ( parent.first == current.first && parent.second <= current.second ) ) );
    };
    for ( int i = buffer_size; i >= 1; i-- ) {  // reverese order
        if ( !data_stream->empty() ) {
            leaves[i - 1] = { 0, data_stream->value() };
            data_stream->next();
        }
        sift_up<node_info>( i - 1, tree, leaves, parent_win );
    }
    int w = tree[0];
    std::vector<int> buffer;
    while ( w >= 0 && leaves[w].first >= 0 ) {
        size_t output_id = leaves[w].first;
        if ( output_id > init_segments.size() ) {
            if ( !buffer.empty() ) {
                init_segments.push_back( std::make_shared<Stream>( std::move( buffer ) ) );
            }
            buffer.clear();
        }
        int lastPop = leaves[w].second;
        buffer.push_back( lastPop );
        data_stream->next();
        if ( data_stream->empty() ) {
            leaves[w] = { -1, 0 };
        } else {
            int nextValue = data_stream->value();
            leaves[w] = { nextValue >= lastPop ? leaves[w].first : ( leaves[w].first + 1 ), nextValue };
        }
        w = sift_up<node_info>( w, tree, leaves, parent_win );
    }
    if ( !buffer.empty() ) {
        init_segments.push_back( std::make_shared<Stream>( std::move( buffer ) ) );
    }
    return init_segments;
}
std::vector<Stream::Node> swap_select_sort( Stream::Node data_stream, size_t buffer_size = 32 ) {
    std::vector<Stream::Node> init_segments;
    std::priority_queue<int, std::vector<int>, std::greater<>> buffer_heap, next_buffer;
    while ( buffer_heap.size() < buffer_size && !data_stream->empty() ) {
        buffer_heap.push( data_stream->value() );
        data_stream->next();
    }
    while ( !buffer_heap.empty() ) {
        std::vector<int> segment;
        while ( !buffer_heap.empty() ) {
            int lastPop = buffer_heap.top();
            buffer_heap.pop();
            segment.push_back( lastPop );
            if ( !data_stream->empty() ) {
                int nextRead = data_stream->value();
                data_stream->next();
                if ( nextRead >= lastPop ) {
                    buffer_heap.push( nextRead );
                } else {
                    next_buffer.push( nextRead );
                }
            }
        }
        buffer_heap.swap( next_buffer );
        init_segments.push_back( std::make_shared<Stream>( std::move( segment ) ) );
    }
    return init_segments;
}
int main() {
    // TEST LOSER_TREE_SORT
    auto loser_sort_test = random_segments( 77 );
    print_segments( loser_sort_test, "====================================TEST LOSER_TREE_SORT====================================" );
    auto result = loser_tree_sort( loser_sort_test );
    print_raw_data( result, "====================================TEST LOSER_TREE_SORT RESULT=============================" );
    // TEST BEST_MERGE_TREE
    auto best_merge_test = random_segments( 77 );
    print_segments( best_merge_test, "====================================TEST BEST_MERGE_TREE=============================" );
    result = huffman_merge_tree( best_merge_test );
    print_raw_data( result, "====================================TEST BEST_MERGE_TREE RESULT======================" );
    // TEST SWAP_SELECT_SORT
    auto swap_select_sort_test_data = random_data( 1024 );
    print_raw_data( swap_select_sort_test_data, "====================================TEST SWAP_SELECT_SORT======================", false );
    auto swap_select_sort_test = std::make_shared<Stream>( std::move( swap_select_sort_test_data ) );
    auto init_segments = swap_select_sort( swap_select_sort_test, 8 );
    result = huffman_merge_tree( init_segments, 5 );
    print_raw_data( result, "====================================TEST SWAP_SELECT_SORT RESULT======================" );
    // TEST SWAP_SELECT_SORT VIA LOSERTREE
    swap_select_sort_test_data = random_data( 1024 );
    print_raw_data( swap_select_sort_test_data, "====================================TEST SWAP_SELECT_SORT VIA LOSERTREE======================", false );
    swap_select_sort_test = std::make_shared<Stream>( std::move( swap_select_sort_test_data ) );
    init_segments = swap_select_sort( use_loser_tree{}, swap_select_sort_test, 8 );
    result = huffman_merge_tree( init_segments, 5 );
    print_raw_data( result, "====================================TEST SWAP_SELECT_SORT VIA LOSERTREE RESULT======================" );
    return 0;
}
