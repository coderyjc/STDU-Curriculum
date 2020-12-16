#pragma once
#include"ListNode.h"

class HashTableApp {
public:
	HashTableApp();

	// 读取姓名文件
	void readFile();

	// 输入所有姓名
	void enterName();
	
	// 向哈希表中插入值
	void insert(int posi, string data);

	// 计算哈希码
	int hashCode(string str);

	// 查看哈希表
	void layout();

	// 查找
	void find();

	// 程序主循环
	void mainLoop();

private:

	string names[30];
	ListNode* hashTable = new ListNode[27];
};

