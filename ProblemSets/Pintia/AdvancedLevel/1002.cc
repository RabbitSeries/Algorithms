#include <bits/stdc++.h>
using namespace std;
void readStream( map<int, double>& poly ) {
    int cnt;
    cin >> cnt;
    int i = 0;
    while( i++ < cnt ) {
        int exp;
        double coeff;
        cin >> exp >> coeff;
        poly[exp] = coeff;
    }
}
int main() {
    map<int, double> poly1, poly2;
    readStream( poly1 );
    readStream( poly2 );
    map<int, double> add;
    for( auto const& p : poly1 ) {
        add[p.first] = add[p.first] + p.second;
    }
    for( auto const& p : poly2 ) {
        add[p.first] = add[p.first] + p.second;
    }
    vector<pair<int, double>> outputList;
    for( auto const& v : add ) {
        if( v.second != 0 )
            outputList.push_back( v );
    }
    cout << outputList.size();
    sort( outputList.begin(), outputList.end(), []( pair<int, double>& p1, pair<int, double>& p2 ) {
        return p1.first > p2.first;
    } );

    for_each( outputList.begin(), outputList.end(), []( pair<int, double>& p1 ) {
        cout << " " << p1.first << " " << fixed << setprecision( 1 ) << p1.second;
    } );
}