/**
 * @file Chat_room.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-09-28
 * 
 * @copyright Copyright (c) 2023
 * 
 */

/*

PROBLEMSSUBMITSTATUSSTANDINGSCUSTOM TEST
A. Chat room
time limit per test1 second
memory limit per test256 megabytes
inputstandard input
outputstandard output
Vasya has recently learned to type and log on to the Internet. He immediately entered a chat room and decided to say hello to everybody. Vasya typed the word s. It is considered that Vasya managed to say hello if several letters can be deleted from the typed word so that it resulted in the word "hello". For example, if Vasya types the word "ahhellllloou", it will be considered that he said hello, and if he types "hlelo", it will be considered that Vasya got misunderstood and he didn't manage to say hello. Determine whether Vasya managed to say hello by the given word s.

Input
The first and only line contains the word s, which Vasya typed. This word consisits of small Latin letters, its length is no less that 1 and no more than 100 letters.

Output
If Vasya managed to say hello, print "YES", otherwise print "NO".

Examples
inputCopy
ahhellllloou
outputCopy
YES
inputCopy
hlelo
outputCopy
NO


*/

#include <bits/stdc++.h>
using namespace std;
char _hash[6] = {'h','e','l','l','o'};
int main(){
    string in_str;
    getline(cin,in_str);
    int j = 0;
    for(int i = 0 ; i < in_str.size();i++){
        if(in_str[i] == _hash[j]){
            j++;
        }
    }
    if(j == 5){
        cout << "YES";
    }
    else{
        cout << "NO";
    }
    return 0;
    
}
