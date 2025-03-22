#include <bits/stdc++.h>
using namespace std;
int main() {
    int betCnt, curBet, res = -1;
    vector<int> notDulp;
    set<int> bet;
    cin >> betCnt;
    for ( int i = 0; i < betCnt; i++ ) {
        cin >> curBet;
        if ( bet.contains( curBet ) ) {
            auto pos = find_if( notDulp.begin(), notDulp.end(), [=]( int cur ) { return cur == curBet; } );
            if ( pos != notDulp.end() )
                notDulp.erase( pos );
            notDulp.empty() ? res = -1 : res = notDulp.front();
            continue;
        }
        if ( res == -1 ) res = curBet;
        notDulp.push_back( curBet );
        bet.insert( curBet );
    }
    ( res == -1 ? ( cout << "None" ) : ( cout << res ) );
}