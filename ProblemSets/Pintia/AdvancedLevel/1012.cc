#include <bits/stdc++.h>
using namespace std;
vector<char> lesson{ 'A', 'C', 'M', 'E' };
using gradeInfo = pair<int, char>;
unordered_map<int, vector<int>> allGrades;
int stuCnt, queryCnt;
gradeInfo findBest( int StuId ) {
    vector<gradeInfo> rankList;
    for ( int i = 0; i < 4; i++ ) {
        vector<int> grades;
        for ( auto const& [_, stuInfo] : allGrades ) {
            grades.emplace_back( stuInfo[i] );
        }
        int cmpGrade = allGrades.at( StuId )[i];
        int curRank = count_if( grades.begin(), grades.end(), bind( greater_equal<>{}, cmpGrade, placeholders::_1 ) );
        rankList.emplace_back( stuCnt - curRank + 1, lesson[i] );
    }
    stable_sort( rankList.begin(), rankList.end(), []( const gradeInfo& lhs, gradeInfo const& rhs ) {  // preserve relative positions for equivalent gradeInfo
        return lhs.first < rhs.first;
    } );
    return move( rankList.front() );
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