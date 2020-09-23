#pragma once

#define NodePosi(T) myNode<T>*

template<class T>
struct myNode {
	NodePosi(T) pre;
	NodePosi(T) suc;
	T data;

	myNode() {}
	myNode(NodePosi(T) p, NodePosi(T) s, T const& d) : pre(p), suc(s), data(d) {}
	myNode(const myNode& node) { this->pre = node.pre; this->suc = node.suc; this->data = node.data; }

	NodePosi(T) InsertAsPre(T const& e) {
		NodePosi(T) t = new myNode(pre, this, e);
		pre->suc = t;
		pre = t;
		return t;
	}

	NodePosi(T) InsertAsSuc(T const& e) {
		NodePosi(T) t = new myNode(this, suc, e);
		t->suc->pre = t;
		suc = t;
		return t;
	}
};