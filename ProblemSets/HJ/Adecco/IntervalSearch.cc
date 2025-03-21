#include <bits/stdc++.h>
using namespace std;
int main() {
    vector<pair<int, int>> inputItvList{ { 1, 4 }, { 2, 3 }, { 10, 12 }, { 4, 5 } };
    sort( inputItvList.begin(), inputItvList.end(), []( pair<int, int> const& p1, pair<int, int> const& p2 ) {
        return p1.first < p2.first;
    } );
    vector<pair<int, int>> mergeList{ inputItvList[0] };
    for ( int i = 1; i < inputItvList.size(); i++ ) {
        auto const& curItv = inputItvList[i];
        if ( curItv.first > mergeList.back().second ) {
            mergeList.emplace_back( curItv.first, curItv.second );
        } else if ( curItv.first <= mergeList.back().second ) {
            mergeList.back().second = max( mergeList.back().second, curItv.second );
        }
    }
    for ( auto const& c : mergeList )
        cout << c.first << "," << c.second << " ";
    return 0;
}

// input
// [1,4] [4,5]
// output
// [1,5]
