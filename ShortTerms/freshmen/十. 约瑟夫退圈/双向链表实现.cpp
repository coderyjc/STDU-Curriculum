#include<iostream>
#include"List.h"
using namespace std;

int main() {
	int allFlag = 1;
	int number;
	do {
		cout << "请输入人数：";
		cin >> number;
		if (number > 0) allFlag = 0;
		else cout << "输入的人数应该大于0" << endl;
	} while (allFlag);
	
	allFlag = 1;
	int startID;
	do {
		cout << "请输入起始ID: ";
		cin >> startID;
		if (startID > 0 && startID <= number) allFlag = 0;
		else cout << "ID 不存在" << endl;
	} while (allFlag);

	int m;
	allFlag = 1;
	do {
		cout << "请输入间隔人数：";
		cin >> m;
		if (m < 0) cout << "间隔人数必须大于等于0" << endl;
		else allFlag = 0;
	} while (allFlag);
	cout << "出列的次序为：";

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