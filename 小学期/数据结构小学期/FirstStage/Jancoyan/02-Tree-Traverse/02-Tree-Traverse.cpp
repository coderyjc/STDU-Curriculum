//
// Created by Administrator on 2021/6/29.
//

#include "TreeNode.h"



//递归建立左右子树
void buildLeftSubTree(TreeNode, string);
void buildRightSubTree(TreeNode, string);


int main(){

    cout << "Enter Tree Sequence : ";

    string str;
    cin >> str; // save bi-tree sequence
    if(0 == str.length()) {
        cout << "WARNING!" << endl;
        return 0;
    }

    // build root node
    TreeNode root = TreeNode(str[0], nullptr, nullptr);
    // if the length of the string >= 2, it has child
    if(str.length() >= 2) {
        buildLeftSubTree(root, str.substr(1, str.length()));
    }

    return 0;
}

// A(B(#,D),C(E(#,F),#))

void buildLeftSubTree(TreeNode node, string str){
//    (B(#,D),C(E(#,F),#))


}

void buildRightSubTree(TreeNode node, string str){

}
