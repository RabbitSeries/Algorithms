#include <bits/stdc++.h>
using namespace std;
void printTime( int minutes ) {
    int hour = minutes / 60 + 8;
    int minute = minutes % 60;
    cout << setw( 2 ) << setfill( '0' ) << right << hour << ":" << setw( 2 ) << setfill( '0' ) << right << minute << endl;
}

inline bool beforeLimit( int serveTime ) {
    if( ( serveTime / 60 + 8 ) < 17 ) {
        return true;
    } else {
        return false;
    }
}

int inqueue( vector<queue<int>>& queueList, int& capacity, int& curTime, int processTime, int index ) {
    int minLength = capacity + 1, minLenId = -1;
    if( index < queueList.size() * capacity ) {
        int finishTime = queueList[index % queueList.size()].empty() ? processTime : queueList[index % queueList.size()].back() + processTime;
        queueList[index % queueList.size()].push( finishTime );
        return finishTime;
    }

    // All queues are full, find the nearest finish time
    int minFinishTime = INT_MAX, minFinishQueueId = -1;
    for( int i = 0; i < queueList.size(); i++ ) {
        queue<int> const& q = queueList[i];
        if( q.front() < minFinishTime ) {
            minFinishTime = q.front();
            minFinishQueueId = i;
        }
    }

    int finishTime = 0;
    // Serve time is queue back finishTime
    if( beforeLimit( queueList[minFinishQueueId].back() ) ) {
        finishTime = queueList[minFinishQueueId].back() + processTime;
        // Pop
        curTime = queueList[minFinishQueueId].front();
        queueList[minFinishQueueId].pop();
        // Inqueue
        queueList[minFinishQueueId].push( finishTime );
        return finishTime;
    } else {
        // later customer can't be served
        return -1;
    }
}



int main() {
    int queueCnt, capacity, customerCnt, queryCnt;
    cin >> queueCnt >> capacity >> customerCnt >> queryCnt;

    vector<int> costList;
    for( int i = 0; i < customerCnt; i++ ) {
        int processTime;
        cin >> processTime;
        costList.push_back( processTime );
    }
    vector<int> finishTime( customerCnt, -1 );
    vector<queue<int>> endServeList( queueCnt, queue<int>() );
    int curTime = 0;
    for( int i = 0; i < customerCnt; i++ ) {
        int cost = costList[i];
        finishTime[i] = inqueue( endServeList, capacity, curTime, cost, i );
        if( finishTime[i] < 0 ) {
            break;
        }
    }
    for( int i = 0; i < queryCnt; i++ ) {
        int q;
        cin >> q;
        q--;
        if( finishTime[q] > 0 && beforeLimit( finishTime[q] - costList[q] ) ) {
            printTime( finishTime[q] );
        } else {
            cout << "Sorry" << endl;
        }
    }
}