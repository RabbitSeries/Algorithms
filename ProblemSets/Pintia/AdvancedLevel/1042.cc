#include <bits/stdc++.h>
using namespace std;
int main() {
    vector<int> order( 54 ), cards( 54 ), tmp( 54 );
    int shuffle;
    cin >> shuffle;
    for ( int i = 0; i < 54; i++ ) {
        cin >> order[i];
        cards[i] = i;
    }
    for ( int i = 0; i < shuffle; i++ ) {
        for ( int j = 0; j < 54; j++ )
            tmp[j] = cards[j];
        for ( int j = 0; j < 54; j++ )
            cards[order[j] - 1] = tmp[j];
    }
    cout << accumulate( cards.begin(), cards.end(), string( "" ), []( string const& init, int const& c ) {
                return init + " " + string( 1, ( c / 13 )["SHCDJ"] ) + ( stringstream() << ( c % 13 + 1 ) ).str();
            } ).substr( 1 );
}