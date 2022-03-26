#pragma once
#include<sstream>
#include<string>
#include"Token.h"
#include"TokenType.h"

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
