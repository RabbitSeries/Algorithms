#include <bits/stdc++.h>
using namespace std;
unordered_map<int, char> lesson{
    {0,'C'},
    {1,'M'},
    {2,'E'},
    {3,'A'}
};

unordered_map<char, int> priority{
    {'A',0},
    {'C',1},
    {'M',2},
    {'E',3}
};

struct gradeInfo {
    gradeInfo( size_t r, char lName ) : rank( r ), lessonName( lName ) {};
    size_t rank = 0;
    char lessonName = '0';
    bool operator>= ( const gradeInfo& another )const {
        if( rank != another.rank ) {
            return rank > another.rank;
        } else {
            return priority[lessonName] >= priority[another.lessonName];
        }
    }
};

vector<int> getGradeCmpList( unordered_map<int, vector<int>>const& allGrades, int lessonId ) {
    static unordered_map<int, vector<int>> gradesCache;
    if( gradesCache.count( lessonId ) != 0 ) {
        return gradesCache[lessonId];
    }
    vector<int> res;
    for( auto const& stuInfo : allGrades ) {
        res.push_back( stuInfo.second[lessonId] );
    }
    gradesCache[lessonId] = res;
    return res;
}

gradeInfo findBest( int StuId, unordered_map<int, vector<int>>const& allGrades, unordered_map<int, int>const& avgGrade, vector<int>const& avgGradeList ) {
    priority_queue<gradeInfo, vector<gradeInfo>, greater_equal<>> pq;
    vector<gradeInfo> rankList;
    for( int i = 0; i < 4; i++ ) {
        vector<int> gradeCmpList;
        int cmpGrade;
        if( i != 3 ) {
            cmpGrade = allGrades.at( StuId ).at( i );
            gradeCmpList = move( getGradeCmpList( allGrades, i ) );
        } else {
            cmpGrade = avgGrade.at( StuId );
            gradeCmpList = move( avgGradeList );
        }
        size_t curRank = 0;
        for_each( gradeCmpList.begin(), gradeCmpList.end(), [ & ]( int grade ) {
            if( cmpGrade >= grade ) {
                // Rank calculation
                curRank++;
            }
        } );
        // rankList.push_back( { allGrades.size() - curRank + 1,lesson.at( i ) } );
        pq.push( { allGrades.size() - curRank + 1,lesson.at( i ) } );
    }
    // sort( rankList.begin(), rankList.end(), less<>{} );
    return pq.top();
    // return rankList[0];
}

int main() {
    unordered_map<int, vector<int>>allGrades;
    unordered_map<int, int>avgGrade;
    vector<int>avgGradeList;
    int stuCnt, queryCnt;
    cin >> stuCnt >> queryCnt;
    for( int i = 0; i < stuCnt; i++ ) {
        vector<int> gradeList( 3, 0 );
        int stuID;
        cin >> stuID;
        int avg = 0;
        for( int i = 0; i < 3; i++ ) {
            cin >> gradeList[i];
            avg += gradeList[i];
        }
        // avg /= 3;
        allGrades[stuID] = move( gradeList );
        avgGrade[stuID] = avg;
        avgGradeList.push_back( avg );
    }
    for( int i = 0; i < queryCnt; i++ ) {
        int stuID;
        cin >> stuID;
        if( allGrades.count( stuID ) == 0 ) {
            cout << "N/A" << ( i != queryCnt ? "\n" : "" );
            continue;
        }
        gradeInfo topGrade = move( findBest( stuID, allGrades, avgGrade, avgGradeList ) );
        cout << topGrade.rank << " " << topGrade.lessonName << ( i != queryCnt ? "\n" : "" );
    }
    return 0;
}