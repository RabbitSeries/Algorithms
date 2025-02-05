#include <vector>
#include <iostream>
#include <string>
using namespace std;
/* Time 8min */
#define maxn 100
string text, model;

int nextC[maxn];
int cnt = 0;
int findModelPos(string text, int textIndex, int nextPos) {
    return text[textIndex] == model[nextPos + 1] ? nextPos + 1 : nextPos == -1 ? -1
           : findModelPos(text, textIndex, nextC[nextPos]);
}

int findModelPos_fix(string text, int textIndex, int nextPos) {
    return text[textIndex] == model[nextPos + 1] ? nextPos == -1 || text[textIndex] != model[nextC[nextPos] + 1] ? /* nextPos + 1 */ nextPos + 1 : findModelPos(text, textIndex, nextC[nextPos]) : nextPos == -1 ? -1
           : findModelPos(text, textIndex, nextC[nextPos]);
}
//FIXME asdasd

// 已经确保了不会出现前缀的下一位额和下一次前缀的下一位是连续相等的了，不需要继续自己调用自己查找相应的前缀。
int findModelPos_fix_fix(string text, int textIndex, int nextPos) {
    return text[textIndex] == model[nextPos + 1] ? nextPos == -1 || text[textIndex] != model[nextC[nextPos] + 1] ? /* nextPos + 1 */ nextPos + 1 : nextC[nextPos] : nextPos == -1 ? -1
           : findModelPos(text, textIndex, nextC[nextPos]);
}

void fillNextC() {
    nextC[0] = -1;
    for (int i = 1; i < model.length(); i++) {
        nextC[i] = findModelPos(model, i, nextC[i - 1]);
    }
}

void statisticsOfmodelText() {
    int nextPos = -1;
    for (int i = 0; i < text.length(); i++) {
        nextPos = findModelPos(text, i, nextPos);
        if (nextPos == model.length() - 1) {
            cnt++;
            nextPos = nextC[nextPos];
        }
    }
}

int main() {
    cin >> text >> model;
}
