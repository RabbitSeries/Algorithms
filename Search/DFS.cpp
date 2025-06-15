#include <bits/stdc++.h>
using namespace std;
vector<vector<int>> numList;
void dfs( set<int> visited ) {
    for ( int i = 0; i < numList.size(); i++ ) {
        if ( !visited.contains( i ) ) {
            visited.emplace( i );
            dfs( visited );
            visited.erase( i );
        }
    }
}
