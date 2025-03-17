#include <bits/stdc++.h>
using namespace std;
int main() {
    map<string, set<int>> courseList;  // map is quicker than unordered_map?
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
        if ( courseList.count( curStu ) ) {
            cout << curStu << " "
                 << courseList.at( curStu ).size()
                 << accumulate( courseList.at( curStu ).begin(), courseList.at( curStu ).end(), string( "" ),
                                []( string curRes, int courseId ) -> string { return ( stringstream() << curRes << " " << courseId ).str(); } )
                 << endl;
        } else {
            cout << curStu << " 0" << endl;
        }
    }
}