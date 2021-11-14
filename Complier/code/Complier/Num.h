#pragma once
#ifndef NUM_H
#define NUM_H

#include"Token.h"
#include"TokenType.h"
#include<string>
#include<sstream>
using namespace std;

class Num : public Token
{
public:
    int val;
    Num(int val)
    {
        this->val = val;
        this->type = NUM;
    }
    virtual string toString()
    {
        stringstream ss;
        ss << val;
        return ss.str();
    }
protected:

private:
};

#endif // NUM_H
