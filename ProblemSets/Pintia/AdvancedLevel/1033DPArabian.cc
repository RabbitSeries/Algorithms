#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <vector>
using namespace std;
class station {
   public:
    double cost;
    int distance;
    station() {};
    station( double a, int b ) {
        cost = a;
        distance = b;
    }
};
class gas {
   public:
    double cost;
    double use;
    gas() {};
    gas( double a, double b ) {
        cost = a;
        use = b;
    }
    bool operator<( const gas& x ) const {
        return cost > x.cost;
    }
};
vector<station> vstation;
priority_queue<gas> vgas;
bool cmp1( const station& a, const station& b );
int main() {
    double capacity;
    int distance, speed, n;
    cin >> capacity >> distance >> speed >> n;
    for ( int i = 0; i < n; ++i ) {
        station x;
        cin >> x.cost >> x.distance;
        vstation.push_back( x );
    }
    double journey = 0;
    double totalcost = 0;
    vstation.push_back( station( 0, distance ) );
    sort( vstation.begin(), vstation.end(), cmp1 );
    if ( vstation[0].distance != 0 ) {
        cout << "The maximum travel distance = 0.00";
        return 0;
    }
    bool f = 0, f2 = 0;
    for ( int i = 0; i < vstation.size(); ++i ) {
        if ( vgas.empty() )
            vgas.push( gas( vstation[i].cost, capacity ) );
        else {
            vector<gas> v;
            while ( !vgas.empty() ) {
                v.push_back( vgas.top() );
                vgas.pop();
            }
            double sumgas = 50.0;
            int j;
            for ( j = 0; j < v.size(); ++j ) {
                if ( vstation[i].cost <= v[j].cost ) break;
                vgas.push( v[j] );
                sumgas -= v[j].use;
            }
            vgas.push( gas( vstation[i].cost, sumgas ) );
        }
        double nextstation = vstation[i + 1].distance;
        if ( nextstation >= distance ) {
            nextstation = distance;
            f = 1;
        }
        while ( !vgas.empty() ) {
            double costgas = ( nextstation - journey ) / speed;
            if ( costgas == 0 ) break;
            if ( costgas > capacity ) {
                f2 = 1;
                journey += ( capacity * speed );
                break;
            }
            gas x = vgas.top();
            if ( x.use - costgas < 0 ) {
                costgas = x.use;
            }
            totalcost += x.cost * costgas;
            journey += costgas * speed;
            x.use -= costgas;
            vgas.pop();
            if ( x.use > 0 ) vgas.push( x );
        }
        if ( f || f2 ) break;
    }
    if ( f && f2 == 0 ) {
        cout.precision( 2 );
        cout << fixed << totalcost;
    }
    if ( f2 ) {
        cout << "The maximum travel distance = ";
        cout.precision( 2 );
        cout << fixed << journey;
    }
    system( "pause" );
    return 0;
}
bool cmp1( const station& a, const station& b ) {
    return a.distance < b.distance;
}