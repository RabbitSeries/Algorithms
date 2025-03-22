#include <bits/stdc++.h>
using namespace std;

int getUnvisited( unordered_set<int>& visited, const int& cityCnt ) {
    for( int i = 0; i < cityCnt; i++ ) {
        if( visited.contains( i ) == 0 ) {
            visited.insert( i );
            return i;
        }
    }
    return -1;
}

int MSTCnt( int cutCity, vector<vector<int>>const& roadMap, const int& cityCnt ) {
    unordered_set<int> visited;
    visited.insert( cutCity );
    queue<int> q;
    int mstCnt = 0;
    int unvisited = -1;
    while( ( unvisited = getUnvisited( visited, cityCnt ) ) != -1 ) {
        mstCnt++;
        q.push( unvisited );
        while( !q.empty() ) {
            int curVisit = q.front();
            q.pop();
            for( int nextV : roadMap[curVisit] ) {
                if( visited.contains( nextV ) == 0 ) {
                    visited.insert( nextV );
                    q.push( nextV );
                }
            }
        }
    }
    return mstCnt;
}

int main() {
    int cityCnt, roadCnt, checkCnt;
    cin >> cityCnt >> roadCnt >> checkCnt;
    vector<vector<int>> roadMap( cityCnt, vector<int>() );
    for( int i = 0; i < roadCnt; i++ ) {
        int city1, city2;
        cin >> city1 >> city2;
        roadMap[city1 - 1].push_back( city2 - 1 );
        roadMap[city2 - 1].push_back( city1 - 1 );
    }
    for( int i = 0; i < checkCnt; i++ ) {
        int query = 0;
        cin >> query;
        int mstCnt = MSTCnt( query - 1, roadMap, cityCnt ) - 1;
        // if (mstCnt < 0)?
        cout << mstCnt << endl;
    }
}