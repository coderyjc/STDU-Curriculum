#pragma once
#include"listNode.h"
#include<iostream>
using namespace std;


class BigInteger {

public:
	//-----------构造函数

	BigInteger();
	BigInteger(const int& b);
	BigInteger(const long& b);
	BigInteger(const BigInteger& b);

	//-----------析构函数

	~BigInteger();

	void operator=(int& number);
	//-----------可写

	friend ostream& operator<<(ostream& cout, BigInteger& b);
	friend istream& operator>>(istream& cin, BigInteger& b);
	friend BigInteger operator+(BigInteger& b1, BigInteger& b2);
	friend BigInteger operator-(BigInteger& b1, BigInteger& b2);
	friend BigInteger operator*(BigInteger& b1, BigInteger& b2);
	friend BigInteger operator*(BigInteger& b1, int& b2);

	BigInteger& operator=(BigInteger& b);

	bool operator>(BigInteger& b);

	//------------节点操作

	int size();

	Posi first();

	Posi last();

	void init();

	int remove(Posi p); //删除节点并返回数据

	int clear(); // 清空链表并返回其大小

	void insertAsFirst(int data); //作为首节点插入

	void insertAsLast(int data); //作为尾节点插入

	int getINT(); //获取int类型的值

private:


	Posi header;
	Posi tailer;
	int _size;

	int isMinus;

};

