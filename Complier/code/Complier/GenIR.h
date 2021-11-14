#pragma once
#ifndef GENIR_H
#define GENIR_H
#include"Var.h"
#include"Fun.h"
#include"SymTab.h"
#include"InterInst.h"
#include"global.h"
class SymTab;
class Var;
class Fun;
class InterInst;
class GenIR
{
public:
    GenIR();
    static bool typeCheck(Var* lval, Var* rval);
    void genFunHead(Fun* func);
    void genFunTail(Fun* func);
    bool genVarInit(Var* var);
    Var* genTwoOp(Var* lval, _TokenType opt, Var* rval);
    Var* genOneOpLeft(_TokenType type, Var* val);
    Var* genOneOpRight(Var* val, _TokenType opt);
    Var* genArray(Var* arr, Var* index);
    void genPara(Var* arg);
    Var* genCall(Fun* fun, vector<Var*>& args);
    Var* genIncR(Var* val);
    Var* genDecR(Var* val);
    void genReturn(Var* ret);
    Var* genAdd(Var* lval, Var* rval);
    Var* genAdd(Var* result, Var* lval, Var* rval);
    Var* genPtr(Var* val);
    Var* genAssign(Var* lval, Var* rval);
    Var* genAssign(Var* val);
    Var* genOr(Var* lval, Var* rval);
    Var* genAnd(Var* lval, Var* rval);
    Var* genEqu(Var* lval, Var* rval);
    Var* genNequ(Var* lval, Var* rval);
    Var* genSub(Var* lval, Var* rval);
    Var* genSub(Var* result, Var* lval, Var* rval);
    Var* genGt(Var* lval, Var* rval);
    Var* genGe(Var* lval, Var* rval);
    Var* genLt(Var* lval, Var* rval);
    Var* genLe(Var* lval, Var* rval);
    Var* genMul(Var* lval, Var* rval);
    Var* genMul(Var* result, Var* lval, Var* rval);
    Var* genDiv(Var* lval, Var* rval);
    Var* genDiv(Var* result, Var* lval, Var* rval);
    Var* genMod(Var* lval, Var* rval);
    Var* genLea(Var* val);
    Var* genIncL(Var* val);
    Var* genDecL(Var* val);
    Var* genNot(Var* val);
    Var* genMinus(Var* val);
    static string genLb();
    vector<InterInst*> heads;
    vector<InterInst*> tails;
    void push(InterInst* head, InterInst* tail);
    void pop();
    void genIFHead(Var* cond, InterInst*& _else);
    void genElseHead(InterInst* _else, InterInst*& _exit);
    void genElseTail(InterInst*& _exit);
    void genIFTail(InterInst*& _else);
    void genSwitchHead(InterInst*& _exit);
    void genSwitchTail(InterInst* _exit);
    void genCaseHead(Var* cond, Var* lb, InterInst*& _case_exit);
    void genCaseTail(InterInst* _case_exit);
    void genWhileHead(InterInst*& _while, InterInst*& _exit);
    void genWhileCond(Var* cond, InterInst* _exit);
    void genWhileTail(InterInst*& _while, InterInst*& _exit);
    void genDoWhileHead(InterInst*& _do, InterInst*& _exit);
    void genDoWhileTail(Var* cond, InterInst* _do, InterInst* _exit);
    void genForHead(InterInst*& _for, InterInst*& _exit);
    void genForCondBegin(Var* cond, InterInst*& step, InterInst*& _block, InterInst* _exit);
    void genForCondEnd(InterInst* _for, InterInst* _block);
    void genForTail(InterInst*& _step, InterInst*& _exit);
    void genBreak();
    void genContinue();
    void genPrintf(Var* val);
    void genWrite(Var* val, Var* vd);
    void genRead(Var* val, Var* vd);
protected:

private:
};

#endif // GENIR_H
