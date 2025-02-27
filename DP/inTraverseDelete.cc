#include <bits/stdc++.h>
using namespace std;

void inTraverseDelete( vector<int>& num, int remainCnt ) {
    sort( num.begin(), num.end(), less<>{} );
    int curPos = remainCnt;
    for ( int i = remainCnt; i < num.size(); i++ )
        if ( num[i] != num[i - remainCnt] ) num[curPos++] = num[i];
    num.erase( num.begin() + curPos, num.end() );
    for ( auto n : num ) {
        cout << n << " ";
    }
}

int main() {
    vector<int> num{ 1, 2, 4, 5, 5, 6, 6, 3, 3, 4, 3 };
    inTraverseDelete( num, 1 );
}