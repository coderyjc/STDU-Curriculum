#include "GenIR.h"
#include<sstream>
#include"Error.h"
using namespace std;

GenIR::GenIR()
{
    push(NULL, NULL);
}
bool GenIR::typeCheck(Var* lval, Var* rval)
{
    bool flag = false;
    if (!rval) return false;
    if (lval->isBase() && rval->isBase()) flag = true;
    else if (!lval->isBase() && !rval->isBase()) flag = (rval->type == lval->type);
    return flag;
}

void GenIR::genFunHead(Fun* func)
{
    func->enterScope();
    symtab->addInst(new InterInst(OP_ENTRY, func));
    func->returnPoint = new InterInst;
}
void GenIR::genFunTail(Fun* func)
{
    symtab->addInst(func->returnPoint);
    symtab->addInst(new InterInst(OP_EXIT, func));
    func->leaveScope();
}

string GenIR::genLb()
{
    static int lbNum = 0;
    lbNum++;
    string lb = "L";
    stringstream ss;
    ss << lbNum;
    string temp = ss.str();
    //int debug;
    //cin>>debug;
    return lb + temp;
}
bool GenIR::genVarInit(Var* var)
{
    if (var->name[0] == '<') return false;
    symtab->addInst(new InterInst(OP_DEC, var));
    if (var->setInit())
    {
        genTwoOp(var, ASSIGN, var->initdata);
    }
    return true;
}
Var* GenIR::genTwoOp(Var* lval, _TokenType opt, Var* rval)
{
    if (!lval || !rval) return NULL;
    if (lval->isVoid() || rval->isVoid()) {
        if (lval->isVoid()) SEMERROR(EXPR_IS_VOID, lval->name);
        else if (rval->isVoid()) SEMERROR(EXPR_IS_VOID, rval->name);
        return NULL;
    }
    if (opt == ASSIGN) return genAssign(lval, rval);
    if (lval->isPtr) lval = genAssign(lval);
    if (rval->isPtr) rval = genAssign(rval);
    if (opt == LOGICAL_OR) return genOr(lval, rval);
    if (opt == LOGICAL_AND) return genAnd(lval, rval);
    if (opt == EQU) return genEqu(lval, rval);
    if (opt == NEQU) return genNequ(lval, rval);
    if (opt == PLUS) return genAdd(lval, rval);
    if (opt == MINUS) return genSub(lval, rval);
    if (!lval->isBase() || !rval->isBase()) {
        if (!lval->isBase()) SEMERROR(EXPR_NOT_BASE, lval->name);
        else if (!rval->isBase()) SEMERROR(EXPR_NOT_BASE, rval->name);
        return lval;
    }
    if (opt == GT) return genGt(lval, rval);
    if (opt == GE) return genGe(lval, rval);
    if (opt == LT) return genLt(lval, rval);
    if (opt == LE) return genLe(lval, rval);
    if (opt == TIMES) return genMul(lval, rval);
    if (opt == DIV) return genDiv(lval, rval);
    if (opt == MOD) return genMod(lval, rval);
    return lval;

}
Var* GenIR::genOneOpLeft(_TokenType opt, Var* val)
{
    if (!val) return NULL;
    if (val->isVoid()) {
        SEMERROR(EXPR_IS_VOID, val->name);
        return NULL;
    }
    if (opt == BIT_AND) return genLea(val);
    if (opt == TIMES) return genPtr(val);
    if (opt == INC) return genIncL(val);
    if (opt == DEC) return genDecL(val);
    if (val->isPtr) val = genAssign(val);
    if (opt == BIT_NOT) return genNot(val);
    if (opt == MINUS) return genMinus(val);
    return val;
}
Var* GenIR::genOneOpRight(Var* val, _TokenType opt)
{
    if (!val) return NULL;
    if (val->isVoid())
    {
        SEMERROR(EXPR_IS_VOID, val->name);
        return NULL;
    }
    if (!val->isLeft)
    {
        SEMERROR(EXPR_NOT_LEFT_VAL, val->name);
        return val;
    }
    if (opt == INC) return genIncR(val);
    if (opt == DEC) return genDecR(val);
    return val;
}
Var* GenIR::genArray(Var* arr, Var* index)
{
    if (!arr || !index) return NULL;
    if (arr->isVoid() || index->isVoid()) {
        SEMERROR(EXPR_IS_VOID, arr->name);
        return NULL;
    }
    if (arr->isBase() || !index->isBase()) {
        SEMERROR(ARR_TYPE_ERR, arr->name);
        return index;
    }
    Var* temp = new Var(arr->scopepath, arr);/**< 这个中间变量不需要存储*/
    temp->offset += index->intVal * Var::getStep(arr)->intVal;
    temp->isLeft = true;
    temp->isArray = false;
    temp->_size = arr->type == _INT ? 4 : 1;
    return temp;
}
void GenIR::genPara(Var* arg)
{
    //if(arg->isPtr) arg =genAssign(arg);
    InterInst* argInst = new InterInst(OP_ARG, arg);
    symtab->addInst(argInst);
}
Var* GenIR::genCall(Fun* func, vector<Var*>& args)
{
    if (!func) return NULL;
    //cout<<args.size()<<endl;
    for (int i = 0; i < args.size(); i++)
    {
        genPara(args[i]);
    }
    if (func->type == _VOID) {
        symtab->addInst(new InterInst(OP_PROC, func));
        return Var::getVoid();//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
    }
    else {
        Var* ret = new Var(symtab->getScopePath(), func->type, false);
        symtab->addVar(ret);
        symtab->addInst((new InterInst(OP_CALL, func, ret)));
        return ret;
    }
}
Var* GenIR::genIncR(Var* val)
{
    Var* temp = genAssign(val);
    if (val->isPtr) {
        Var* t2 = genAdd(temp, Var::getStep(val));
        genAssign(val, t2);
    }
    else symtab->addInst(new InterInst(OP_ADD, val, val, Var::getStep(val)));
    return temp;
}
Var* GenIR::genDecR(Var* val)
{
    Var* temp = genAssign(val);
    if (val->isPtr) {
        Var* t2 = genSub(temp, Var::getStep(val));
        genAssign(val, t2);
    }
    else symtab->addInst(new InterInst(OP_SUB, val, val, Var::getStep(val)));
    return temp;
}
void GenIR::genReturn(Var* ret)
{
    if (!ret) return;
    Fun* fun = symtab->curFun;
    if (ret->isVoid() && fun->type != _VOID ||
        ret->isBase() && fun->type == _VOID) {
        SEMERROR(RETURN_ERR, ret->name);
        return;
    }
    InterInst* returnPoint = fun->returnPoint;
    if (ret->isVoid())
        symtab->addInst(new InterInst(OP_RET, returnPoint, NULL));
    else {
        if (ret->isPtr) ret = genAssign(ret);
        symtab->addInst(new InterInst(OP_RETV, returnPoint, ret));
    }
}

Var* GenIR::genPtr(Var* val)/**< 不能使用中间量传递！！！！ */
{
    if (val->isBase()) {
        SEMERROR(EXPR_IS_BASE, val->name);
        return val;
    }
    //    Var *temp = new Var(symtab->getScopePath(),val->type,false);
    //    temp->isLeft =true;
    //    temp->ptr =val;
    //    symtab->addVar(temp);
    //    return temp;
    if (val->pointTo == NULL && !val->isPara)
    {
        SEMWARN(PTR_SEG_FAULT, val->name);
        Var* temp = new Var(val->scopepath, val->type, false);
        val->pointTo = temp;
        temp->ptr = val;
        val->pointTo->isLeft = true;
        symtab->addVar(val->pointTo);
        InterInst* temp2 = new InterInst(OP_GET, val->pointTo, val);/**< 在汇编时需要判断 */
        symtab->addInst(temp2);
        return val->pointTo;
    }
    else if (val->pointTo == NULL && val->isPara)
    {
        Var* temp = new Var(val->scopepath, val);
        temp->isPara = true;/**< 只使用 offset 不需要添加到varTab */
        temp->isLeft = true;
        return temp;
    }
    else if (val->pointTo != NULL) {//不要中间代码
        return val->pointTo;
    }
}

Var* GenIR::genAssign(Var* lval, Var* rval)
{
    if (!lval->isLeft) {
        SEMERROR(EXPR_NOT_LEFT_VAL, lval->name);
        return rval;
    }
    if (!typeCheck(lval, rval)) {
        SEMERROR(ASSIGN_TYPE_ERR, lval->name);
        return rval;
    }
    //if(rval->isPtr) rval =genAssign(rval);
    //if(lval->isPtr) symtab->addInst(new InterInst(OP_SET,rval,lval->ptr));
    //else symtab->addInst(new InterInst(OP_AS,lval,rval));
    if (!lval->isPara && rval->isPara) {
        symtab->addInst(new InterInst(OP_GET, lval, rval));
    }
    else if (lval->isPara && !rval->isPara) {
        symtab->addInst(new InterInst(OP_SET, lval, rval));
    }
    else if (lval->isPara && rval->isPara) {
        symtab->addInst(new InterInst(OP_ASP, lval, rval));
    }
    else  symtab->addInst(new InterInst(OP_AS, lval, rval));
    return lval;
}
Var* GenIR::genAssign(Var* val)/**< 好像没什么必要 */
{
    Var* temp = new Var(symtab->getScopePath(), val);
    symtab->addVar(temp);
    if (val->isPtr) symtab->addInst(new InterInst(OP_GET, temp, val->ptr));
    else symtab->addInst(new InterInst(OP_AS, temp, val));
    return temp;
}
Var* GenIR::genLea(Var* val)
{
    if (!val->isLeft) {
        SEMERROR(EXPR_NOT_LEFT_VAL, val->name);
        return val;
    }
    if (val->ptr != NULL)/**<如果当前变量的指针变量不为空，即当前的地址，返回变量  */
        return val->ptr;
    else {
        Var* temp = new Var(symtab->getScopePath(), val->type, true);
        temp->isLeft = true;
        temp->pointTo = val;
        val->ptr = temp;
        symtab->addVar(temp);
        symtab->addInst(new InterInst(OP_LEA, temp, val));
        return temp;
    }
}
Var* GenIR::genOr(Var* lval, Var* rval)
{
    Var* temp = new Var(symtab->getScopePath(), _INT, false);
    symtab->addVar(temp);
    symtab->addInst(new InterInst(OP_OR, temp, lval, rval));
    return temp;
}
Var* GenIR::genAnd(Var* lval, Var* rval)
{
    Var* temp = new Var(symtab->getScopePath(), _INT, false);
    symtab->addVar(temp);
    symtab->addInst(new InterInst(OP_AND, temp, lval, rval));
    return temp;
}
Var* GenIR::genEqu(Var* lval, Var* rval)
{
    Var* temp = new Var(symtab->getScopePath(), _INT, false);
    symtab->addVar(temp);
    symtab->addInst(new InterInst(OP_EQU, temp, lval, rval));
    return temp;
}
Var* GenIR::genNequ(Var* lval, Var* rval)
{
    Var* temp = new Var(symtab->getScopePath(), _INT, false);
    symtab->addVar(temp);
    symtab->addInst(new InterInst(OP_NE, temp, lval, rval));
    return temp;
}
Var* GenIR::genAdd(Var* lval, Var* rval)
{
    Var* temp = NULL;
    if (!lval->isBase() && rval->isBase()) {
        temp = new Var(symtab->getScopePath(), lval);
        rval = genMul(rval, Var::getStep(lval));
    }
    else if (lval->isBase() && !rval->isBase()) {
        temp = new Var(symtab->getScopePath(), rval);
        lval = genMul(lval, Var::getStep(rval));
    }
    else if (lval->isBase() && rval->isBase()) {
        temp = new Var(symtab->getScopePath(), _INT, false);
    }
    else {
        if (!lval->isBase())SEMERROR(EXPR_NOT_BASE, lval->name);
        else if (!rval->isBase()) SEMERROR(EXPR_NOT_BASE, rval->name);
        return lval;
    }
    symtab->addVar(temp);
    symtab->addInst(new InterInst(OP_ADD, temp, lval, rval));
    return temp;
}
Var* GenIR::genSub(Var* lval, Var* rval)
{
    Var* temp = NULL;
    if (!rval->isBase()) {
        SEMERROR(EXPR_NOT_BASE, rval->name);
        return lval;
    }
    if (!lval->isBase()) {
        temp = new Var(symtab->getScopePath(), lval);
        rval = genMul(rval, Var::getStep(lval));
    }
    else temp = new Var(symtab->getScopePath(), _INT, false);
    symtab->addVar(temp);
    symtab->addInst(new InterInst(OP_SUB, temp, lval, rval));
    return temp;
}
Var* GenIR::genGt(Var* lval, Var* rval)
{
    Var* temp = new Var(symtab->getScopePath(), _INT, false);
    symtab->addVar(temp);
    symtab->addInst(new InterInst(OP_GT, temp, lval, rval));
    return temp;
}
Var* GenIR::genGe(Var* lval, Var* rval)
{
    Var* temp = new Var(symtab->getScopePath(), _INT, false);
    symtab->addVar(temp);
    symtab->addInst(new InterInst(OP_GE, temp, lval, rval));
    return temp;
}
Var* GenIR::genLt(Var* lval, Var* rval)
{
    Var* temp = new Var(symtab->getScopePath(), _INT, false);
    symtab->addVar(temp);
    symtab->addInst(new InterInst(OP_LT, temp, lval, rval));
    return temp;
}
Var* GenIR::genLe(Var* lval, Var* rval)
{
    Var* temp = new Var(symtab->getScopePath(), _INT, false);
    symtab->addVar(temp);
    symtab->addInst(new InterInst(OP_LE, temp, lval, rval));
    return temp;
}
Var* GenIR::genMul(Var* lval, Var* rval)
{
    Var* temp = new Var(symtab->getScopePath(), _INT, false);
    symtab->addVar(temp);
    symtab->addInst(new InterInst(OP_MUL, temp, lval, rval));
    return temp;
}
Var* GenIR::genDiv(Var* lval, Var* rval)
{
    Var* temp = new Var(symtab->getScopePath(), _INT, false);
    symtab->addVar(temp);
    symtab->addInst(new InterInst(OP_DIV, temp, lval, rval));
    return temp;
}
Var* GenIR::genMod(Var* lval, Var* rval)
{
    Var* temp = new Var(symtab->getScopePath(), _INT, false);
    symtab->addVar(temp);
    symtab->addInst(new InterInst(OP_MOD, temp, lval, rval));
    return temp;
}
Var* GenIR::genIncL(Var* val)
{
    if (!val->isLeft) {
        SEMERROR(EXPR_NOT_LEFT_VAL, val->name);
        return val;
    }
    if (val->isPtr) {
        Var* t1 = genAssign(val);
        Var* t2 = genAdd(t1, Var::getStep(val));
        genAssign(val, t2);
    }
    else symtab->addInst(new InterInst(OP_ADD, val, val, Var::getStep(val)));
    return val;
}
Var* GenIR::genDecL(Var* val)
{
    if (!val->isLeft) {
        SEMERROR(EXPR_NOT_LEFT_VAL, val->name);
        return val;
    }
    if (val->isPtr) {
        Var* t1 = genAssign(val);
        Var* t2 = genSub(t1, Var::getStep(val));
        genAssign(val, t2);
    }
    else symtab->addInst(new InterInst(OP_SUB, val, val, Var::getStep(val)));
    return val;
}
Var* GenIR::genNot(Var* val)
/**< 需要判断是否是基本类型吗？？？？？？？？？？？？ */
{
    Var* temp = new Var(symtab->getScopePath(), _INT, false);
    symtab->addVar(temp);
    symtab->addInst(new InterInst(OP_NOT, temp, val));
    return temp;
}
Var* GenIR::genMinus(Var* val)
{
    if (!val->isBase()) {
        SEMERROR(EXPR_NOT_BASE, val->name);
        return val;
    }
    Var* temp = new Var(symtab->getScopePath(), _INT, false);
    symtab->addVar(temp);
    symtab->addInst(new InterInst(OP_NEG, temp, val));
    return temp;
}
void GenIR::genIFHead(Var* cond, InterInst*& _else)
{
    _else = new InterInst();
    if (cond) {
        if (cond->isPtr) cond = genAssign(cond);
        symtab->addInst(new InterInst(OP_JF, _else, cond));
    }
}
void GenIR::genElseHead(InterInst* _else, InterInst*& _exit)
{
    _exit = new InterInst();
    symtab->addInst(new InterInst(OP_JMP, _exit));
    symtab->addInst(_else);
}
void GenIR::genElseTail(InterInst*& _exit)
{
    symtab->addInst(_exit);
}
void GenIR::genIFTail(InterInst*& _else)
{
    symtab->addInst(_else);
}
void GenIR::genSwitchHead(InterInst*& _exit)
{
    _exit = new InterInst();
    push(NULL, _exit);
}
void GenIR::genSwitchTail(InterInst* _exit)
{
    symtab->addInst(_exit);
    pop();
}
void GenIR::genCaseHead(Var* cond, Var* lb, InterInst*& _case_exit)
{
    _case_exit = new InterInst();

    if (lb) symtab->addInst(new InterInst(OP_JNE, _case_exit, cond, lb));
}
void GenIR::genCaseTail(InterInst* _case_exit)
{
    symtab->addInst(_case_exit);
}
void GenIR::genWhileHead(InterInst*& _while, InterInst*& _exit)
{
    _while = new InterInst();
    symtab->addInst(_while);
    _exit = new InterInst();
    push(_while, _exit);
}
void GenIR::genWhileCond(Var* cond, InterInst* _exit)
{
    if (cond) {
        if (cond->isVoid()) cond = Var::getTrue();
        else if (cond->isPtr) cond = genAssign(cond);
        symtab->addInst(new InterInst(OP_JF, _exit, cond));
    }
}
void GenIR::genWhileTail(InterInst*& _while, InterInst*& _exit)
{
    symtab->addInst(new InterInst(OP_JMP, _while));
    symtab->addInst(_exit);
    pop();
}
void GenIR::genDoWhileHead(InterInst*& _do, InterInst*& _exit)
{
    _do = new InterInst();
    _exit = new InterInst();
    symtab->addInst(_do);
    push(_do, _exit);
}
void GenIR::genDoWhileTail(Var* cond, InterInst* _do, InterInst* _exit)
{
    if (cond) {
        if (cond->isVoid()) cond == Var::getTrue();
        else if (cond->isPtr) cond = genAssign(cond);
        symtab->addInst(new InterInst(OP_JT, _do, cond));
    }
    symtab->addInst(_exit);
    pop();
}
void GenIR::genForHead(InterInst*& _for, InterInst*& _exit)
{
    _for = new InterInst();
    _exit = new InterInst();
    symtab->addInst(_for);
}
void GenIR::genForCondBegin(Var* cond, InterInst*& _step, InterInst*& _block, InterInst* _exit)
{
    _block = new InterInst();
    _step = new InterInst();
    if (cond) {
        if (cond->isVoid()) cond == Var::getTrue();
        else if (cond->isPtr) cond = genAssign(cond);
        symtab->addInst(new InterInst(OP_JF, _exit, cond));
        symtab->addInst(new InterInst(OP_JMP, _block));
    }
    symtab->addInst(_step);

    push(_step, _exit);
}
void GenIR::genForCondEnd(InterInst* _for, InterInst* _block)
{
    symtab->addInst(new InterInst(OP_JMP, _for));
    symtab->addInst(_block);
}
void GenIR::genForTail(InterInst*& _step, InterInst*& _exit)
{
    symtab->addInst(new InterInst(OP_JMP, _step));
    symtab->addInst(_exit);
    pop();
}
void GenIR::push(InterInst* head, InterInst* tail)
{
    heads.push_back(head);
    tails.push_back(tail);
}
void GenIR::pop()
{
    heads.pop_back();
    tails.pop_back();
}
void GenIR::genBreak()
{
    InterInst* tail = tails.back();
    if (tail) symtab->addInst(new InterInst(OP_JMP, tail));
    else SEMERROR(BREAK_ERR, "break");
}
void GenIR::genContinue()
{
    InterInst* head = heads.back();
    if (head) symtab->addInst(new InterInst(OP_JMP, head));
    else SEMERROR(CONTINUE_ERR, "continue");
}
void GenIR::genPrintf(Var* val)
{
    if (val == NULL) return;
    symtab->addInst(new InterInst(OP_PRINTF, val));
}

void GenIR::genWrite(Var* val, Var* vd)
{
    if (val == NULL) return;
    InterInst* temp = new InterInst(OP_WRITE, NULL, val, vd, NULL, NULL);
    symtab->addInst(temp);
}

void GenIR::genRead(Var* val, Var* vd)
{
    if (val == NULL) return;
    symtab->addInst(new InterInst(OP_READ, val, vd, NULL, NULL, NULL));
}

Var* GenIR::genAdd(Var* result, Var* lval, Var* rval)
{
    if (!lval->isBase() && rval->isBase()) {
        rval = genMul(rval, Var::getStep(lval));
    }
    else if (lval->isBase() && !rval->isBase()) {
        lval = genMul(lval, Var::getStep(rval));
    }
    else if (!lval->isBase() && !rval->isBase()) {
        if (!lval->isBase())SEMERROR(EXPR_NOT_BASE, lval->name);
        else if (!rval->isBase()) SEMERROR(EXPR_NOT_BASE, rval->name);
        return lval;
    }
    symtab->addInst(new InterInst(OP_ADD, result, lval, rval));
    return result;
}

Var* GenIR::genSub(Var* result, Var* lval, Var* rval)
{
    if (!rval->isBase()) {
        SEMERROR(EXPR_NOT_BASE, rval->name);
        return lval;
    }
    if (!lval->isBase()) {
        rval = genMul(rval, Var::getStep(lval));
    }
    symtab->addInst(new InterInst(OP_SUB, result, lval, rval));
    return result;
}

Var* GenIR::genMul(Var* result, Var* lval, Var* rval)
{
    symtab->addInst(new InterInst(OP_MUL, result, lval, rval));
    return result;
}

Var* GenIR::genDiv(Var* result, Var* lval, Var* rval)
{
    symtab->addInst(new InterInst(OP_DIV, result, lval, rval));
    return result;
}
