
#include <bits/stdc++.h>
using namespace std;

void DFS( map<int, vector<int>>const& childList ) {
    queue<int> q;
    bool first = true;
    q.push( 1 );
    while( !q.empty() ) {
        vector<int> curLevelList;
        while( !q.empty() ) {
            curLevelList.push_back( q.front() );
            q.pop();
        }
        int levelCnt = 0;
        for( int pid : curLevelList ) {
            bool hasNoChild = true;
            if( childList.count( pid ) != 0 ) {
                for( int child : childList.at( pid ) ) {
                    hasNoChild = false;
                    q.push( child );
                }
            }
            if( hasNoChild ) {
                levelCnt++;
            }
        }
        cout << ( ( !first ) ? ( " " + to_string( levelCnt ) ) : to_string( levelCnt ) );
        first = false;
    }
}

int main() {
    int member, parent;
    cin >> member;
    if( member == 0 ) {
        return 0;
    }
    cin >> parent;
    getchar();
    map<int, vector<int>> childList;
    int i = 0;
    while( i++ < parent ) {
        string id;
        int childCnt;
        cin >> id >> childCnt;
        childList[stoi( id )];
        int j = 0;
        while( j++ < childCnt ) {
            string childId;
            cin >> childId;
            childList[stoi( id )].push_back( stoi( childId ) );
        }
        if( i != parent ) {
            getchar();
        }
    }
    DFS( childList );
    return 0;
}