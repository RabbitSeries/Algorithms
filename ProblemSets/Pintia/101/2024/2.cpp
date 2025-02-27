#include "bits/stdc++.h"
using namespace std;

int main() {
    int num = 0;
    cin >> num;
    cout << num << endl;
    if( num == 0 ) {
        cout << "xian ren";
    }
    else if( num > 0 ) {
        cout << "nong ren";
    }
    else {
        cout << "dan ren";
    }
    return 0;
}