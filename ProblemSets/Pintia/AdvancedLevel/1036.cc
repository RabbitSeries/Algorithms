#include <bits/stdc++.h>
using namespace std;
int main() {
    string maleName = "", maleCourseName = "", femaleName = "", femaleCourseName = "";
    int maleScore = INT_MAX, femaleScore = INT_MIN, stuCnt;
    cin >> stuCnt;
    for ( int i = 0; i < stuCnt; i++ ) {
        string curName, curGender, curCourse;
        int curScore;
        cin >> curName >> curGender >> curCourse >> curScore;
        if ( curGender == "M" && curScore < maleScore ) {
            maleScore = curScore;
            maleCourseName = curCourse;
            maleName = curName;
        } else if ( curGender == "F" && curScore > femaleScore ) {
            femaleScore = curScore;
            femaleCourseName = curCourse;
            femaleName = curName;
        }
    }
    if ( femaleName.empty() )
        cout << "Absent" << endl;
    else
        cout << femaleName << " " << femaleCourseName << endl;
    if ( maleName.empty() )
        cout << "Absent" << endl;
    else
        cout << maleName << " " << maleCourseName << endl;
    if ( maleScore == INT_MAX || femaleScore == INT_MIN ) {
        cout << "NA";
    } else
        cout << femaleScore - maleScore << endl;
    return 0;
}