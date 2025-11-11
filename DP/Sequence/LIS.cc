// Longest Increase Subsequence
#include <algorithm>
#include <climits>
#include <deque>
#include <vector>
std::vector<int> LIS( std::vector<int> const& arr ) {
    std::vector dp( arr.size(), 1 ), pre( arr.size(), -1 );  // Max length endwith arr[i], LIS connection pre
    int p = 0, max_len = 1;
    for ( size_t i = 0; i < arr.size(); i++ ) {
        for ( size_t j = 0; j < i; j++ ) {
            if ( arr[i] > arr[j] && dp[j] + 1 > dp[i] ) {    // arr[i] can extend LIS at dp[j]
                dp[i] = dp[j] + 1;
                pre[i] = j;
            }
            if ( dp[i] > max_len ) {
                p = i;
                max_len = dp[i];
            }
        }
    }
    std::vector<int> res;
    while ( p != -1 ) {
        res.push_back( arr[p] );
        p = pre[p];
    }
    std::reverse( res.begin(), res.end() );
    return res;
}
std::vector<int> LNDS( std::vector<int> const& arr ) {
    std::vector dp( arr.size(), 1 ), pre( arr.size(), -1 );  // Same as above
    int p = 0, max_len = 1;
    for ( size_t i = 0; i < arr.size(); i++ ) {
        for ( size_t j = 0; j < i; j++ ) {
            if ( arr[i] >= arr[j] && dp[j] + 1 > dp[i] ) {   // arr[i] can extend LIS at dp[j], this time, in Non-Descreasing order
                dp[i] = dp[j] + 1;
                pre[i] = j;
            }
            if ( dp[i] > max_len ) {
                p = i;
                max_len = dp[i];
            }
        }
    }
    std::vector<int> res;
    while ( p != -1 ) {
        res.push_back( arr[p] );
        p = pre[p];
    }
    std::reverse( res.begin(), res.end() );
    return res;
}
std::vector<int> LIS_LowerBound( std::vector<int> const& arr ) {
    // tail[len-1].first means minimal tail element in each len-size LIS
    // tail[i].second: pos[i] means tail[i]'s value is arr[pos[i]]
    // pre is same as above
    std::vector pre( arr.size(), -1 );
    std::vector tail{ std::pair{ arr[0], 0 } };
    for ( size_t i = 1; i < arr.size(); i++ ) {
        // 0. Equal should be replaced
        // 1. tail is strictly inceasing.
        // 2. If there is a longer LIS, then arr[i] will be pushed back, thus tail will change, so tail's length is LIS's length.
        // 3. Tail is NOT a subsequence of arr.
        // An iterator pointing to the first element <em>not less than</em> val // the fist t.first >= v, but the impl is ugly
        auto ins = std::lower_bound( tail.begin(), tail.end(), arr[i],
                                     []( std::pair<int, int> const& t, int v ) {  // Provide a strict less comparator to obtain not less result
                                         return t.first < v;                      // God, this logic is so twisting
                                     } );                                         // if _Comp(middle, val) _first = mid + 1 (exclude mid) else len = mid include mid
        if ( ins == tail.end() ) {
            pre[i] = tail.back().second;
            tail.emplace_back( arr[i], i );
        } else {
            int tail_pos = ins - tail.begin();                                    // tail_pos + 1 is LIS's length of i
            tail[tail_pos] = { arr[i], i };
            if ( tail_pos > 0 ) {                                                 // LIS's length > 1, connect to former tail
                pre[i] = tail[tail_pos - 1].second;
            }
        }
    }
    std::vector<int> res{ tail.back().first };
    int p = pre[tail.back().second];
    while ( p != -1 ) {
        res.push_back( arr[p] );
        p = pre[p];
    }
    std::reverse( res.begin(), res.end() );
    return res;
}
// Longest Non-Descreasing Subsequence
std::vector<int> LNDS_UpperBound( std::vector<int> const& arr ) {
    std::vector pre( arr.size(), -1 );           // Same as above
    std::vector tail{ std::pair{ arr[0], 0 } };  // This time, tail is Non_Decreasing order
    for ( size_t i = 1; i < arr.size(); i++ ) {
        // An iterator pointing to the first element greater than __val
        // Equal should be pushed back, shoud return tail.end, so t.first > vs.
        auto ins = std::upper_bound( tail.begin(), tail.end(), arr[i],
                                     []( int v, const std::pair<int, int>& t ) {  // Provide a strict greater comparator to obtain the first greater iterator.
                                         return t.first > v;
                                     } );                                         // if _Comp(val ,middle) len = mid (include mid) else first = mid + 1 (exclude)
        // Same as above
        if ( ins == tail.end() ) {
            pre[i] = tail.back().second;
            tail.emplace_back( arr[i], i );
        } else {
            int tail_pos = ins - tail.begin();
            tail[tail_pos] = { arr[i], i };
            if ( tail_pos > 0 ) {
                pre[i] = tail[tail_pos - 1].second;
            }
        }
    }
    std::vector<int> res{ tail.back().first };
    int p = pre[tail.back().second];
    while ( p != -1 ) {
        res.push_back( arr[p] );
        p = pre[p];
    }
    std::reverse( res.begin(), res.end() );
    return res;
}
