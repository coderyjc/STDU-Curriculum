#pragma once
#include<iostream>
using namespace std;

#define Posi Node*

class Node {
public:

	Node(Posi p = NULL, int d = 0, Posi s = NULL) : pre(p), data(d), suc(s) {}
	~Node() {}

	Posi insertAsPre(int d) {
		Posi temp = new Node(pre, d, this);
		temp->pre->suc = temp;
		this->pre = temp;
		return temp;
	}

	Posi insertAsSuc(int d) {
		Posi temp = new Node(this, d, suc);
		this->suc->pre = temp;
		this->suc = temp;
		return temp;
	}

	Posi pre;
	int data;
	Posi suc;

};