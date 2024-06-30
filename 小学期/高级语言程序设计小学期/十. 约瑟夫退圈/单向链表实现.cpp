#include<iostream>
using namespace std;

//��������ʵ��
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
		cout << "������������";
		cin >> number;
		if (number > 0) allFlag = 0;
		else cout << "���������Ӧ�ô���0" << endl;
	} while (allFlag);
	
	int* p = new int[number];
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
	singleList sl;
	for (int i = 1; i <= number; i++) sl.insertAsLast(i);
	sl.last()->next = sl.first();

	singleNode* temp = sl.first();
	for (int i = 1; i < startID; i++) temp = temp->next;
	while (sl.getSize()) {
		for (int j = 1; j < m; j++) temp = temp->next;  //Ҫɾ���Ľڵ�
		singleNode* nex;
		nex = temp->next;
		cout << sl.remove(temp) << " ";
		temp = nex;
	}
	delete[] p;
	return 0;
} 
