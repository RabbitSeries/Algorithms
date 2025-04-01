#include <bits/stdc++.h>
using namespace std;
struct person {
    int speed, id, round;
};
int main() {
    int pCnt, gCnt, order, roundCnt = 1;
    cin >> pCnt >> gCnt;
    vector<person> pList( pCnt );
    queue<int> gameQ;
    for ( int i = 0; i < pCnt; i++ ) {
        cin >> pList[i].speed;
        pList[i].id = i;
    }
    for ( int i = 0; i < pCnt; i++ ) {
        cin >> order;
        gameQ.emplace( order );
    }
    while ( gameQ.size() > 1 ) {
        queue<int> nextMatch;
        while ( !gameQ.empty() ) {
            int promotion = -1, maxSpeed = -1;
            for ( int i = 0; i < gCnt && !gameQ.empty(); i++ ) {
                person const& curP = pList[gameQ.front()];
                gameQ.pop();
                pList[curP.id].round = roundCnt;  // record player's match round
                if ( curP.speed > maxSpeed ) {
                    maxSpeed = curP.speed;
                    promotion = curP.id;
                }
            }
            nextMatch.emplace( promotion );
        }
        gameQ = move( nextMatch );
        roundCnt++;
    }
    pList[gameQ.front()].round = roundCnt;
    stringstream buf;
    sort( pList.begin(), pList.end(), []( person const& p1, person const& p2 ) { return p1.round > p2.round; } );
    vector<int> finalRank( pCnt );
    finalRank[pList[0].id] = 1;
    for ( int i = 1; i < pCnt; i++ ) {
        finalRank[pList[i].id] = ( pList[i].round == pList[i - 1].round ? finalRank[pList[i - 1].id] : ( i + 1 ) );
    }
    for ( int p : finalRank ) {
        buf << " " << p;
    }
    cout << buf.str().substr( 1 );
}