#include <bits/stdc++.h>
using namespace std;
int main() {
    int vCnt, cnt = 0, zeroPos;
    cin >> vCnt;
    vector<int> valuePosition( vCnt );
    for ( int i = 0, t; i < vCnt; i++ ) {
        cin >> t;
        valuePosition[t] = i;
    }
    for ( int i = 1; i < vCnt; i++ ) {
        while ( valuePosition[0] != 0 ) {                               // While number 0 is not at 0_th place ( k = valuePosition[0] )
            swap( valuePosition[0], valuePosition[valuePosition[0]] );  // number 0 swap to number k's position ( greedy, extra swaps is definitely less effective or equivalent effective )
            cnt++;
        }  // number 0 is at 0_th position
        if ( valuePosition[i] != i ) {                   // start from 1 position search for displaced numbers
            swap( valuePosition[0], valuePosition[i] );  // swap 0 with number i, 0 will only swap with a number that should be placed at 0's current position.
            cnt++;                                       // But current found i is not in place, so 0 won't return to swapped position then replace i, i can safely continue to search other values
        }
    }
    cout << cnt;
}