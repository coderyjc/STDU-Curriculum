#include"Header.h"
#include<iostream>
using namespace std;


// Liner realization of sequal list

#define MAXSIZE 100 //The max size of the table.

template<class ElemType>
class SqList{

private:
	ElemType* elem;
	int length;

public:

	Status InitList(); //initialize the linear list

	Status DestoryList(); //destory the list

	Status ClearList();//clear the list but not destory it

	bool empty(); // empty:1 ; not empty:2

	int Length(); // return its length

	Status GetElem(int i, ElemType& e); //returh its i th element

	int LocateElem(ElemType e); //find the e's location and return its position

	Status PriorElem(ElemType cur_e, ElemType& pre_e); //prior element

	Status NextElem(ElemType cur_e, ElemType& next_e); //next element

	Status ListInsert(int i, ElemType e); //insert in the i-th

	Status ListDelete(int i, ElemType& e); //delete  the i-th element

	void showList(string str); //print all elements
};

template<class ElemType>
Status SqList<ElemType>::InitList() {
	this->length = 0;
	this->elem = new ElemType[MAXSIZE]; // 100 elements
	return OK;
}

template<class ElemType>
Status SqList<ElemType>::DestoryList() {
	if (NULL == this->elem) return ERROR;
	if (NULL != this->elem) delete[] this->elem;
	this->length = 0;
	return OK;
}

template<class ElemType>
Status SqList<ElemType>::ClearList() {
	if (NULL == this->elem) return ERROR;
	this->length = 0;
	return OK;
}

template<class ElemType>
bool SqList<ElemType>::empty() {
	return 0 == this->length;
}

template<class ElemType>
int SqList<ElemType>::Length() {
	return this->length;
}

template<class ElemType>
Status SqList<ElemType>::GetElem(int i, ElemType& e) {
	if (NULL == this->elem || i < 1 || i > this->length) return ERROR;
	e = this->elem[i - 1];
	return OK;
}

template<class ElemType>
int SqList<ElemType>::LocateElem(ElemType e) {
	if (NULL == this->elem) return ERROR;
	for (int i = 0; i < this->length; i++) // find it and return its position
		if (e == this->elem[i]) 
			return ++i;	
	return -1; //not found 
}

template<class ElemType>
Status SqList<ElemType>::PriorElem(ElemType cur_e, ElemType& pre_e) {
	int pos = 0;
	for (pos = 0; pos < this->length; pos++)
		if (cur_e == this->elem[pos]) break;
	if (0 == pos) return ERROR;
	pre_e = this->elem[pos - 1];
	return OK;
}

template<class ElemType>
Status SqList<ElemType>::NextElem(ElemType cur_e, ElemType& next_e) {
	int pos = 0;
	for (pos = 0; pos < this->length; pos++)
		if (cur_e == this->elem[pos]) break;
	if (pos == this->length - 1) return ERROR;
	next_e = this->elem[pos + 1];
	return OK;
}

template<class ElemType>
Status SqList<ElemType>::ListInsert(int i, ElemType e) {
	if (this->length + 1 < i || 0 >= i) return ERROR;
	for (int j = this->length; j >= i; j--) {
		this->elem[j] = this->elem[j - 1];
	}
	this->elem[i - 1] = e;
	this->length++;
	return OK;
}

template<class ElemType>
Status SqList<ElemType>::ListDelete(int i, ElemType& e) {
	if (i <= 0 || i > this->length) return ERROR;
	e = this->elem[i - 1];
	for (int j = i; j < this->length; j++)
		this->elem[j - 1] = this->elem[j];
	this->length--;
	return OK;
}

template<class ElemType>
void SqList<ElemType>::showList(string str) {
	cout << "------------------------------" << endl;
	cout << str << endl;
	cout << "Length = " << this->length << endl;
	for (int i = 0; i < this->length; i++) cout << this->elem[i] << " ";
	cout << "\n------------------------------" << endl;
}

int main() {
	SqList<int> S;
	//---------Init test-------
	S.InitList();
	S.showList("InitList:");
	cout << "isempty: " << S.empty() << endl;
	//------------Insert test-------
	S.ListInsert(1, 1);
	S.ListInsert(1, 2);
	S.ListInsert(30, 4);
	S.ListInsert(-2, 5);
	S.showList("insert test:");
	//-------------clear test-------
	S.ClearList();
	S.showList("After clear:");
	//-----------Delete test----------
	S.ListInsert(1, 8);
	S.ListInsert(1, 9);
	S.ListInsert(1, 10);
	S.showList("now list:");
	int temp = 0;
	S.ListDelete(-3, temp);
	S.ListDelete(1, temp);
	S.showList("after delete 1st: ");
	S.ListDelete(99, temp);
	S.ListDelete(4, temp);
	S.showList("after delete 4th: ");
	//------------nextElem------
	S.NextElem(8, temp);
	cout << "8-next is " << temp << endl;
	//-----------preElem----------
	S.PriorElem(8, temp);
	cout << "8-pre is " << temp << endl;
	//-------getElem---------
	S.GetElem(1, temp);
	cout << "the 1th elem is " << temp << endl;
	S.GetElem(3, temp);
	cout << "the 3th elem is " << temp << endl;
	//------locateElem-------
	cout << "9 is the " << S.LocateElem(9) << " element" << endl;
	cout << "7 is the " << S.LocateElem(7) << " element" << endl;
	//------empty-------
	cout << "isempty: " << S.empty() << endl;
	//--------destory-----
	S.DestoryList();

	return 0;
}

