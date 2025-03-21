#include <bits/stdc++.h>
using namespace std;
long long Dijkstra( long long n, int bound ) {
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<>> pq;
    pq.emplace( n, 0 );
    while ( !pq.empty() ) {
        auto [curN, t] = pq.top();
        pq.pop();
        if ( curN == 0 ) return t;
        for ( int i = ( curN % 2 ? 1 : 2 ); i <= bound; i += 2 ) {
            if ( curN - i >= 0 )
                pq.emplace( curN - i, t + 1 );
        }
    }
}
int main() {
    int caseCnt, curN, bound;
    cin >> caseCnt;
    for ( int i = 0; i < caseCnt; i++ ) {
        cin >> curN >> bound;
        cout << Dijkstra( curN, bound ) << endl;
    }
}