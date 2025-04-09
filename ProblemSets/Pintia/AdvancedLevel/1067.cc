#include <bits/stdc++.h>
using namespace std;
int main() {
    int vCnt, cnt = 0;
    cin >> vCnt;
    vector<int> displaceMent( vCnt );
    for ( int i = 0; i < vCnt; i++ ) {
        int tmp;
        cin >> tmp;
        // cin >> displaceMent[i];
        displaceMent[tmp] = i;
    }
    for ( int i = 1; i < vCnt; i++ ) {
        if ( displaceMent[i] != i ) {
            while ( displaceMent[0] != 0 ) {
                swap( displaceMent[0], displaceMent[displaceMent[0]] );
                cnt++;
            }
            if ( displaceMent[i] != i ) {
                cnt++;
                swap( displaceMent[0], displaceMent[i] );
            }
        }
    }
    cout << cnt;
}