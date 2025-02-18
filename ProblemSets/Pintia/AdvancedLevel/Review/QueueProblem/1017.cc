#include <bits/stdc++.h>
using namespace std;
struct hms {
    int arriveTime, needed;
    hms( int as = 0, int ns = 0 ) : arriveTime( as ), needed( ns ) {};
    bool operator>( hms const& c ) const {
        return arriveTime > c.arriveTime;
    }
};

hms parseClock( string c, int needM ) {
    int res = 0;
    res += stoi( c.substr( 0, 2 ) ) * 60 * 60;
    res += stoi( c.substr( 3, 2 ) ) * 60;
    res += stoi( c.substr( 6, 2 ) );
    return hms( res, needM * 60 );
}

int main() {
    int openTime = 8 * 60 * 60, closeTime = 17 * 60 * 60;
    int customerCnt, windowCnt;
    cin >> customerCnt >> windowCnt;
    vector<int> windowFinishTime( windowCnt, openTime );
    priority_queue<hms, vector<hms>, greater<>> pq;
    for( int i = 0; i < customerCnt; i++ ) {
        string curTime;
        int needM;
        cin >> curTime >> needM;
        // assert(needM > 60) fails 
        // This is an ~~assumption~~ or an **objective detection**?
        if( needM > 60 ) {
            needM = 60;
        }
        hms curClock = parseClock( curTime, needM );
        if( curClock.arriveTime < closeTime ) {
            pq.push( curClock );
        }
    }
    int filteredCnt = pq.size();
    int totalWaitedSeconds = 0;
    while( !pq.empty() ) {
        hms arriveCustomer = pq.top();
        pq.pop();
        int minFinishTime = INT_MAX;
        int windowId = -1;
        for( int i = 0; i < windowCnt; i++ ) {
            if( windowFinishTime[i] < minFinishTime ) {
                minFinishTime = windowFinishTime[i];
                windowId = i;
            }
        }
        // You gotta be crazy ? 
        // Why should this case be "served"?
        // if( minFinishTime <= closeTime ) 
        // assert(minFinishTime <= closeTime) fails 
        if( minFinishTime < arriveCustomer.arriveTime ) {
            windowFinishTime[windowId] = arriveCustomer.arriveTime + arriveCustomer.needed;
        } else {
            totalWaitedSeconds += minFinishTime - arriveCustomer.arriveTime;
            windowFinishTime[windowId] = minFinishTime + arriveCustomer.needed;

        }
    }
    cout << fixed << setprecision( 1 ) << totalWaitedSeconds / 60.0 / filteredCnt << endl;
    return 0;
}