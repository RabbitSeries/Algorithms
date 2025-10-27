#include <bits/stdc++.h>
using namespace std;
int StateMachineSolution( int TransN, deque<int> Prices ) {
    int DayN = (int)( Prices.size() );
    Prices.push_front( 0 );  // Index from 1
    struct state {
        int day, trans, profit;
        bool isHolding;
        string key() {
            return ( ostringstream() << day << "," << trans << "," << isHolding ).str();
        }
    };
    state start{ 0, 0, 0, false };
    queue<state> q;
    q.push( start );
    unordered_map<string, int> Profits{ { start.key(), start.profit } };
    int maxProfit = 0;
    while ( !q.empty() ) {
        state s = q.front();
        q.pop();
        if ( Profits[s.key()] > s.profit ) {
            continue;
        }
        // Profits[s.key()] == s.profit from here
        maxProfit = max( maxProfit, Profits[s.key()] );
        state noAction = { s.day + 1, s.trans, s.profit, s.isHolding };
        if ( noAction.day <= DayN && ( !Profits.contains( noAction.key() ) || Profits[noAction.key()] < noAction.profit ) ) {
            Profits[noAction.key()] = noAction.profit;
            q.push( noAction );
        }
        if ( s.day < DayN ) {
            state Action = { s.day + 1, s.isHolding ? s.trans + 1 : s.trans,
                             s.profit + Prices[s.day + 1] * ( s.isHolding ? 1 : -1 ),
                             !s.isHolding };
            if ( Action.trans <= TransN && ( !Profits.contains( Action.key() ) || Profits[Action.key()] < Action.profit ) ) {
                Profits[Action.key()] = Action.profit;
                q.push( Action );
            }
        }
    }
    return maxProfit;
}
int DPArraySolution( int TransN, deque<int> Prices ) {
    int DayN = (int)( Prices.size() );
    Prices.push_front( 0 );  // Index from 1
    vector holding( DayN + 1, vector( TransN + 1, 0 ) );
    // Init Day 0, sold profit at day 0 is 0, holding is impossible, day 1~DayN will be populated using dependency
    vector sold( DayN + 1, vector( TransN + 1, 0 ) );
    ranges::fill( holding[0], INT_MIN );       // impossible holding at day 0
    for ( int day = 1; day <= DayN; day++ ) {  // Traverse through all states, in dependency sequence
        for ( int trans = 0; trans <= TransN; trans++ ) {
            holding[day][trans] = max( holding[day - 1][trans], sold[day - 1][trans] - Prices[day] );
            sold[day][trans] = max( sold[day - 1][trans], trans >= 1 ? holding[day - 1][trans - 1] + Prices[day] : INT_MIN /* trans at -1 is impossible */ );
        }
    }
    return sold[DayN][TransN];
}
int RollDP( int TransN, deque<int> Prices ) {
    int DayN = (int)( Prices.size() );
    Prices.push_front( 0 );                                                   // Index from 1
    vector holding( TransN + 1, INT_MIN );                                    // impossible holding at day 0
    vector sold( TransN + 1, 0 );                                             // day 0's sold profit is 0
    for ( int day = 1; day <= DayN; day++ ) {
        for ( int trans : views::reverse( views::iota( 0, TransN + 1 ) ) ) {  // Refresh dependency in reverse traversal
            holding[trans] = max( holding[trans], sold[trans] - Prices[day] );
            sold[trans] = max( sold[trans], trans >= 1 ? holding[trans - 1] + Prices[day] : INT_MIN /* trans at -1 is impossible */ );
        }
    }
    return sold[TransN];
}
int main() {
    // 343
    // int TransN = 2;
    // deque<int> Prices{ 40, 24, 91, 73, 115, 24, 144, 177, 41, 168, 24, 177, 67, 46, 168, 22, 48, 27, 38, 56, 46, 6, 130, 100, 9, 101, 196, 103, 75, 15, 152 };
    // 994
    int TransN = 6;
    deque<int> Prices{ 86, 119, 156, 19, 3, 127, 110, 185, 200, 39, 152, 173, 78, 145, 54, 21, 188, 67, 15, 114, 68, 106, 43, 169, 84, 156, 197, 42, 43, 10, 168, 178, 133, 165, 31, 177, 119, 111, 103, 82, 45, 35 };
    std::cout << "StateMachineSolution: " << StateMachineSolution( TransN, Prices ) << "\n";
    std::cout << "DPArraySolution: " << DPArraySolution( TransN, Prices ) << "\n";
    std::cout << "RollDP: " << RollDP( TransN, Prices ) << "\n";
}