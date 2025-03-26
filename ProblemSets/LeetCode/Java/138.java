package LeetCode.Java;
// Definition for a Node.

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;

class Node {
    int val;
    Node next;
    Node random;

    public Node(int val) {
        this.val = val;
        this.next = null;
        this.random = null;
    }
}

class Solution {

    public Node copyRandomList(Node head) {
        List<Integer> valList = new ArrayList<>();
        HashMap<Node, Integer> Addr2Id = new HashMap<>();
        List<Node> oldAddrList = new ArrayList<>();
        Node p = head;
        while (p != null) {
            Addr2Id.put(p, valList.size());
            oldAddrList.add(p);
            valList.add(p.val);
            p = p.next;
        }
        Node resNode = null;
        if (head != null)
            resNode = new Node(head.val);
        p = resNode;
        List<Node> newLinkedList = new ArrayList<>(); // List.of can't accept mull cause if can't deduce element type.
        newLinkedList.add(p);
        for (int i = 1; i < valList.size(); i++) {
            p.next = new Node(valList.get(i));
            newLinkedList.add(p.next);
            p = p.next;
        }
        for (int i = 0; i < valList.size(); i++) {
            if (oldAddrList.get(i).random != null)
                newLinkedList.get(i).random = newLinkedList.get(Addr2Id.get(oldAddrList.get(i).random));
        }
        return resNode;
    }

    public static void main(String[] args) {
        Solution s = new Solution();
        s.copyRandomList(new Node(10));
    }
}