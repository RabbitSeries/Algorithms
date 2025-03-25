#include <bits/stdc++.h>
// This algorithm lower the time complexity from DP O(n) to O(log(n)) andd space from O(n) to O(1)
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