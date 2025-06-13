#include <bits/stdc++.h>
using namespace std;
int main() {
    int inventory;
    float market;
    cin >> inventory >> market;
    using mk = pair<float, float>;  // inventory can be float
    vector<mk> mooncakes( inventory );
    for ( int i = 0; i < inventory; i++ ) {
        cin >> mooncakes[i].first;
    }
    for ( int i = 0; i < inventory; i++ ) {
        cin >> mooncakes[i].second;
    }
    sort( mooncakes.begin(), mooncakes.end(), []( mk const& mk1, mk const& mk2 ) {
        return mk1.second / mk1.first > mk2.second / mk2.first;
    } );
    float revenue = 0;
    for ( int i = 0; market > 0 && i < inventory; i++ ) {
        int take = min( market, mooncakes[i].first );
        market -= take;
        revenue += take * ( mooncakes[i].second / mooncakes[i].first );
    }
    cout << fixed << setprecision( 2 ) << revenue;
}