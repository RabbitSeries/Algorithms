#include <bits/stdc++.h>
using namespace std;
int main() {
    string day1, day2, min1, min2;
    cin >> day1 >> day2 >> min1 >> min2;
    int day = 0, hour = 0, min = 0;
    bool dayFound = false;
    size_t minLen = ::min( day1.length(), day2.length() );
    for ( size_t i = 0; i < minLen; i++ ) {
        char c = day1[i];
        if ( !dayFound ) {
            if ( isalpha( c ) && isupper( c ) && c <= 'G' && day2[i] == c ) {
                day = c - 'A';
                dayFound = true;
            }
        } else {
            if ( ( isalpha( c ) && isupper( c ) && c <= 'N' || isdigit( c ) ) && day2[i] == c ) {
                hour = isdigit( c ) ? ( c - '0' ) : ( 10 + c - 'A' );
                break;
            }
        }
    }
    minLen = ::min( min1.length(), min2.length() );
    for ( size_t i = 0; i < minLen; i++ ) {
        if ( isalpha( min1[i] ) && min1[i] == min2[i] ) {
            min = i;
            break;
        }
    }
    printf( "%s %02d:%02d", ( vector<string>{ "MON", "TUE", "WED", "THU", "FRI", "SAT", "SUN" }[day].c_str() ), hour, min );
}