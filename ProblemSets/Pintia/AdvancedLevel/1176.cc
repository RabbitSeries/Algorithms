#include <bits/stdc++.h>
using namespace std;
int rectantCnt, productCnt, equationCnt;
set<string> rectants;
vector<string> products, selections;
map<string, vector<set<string>>> equations;
vector<int> intervals;
int printEquation( int group, int curSelection ) {
    for ( int i = 0; i < intervals[group]; i++, curSelection++ ) {
        cout << ( i ? " + " : "" ) << selections[curSelection];
    }
    cout << " -> " << products[group] << endl;
    return curSelection;
}
void DFS( vector<int>& lhsLens, vector<string>& curSelection, int pId = 0 ) {
    if ( pId == productCnt ) {
        if ( selections.empty() || curSelection < selections ) {
            selections = curSelection;
            intervals = lhsLens;
        }
        return;
    }
    for ( auto const& lhs : equations.at( products[pId] ) ) {
        bool isOverlapping = any_of( curSelection.begin(), curSelection.end(), [&]( const string& rectant ) {
            return lhs.contains( rectant );
        } );
        if ( !isOverlapping ) {
            for ( auto const& rectant : lhs ) {
                curSelection.emplace_back( rectant );
            }
            lhsLens.emplace_back( lhs.size() );
            DFS( lhsLens, curSelection, pId + 1 );
            lhsLens.pop_back();
            for ( auto const& _ : lhs ) {
                curSelection.pop_back();
            }
        }
    }
}
int main() {
    cin >> rectantCnt;
    for ( int i = 0; i < rectantCnt; i++ ) {
        string rectant;
        cin >> rectant;
        rectants.emplace( move( rectant ) );
    }
    cin >> productCnt;
    products.resize( productCnt );
    for ( int i = 0; i < productCnt; i++ ) {
        cin >> products[i];
        if ( rectants.contains( products[i] ) ) {
            equations[products[i]].emplace_back( set( { products[i] } ) );
        }
    }
    cin >> equationCnt;
    for ( int i = 0; i < equationCnt; i++ ) {
        set<string> lhs;
        for ( string rectant; ( cin >> rectant ) && rectant != "->"; ) {
            if ( rectant != "+" ) {
                lhs.emplace( move( rectant ) );
            }
        }
        if ( string product; cin >> product && all_of( lhs.begin(), lhs.end(), [&]( const string& rec ) { return rectants.contains( rec ); } ) ) {  // Filter
            equations[product].emplace_back( move( lhs ) );
        }
    }
    vector<int> lhsLens;
    vector<string> curSelection;
    DFS( lhsLens, curSelection );
    for ( int i = 0, selectionI = 0; i < productCnt; i++ ) {
        selectionI = printEquation( i, selectionI );
    }
}
