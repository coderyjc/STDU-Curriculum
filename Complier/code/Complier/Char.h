#pragma once
#ifndef CHAR_H
#define CHAR_H

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

#endif // CHAR_H
