#include "bits/stdc++.h"
using namespace std;

int main() {
    int cnt = 0, res = 1;
    cin >> cnt;
    int i = 0;
    while( i++ < cnt ) {
        int tmp = -1;
        cin >> tmp;
        if( tmp == 1 );
        else if( tmp == 0 ) {
            res++;
        }
    }
    cout << res;
    return 0;
}