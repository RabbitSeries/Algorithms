#include <bits/stdc++.h>
using namespace std;

using point2D = pair<int, int>;

const int BLOCK = -1;
const int EMPTY = 0;

const int dx[4]{ 0, 0, 1, -1 };
const int dy[4]{ 1, -1, 0, 0 };

inline bool isValid( point2D curPos, vector<vector<int>> const& internetMap ) {
    return curPos.first < internetMap.size() && curPos.second < internetMap[0].size() && internetMap[curPos.first][curPos.second] == EMPTY;
}

inline int manhattanDistance( point2D const& p1, point2D const& p2 ) {
    return abs( p1.first - p2.first ) + abs( p1.second - p2.second );
}

vector<vector<int>> Dijkstra( point2D s, vector<vector<int>> const& internetMap ) {
    int initSignal = internetMap[s.first][s.second];
    vector<vector<int>> distance( internetMap.size(), vector<int>( internetMap[0].size(), INT_MAX ) );
    vector<vector<int>> signal( internetMap.size(), vector<int>( internetMap[0].size(), 0 ) );
    distance[s.first][s.second] = 0;
    signal[s.first][s.second] = initSignal;
    priority_queue<pair<int, point2D>, vector<pair<int, point2D>>, greater<>> pq;
    pq.emplace( 0, s );
    while ( !pq.empty() ) {
        auto [curDist, curPos] = pq.top();
        pq.pop();
        for ( int i = 0; i < 4; i++ ) {
            point2D nextPos{ curPos.first + dx[i], curPos.second + dy[i] };
            // int nextDist = manhattanDistance( s, nextPos );
            int signalLevel = initSignal - curDist - 1;
            if ( isValid( nextPos, internetMap ) && signalLevel >= 0 ) {
                if ( curDist + 1 < distance[nextPos.first][nextPos.second] ) {
                    distance[nextPos.first][nextPos.second] = curDist + 1;
                    signal[nextPos.first][nextPos.second] = signalLevel;
                    pq.emplace( curDist + 1, nextPos );
                } else if ( curDist + 1 == distance[nextPos.first][nextPos.second] ) {
                    signal[nextPos.first][nextPos.second] = max( signalLevel, signal[nextPos.first][nextPos.second] );
                }
            }
        }
    }
    return signal;
}

int main() {
    int row, col;
    cin >> row >> col;
    point2D start;
    vector<vector<int>> internetMap( row, vector<int>( col, 0 ) );
    for ( int i = 0; i < row; i++ ) {
        for ( int j = 0; j < col; j++ ) {
            cin >> internetMap[i][j];
            if ( internetMap[i][j] > 0 ) {
                start = point2D{ i, j };
            }
        }
    }
    vector<vector<int>> res = move( Dijkstra( start, internetMap ) );
    int outPutRow, outputCol;
    cin >> outPutRow >> outputCol;
    cout << res[outPutRow][outputCol];
    cout << endl;
    return 0;
}
// printSingal( res );

void printSingal( vector<vector<int>> const& signal ) {
    for ( auto row : signal ) {
        for ( int signalCell : row ) {
            cout << signalCell;
        }
        cout << endl;
    }
}