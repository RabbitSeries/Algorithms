#include <bits/stdc++.h>
using namespace std;
struct bfsNode {
    size_t pos;
    int pay;
    string bitmask;
    bfsNode( size_t p, int c, string pt ) : pos{ p }, pay{ c }, bitmask{ move( pt ) } {}
    bool operator>( const bfsNode& rhs ) const {
        return pay > rhs.pay;
    }
    vector<int> mapToCoins( vector<int> const& coins ) {
        vector<int> res;
        for ( size_t i = 0; i < bitmask.size(); i++ ) {
            if ( bitmask[i] == '1' )
                res.emplace_back( coins[i] );
        }
        sort( res.begin(), res.end() );
        return res;
    }
};
int main() {
    size_t coinCnt;
    int money;
    cin >> coinCnt >> money;
    vector<int> coins( coinCnt );
    for ( size_t i = 0; i < coinCnt; i++ ) {
        cin >> coins[i];
    }
    sort( coins.begin(), coins.end() );
    if ( accumulate( coins.begin(), coins.end(), 0, []( int res, int v ) { return res + v; } ) < money ) {
        cout << "No Solution";
        return 0;
    }
    priority_queue<bfsNode, vector<bfsNode>, greater<>> q;
    q.emplace( coinCnt, 0, string( coinCnt, '0' ) );
    vector<int> payment( coins.size(), 0 );
    vector<int> res;
    while ( !q.empty() ) {
        auto curPos = move( const_cast<bfsNode&>( q.top() ) );
        q.pop();
        if ( curPos.pos != coinCnt ) {
            curPos.bitmask[curPos.pos] = '1';
        }
        if ( curPos.pay > money ) {
            break;
        }
        if ( curPos.pay == money ) {
            vector<int> rhsCoins = curPos.mapToCoins( coins );
            if ( res.empty() || rhsCoins < res ) {
                res = move( rhsCoins );
                continue;
            }
        }
        for ( size_t i = 0; i < coins.size(); i++ ) {
            if ( curPos.bitmask[i] == '0' ) {
                const int nextPay = curPos.pay + coins[i];
                if ( nextPay <= money && nextPay >= payment[i] ) {
                    payment[i] = nextPay;
                    q.emplace( i, nextPay, curPos.bitmask );
                }
            }
        }
    }
    if ( res.empty() ) {
        cout << "No Solution";
        return 0;
    }
    cout << *res.begin();
    for ( auto itr = ++res.cbegin(); itr != res.cend(); itr++ ) {
        cout << " " << ( *itr );
    }
    return 0;
}