#include <bits/stdc++.h>
using namespace std;
vector<char> lesson{ 'A', 'C', 'M', 'E' };
using gradeInfo = pair<int, char>;
unordered_map<int, vector<int>> allGrades;
int stuCnt, queryCnt;
gradeInfo findBest( int StuId ) {
    gradeInfo minRank{ INT_MAX, 0 };
    for ( int i = 0; i < 4; i++ ) {
        int cmpGrade = allGrades.at( StuId )[i];
        int curRank = count_if( allGrades.begin(), allGrades.end(), [&]( decltype( allGrades )::value_type const& stuInfo ) {
            return cmpGrade < stuInfo.second[i];  // _____(higher)->|->(greaterequal)______
        } );
        if ( curRank + 1 < minRank.first ) {      // leave equivalent grades which have lower priority
            minRank = { curRank + 1, lesson[i] };
        }
    }
    return minRank;
}
int main() {
    cin >> stuCnt >> queryCnt;
    for ( int i = 0, stuID; i < stuCnt; i++ ) {
        vector<int> gradeList( 4 );
        cin >> stuID;
        for ( int i = 1; i <= 3; i++ ) {
            cin >> gradeList[i];
        }
        gradeList[0] = accumulate( gradeList.begin() + 1, gradeList.end(), 0, plus<>{} );
        allGrades[stuID] = move( gradeList );  // A, C, M, E
    }
    for ( int i = 0, stuID; i < queryCnt; i++ ) {
        cin >> stuID;
        if ( !allGrades.contains( stuID ) ) {
            cout << "N/A" << endl;
            continue;
        }
        gradeInfo topGrade = findBest( stuID );
        cout << topGrade.first << " " << topGrade.second << endl;
    }
    return 0;
}