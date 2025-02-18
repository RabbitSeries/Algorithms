#include <bits/stdc++.h>
using namespace std;
int main() {
    int locationCnt;
    cin >> locationCnt;
    vector<vector<pair<string, int>>> scoreLists( locationCnt );
    vector<pair<string, int>> mergeList;
    for( int i = 0; i < locationCnt; i++ ) {
        int testeeCnt;
        cin >> testeeCnt;
        scoreLists[i].resize( testeeCnt );
        for( int j = 0; j < testeeCnt; j++ ) {
            string curId;
            int curScore;
            cin >> curId >> curScore;
            scoreLists[i][j] = { curId,curScore };
            mergeList.emplace_back( curId, curScore );
        }
    }
    function<bool( pair<string, int>, pair<string, int> )> cmp = []( pair<string, int> const& p1, pair<string, int> const& p2 ) ->bool {
        return p1.second != p2.second ? p1.second > p2.second:p1.first <= p2.first;
    };
    unordered_map<string, int> mergeRank;
    stable_sort( mergeList.begin(), mergeList.end(), cmp );
    mergeRank[mergeList[0].first] = 1;
    for( int i = 1; i < mergeList.size(); i++ ) {
        mergeRank[mergeList[i].first] = ( mergeList[i].second == mergeList[i - 1].second ? mergeRank[mergeList[i - 1].first] : i + 1 );
    }
    unordered_map<string, int> localRank;
    unordered_map<string, int> locationBelonging;
    for( int location = 0; location < locationCnt; location++ ) {
        vector<pair<string, int>> scoreList = scoreLists[location];
        stable_sort( scoreList.begin(), scoreList.end(), cmp );
        localRank[scoreList[0].first] = 1;
        locationBelonging[scoreList[0].first] = location + 1;
        for( int i = 1; i < scoreList.size(); i++ ) {
            localRank[scoreList[i].first] = ( scoreList[i].second == scoreList[i - 1].second ? localRank[scoreList[i - 1].first] : i + 1 );
            locationBelonging[scoreList[i].first] = location + 1;
        }
    }
    cout << mergeList.size() << endl;
    for( auto [id, score] : mergeList ) {
        cout << id << " " << mergeRank[id] << " " << locationBelonging[id] << " " << localRank[id] << endl;
    }
}