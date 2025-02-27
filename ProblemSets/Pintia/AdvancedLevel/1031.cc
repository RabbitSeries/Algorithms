#include <bits/stdc++.h>
using namespace std;
int main() {
    string input;
    getline( cin, input );
    int row = -1, col = -1;
    for ( int i = input.length(); i >= 1; i-- ) {
        for ( int j = i; j >= 0; j-- ) {
            if ( 2 * j + i - 2 == input.length() ) {
                if ( j > row ) {
                    row = j;
                    col = i;
                }
            }
        }
    }
    for ( int r = 0; r < row - 1; r++ ) {
        cout << input[r];
        for ( int c = 1; c < col - 1; c++ ) cout << " ";
        cout << input[input.length() - 1 - r] << endl;
    }
    for ( int c = 0; c < col; c++ ) cout << input[row - 1 + c];
    return 0;
}