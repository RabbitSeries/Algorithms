#include <bits/stdc++.h>
using namespace std;
struct obj {
    int val;
    auto operator<=>( const obj& ) const = default;
};
/**
 * @brief
 * @ASL on success: avg 1,2,...,n = (n+1)/2
 * @ASL on failure: n
 * If the search table is ordered:
 * @ASL on success: (n+1)/2
 * @ASL on failure: avg 1,2,...,n = (n+1)/2
 * @return index or -1
 */
int Linear( obj const& target, std::vector<obj> const& table, bool ordered ) {
    for ( int i = 0; const obj& elem : table ) {
        if ( target == elem ) {
            return i;
        } else if ( ordered && target > elem ) {
            break;
        }
        i++;
    }
    return -1;
}
/**
 * @brief
 * @ASL on success: log2(n)
 * @ASL on failure: log2(n)
 * @param table Ascending ordered
 * @return index or -1
 */
int Binary( obj const& target, std::vector<obj> const& table ) {
    int l = 0, r = (int)table.size();
    while ( l <= r ) {
        int mid = l + ( ( r - l ) >> 1 );
        auto cmp = target <=> table[mid];
        if ( cmp < 0 ) {
            r = mid - 1;
        } else if ( cmp > 0 ) {
            l = mid + 1;
        } else if ( cmp == 0 ) {
            if ( l == r ) {
                return l;
            } else {
                r = mid - 1;  // Find the first satisfied element.
            }
        }
    }
    return -1;
}
/**
 * @brief
 * n = table.size()
 * m = index.size()
 * If perfrom linear search in indexed array:
 * @ASL on success: (m+1)/2 + (n/m+1)*1/2
 * @ASL on failure: m + n/m
 * If perform binary search in indexed array (requires a O(mlog2(m)) pre-sort):
 * @ASL on success: log2(m) + (n/m+1)*1/2
 * @ASL on failure: log2(m) + n/m
 * @param target Search target
 * @param table Unordered table
 * @param index Block index, ascending order by largest elem, (block start index, largest elem in block), block length is table.size()/index.size()
 * @return
 */
int IndexedBlock( obj const& target, std::vector<obj> const& table, std::vector<std::pair<int, const obj&>> const& index ) {
    int l = 0, r = (int)index.size();
    int best = -1;
    while ( l <= r ) {
        int mid = l + ( ( r - l ) >> 1 );
        auto cmp = target <=> index[mid].second;
        if ( cmp <= 0 ) {
            best = mid;
            r = mid - 1;
        } else if ( cmp > 0 ) {
            l = mid + 1;
        }
    }
    if ( best == -1 ) {
        return -1;
    }
    int blockLen = (int)( table.size() / index.size() );
    int beginIndex = index[best].first;
    int endIndex = std::min( beginIndex + blockLen, (int)index.size() );
    for ( int i = beginIndex; i <= endIndex; i++ ) {
        if ( target == table[i] ) {
            return i;
        }
    }
    return -1;
}
/**
 * @brief
 * Summary:
 * Search Algorithm|ASL on sucess       |ASL on failure
 * Linear Search   |(n+1)/2             |n if table is not ordered else (n+1)/2
 * Binary Search   |log2(n)             |log2(n)
 * Indexed Block   |log2(m)+(n/m+1)*1/2 |log2(m)+n/m
 */
