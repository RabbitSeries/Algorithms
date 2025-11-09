// Small Label first. SLF
// Large Label last. LLL
#include <algorithm>
#include <queue>
#include <vector>
bool SPFA( const std::vector<std::vector<std::pair<int, int>>>& graph, int s ) {
    std::vector<int> dis( graph.size(), INT_MAX ), inQueueTimes( graph.size(), 0 ), inQueueStatus( graph.size(), false );
    std::vector<bool> a;
    dis[s] = 0;
    std::deque<int> relaxVQ;
    int queueDisSum = dis[s];
    relaxVQ.push_back( s );
    inQueueStatus[s] = inQueueTimes[s] = 1;
    while ( !relaxVQ.empty() ) {
        while ( dis[relaxVQ.front()] * relaxVQ.size() > queueDisSum ) {
            relaxVQ.push_back( relaxVQ.front() );
            relaxVQ.pop_front();
        }
        auto nodeIndex = relaxVQ.front();
        relaxVQ.pop_front();
        queueDisSum -= dis[nodeIndex];
        inQueueStatus[nodeIndex] = 0;
        for ( auto const& [nextV, edgeW] : graph[nodeIndex] ) {
            if ( !inQueueStatus[nextV] && dis[nodeIndex] + edgeW < dis[nextV] ) {
                dis[nextV] = dis[nodeIndex] + edgeW;
                if ( !relaxVQ.empty() && dis[nextV] < dis[relaxVQ.front()] ) {
                    relaxVQ.push_front( nextV );
                } else {
                    relaxVQ.push_back( nextV );
                }
                queueDisSum += dis[nextV];
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
