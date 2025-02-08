#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ll;

ll powLL( ll radix, ll times ) {
    static map<ll, map<ll, ll>> cache;
    if( cache.count( radix ) != 0 && cache.at( radix ).count( times ) != 0 ) {
        return cache.at( radix ).at( times );
    }
    if( times == 0 ) {
        cache[radix][0] = 1;
        return 1;
    }
    cache[radix][times] = radix * powLL( radix, times - 1 );
    return cache[radix][times];

}

ll stringToLL( string num, ll radix ) {
    ll res = 0;
    reverse( num.begin(), num.end() );
    ll times = 0;
    for( auto c : num ) {
        ll mul = powLL( radix, times );
        if( isdigit( c ) ) {
            res += ( c - '0' ) * mul;
        } else
            res += ( c - 'a' + 10 ) * mul;
        times++;
    }
    return res;
}

int main() {
    string n1, n2;
    int tag, radix;
    ll num1;
    string num2;
    cin >> n1 >> n2 >> tag >> radix;

    if( tag == 1 ) {
        num1 = stringToLL( n1, radix );
        num2 = n2;
    } else {
        num1 = stringToLL( n2, radix );
        num2 = n1;
    }
    if( num1 < 0 ) {
        cout << "Impossible";
    }

    ll minRadix = 0;
    for_each( num2.begin(), num2.end(), [ & ]( char c ) {
        if( isdigit( c ) ) {
            minRadix = max( (ll)( c - '0' ), minRadix );
        } else
            minRadix = max( (ll)( c - 'a' + 10 ), minRadix );
    } );


    ll left = minRadix + 1, right = max( minRadix, num1 ) + 1;
    while( left <= right ) {
        ll mid = left + ( right - left ) / 2;
        ll trans = stringToLL( num2, mid );
        int cmp = -1;
        if( trans < num1 ) {
            cmp = -1;
        } else if( trans > num1 ) {
            cmp = 1;
        } else {
            cmp = 0;
        }

        if( cmp == 0 ) {
            cout << mid;
            return 0;
        } else if( cmp == 1 ) {
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    cout << "Impossible";
    return 0;
}

