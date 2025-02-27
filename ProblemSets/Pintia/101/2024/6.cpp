#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
string getNum( int startx, int starty, pair<int, int> pos ) {
    int horizen = pos.first - startx;
    int vertical = pos.second - starty;
    string tmp = "";
    if( vertical > 0 ) {
        while( vertical-- > 0 ) {
            tmp += "1";
        }
        if( horizen > 0 ) {
            while( horizen-- > 0 ) {
                tmp += "2";
            }
        }
        else {
            while( horizen++ < 0 ) {
                tmp += "4";
            }
        }
    }
    else {
        if( horizen > 0 ) {
            while( horizen-- > 0 ) {
                tmp += "2";
            }
            while( vertical++ < 0 ) {
                tmp += "3";
            }
        }
        else {
            while( vertical++ < 0 ) {
                tmp += "3";
            }
            while( horizen++ < 0 ) {
                tmp += "4";
            }
        }
    }
    tmp += "0";
    return tmp;
}

int abs( int a, int b ) {
    return a > b ? a - b : b - a;
}

typedef pair<int, int> pos;
void getPermutation( vector<pos> applePos, vector<bool>& visited, vector<pos>& curList, vector<vector<pos>>& res ) {
    for( int i = 0; i < visited.size(); i++ ) {
        if( !visited[i] ) {
            visited[i] = true;
            curList.push_back( applePos[i] );
            if( curList.size() != applePos.size() )
                getPermutation( applePos, visited, curList, res );
            else {
                res.push_back( curList );
            }
            visited[i] = false;
        }
    }
    return;
}

ll getPathNum( int startx, int starty, vector<pos> oneRes ) {
    string res;
    for( auto p : oneRes ) {
        res += getNum( startx, starty, p );
        auto [startx, starty] = p;
    }
    return stoll( res );

}

int main() {
    vector<pos> applePos;
    int size = 0;
    int startx, starty;
    int appleCnt = 0;
    cin >> size;
    getchar();
    for( int i = 0; i < size; i++ ) {
        string line;
        getline( cin, line );
        int j = 0;
        while( j < size ) {
            int num = line[j] - '0';
            if( num == 2 ) {
                startx = i; starty = j;
            }
            else if( num == 1 ) {
                appleCnt++;
                applePos.push_back( pair<int, int>( i, j ) );
            }

            j++;
        }
    }
    priority_queue<ll, vector<ll>, less<>> appleQueue;
    vector<bool> eaten( appleCnt, false );
    vector<pos> curRes;
    vector<vector<pos>> res;
    getPermutation( applePos, eaten, curRes, res );
    for( auto path : res ) {
        appleQueue.push( getPathNum( startx, starty, path ) );
    }
    cout << appleQueue.top();
    return 0;
}