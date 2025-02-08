#include <bits/stdc++.h>
using namespace std;
unordered_map<int, string> d2s{
    {0,"zero"},
    {1,"one"},
    {2,"two"},
    {3,"three"},
    {4,"four"},
    {5,"five"},
    {6,"six"},
    {7,"seven"},
    {8,"eight"},
    {9,"nine"}
};

int main() {
    string numList;
    cin >> numList;
    int sum = accumulate( numList.begin(), numList.end(), 0, []( int init, char c ) {
        return   init + c - '0';
    } );
    bool first = true;
    for( char c : to_string( sum ) ) {
        cout << ( !first ? ( " " + d2s[c - '0'] ) : d2s[c - '0'] );
        first = false;
    }
}