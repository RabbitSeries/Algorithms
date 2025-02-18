#include <bits/stdc++.h>
using namespace std;
struct customer {
    int arriveTime = 0, serviceTime = 0;
    bool isVip = 0;
    friend istream& operator>>( istream& in, customer& c ) {
        string buf;
        getline( in, buf );
        c.arriveTime += stoi( buf.substr( 0, 3 ) ) * 60 * 60;
        c.arriveTime += stoi( buf.substr( 3, 6 ) ) * 60;
        c.arriveTime += stoi( buf.substr( 6, 9 ) );
        stringstream( buf.substr( 9 ) ) >> c.serviceTime >> c.isVip;
        c.serviceTime = min( 120, c.serviceTime );
        return in;
    };
};

void initData( int& customerCnt, vector<customer>& customerList, vector<customer>& vipCustomerList, int& tableCnt, int& vipTableCnt, set<int>& vipTableList ) {
    cin >> customerCnt;
    getchar();
    for( int i = 0; i < customerCnt; i++ ) {
        customer curCustomer;
        cin >> curCustomer;
        if( curCustomer.isVip ) {
            vipCustomerList.push_back( curCustomer );
        } else {
            customerList.push_back( curCustomer );
        }
    }
    sort( customerList.begin(), customerList.end(), []( const  customer& c1, const customer& c2 ) {
        return c1.arriveTime < c2.arriveTime;
    } );
    sort( vipCustomerList.begin(), vipCustomerList.end(), []( const  customer& c1, const customer& c2 ) {
        return c1.arriveTime < c2.arriveTime;
    } );

    string buf;
    getline( cin, buf );
    stringstream( buf ) >> tableCnt >> vipTableCnt;

    for( int i = 0; i < vipTableCnt; i++ ) {
        int curTable;
        cin >> curTable;
        vipTableList.insert( curTable );
    }
}

pair<int, int> findMinTime( vector<queue<int>>& finishTimeQueueList ) {

}

int main() {
    int customerCnt, tableCnt, vipTableCnt;
    vector<customer> customerList, vipCustomerList;
    set<int> vipTableList;
    initData( customerCnt, customerList, vipCustomerList, tableCnt, vipTableCnt, vipTableList );

    int closeTime = 21 * 60 * 60;
    int curTime = 8 * 60 * 60;
    vector<pair<int, queue<int>>> finishTimeQueueList( tableCnt, { curTime , {} } );
    for( int i = 0; i < customerCnt; i++ ) {
        customer curCustomer;
        if( curTime < vipCustomerList.front().arriveTime ) {
            // no vip in waiting queue
            curCustomer = customerList.front();
            customerList.erase( customerList.begin() );
        } else {
            // have vip in waiting queue
            curCustomer = vipCustomerList.front();
            vipCustomerList.erase( vipCustomerList.begin() );
        }

    }
    return 0;
}