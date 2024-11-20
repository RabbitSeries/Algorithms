// Time complexity of creating a heap is O(V)
#include "algorithm"
#include "vector"
#include "iostream"
using namespace std;
int HeapLen = 0;
int Heap[100 + 1];

void downAdjust( int id, int scale ) {
    int l = id * 2;
    if( l <= scale ) {
        int max;
        int r = id * 2 + 1;
        if( r <= scale ) {
            max = Heap[l] > Heap[r] ? l : r;
        }
        else {
            max = l;
        }
        if( Heap[max] > Heap[id] ) {
            // Swap
            swap( Heap[max], Heap[id] );
            downAdjust( max, scale );
        }
    }
}

void upAdjust( int id ) {
    for( int i = id / 2; i > 0; i /= 2 ) {
        if( Heap[i] < Heap[id] ) {
            swap( Heap[i], Heap[id] );
            id = i;
        }
        else {
            break;
        }
    }

}

void inseart( int v ) {
    Heap[++HeapLen] = v;
    upAdjust( HeapLen );
}

int pop() {
    int tmp = Heap[1];
    Heap[1] = Heap[HeapLen--];
    downAdjust( 1, HeapLen );
    return tmp;
}

void createHeap() {
    for( int i = HeapLen / 2; i > 0; i-- ) {
        downAdjust( i, HeapLen );
    }
}

// Remember to restore heap after performming sort.
void sort() {
    // get top
    for( int i = HeapLen; i > 0; i-- ) {
        swap( Heap[i], Heap[1] );
        downAdjust( 1, i - 1 );
    }
}

void Init_Test() {
    HeapLen = 0;
    vector<int> num = { 1,2,2,45,55,45,25 };
    for( int i = 0; i < num.size(); i++ ) {
        Heap[++HeapLen] = num[i];
    }
    createHeap();
    sort();
    for( int i = HeapLen; i > 0; i-- ) {
        cout << Heap[i] << " ";
    }
    cout << endl;
    createHeap();
}

int main() {
    Init_Test();
    Init_Test();
    return 0;
}