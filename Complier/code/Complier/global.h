#pragma once
#include<stdio.h>
#include<string>
#include<windows.h>

#include "Lex.h"


using namespace std;

class Lex;

extern Lex* lex;

// 错误的数量
extern int errorNum;
// 警告的数量
extern int warnNum;

/** 源代码文件 */
extern char* filename;

/**< 源文件指针为检查文件是否存在 */
extern FILE* source;

/** 词法分析中间结果存储文件 */
extern char* lexFile;

/**  目标汇编文件指针 */
extern FILE* file;


extern string getRawString(string str);
extern char* trim(char* str);
extern bool startWith(char* source, const char* start);
extern char* getRawFileName(char* externFile);
extern bool deleteWith(char*& source, const char* start, int len);