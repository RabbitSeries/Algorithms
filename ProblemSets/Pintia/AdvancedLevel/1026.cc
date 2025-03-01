#include <bits/stdc++.h>
using namespace std;
struct cstInfo {
    int arrT = 0, srvT = 0;
    bool isVip = 0;
    friend istream& operator>>( istream& in, cstInfo& c ) {
        int hh, mm, ss;
        scanf( "%2d:%2d:%2d%d%d", &hh, &mm, &ss, &c.srvT, &c.isVip );
        c.arrT = hh * 3600 + mm * 60 + ss;
        c.srvT = min( 120 * 60, c.srvT * 60 );
        return in;
    };
};

vector<int> nextTable( vector<int> const& tableTime ) {
    int minT = INT_MAX;
    vector<int> idList;
    for ( int i = 0; i < tableTime.size(); i++ ) {
        if ( tableTime[i] < minT ) {
            minT = tableTime[i];
            idList.clear();
            idList.push_back( i );
        } else if ( tableTime[i] == minT ) {
            idList.push_back( i );
        }
    }
    return idList;
}

int main() {
    int cstCnt, tableCnt, vipTableCnt;
    cin >> cstCnt;
    vector<cstInfo> cstList( cstCnt );
    for ( int i = 0; i < cstCnt; i++ ) cin >> cstList[i];
    sort( cstList.begin(), cstList.end(), []( const cstInfo& c1, const cstInfo& c2 ) { return c1.arrT < c2.arrT; } );
    cin >> tableCnt >> vipTableCnt;
    set<int> vipTableList;
    for ( int i = 0; i < vipTableCnt; i++ ) {
        int curTable;
        cin >> curTable;
        vipTableList.insert( curTable - 1 );
    }

    vector<int> tableTime( tableCnt, 8 * 60 * 60 ), srvCnt( tableCnt, 0 );
    vector<bool> distributed( cstCnt, false );
    vector<array<int, 3>> resList;
    for ( size_t curId = 0; curId < cstList.size(); ) {
        if ( distributed[curId] ) {
            curId++;
            continue;
        }
        if ( cstList[curId].arrT >= 21 * 60 * 60 ) break;
        for ( int& t : tableTime ) t = max( t, cstList[curId].arrT );  // free table
        vector<int> nextIdList = nextTable( tableTime );

        int distributeId = curId, srvT = tableTime[nextIdList.front()], nextTableId = nextIdList.front();
        if ( srvT >= 21 * 60 * 60 ) break;
        for ( int tId : nextIdList ) {
            if ( vipTableList.count( tId ) ) {
                for ( size_t cstId = curId; cstId < cstList.size() && srvT >= cstList[cstId].arrT; cstId++ ) {
                    if ( cstList[cstId].isVip && !distributed[cstId] ) {  // When a vip table is open, have vip in queue
                        distributeId = cstId;
                        nextTableId = tId;
                        break;
                    }
                }
                break;
            }
        }
        cstInfo nextCst = move( cstList[distributeId] );
        srvT = max( srvT, nextCst.arrT );
        tableTime[nextTableId] = srvT + nextCst.srvT;  // Distribute as any player
        distributed[distributeId] = true;
        resList.push_back( { nextCst.arrT, srvT, srvT - nextCst.arrT } );
        srvCnt[nextTableId]++;
        if ( distributeId == curId ) curId++;
    }

    sort( resList.begin(), resList.end(), []( array<int, 3> const& res1, array<int, 3> const& res2 ) { return res1[1] < res2[1]; } );
    for ( auto& [arrT, srvT, wT] : resList )
        printf( "%02d:%02d:%02d %02d:%02d:%02d %d\n", arrT / 3600, arrT / 60 % 60, arrT % 60, srvT / 3600, srvT / 60 % 60, srvT % 60, ( wT + 30 ) / 60 );
    for ( int i = 0; i < srvCnt.size(); i++ )
        cout << srvCnt[i] << ( i == srvCnt.size() - 1 ? "" : " " );
    return 0;
}