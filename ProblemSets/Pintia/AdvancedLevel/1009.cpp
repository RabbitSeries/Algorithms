#include <bits/stdc++.h>
using namespace std;
void readPoly( vector<pair<int, float>>& poly ) {
    string line;
    getline( cin, line );
    int pCnt;
    stringstream ss( line );
    ss >> pCnt;
    for( int i = 0; i < pCnt; i++ ) {
        int exp;
        float coeff;
        ss >> exp >> coeff;
        poly.push_back( { exp,coeff } );
    }
}
int main() {
    vector<pair<int, float>> poly1, poly2;
    readPoly( poly1 );
    readPoly( poly2 );
    unordered_map<int, float> production;
    priority_queue<pair<int, float>, vector<pair<int, float>>, less<>> output;
    for( auto p1 : poly1 ) {
        int exp1 = p1.first;
        float coeff1 = p1.second;
        for( auto p2 : poly2 ) {
            int exp2 = p2.first;
            float coeff2 = p2.second;
            production[exp1 + exp2] += coeff1 * coeff2;
        }
    }
    for( auto p : production ) {
        if( p.second != 0 ) {
            output.push( p );
        }
    }
    cout << output.size();
    cout << fixed << setprecision( 1 );
    while( !output.empty() ) {
        cout << " " << output.top().first << " " << output.top().second;
        output.pop();
    }
    return 0;
}

