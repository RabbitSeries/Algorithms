#include <bits/stdc++.h>
using namespace std;
struct Solution {
public:
    int maxProfit( vector<int>& prices, int fee ) {
        bool soldPoint = false;
        int buyPrice = prices[0], soldPrice = prices[0];
        int profit = 0, lastProfit = 0;
        for( int price : prices ) {
            //For soldPrice update
            if( price > soldPrice && price - buyPrice > fee ) {
                soldPoint = true;
                soldPrice = price;
                profit = lastProfit + soldPrice - buyPrice - fee;
            } else if( price > soldPrice && price - soldPrice < fee ) {
                continue;
            } else if( soldPrice >= price && soldPrice - price <= fee ) {
                if( !soldPoint ) {
                    soldPrice = price;
                    buyPrice = price;

                }
            } else if( soldPrice - price > fee ) {
                //Start new phase
                soldPoint = false;
                lastProfit = profit;
                soldPrice = price;
                buyPrice = price;
            }
        }
        return profit;
    }
};