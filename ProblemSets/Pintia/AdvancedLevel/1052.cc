#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio( false ), cin.tie( nullptr );
    int nodeCnt;
    using nodeInfo = pair<string, int>;
    string addrBegin;
    cin >> nodeCnt >> addrBegin;
    vector<nodeInfo> nodeList( nodeCnt ), filtered;
    vector<string> nextAddr( nodeCnt );
    unordered_map<string, int> addr2Id;
    for ( int i = 0; i < nodeCnt; i++ ) {
        cin >> nodeList[i].first >> nodeList[i].second >> nextAddr[i];
        addr2Id[nodeList[i].first] = i;
    }
    for ( string curAddr = addrBegin; curAddr != "-1"; curAddr = nextAddr[addr2Id.at( curAddr )] )
        filtered.emplace_back( curAddr, nodeList[addr2Id.at( curAddr )].second );
    sort( filtered.begin(), filtered.end(), []( nodeInfo const& p1, nodeInfo const& p2 ) { return p1.second < p2.second; } );
    stringstream buf;
    nodeCnt = filtered.size();
    buf << nodeCnt << " " << ( nodeCnt > 0 ? filtered[0].first : "-1" ) << endl;
    for ( int i = 0; i < nodeCnt; i++ )
        buf << filtered[i].first << " " << filtered[i].second << " " << ( ( i + 1 < nodeCnt ) ? filtered[i + 1].first : "-1" ) << endl;
    cout << buf.str();
}