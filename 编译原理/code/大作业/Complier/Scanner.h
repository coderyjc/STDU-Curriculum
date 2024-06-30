#pragma once
#include<stdio.h>
#include<string>
#include"global.h"

#define BUFLEN 200

using namespace std;
class Scanner
{
public:
    // 成功读写的块数
    int bufferLen = 0;



    int readPos = -1;

    // 缓冲，字符暂存到这里面
    char buffer[BUFLEN];

    // 当前所在是第几行
    int lineNum = 1;

    // 当前所在是第几列
    int colNum = 0;

    // 
    int lastCol = 0;

    // 上一个字符
    char lastch;

    //======函数======

    // 向后扫描一个字符
    char scan(FILE* file);

    // 获取当前是第几行
    int getLine();

    // 获取当前是第几列
    int getCol();

protected:

private:
};
