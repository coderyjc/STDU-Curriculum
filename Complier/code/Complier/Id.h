#pragma once
#ifndef ID_H
#define ID_H


#include<string>
#include"Token.h"
//class Token;
using namespace std;

/**
*±êÊ¶·û
*/
class Id : public Token
{
public:
    string name;
    //Id();
    Id(string name)
    {
        this->name = name;
        this->type = ID;
    }
    virtual string toString()
    {
        return name;
    }

protected:

private:
};


#endif // ID_H
