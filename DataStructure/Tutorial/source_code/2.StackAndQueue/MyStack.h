#define MAX_STACK_SIZE 50

template<class T>
class MyStack {
public:

	MyStack() {
		_top = 0;
		_btm = 0;
		data = new T[MAX_STACK_SIZE];
		capacity = MAX_STACK_SIZE;
	}

	void push(T data);

	int size();

	void pop();

	T top();

	bool empty();

	void destory();

	void clean();


private:
	int _top;
	int _btm;
	T* data;
	int capacity;
};


template<class T>
void MyStack<T>::push(T data) {
	if (size() + 1 > this->capacity) {
		cout << "OVERFLOW" << endl;
		exit(0);
	} else {
		this->data[_top] = data;
		_top++;
	}
}

template<class T>
int MyStack<T>::size() {
	return _top - _btm;
}

template<class T>
void MyStack<T>::pop() {
	if (empty()) {
		cout << "Stack is empty" << endl;
		exit(0);
	} else {
		_top--;
	}
}

template<class T>
T MyStack<T>::top() {
	if (empty()) {
		cout << "Stack is empty." << endl;
		exit(0);
	}
	return data[_top - 1];
}

template<class T>
bool MyStack<T>::empty() {
	return _top == _btm;
}

template<class T>
void MyStack<T>::destory() {
	if (data != NULL) {
		delete[] data;
		data = nullptr;
	}
}

template<class T>
void MyStack<T>::clean() {
	_top = 0;
}
