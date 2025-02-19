#include <bits/stdc++.h>
using namespace std;
int main() {
    size_t customerCnt, windowCnt, filteredCnt = 0, totalWaitedSeconds = 0;
    cin >> customerCnt >> windowCnt;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    for( size_t i = 0; i < customerCnt; i++ ) {
        int hh, mm, ss, needM;
        scanf( "%d:%d:%d %d", &hh, &mm, &ss, &needM );
        if( hh * 3600 + mm * 60 + ss > 17 * 60 * 60 ) continue;
        pq.emplace( hh * 3600 + mm * 60 + ss, needM * 60 );// once arrived must be served
        filteredCnt++;
    }
    priority_queue<int, vector<int>, greater<>> q;// Since the casher always choose the nearest last finish time and windowid choice is not relevant to the res calculation, this window queue can be maintained by priorityQueue;
    while( !pq.empty() ) {
        auto [arriveTime, neededTime] = pq.top();
        pq.pop();
        int minFinishTime = q.size() < windowCnt ? 8 * 60 * 60 : q.top();   //if the window queue is not full, it's last finishtime is the opentime of the bank
        if( q.size() == windowCnt ) q.pop();                                //if the queue is full, the nearest last last finish time's service is finished and will be poped from the queue.
        q.push( max( minFinishTime, arriveTime ) + neededTime );            // The service time is the maximun of last finishtime and the arrival time of the customer.
        totalWaitedSeconds += max( minFinishTime, arriveTime ) - arriveTime;// Service time - arrvice time = waited time
    }
    cout << fixed << setprecision( 1 ) << totalWaitedSeconds / 60.0 / filteredCnt << endl;
    return 0;
}