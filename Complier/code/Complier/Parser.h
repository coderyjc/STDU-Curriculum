#pragma once
#ifndef PARSER_H
#define PARSER_H
#include"global.h"
#include"Error.h"
#include"SymTab.h"

#define _(T) ||look->type==T
#define F(C) look->type==C

//#define FUN_PRINT(times,fmt,...) for(int i=0;i<times-1;i++)cout<<" ";cout<<"|_";printf("<%s>:"fmt"\n", __FUNCTION__, ##__VA_ARGS__)

class DrawTreeData {
public:
    vector<int> drawCol;
    int depth;
    char* funName;
    DrawTreeData(vector<int> drawCol, int depth, char* funName)
    {
        this->drawCol = drawCol;
        this->depth = depth;
        this->funName = funName;
    }
};
class SymTab;
class Parser
{
public:
    int depth = 0;
    Token* pre = NULL;
    vector<int> drawCol;
    vector<DrawTreeData*> data;
    Parser(char* filename);
    Token* look = NULL;
    void whilestat();
    bool match(_TokenType need);
    void mov();
    void recovery(bool cond, SynError lost, SynError wrong);
    Var* altexpr();
    void block();
    void statement();
    void dowhilestat();
    void ifstat();
    void switchstat();
    void forstat();
    void program();
    void analyze();
    void segment();
    _TokenType type();
    void deflist(bool ext, _TokenType type);
    void fun();
    void def(bool ext, _TokenType type);
    void idtail(bool ext, _TokenType type, bool ptr, string name);
    void funtail(Fun* fun);
    Var* paradata(_TokenType type);
    Var* paradatatail(_TokenType type, string name);
    void paralist(vector<Var*>& result);
    void para(vector<Var*>& paraList);
    void subprogram();
    void localdef(bool ext, _TokenType type);
    Var* assexpr();
    _TokenType ass();
    Var* asstail(Var*& a);
    Var* orexpr();
    Var* ortail(Var*& a);
    Var* andexpr();
    Var* andtail(Var*& a);
    Var* cmpexpr();
    Var* cmptail(Var*& a);
    _TokenType cmps();
    Var* aloexpr();
    Var* alotail(Var*& a);
    _TokenType adds();
    Var* item();
    Var* itemtail(Var*& a);
    _TokenType muls();
    Var* factor();
    _TokenType lop();
    Var* val();
    _TokenType rop();
    Var* elem();
    Var* idexpr(string name);
    vector<Var*> realarg();
    void arglist(vector<Var*>& var);
    Var* arg();
    Var* literal();
    void forinit();
    void elsestat();
    void casestat(Var* cond);
    Var* caselabel();
    Var* varrdef(bool ext, _TokenType type, bool ptr, string name);
    Var* init(bool ext, _TokenType type, bool ptr, string name);
    Var* expr();
    Var* defdata(bool ext, _TokenType type);
    void printfstat();/**< printf */
    void writestat();/**< 输出单个变量 */
    void readstat();/**< 输入单个变量 */
    void DrawTree(bool outOpt = 0);
protected:

private:
};

#endif // PARSER_H
