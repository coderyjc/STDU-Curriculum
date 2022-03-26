#pragma once
#include<string>
#include"TokenType.h"

using namespace std;


class Token
{
public:
    _TokenType type;
    Token(_TokenType type)
    {
        this->type = type;
    }
    Token() {}

    virtual string toString()
    {
        if ((type != ID) && (type != STR) && (type != NUM) && (type != CH))
            return TokenTypeArray[type];
    }
protected:
private:
};