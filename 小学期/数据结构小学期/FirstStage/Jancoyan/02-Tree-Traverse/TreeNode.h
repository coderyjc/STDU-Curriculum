//
// Created by Administrator on 2021/6/29.
//

#ifndef CLION_TREENODE_H
#define CLION_TREENODE_H

#include <iostream>

using namespace std;

class TreeNode {


public:

    TreeNode(char data, TreeNode *lChild, TreeNode *rChild);

    char data;
    TreeNode* lChild;
    TreeNode* rChild;

public:

    void preTraverse();

    void midTraverse();

    void lastTraverse();
};

void TreeNode::preTraverse() {
    cout << data << endl;
    this->lChild->preTraverse();
    this->rChild->preTraverse();
}

void TreeNode::midTraverse() {
    this->lChild->midTraverse();
    cout << data << endl;
    this->rChild->midTraverse();
}

void TreeNode::lastTraverse() {
    this->lChild->lastTraverse();
    this->rChild->lastTraverse();
    cout << data << endl;
}

TreeNode::TreeNode(char data, TreeNode *lChild, TreeNode *rChild) : data(data), lChild(lChild), rChild(rChild) {}


#endif //CLION_TREENODE_H
