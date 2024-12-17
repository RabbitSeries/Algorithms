// Time complexity of creating a heap is O(V)
#include "algorithm"
#include "vector"
#include "iostream"
using namespace std;
class Heap {
private:
    vector<int> Heap;
    // Treat the vector as the index starts from 1;
    int getHeapSize() { return Heap.size() - 1; }
    void clearHeap() { Heap.clear(); Heap.push_back( -1 ); }
public:
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
        //If the heap is empty id / 2 = 0, no process is performed.
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
        Heap.push_back( v );
        upAdjust( getHeapSize() );
    }

    int pop() {
        int tmp = Heap[1];
        Heap[1] = Heap.back();
        Heap.pop_back();
        downAdjust( 1, getHeapSize() );
        return tmp;
    }

    void createHeap() {
        for( int i = getHeapSize() / 2; i > 0; i-- ) {
            downAdjust( i, getHeapSize() );
        }
    }

    // Remember to restore heap after performming sort.
    void sort() {
        // get top
        for( int i = getHeapSize(); i > 0; i-- ) {
            swap( Heap[i], Heap[1] );
            downAdjust( 1, i - 1 );
        }
    }

    void Init_Test() {
        clearHeap();
        vector<int> num = { 1,2,2,45,55,45,25 };
        for( int i = 0; i < num.size(); i++ ) {
            Heap.push_back(num[i]);
        }
        inseart(5656);
        createHeap();
        inseart(566);
        sort();
        for( int i = getHeapSize(); i > 0; i-- ) {
            cout << Heap[i] << " ";
        }
        cout << endl;
        createHeap();
    }
};

int main() {
    Heap heap;
    heap.Init_Test();
    heap.Init_Test();
    return 0;
}