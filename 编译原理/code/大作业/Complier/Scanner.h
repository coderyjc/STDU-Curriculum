#pragma once
#include<stdio.h>
#include<string>
#include"global.h"

#define BUFLEN 200

using namespace std;
class Scanner
{
public:
    // �ɹ���д�Ŀ���
    int bufferLen = 0;



    int readPos = -1;

    // ���壬�ַ��ݴ浽������
    char buffer[BUFLEN];

    // ��ǰ�����ǵڼ���
    int lineNum = 1;

    // ��ǰ�����ǵڼ���
    int colNum = 0;

    // 
    int lastCol = 0;

    // ��һ���ַ�
    char lastch;

    //======����======

    // ���ɨ��һ���ַ�
    char scan(FILE* file);

    // ��ȡ��ǰ�ǵڼ���
    int getLine();

    // ��ȡ��ǰ�ǵڼ���
    int getCol();

protected:

private:
};
