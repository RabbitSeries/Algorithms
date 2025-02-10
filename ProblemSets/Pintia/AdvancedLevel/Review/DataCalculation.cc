#include <bits/stdc++.h>
using namespace std;

vector<int> toll( 24, 0 );

struct date {
    int month = -1, day = -1, hour = -1, minute = -1;
    bool operator<( date const& r )const {
        if( day != r.day ) {
            return day < r.day;
        } else if( hour != r.hour ) {
            return hour < r.hour;
        } else {
            return minute < r.minute;
        }
    }
};

struct record {
    date beginDate, endDate;
    // Time gaping calculation
    pair<int, int> getCost() const {
        int cost = 0;
        int dayGap = endDate.day - beginDate.day;
        int duration = 0;
        for( int i = beginDate.hour + 1; i < 24 * dayGap + endDate.hour; i++ ) {
            duration += 60;
            cost += toll[i % 24] * 60;
        }

        if( dayGap == 0 && beginDate.hour == endDate.hour ) {
            duration += endDate.minute - beginDate.minute;
            cost += toll[beginDate.hour] * ( endDate.minute - beginDate.minute );
        } else {
            duration += 60 - beginDate.minute + endDate.minute;
            cost += toll[beginDate.hour] * ( 60 - beginDate.minute );
            cost += toll[endDate.hour] * endDate.minute;
        }
        return { cost,duration };
    }
    float printRecord() const {
        auto [cost, duration] = getCost();
        float printCost = cost / 100 + cost % 100 / 100.0;
        printf( "%02d:%02d:%02d %02d:%02d:%02d %d $%.2f\n", beginDate.day, beginDate.hour, beginDate.minute, endDate.day, endDate.hour, endDate.minute, duration, printCost );
        return printCost;
    }

};