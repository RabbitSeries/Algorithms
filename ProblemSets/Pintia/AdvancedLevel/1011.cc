#include <bits/stdc++.h>
using namespace std;
int main() {
    vector<float> W( 3 ), T( 3 ), L( 3 );
    vector<float> res1( 3 );
    vector<char> res2( 3 );
    for( int i = 0; i < 3; i++ ) {
        float min = -1;
        cin >> W[i] >> T[i] >> L[i];
        if( W[i] > min ) {
            min = W[i];
            res1[i] = W[i];
            res2[i] = 'W';
        }
        if( T[i] > min ) {
            min = T[i];
            res1[i] = T[i];
            res2[i] = 'T';
        }
        if( L[i] > min ) {
            min = L[i];
            res1[i] = L[i];
            res2[i] = 'L';
        }
    }
    for_each( res2.begin(), res2.end(), []( char c ) {
        cout << c << " ";
    } );

    float res = 1;
    for_each( res1.begin(), res1.end(), [ & ]( float bet ) {
        res *= bet;
    } );
    cout << fixed << setprecision( 2 ) << ( res * 0.65 - 1 ) * 2;
}