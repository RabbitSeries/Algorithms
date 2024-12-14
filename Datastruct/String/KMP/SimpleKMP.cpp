#include <string>
using namespace std;
#define len 100
string text, pattern;
int next[len];
int nextval[len];
int nextCnt[len + 1];
int nextCntVal[len + 1];
void get_next( string pattern, int next[] ) {
    int i = 0, j = -1;
    while( i + 1 < pattern.length() ) {
        if( j == -1 || pattern[i] == pattern[j] ) {
            i++, j++;
            next[i] = j;
        }
        else {
            j = next[j];
        }
    }
}

void get_nextVal( string pattern, int nextval[] ) {
    int i = 0, j = -1;
    while( i + 1 < pattern.length() ) {
        if( j == -1 || pattern[i] == pattern[j] ) {
            i++, j++;
            if( pattern[i] == pattern[j] ) {
                nextval[i] = nextval[j];
            }
            else {
                nextval[i] = j;
            }
        }
        else {
            j = nextval[j];
        }
    }
}
void get_nextCnt( string pattern, int nextCnt[] ) {
    int i = 0, j = -1;
    while( i < pattern.length() ) {
        if( j == -1 || pattern[i] == pattern[j] ) {
            i++, j++;
            nextCnt[i] = j;
        }
        else {
            j = nextCnt[j];
        }
    }
}


void get_nextCntVal( string pattern, int nextCntVal[] ) {
    int i = 0, j = -1;
    while( i < pattern.length() ) {
        if( j == -1 || pattern[i] == pattern[j] ) {
            i++, j++;
            if( i < pattern.length() && pattern[i] == pattern[j] ) {
                nextCntVal[i] = nextCntVal[j];
            }
            else
                nextCntVal[i] = j;
        }
        else {
            j = nextCntVal[j];
        }
    }
}
/**
 * @brief
 * @param text
 * @param pattern
 * @param next
 * @return The first matching pos of target pattern string in text string.
 */
int find_text( string text, string pattern, int next[] ) {
    int i = 0, j = 0;
    while( i < text.length() && j < pattern.length() ) {
        if( j == -1 || text[i] == pattern[j] ) i++, j++;
        else {
            j = next[j];
        }
    }
    if( j == pattern.length() ) {
        return i - pattern.length();
    }
    else {
        return -1;
    }
}

int statistic_text( string text, string pattern, int next[] ) {
    int cnt = 0;
    int i = 0, j = 0;
    while( i < text.length() && j < pattern.length() ) {
        if( j == -1 || text[i] == pattern[j] ) i++, j++;
        else {
            j = next[j];
        }
    }
    if( j == pattern.length() ) {
        cnt++;
        return i - pattern.length();
    }
    else {
        return -1;
    }
}