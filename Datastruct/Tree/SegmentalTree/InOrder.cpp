#include "iostream"
typedef int* ThreadTree;
void InThread( ThreadTree& p, ThreadTree& pre ) {
    pre = p;
}

int main() {
    int node1 = 1, node2 = 2;
    int* Node1 = &node1, * Node2 = &node2;
    InThread( Node1, Node2 );
    return 0;
}