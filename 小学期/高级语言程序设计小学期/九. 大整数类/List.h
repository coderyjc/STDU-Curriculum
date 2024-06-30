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

	int remove(Posi p); //ɾ���ڵ㲢��������

	int clear(); // ��������������С

	void insertAsFirst(int data); //��Ϊ�׽ڵ����

	void insertAsLast(int data); //��Ϊβ�ڵ����

private:
	Posi header;
	Posi tailer;
	int _size;
};