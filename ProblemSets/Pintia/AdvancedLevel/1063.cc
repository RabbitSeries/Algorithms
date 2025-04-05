#include <bits/stdc++.h>
using namespace std;
int main() {
    int sCnt, qCnt, M, val;
    cin >> sCnt;
    vector<set<int>> setList( sCnt + 1 );
    for ( int i = 1; i <= sCnt; i++ ) {
        cin >> M;
        for ( int j = 0; j < M; j++ ) {
            cin >> val;
            setList[i].emplace( val );
        }
    }
    cin >> qCnt;
    for ( int i = 0; i < qCnt; i++ ) {
        int s1, s2;
        cin >> s1 >> s2;
        vector<int> Nt, Nc;
        set<int> const &set1 = setList[s1], &set2 = setList[s2];
        set_union( set1.begin(), set1.end(), set2.begin(), set2.end(), back_inserter( Nt ), less<>{} );
        set_intersection( set1.begin(), set1.end(), set2.begin(), set2.end(), back_inserter( Nc ) );
        cout << fixed << setprecision( 1 ) << 100.0 * Nc.size() / Nt.size() << "%" << endl;
    }
}