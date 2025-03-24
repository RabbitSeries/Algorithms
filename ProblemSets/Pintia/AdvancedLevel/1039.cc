#include <bits/stdc++.h>

#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
using namespace std;
struct strHash {
    int operator()( string const &name ) const {
        return accumulate( name.rbegin() + 1, name.rend(), name.back() - '0', []( int init, char c ) { return ( init * 26 ) + ( c - 'A' ); } );
    }
};
int main() {
    // gp_hash_table<string, set<int>, strHash> courseList; // underlying impl is plain hash table, cost more space so that exceeeds space limit.
    unordered_map<string, set<int>, strHash> courseList;
    int queryCnt, courseCnt, curCourse, curStuCnt;
    cin >> queryCnt >> courseCnt;
    string curStu;
    for ( int i = 0; i < courseCnt; i++ ) {
        cin >> curCourse >> curStuCnt;
        for ( int j = 0; j < curStuCnt; j++ ) {
            cin >> curStu;
            courseList[curStu].insert( curCourse );
        }
    }
    for ( int i = 0; i < queryCnt; i++ ) {
        cin >> curStu;
        cout << curStu << " " << courseList[curStu].size();
        for ( auto const &courseId : courseList[curStu] )
            cout << " " << courseId;
        cout << endl;
    }
}