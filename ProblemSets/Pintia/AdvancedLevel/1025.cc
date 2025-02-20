#include <bits/stdc++.h>
using namespace std;
// id score locale
typedef pair<pair<string, int>, int> stuRankInfo;
int main() {
    int locationCnt;
    cin >> locationCnt;
    vector<vector<stuRankInfo>> scoreLists( locationCnt );
    vector<stuRankInfo> mergeList;
    for( int i = 0; i < locationCnt; i++ ) {
        int testeeCnt;
        cin >> testeeCnt;
        scoreLists[i].resize( testeeCnt );
        for( int j = 0; j < testeeCnt; j++ ) {
            string curId;
            int curScore;
            cin >> curId >> curScore;
            scoreLists[i][j] = { { curId,curScore },i + 1 };
            mergeList.push_back( { {curId, curScore}, i + 1 } );
        }
    }
    auto cmp = []( stuRankInfo const& p1, stuRankInfo const& p2 ) ->bool {
        return p1.first.second != p2.first.second ? p1.first.second > p2.first.second:p1.first.first <= p2.first.first;
    };
    unordered_map<string, int> mergeRank;
    stable_sort( mergeList.begin(), mergeList.end(), cmp );
    mergeRank[mergeList[0].first.first] = 1;
    for( int i = 1; i < mergeList.size(); i++ )
        mergeRank[mergeList[i].first.first] = ( mergeList[i].first.second == mergeList[i - 1].first.second ? mergeRank[mergeList[i - 1].first.first] : i + 1 );
    unordered_map<string, int> localRank;
    for( int location = 0; location < locationCnt; location++ ) {
        vector<stuRankInfo> scoreList = scoreLists[location];
        stable_sort( scoreList.begin(), scoreList.end(), cmp );
        localRank[scoreList[0].first.first] = 1;
        for( int i = 1; i < scoreList.size(); i++ ) {
            localRank[scoreList[i].first.first] = ( scoreList[i].first.second == scoreList[i - 1].first.second ? localRank[scoreList[i - 1].first.first] : i + 1 );
        }
    }
    cout << mergeList.size() << endl;
    for( auto [rankInfo, locale] : mergeList )
        cout << rankInfo.first << " " << mergeRank[rankInfo.first] << " " << locale << " " << localRank[rankInfo.first] << endl;
}