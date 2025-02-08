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

int inqueue( vector<queue<int>>& queueList, int& capacity, int& curTime, int processTime ) {
    int minLength = capacity + 1, minLenId = -1;

    // Find the shortest queue size
    for( int i = 0; i < queueList.size(); i++ ) {
        queue<int> const& q = queueList[i];
        if( q.size() < minLength ) {
            minLength = q.size();
            minLenId = i;
        }
    }

    if( queueList[minLenId].empty() ) {
        // serveTime is curtime
        assert( beforeLimit( curTime ) );
        if( beforeLimit( curTime ) ) {
            queueList[minLenId].push( curTime + processTime );
            return curTime + processTime;
        } else {
            return -1;
        }
    } else if( queueList[minLenId].size() < capacity ) {
        // serveTime is queuebackFinishTime
        int backTime = queueList[minLenId].back();
        // assert( beforeLimit( backTime ) );
        // if( beforeLimit( backTime ) ) {
        // Although this person might be impossible to be served, inqueue anyways, and the first queueCnt*capacity must not stop others serve time.
        // suppose this case:
        // Window
        // 1 2 3 4
        // Queue size
        // 3 3 2 2
        // Possibility
        // p p i p
        // if stop at 3rd window, the 4th windows's service will be stoped *Passively*.
        queueList[minLenId].push( backTime + processTime );
        return backTime + processTime;
        // } else {
            // return -1;
            // cotinue;
        // }
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
    finishTime = queueList[minFinishQueueId].back() + processTime;
    // Pop
    curTime = queueList[minFinishQueueId].front();
    queueList[minFinishQueueId].pop();
    // Inqueue
    queueList[minFinishQueueId].push( finishTime );
    return finishTime;

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

        finishTime[i] = inqueue( endServeList, capacity, curTime, cost );
        if( finishTime[i] < 0 ) {
            break;
        }
    }
    for( int i = 0; i < queryCnt; i++ ) {
        int q;
        cin >> q;
        q--;
        if( beforeLimit( finishTime[q] - costList[q] ) ) {
            printTime( finishTime[q] );
        } else {
            cout << "Sorry" << endl;
        }
    }
}