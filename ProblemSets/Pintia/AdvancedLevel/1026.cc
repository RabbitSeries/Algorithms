#include <bits/stdc++.h>
using namespace std;
struct cstInfo {
    int arrT = 0, srvT = 0;
    bool isVip = 0;
    friend istream& operator>>( istream& in, cstInfo& c ) {
        string buf;
        getline( in, buf );
        c.arrT += stoi( buf.substr( 0, 3 ) ) * 60 * 60;
        c.arrT += stoi( buf.substr( 3, 6 ) ) * 60;
        c.arrT += stoi( buf.substr( 6, 9 ) );
        stringstream( buf.substr( 9 ) ) >> c.srvT >> c.isVip;
        c.srvT *= 60;
        c.srvT = min( 120 * 60, c.srvT );
        return in;
    };
};

int cstCnt, tableCnt, vipTableCnt;

vector<cstInfo> cstList;
set<int> vipTableList;


vector<int> tableTime;
vector<array<int, 3>> resList;
vector<int> srvCnt;

void input() {
    cin >> cstCnt;
    getchar();
    for( int i = 0; i < cstCnt; i++ ) {
        cstInfo cst;
        cin >> cst;
        cstList.push_back( cst );
    }
    sort( cstList.begin(), cstList.end(), []( const  cstInfo& c1, const cstInfo& c2 ) {
        return c1.arrT < c2.arrT;
    } );

    string buf;
    getline( cin, buf );
    stringstream( buf ) >> tableCnt >> vipTableCnt;

    for( int i = 0; i < vipTableCnt; i++ ) {
        int curTable;
        cin >> curTable;
        vipTableList.insert( curTable - 1 );
    }

    tableTime = vector<int>( tableCnt, 8 * 60 * 60 );
    srvCnt = vector<int>( tableCnt, 0 );
}

vector<int>  nextTable() {
    int minT = INT_MAX;
    vector<int> idList;
    for( int i = 0; i < tableTime.size(); i++ ) {
        if( tableTime[i] < minT ) {
            minT = tableTime[i];
            idList.clear();
            idList.push_back( i );
        } else if( tableTime[i] == minT ) {
            idList.push_back( i );
        }
    }
    return idList;
}

bool findTable() {
    if( cstList.empty() ) {
        return false;
    }
    cstInfo nextCst = move( cstList.front() );
    if( nextCst.arrT >= 21 * 60 * 60 ) {
        return false;
    }
    int queryTime = nextCst.arrT;
    for( int& t : tableTime ) {
        if( t < queryTime ) {
            // free table
            t = queryTime;
        }
    }

    vector<int> nextIdList = move( nextTable() );
    int srvT = tableTime[nextIdList.front()];
    if( srvT >= 21 * 60 * 60 ) {
        return false;
    }
    for( int tId : nextIdList ) {
        if( vipTableList.count( tId ) ) {
            int cstId = 0;
            while( cstId < cstList.size() && srvT >= cstList[cstId].arrT ) {
                if( cstList[cstId].isVip ) {
                    // When a vip table is open, have vip in queue
                    nextCst = cstList[cstId];
                    cstList.erase( cstList.begin() + cstId );
                    srvCnt[tId]++;
                    srvT = max( srvT, nextCst.arrT );
                    tableTime[tId] = srvT + nextCst.srvT;
                    resList.push_back( { nextCst.arrT,srvT,(int)round( ( srvT - nextCst.arrT ) / 60.0 ) } );
                    return true;
                }
                cstId++;
            }
            break;
        }
    }
    // Distribute any player
    int nextId = nextIdList.front();
    srvT = max( srvT, nextCst.arrT );
    tableTime[nextId] = srvT + nextCst.srvT;
    cstList.erase( cstList.begin() );
    resList.push_back( { nextCst.arrT,srvT, (int)round( ( srvT - nextCst.arrT ) / 60.0 ) } );
    srvCnt[nextId]++;
    return true;
}

int main() {
    input();
    while( findTable() ) {
        ;
    }
    sort( resList.begin(), resList.end(), []( array<int, 3> const& res1, array<int, 3> const& res2 ) {
        return res1[1] < res2[1];
    } );
    for( auto [arrT, srvT, wT] : resList ) {
        cout
            << setw( 2 ) << setfill( '0' ) << arrT / 60 / 60 << ":"
            << setw( 2 ) << setfill( '0' ) << arrT / 60 % 60 << ":"
            << setw( 2 ) << setfill( '0' ) << arrT % 60 << " ";
        cout
            << setw( 2 ) << setfill( '0' ) << srvT / 60 / 60 << ":"
            << setw( 2 ) << setfill( '0' ) << srvT / 60 % 60 << ":"
            << setw( 2 ) << setfill( '0' ) << srvT % 60 << " ";
        cout << wT << endl;
    }
    for( int i = 0; i < srvCnt.size(); i++ ) {
        cout << srvCnt[i] << ( i == srvCnt.size() - 1 ? "" : " " );
    }
    return 0;
}