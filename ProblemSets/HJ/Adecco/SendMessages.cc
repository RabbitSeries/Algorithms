#include <bits/stdc++.h>
using namespace std;

// subscribe, unsub, id
vector<tuple<int, int, int>> pq;
vector<pair<int, int>> message;
vector<vector<int>> receivedMessages;

void readInput() {
    string buf;
    getline( cin, buf );
    stringstream ss( buf );
    int curTime, curMessage;
    while ( ss >> curTime >> curMessage ) {
        message.emplace_back( curTime, curMessage );
    }
    sort( message.begin(), message.end(), less<>{} );
    getline( cin, buf );
    ss = stringstream( buf );
    int subscribeTime, unsubTime, curConsumerId = 0;
    while ( ss >> subscribeTime >> unsubTime ) {
        pq.emplace_back( subscribeTime, unsubTime, curConsumerId++ );
    }
    sort( pq.begin(), pq.end(), []( tuple<int, int, int> const& c1, tuple<int, int, int> const& c2 ) {
        // auto [foo1, foo2, c1Priority] = c1;
        // auto [foo3, foo4, c2Priority] = c2;
        return get<2>( c1 ) > get<2>( c2 );
    } );
    receivedMessages.resize( pq.size() );
}

int main() {
    readInput();
    int i = 0, checkStart = 0;
    while ( i < message.size() ) {
        auto [curTime, curMessage] = message[i];
        for ( int j = checkStart; j < pq.size(); ) {
            auto [subscribe, unsub, id] = pq[j];
            if ( curTime >= subscribe ) {
                if ( curTime < unsub ) {
                    receivedMessages[id].push_back( curMessage );
                    break;
                    // send message to pq.top() to the first priority and qualified consumer ;
                } else if ( curTime >= unsub ) {
                    j++;
                    continue;
                    // get next subscriber
                }
            } else
                j++;
        }
        i++;
    }
    for ( auto rMessage : receivedMessages ) {
        if ( rMessage.empty() ) {
            cout << -1 << endl;
        } else {
            for ( int i = 0; i < rMessage.size(); i++ ) {
                cout << rMessage[i] << ( i == rMessage.size() - 1 ? "" : " " );
            }
            cout << endl;
        }
    }
}