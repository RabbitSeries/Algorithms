#include <bits/stdc++.h>
using namespace std;
int main() {
    int caseCnt;
    cin >> caseCnt;
    for ( int i = 1; i <= caseCnt; i++ ) {
        long long int A, B, C;
        cin >> A >> B >> C;
        cout << "Case #" << i << ": ";
        if ( A > 0 && B > 0 && A > LLONG_MAX - B ) {
            cout << "true";
        } else if ( A < 0 && B < 0 && A < LLONG_MIN - B )
            cout << "false";
        else
            cout << boolalpha << ( A + B > C );
        cout << endl;
    }
    return 0;
}