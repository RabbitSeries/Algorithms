#include <algorithm>
#include <map>
#include <queue>
#include <tuple>
#include <vector>
// AOE: Event - Activity -> Event
using Graph = std::vector<std::vector<std::pair<int, int>>>;
std::vector<int> TopoSort( Graph const& AOE, int s ) {
    std::vector<int> inDegree( AOE.size(), 0 ), sorted;
    sorted.reserve( AOE.size() );
    for ( size_t i = 0; i < AOE.size(); i++ ) {
        auto& nextVList = AOE[i];
        for ( auto const& outEdge : nextVList ) {
            inDegree[outEdge.first]++;
        }
    }
    std::queue<int> q{ { s } };
    while ( !q.empty() ) {
        int event = q.front();
        q.pop();
        sorted.push_back( event );
        for ( auto const& outEdge : AOE[event] ) {
            if ( !( --inDegree[outEdge.first] ) ) {
                q.emplace( outEdge.first );
            }
        }
    }
    return sorted;
}
std::vector<int> EarliestBegin( Graph const& AOE, std::vector<int> const& topoOrder ) {
    std::vector<int> earliestBegin( AOE.size(), 0 );  // It is only possible to determine earliest begin time in topoOrder,
                                                      // any event is possible to begin later.
                                                      // But it is meaningless if this event delays so long that end event's start(finish) time is delayed.
                                                      // So there are both earliest begin and latest begin time.
    for ( int v : topoOrder ) {
        for ( auto [nextV, act_duration] : AOE[v] ) {
            earliestBegin[nextV] = std::max( earliestBegin[v] + act_duration, earliestBegin[nextV] );
        }
    }
    return earliestBegin;
}
std::vector<int> LatestBegin( Graph const& AOE, std::vector<int> const& topoOrder, std::vector<int> const& earliestBegin ) {
    std::vector<int> latestBegin( AOE.size(), INT_MAX );
    latestBegin[topoOrder.back()] = earliestBegin[topoOrder.back()];
    for ( int v : std::views::reverse( topoOrder ) ) {
        for ( auto [nextV, act_duration] : AOE[v] ) {
            latestBegin[v] = std::min( latestBegin[nextV] - act_duration, latestBegin[v] );
        }
    }
    return latestBegin;
}
std::vector<std::vector<int>> CriticalPath( Graph const& AOE,
                                            std::vector<int> const& topoOrder,
                                            std::vector<int> const& earliestBegin,
                                            std::vector<int> const& latestBegin ) {
    std::vector<std::vector<int>> paths;
    std::queue<std::pair<int, std::vector<int>>> q;
    q.emplace( topoOrder[0], std::vector{ topoOrder[0] } );
    while ( !q.empty() ) {
        auto [s, p] = q.front();
        q.pop();
        if ( s == topoOrder.back() ) {
            paths.emplace_back( std::move( p ) );
            continue;
        }
        for ( const auto& [nextV, act_duration] : AOE[s] ) {
            if ( earliestBegin[nextV] == latestBegin[nextV] ) {
                auto nextP = p;
                nextP.push_back( nextV );
                q.emplace( nextV, std::move( nextP ) );
            }
        }
    }
    return paths;
}
