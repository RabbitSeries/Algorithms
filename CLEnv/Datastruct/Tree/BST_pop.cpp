#include <vector>
#include <iostream>
#include <queue>
#include <algorithm>

typedef struct bstTree {
    int data;
    struct bstTree* left;
    struct bstTree* right;
} bstTree;

bstTree* root = NULL;

void insertNode(int val, bstTree*& r = root) {
    if (!r) {
        r = (bstTree*)malloc(sizeof(bstTree));
        r->data = val;
        r->left = r->right = NULL;
    } else {
        if (val < r->data) {
            insertNode(val, r->left);
        } else { // val >= r->data
            insertNode(val, r->right);
        }
    }
}

void deleteNode(int val, bstTree*& r = root) {
    if (r == NULL) {
        return;
    }
    if (r->data == val) {
        if (!r->left && !r->right) {
            delete r;
            r = NULL;
        } else if (r->left) {
            bstTree* biggest = r->left;
            while (biggest->right) {
                biggest = biggest->right;
            }
            r->data = biggest->data;
            deleteNode(biggest->data, r->left);
        } else if (r->right) {
            bstTree* lowest = r->right;
            while (lowest->left) {
                lowest = lowest->left;
            }
            r->data = lowest->data;
            deleteNode(lowest->data, r->right);
        }
    } else if (r->data > val) {
        deleteNode(val, r->left);
    } else { // r.data <= val
        deleteNode(val, r->right);
    }
}

void bfs_traverse(bstTree* root) {
    std::queue<bstTree*> layerQueue;
    layerQueue.push(root);
    while (!layerQueue.empty()) {
        int size = layerQueue.size();
        for (int i = 0; i < size; i++) {
            bstTree* node = layerQueue.front();
            layerQueue.pop();
            if (node->left)
                layerQueue.push(node->left);
            if (node->right)
                layerQueue.push(node->right);
            printf("%d ", node->data);
        }
        printf("\n");
    }
}

int main() {
    std::vector<int> number = { 8, 9, 4, 5, 7, 2, 3, 6 };
    for (int i = 0; i < number.size(); i++) {
        insertNode(number[i], root);
    }
    bfs_traverse(root);
    deleteNode(8, root);
    root->left = NULL;
    deleteNode(8, root->left);
    printf("\n");
    bfs_traverse(root);

    return 0;
}
