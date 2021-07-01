#include<iostream>
#include<string>
#include <climits>
#include <algorithm>
#include "BiTreeAppliction.h"
using namespace std;


BiTreeApplication::BiTreeApplication() {
    this->huffTree = new HuffNode[100](); // init volume is 100
    this->nodeCount = 0;
    this->maxLength = 0;
    this->hasConstruct = 0;
}

BiTreeApplication::~BiTreeApplication() {
    if (this->huffTree) {
        delete this->huffTree;
    }
}

void BiTreeApplication::init() {
    cout << "----------------\nInitializing\n----------------" << endl;
    // enter chars and its weight;
    cout << "enter character and its rank, part with space and end with # and -1" << endl;

    char tempChar;
    int tempWeight;
    for (this->nodeCount = 1; (cin >> tempChar >> tempWeight) && tempChar != '#'; nodeCount++) {
        this->huffTree[nodeCount].data = tempChar;
        this->huffTree[nodeCount].weight = tempWeight;
    }
    this->nodeCount--; //减去在循环的时候多出来的那个
    this->maxLength = this->nodeCount * 2 - 1;

    cout << "----------------\nTips\n\nSuccess!\n----------------" << endl;
    cin.clear();
    this->constructHuffTree();
}

void BiTreeApplication::constructHuffTree() {

    cout << "Building..." << endl;
    for (int i = ++this->nodeCount; i <= this->maxLength; i++) {
        // 将s1和s2赋值为最大int值方便查找
        int s1 = 0, s2 = 0;
        this->selectNode(s1, i - 1, s2);
        this->huffTree[s1].parent = i;
        this->huffTree[s2].parent = i;
        this->huffTree[i].lch = s1;
        this->huffTree[i].rch = s2;
        this->huffTree[i].weight = this->huffTree[s1].weight + this->huffTree[s2].weight;
    }
    cout << "--------------\nTips：\n\nBuild Success\n--------------" << endl;
    system("pause");
    
    this->hasConstruct = 1;
}

void BiTreeApplication::encoding() {
    if (!this->hasConstruct) {
        cout << "---------------------------\nTips：\n\nBi-Tree Hasre not been built, Please execute opt-1\n---------------------------" << endl;
        system("pause");
        
        return;
    }
    cout << "enter character(without space): ";
    string str;
    cin.clear();
    cin >> str;
    cout << "\nHuffman code is :" << endl;
    for (int i = 0; i < str.length(); i++) {
        // traverse the tree
        string tempCode = "";
        int flag = 0; // find the point or not
        for (int j = 1; j < this->nodeCount; j++) {
            if (this->huffTree[j].data == str[i]) {
                // show
                flag = 1;
                int tempNumber = j;
                int parent = this->huffTree[j].parent;
                while (parent != 0) {
                    // left child is the node
                    if (this->huffTree[parent].lch == tempNumber) tempCode += "0";
                    if (this->huffTree[parent].rch == tempNumber) tempCode += "1";
                    tempNumber = parent;
                    parent = this->huffTree[parent].parent;
                }
                //cout << tempCode;
                break;
            }
        }
        // not found
        if (!flag) {
            cout << "\n\nWarning：\n\nNode Not Found" << str[i] << " Return Last Step\n" << endl;
            system("pause");
            
            return;
        }
        // reverse the list
        reverse(tempCode.begin(), tempCode.end());
        cout << tempCode;
    }
    cout << endl;
    system("pause");
    
}

void BiTreeApplication::decoding() {
    if (!this->hasConstruct) {
        cout << "---------------------------\nTips：\n\nBi-Tree has bot been built, Please execute opt-1\n---------------------------" << endl;
        system("pause");
        
        return;
    }
    cout << "\nenter Huffman code：";
    string source;
    cin >> source;
    cout << "\nThe Result is ：";

    int ptr = this->maxLength;
    for (int i = 0; i < source.length(); i++) {
        if (this->huffTree[ptr].lch != 0 && this->huffTree[ptr].rch != 0) {
            if (source[i] == '0') {
                ptr = this->huffTree[ptr].lch;
            } else if (source[i] == '1') {
                ptr = this->huffTree[ptr].rch;
            } else {
                cout << "\n----------------------\nWarning：\n\nWrong，Returning\n----------------------";
                system("pause");
                
                return;
            }
        } else {
            cout << this->huffTree[ptr].data;
            ptr = this->maxLength;
            i--; // roll back
        }
    }
    cout << endl;
    system("pause");
    
}

void BiTreeApplication::mainBody() {
    int choose = 0;
    do {
        cout << "-----------------\nBiTree Application Test\n-----------------" << endl
             << "1. Build Bi-Tree" << endl
             << "2. Encode" << endl
             << "3. Decode" << endl
             << "0. Exit System\n-----------------" << endl
             << "Enter Option : " ;
        cin >> choose;
        switch (choose) {
            case 1: this->init(); break;
            case 2: this->encoding(); break;
            case 3:	this->decoding(); break;
            default: return;
        }
    } while (choose);
}

/*
* s1、s2 are initialized with 0
* s1 and s2 should be a index, not a value.
* s1 is the smallest one , and s2 is the second smallest one
*/
void BiTreeApplication::selectNode(int& s1,int limit, int& s2) {

    int number1 = INT_MAX;
    int number2 = INT_MAX;
    for (int i = 1; i <= limit; i++) {
        // we can ensure that parent is not 0
        // find the two smallest node directly
        if (this->huffTree[i].parent != 0) continue;
        int temp = this->huffTree[i].weight;
        if (temp < number2) {
            if (temp > number1) {
                // copy to 2 directly
                number2 = temp;
                s2 = i;
            } else {
                // copy to 1, and 1 copy to 2
                number2 = number1;
                number1 = temp;
                s2 = s1;
                s1 = i;
            }
        }
    }
}
