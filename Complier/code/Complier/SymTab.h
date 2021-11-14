#pragma once
#ifndef SYMTAB_H
#define SYMTAB_H

#include<unordered_map>
#include<string>
#include"Var.h"
#include"Fun.h"
#include"Lex.h"
#include"GenIR.h"
#include"global.h"
#include"InterInst.h"
using namespace __gnu_cxx;

//class GenIR;
class SymTab
{
public:
    struct str_hash
    {
        size_t operator()(const string& str) const
        {
            return __stl_hash_string(str.c_str());
        }
    };
    unordered_map<string, vector<Var*>*, str_hash> varTab;//var table
    unordered_map<string, Var*, str_hash> strTab;
    unordered_map<string, Fun*, str_hash> funTab;
    Fun* curFun;
    int scopeId;
    vector<int> scopePath;
    int counter;
    SymTab();
    void enter();
    void leave();
    vector<int> getScopePath();
    void addVar(Var* var);
    void addStr(Var*& v);
    Var* getVar(string name);
    Var* getVar(string name, vector<int> scppth);
    void decFun(Fun* fun);
    void defFun(Fun* fun);
    void define(Fun* def);
    void endDefFun();
    void addInst(InterInst* newInst);
    Fun* getFun(string name, vector<Var*>& args);
    vector<Var*> getGlbVars();
    int genData();
    void genAsm();

    void ShowVarTab();
    void ShowIR(bool outOpt = 0);
    void ShowFunTab();
protected:

private:
};

#endif // SYMTAB_H
