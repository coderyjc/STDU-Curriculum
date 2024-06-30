#include "List.h"

List::List() {
	cout << "list ��Ĭ�Ϲ���" << endl;
	init();
}

List::List(const List& l) {
	cout << "list ����������" << endl;
	init();
	_size = l._size;
	Posi temp = l.header->suc;
	while (temp->suc) {
		this->insertAsLast(temp->data);
	}
}

List::~List() {
	clear();
	header->suc = NULL;
	tailer->pre = NULL;
	delete header;
	delete tailer;
	cout << "list������������" << endl;
}

int List::size() {
	return this->_size;
}

Posi List::first() {
	return this->header->suc;
}

Posi List::last() {
	return this->tailer->pre;
}

void List::init() {
	header = new Node(NULL, 0, NULL);
	tailer = new Node(header, 0, NULL);
	header->suc = tailer;
	_size = 0;
}

int List::remove(Posi p) {
	int e = p->data;
	p->pre->suc = p->suc;
	p->suc->pre = p->pre;
	delete p;
	_size--;
//	cout << "remove��������, ɾ�� " << e << endl;
	return e;
}

int List::clear() {
	int oldsize = _size;
	while (_size) remove(header->suc);
//	cout << "clear��������" << endl;
	return oldsize;
}

void List::insertAsFirst(int data) {
	this->header->insertAsSuc(data);
	_size++;
}

void List::insertAsLast(int data) {
	this->tailer->insertAsPre(data);
	_size++;
}

void List::setSize(int n) {
	this->_size = n;	
}
