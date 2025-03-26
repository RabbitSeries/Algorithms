#include <bits/stdc++.h>
// Definition for a Node.
#ifdef NATIVE_IDE
class Node {
   public:
    int val;
    Node* next;
    Node* random;

    Node( int _val ) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};
#endif
using namespace std;
class Solution {
   public:
    Node* copyRandomList( Node* head ) {
        vector<int> valList;
        unordered_map<Node*, int> Addr2Id;
        vector<Node*> oldAddrList;
        Node* p = head;
        while ( p ) {
            Addr2Id[p] = valList.size();
            oldAddrList.push_back( p );
            valList.push_back( p->val );
            p = p->next;
        }
        Node* resNode = NULL;
        if ( head )
            resNode = new Node( head->val );
        p = resNode;
        vector<Node*> newLinkedList{ resNode };
        for ( int i = 1; i < valList.size(); i++ ) {
            p->next = new Node( valList[i] );
            newLinkedList.push_back( p->next );
            p = p->next;
        }
        for ( int i = 0; i < valList.size(); i++ ) {
            if ( oldAddrList[i]->random )
                newLinkedList[i]->random = newLinkedList[Addr2Id[oldAddrList[i]->random]];
        }
        return resNode;
    }
};