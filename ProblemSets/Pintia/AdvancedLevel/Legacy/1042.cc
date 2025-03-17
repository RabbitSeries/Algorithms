#include <bits/stdc++.h>
using namespace std;
int main() {
    vector<int> order( 54 );
    vector<pair<int, int>> cards( 54 );
    int shuffle;
    cin >> shuffle;
    for ( int i = 0; i < 54; i++ ) {
        cin >> order[i];
        cards[i].second = i;
    }
    for ( int i = 0; i < shuffle; i++ ) {
        for ( int i = 0; i < 54; i++ )
            cards[i].first = order[i];
        sort( cards.begin(), cards.end() );  // If the target permutation order is known beforehand, a tmp swapping space were used. O(n * nlogn) -> O(n * n)
    }
    cout << accumulate( cards.begin(), cards.end(), string( "" ), []( string const& init, pair<int, int> const& curcard ) {
                return init + " " + string( 1, ( curcard.second / 13 )["SHCDJ"] ) + ( stringstream() << ( curcard.second % 13 + 1 ) ).str();
            } ).substr( 1 );
}