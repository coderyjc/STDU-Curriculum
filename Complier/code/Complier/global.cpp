#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<vector>
#include "global.h"
using namespace std;

Lex* lex;
SymTab* symtab = new SymTab();
GenIR* ir = new GenIR();
//InterInst *inst = new InterInst();
char* filename;/**< 源代码文件 */
char* targetFile;/**< 目标汇编代码文件 */
char* lexFile;/**< 词法分析中间结果存储文件 */
char* parseFile;/**< 语法分析树 存储文件 */
char* intercodeFile;/**< 中间代码 存储文件 */
FILE* file;/**< 目标汇编代码文件指针 */
FILE* source;/**< 源文件指针为检查文件是否存在 */
int errorNum = 0;
vector<int> IOflag;
int warnNum = 0;
void highlight(char* text, TextColor _color)
{
    if (_color == KEYWORDS) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x02);
        printf("%s", text);
    }
    else if (_color == PARAMETER) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x08);
        printf("%s", text);
    }
    else if (_color == EXPLANATION) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0d);
        printf("%s", text);
    }
    else if (_color == NORMAL) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0f);
        printf("%s", text);
    }
    else if (_color == ERRORCOLOR)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0c);
        printf("%s", text);
    }
    else if (_color == WARNINGCOLOR)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x03);
        printf("%s", text);
    }
}
char* trim(char* str)
{
    if (str == NULL || *str == '\0')
        return str;
    int rlen = strlen(str);
    char* rp = str + rlen - 1;
    while (rp >= str && isspace(*rp))
    {
        *rp = '\0';
        --rp;
    }
    int llen = 0;
    char* lp = str;
    while (*lp != '\0' && isspace(*lp))
    {
        ++lp;
        ++llen;
    }
    memmove(str, lp, strlen(str) - llen + 1);
    return str;
}
bool startWith(char* source, char* start)
{
    int len = strlen(start);
    for (int i = 0; i < len; i++)
    {
        if (source[i] == start[i]) continue;
        else return false;
    }
    return true;
}
bool deleteWith(char*& source, char* start, int len)
{
    int counter = 0;
    for (int i = 0; i < len; i++)
    {
        if (source[i] == start[i]) { counter++; continue; }
        else return false;
    }
    for (int i = 0; i < counter; i++)
        source++;
    return true;
}
char* getRawFileName(char* str)
{
    if (str == NULL || *str == '\0')
        return str;
    int rlen = strlen(str);
    char* rp = str + rlen - 1;
    while (rp >= str && (*rp) != '.')
    {
        *rp = '\0';
        --rp;
    }
    *rp = '\0';
    return str;
}
string getRawString(string str)
{
    int len = str.length();
    string temp = "";
    for (int i = 0; i < len; i++)
    {
        if (str[i] == '\n') temp += "\\n";
        else if (str[i] == '\t') temp += "\\t";
        else if (str[i] == '\0') temp += "\\0";
        else if (str[i] == '\"') temp += "\\\"";
        else if (str[i] == '\'') temp += "\\'";
        else if (str[i] == '\a') temp += "\\a";
        else if (str[i] == '\b') temp += "\\b";
        else if (str[i] == '\v') temp += "\\v";
        //else if(str[i]=='\?') temp+="\\?";
        else temp += str[i];
    }
    return temp;
}

void trimVetor(vector<int>& temp)
{

}


