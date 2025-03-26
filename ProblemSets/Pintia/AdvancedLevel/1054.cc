#include <bits/stdc++.h>
using namespace std;
// int hashMap[1 << 24]{ 0 };
int main() {
    int M, N, color, dominantCnt = -1, dominantColor = -1;
    cin >> M >> N;
    array<int, 1 << 24> hashMap;
    hashMap.fill( 0 );
    for ( int i = 0; i < M; i++ ) {
        for ( int j = 0; j < N; j++ ) {
            cin >> color;
            hashMap[color]++;
            if ( hashMap[color] > dominantCnt ) {
                dominantCnt++;
                dominantColor = color;
            }
        }
    }
    cout << dominantColor;
}