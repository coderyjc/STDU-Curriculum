#include "BigInteger.h"

BigInteger::BigInteger() {
	//cout << "default copy constructor called" << endl;

	init();
}

BigInteger::BigInteger(const BigInteger& b) {
	init();
	this->isMinus = b.isMinus;
	this->_size = 0;
	Posi temp = b.header->suc;
	while (temp->suc) {
		this->insertAsLast(temp->data);
		temp = temp->suc;
	}
}

BigInteger::BigInteger(const int& b) {
	init();
	//cout << "int copy constructor called" << endl;
	int n = b;
	if (b < 0) {
		this->isMinus = 1;
		n = -n;
	} else this->isMinus = 0;
	while (n) {
		this->insertAsFirst(n % 10);
		n /= 10;
	}
}

BigInteger::BigInteger(const long& b) {
	init();
	//cout << "long copy constructor called" << endl;
	long n = b;
	if (b < 0) {
		this->isMinus = 1;
		n = -n;
	} else this->isMinus = 0;
	while (n) {
		this->insertAsFirst(n % 10);
		n /= 10;
	}
}

ostream& operator<<(ostream& cout, BigInteger& b) {
	Posi temp = b.first();
	if (b.isMinus) cout << "-";
	while (temp->suc) {
		cout << temp->data;
		temp = temp->suc;
	}
	return cout;
}

istream& operator>>(istream& cin, BigInteger& b) {
	b.clear();
	string number;
	cin >> number;
	for (int i = 0; i < number.size(); i++) {
		if (number[i] == '-') {
			b.isMinus = 1;
			continue;
		}
		b.insertAsLast(number[i] - '0');
	}
	return cin;
}

void BigInteger::operator=(int& number) {
	this->clear();
	while (number) {
		this->insertAsFirst(number % 10);
		number /= 10;
	}
	return;
}

BigInteger operator+(BigInteger& b1, BigInteger& b2) {

	if (!b1.isMinus && b2.isMinus) {
		b2.isMinus = 0;
		return b1 - b2;
	}
	if (b1.isMinus && !b2.isMinus) {
		b1.isMinus = 0;
		return b2 - b1;
	}

	BigInteger temp;
	//p1是长的， p2是短的
	Posi p1 = b1.size() >= b2.size() ? b1.last() : b2.last();
	Posi p2 = b1.size() >= b2.size() ? b2.last() : b1.last();

	if ((b1.isMinus && b2.isMinus) || ((!b1.isMinus) && (!b2.isMinus))) {
		while (p1->pre && p2->pre) {
			temp.insertAsFirst(p1->data + p2->data);
			p1 = p1->pre;
			p2 = p2->pre;
		}
		while (p2->pre) {
			temp.insertAsFirst(p2->data);
			p2 = p2->pre;
		}
		while (p1->pre) {
			temp.insertAsFirst(p1->data);
			p1 = p1->pre;
		}
	}
	
	Posi t = temp.last();
	while (t->pre) {
		if (t == temp.first() && t->data >= 10) {
			t->data -= 10;
			temp.insertAsFirst(1);
			break;
		}
		if (t->data >= 10) {
			t->data -= 10;
			t->pre->data++;
		}
		t = t->pre;
	}

	if (b1.isMinus && b2.isMinus) temp.isMinus = 1;
	else temp.isMinus = 0;
	return temp;
}

BigInteger operator-(BigInteger& b1, BigInteger& b2) {

	if (!b1.isMinus && b2.isMinus) {
		b2.isMinus = 0;
		return b1 + b2;
	}
	if (b1.isMinus && !b2.isMinus) {
		b2.isMinus = 1;
		return b1 + b2;
	}
	if (b1.isMinus && b2.isMinus) {
		b1.isMinus = b2.isMinus = 0;
		return b2 - b1;
	}

	int b1IsBigger = b1 > b2; //这个大吗 ？

	BigInteger temp;
	Posi p1 = b1IsBigger ? b1.last() : b2.last();
	Posi p2 = b1IsBigger ? b2.last() : b1.last();
	// p1 是绝对值大的数
	while (p1->pre && p2->pre) {
		temp.insertAsFirst(p1->data - p2->data);
		p1 = p1->pre;
		p2 = p2->pre;
	}
	while (p1->pre) {
		temp.insertAsFirst(p1->data);
		p1 = p1->pre;
	}
	while (p2->pre) {
		temp.insertAsFirst(p2->data);
		p2 = p2->pre;
	}

	Posi t = temp.last();
	while (t->pre) { //进位
		if (t->data < 0) {
			t->data += 10;
			t->pre->data--;
		}
		t = t->pre;
	}

	int flag = 1;
	while (flag) {
		if (temp.header->suc->data == 0 && temp._size > 1)
			temp.remove(temp.header->suc);
		else flag = 0;
	}

	if (b1.isMinus && b1IsBigger) temp.isMinus = 1;
	else if (b1.isMinus && !b1IsBigger) temp.isMinus = 0;
	else if (!b1.isMinus && b1IsBigger) temp.isMinus = 0;
	else if (!b1.isMinus && !b1IsBigger) temp.isMinus = 1;
	else;
	if (temp._size == 1 && temp.first()->data == 0) temp.isMinus = 0;

	return temp;
}

BigInteger operator*(BigInteger& b1, BigInteger& b2) {
	BigInteger temp;
	Posi p1 = b1 > b2 ? b1.last() : b2.last(); //p1 大
	Posi p2 = b1 > b2 ? b2.last() : b1.last(); //p1 大

	int dir = b1 > b2 ? b2.getINT() : b1.getINT();
	while (p1->pre && p2->pre) {
		temp.insertAsFirst(p1->data * dir);
		p1 = p1->pre;
		p2 = p2->pre;
	}
	while (p1->pre) {
		temp.insertAsFirst(p1->data);
		p1 = p1->pre;
	}
	while (p2->pre) {
		temp.insertAsFirst(p2->data);
		p2 = p2->pre;
	}
	Posi t = temp.last();
	while (t->pre) {
		if (t == temp.first()) break;
		if (t->data / 10 != 0) {
			t->pre->data += (t->data / 10);
			t->data %= 10;
		}
		t = t->pre;
	}
	if (!b1.isMinus && b2.isMinus || b1.isMinus && !b2.isMinus) temp.isMinus = 1;
	else temp.isMinus = 0;

	return temp;
}

BigInteger operator*(BigInteger& b1, int& b2) {
	BigInteger temp;
	Posi p1 = b1.last() ; //p1 大

	int dir =  b2;
	while (p1->pre) {
		temp.insertAsFirst(p1->data * dir);
		p1 = p1->pre;
	}
	Posi t = temp.last();
	while (t->pre) {
		if (t == temp.first()) {
			while (temp.first()->data >= 10) {
				temp.insertAsFirst(temp.first()->data / 10);
				temp.first()->suc->data %= 10;
			}
		}
		if (t->data / 10 != 0) {
			t->pre->data += (t->data / 10);
			t->data %= 10;
		}
		t = t->pre;
	}
	 temp.isMinus = 0;
	return temp;
}


BigInteger::~BigInteger() {
	clear();
	header->suc = NULL;
	tailer->pre = NULL;
	delete header;
	delete tailer;
}

BigInteger& BigInteger::operator=(BigInteger& b) {
	init();
	this->isMinus = b.isMinus;
	this->_size = 0;
	Posi temp = b.header->suc;
	while (temp->suc) {
		this->insertAsLast(temp->data);
		temp = temp->suc;
	}
	return *this;
}

bool BigInteger::operator>(BigInteger& b2) {
	if (this->_size > b2._size) return 1;
	if (this->_size < b2._size) return 0;
	Posi p1 = this->first();
	Posi p2 = b2.first();
	while (p1->suc) {
		if (p1->data > p2->data)
			return 1;
		if (p1->data < p2->data)
			return 0;
		p1 = p1->suc;
		p2 = p2->suc;
	}
	return 0;
}

int BigInteger::size() {
	return this->_size;
}

Posi BigInteger::first() {
	return this->header->suc;
}

Posi BigInteger::last() {
	return this->tailer->pre;
}

void BigInteger::init() {
	header = new Node(NULL, 0, NULL);
	tailer = new Node(header, 0, NULL);
	header->suc = tailer;
	_size = 0;
}

int BigInteger::remove(Posi p) {
	int e = p->data;
	p->pre->suc = p->suc;
	p->suc->pre = p->pre;
	delete p;
	_size--;
	return e;
}

int BigInteger::clear() {
	int oldsize = _size;
	while (_size) remove(header->suc);
	return oldsize;
}

void BigInteger::insertAsFirst(int data) {
	this->header->insertAsSuc(data);
	_size++;
}

void BigInteger::insertAsLast(int data) {
	this->tailer->insertAsPre(data);
	_size++;
}

int BigInteger::getINT() {
	Posi t = this->last();
	int sum = 0;
	for (int i = 1; t->pre; i *= 10) {
		sum += i * t->data;
		t = t->pre;
	}
	return sum;
}
