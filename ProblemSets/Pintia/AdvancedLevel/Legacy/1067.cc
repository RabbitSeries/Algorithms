#include <bits/stdc++.h>
using namespace std;
map<int, int> displaceMent;
void swapZero( int num, vector<int>& vList ) {
    int targetPos = displaceMent[num], zeroPosition;
    if ( displaceMent.contains( 0 ) ) {
        zeroPosition = displaceMent[0];
    } else {
        zeroPosition = 0;
    }
    displaceMent[0] = targetPos;
    displaceMent[num] = zeroPosition;
    if ( displaceMent.at( 0 ) == 0 ) {
        displaceMent.erase( 0 );
    }
    if ( displaceMent.at( num ) == num ) {
        displaceMent.erase( num );
    }
    swap( vList[zeroPosition], vList[targetPos] );
}
int main() {
    int vCnt;
    cin >> vCnt;
    vector<int> vList( vCnt );
    for ( int i = 0; i < vCnt; i++ ) {
        cin >> vList[i];
        if ( vList[i] != i ) {
            displaceMent[vList[i]] = i;
        }
    }
    int id = 0;
    while ( !displaceMent.empty() ) {
        id++;
        if ( displaceMent.contains( 0 ) ) {
            swapZero( displaceMent[0], vList );
        } else {
            swapZero( displaceMent.begin()->first, vList );
        }
    }
    cout << id;
}