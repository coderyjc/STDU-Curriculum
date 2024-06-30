#pragma once

class Tree {
public:

    Tree(float weight = 0, int p = 0, int l = 0, int r = 0) {
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

    float weight;
    int parent;
    int lch;
    int rch;
};


class HuffNode {
public:
    HuffNode() {
        this->data = 0;
        this->lch = 0;
        this->parent = 0;
        this->rch = 0;
        this->weight = 0;
    }

    char data;
    float weight;
    int parent;
    int lch;
    int rch;
};
