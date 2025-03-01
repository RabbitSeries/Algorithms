#include <bits/stdc++.h>
using namespace std;
int main() {
    unordered_map<string, unordered_map<string, int>> relation;
    unordered_map<string, unordered_map<string, bool>> edgeVisited;  // actually node weight can't be obtained in the initialization stage
    unordered_map<string, bool> visited;
    int phoneCallCnt, threshold;
    cin >> phoneCallCnt >> threshold;
    for ( int i = 0; i < phoneCallCnt; i++ ) {
        string name1, name2;
        int duration;
        cin >> name1 >> name2 >> duration;
        visited[name1] = visited[name2] = false;
        relation[name2][name1] = relation[name1][name2] = relation[name1][name2] + duration;
    }
    vector<string> nameList;
    for ( auto const &[name, status] : visited ) nameList.emplace_back( name );

    int nameCnt = visited.size();
    map<string, int> headList;
    for ( int i = 0; i < nameCnt; i++ ) {
        if ( visited[nameList[i]] ) continue;
        int totalWeight = 0, memberCnt = 1, maxWeight = 0;
        string headName = "";
        queue<string> q;  // bfs start
        q.push( nameList[i] );
        visited[nameList[i]] = true;
        while ( !q.empty() ) {
            string curName = q.front();
            q.pop();
            int curWeight = 0;
            for ( auto const &[nextName, w] : relation.at( curName ) ) {
                curWeight += w;
                if ( !edgeVisited[curName][nextName] ) {
                    totalWeight += w;
                    edgeVisited[curName][nextName] = edgeVisited[nextName][curName] = true;
                }
                if ( !visited[nextName] ) {
                    memberCnt++;
                    visited[nextName] = true;
                    q.push( nextName );
                }
            }
            if ( curWeight > maxWeight ) {
                maxWeight = curWeight;
                headName = curName;
            }
        }
        if ( totalWeight > threshold && memberCnt > 2 ) headList[headName] = memberCnt;  // cur bfs res
    }
    if ( !headList.empty() ) {
        cout << headList.size() << endl;
        for ( auto const &[headName, memberCnt] : headList ) {
            cout << headName << " " << memberCnt << endl;
        }
    } else {
        cout << 0;
    }
}

// TODO dfs version?
// auto dfs = []( auto &&self, auto &&relation, auto &&edgeVisited, auto &&visited, string curName,int& totalWeight,int & ) {
//     for ( auto const &[nextName, w] : relation.at( curName ) ) {
//         if ( !edgeVisited[curName][nextName] ) {
//             totalWeight += w;
//             edgeVisited[curName][nextName] = edgeVisited[nextName][curName] = true;
//         }
//         if ( !visited[nextName] ) {
//             memberCnt++;
//             visited[nextName] = true;
//             self( self, nextName );
//         }
//     }
// };
// dfs( dfs, relation, edgeVisited, visited, nameList[i] );