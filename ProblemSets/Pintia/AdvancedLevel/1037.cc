#include <bits/stdc++.h>
using namespace std;
int main() {
    long long couponCnt{ 0 }, productCnt{ 0 }, res{ 0 };
    cin >> couponCnt;
    deque<long long> coupon( couponCnt ), product;
    for ( int i = 0; i < couponCnt; i++ )
        cin >> coupon[i];
    cin >> productCnt;
    product.resize( productCnt );
    for ( int i = 0; i < productCnt; i++ )
        cin >> product[i];
    sort( coupon.begin(), coupon.end() );
    sort( product.begin(), product.end() );
    while ( !coupon.empty() && !product.empty() && coupon.front() < 0 && product.front() < 0 ) {
        res += product.front() * coupon.front();
        product.pop_front(), coupon.pop_front();
    }
    while ( !coupon.empty() && !product.empty() && coupon.back() > 0 && product.back() > 0 ) {
        res += product.back() * coupon.back();
        product.pop_back(), coupon.pop_back();
    }
    cout << res;
}