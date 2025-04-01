#include <bits/extc++.h>
#include <bits/stdc++.h>
using namespace __gnu_pbds;
using namespace std;
int main() {
    int opCnt;
    cin >> opCnt;
    stack<pair<int, int>> simStack;
    tree<pair<int, int>, null_type, less<>, rb_tree_tag, tree_order_statistics_node_update> rb_tree;
    stringstream buf;
    for ( auto [i, type] = pair<int, string>{ 0, string( "" ) }; i < opCnt; i++ ) {
        cin >> type;
        if ( type == "Pop" ) {
            if ( simStack.empty() ) {
                buf << "Invalid";
            } else {
                buf << simStack.top().first;
                rb_tree.erase( simStack.top() );
                simStack.pop();
            }
            buf << endl;
        } else if ( type == "PeekMedian" ) {
            if ( simStack.empty() ) {
                buf << "Invalid";
            } else {
                buf << rb_tree.find_by_order( ( simStack.size() % 2 == 0 ? ( simStack.size() / 2 - 1 ) : ( simStack.size() + 1 ) / 2 - 1 ) )->first;
            }
            buf << endl;
        } else {  //( type == "Push" )
            int val;
            cin >> val;
            rb_tree.insert( make_pair( val, i ) );
            simStack.emplace( val, i );
        }
    }
    cout << buf.str();
}