#include "Scanner.h"
#include<string>
using namespace std;

// ���ɨ��һ���ַ�
char Scanner::scan(FILE* filein)
{
    // ����ͷ��
    if (!filein) return -1;
    // 
    if (readPos == bufferLen - 1)
    {
        // �ɹ���д�Ŀ��� = fread(����buffer�У�ÿ�����ݿ���ֽ����������ٸ����ݿ飬�ļ�ָ��)
        bufferLen = fread(buffer, 1, BUFLEN, filein);
        if (bufferLen == 0)
        {
            bufferLen = 1;
            buffer[0] = -1;
        }
        readPos = -1;
    }
    readPos++; // �� readPos == 0
    char ch = buffer[readPos];
    lastch = ch;
    if (lastch == '\n')
    {
        lineNum++;
        lastCol = colNum + 1;
        colNum = 0;
    }
    if (ch == -1)
    {
        lastCol = colNum + 1;
        fclose(file);
        file = NULL;
    }
    else if (ch != '\n')
        colNum++;
    lastch = ch;
    return ch;
}

int Scanner::getCol()
{
    return this->colNum;
}
int Scanner::getLine()
{
    return this->lineNum;
}
