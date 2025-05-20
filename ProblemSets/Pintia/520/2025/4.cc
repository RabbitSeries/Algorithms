#include <bits/stdc++.h>
using namespace std;
map<int, int> relationShip;
int main() {
    int coupleCnt;
    cin >> coupleCnt;
    for ( int i = 0; i < coupleCnt; i++ ) {
        int a, b;
        cin >> a >> b;
        relationShip[a] = b;
        relationShip[b] = a;
    }
    cin >> coupleCnt;
    for ( int i = 0; i < coupleCnt; i++ ) {
        int a, b;
        cin >> a >> b;
        if ( relationShip.contains( a ) && relationShip[a] == b ) {
            cout << "(~_~)\n";
        } else {
            cout << "o(@O@)o\n";
        }
    }
}
