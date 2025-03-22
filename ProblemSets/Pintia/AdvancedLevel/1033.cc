#include <bits/stdc++.h>
using namespace std;
int main() {
    double capacity, distance, disPerGasUnit, stationCnt;
    cin >> capacity >> distance >> disPerGasUnit >> stationCnt;
    vector<pair<double, double>> stationInfo( stationCnt );
    for ( int i = 0; i < stationCnt; i++ )
        cin >> stationInfo[i].first >> stationInfo[i].second;
    sort( stationInfo.begin(), stationInfo.end(), []( pair<double, double> const &p1, pair<double, double> const &p2 ) {
        return p1.second < p2.second;
    } );
    if ( stationInfo[0].second != 0 ) {
        cout << "The maximum travel distance = 0.00" << endl;
        return 0;
    }
    stationInfo.emplace_back( 0, distance );  // The last place (destination) must have the lowest fee(there can be multiple lowest before the last place)
    priority_queue<tuple<double, int, double>, vector<tuple<double, int, double>>, greater<>> pq;
    vector<unordered_map<double, double>> fee( stationCnt + 1 );  // remainGas( stationCnt, 0 )
    double maxDist = 0;
    fee[0][0] = 0;
    pq.emplace( 0, 0, 0 );
    while ( !pq.empty() ) {
        auto [curFee, curPos, curGasRemain] = pq.top();
        pq.pop();
        if ( curFee > fee[curPos][curGasRemain] ) continue;
        if ( curPos == stationCnt ) {
            cout << fixed << setprecision( 2 ) << curFee << endl;
            return 0;
        }
        for ( int nextPos = curPos + 1; nextPos < stationCnt + 1; nextPos++ ) {
            double deltaDis = stationInfo[nextPos].second - stationInfo[curPos].second;
            double gasRequired = deltaDis / disPerGasUnit;
            if ( gasRequired > capacity ) {
                maxDist = max( capacity * disPerGasUnit + stationInfo[curPos].second, maxDist );
                break;
            }
            if ( stationInfo[curPos].first < stationInfo[nextPos].first ) {  // TODO prove this logic
                double maxFee = curFee + ( capacity - curGasRemain ) * stationInfo[curPos].first;
                if ( !fee[nextPos].contains( capacity - gasRequired ) || maxFee < fee[nextPos][capacity - gasRequired] ) {
                    fee[nextPos][capacity - gasRequired] = maxFee;
                    pq.emplace( maxFee, nextPos, capacity - gasRequired );
                }
            } else {
                double nextFee = ( max( gasRequired, curGasRemain ) - curGasRemain ) * stationInfo[curPos].first + curFee;
                double nextGas = max( curGasRemain - gasRequired, (double)0 );
                if ( !fee[nextPos].contains( nextGas ) || nextFee < fee[nextPos][nextGas] ) {
                    fee[nextPos][nextGas] = nextFee;
                    pq.emplace( nextFee, nextPos, nextGas );
                }
            }
        }
    }
    cout << "The maximum travel distance = " << fixed << setprecision( 2 ) << maxDist;
    return 0;
}
// double maxFee = curFee + ( capacity - curGasRemain ) * stationInfo[curPos].first;
// if ( !fee[nextPos].contains( capacity - gasRequired ) || maxFee < fee[nextPos][capacity - gasRequired] ) {
//     fee[nextPos][capacity - gasRequired] = maxFee;
//     pq.emplace( maxFee, nextPos, capacity - gasRequired );
// }
// double nextFee = ( max( gasRequired, curGasRemain ) - curGasRemain ) * stationInfo[curPos].first + curFee;
// double nextGas = max( curGasRemain - gasRequired, (double)0 );
// if ( !fee[nextPos].contains( nextGas ) || nextFee < fee[nextPos][nextGas] ) {
//     fee[nextPos][nextGas] = nextFee;
//     pq.emplace( nextFee, nextPos, nextGas );
// }