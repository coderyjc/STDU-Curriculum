#pragma once
#include"listNode.h"
#include<iostream>
using namespace std;


class BigInteger {

public:
	//-----------���캯��

	BigInteger();
	BigInteger(const int& b);
	BigInteger(const long& b);
	BigInteger(const BigInteger& b);

	//-----------��������

	~BigInteger();

	void operator=(int& number);
	//-----------��д

	friend ostream& operator<<(ostream& cout, BigInteger& b);
	friend istream& operator>>(istream& cin, BigInteger& b);
	friend BigInteger operator+(BigInteger& b1, BigInteger& b2);
	friend BigInteger operator-(BigInteger& b1, BigInteger& b2);
	friend BigInteger operator*(BigInteger& b1, BigInteger& b2);
	friend BigInteger operator*(BigInteger& b1, int& b2);

	BigInteger& operator=(BigInteger& b);

	bool operator>(BigInteger& b);

	//------------�ڵ����

	int size();

	Posi first();

	Posi last();

	void init();

	int remove(Posi p); //ɾ���ڵ㲢��������

	int clear(); // ��������������С

	void insertAsFirst(int data); //��Ϊ�׽ڵ����

	void insertAsLast(int data); //��Ϊβ�ڵ����

	int getINT(); //��ȡint���͵�ֵ

private:


	Posi header;
	Posi tailer;
	int _size;

	int isMinus;

};

