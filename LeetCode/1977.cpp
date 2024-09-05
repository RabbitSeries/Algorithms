#include <vector>
#include <string>
#include <iostream>
using namespace std;
#define MODULO int(1e9 + 7)
class Solution {
public:
    vector<string> List;
    int counter = 0;
    int numberOfCombinations( string num ) {
        if( num == "" || num[0] == '0' ) {
            if( List.size() > 0 && num[0] != '0' ) counter++;
            return counter % MODULO;
        }
        for( int i = 0; i < num.length(); i++ ) {
            if( !List.empty() && compareLongString( num.substr( i + 1 ), List.back() ) ) {
                break;
            }
            if( List.empty() || !compareLongString( num.substr( 0, i + 1 ), List.back() ) ) {
                List.push_back( num.substr( 0, i + 1 ) );
                numberOfCombinations( num.substr( i + 1 ) );
                if( num.length() <= i + 2 || num[i + 1] == '0' || ( !List.empty() && compareLongString( num.substr( i + 1 ), List.back() ) ) ) {
                    counter++;
                    List.pop_back();
                    return counter % MODULO;

                }
                List.pop_back();
            }
        }
        return counter % MODULO;
    }
    bool compareLongString( string s1, string s2 ) {
        return s1.length() == s2.length() ? s1.compare( s2 ) < 0 : s1.length() < s2.length();
    }
};


int main() {
    Solution s;
    std::cout << ( s.numberOfCombinations( "181599706296201533688444310698720506149731032417146774186256527047743490211586938068687937416089" ) + 1 ) % MODULO;
}