#include <bits/stdc++.h>
using namespace std;
int rectantCnt, productCnt, equationCnt;
set<string> rectants;
vector<string> products;
map<string, vector<set<string>>> equations;
bool allRetants( set<string> const& recList ) {
    for ( auto const& rec : recList ) {
        if ( !rectants.contains( rec ) ) {
            return false;
        }
    }
    return true;
}
struct cmp {
    bool operator()( vector<set<string>> const& lhs, vector<set<string>> const& rhs ) const {
        return false;
    }
};
vector<string> selections;
vector<int> intervals;
int printEquation( int group, int curSelection ) {
    for ( int i = 0; i < intervals[group]; i++, curSelection++ ) {
        cout << ( i == 0 ? "" : " + " ) << selections[curSelection];
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
        bool isOverlapping = false;
        for ( auto const& rectant : curSelection ) {
            if ( lhs.contains( rectant ) ) {
                isOverlapping = true;
                break;
            }
        }
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
        for ( string rectant; cin >> rectant; ) {
            if ( rectant == "->" ) {
                cin >> rectant;
                if ( allRetants( lhs ) ) {  // Filter
                    equations[rectant].emplace_back( move( lhs ) );
                }
                break;
            } else if ( rectant == "+" ) {
                continue;
            }
            lhs.emplace( move( rectant ) );
        }
    }
    vector<int> lhsLens;
    vector<string> curSelection;
    DFS( lhsLens, curSelection );
    for ( int i = 0, selectionI = 0; i < productCnt; i++ ) {
        selectionI = printEquation( i, selectionI );
    }
}
