#include <bits/stdc++.h>
using namespace std;
map<string, vector<pair<string, int>>> city;
set<string> candidates;
string minCandidate;
int minDis = 0, sumDis = 0;
void MST( string const &r, int verifyN, int disLimit ) {
    using nodeInfo = pair<int, string>;
    priority_queue<nodeInfo, vector<nodeInfo>, greater<>> pq;
    map<string, int> dist( { { r, 0 } } );
    pq.emplace( 0, r );
    while ( !pq.empty() ) {
        auto [curDis, curPos] = pq.top();
        pq.pop();
        if ( curDis > dist.at( curPos ) ) {
            continue;
        }
        for ( auto const &[nextv, edgew] : city.at( curPos ) ) {
            int nextd = edgew + curDis;
            if ( nextd <= disLimit && ( !dist.contains( nextv ) || nextd < dist[nextv] ) ) {
                dist[nextv] = nextd;
                pq.emplace( nextd, nextv );
            }
        }
    }
    int curMinDis = INT_MAX, reachableN = 0;
    int totalDis = accumulate( dist.begin(), dist.end(), 0, [&]( int res, const pair<string, int> &pos ) {
        if ( !pos.first.starts_with( "G" ) ) {
            reachableN++;
            curMinDis = min( pos.second, curMinDis );
            return res + pos.second;
        }
        return res;
    } );
    if ( reachableN == verifyN ) {
        if ( curMinDis > minDis || ( curMinDis == minDis && totalDis < sumDis ) || ( curMinDis == minDis && totalDis == sumDis && r < minCandidate ) ) {
            minDis = curMinDis;
            sumDis = totalDis;
            minCandidate = r;
        }
    }
}
int main() {
    int N, M, K, Ds;
    cin >> N >> M >> K >> Ds;
    for ( int i = 0, dist; i < K; i++ ) {
        string from, to;
        cin >> from >> to >> dist;
        if ( from.starts_with( "G" ) ) {
            candidates.insert( from );
        }
        if ( to.starts_with( "G" ) ) {
            candidates.insert( to );
        }
        city[from].emplace_back( to, dist );
        city[to].emplace_back( from, dist );
    }
    for ( const string &candidate : candidates ) {
        MST( candidate, N, Ds );
    }
    if ( minCandidate.empty() ) {
        cout << "No Solution";
        return 0;
    }
    cout << minCandidate << "\n"
         << fixed << setprecision( 1 ) << minDis * 1.0 << " "
         << fixed << setprecision( 1 ) << round( sumDis * 10.0 / N ) / 10.0;
    return 0;
}