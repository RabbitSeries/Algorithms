#include <bits/stdc++.h>
using namespace std;
int getAlpha( char c ) {
    return isupper( c ) ? c - 'A' : c - 'a';
}
int countSame( string& A, string& B ) {
    int res = 0;
    for ( size_t i = 0; i < A.length(); i++ ) {
        int a = getAlpha( A[i] ), b = getAlpha( B[i] );
        if ( a == b ) {
            res++;
        }
    }
    return res;
}
bool match( string& A, string& B ) {
    for ( size_t i = 0; i < A.length(); i++ ) {
        if ( getAlpha( A[i] ) != getAlpha( B[i] ) ) {
            for ( size_t j = i + 1; j < A.length(); j++ ) {
                if ( getAlpha( A[j] ) != getAlpha( B[j] ) && getAlpha( A[i] ) == getAlpha( B[j] ) && getAlpha( A[j] ) == getAlpha( B[i] ) ) {
                    return true;
                }
            }
        }
    }
    return false;
}
bool match1( string& A, string& B ) {
    for ( size_t i = 0; i < A.length(); i++ ) {
        if ( getAlpha( A[i] ) != getAlpha( B[i] ) ) {
            for ( size_t j = i + 1; j < A.length(); j++ ) {
                swap( A[i], A[j] );
                if ( countSame( A, B ) >= 4 ) {
                    return true;
                }
                swap( A[i], A[j] );
            }
        }
    }
    return false;
}
int main() {
    int trial;
    cin >> trial;
    for ( int i = 0; i < trial; i++ ) {
        string A, B;
        cin >> A >> B;
        if ( A.size() == B.size() ) {
            int counter = countSame( A, B );
            if ( counter >= 4 ) {
                cout << "how pay\n";
                continue;
            }
            if ( counter == 2 && match( A, B ) ) {
                cout << "how pay\n";
                continue;
            }
            if ( counter == 3 && match1( A, B ) ) {
                cout << "how pay\n";
                continue;
            }
        }
        cout << "bull pay\n";
    }
}
