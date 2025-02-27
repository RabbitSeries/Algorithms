#include <iostream>
using namespace std;
int main() {
    int zodvalid[12][10], zodvalidn[12], zodinvalid[12][10], zodinvalidn[12];
    int zodn;
    for ( int i = 0; i < 12; i++ )  // initialize
    {
        cin >> zodn;
        cin >> zodvalidn[zodn];
        for ( int j = 0; j < zodvalidn[zodn]; j++ ) {
            cin >> zodvalid[zodn][j];
        }
        cin >> zodinvalidn[zodn];
        for ( int j = 0; j < zodinvalidn[zodn]; j++ ) {
            cin >> zodinvalid[zodn][j];
        }
    }
    int n, zod1, zod2, flagCP, flagNCP, flagNA;
    cin >> n;
    for ( int i = 0; i < n; i++ ) {
        flagCP = flagNCP = flagNA = 0;
        cin >> zod1 >> zod2;
        for ( int j = 0; j < zodvalidn[zod1]; j++ ) {
            if ( zodvalid[zod1][j] == zod2 ) {
                flagCP = 1;
                break;
            }
        }
        if ( flagCP ) {
            cout << "Yes" << endl;
            continue;
        } else {
            for ( int j = 0; j < zodinvalidn[zod1]; j++ ) {
                if ( zodinvalid[zod1][j] == zod2 ) {
                    flagNCP = 1;
                    break;
                }
            }
            if ( flagNCP ) {
                cout << "No" << endl;
                continue;
            } else {
                for ( int j = 0; j < zodvalidn[zod2]; j++ ) {
                    if ( zodvalid[zod2][j] == zod1 ) {
                        flagCP = 1;
                        break;
                    }
                }
                if ( flagCP ) {
                    cout << "Yes" << endl;
                    continue;
                } else {
                    for ( int j = 0; j < zodinvalidn[zod2]; j++ ) {
                        if ( zodinvalid[zod2][j] == zod1 ) {
                            flagNCP = 1;
                            break;
                        }
                    }
                    if ( flagNCP ) {
                        cout << "No" << endl;
                        continue;
                    }
                }
            }
        }
        cout << "NA" << endl;
    }
    return 0;
}