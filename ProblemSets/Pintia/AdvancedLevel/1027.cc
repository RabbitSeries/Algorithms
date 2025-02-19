#include <bits/stdc++.h>
using namespace std;
int main() {
    cout << "#";
    for( int i = 0; i < 3; i++ ) {
        int n;
        cin >> n;
        cout << uppercase << hex << n / 13 << n % 13;
    }
    return 0;
}