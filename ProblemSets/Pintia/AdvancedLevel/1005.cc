#include <bits/stdc++.h>
using namespace std;
int main() {
    string numList;
    cin >> numList;
    int sum = accumulate( numList.begin(), numList.end(), 0, []( int init, char c ) {
        return init + c - '0';
    } );
    bool first = true;
    vector<string> dict{ "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine" };
    for ( char c : to_string( sum ) ) {
        cout << ( !first ? ( " " + dict[c - '0'] ) : dict[c - '0'] );
        first = false;
    }
}