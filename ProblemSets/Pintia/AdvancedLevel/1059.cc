#include <bits/extc++.h>
#include <bits/stdc++.h>
using namespace __gnu_pbds;
using namespace std;
int main() {
    using ll = long long int;
    ll input, res;
    cin >> input;
    res = input;
    // map<int, int> exp;
    tree<int, int> exp;
    for ( int i = 2; i <= input && input != 1; i++ ) {
        while ( input % i == 0 ) {
            exp[i]++;
            input /= i;
        }
    }
    cout << res << "=";
    if ( exp.empty() ) {
        cout << res;
    } else {
        stringstream buf;
        for ( auto const& [factor, e] : exp ) {
            buf << "*" << factor;
            if ( e != 1 ) {
                buf << "^" << e;
            }
        }
        cout << buf.str().substr( 1 );
    }
}