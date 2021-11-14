#pragma once
#ifndef INTERINST_H
#define INTERINST_H
#include"Operator.h"
#include"Fun.h"
#include<string>
#include"Var.h"
#include<stdio.h>
#include<stdlib.h>
using namespace std;
#define emit(fmt,args...) fprintf(file,"\t" fmt "\n",##args)
class Fun;
class Var;
class InterInst
{
public:
    string label;//Instruction or label
    Operator op;
    Var* result;
    Var* arg1;
    Var* arg2;
    Fun* fun;
    InterInst* target;
    InterInst(Operator op, Var* result, Var* arg1, Var* arg2, Fun* fun, InterInst* target);
    InterInst(Operator op, InterInst* target, Var* result);
    InterInst(Operator op, Fun* func);
    InterInst(Operator op, Var* arg);
    InterInst(Operator op, Fun* func, Var* result);
    InterInst(Operator op, Var* result, Var* arg1, Var* arg2);
    InterInst(Operator op, Var* result, Var* arg1);
    InterInst(Operator op, InterInst* target);
    InterInst(Operator op, InterInst* target, Var* arg1, Var* arg2);
    InterInst();
    void _clear();
    void loadVar(string reg32, string reg8, Var* var);
    void leaVar(string reg32, Var* var);
    void storeVar(string reg32, string reg8, Var* var);
    void initVar(Var* var);
    void toX86();

protected:

private:
};

#endif // INTERINST_H
