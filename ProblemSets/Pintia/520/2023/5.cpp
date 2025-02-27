#include <string.h>

#include <algorithm>
#include <iostream>
using namespace std;

int main() {
    char reva[10] = { '0', '1', '\0', '\0', '\0', '\0', '9', '\0', '8', '6' };
    int n;
    string reastr;
    char rea[20], tprea[20];
    cin >> n;
    for ( int i = 0; i < n; i++ ) {
        cin >> reastr;
        strcpy( rea, reastr.c_str() );
        // for (int j = 0; j < strlen(rea) / 2; j++)
        // {
        //     rea[strlen(rea) - 1 - j] = rea[j];
        // }
        // strcpy(rea, strrev(rea));
        int j;
        for ( j = 0; j < strlen( rea ); j++ ) {
            if ( reva[rea[j] - '0'] )
                rea[j] = reva[rea[j] - '0'];
            else {
                cout << "bu ke neng" << endl;
                break;
            }
        }
        if ( j == strlen( rea ) ) {
            if ( string( rea ) == reastr ) {
                printf( "%s\n", rea );
            } else {
                cout << "bu ke neng" << endl;
            }
        }
    }
    return 0;
}
