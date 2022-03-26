#pragma once
#include"global.h"

#include<iostream>
using namespace std;

enum LexError
{
    STR_NO_R_QUTION,
    NUM_BIN_TYPE,
    NUM_HEX_TYPE,
    CHAR_NO_R_QUTION,
    CHAR_NO_DATA,
    OR_NO_PAIR,
    COMMMENT_NO_END,
    TOKEN_NO_EXIST
};
enum SynError {
    TYPE_LOST, TYPE_WRONG,
    ID_LOST, ID_WRONG,
    NUM_LOST, NUM_WRONG,
    LITERAL_LOST, LITERAL_WRONG,
    COMMMA_LOST, COMMMA_WRONG,
    SEMICON_LOST, SEMICON_WRONG,
    ASSIGN_LOST, ASSIGN_WRONG,
    COLON_LOST, COLON_WRONG,
    WHILE_LOST, WHILE_WRONG,
    LPAREN_LOST, LPAREN_WRONG,
    RPAREN_LOST, RPAREN_WRONG,
    LBRACK_LOST, LBRACK_WRONG,
    RBRACK_LOST, RBRACK_WRONG,
    LBRACE_LOST, LBRACE_WRONG,
    RBRACE_LOST, RBRACE_WRONG
};

enum SemError {
    VAR_RE_DEF,
    FUN_RE_DEF,
    VAR_UN_DEC,
    FUN_UN_DEC,
    FUN_DEC_ERR,
    FUN_CALL_ERR,
    DEC_INIT_DENY,
    EXTERN_FUN_DEF,
    ARRAY_LEN_INVALID,
    VAR_INIT_ERR,
    GLB_INIT_ERR,
    VOID_VAR,
    EXPR_NOT_LEFT_VAL,
    ASSIGN_TYPE_ERR,
    EXPR_IS_BASE,
    EXPR_NOT_BASE,
    ARR_TYPE_ERR,
    EXPR_IS_VOID,
    BREAK_ERR,
    CONTINUE_ERR,
    RETURN_ERR
};

enum SemWarn {
    FUN_DEC_CONFLICT,
    FUN_RET_CONFLICT,
    PTR_SEG_FAULT
};
class Error
{
public:
    static void LexError(int code)
    {
        static const char* lexErrorTable[] =
        {
            "字符串丢失右向导",
            "二进制数没有实体数据",
            "十六进制数据没有实体数据",
            "字符丢失右单引号",
            "不支持空字符",
            "错误的'|'运算符",
            "多行注释没有正常结束",
            "词法记号不存在"
        };
        errorNum++;
        cerr << lex->getFileName(true) << " <" << lex->getLineNum() << "行," << lex->getColNum() << "列> 词法错误:" << lexErrorTable[code] << ".\n";
    }
    static void SynError(int code, Token* t)
    {
        static const char* synErrorTable[] =
        {
            "类型",
            "标识符",
            "数组长度",
            "常量",
            "逗号",
            "分号",
            "=",
            "冒号",
            "while",
            "(",
            ")",
            "[",
            "]",
            "{",
            "}"
        };
        errorNum++;
        if (code % 2 == 0) {
            cerr << lex->getFileName(true) << " <" << lex->getLineNum() << "行> 语法错误: 在 ";
            cerr << t->toString() << " 之前丢失" << synErrorTable[code / 2] << endl;
        }

        else cerr << lex->getFileName(true) << " <" << lex->getLineNum() << "行> 语法错误: 在 " << t->toString() << " 处没有正确匹配" << synErrorTable[code / 2] << endl;
    }
    static void SemError(int code, string name)
    {
        static const char* SemErrorTable[] = {
            "变量重定义",
            "函数重定义",
            "变量未声明",
            "函数未声明",
            "函数声明与定义不匹配",
            "函数形参与实参不匹配",
            "变量声明时不允许初始化",
            "函数定义不能使用保留字extern",
            "数组长度应该是正整数",
            "变量初始化类型错误",
            "全局变量初始化不是常量",
            "变量不能声明为void类型",
            "无效的左值表达式",
            "赋值表达式不兼容",
            "表达式操作数不能是基本类型",
            "表达式操作数不是基本类型",
            "数组索引运算类型错误",
            "void的函数返回值不能参与表达式运算",
            "break语句不能出现在循环或switch语句之外",
            "continue语句不能出现在循环之外",
            "return语句和函数返回值类型不匹配"
        };
        errorNum++;
        cerr << lex->getFileName(true) << " <" << lex->getLineNum() << "行> 语义错误: " << name << " " << SemErrorTable[code] << endl;
    }
    static void SemWarn(int code, string name)
    {
        static const char* SemWarnTable[] = {
            "函数参数列表类型冲突",
            "函数返回值类型不精确匹配",
            "极有可能发生Segmentation Fault"
        };
        warnNum++;
        cout << lex->getFileName(true) << " <" << lex->getLineNum() << "行> 语义警告: " << name << " " << SemWarnTable[code] << endl;
    }
};
#define LEXERROR Error::LexError
#define SYNERROR Error::SynError
#define SEMERROR Error::SemError
#define SEMWARN Error::SemWarn