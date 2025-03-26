#include <bits/stdc++.h>
using namespace std;
int main() {
    int pCnt, qCnt;
    cin >> pCnt >> qCnt;
    using pInfo = pair<pair<string, int>, int>;
    vector<pInfo> pList( pCnt ), filtered;
    for ( int i = 0; i < pCnt; i++ ) {
        cin >> pList[i].first.first >> pList[i].first.second >> pList[i].second;
    }
    sort( pList.begin(), pList.end(), []( pInfo const& p1, pInfo const& p2 ) {
        if ( p1.second != p2.second )
            return p1.second > p2.second;
        else if ( p1.first.second != p2.first.second )
            return p1.first.second < p2.first.second;
        else
            return p1.first.first < p2.first.first;
    } );
    vector<int> ageCnt( 201 );
    for ( pInfo const& p : pList ) {
        if ( ageCnt[p.first.second] < 100 ) {
            filtered.emplace_back( p );
            ageCnt[p.first.second]++;
        }
    }
    stringstream buf;
    for ( int i = 0; i < qCnt; i++ ) {
        buf << "Case #" << ( i + 1 ) << ":" << endl;
        int curQ, lAge, rAge, outCnt = 0;
        cin >> curQ >> lAge >> rAge;
        for ( auto const& p : filtered ) {
            if ( p.first.second >= lAge && p.first.second <= rAge && outCnt < curQ ) {
                buf << p.first.first << " " << p.first.second << " " << p.second << endl;
                outCnt++;
            }
        }
        if ( !outCnt ) {
            buf << "None" << endl;
        }
    }
    cout << buf.str();
}