#pragma once

#include"Token.h"
#include"TokenType.h"

class Char : public Token
{
public:
    char ch;
    Char(char ch)
    {
        this->ch = ch;
        this->type = CH;
    }

    virtual string toString()
    {
        string str = "";
        str += ch;
        return str;
    }

protected:

private:
};