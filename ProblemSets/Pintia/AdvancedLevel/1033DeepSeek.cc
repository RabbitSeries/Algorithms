#include <bits/stdc++.h>
using namespace std;
struct GasStation {
    double price;
    double di;

    GasStation( double p, double d ) : price( p ), di( d ) {}
};
struct State {
    double cost;
    int station;
    double gas;

    State( double c, int s, double g ) : cost( c ), station( s ), gas( g ) {}

    bool operator>( const State& other ) const {
        return cost > other.cost;
    }
};
int main() {
    double Cmax, D, Davg;
    int N;
    cin >> Cmax >> D >> Davg >> N;
    vector<GasStation> stations;
    for ( int i = 0; i < N; ++i ) {
        double p, d;
        cin >> p >> d;
        stations.emplace_back( p, d );
    }
    stations.emplace_back( 0.0, D );  // Add destination as a station with price 0
    sort( stations.begin(), stations.end(), []( const GasStation& a, const GasStation& b ) {
        return a.di < b.di;  // Sort stations by distance
    } );

    if ( stations[0].di != 0 ) {  // Check if the first station is at 0
        cout << "The maximum travel distance = 0.00" << endl;
        return 0;
    }
    int n = stations.size();
    for ( int i = 0; i < n - 1; ++i ) {  // Check consecutive gaps
        double delta = stations[i + 1].di - stations[i].di;
        if ( delta > Cmax * Davg ) {
            double max_dist = stations[i].di + Cmax * Davg;
            cout << "The maximum travel distance = " << fixed << setprecision( 2 ) << max_dist << endl;
            return 0;
        }
    }
    if ( stations.back().di != D ) {      // Check if the last station is the destination
        stations.emplace_back( 0.0, D );  // Add the destination station
        n = stations.size();
        double delta = D - stations[n - 2].di;  // Check the gap between previous last and destination
        if ( delta > Cmax * Davg ) {
            double max_dist = stations[n - 2].di + Cmax * Davg;
            cout << "The maximum travel distance = " << fixed << setprecision( 2 ) << max_dist << endl;
            return 0;
        }
    }
    vector<unordered_map<double, double>> dist( n );  // Now, proceed to compute minimal cost using Dijkstra-like approach
    priority_queue<State, vector<State>, greater<State>> pq;
    dist[0][0.0] = 0.0;
    pq.emplace( 0.0, 0, 0.0 );
    bool found = false;
    double min_cost = 0.0;
    while ( !pq.empty() ) {
        State current = pq.top();
        pq.pop();
        double current_cost = current.cost;
        int i = current.station;
        double g = current.gas;
        if ( i == n - 1 ) {
            min_cost = current_cost;  // Reached destination
            found = true;
            break;
        }
        if ( dist[i].count( g ) && current_cost > dist[i][g] ) {
            continue;
        }
        for ( int j = i + 1; j < n; ++j ) {
            double delta = stations[j].di - stations[i].di;
            if ( delta > Cmax * Davg ) {
                break;  // stations are sorted, so further j's will have larger delta
            }
            double required_gas = delta / Davg;
            // if ( required_gas > Cmax ) {
            //     continue;
            // }
            double x_min = max( 0.0, required_gas - g );
            double x_max = Cmax - g;
            // if ( x_min > x_max ) {
            //     continue;
            // }
            if ( stations[j].price < stations[i].price ) {  // Decide whether to buy x_min or x_max based on price comparison
                double new_g = g + x_min - required_gas;    // Buy x_min to reach j
                double new_cost = current_cost + x_min * stations[i].price;
                if ( new_g < 0 ) {
                    continue;
                }
                if ( !dist[j].count( new_g ) || new_cost < dist[j][new_g] ) {
                    dist[j][new_g] = new_cost;
                    pq.emplace( new_cost, j, new_g );
                }
            } else {
                double new_g = g + x_max - required_gas;  // Buy x_max to have as much gas as possible from cheaper station i
                double new_cost = current_cost + x_max * stations[i].price;
                if ( new_g < 0 ) {
                    continue;
                }
                if ( !dist[j].count( new_g ) || new_cost < dist[j][new_g] ) {
                    dist[j][new_g] = new_cost;
                    pq.emplace( new_cost, j, new_g );
                }
            }
        }
    }
    if ( found ) {
        cout << fixed << setprecision( 2 ) << min_cost << endl;
    } else {                    // This should not happen as initial checks passed
        double max_dist = 0.0;  // But handle just in case
        for ( int i = 0; i < n; ++i ) {
            if ( stations[i].di + Cmax * Davg > max_dist ) {
                max_dist = stations[i].di + Cmax * Davg;
            }
        }
        if ( max_dist > D ) {
            max_dist = D;
        }
        cout << "The maximum travel distance = " << fixed << setprecision( 2 ) << max_dist << endl;
    }
    return 0;
}