#pragma once
#include<string>

#include"Token.h"
#include"TokenType.h"

using namespace std;

class Str : public Token
{
public:
    string str;
    Str(string str)
    {
        this->str = str;
        this->type = STR;
    }
    virtual string toString()
    {
        return str;
    }
protected:

private:
};