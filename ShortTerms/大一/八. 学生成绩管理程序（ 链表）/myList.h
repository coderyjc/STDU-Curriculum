#include"myNode.h"
#include<iostream>
using namespace std;
typedef int Rank;

template<class T>
class myList {

private:
    NodePosi(T) header;
    NodePosi(T) tailer;
    int _size;

protected:
    void init(); //Initialize when created
    int clear(); //Clear all nodes
    void selectionSort(NodePosi(T) p, int n); //Selection sort from p, totally n

public:

    myList() { init(); } //Default
    myList(const myList& list); //copy constructor
    ~myList(); //Release all nodes

    Rank size() const { return _size; } //Get size
    bool empty() const { return _size <= 0; } //Is empty
    T& operator[] (Rank r) const; //reload []
    NodePosi(T) first() const { return header->suc; } //The first node
    NodePosi(T) last() const { return tailer->pre; } //The last node

    NodePosi(T) find(T const& e) const //Unordered list lookup in reverse order
    {
        return find(e, first(), _size);
    }
    NodePosi(T) find(T const& e, int n, NodePosi(T) p) const; //Find before p
    NodePosi(T) find(T e, NodePosi(T) p, int n) const; //Find after p

    NodePosi(T) selectMax(NodePosi(T) p, int n); //Select the largest among p and its N-1 successors
    NodePosi(T) selectMax() { return selectMax(first(), _size); } //find max in all

    NodePosi(T) insertAsFirst(T const& e); //Insert e(data) as the first node
    NodePosi(T) insertAsLast(T const& e); //Insert e(data) as the last node

    NodePosi(T) insertA(NodePosi(T) p, T const& e); //Insert e(data) after p(NodePosi)
    NodePosi(T) insertB(NodePosi(T) p, T const& e); //Insert e(data) before p(NodePosi)

    T remove(NodePosi(T) p); //Deletes the node at legal positionm return the deleted data
    void sort();//Sort in all list
    void sort(NodePosi(T) p, int n); //Sort in a range
    void reverse(); //Reverse the list
};

template<class T>
void myList<T>::init() {
    _size = 0;
    header = new myNode<T>;
    tailer = new myNode<T>;
    header->pre = NULL; tailer->suc = NULL;
    header->suc = tailer; tailer->pre = header;
}

template<class T>
int myList<T>::clear() {
    int oldsize = _size;
    while (_size) remove(header->suc);
    return oldsize;
}

template<class T>
void myList<T>::selectionSort(NodePosi(T) p, int n) {
    NodePosi(T) head = p->pre;
    NodePosi(T) tail = p;
    for (int i = 0; i < n; i++) tail = tail->suc;
    while (1 <= n--) {
        insertB(tail, remove(selectMax(head->suc, n)));
    }
}

template<class T>
T& myList<T>::operator[] (Rank r) const {
    NodePosi(T) t = this->first();
    while (0 < r--)  t = t->suc;
    return t->data;
}

template<class T>
NodePosi(T) myList<T>::find(T const& e, int n, NodePosi(T) p) const {
    NodePosi(T) t = p;
    while ((0 < n--) && t) { 
        if (e == t->data) 
            return t;  
        t = t->pre; 
    }
    return NULL;
}

template<class T>
NodePosi(T) myList<T>::find(T e, NodePosi(T) p, int n) const {
    NodePosi(T) t = p;
    while ((0 < n--) && t) {
        if (e == t->data) 
            return t; 
        t = t->suc; 
    }
    return NULL;
}

template<class T>
NodePosi(T) myList<T>::selectMax(NodePosi(T) p, int n) {
    NodePosi(T) max = p;
    NodePosi(T) cur;
    for (cur = p->suc; 1 <= n; n--) {
        if (cur->data >= max->data)
            max = cur;
        cur = cur->suc;
    }
    return max;
}

template<class T>
NodePosi(T) myList<T>::insertAsFirst(T const& e) { _size++;  return header->InsertAsSuc(e); }

template<class T>
NodePosi(T) myList<T>::insertAsLast(T const& e) { _size++; return tailer->InsertAsPre(e); }

template<class T>
NodePosi(T) myList<T>::insertA(NodePosi(T) p, T const& e) { _size++; return p->InsertAsSuc(e); }

template<class T>
NodePosi(T) myList<T>::insertB(NodePosi(T) p, T const& e) { _size++; return p->InsertAsPre(e); }

template<class T>
T myList<T>::remove(NodePosi(T) p) {
    T e = p->data;
    p->pre->suc = p->suc;
    p->suc->pre = p->pre;
    delete p;
    _size--;
    return e;
}

template<class T>
void myList<T>::sort(NodePosi(T) p, int n) {
    selectionSort(p, n);
}

template<class T>
void myList<T>::sort() {
    this->sort(first(), _size);
}

template<class T>
void myList<T>::reverse() {
    NodePosi(T) p = header->suc;
    NodePosi(T) q = tailer->pre;
    for (int i = 0; i < _size; i += 2) {
        T temp = p->data;
        p->data = q->data;
        q->data = temp;
        p = p->suc;
        q = q->pre;
    }
}

template<class T>
inline myList<T>::myList(const myList& list) {
    init();
    NodePosi(T) temp = list.first();
    int n = list.size();
    while (n--) {
        insertAsLast(temp->data);
        temp = temp->suc;
    }
}

template<class T>
myList<T>::~myList() { clear();  delete header;  delete tailer; }