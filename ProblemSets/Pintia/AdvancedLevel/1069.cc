#include <bits/stdc++.h>
using namespace std;
using ull = unsigned long long;
string itos( ull num ) {
    return ( ostringstream() << right << setw( 4 ) << setfill( '0' ) << num ).str();
}
string reversed( string s ) {
    reverse( s.begin(), s.end() );
    return s;
}
string sorted( string s ) {
    sort( s.begin(), s.end() );
    return s;
}
bool sameDigit( int num ) {
    set<char> s;
    for ( auto c : itos( num ) ) {
        s.insert( c );
    }
    return s.size() == 1;
}
int main() {
    int N;
    cin >> N;
    vector<tuple<string, string, string>> resList;
    if ( sameDigit( N ) ) {
        resList.emplace_back( itos( N ), itos( N ), itos( 0 ) );
    } else {
        do {
            string sortDigits = sorted( itos( N ) );
            int lN = stoi( sortDigits ), rN = stoi( reversed( sortDigits ) );
            N = abs( lN - rN );
            resList.emplace_back( itos( max( lN, rN ) ), itos( min( lN, rN ) ), itos( N ) );
        } while ( N != 6174 );
    }
    for ( auto [l, r, res] : resList ) {
        cout << l << " - " << r << " = " << res << endl;
    }
}