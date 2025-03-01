#include <bits/stdc++.h>
using namespace std;
int main() {
    int accountCnt;
    cin >> accountCnt;
    vector<pair<string, string>> resList;
    for ( int i = 0; i < accountCnt; i++ ) {
        string curUsr, curPsw;
        cin >> curUsr >> curPsw;
        regex re( R"([1lO0])" );
        if ( regex_search( curPsw, re ) ) {
            while ( curPsw.find( "1" ) != string::npos )
                curPsw.replace( curPsw.find( "1" ), 1, "@" );
            while ( curPsw.find( "l" ) != string::npos )
                curPsw.replace( curPsw.find( "l" ), 1, "L" );
            while ( curPsw.find( "O" ) != string::npos )
                curPsw.replace( curPsw.find( "O" ), 1, "o" );
            while ( curPsw.find( "0" ) != string::npos )
                curPsw.replace( curPsw.find( "0" ), 1, "%" );
            resList.emplace_back( curUsr, curPsw );
        }
    }
    if ( resList.empty() ) {
        cout << "There " << ( accountCnt == 1 ? "is " : "are " ) << accountCnt << " " << ( accountCnt == 1 ? "account" : "accounts" ) << " and no account is modified";
    } else {
        cout << resList.size() << endl;
        for ( auto const &[usr, psw] : resList ) {
            cout << usr << " " << psw << endl;
        }
    }
}