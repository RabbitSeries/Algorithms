#include "vector"
#include "stdio.h"
#include "queue"

class bstTree {
public:
    int data;
    bstTree* root = NULL;
    bstTree* left = NULL;
    bstTree* right = NULL;
    bstTree* insertNode(int val) {
        if (val < this->data) {
            if (!this->left) {
                this->left = new bstTree;
                this->left->data = val;
            }
            else {
                this->left = this->left->insertNode(val);
            }
        }
        else // val >= this->data
        {
            if (!this->right) {
                this->right = new bstTree;
                this->right->data = val;
            }
            else
                this->right = this->right->insertNode(val);
        }
        return this;
    }

    bstTree* deleteNode(int val) {
        if (this->root->data == val) {
            if (!this->root->left && !this->root->right) {
                delete this->root;
                this->root = NULL;
            }
            else if (this->root->left) {
                bstTree* biggestCld = this->root->left;
                while (biggestCld->right) {
                    biggestCld = biggestCld->right;
                }
                this->root->data = biggestCld->root->data;
                this->left = this->left->deleteNode(biggestCld->root->data);
            }
            else //(this->root->right)
            {
                bstTree* lowestCld = this->root->right;
                while (lowestCld->left) {
                    lowestCld = lowestCld->left;
                }
                this->root->data = lowestCld->root->data;
                this->right = this->right->deleteNode(lowestCld->root->data);
            }
        }
        else if (this->root->data > val) {
            this->root->left = this->root->left->deleteNode(val);
        }
        else // this.root.data <= val
        {
            this->root->right = this->root->right->deleteNode(val);
        }
        return this->root;
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
    bstTree createTree;
    createTree.root = new bstTree;
    createTree.root->data = 8;
    for (int i = 1; i < number.size(); i++) {
        createTree.root->insertNode(number[i]);
    }
    createTree.root->bfs_traverse();
    return 0;
}