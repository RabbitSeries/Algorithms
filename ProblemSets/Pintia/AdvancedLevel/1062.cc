#include <bits/stdc++.h>
using namespace std;
int main() {
    int N, L, H, filterCnt;
    cin >> N >> L >> H;
    vector<tuple<int, int, string, int, int>> manList;
    filterCnt = N;
    for ( int i = 0; i < N; i++ ) {
        string id;
        int v, t, tag;
        cin >> id >> v >> t;
        if ( v >= H && t >= H ) {
            tag = 3;
        } else if ( v >= H && t >= L && t < H ) {
            tag = 2;
        } else if ( v >= L && t >= L && v < H && v >= t ) {
            tag = 1;
        } else if ( v >= L && t >= L ) {
            tag = 0;
        } else {
            continue;
        }
        manList.emplace_back( tag, v + t, id, v, t );
    }
    using info = tuple<int, int, string, int, int>;
    sort( manList.begin(), manList.end(), []( info& m1, info& m2 ) {
        if ( get<0>( m1 ) != get<0>( m2 ) ) {
            return get<0>( m1 ) > get<0>( m2 );
        } else if ( get<1>( m1 ) != get<1>( m2 ) ) {
            return get<1>( m1 ) > get<1>( m2 );
        } else if ( get<3>( m1 ) != get<3>( m2 ) ) {
            return get<3>( m1 ) > get<3>( m2 );
        } else
            return get<2>( m1 ) < get<2>( m2 );
    } );
    stringstream ss;
    ss << manList.size() << endl;
    for ( auto const& [tag, total, id, v, t] : manList ) {
        ss << id << " " << v << " " << t << endl;
    }
    cout << ss.str();
}

// struct info {
//     info( int tag, int total, string id, int v, int t ) : tag{ tag }, total{ total }, v{ v }, t{ t }, id{ id } {}
//     int tag, total;
//     string id;
//     int v, t;
// };
// structure binding requires specific declaration order