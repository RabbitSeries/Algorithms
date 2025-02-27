#include <bits/stdc++.h>
using namespace std;
int main() {
    unordered_map<string, int> id2Pos;
    int registerCnt;
    cin >> registerCnt;
    for ( int i = 0; i < registerCnt; i++ ) {
        string curId;
        cin >> curId;
        id2Pos[curId] = i;
    }
    cin >> registerCnt;
    vector<string> queryList;
    for ( int i = 0; i < registerCnt; i++ ) {
        string curId;
        cin >> curId;
        queryList.push_back( curId );
    }
    for ( string curId : queryList ) {
        if ( id2Pos.count( curId ) ) {
            cout << id2Pos.at( curId ) + 1 << endl;
        } else {
            cout << "Sorry" << endl;
        }
    }
    return 0;
}