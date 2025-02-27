#include "bits/stdc++.h"
using namespace std;

int main() {
    int cnt = 0, dan = 0, nong = 0;
    cin >> cnt;
    int i = 0;
    while( i++ < cnt ) {
        string tmp;
        cin >> tmp;
        if( i != cnt )
            getchar();
        if( tmp == "haha" || tmp == "wawa" ) {
            nong++;
        }
        else if( tmp == "enen" || tmp == "hehe" ) {
            dan++;
        }
    }
    cout << nong << " " << dan << endl;
    if( dan > nong ) {
        cout << "dan ren";
    }
    else if( dan < nong ) {
        cout << "nong ren";
    }
    else {
        cout << "xian ren";
    }
    return 0;
}