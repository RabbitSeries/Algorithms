#include <bits/stdc++.h>
using namespace std;
int main() {
    size_t infoCnt, sortCol;
    cin >> infoCnt >> sortCol;
    vector<tuple<string, string, int>> infoList( infoCnt );
    for( int i = 0; i < infoCnt; i++ ) {
        cin >> get<0>( infoList[i] ) >> get<1>( infoList[i] ) >> get<2>( infoList[i] );
    }
    sort( infoList.begin(), infoList.end(), [ & ]( tuple<string, string, int> const& i1, tuple<string, string, int> const& i2 ) {
        switch( sortCol ) {
        case 1:
            return get<0>( i1 ) < get<0>( i2 );
        case 2:
            return get<1>( i1 ) == get<1>( i2 ) ? get<0>( i1 ) < get<0>( i2 ) : get<1>( i1 ) < get<1>( i2 );
        case 3:
            return get<2>( i1 ) == get<2>( i2 ) ? get<0>( i1 ) < get<0>( i2 ) : get<2>( i1 ) < get<2>( i2 );
        default:
            return false;
        }
    } );
    for( auto [id, name, grade] : infoList ) {
        cout << setw( 6 ) << setfill( '0' ) << id << " " << name << " " << grade << endl;
    }
}