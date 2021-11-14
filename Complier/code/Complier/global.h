#pragma once
#ifndef GLOBA_H_INCLUDED
#define GLOBA_H_INCLUDED

#include "Lex.h"
#include "Scanner.h"
#include "SymTab.h"
#include "GenIR.h"
#include "InterInst.h"
#include<stdio.h>
#include<windows.h>
#include<string>
using namespace std;
class GenIR;
class Lex;
class SymTab;
enum TextColor {
    KEYWORDS,
    PARAMETER,
    EXPLANATION,
    NORMAL,
    ERRORCOLOR,
    WARNINGCOLOR
};
extern Lex* lex;
extern SymTab* symtab;
extern GenIR* ir;
extern InterInst* inst;
extern char* filename;/**< 源代码文件 */
extern char* targetFile;/**< 目标汇编代码文件 */
extern char* lexFile;/**< 词法分析中间结果存储文件 */
extern char* parseFile;/**< 语法分析树 存储文件 */
extern char* intercodeFile;/**< 中间代码 存储文件 */
extern int errorNum;
extern int warnNum;

extern FILE* file;/**< 目标汇编文件指针 */
extern FILE* source;/**< 源文件指针为检查文件是否存在 */
/**<  extern Fun* global;/**< 为存储全局变量 */
extern void highlight(char* text, TextColor _color);
extern char* trim(char* str);
extern bool startWith(char* source, char* start);
extern char* getRawFileName(char* externFile);
extern string getRawString(string str);
extern bool deleteWith(char*& source, char* start, int len);
extern void trimVetor(vector<int>& temp);
extern vector<int> IOflag;/**< 1 for putchar ;2 for puts ; 3 for printf;*/
//extern void _remove(char* source,char* start);
#endif // GLOBA_H_INCLUDED
