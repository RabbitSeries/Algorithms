#include <bits/stdc++.h>
using namespace std;
using ull = unsigned long long;
optional<ull> stringToLL( string const& num, ull radix ) {
    ull res = 0;
    for ( auto c : num ) {
        ull v = isdigit( c ) ? ( c - '0' ) : ( c - 'a' + 10 );
        // if ( v <= radix ) {// this in pre-ensured
        //     return nullopt;
        // }
        if ( ULLONG_MAX / radix < res || ( ULLONG_MAX - res * radix < v ) ) {
            return nullopt;
        }
        res = res * radix + v;
    }
    return res;
}
optional<ull> findRadix( string const& n1, string const& num2, int radix ) {
    auto num1 = stringToLL( n1, radix );
    if ( !num1.has_value() ) {
        return nullopt;
    }
    char it = *max_element( num2.begin(), num2.end() );
    ull left = ( isdigit( it ) ? it - '0' : it - 'a' + 10 ) + 1, right = max( num1.value() + 1, left );  // ull left = ( isdigit( it ) ? it - '0' : it - 'a' + 10 ) + 1, right = INT_MAX;
    optional<ull> res = nullopt;
    while ( left <= right ) {
        ull mid = left + ( right - left ) / 2;
        auto trans = stringToLL( num2, mid );
        if ( !trans.has_value() || trans.value() > num1.value() ) {
            right = mid - 1;
        } else if ( trans.value() < num1.value() ) {
            left = mid + 1;
        } else {
            res = mid;
            right = mid - 1;  // continue to search the minimum
        }
    }
    return res;
}
int main() {
    string n1, n2;
    int tag, radix;
    cin >> n1 >> n2 >> tag >> radix;
    optional<ull> res = tag == 1 ? findRadix( n1, n2, radix ) : findRadix( n2, n1, radix );
    res.has_value() ? cout << res.value() : cout << "Impossible";
    return 0;
}
// 110 6 1 2
// The minimum right value is 110 + 1  (6) -> 7-6 -> (6)  (10)-> 7-7 6-6 -> (6)
// Any answer that is larger than 6 is a solution, so must find the minimum solution!
// if ( radix == 2 && unChangeableNum == "110" && unChangeableNum.size() == 3 && changableNUm.size() == 1 && isalnum( changableNUm[0] ) && ( changableNUm[0] - '0' == 6 ) && verify != 0 && res == 7 && ( unlimitedRes > ( INT_MAX / 2 ) ) && unlimitedRes != res && stringToLL( changableNUm, unlimitedRes ) == verify && pow( unlimitedRes, changableNUm.size() ) < INT_MAX ) {
//     throw exception();
// }