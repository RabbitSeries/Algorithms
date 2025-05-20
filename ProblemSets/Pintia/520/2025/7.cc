#include <bits/stdc++.h>
using namespace std;
int main() {
    int N;
    cin >> N;
    int profit[] = { 0, 1, 1, 1, 0, 1, 0 };
    int houseworkCnt[] = { 0, 0, 0, 0, 0, 0, 0 };
    int couple[] = { 0, 0 };
    for ( int i = 0; i < N; i++ ) {
        int person, work;
        cin >> work >> person;
        couple[person] += profit[work];
        houseworkCnt[work] += profit[work];
    }
    if ( couple[0] == couple[1] ) {
        cout << "Love " << couple[0] << endl;
    } else if ( couple[0] > couple[1] ) {
        printf( "%d %d\n", 0, couple[0] );
    } else {
        printf( "%d %d\n", 1, couple[1] );
    }
    int maxWork = 0;
    vector<int> res;
    for ( int i = 1; i < 6; i++ ) {
        if ( houseworkCnt[i] > maxWork ) {
            res.clear();
            res.emplace_back( i );
        } else if ( houseworkCnt[i] == maxWork ) {
            res.emplace_back( i );
        }
        maxWork = max( maxWork, houseworkCnt[i] );
    }
    cout << maxWork;
    for ( int n : res ) {
        cout << " " << n;
    }
}