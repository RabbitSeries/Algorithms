// 给你一个字符串 s 、一个字符串 t 。返回 s 中涵盖 t 所有字符的最小子串。如果 s 中不存在涵盖 t 所有字符的子串，则返回空字符串 "" 。
// 注意：如果 s 中存在这样的子串，我们保证它是唯一的答案。
// 示例 1：
// 输入：s = "ADOBECODEBANC", t = "ABC"
// 输出："BANC"
// 示例 2：
// 输入：s = "a", t = "a"
// 输出："a"
// 提示：
// 1 <= s.length, t.length <= 105
// s 和 t 由英文字母组成
#include <bits/stdc++.h>

using namespace std;

void dpApproach() {
    // not contin
    string s{ "ADOBECODEBANC" }, t{ "ABC" }, res{ "" };
    size_t allCharCnt = 0;
    set<char> allCharSet;
    for ( char c : t ) {
        allCharSet.insert( c );
    }
    allCharCnt = allCharSet.size();
    vector<set<char>> dp( s.size() + 1 );
    vector<int> initPos( s.size() + 1, -1 );
    int minLenth = INT_MAX;
    for ( int i = 1; i <= s.size(); i++ ) {
        char curChar = s[i - 1];
        if ( t.find( curChar ) != string::npos ) {
            if ( !dp[i - 1].empty() ) {
                dp[i] = dp[i - 1];
                dp[i].insert( curChar );
                initPos[i] = initPos[i - 1];
            } else {
                dp[i].insert( curChar );
                initPos[i] = i;
            }

            size_t curContinuousLen = i - initPos[i] + 1;
            if ( dp[i].size() == allCharCnt && curContinuousLen < minLenth ) {
                minLenth = curContinuousLen;
                res = s.substr( initPos[i], curContinuousLen );
            }
        } else {
            dp[i] = dp[i - 1];
            initPos[i] = i;
        }
    }
    cout << res;
}

int main() {
    string s{ "ADOBECODEBANC" }, t{ "ABC" }, res{ "" };
    set<char> allCharSet;
    for ( char c : t ) {
        allCharSet.insert( c );
    }
    size_t allCharCnt = allCharSet.size();
    int minLenth = INT_MAX;
    for ( int i = 0; i < s.size(); i++ ) {
        set<char> curContaining;
        for ( int j = i; j < s.size(); j++ ) {
            if ( allCharSet.count( s[j] ) ) {
                curContaining.insert( s[j] );
            }
            if ( curContaining.size() == allCharCnt ) {
                if ( j - i + 1 < minLenth ) {
                    minLenth = j - i + 1;
                    res = s.substr( i, j - i + 1 );
                }
                break;
            }
        }
    }
    cout << res << endl;
}