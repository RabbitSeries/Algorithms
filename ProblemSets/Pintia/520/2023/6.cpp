#include <stdlib.h>
#include <string.h>

#include <iostream>
using namespace std;
int main() {
    int c, count = 0;
    string num, tpnum( "" );
    cin >> c;
    for ( int i = 0, na, nb; i < c; i++ ) {
        na = nb = 0;
        cin >> num;
        if ( num[0] != '-' ) {
            if ( num.size() % 2 == 0 ) {
                int halflen = num.size() / 2;
                string anum = num.substr( 0, halflen );
                string bnum = num.substr( halflen, halflen );
                for ( int j = 0; j < halflen - 1; j++ ) {
                    if ( ( anum[j] < anum[j + 1] ) ) {
                        na = 1;
                        break;
                    }
                }
                for ( int j = 0; j < halflen - 1; j++ ) {
                    if ( ( bnum[j] > bnum[j + 1] ) ) {
                        nb = 1;
                        break;
                    }
                }
                if ( !na && !nb ) {
                    int suma( 0 ), sumb( 0 );
                    for ( int si = 0; si < halflen; si++ ) {
                        suma += anum[si] - '0';
                        sumb += bnum[si] - '0';
                    }
                    if ( ( suma + sumb ) % 2 ) {
                        count++;
                        if ( count == 0 ) {
                            tpnum = num;
                        } else {
                            if ( atof( tpnum.c_str() ) < atof( num.c_str() ) ) {
                                tpnum = num;
                            }
                        }
                    }
                }
            }
        }
    }
    cout << count << endl;
    if ( tpnum != "" ) {
        cout << tpnum;
    }
    return 0;
}