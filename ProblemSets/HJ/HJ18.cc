#include <bits/stdc++.h>
using namespace std;
bool withinRange( int num ) {
    return num >= 0 && num <= 255;
}
int main() {
    string buf;
    vector<int> validCnt( 5, 0 );
    int fault = 0, privateCnt = 0;
    while( getline( cin, buf ) ) {
        regex splitRe( R"((.*)~(.*))" );
        smatch m;
        regex_search( buf, m, splitRe );
        if( m.size() == 3 ) {
            string ip = m[1].str(), mask = m[2].str();
            regex re( R"((\d+)\.(\d+)\.(\d+)\.(\d+))" );
            smatch ipM, maskM;
            regex_search( ip, ipM, re );
            regex_search( mask, maskM, re );
            if( ipM.size() == 5 && maskM.size() == 5 ) {
                vector<int> matchIpList;
                for( int i = 1; i < 5; i++ ) matchIpList.push_back( stoi( ipM[i] ) );
                if( matchIpList[0] == 0 || matchIpList[0] == 127 ) continue;
                bool hostValid = all_of( matchIpList.begin() + 1, matchIpList.end(),
                    withinRange );
                hostValid = ( hostValid && matchIpList[0] <= 255 );
                if( !hostValid ) {
                    fault++;
                    continue;
                }
                vector<int> matchMaskList;
                for( int i = 1; i < 5; i++ ) matchMaskList.push_back( stoi( maskM[i] ) );
                string checkStr = accumulate( matchMaskList.begin(), matchMaskList.end(),
                    string( "" ), []( string init, int num ) {
                    return init + bitset<8>( num ).to_string();
                } );
                if( checkStr.find( '0' ) == 0 || checkStr.find( '0' ) == string::npos ) {
                    fault++;
                    continue;
                }
                bool maskValid = all_of( checkStr.begin() + checkStr.find( '0' ),
                    checkStr.end(), []( char c ) {
                    return c != '1';
                } );
                if( !maskValid ) {
                    fault++;
                    continue;
                }
                if( matchIpList[0] > 0 && matchIpList[0] < 127 ) {
                    validCnt[0]++;
                    if( matchIpList[0] == 10 ) {
                        privateCnt++;
                    }
                } else if( matchIpList[0] > 127 && matchIpList[0] < 192 ) {
                    validCnt[1]++;
                    if( matchIpList[0] == 172 && matchIpList[1] >= 16 && matchIpList[1] <= 31 ) {
                        privateCnt++;
                    }
                } else if( matchIpList[0] >= 192 && matchIpList[0] < 224 ) {
                    validCnt[2]++;
                    if( matchIpList[0] == 192 && matchIpList[1] == 168 ) {
                        privateCnt++;
                    }
                } else if( matchIpList[0] >= 224 && matchIpList[0] < 240 ) {
                    validCnt[3]++;
                } else if( matchIpList[0] >= 240 && matchIpList[0] <= 255 ) {
                    validCnt[4]++;
                }
            } else {
                fault++;
            }
        } else {
            fault++;
        }
    }
    for( int num : validCnt ) cout << num << " ";
    cout << fault << " " << privateCnt;
}