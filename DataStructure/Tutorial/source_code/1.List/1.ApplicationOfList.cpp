//#include"Header.h"

#include<iostream>

using namespace std;

class People {
public:

	People(int id = 0, int pwd = 0) {
		this->ID = id;
		this->pwd = pwd;
	}

	People(const People& p) {
		this->ID = p.ID;
		this->pwd = p.pwd;
	}

public:

	int ID;
	int pwd;
};

class ListNode {
public:
	People* data;
	ListNode* next;

public:
	ListNode(People* d, ListNode* n = NULL) : data(d), next(n) {}
};

ListNode* head;

int main() {
	int flag = 0; // 输入正确检查
	int n = 0, m = 0;
	
	cout << "----------------------\n       约瑟夫退圈\n----------------------" << endl;

	do{
		cout << "指定人数 n : ";
		cin >> n;
		if (n <= 0) {
			flag = 1;
			cout << "人数应该大于 0, 请重新输入" << endl;
		} else flag = 0;
	} while (flag);

	flag = 0;
	do {
		cout << "指定初始上报的上限值 m : ";
		cin >> m;
		if (m <= 0) {
			flag = 1;
			cout << "初始上报的上限值应该大于0，请重新输入" << endl;
		} else flag = 0;
	} while (flag);

	flag = 0;
	cout << "输入这些人的密码 ：" << endl;
	int temp;

	ListNode* t = NULL; //临时节点

	for (int i = 1; i <= n; i++) { //数值录入

		do {
			cin >> temp;
			if (temp <= 0) {
				flag = 1;
				cout << "密码应该大于0，请重新输入" << endl;
			} else flag = 0;
		} while (flag);

		if (i == 1) {
			head = new ListNode(new People(i, temp), NULL);
			t = head;
		} else if (i == n) {
			t->next = new ListNode(new People(i, temp), head);
			t = t->next;
		} else {
			t->next = new ListNode(new People(i, temp), NULL);
			t = t->next;
		}
	}

	int* outOrder = new int[n];
	int cntOutNumber = 0;
	int totalNumber = n;
	cout << "-------------------------" << endl;

	while (t && t->next != t) { 
		for (int i = 1; i < m; i++) t = t->next;
		ListNode* p = t->next;
		if (p) {
			m = p->data->pwd;
			outOrder[cntOutNumber++] = p->data->ID; // 记录出列顺序
			cout << p->data->ID << " 出列，当前队列: ";
			t->next = p->next;

			// 输出当前队列的值
			int temp = --totalNumber;
			ListNode* pt = t;
			while (temp--) {
				cout << pt->data->ID << ' ';
				pt = pt->next;
			}
			cout << endl;

			delete p;
		} else break;
	}
	if (t) cout << t->data->ID << " 出列" << "，队列已空" << endl;
	outOrder[cntOutNumber++] = t->data->ID; //最后一个数字入队 

	cout << "-------------------------\n出列顺序为：";
	for (int i = 0; i < n; i++) cout << outOrder[i] << " ";
	cout << "\n-------------------------" << endl;
	return 0;
}