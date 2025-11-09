#include <algorithm>
#include <queue>
#include <vector>
/**
 * @brief
 * @param graph
 * @param s
 * @return true if there is negative loop, false otherwise
 */
bool SPFA( const std::vector<std::vector<std::pair<int, int>>>& graph, int s ) {
    std::vector<int> dis( graph.size(), INT_MAX ), inQueueTimes( graph.size(), 0 ), inQueueStatus( graph.size(), false );
    dis[s] = 0;
    inQueueTimes[s] = inQueueStatus[s] = 1;
    std::priority_queue pq( std::greater<>{}, std::vector<std::pair<int, int>>{} );
    pq.emplace( s, 0 );
    while ( !pq.empty() ) {
        auto [curDis, i] = pq.top();
        inQueueStatus[i] = false;
        pq.pop();
        for ( auto const& [nextV, edgeW] : graph[i] ) {
            if ( !inQueueStatus[i] && dis[i] + edgeW < dis[nextV] ) {
                dis[nextV] = dis[i] + edgeW;
                pq.emplace( dis[nextV], nextV );
                inQueueStatus[nextV] = true;
                inQueueTimes[nextV]++;
                if ( inQueueTimes[nextV] >= graph.size() ) {
                    return true;
                }
            }
        }
    }
    return false;
}
