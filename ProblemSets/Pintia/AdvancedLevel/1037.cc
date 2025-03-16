#include <bits/stdc++.h>
using namespace std;

struct value {
    bool isNagative = false;
    long long val = 0;
};

void readValue( int len, deque<value> &list ) {
    for ( int i = 0; i < len; i++ ) {
        long long val;
        cin >> val;
        list[i].val = abs( val );
        list[i].isNagative = val < 0;
    }
}

int main() {
    int couponCnt{ 0 }, productCnt{ 0 };
    cin >> couponCnt;
    deque<value> coupon( couponCnt ), product;
    readValue( couponCnt, coupon );
    cin >> productCnt;
    product.resize( productCnt );
    readValue( productCnt, product );
    auto comparator = []( const value &v1, const value &v2 ) -> bool {
        return !v1.isNagative ? ( v2.isNagative ? true : v1.val > v2.val ) : ( !v2.isNagative ? false : ( v1.val > v2.val ) );
    };
    sort( coupon.begin(), coupon.end(), comparator );
    sort( product.begin(), product.end(), comparator );
    long long res = 0;
    while ( !coupon.empty() && !product.empty() ) {
        if ( product.front().isNagative ) {
            while ( !coupon.empty() && !coupon.front().isNagative ) coupon.pop_front();
            if ( coupon.empty() ) break;
        } else {
            if ( coupon.front().isNagative ) {
                while ( !product.empty() && !product.front().isNagative ) product.pop_front();
                if ( product.empty() ) break;
            }
        }
        res += product.front().val * coupon.front().val;
        product.pop_front();
        coupon.pop_front();
    }
    cout << res;
}