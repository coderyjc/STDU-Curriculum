#include<iostream>
using namespace std;

#define MAX_STACK_SIZE 5

template<class T>
class MyDoubleStack {
public:
	MyDoubleStack() {
		_top[0] = _btm[0] = 0;
		_top[1] = _btm[1] = MAX_STACK_SIZE * 2;
		data = new T[MAX_STACK_SIZE * 2 + 1];
		capacity = MAX_STACK_SIZE;
	}

	int size();

	T top_0();
	T top_1();

	void push_0(T data);
	void push_1(T data);

	void pop_0();
	void pop_1();

	bool empty_0();
	bool empty_1();

private:
	int _top[2];
	int _btm[2];
	/*
		top[0] 为 基础栈
		top[1] 为 转移栈
	*/
	T* data;
	int capacity;
};

template<class T>
int MyDoubleStack<T>::size() {
	return this->_top[0] - this->_btm[0];
}

template<class T>
T MyDoubleStack<T>::top_0() {
	if (this->empty_0()) {
		cout << "Stack 0 is empty.." << endl;
		exit(0);
	}
	return this->data[this->_top[0] - 1];
}

template<class T>
T MyDoubleStack<T>::top_1() {
	if (this->empty_1()) {
		cout << "Stack 1 is empty.." << endl;
		exit(0);
	}
	return this->data[this->_top[1] + 1];
}

template<class T>
void MyDoubleStack<T>::push_0(T data) {
	if (size() + 1 > this->capacity) {
		cout << "OVERFLOW" << endl;
		exit(0);
	} else {
		this->data[_top[0]] = data;
		_top[0]++;
	}
}

template<class T>
void MyDoubleStack<T>::push_1(T data) {
	//	临时栈不需要 判断是不是满了
	this->data[_top[1]] = data;
	_top[1]--;
}

template<class T>
void MyDoubleStack<T>::pop_0() {
	if (this->empty_0()) {
		cout << "Stack 0 is empty" << endl;
		exit(0);
	} else {
		//delete this->top_0();
		this->_top[0]--;
	}
}

template<class T>
void MyDoubleStack<T>::pop_1() {
	if (this->empty_1()) {
		cout << "Stack 1 is empty" << endl;
		exit(0);
	} else {
		//delete this->top_1();
		this->_top[1]++;
	}
}

template<class T>
bool MyDoubleStack<T>::empty_0() {
	return this->_top[0] == this->_btm[0];
}

template<class T>
bool MyDoubleStack<T>::empty_1() {
	return this->_top[1] == this->_btm[1];
}
