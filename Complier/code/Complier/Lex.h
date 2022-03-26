#pragma once
#include<string>
#include<windows.h>
#include<tchar.h>
#include<vector>

#include"Token.h"
#include"Scanner.h"
#include"global.h"

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
    Scanner* scanner;  // 扫描器，每一次向后扫描一个字符
    FILE* fp; // 文件指针
    int charLen = 0; // 
    char ch = 0; // 当前扫描到的字符

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

    // ===词法分析的结果===
    vector<LexData*> result;
};
