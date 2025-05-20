#include <bits/stdc++.h>
using namespace std;
int dx[] = { 0, 0, -1, 1 };
int dy[] = { 1, -1, 0, 0 };
int main() {
    int N, row, col, checkN;
    cin >> N >> row >> col;
    vector<vector<int>> seats;
    vector<pair<int, int>> seatPos = vector( N + 1, pair( -1, -1 ) );
    for ( int i = 0; i < row; i++ ) {
        seats.emplace_back( col, -1 );
        for ( int j = 0; j < col; j++ ) {
            cin >> seats[i][j];
            seatPos[seats[i][j]] = pair( i, j );
        }
    }
    cin >> checkN;
    for ( int i = 0; i < checkN; i++ ) {
        int a, b;
        cin >> a >> b;
        auto posA = seatPos[a];
        bool res = false;
        for ( int j = 0; j < 4; j++ ) {
            auto nextPos = pair( posA.first + dx[j], posA.second + dy[j] );
            if ( nextPos.first >= 0 and nextPos.second >= 0 and nextPos.first < row and nextPos.second < col and seats[nextPos.first][nextPos.second] == b ) {
                res = true;
                break;
            }
        }
        cout << ( res ? "yes\n" : "no\n" );
    }
}
