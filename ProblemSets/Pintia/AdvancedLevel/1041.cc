#include <bits/stdc++.h>
using namespace std;
int main() {
    int betCnt;
    cin >> betCnt;
    vector<int> uniqueList( 10001, 0 ), betList( betCnt );
    for ( int i = 0; i < betCnt; i++ ) {
        cin >> betList[i];
        uniqueList[betList[i]]++;
    }
    auto pos = find_if( betList.begin(), betList.end(), [&]( int curBet ) { return uniqueList[curBet] == 1; } );
    ( pos == betList.end() ? ( cout << "None" ) : ( cout << *pos ) );
}