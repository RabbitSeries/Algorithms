#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio( false ), cin.tie( nullptr );
    int stuCnt, courseCnt;
    cin >> stuCnt >> courseCnt;
    vector<vector<string>> stuList( courseCnt + 1 );
    for ( int i = 0; i < stuCnt; i++ ) {
        string curStu;
        cin >> curStu;
        int subscribeCnt, curCourse;
        cin >> subscribeCnt;
        for ( int j = 0; j < subscribeCnt; j++ ) {
            cin >> curCourse;
            stuList[curCourse].emplace_back( curStu );
        }
    }
    stringstream buf;
    for ( int i = 1; i <= courseCnt; i++ ) {
        buf << i << " " << stuList[i].size() << endl;
        sort( stuList[i].begin(), stuList[i].end() );
        for ( auto const& stu : stuList[i] )
            buf << stu << endl;
    }
    cout << buf.str();
}
// please use printf("%s\n",string.c_str()) in altanative to cout << string or use stringstream to connect all.
// or use stringstream to act as a output buffer