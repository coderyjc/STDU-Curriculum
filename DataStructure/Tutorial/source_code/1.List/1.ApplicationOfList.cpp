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
	~ListNode() {
		if (data) {
			data = NULL;
			delete data;
		}
		if (next) {
			next = NULL;
			delete next;
		}
	}
};

ListNode* head;

int main() {
	cout << "指定人数 n : ";
	int n; cin >> n;
	cout << "指定初始上报的上限值 m : ";
	int m; cin >> m;
	cout << "输入这些人的密码 ：" << endl;
	int temp;
	
	ListNode* t = NULL; //临时节点

	for (int i = 1; i <= n; i++) { //数值录入
		cin >> temp;
		if (i == 1) {
			head = new ListNode(new People(i, temp), NULL);
			t = head;
		} else if(i == n){
			t->next = new ListNode(new People(i, temp), head);
			t = t->next;
		} else {
			t->next = new ListNode(new People(i, temp), NULL);
			t = t->next;
		}
	}

	cout << "出列顺序：";

 	while (t && t->next != t) { //DeQueue
		for (int i = 1; i < m; i++) t = t->next;
		ListNode* p = t->next;
		if (p) {
			m = p->data->pwd;
			cout << p->data->ID << " ";
			t->next = p->next;
			delete p;
		} else break;
	}
	if(t) cout << t->data->ID << endl;

	return 0;
}