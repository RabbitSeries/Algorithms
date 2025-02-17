package LeetCode;

import static java.lang.Math.*;

public class StockLinear {
    public int solve(int[] priceList, Integer fee) {
        int buyProfit = -priceList[0], sellProfit = 0;
        for (int price : priceList) {
            buyProfit = max(buyProfit, sellProfit - price);
            sellProfit = max(sellProfit, buyProfit + price - fee);
        }
        return sellProfit;
    }

    public int pureLogic(int[] prices, int fee) {
        boolean soldPoint = false;
        int buyPrice = prices[0], soldPrice = prices[0];
        int profit = 0, lastProfit = 0;
        for (int price : prices) {
            // For soldPrice update
            if (price > soldPrice && price - buyPrice > fee) {
                soldPoint = true;
                soldPrice = price;
                profit = lastProfit + soldPrice - buyPrice - fee;
            } else if (price > soldPrice && price - soldPrice < fee) {
                continue;
            } else if (soldPrice >= price && soldPrice - price <= fee) {
                // If lower price exists, in new phase, change to lower price at first priority.
                if (!soldPoint) {
                    soldPrice = price;
                    buyPrice = price;
                }
            } else if (soldPrice - price > fee) {
                // Start new phase
                soldPoint = false;
                lastProfit = profit;
                soldPrice = price;
                buyPrice = price;
            }
        }
        // System.out.println(profit);
        return profit;
    }

    public static void main(String[] args) {
        StockLinear linear = new StockLinear();
        int[] prices = new int[] { 1, 3, 7, 5, 10, 3 };
        linear.pureLogic(prices, 3);
    }
}
