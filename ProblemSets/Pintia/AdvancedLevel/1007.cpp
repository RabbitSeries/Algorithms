#include <bits/stdc++.h>
using namespace std;
int main() {
    string input = "HELLO~WORLD!";
    stringstream ss( input );
    string output = string( input.length(), ' ' );
    std::transform( input.begin(), input.end(), output.begin(), []( char c ) {
        return tolower( c );
    } );
    cout << output.find_first_not_of( "abcdedghijklmnopqrstuvwxyz" );
    int splitPos;
    string reverse = string( input.length(), ' ' );
    reverse_copy( input.begin(), input.end(), reverse.begin() );
    int i = reverse.length() - 1;
    for_each( reverse.begin(), reverse.end(), [ &i, &splitPos ]( char c ) {
        if( !isalpha( c ) ) {
            splitPos = i;
        }
        i--;
    } );
    cout << splitPos;
    cout << boolalpha << false << endl;
    cout << false << endl;
    return 0;
}