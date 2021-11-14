#pragma once
#ifndef VAR_H
#define VAR_H
#include<vector>
#include<string>
#include"TokenType.h"
#include"Token.h"
#include"global.h"
#include"Lex.h"
using namespace std;


class Var
{
public:
    bool literal;
    vector<int> scopepath;
    bool externed;
    _TokenType type;
    string name;
    bool isPtr;
    bool isPara;
    bool isArray;
    int arraySize;
    bool isLeft;
    Var* initdata;/**< 初始化表达式的结果变量 */
    bool inited;
    union {
        int intVal;
        char charVal;
    };
    string strVal;
    string ptrVal;
    Var* ptr;/**< 当前变量的指针变量，即指向它的变量 */
    Var* pointTo;/**< 如果当前变量是指针变量，它所指向的变量 */
    int _size;
    int offset;/**< 栈帧偏移 */

    //------------------------------------------------method
    Var(vector<int> scopepath, bool ext, _TokenType _type, string name, bool isPtr, bool isArray, int arraySize, bool isLeft, Var* initdata, bool inited);
    Var(Token* token);
    Var(vector<int> scopepath, _TokenType _type, bool isPtr);
    Var(vector<int> scopepath, Var* val);
    Var();
    void _clear();
    bool isBase();
    void setType(_TokenType type);
    void setArray(int len);
    bool setInit();
    bool isVoid();
    static Var* getStep(Var* val);
    string getRawStr();
    static Var* getVoid();
    static Var* getTrue();
protected:

private:
};

#endif // VAR_H
