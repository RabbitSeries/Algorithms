#include "vector"
#include "queue"
#include "map"
using namespace std;
#define _UNREACHABLE 1<<30
class Solution {
public:
    int time, change, n;
    vector<int> dis;
    vector<int> pre;
    priority_queue<int, vector<int>, greater<>> pathOrder;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> visitOrder;
    int secondMinimum( int n, vector<vector<int>> edges, int time, int change ) {
        this->time = time;
        this->change = change;
        this->n = n;
        vector<int> dis = vector<int>( n + 1, _UNREACHABLE );
        vector<vector<int>> graph( n + 1 );
        for( auto edge : edges ) {
            graph[edge[0]].push_back( edge[1] );
            graph[edge[1]].push_back( edge[0] );
        }
        dis[1] = 0;
        visitOrder.emplace( 0, 1 );
        while( !visitOrder.empty() ) {
            auto [arriveTime, index] = visitOrder.top();
            visitOrder.pop();
            if( dis[index] < arriveTime ) {
                for( auto nextV : graph[index] ) {
                    int arriveNext = arriveTime + getWaitTime( arriveTime ) + time;
                    if( nextV == n ) {
                        pathOrder.push( arriveNext );
                        getPre( arriveNext );
                        break;
                    }
                }
                continue;
            }
            for( auto nextV : graph[index] ) {
                int arriveNext = arriveTime + getWaitTime( arriveTime ) + time;
                if( nextV == n ) {
                    pathOrder.push( arriveNext );
                    getPre( arriveNext );
                    if( dis[nextV] >= arriveNext ) {
                        dis[nextV] = arriveNext;
                        visitOrder.emplace( arriveNext, nextV );
                    }
                }
                else if( dis[nextV] >= arriveNext ) {
                    dis[nextV] = arriveNext;
                    visitOrder.emplace( arriveNext, nextV );
                }
            }
        }
        int small = pathOrder.top();
        while( pathOrder.top() == small ) {
            pathOrder.pop();
        }
        return pathOrder.top();
    }
    int getWaitTime( int startTime ) {
        if( ( startTime / change ) % 2 == 0 ) {
            return 0;
        }
        else {
            return change - ( startTime % change );
        }
    }
    void getPre( int arriveTime ) {
        int arriveTimeBack = arriveTime + getWaitTime( arriveTime ) + time;
        int arriveTimeForward = arriveTimeBack + getWaitTime( arriveTimeBack ) + time;
        pathOrder.push( arriveTimeForward );
    }
};
int main() {
    Solution s;
    s.secondMinimum( 5, { {1,2},{1,3},{1,4},{3,4},{4,5} }, 3, 5 );
    return 0;
}