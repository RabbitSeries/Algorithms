#include "vector"
#include "stdio.h"
#include "queue"

class bstTree {
public:
    int data;
    bstTree* left = NULL;
    bstTree* right = NULL;
    bstTree* insertNode(int val) {
        if (val < this->data) {
            if (!this->left) {
                this->left = new bstTree;
                this->left->data = val;
            } else
                this->left = this->left->insertNode(val);
        } else { // val >= root->data
            if (!this->right) {
                this->right = new bstTree;
                this->right->data = val;
            } else
                this->right = this->right->insertNode(val);
        }
        return this;
    }

    bstTree* deleteNode(int val) {
        if (this->data == val) {
            if (!this->left && !this->right) {
                delete this;
            } else if (this->left) {
                bstTree* biggestCld = this->left;
                while (biggestCld->right) {
                    biggestCld = biggestCld->right;
                }
                this->data = biggestCld->data;
                this->left = this->left->deleteNode(biggestCld->data);
            } else { //(this->root->right)
                bstTree* lowestCld = this->right;
                while (lowestCld->left) {
                    lowestCld = lowestCld->left;
                }
                this->data = lowestCld->data;
                this->right = this->right->deleteNode(lowestCld->data);
            }
        } else if (this->data > val) {
            this->left = this->left->deleteNode(val);
        } else { // this.root.data <= val
            this->right = this->right->deleteNode(val);
        }
        return this;
    }

    void bfs_traverse() {
        std::queue<bstTree*> layerQueue;
        layerQueue.push(this);
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
};

int main() {
    std::vector<int> number = { 8, 9, 4, 5, 7, 2, 3, 6 };
    bstTree* createTree;
    createTree = new bstTree;
    createTree->data = 8;
    for (int i = 1; i < number.size(); i++) {
        createTree->insertNode(number[i]);
    }
    createTree->bfs_traverse();
    return 0;
}
