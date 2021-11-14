#pragma once
#ifndef LEX_H
#define LEX_H
#include"Token.h"
#include"Scanner.h"
#include<string>
#include<windows.h>
#include<tchar.h>
#include"global.h"
#include<vector>

using namespace std;
class LexData {
public:
    Token* token;
    int row;
    int col;
    LexData(Token* token, int row, int col)
    {
        this->token = token;
        this->row = row;
        this->col = col;
    }

};
class Scanner;
class Lex
{
public:
    int number = 1;//for show index number
    Scanner* scanner;
    FILE* fp;
    int charLen = 0;
    char ch = 0;
    /**< method */
    Lex();
    Lex(char* file);
    bool scan(char need = 0);
    int getColNum();
    int getLineNum();
    char* getFileName(bool outOpt = false);

    Token* tokenize();
    void LexShow(Token* token, bool outOpt = 0);
    void LexShow(bool outOpt = 0);
    void analysis();
    void LexShowData(Token* token, int row, int col, bool outOption);
    vector<LexData*> result;
};

#endif // LEX_H
