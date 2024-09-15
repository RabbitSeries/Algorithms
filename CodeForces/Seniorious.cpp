#include "bits/stdc++.h"
using namespace std;
int n, m, vmax;
typedef long long ll;
ll seed;
bool flag = false;
vector<int> a;
int rnd() {
    int ret = seed;
    seed = ( seed * 7 + 13 ) % 1000000007;
    return ret;
}

int power( int x, int e ) {
    return x == 1 ? e : e * power( x - 1, e );
}

void operation() {
    int result, x, y, l, r, op;
    op = ( rnd() % 4 ) + 1;
    l = ( rnd() % n ) + 1;
    r = ( rnd() % n ) + 1;

    if( l > r )
        swap( l, r );

    if( op == 3 ) {
        x = ( rnd() % ( r - l + 1 ) ) + 1;
        vector<int> lrv( a.begin() + l + 1, a.begin() + r + 2 );
        sort( lrv.begin(), lrv.end() );
        cout << lrv[x - 1];
        flag = true;
    }
    else {
        x = ( rnd() % vmax ) + 1;
        if( op != 4 ) {
            switch( op ) {
            case 1:
                for( int i = l; i <= r; i++ ) {
                    a[i] = a[i] + x;
                }
                break;
            case 2:
                for( int i = l; i <= r; i++ ) {
                    a[i] = x;
                }
                break;
            }
        }
    }


    if( op == 4 ) {
        y = ( rnd() % vmax ) + 1;
        int sum = 0;
        for( int i = l; i <= r; i++ ) {
            sum += power( x, a[i] ) % y;
        }
        cout << sum;
        flag = true;
    }
}

int main() {
    cin >> n >> m >> seed >> vmax;
    a = vector<int>( n + 1 );
    for( int i = 1; i <= n; i++ ) {
        a[i] = ( rnd() % vmax ) + 1;
    }
    for( int i = 1; i <= m; ++i ) {
        operation();
        cout << ( flag ? "\n" : "" );
        flag = false;
    }
    return 0;
}