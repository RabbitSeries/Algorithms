#include <bits/stdc++.h>
using namespace std;
struct signTime {
    signTime( int h, int m, int s ) : hour( h ), minute( m ), seconds( s ) {}
    int hour, minute, seconds;
    bool isLater( const signTime& t ) const {
        return ( ( hour != t.hour ) ? ( hour > t.hour ) : ( ( minute != t.minute ) ? ( minute > t.minute ) : ( seconds > t.seconds ) ) );
    }
};

int main() {
    int n;
    stringstream ss;
    string buf;
    getline( cin, buf );
    stringstream( buf ) >> n;
    int i = 0;
    string earliestPersonId = "", latestPersonId;
    signTime earliestSignTime{ 24, 60, 60 }, latestSignTime{ -1, 0, 0 };
    while ( i++ < n ) {
        string id, inTime, outTime;
        getline( cin, buf );
        stringstream( buf ) >> id >> inTime >> outTime;
        signTime inT{ stoi( inTime.substr( 0, 2 ) ), stoi( inTime.substr( 3, 2 ) ), stoi( inTime.substr( 6, 2 ) ) };
        signTime outT{ stoi( outTime.substr( 0, 2 ) ), stoi( outTime.substr( 3, 2 ) ), stoi( outTime.substr( 6, 2 ) ) };
        if ( !inT.isLater( earliestSignTime ) ) {
            earliestPersonId = id;
            earliestSignTime = inT;
        }
        if ( outT.isLater( latestSignTime ) ) {
            latestPersonId = id;
            latestSignTime = outT;
        }
    }
    cout << earliestPersonId << " " << latestPersonId;
}