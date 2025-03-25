#include <bits/stdc++.h>
using namespace std;
int main() {
    int coinCnt, pay;
    cin >> coinCnt >> pay;
    vector<int> coinList( coinCnt );
    for ( int i = 0; i < coinCnt; i++ ) {
        cin >> coinList[i];
    }
    sort( coinList.begin(), coinList.end() );
    for ( int i = 0; i < coinCnt - 1; i++ ) {
        int pairCoin = pay - coinList[i];
        if ( [&]() -> bool {
                 int l = i + 1, r = coinCnt - 1;
                 while ( l <= r ) {
                     int mid = l + ( r - l ) / 2;
                     if ( coinList[mid] == pairCoin ) {
                         return true;
                     } else if ( coinList[mid] > pairCoin ) {
                         r = mid - 1;
                     } else {
                         l = mid + 1;
                     }
                 }
                 return false;
             }() ) {
            cout << coinList[i] << " " << pairCoin;
            return 0;
        }
    }
    cout << "No Solution";
    return 0;
}