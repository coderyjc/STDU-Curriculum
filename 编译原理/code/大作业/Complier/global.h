#pragma once
#include<stdio.h>
#include<string>
#include<windows.h>

#include "Lex.h"


using namespace std;

class Lex;

extern Lex* lex;

// ���������
extern int errorNum;
// ���������
extern int warnNum;

/** Դ�����ļ� */
extern char* filename;

/**< Դ�ļ�ָ��Ϊ����ļ��Ƿ���� */
extern FILE* source;

/** �ʷ������м����洢�ļ� */
extern char* lexFile;

/**  Ŀ�����ļ�ָ�� */
extern FILE* file;


extern string getRawString(string str);
extern char* trim(char* str);
extern bool startWith(char* source, const char* start);
extern char* getRawFileName(char* externFile);
extern bool deleteWith(char*& source, const char* start, int len);