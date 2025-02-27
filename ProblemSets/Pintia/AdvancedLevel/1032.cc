#include <bits/stdc++.h>
using namespace std;
int main() {
    using node = struct {
        string word, next;
        bool visited = false;
    };
    unordered_map<string, node> List;
    string s1, s2, crossId = "";
    cin >> s1 >> s2;
    int nodeCnt;
    cin >> nodeCnt;
    for ( int i = 0; i < nodeCnt; i++ ) {
        string id, word, nextId;
        cin >> id >> word >> nextId;
        List[id] = { word, nextId, false };
    }
    for ( ; s1 != "-1"; s1 = List[s1].next ) List[s1].visited = true;
    while ( s2 != "-1" && !List[s2].visited ) s2 = List[s2].next;
    cout << s2;
}
// Search until null or visited before
// consider this :
// word1: 111 -> 112 -> -1
// word2: 112 -> -1
