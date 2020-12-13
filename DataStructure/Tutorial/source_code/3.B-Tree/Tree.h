#pragma once

class Tree { //树
public:

	Tree(float weight = 0, int p = 0, int l = 0, int r = 0) { // 全参构造
		this->weight = weight;
		this->parent = p;
		this->lch = l;
		this->rch = r;
	}

	Tree(const Tree& t) {
		this->lch = t.lch;
		this->rch = t.rch;
		this->parent = t.parent;
		this->weight = t.weight;
	}

	float weight; // 权值
	int parent; // 双亲
	int lch; //左孩子
	int rch; // 右孩子
};


class HuffNode { //哈夫曼树的节点
public:
	HuffNode() {
		this->data = 0;
		this->lch = 0;
		this->parent = 0;
		this->rch = 0;
		this->weight = 0;
	}

	char data;
	float weight; // 权值
	int parent; // 双亲
	int lch; //左孩子
	int rch; // 右孩子
};
