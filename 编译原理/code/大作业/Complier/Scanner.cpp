#include "Scanner.h"
#include<string>
using namespace std;

// 向后扫描一个字符
char Scanner::scan(FILE* filein)
{
    // 读到头了
    if (!filein) return -1;
    // 
    if (readPos == bufferLen - 1)
    {
        // 成功读写的块数 = fread(读到buffer中，每个数据块的字节数，读多少个数据块，文件指针)
        bufferLen = fread(buffer, 1, BUFLEN, filein);
        if (bufferLen == 0)
        {
            bufferLen = 1;
            buffer[0] = -1;
        }
        readPos = -1;
    }
    readPos++; // 令 readPos == 0
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
