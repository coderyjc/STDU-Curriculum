#include"Fun.h"
#include"Error.h"
#include"GenIR.h"

void Fun::enterScope()
{
    ScopeEsp.push_back(0);
}
void Fun::leaveScope()
{
    maxDepth = (curEsp > maxDepth) ? curEsp : maxDepth;
    if (IODepthflag) maxDepth += 8;
    curEsp -= ScopeEsp.back();
    ScopeEsp.pop_back();
}

void Fun::locate(Var* var)
{
    int _size = var->_size;
    _size += (4 - _size % 4) % 4;
    ScopeEsp.back() += _size;
    curEsp += _size;
    var->offset = 0 - curEsp;

}
Fun::Fun(bool ext, _TokenType type, string n, vector<Var*>& paraList)
{
    this->externed = ext;
    this->type = type;
    this->name = n;
    this->paraVar = paraList;
    this->curEsp = 0;
    this->maxDepth = 0;
    this->IODepthflag = false;
    //cout<<paraVar.size()<<endl;
    for (int i = 0, argOff = 8; i < paraVar.size(); i++, argOff += 4)
    {
        //cout<<paraList[i]->offset<<endl;
        //cout<<paraVar[i]<<endl;
        this->paraVar[i]->offset = argOff;
    }
}

bool Fun::match(Fun* fun)
{
    if (name != fun->name) return false;
    if (paraVar.size() != fun->paraVar.size()) return false;
    int len = paraVar.size();
    for (int i = 0; i < len; i++) {
        if (GenIR::typeCheck(paraVar[i], fun->paraVar[i])) {
            if (paraVar[i]->type != fun->paraVar[i]->type) {
                SEMWARN(FUN_DEC_CONFLICT, name);
            }
        }
        else return false;
    }
    if (type != fun->type) {
        SEMWARN(FUN_RET_CONFLICT, name);
    }
    return true;
}

bool Fun::match(vector<Var*>& args) {
    if (paraVar.size() != args.size()) return false;
    int len = paraVar.size();
    for (int i = 0; i < len; i++) {
        if (!GenIR::typeCheck(paraVar[i], args[i])) return false;
    }
    return true;
}

void Fun::define(Fun* def)
{
    externed = false;
    paraVar = def->paraVar;
}
Fun::Fun()
{
    this->externed = false;
    this->type = _INT;
    this->paraVar.clear();
    this->maxDepth = 0;
    this->curEsp = 0;
    this->ScopeEsp.clear();
    this->interCode.clear();
    this->returnPoint = NULL;
    this->IODepthflag = false;
}
