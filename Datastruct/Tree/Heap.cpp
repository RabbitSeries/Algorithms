#include "algorithm"
#include "iostream"
#include "vector"
using namespace std;
template<typename cmp>
class Heap {
private:
    int HeapLen;
    int Tree[1000];
    cmp _cmp;
    void downFilter( int s, int d ) {
        int l = 2 * s, r = 2 * s + 1, lower;
        if( l <= d && r <= d ) {
            lower = _cmp( Tree[l], Tree[r] ) ? l : r;
        }
        else if( l <= d ) {
            lower = l;
        }
        else {
            return;
        }
        if( _cmp( Tree[lower], Tree[s] ) ) {
            swap( Tree[lower], Tree[s] );
            s = lower;
            downFilter( s, d );
        }
    }
    void upFilter( int s ) {
        for( int i = s / 2; i > 0; i /= 2 ) {
            if( _cmp( Tree[s], Tree[i] ) ) {
                swap( Tree[i], Tree[s] );
                s = i;
            }
            else {
                return;
            }
        }
    }
    void inseart( int val ) {
        Tree[++HeapLen] = val;
        upFilter( HeapLen );
    }
    int pop() {
        swap( Tree[1], Tree[HeapLen] );
        HeapLen--;
        downFilter( 1, HeapLen );
        return Tree[HeapLen + 1];
    }
    void HeapInit() {
        // Set Emlemtes
        HeapLen = 0;
        inseart( 5668 );
        vector<int> num = { 1,2,2,45,55,45,25 };
        for( int i = 0; i < num.size(); i++ ) {
            Tree[++HeapLen] = num[i];
        }
        for( int i = HeapLen / 2; i > 0; i-- ) {
            downFilter( i, HeapLen );
        }
    }
public:
    void mySort() {
        HeapInit();
        inseart( 566 );
        for( int i = HeapLen; i > 0; i-- ) {
            swap( Tree[i], Tree[1] );
            downFilter( 1, i - 1 );
            cout << Tree[i] << " ";
        }
        cout << endl;
    }
    void popAll() {
        HeapInit();
        inseart( 566 );
        // Must init i using heapLen, the pop process will change HeapLen's value. So Heaplen can only be used once.
        for( int i = HeapLen; i > 0; i-- ) {
            cout << pop() << " ";
        }
        cout << endl;
    }
};
void sortOutput() {
    Heap<less<int>>  MinimalTop;
    Heap<greater<int>>  LargeTop;
    LargeTop.mySort();
    MinimalTop.mySort();
}
void popOutput() {
    Heap<less<int>>  MinimalTop;
    Heap<greater<int>>  LargeTop;
    LargeTop.popAll();
    MinimalTop.popAll();
}
int main() {
    sortOutput();
    popOutput();
    return 0;
}