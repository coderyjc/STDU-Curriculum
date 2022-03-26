#include<string>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<vector>

#include "global.h"
using namespace std;

Lex* lex;

char* filename;/**< 源代码文件 */
char* targetFile;/**< 目标汇编代码文件 */

char* lexFile;/**< 词法分析中间结果存储文件 */
char* parseFile;/**< 语法分析树 存储文件 */
char* intercodeFile;/**< 中间代码 存储文件 */

FILE* file;/**< 目标汇编代码文件指针 */
FILE* source;/**< 源文件指针为检查文件是否存在 */

int errorNum = 0;
int warnNum = 0;

vector<int> IOflag;

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

bool startWith(char* source, const char* start)
{
    int len = strlen(start);
    for (int i = 0; i < len; i++)
    {
        if (source[i] == start[i]) continue;
        else return false;
    }
    return true;
}

bool deleteWith(char*& source, const char* start, int len)
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