#include <bits/stdc++.h>
using namespace std;
struct person {
    person( int s, int r, int i, int o ) {
        speed = s;
        rank = r;
        id = i;
        order = o;
    }
    int speed, rank, id, order;
};
int main() {
    int pCnt, gCnt;
    cin >> pCnt >> gCnt;
    vector<person> pList( pCnt ), resList, nextMatch;
    for ( int i = 0; i < pCnt; i++ ) {
        cin >> pList[i].speed;
        pList[i].id = i;
    }
    for ( int i = 0; i < pCnt; i++ ) cin >> pList[i].order;
    sort( pList.begin(), pList.end(), []( person const& p1, person const& p2 ) { return p1.order < p2.order; } );
    int curRank = pCnt / gCnt + 1;
    while ( pList.size() > 1 ) {
        for ( int i = 0; i < pList.size(); i += gCnt ) {
            int maxId = -1, maxW = -1;
            nextMatch.emplace_back( maxW, 0, maxId, 0 );
            for ( int j = 0; j < gCnt && ( i + j ) < pList.size(); j++ ) {
                if ( pList[i + j].speed > maxW ) {
                    maxW = pList[i + j].speed;
                    maxId = pList[i + j].id;
                    nextMatch.back() = pList[i + j];
                }
            }
            for ( int j = 0; j < gCnt && ( i + j ) < pList.size(); j++ ) {
                if ( pList[i + j].id != maxId ) {
                    pList[i + j].rank = curRank;
                    resList.emplace_back( pList[i + j] );
                }
            }
        }
        pList = nextMatch;
        curRank--;
    }
    resList.emplace_back( 0, 1, pList[0].id, 0 );
    sort( resList.begin(), resList.end(), []( person const& p1, person const& p2 ) { return p1.id < p2.id; } );
    stringstream buf;
    for ( auto& p : resList ) buf << " " << p.rank;
    cout << buf.str().substr( 1 );
}