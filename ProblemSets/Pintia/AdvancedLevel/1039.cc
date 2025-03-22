#include <bits/stdc++.h>
using namespace std;
template <class T = string>
struct myHash {
    myHash() {};
    int operator()( string const &name ) const {
        return accumulate( name.begin(), name.end() - 1, 0, []( int init, char c ) { return init * 26 + c - 'A'; } ) * 10 + name.back() - '0';  // 268 ms
        // return accumulate( name.begin(), name.end() - 1, 0, []( int init, char c ) { return init << 5 + c - 'A'; } ) << 3 + name.back() - '0';  // Time exceeded
    };
};
unordered_map<string, set<int>, myHash<>> courseList;
int main() {
    ios::sync_with_stdio( false );
    cin.tie( nullptr );
    courseList.reserve( 1 << 15 );
    int queryCnt, courseCnt, curCourse, curStuCnt;
    string curStu;
    cin >> queryCnt >> courseCnt;
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