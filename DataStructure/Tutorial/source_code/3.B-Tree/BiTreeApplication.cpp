#include "BiTreeApplication.h"
#include<iostream>
#include<string>
using namespace std;

BiTreeApplication::BiTreeApplication() {
	this->huffTree = new HuffNode[100](); // 初始容量为100个
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
	cout << "----------------\n正在初始化二叉树\n----------------" << endl;
	// enter chars and its weight;
	cout << "输入字符和其权值，中间以空格隔开，EOF 代表结束" << endl;

	char tempChar;
	int tempWeight;
	for (this->nodeCount = 1; cin >> tempChar >> tempWeight; nodeCount++) {
		this->huffTree[nodeCount].data = tempChar;
		this->huffTree[nodeCount].weight = tempWeight;
	}
	this->nodeCount--; //减去在循环的时候多出来的那个
	this->maxLength = this->nodeCount * 2 - 1;

	cout << "----------------\n提示\n\n输入字母代码成功\n----------------" << endl;
	system("pause");
	system("cls");
	cin.clear();
}

void BiTreeApplication::constructHuffTree() {
	if (this->maxLength <= 0) {
		cout << "---------------------------\n提示：\n\n字母代码未输入，请执行选项1\n---------------------------" << endl;
		system("pause");
		system("cls");
		return;
	}
	cout << "正在构建二叉树..." << endl;
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
	cout << "--------------\n提示：\n\n二叉树构建完毕\n--------------" << endl;
	system("pause");
	system("cls");
	this->hasConstruct = 1;
}

void BiTreeApplication::encoding() {
	if (!this->hasConstruct) {
		cout << "---------------------------\n提示：\n\n二叉树尚未建立, 请执行选项2\n---------------------------" << endl;
		system("pause");
		system("cls");
		return;
	}
	cout << "输入字符(不含空格): ";
	string str;
	cin.clear();
	cin >> str;
	cout << "\n哈夫曼编码为 :" << endl;
	for (int i = 0; i < str.length(); i++) {
		// 遍历树，寻找数据节点
		string tempCode = "";
		int flag = 0; // 有没有找到这个字母所在的节点
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
		// 在树中没找到这个节点
		if (!flag) {
			cout << "\n\n警告：\n\n未找到节点" << str[i] << " 程序即将返回上一层\n" << endl;
			system("pause");
			system("cls");
			return;
		}
		// 反转10序列然后输出
		reverse(tempCode.begin(), tempCode.end());
		cout << tempCode;
	}
	cout << endl;
	system("pause");
	system("cls");
}

void BiTreeApplication::decoding() {
	if (!this->hasConstruct) {
		cout << "---------------------------\n提示：\n\n二叉树尚未建立, 请执行选项2\n---------------------------" << endl;
		system("pause");
		system("cls");
		return;
	}
	cout << "\n输入Huffman code：";
	string source;
	cin >> source;
	cout << "\n解码结果为 ：";

	int ptr = this->maxLength;
	for (int i = 0; i <= source.length(); i++) {
		if (this->huffTree[ptr].lch != 0 && this->huffTree[ptr].rch != 0) {
			if (source[i] == '0') {
				ptr = this->huffTree[ptr].lch;
			} else if (source[i] == '1') {
				ptr = this->huffTree[ptr].rch;
			} else {
				cout << source[i];
			}
		} else {
			cout << this->huffTree[ptr].data;
			ptr = this->maxLength;
			i--; // 回退
		}
	}
	cout << endl;
	system("pause");
	system("cls");
}

void BiTreeApplication::mainBody() {
	int choose = 0;
	do {
		cout << "-----------------\n二叉树应用测试\n-----------------\n1. 初始化二叉树" << endl
			<< "2. 编制哈夫码" << endl
			<< "3. 为字符编码" << endl
			<< "4. 解二进制码" << endl
			<< "0. 退出系统\n-----------------" << endl
			<< "输入选项 : " ;
		cin >> choose;
		switch (choose) {
			case 1: this->init(); break;
			case 2:	this->constructHuffTree(); break;
			case 3: this->encoding(); break;
			case 4:	this->decoding(); break;
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
