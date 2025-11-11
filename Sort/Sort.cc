#include <algorithm>
#include <functional>
#include <iostream>
#include <random>
#include <ranges>
#include <vector>
// * ==============================================================================================
namespace Insertion {
    // * ===============================================
    /**
     * @best    O(n)
     * @worst   O(n^2)
     * @average O(n^2)
     * @space   O(1)
     * @stable
     * @apply   Sequence table, linked list
     */
    void direct_insertion_sort( std::vector<int>& data ) {
        for ( size_t i = 1; i < data.size(); i++ ) {
            int j = i;
            while ( j > 0 && data[j] < data[j - 1] ) {  // Find the insert place, and swap to that place
                std::swap( data[j], data[j - 1] );
                j--;
            }
        }
    }
    // * ===============================================
    /**
     * @best    O(nlog2(n))
     * @worst   O(n^2)
     * @average O(n^2)
     * @space   O(1)
     * @stable
     * @apply   Sequence table only
     */
    void half_insertion_sort( std::vector<int>& data ) {
        for ( size_t i = 1; i < data.size(); i++ ) {
            // From min to max, find the insertion position of data[i]
            int j = i;
            int l = 0, r = i - 1;
            while ( l <= r ) {
                int mid = ( l + r ) / 2;
                if ( data[i] < data[mid] ) {
                    j = mid;
                    r = mid - 1;
                } else {
                    l = mid + 1;
                }
            }
            for ( int k = i; k > j; k-- ) {
                std::swap( data[k - 1], data[k] );  // Still cost much time to move the elements.
            }
        }
    }
    // * ===============================================
    /**
     * gap
     * sequnce on every iteration: n/gap
     *                  best: O(n/gap)
     *                  worst: O((n/gap)^2)
     * total: Σ O(f(gap))
     * @best    ~O(n)
     * @worst   O(n^2)
     * @average O(n^1.3~1.5)
     * @space   O(1)
     * @unstable
     * @apply   Sequence table only
     */
    void shell_sort( std::vector<int>& data ) {
        for ( int gap = data.size() / 2; gap > 0; gap /= 2 ) {
            // for ( int gap = data.size() / 2; gap > 0; gap -- ) {
            for ( size_t i = gap; i < data.size(); i += gap ) {
                int j = i;
                while ( j > 0 && data[j] < data[j - gap] ) {
                    std::swap( data[j], data[j - gap] );
                    j -= gap;
                }
            }
        }
    }
}  // namespace Insertion
// * ==============================================================================================
namespace Exchange {
    // * ===============================================
    /**
     * @best    O(n) - if no swap in one bubble, stop sorting
     * @worst   O(n^2)
     * @average O(n^2)
     * @space   O(1)
     * @stable
     * @apply   Sequence table, linked list
     */
    void bubble_sort( std::vector<int>& data ) {
        for ( int i = data.size() - 1; i > 0; i-- ) {  // Bubble to end
            bool swapped = false;
            for ( int j = 0; j < i; j++ ) {
                if ( data[j] > data[j + 1] ) {
                    std::swap( data[j], data[j + 1] );
                    swapped = true;
                }
            }
            if ( !swapped ) {
                break;
            }
        }
    }
    // * ===============================================
    /**
     * @best    O(nlog2(n)) even data is ordered, still cost much time
     * @worst   O(n^2)
     * @average O(nlog2(n))
     * @space   O(log2(n))
     * @unstable pivot selection may accidentally swap it to the place after another element with the same pivot value
     * @apply   Sequence table (random access only)
     */
    void quick_sort( std::vector<int>& data, int l, int r ) {  // two swap method
        if ( l >= r ) {
            return;
        }
        int i = l, j = r, pivot = data[l];
        while ( i < j ) {
            while ( j > i && data[j] >= pivot ) {
                j--;
            }
            while ( i < j && data[i] <= pivot ) {
                i++;
            }
            std::swap( data[i], data[j] );
        }
        std::swap( data[i], data[l] );  // pivot's place is found, but it is not swapped at the very beggining, apply an additional swap
        quick_sort( data, l, i - 1 );
        quick_sort( data, i + 1, r );
    }
    // hole method, take the pivot out, then fill will a smaller/greater.
    // void quick_sort( std::vector<int>& data, int l, int r ) {
    //     if ( l >= r ) {
    //         return;
    //     }
    //     int i = l, j = r, pivot = data[l];
    //     while ( i < j ) {
    //         while ( j > i && data[j] >= pivot ) { // take only the strong less order
    //             j--;
    //         }
    //         data[i] = data[j];
    //         while ( i < j && data[i] <= pivot ) {// take only the strong greater order
    //             i++;
    //         }
    //         data[j] = data[i];
    //     }
    //     data[i] = pivot;
    //     quick_sort( data, l, i - 1 );
    //     quick_sort( data, i + 1, r );
    // }
}  // namespace Exchange
// * ==============================================================================================
namespace Select {
    // * ===============================================
    /**
     * @best    O(n^2)
     * @worst   O(n^2)
     * @average O(n^2)
     * @space   O(1)
     * @unstable ~a a min -> min a ~a
     * @apply   Sequence table, linked list
     */
    void plain_select_sort( std::vector<int>& data ) {
        int len = int( data.size() );
        for ( int i = 0; i < len; i++ ) {
            int min = i;
            for ( int j = i + 1; j < len; j++ ) {
                if ( data[j] < data[min] ) {
                    min = j;
                }
            }
            std::swap( data[i], data[min] );
        }
    }
    // * ===============================================
    /** Heap sort
     * @best    O(nlogn)
     * @worst   O(nlogn)
     * @average O(nlogn)
     * @space   O(1)
     * @unstable
     * @apply   Sequence table
     */
    /* Pop helper, init helper */
    void sift_down( std::vector<int>& data, size_t i ) {
        while ( i < data.size() ) {
            size_t l = i * 2 + 1, r = i * 2 + 2;
            size_t smallest = i;
            if ( l < data.size() && data[l] < data[smallest] ) {
                smallest = l;
            }
            if ( r < data.size() && data[r] < data[smallest] ) {
                smallest = r;
            }
            if ( smallest != i ) {
                std::swap( data[i], data[smallest] );
                i = smallest;
            } else {  // In order, break sift down
                break;
            }
        }
    }
    /* Push helper */
    void sift_up( std::vector<int>& data, size_t i ) {
        while ( i && data[i] < data[( i - 1 ) / 2] ) {  // Stop if already in order
            std::swap( data[i], data[( i - 1 ) / 2] );  // Indexed from 0, l = 2*i+1, r = 2*i+2, p = (i-1)/2
            i = ( i - 1 ) / 2;
        }
    }
    /**
     * @best    O(n)
     * @worst   O(n)
     * @average O(n)
     * @space   O(1)
     * @unstable
     * @apply   Sequence table
     */
    void heapify( std::vector<int>& data ) {  // From n/2 sift down can hepify in (Σ 1 2^h, ... , h*1 / n/2) , where h=log2(n)~1, so it is just ~ O(n)
        // Maintain data[0] is root;
        int len = int( data.size() );
        for ( int i = ( len - 1 ) / 2; i >= 0; i-- ) {  // ajust each non-leave to leave in path
            sift_down( data, i );
        }
    }
    /**
     * @best    O(n)
     * @worst   O(nlogn)
     * @average O(nlogn)
     * @space   O(1)
     * @unstable
     * @apply   Sequence table
     */
    void heapify_nlogn( std::vector<int>& data ) {
        // Maintain data[0] is root;
        int len = int( data.size() );
        for ( int i = 1; i < len; i++ ) {  // insert data[i] to root
            sift_up( data, i );
        }
    }
    /**
     * @best    O(1)
     * @worst   O(logn)
     * @average O(logn)
     * @space   O(1)
     * @unstable
     * @apply   Sequence table
     */
    void heappush( std::vector<int>& data, int elem ) {
        data.push_back( elem );
        sift_up( data, data.size() - 1 );
    }
    /**
     * @best    O(logn)
     * @worst   O(logn)
     * @average O(logn)
     * @space   O(1)
     * @unstable
     * @apply   Sequence table
     */
    int heappop( std::vector<int>& data ) {
        int val = data[0];
        data[0] = data.back();
        data.pop_back();
        sift_down( data, 0 );
        return val;
    }
    void heap_sort_test( std::vector<int> data ) {
        std::vector<int> copy = data, tmp;
        std::cout << "Heapify:\n";
        heapify( data );
        while ( !data.empty() ) {
            std::cout << heappop( data ) << " ";
        }
        std::cout << "\n"
                  << "Insert:\n";
        for ( int e : copy ) {
            heappush( tmp, e );
        };
        while ( !tmp.empty() ) {
            std::cout << heappop( tmp ) << " ";
        }
        std::cout << "\n";
    }
    // * ===============================================
}  // namespace Select
// * ==============================================================================================
// * ===============================================
/**
 * @best    O(nlogn)
 * @worst   O(nlogn)
 * @average O(nlogn)
 * @space   O(n)
 * @stable
 * @apply   Sequence table
 */
void merge_sort( std::vector<int>& data ) {
    if ( data.size() <= 1 ) return;
    std::vector<std::vector<int>> segments;
    for ( int num : data ) {
        segments.push_back( { num } );
    }
    while ( segments.size() > 1 ) {
        std::vector<std::vector<int>> merged_segments;
        for ( size_t i = 0; i < segments.size(); i += 2 ) {
            std::vector<int>& A = segments[i];
            if ( i + 1 < segments.size() ) {
                std::vector<int>& B = segments[i + 1];
                merged_segments.push_back( {} );
                auto& merged = merged_segments.back();
                merged.reserve( A.size() + B.size() );
                auto a = A.begin(), b = B.begin();
                while ( a != A.end() && b != B.end() ) {
                    if ( *a <= *b ) {  // stable
                        merged_segments.rbegin()->push_back( *( a++ ) );
                    } else {
                        merged_segments.rbegin()->push_back( *( b++ ) );
                    }
                }
                merged.insert( merged.end(), a, A.end() );
                merged.insert( merged.end(), b, B.end() );
            } else {
                merged_segments.push_back( std::move( A ) );
            }
        }
        segments = std::move( merged_segments );
    }
    data = std::move( segments[0] );
}
// * ===============================================
/**
 * d: digit count
 * n: total numbers
 * r: radix of each number
 * @best    O(d(n+r))
 * @worst   O(d(n+r))
 * @average O(d(n+r))
 * @space   O(r+n)
 * @unstable
 * @apply   Sequence table
 */
void radix_sort( std::vector<int>& data, int limit = 3 ) {
    std::vector<int> temp( data.size() );
    for ( int i = 0, div = 1; i < limit; i++, div *= 10 ) {
        std::vector count( 10, 0 );
        for ( int num : data ) {                                        // Use accumulated count to optimize space from O(r*n) to O(r)
            count[( num / div ) % 10]++;
        }
        std::partial_sum( count.begin(), count.end(), count.begin() );  // 1 -> 1, 2+1 -> 2, ..., n+n-1 -> n
        for ( int num : std::views::reverse( data ) ) {
            temp[--count[( num / div ) % 10]] = num;
        }
        data.swap( temp );
    }
}
// * ===============================================
void test( std::function<void( std::vector<int>& )> f, std::vector<int> data ) {
    f( data );
    for ( auto i : data ) {
        std::cout << i << " ";
    }
    std::cout << "\n";
}
// * ===============================================
int main() {
    std::random_device rd;
    std::mt19937 gen( rd() );
    std::uniform_int_distribution<int> u_distri( 0, 100 );
    std::vector<int> data;
    for ( int _ : std::views::iota( 0, 50 ) ) {
        data.push_back( u_distri( gen ) );
    }
    using namespace Insertion;
    test( &direct_insertion_sort, data );
    test( &half_insertion_sort, data );
    test( &shell_sort, data );
    using namespace Exchange;
    test( &bubble_sort, data );
    test( std::bind( &quick_sort, std::placeholders::_1, 0, int( data.size() ) - 1 ), data );
    using namespace Select;
    test( &plain_select_sort, data );
    heap_sort_test( data );
    // Merge Sort
    test( &merge_sort, data );
    // Radix Sort
    test( std::bind( &radix_sort, std::placeholders::_1, 3 ), data );
}
