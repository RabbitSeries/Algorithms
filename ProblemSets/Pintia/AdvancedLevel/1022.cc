#include <bits/stdc++.h>
using namespace std;
int main() {
    int bookCnt;
    cin >> bookCnt;
    getchar();
    unordered_map<string, set<string, less<>>> titleToId;
    unordered_map<string, set<string, less<>>> authorToId;
    unordered_map<string, set<string, less<>>> keywordToId;
    unordered_map<string, set<string, less<>>> publisherToId;
    unordered_map<string, set<string, less<>>> yearToId;
    for( int i = 0; i < bookCnt; i++ ) {
        string buf;
        getline( cin, buf );
        string id = buf;
        getline( cin, buf );
        titleToId[buf].insert( id );
        getline( cin, buf );
        authorToId[buf].insert( id );
        getline( cin, buf );
        stringstream ss( buf );
        while( ss >> buf ) {
            keywordToId[buf].insert( id );
        }
        getline( cin, buf );
        publisherToId[buf].insert( id );
        getline( cin, buf );
        yearToId[buf].insert( id );
    }
    int queryCnt;
    cin >> queryCnt;
    getchar();
    for( int i = 0; i < queryCnt; i++ ) {
        string buf;
        getline( cin, buf );
        regex re( "(\\d+):\\s+(.+)" );
        sregex_iterator it( buf.begin(), buf.end(), re ), end_it;
        int queryType = -1;
        string queryInfo;
        queryType = stoi( ( *it )[1] );
        queryInfo = ( *it )[2];
        set<string, less<>> res;
        assert( !queryInfo.empty() );
        assert( queryType >= 0 && queryType <= 5 );
        switch( queryType ) {
        case 1:
            res = titleToId[queryInfo];
            break;
        case 2:
            res = authorToId[queryInfo];
            break;
        case 3:
            res = keywordToId[queryInfo];
            break;
        case 4:
            res = publisherToId[queryInfo];
            break;
        case 5:
            res = yearToId[queryInfo];
            break;
        default:
            break;
        }
        cout << buf << endl;
        if( res.empty() ) {
            cout << "Not Found" << endl;
        } else {
            for( auto key : res ) {
                cout << key << endl;
            }
        }
    }
    return 0;
} 