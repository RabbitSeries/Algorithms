#include <bits/stdc++.h>
using namespace std;
int main() {
    unordered_map<string, unordered_map<string, int>> relation;
    unordered_map<string, int> nameWeight;  // nameWeight == 0 as visited
    set<string> nameList;
    int phoneCallCnt, threshold;
    cin >> phoneCallCnt >> threshold;
    for ( int i = 0; i < phoneCallCnt; i++ ) {
        string name1, name2;
        int duration;
        cin >> name1 >> name2 >> duration;
        nameWeight[name1] += duration;
        nameWeight[name2] += duration;
        nameList.insert( name1 );
        nameList.insert( name2 );
        relation[name1][name2] += duration;
        relation[name2][name1] += duration;
    }
    map<string, int> headList;
    for ( auto const &curName : nameList ) {
        if ( nameWeight[curName] == 0 ) continue;
        int totalWeight = 0, memberCnt = 0, maxWeight = nameWeight[curName];
        string headName = curName;
        queue<string> q;  // bfs start
        q.push( curName );
        nameWeight[curName] = 0;
        while ( !q.empty() ) {
            string curName = q.front();
            q.pop();
            memberCnt++;
            for ( auto const &[nextName, w] : relation.at( curName ) ) {
                totalWeight += relation[curName][nextName];
                relation[curName][nextName] = relation[nextName][curName] = 0;
                if ( nameWeight[nextName] > 0 ) {
                    if ( nameWeight[nextName] > maxWeight ) {
                        maxWeight = nameWeight[nextName];
                        headName = nextName;
                    }
                    nameWeight[nextName] = 0;
                    q.push( nextName );
                }
            }
        }
        if ( totalWeight > threshold && memberCnt > 2 )  // cur bfs res
            headList[headName] = memberCnt;
    }
    cout << headList.size() << endl;
    for ( auto const &[headName, memberCnt] : headList )
        cout << headName << " " << memberCnt << endl;
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
// dfs( dfs, relation, edgeVisited, visited, curName );