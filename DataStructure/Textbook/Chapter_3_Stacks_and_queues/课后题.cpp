#include"Header.h"

template<class T>
class Stack {

private:
	T data[100];
	int capacity;
	int topPosi;
	int bottom;

public:

	Stack() {
		capacity = 100;
		topPosi = 0;
		bottom = 0;
	}

	bool empty() {
		return topPosi == bottom;
	}

	T top() {
		if(empty()) return 0;
		return data[topPosi - 1];
	}

	void pop() {
		if (empty()) return;
		topPosi--;
	}

	void push(T e) {
		if (topPosi - bottom >= capacity) return;
		data[topPosi] = e;
		topPosi++;
	}

};




//2.2

bool isPlalindrome(string str) {
	if (str.size() == 0 || str.size() == 1) return true;
	Stack<char> s;
	int posi = 0;
	for (posi = 0; posi <= (str.size() - 2) / 2; posi++) {
		s.push(str[posi]);
	}
	if (str.size() % 2) posi++;
	while (!s.empty() && posi < str.size()) {
		if (s.top() == str[posi]) {
			s.pop();
			posi++;
		} else return false;
	}
	if (s.empty()) return true;
}


//2.3

void mystack() {
	int* stk = new int[10];
	int bottom = 0;
	int top = 0;
	int temp = 0;
	while (cin >> temp) {
		if (top - bottom == 10) {
			cout << "OVERFLOW" << endl;
			return;
		}
		if (top == bottom && temp == -1) {
			cout << "EMPTY STACK" << endl;
			return;
		}
		if (-1 == temp) {
			cout << "pop : " << stk[--top] << endl;
		} else {
			stk[top] = temp;
			top++;
		}
	}
}


//2.5.1

/*

	A/D is legal.

*/

//2.5.2

bool isLegal(string str) {
	int stk = 0; 
	for (auto i : str) {
		if (i == 'I') stk++;
		else stk--;
		if (stk < 0) return false;
	}
	if (stk > 0) return false;
	return true;
}




//2.9.1

int Ack_1(int m, int n) {
	if (0 == m) return n + 1;
	if (0 == n && 0 != m) return Ack_1(m - 1, 1);
	if (0 != m && 0 != n) return Ack_1(m - 1, Ack_1(m, n - 1));
}

//2.9.2

int Ack_2(int m, int n) {
	Stack<int> s;
	s.push(m);
	while (!s.empty()) {
		m = s.top();
		s.pop();
		if (0 == m || 0 == n) {
			n += m + 1;
		} else {
			s.push(--m);
			s.push(++m);
			n--;
		}
	}
	return n;
}


//defination

struct ListNode {
	int val;
	ListNode* next;
	ListNode(int x) : val(x), next(NULL) {}
	ListNode(int x, ListNode* n) : val(x), next(n) {}
};

//2.10.1

int recursionMax(ListNode* head) {
	if (!head->next) return head->val;
	return max(head->next->val, recursionMax(head->next));
}

//2.10.2

int recursionNum(ListNode* head) {
	if (!head->next) return 1;
	return 1 + recursionNum(head->next);
}

//2.10.3

double recursionAvg(ListNode* head, int count = 0, double sum = 0) {
	if (!head->next) return sum / count;
	else {
		count++;
		sum += head->next->val;
		return recursionAvg(head->next, count, sum);
	}
}