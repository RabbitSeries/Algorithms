#include <bits/stdc++.h>
using namespace std;
int main() {
    int pCnt, qCnt;
    cin >> pCnt >> qCnt;
    using pInfo = pair<pair<string, int>, int>;
    vector<pInfo> pList( pCnt );
    for ( int i = 0; i < pCnt; i++ ) {
        cin >> pList[i].first.first >> pList[i].first.second >> pList[i].second;
    }
    sort( pList.begin(), pList.end(), []( pInfo const& p1, pInfo const& p2 ) {
        return p1.first.second < p2.first.second;
    } );
    stringstream buf;
    for ( int i = 0; i < qCnt; i++ ) {
        buf << "Case #" << ( i + 1 ) << ":" << endl;
        int curQ, lAge, rAge;
        cin >> curQ >> lAge >> rAge;
        // auto res = upper_bound( pList.begin(), pList.end(), rAge, []( int age, pInfo const& p ) {//reverse lambda
        //     return p.first.second > age;
        // } );
        auto res = lower_bound( pList.begin(), pList.end(), lAge, []( pInfo const& p, int age ) {
            return p.first.second < age;
        } );
        if ( curQ > 0 && res != pList.end() && ( *res ).first.second <= rAge ) {
            vector<pInfo> resList;
            while ( res != pList.end() && ( *res ).first.second <= rAge ) {
                resList.emplace_back( *res );
                res++;
            }
            sort( resList.begin(), resList.end(), []( pInfo const& p1, pInfo const& p2 ) {  // If all age is within range, this sublist is sorted every time. making time complexity to be n*n*logn
                if ( p1.second != p2.second )
                    return p1.second > p2.second;
                else if ( p1.first.second != p2.first.second )
                    return p1.first.second < p2.first.second;
                else
                    return p1.first.first < p2.first.first;
            } );
            for ( int j = 0; j < curQ && j < resList.size(); j++ ) {
                pInfo const& p = resList[j];
                buf << p.first.first << " " << p.first.second << " " << p.second << endl;
            }
        } else {
            buf << "None" << endl;
        }
    }
    cout << buf.str();
}