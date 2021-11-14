#pragma once
#ifndef STR_H
#define STR_H

#include"Token.h"
#include"TokenType.h"
#include<string>
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

#endif // STR_H
