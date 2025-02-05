#include "string"
#include "algorithm"
#include "iostream"
using namespace std;
#define maxn 100

int nextC[maxn]; // nextC[i]表示模式串下标从0..i范围内的最长的、可以扩充的相等的首字母连续前缀、尾字母连续后缀的前缀下标
//学到后面可以发现nextC[i]实际上是模式串失去匹配的时候前面0..i-1是已经匹配到的了,那么在0..i-1中可以有
string model;

/**
 * @brief
 *  *查找模式串下标从0..i范围内的最长的、可以扩充的相等的首字母连续前缀、尾字母连续后缀的前缀下标
 * @param i     当前待求next数组的模式串下标
 * @param next  next=nextC[i-1]，next参数是模式串model下标0..(i-1)范围内的最长可以扩充的前缀的最后一位的下标
 * @return      int 递归返回代求的nextC[i]
 */
inline int find(int i, int next) {
    if (model[i] == model[next + 1]) { // 默认对前一次级联到的前后缀扩充一位，即使第一次进入循环前缀为空，长度为0，在数学上做了一个值为-1的“ 虚拟前缀”，表示这个级联前缀为0的前一位，做了扩充之后，第一次进入循环，就对空的前缀扩充成了第一位和第二位做比较，在数学上就成了把模式串下标范围在0..1的字串做“首字母向后数前缀，尾字母向前数后缀”的操作。
        return next + 1; // 如果可以再次扩充成相等的前后缀，就把扩充后的前缀最后一位的下标返回，实际上就是扩充前的前缀尾字母下标+1
    } else {            // model[i] != model[next+1]
        // 此时表示不能扩充，那就得按照两次级联数学推导含义（对应的i得满足i>2,因为i==1的时候，第一个字母和第二字母不相等，再扩充就成了整个模式串了，这必然是相等的，但是对模式串滑动匹配没有帮助)，要在前缀（这个前缀是模式串下标的0..next范围字串）的前缀中寻找一个扩充的“前前缀”，因此要做能否继续向前缀中寻找“前前缀”
        if (next == -1) // 如果前缀的前缀是空的，不能继续split出一个“前缀的前缀”
            //!注意，只有前缀的前缀是空的时候才不能分出“前缀的前缀”
            return -1;
        else {
            return find(i, nextC[next]);//!当前缀nextC[next]=-1，是空的时候，还是可以继续和model的首位作比较的。
        }
    }
}

int main() {
    nextC[0] = -1;
    cin >> model;
    for (int i = 1; i < model.size(); i++) {
        nextC[i] = find(i, nextC[i - 1]);
    }
    for_each(nextC, nextC + model.size(), [](int num) {
        cout << num << " ";
    });
    return 0;
}
