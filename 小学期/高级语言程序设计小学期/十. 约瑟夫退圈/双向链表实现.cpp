#include<iostream>
#include"List.h"
using namespace std;

int main() {
	int allFlag = 1;
	int number;
	do {
		cout << "������������";
		cin >> number;
		if (number > 0) allFlag = 0;
		else cout << "���������Ӧ�ô���0" << endl;
	} while (allFlag);
	
	allFlag = 1;
	int startID;
	do {
		cout << "��������ʼID: ";
		cin >> startID;
		if (startID > 0 && startID <= number) allFlag = 0;
		else cout << "ID ������" << endl;
	} while (allFlag);

	int m;
	allFlag = 1;
	do {
		cout << "��������������";
		cin >> m;
		if (m < 0) cout << "�������������ڵ���0" << endl;
		else allFlag = 0;
	} while (allFlag);
	cout << "���еĴ���Ϊ��";

	List l;
	for (int i = 1; i <= number; i++) l.insertAsLast(i);
	l.last()->suc = l.first();
	l.first()->pre = l.last();
	Posi temp = l.first();
	for (int i = 1; i < startID; i++) { temp = temp->suc; }
	while (l.getSize()) {
		for (int i = 1; i < m; i++) { temp = temp->suc; }
		Posi nex = temp->suc;
		cout << l.remove(temp) << " ";
		temp = nex;
	}



	return 0;
}