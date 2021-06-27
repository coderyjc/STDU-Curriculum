#pragma once

#include"listNode.h"


class BigInteger {
public:

	BigInteger();

	BigInteger(const BigInteger& l);

	~BigInteger();

	int size();

	Posi first();

	Posi last();

	void init();

	int remove(Posi p); //删除节点并返回数据

	int clear(); // 清空链表并返回其大小

	void insertAsFirst(int data); //作为首节点插入

	void insertAsLast(int data); //作为尾节点插入

private:
	Posi header;
	Posi tailer;
	int _size;
};