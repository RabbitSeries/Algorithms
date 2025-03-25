#include <bits/stdc++.h>
using namespace std;
int main() {
    int m, n, caseCnt;
    cin >> m >> n >> caseCnt;
    for ( int i = 0; i < caseCnt; i++ ) {
        stack<int> simulate;
        vector<int> popList( n );
        for ( int i = 0; i < n; i++ )
            cin >> popList[i];
        for ( int i = 1, j = 0; i <= n; i++ ) {
            simulate.push( i );
            if ( simulate.size() > m ) break;
            while ( !simulate.empty() && simulate.top() == popList[j] ) {
                simulate.pop();
                j++;
            }
        }
        cout << ( simulate.empty() ? "YES\n" : "NO\n" );
    }
}