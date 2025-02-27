#include <bits/stdc++.h>
using namespace std;
inline bool notSingle( unordered_map<int, int> const& pairInfo, const unordered_map<int, bool>& attended, int id ) {
    return pairInfo.count( id ) && attended.at( id ) && attended.count( pairInfo.at( id ) );
}
int main() {
    int pairCnt, mbCnt;
    cin >> pairCnt;
    unordered_map<int, int> pairInfo, pairSeat, seatId;
    unordered_map<int, bool> attended, processed;
    vector<int> seatList, faceCnt;
    for ( int i = 0; i < pairCnt; i++ ) {
        pair<int, int> curPair;
        cin >> curPair.first >> curPair.second;
        pairInfo[curPair.first] = curPair.second;
        pairInfo[curPair.second] = curPair.first;
    }
    cin >> mbCnt;
    seatList.resize( mbCnt );
    faceCnt.resize( mbCnt );
    for ( int i = 0; i < mbCnt; i++ ) {
        int curId;
        cin >> curId;
        seatList[i] = curId;
        seatId[curId] = i;
        attended[curId] = true;
        if ( notSingle( pairInfo, attended, curId ) ) {
            pairSeat[curId] = seatId[pairInfo.at( curId )];
            pairSeat[pairInfo.at( curId )] = seatId[curId];
        }
    }
    for ( int i = 0; i < mbCnt; i++ ) {
        int curId = seatList[i];
        if ( notSingle( pairInfo, attended, curId ) && !processed.count( curId ) ) {
            int nextId = pairInfo.at( curId );
            int pairSeatId = pairSeat.at( curId );
            processed[curId] = processed[nextId] = true;
            if ( pairSeatId - 1 == i ) {
                if ( i > 0 && !notSingle( pairInfo, attended, seatList[i - 1] ) ) faceCnt[i - 1]++;
                if ( pairSeatId < mbCnt - 1 && !notSingle( pairInfo, attended, seatList[pairSeatId + 1] ) ) faceCnt[pairSeatId + 1]++;
            } else {
                for ( int j = i + 1; j < pairSeatId; j++ ) {
                    if ( !notSingle( pairInfo, attended, seatList[j] ) ) faceCnt[j]++;
                }
            }
        }
    }
    int maxFace = -1;
    vector<int> maxFaceList;
    for ( int i = 0; i < mbCnt; i++ ) {
        if ( faceCnt[i] > maxFace ) {
            maxFaceList.clear();
            maxFaceList.push_back( seatList[i] );
            maxFace = faceCnt[i];
        } else if ( faceCnt[i] == maxFace ) {
            maxFaceList.push_back( seatList[i] );
        }
    }
    sort( maxFaceList.begin(), maxFaceList.end(), less<>{} );
    for ( int i = 0; i < maxFaceList.size(); i++ ) {
        cout << maxFaceList[i] << ( i == maxFaceList.size() - 1 ? "" : " " );
    }
    return 0;
}