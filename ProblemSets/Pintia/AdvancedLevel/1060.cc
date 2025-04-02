#include <bits/stdc++.h>
using namespace std;
struct sigNum {
    size_t exp = 0;
    string digits;
    sigNum( string num, size_t sigCnt ) {
        while ( num.size() > 0 && num[0] == '0' ) num = num.substr( 1 );
        size_t pointPos = num.find( '.' );
        if ( pointPos != string::npos ) {
            if ( num[0] == '.' ) {
                exp = 0;
                num = num.substr( 1 );
                while ( num.size() > 0 && num[0] == '0' ) {
                    num = num.substr( 1 );
                    exp--;
                }
                if ( num.empty() ) {
                    exp = 0;
                }
            } else {
                exp = pointPos;
                num = num.substr( 0, pointPos ) + num.substr( pointPos + 1 );
            }
        } else {
            exp = num.length();
        }
        num = num.substr( 0, min( num.length(), sigCnt ) );  // chop
        stringstream ss;
        ss << setfill( '0' ) << setw( sigCnt ) << left << num;
        digits = ss.str();
    }
    string toString() {
        return "0." + digits + "*10^" + to_string( exp );
    }
};
int main() {
    string num1, num2;
    int sigCnt;
    cin >> sigCnt >> num1 >> num2;
    sigNum n1( num1, sigCnt ), n2( num2, sigCnt );
    if ( ( n1.exp == n2.exp && n1.digits == n2.digits ) ) {
        cout << "YES " << "0." << n1.digits << "*" << "10^" << n1.exp;
    } else {
        cout << "NO " << n1.toString() << " " << n2.toString();
    }
}