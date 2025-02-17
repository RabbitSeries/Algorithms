#include <bits/stdc++.h>
using namespace std;
string reverse_str( string number ) {
    string reverseStr( number.length(), ' ' );
    reverse_copy( number.begin(), number.end(), reverseStr.begin() );
    return reverseStr;
}
bool isPalindromic( string number ) {
    if( number.length() == 1 ) {
        return true;
    }
    int mid = number.length() / 2;
    // 4 -> 2 [0,2) [2,4) 3-> 1 [0,1) [2,3) 2->1 [0,1) [1,2)
    string left = number.substr( 0, mid ), right = number.length() % 2 == 0 ? number.substr( mid, number.length() ) : number.substr( mid + 1, number.length() );
    return left == reverse_str( right );
}
string addUp( string num1, string num2 ) {
    assert( num1.length() == num2.length() );
    string res = "";
    int carry = 0;
    for( int i = num1.length() - 1; i >= 0; i-- ) {
        int curCarry = ( carry + num1[i] - '0' + num2[i] - '0' ) / 10;
        res = to_string( ( carry + num1[i] - '0' + num2[i] - '0' ) % 10 ) + res;
        carry = curCarry;
    }
    if( carry != 0 ) {
        res = to_string( carry ) + res;
    }
    return res;
}
int main() {
    string number;
    int step;
    cin >> number >> step;
    int curStep = 0;
    while( !isPalindromic( number ) ) {
        if( curStep < step ) {
            number = addUp( number, reverse_str( number ) );
            curStep++;
        } else {
            cout << number << endl << step;
            return 0;
        }
    }
    cout << number << endl << curStep;
    return 0;
}