#include<iostream>
using namespace std;

//单向链表实现
class singleNode {
public:
	int id;
	singleNode* next;

	singleNode() : id(0) , next(NULL){}
	singleNode(int i, singleNode* n) {
		this->id = i;
		this->next = n;
	}

	void insertAsSuc(int id) {
		singleNode* temp = new singleNode(id, NULL);
		temp->next = this->next;
		this->next = temp;
	}
};

class singleList {
public:
	
	singleList() {
		_size = 0;
		header = new singleNode(0, NULL);
	}
	~singleList() {
		singleNode* p = this->header;
		singleNode* q = p->next;
		while (_size--) {
			delete p;
			p = q;
			q = q->next;
		}
	}

	void insertAsFirst(int data) {
		singleNode* temp = new singleNode(data, header->next);
		header->next = temp;
		_size++;
	}

	void insertAsLast(int data) {
		if (_size == 0) {
			this->insertAsFirst(data);
			return;
		}
		int t = _size;
		singleNode* temp = header;
		while (t--) temp = temp->next;
		temp->next = new singleNode(data, NULL);
		_size++;
	}

	int remove(singleNode* posi) {
		int e = posi->id;
		singleNode* temp;
		for (temp = header; temp->next != posi; temp = temp->next);
		if (posi == first()) last()->next = posi->next;
		temp->next = posi->next;
		delete posi;
		_size--;
		return e;
	}

	singleNode* first() {	return header->next;	}

	singleNode* last() {
		int t = _size;
		singleNode* temp = header;
		while (t--) temp = temp->next;
		return temp;
	}

	int getSize() {	return this->_size;	}

private:
	singleNode* header;
	int _size;
};

int main() {
	int allFlag = 1;
	int number;
	do {
		cout << "请输入人数：";
		cin >> number;
		if (number > 0) allFlag = 0;
		else cout << "输入的人数应该大于0" << endl;
	} while (allFlag);
	
	int* p = new int[number];
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
	singleList sl;
	for (int i = 1; i <= number; i++) sl.insertAsLast(i);
	sl.last()->next = sl.first();

	singleNode* temp = sl.first();
	for (int i = 1; i < startID; i++) temp = temp->next;
	while (sl.getSize()) {
		for (int j = 1; j < m; j++) temp = temp->next;  //要删除的节点
		singleNode* nex;
		nex = temp->next;
		cout << sl.remove(temp) << " ";
		temp = nex;
	}
	delete[] p;
	return 0;
} 
