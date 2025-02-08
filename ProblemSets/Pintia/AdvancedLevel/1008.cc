#include <bits/stdc++.h>
using namespace std;
int main() {
    int N, count = 0;
    cin >> N;
    vector<int> series( N );
    for( int i = 0; i < N; i++ ) {
        cin >> series[i];
    }
    int i, temp = 0;
    count += 5 * N;
    for( i = 0; i < N; i++ ) {
        if( series[i] > temp ) {
            count += 6 * ( series[i] - temp );
        } else {
            count += 4 * ( temp - series[i] );
        }
        temp = series[i];
    }
    if( i == N )
        cout << count;
    return 0;
}