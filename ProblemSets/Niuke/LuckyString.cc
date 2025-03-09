#include <bits/stdc++.h>
using namespace std;

void luckySubstring() {
    string input;
    cin >> input;
    unordered_set<int> fibo;
    int a = 1, b = 1;
    while ( b <= 100 ) {
        fibo.insert( b );
        int t = a + b;
        a = b;
        b = t;
    }
    set<string> res;
    for ( int i = 0; i < input.size(); i++ ) {
        unordered_set<char> distinctLetters;
        for ( int j = i; j < input.size(); j++ ) {
            distinctLetters.insert( input[j] );
            if ( fibo.count( distinctLetters.size() ) )
                res.insert( input.substr( i, j - i + 1 ) );
        }
    }
    for ( string s : res ) {
        cout << s << endl;
    }
}

void reinforceVersion() {
    string input;
    cin >> input;
    unordered_set<int> fibo;
    int a = 1, b = 1;
    while ( b <= 100 ) {
        fibo.insert( b );
        int t = a + b;
        a = b;
        b = t;
    }
    set<string> res;
    auto nowT = chrono::high_resolution_clock::now();
    for ( int i = 0; i < input.size(); i++ ) {
        unordered_map<char, int> distinctLetters;
        for ( int j = i; j < input.size(); j++ ) {
            distinctLetters[input[j]]++;

            if ( all_of( distinctLetters.begin(), distinctLetters.end(), [&]( pair<const char, int> const& e ) -> bool { return fibo.count( e.second ); } ) )
                // if ( all_of( distinctLetters.begin(), distinctLetters.end(), [&]( pair<char, int> const& e ) -> bool { return fibo.count( e.second ); } ) )
                res.insert( input.substr( i, j - i + 1 ) );
        }
    }
    auto endT = chrono::high_resolution_clock::now();
    cout << chrono::duration_cast<chrono::microseconds>( endT - nowT ).count() << endl;
    // for ( string s : res ) {
    //     cout << s << endl;
    // }
}
template <typename K, typename V>
class MyClass {
    // Some implementation
};
MyClass<int, int> a;
// MyClass<const int, int> const& ref = a; // error
int main() {
    // luckySubstring();
    reinforceVersion();
}
