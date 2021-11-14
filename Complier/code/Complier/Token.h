#pragma once
#ifndef TOKEN_H
#define TOKEN_H
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
    //virtual ~Token();
    virtual string toString()
    {
        if ((type != ID) && (type != STR) && (type != NUM) && (type != CH))
            return TokenTypeArray[type];
    }
protected:
private:
};

#endif // TOKEN_H
