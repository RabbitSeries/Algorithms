#include <bits/stdc++.h>
using namespace std;
int main() {
    map<string, int> words;
    string buf, token;
    getline( cin, buf );
    for ( char c : buf ) {
        if ( isalpha( c ) || isalnum( c ) ) {
            token.push_back( tolower( c ) );
        } else {
            if ( !token.empty() ) {
                words[token]++;
            }
            token.clear();
        }
    }
    if ( !token.empty() ) {  // 1 -> 1 1
        words[token]++;
    }
    auto mostFrequentToken = words.end();
    int maxn = 0;
    for ( auto itr = words.begin(); itr != words.end(); itr++ ) {
        if ( itr->second > maxn ) {
            maxn = itr->second;
            mostFrequentToken = itr;
        } else if ( itr->second == maxn ) {
            if ( itr->first < mostFrequentToken->first ) {
                mostFrequentToken = itr;
            }
        }
    }
    cout << mostFrequentToken->first << " " << mostFrequentToken->second;
    return 0;
}