#include <vector>
#include <queue>
using namespace std;
#define _UNREACHABLE 1<<30
class Solution {
public:
    vector<vector<int>> allPathsSourceTarget( vector<vector<int>>& graph ) {
        int vcnt = graph.size();
        vector<int> topoSequence;
        vector<int> dis( vcnt, _UNREACHABLE );
        vector<vector<vector<int>>> path( vcnt );
        dis[0] = 0;
        path[0].emplace_back( vector<int>{0} );
        getTopoSequence( topoSequence, graph );
        for( auto topoOrder : topoSequence ) {
            for( auto nextV : graph[topoOrder] ) {
                for( auto prePath : path[topoOrder] ) {
                    auto CopyPath = prePath;
                    CopyPath.push_back( nextV );
                    path[nextV].push_back( CopyPath );
                }
            }
        }
        return path[vcnt - 1];
    }
    vector<vector<int>> allPathsSourceTarget( vector<vector<int>> graph ) {
        int vcnt = graph.size();
        vector<int> topoSequence;
        vector<int> dis( vcnt, _UNREACHABLE );
        vector<vector<vector<int>>> path( vcnt );
        dis[0] = 0;
        path[0].emplace_back( vector<int>{0} );
        getTopoSequence( topoSequence, graph );
        for( auto topoOrder : topoSequence ) {
            for( auto nextV : graph[topoOrder] ) {
                for( auto prePath : path[topoOrder] ) {
                    auto CopyPath = prePath;
                    CopyPath.push_back( nextV );
                    path[nextV].push_back( CopyPath );
                }
            }
        }
        return path[vcnt - 1];
    }
    void getTopoSequence( vector<int>& topoSequence, vector<vector<int>>& graph ) {
        int vcnt = graph.size();
        vector<int> inDegree( vcnt, 0 );
        for( auto nextVList : graph ) {
            for( auto nextV : nextVList ) {
                inDegree[nextV]++;
            }
        }
        queue<int> topOrder;
        topOrder.push( 0 );
        while( !topOrder.empty() ) {
            int u = topOrder.front();
            topOrder.pop();
            topoSequence.push_back( u );
            for( auto nextV : graph[u] ) {
                inDegree[nextV]--;
                if( inDegree[nextV] == 0 ) {
                    topOrder.push( nextV );
                }
            }
        }
    }
};

int main() {
    Solution s;
    s.allPathsSourceTarget( { {1,2},{3},{3},{} } );
    return 0;
}