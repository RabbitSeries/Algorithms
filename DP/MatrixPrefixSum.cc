#include <cstdio>
#include <iostream>
#include <sstream>
#include <vector>
#include <cmath>
using namespace std;
int main() {
    string buf;
    int matrix_size;
    getline( cin, buf );
    stringstream( buf ) >> matrix_size;
    // If only use matrix_size to create this space, the dp eqation needs multiple dimensional judgement
    // i-1, j-1 ; i-1 ; j-1; 0,0;
    vector<vector<int>> prefix_sum( matrix_size + 1, vector<int>( matrix_size + 1, 0 ) );
    for( int i = 1; i <= matrix_size; i++ ) {
        getline( cin, buf );
        for( int j = 1; j <= matrix_size; j++ ) {
            prefix_sum[i][j] = prefix_sum[i - 1][j] + prefix_sum[i][j - 1] - prefix_sum[i - 1][j - 1] + buf[j - 1] - '0';
        }
    }
    for( int sz = 1; sz <= matrix_size; sz++ ) {
        int curCnt = 0, target = (int)pow( sz, 2 );
        if( target % 2 == 0 )
            for( int i = 1; i + sz - 1 <= matrix_size; i++ ) {
                for( int j = 1; j + sz - 1 <= matrix_size; j++ ) {
                    if( ( prefix_sum[i + sz - 1][j + sz - 1] - prefix_sum[i + sz - 1][j - 1] - prefix_sum[i - 1][j + sz - 1] + prefix_sum[i - 1][j - 1] ) * 2 == target ) {
                        curCnt++;
                    }
                }
            }
        printf( "%d\n", curCnt );
    }
}