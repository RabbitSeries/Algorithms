#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
int main() {
    string numStr;
    cin >> numStr;
    int weight = (int)pow( 10, numStr.size() - 1 ), num = stoi( numStr ), res = numStr[0] == '1' ? ( num - ( numStr[0] - '0' ) * weight + 1 ) : weight;
    for ( int i = 1; i < numStr.size(); i++ ) {
        weight /= 10;
        res += ( stoi( numStr.substr( 0, i ) ) + ( numStr[i] > '1' ) ) * weight;
        res += ( numStr[i] == '1' ) * ( num - stoi( numStr.substr( 0, i + 1 ) ) * weight + 1 );
    }
    cout << res;
}