#include"SymTab.h"
#include"Error.h"
#include<fstream>
#include<algorithm>
using namespace std;

SymTab::SymTab()
{
    this->curFun = NULL;
    this->scopeId = 0;
    this->scopePath.push_back(this->scopeId);
    this->varTab.clear();
    this->strTab.clear();
    this->funTab.clear();
}
vector<int> SymTab::getScopePath()
{
    return scopePath;
}
void SymTab::leave()
{
    scopePath.pop_back();
    if (curFun) curFun->leaveScope();
}
void SymTab::enter()
{
    scopeId++;
    scopePath.push_back(scopeId);
    if (curFun) curFun->enterScope();
}
void SymTab::addVar(Var* var)
{
    //cout<<var->name<<endl;
    if (varTab.find(var->name) == varTab.end())
    {
        varTab[var->name] = new vector<Var*>;
        varTab[var->name]->push_back(var);
    }
    else
    {
        vector<Var*>& _list = *varTab[var->name];//&_list vector<Var*> so _list vector<Var*>*
        int i = 0;
        for (; i < _list.size(); i++)
        {
            if (_list[i]->scopepath.size() == 0 || var->scopepath.size() == 0) break;
            if (_list[i]->scopepath.back() == var->scopepath.back()) break;
        }
        if (i == _list.size() || var->name[0] == '<')
            _list.push_back(var);
        else
        {
            SEMERROR(VAR_RE_DEF, var->name);
            //cout<<"debug for var re def"<<endl;
            delete var;
            return;
        }
    }
    if (ir)
    {
        int flag = ir->genVarInit(var);/**< 中间代码 变量初始化 */
        if (curFun && flag) curFun->locate(var);/**< 计算局部变量栈帧偏移 scopeEsp curEsp offset */
        //symtab->ShowIR();
    }
}

void SymTab::addStr(Var*& v)//引用
{
    hash_map<string, Var*, str_hash>::iterator strIt, strEnd = strTab.end();
    for (strIt = strTab.begin(); strIt != strEnd; ++strIt)
    {
        Var* str = strIt->second;
        if (v->strVal == str->strVal)/**< string already existed */
        {
            delete v;
            v = str;
            return;
        }
    }
    strTab[v->name] = v;
}
Var* SymTab::getVar(string name, vector<int> scopepath)
{
    Var* _select = NULL;
    if (varTab.find(name) != varTab.end())
    {
        vector<Var*>& _list = *varTab[name];
        int pathLen = scopePath.size();
        int maxLen = 0;
        for (int i = 0; i < _list.size(); i++)
        {
            int len = _list[i]->scopepath.size();
            if (len <= pathLen && _list[i]->scopepath[len - 1] == scopePath[len - 1])
                if (len > maxLen)
                {
                    maxLen = len;
                    _select = _list[i];
                }
        }
    }
    if (!_select)
        SEMERROR(VAR_UN_DEC, name);
    return _select;
}
Var* SymTab::getVar(string name)
{
    Var* _select = NULL;
    if (varTab.find(name) != varTab.end())
    {
        vector<Var*>& _list = *varTab[name];
        int pathLen = scopePath.size();
        int maxLen = 0;
        for (int i = 0; i < _list.size(); i++)
        {
            int len = _list[i]->scopepath.size();
            if (len <= pathLen && _list[i]->scopepath[len - 1] == scopePath[len - 1])
                if (len > maxLen)
                {
                    maxLen = len;
                    _select = _list[i];
                }
        }
    }
    if (!_select)
        SEMERROR(VAR_UN_DEC, name);
    return _select;
}

void SymTab::decFun(Fun* fun)
{
    fun->externed = true;
    if (funTab.find(fun->name) == funTab.end())
    {
        funTab[fun->name] = fun;
        //        for(int i=0;i<fun->paraVar.size();i++)
        //        {
        //            symtab->addVar(fun->paraVar[i]);
        //        }
    }
    else
    {
        Fun* last = funTab[fun->name];
        if (!last->match(fun))
        {
            SEMERROR(FUN_DEC_ERR, fun->name);
        }
        delete fun;
    }
}

void SymTab::defFun(Fun* fun)
{
    //cout<<fun->name<<fun->paraVar.size()<<endl;
    //if(fun->paraVar.size()>0) cout<<fun->paraVar[0]->name<<fun->paraVar[1]->name<<endl;
    if (fun->externed)
    {
        SEMERROR(EXTERN_FUN_DEF, fun->name);
        fun->externed = false;
    }
    if (funTab.find(fun->name) == funTab.end())
    {
        funTab[fun->name] = fun;
        //funList.push_back(fun->name);
//        for(int i=0;i<fun->paraVar.size();i++)
//        {
//            symtab->addVar(fun->paraVar[i]);
//        }
    }
    else
    {
        Fun* last = funTab[fun->name];
        if (last->externed)
        {
            if (!last->match(fun))
            {
                SEMERROR(FUN_DEC_ERR, fun->name);
            }
            last->define(fun);
        }
        else
        {
            SEMERROR(FUN_RE_DEF, fun->name);
        }
        hash_map<string, Fun*, str_hash>::iterator funIt, funEnd = funTab.end();
        for (funIt = funTab.begin(); funIt != funEnd; ++funIt)
        {
            string str = funIt->first;
            //cout<<str<<endl;
            if (str == fun->name) { funTab.erase(funIt); break; }
        }
        funTab[fun->name] = fun;
    }
    //ShowFunTab();
    curFun = fun;
    ir->genFunHead(curFun);/**< 产生入口地址 */
}

void SymTab::endDefFun()
{
    ir->genFunTail(curFun);/**< 产生函数出口 */
    curFun = NULL;/**< ？？？？？？？不应该是NULL？？ */
}

Fun* SymTab::getFun(string name, vector<Var*>& args)
{
    if (funTab.find(name) != funTab.end())
    {
        Fun* last = funTab[name];
        if (!last->match(args))
        {
            SEMERROR(FUN_CALL_ERR, name);
            return NULL;
        }
        return last;
    }
    SEMERROR(FUN_UN_DEC, name);
    return NULL;
}

void SymTab::addInst(InterInst* newInst)
{
    if (curFun == NULL) return;
    funTab[curFun->name]->interCode.push_back(newInst);
}
vector<Var*> SymTab::getGlbVars()
{
    vector<Var*> glbVars;
    hash_map<string, vector<Var*>*, str_hash>::iterator varIt, varEnd = varTab.end();
    for (varIt = varTab.begin(); varIt != varEnd; ++varIt)
    {
        string varName = varIt->first;
        if (varName[0] == '<') continue;
        vector<Var*>& list = *varIt->second;
        for (int j = 0; j < list.size(); j++)
        {
            if (list[j]->scopepath.size() == 1)
            {
                glbVars.push_back(list[j]);
                break;
            }
        }
    }
    return glbVars;
}
int SymTab::genData()
{

    vector<Var*> glbVars = getGlbVars();
    counter = glbVars.size();
    for (unsigned int i = 0; i < glbVars.size(); i++)
    {
        Var* var = glbVars[i];
        if (var->inited == false)
        {
            int first_size = var->type == _CHAR ? 1 : 4;
            if (var->isArray) first_size *= var->arraySize;
            int second_size = _CHAR ? 0 : 2;
            fprintf(file, "\t.comm\t_%s, %d, %d\n", var->name.c_str(), first_size, second_size);
            continue;
        }
        fprintf(file, "\t.globl _%s\n", var->name.c_str());
        fprintf(file, "\t.data\n");
        fprintf(file, "_%s:\n", var->name.c_str());
        int flag = var->type == _CHAR ? 1 : 2;
        if (flag == 1 && var->isBase())
        {
            fprintf(file, "\t.byte\t%d\n", var->charVal);
            fprintf(file, "\t.align 4\n");
        }
        else if (flag == 2 && var->isBase()) {
            fprintf(file, "\t.long\t%d\n", var->intVal);
            fprintf(file, "\t.align 4\n");
        }
        else if (!var->isBase() && flag == 2)
        {
            fprintf(file, "\t.long\t_%s\n", var->initdata->name.c_str());
            fprintf(file, "\t.align 4\n");
        }
        else if (!var->isBase() && flag == 1) {
            fprintf(file, "\t.long\t%s\n", var->initdata->name.c_str());
            fprintf(file, "\t.align 4\n");
        }
    }
    hash_map<string, Var*, str_hash>::iterator strIt = strTab.begin(), strEnd = strTab.end();
    if (strIt != strEnd) {
        fprintf(file, "\t.section .rdata,\"dr\"\n");
    }
    else return counter;
    for (strIt = strTab.begin(); strIt != strEnd; ++strIt)
    {
        Var* str = strIt->second;
        fprintf(file, "_%s:\n", str->name.c_str());
        fprintf(file, "\t.ascii \"%s\"\n", str->getRawStr().c_str());
        fprintf(file, "\t.align 4\n");
        counter++;
    }
    return counter;
}
void SymTab::genAsm()
{
    fprintf(file, "\t.file\t\"%s\"\n", strcat(lex->getFileName(false), ".c"));
    //cout<<lex->getFileName(false)<<endl;
    fprintf(file, "\t.intel_syntax noprefix\n");
    genData();
    fprintf(file, "\t.def	___main;	.scl	2;	.type	32;	.endef\n");
    fprintf(file, "\t.text\n");
    hash_map<string, Fun*, str_hash>::iterator funIt, funEnd = funTab.end();
    for (funIt = funTab.begin(); funIt != funEnd; ++funIt)
    {
        Fun* fun = funIt->second;
        fprintf(file, "\t.globl _%s\n", fun->name.c_str());
        fprintf(file, "\t.def	_%s;	.scl	2;	.type	32;	.endef\n", fun->name.c_str());
        fprintf(file, "_%s:\n", fun->name.c_str());
        vector<InterInst*>& code = fun->interCode;
        vector<InterInst*>::iterator instIt, instEnd = code.end();
        for (instIt = code.begin(); instIt != instEnd; ++instIt)
        {

            (*instIt)->toX86();
        }
    }
    fprintf(file, "\t.ident	\"GCC: (GNU) 6.4.0\"\n");
    sort(IOflag.begin(), IOflag.end());
    IOflag.erase(unique(IOflag.begin(), IOflag.end()), IOflag.end());
    for (int i = 0; i < IOflag.size(); i++)
    {
        if (IOflag[i] == 1) fprintf(file, "\t.def	_putchar;	.scl	2;	.type	32;	.endef\n");
        else if (IOflag[i] == 2) fprintf(file, "\t.def	_puts;	.scl	2;	.type	32;	.endef\n");
        else if (IOflag[i] == 3) fprintf(file, "\t.def	_printf;	.scl	2;	.type	32;	.endef\n");
        else if (IOflag[i] == 4) fprintf(file, "\t.def	_scanf;	.scl	2;	.type	32;	.endef\n");
    }

}
void SymTab::ShowVarTab()
{
    hash_map<string, vector<Var*>*, str_hash>::iterator varIt, varEnd = varTab.end();
    for (varIt = varTab.begin(); varIt != varEnd; ++varIt)
    {
        vector<Var*>& _list = *varIt->second;
        for (int j = 0; j < _list.size(); j++)
        {
            cout << _list[j]->name;
            for (int k = 0; k < _list[j]->scopepath.size(); k++)
                cout << _list[j]->scopepath[k];
            cout << endl;
        }
    }
}
void SymTab::ShowFunTab()
{
    hash_map<string, Fun*, str_hash>::iterator funIt, funEnd = funTab.end();
    for (funIt = funTab.begin(); funIt != funEnd; ++funIt)
    {
        Fun& _list = *funIt->second;
        cout << _list.name << "\tpara: ";
        for (int i = 0; i < _list.paraVar.size(); i++)
            cout << _list.paraVar[i]->name << "   ";
        cout << endl;
    }
}
void SymTab::ShowIR(bool outOpt)
{
    streambuf* coutbackup;
    ofstream fout(intercodeFile);
    if (outOpt == 1)
        coutbackup = cout.rdbuf(fout.rdbuf());
    hash_map<string, Fun*, str_hash>::iterator funIt, funEnd = funTab.end();
    for (funIt = funTab.begin(); funIt != funEnd; ++funIt)
    {
        Fun& _list = *funIt->second;
        vector<InterInst*>& intercode_copy = _list.interCode;
        for (int j = 0; j < intercode_copy.size(); j++)
        {
            if (intercode_copy[j]->label != "") cout << intercode_copy[j]->label << ":" << endl;
            else
            {
                cout << OperatorArray[int(intercode_copy[j]->op)] << " ";//cout<<(int)(intercode_copy[j]->op)<<" ";
                if (intercode_copy[j]->target != NULL)
                {
                    if (intercode_copy[j]->target->label != "")cout << intercode_copy[j]->target->label << " ";
                }
                if (intercode_copy[j]->result != NULL) {
                    if (intercode_copy[j]->result->name[0] == '<') cout << intercode_copy[j]->result->intVal << " ";
                    else  cout << intercode_copy[j]->result->name << " ";
                }
                if (intercode_copy[j]->arg1 != NULL)
                {
                    if (intercode_copy[j]->arg1->name[0] == '<') cout << intercode_copy[j]->arg1->intVal << " ";
                    else cout << intercode_copy[j]->arg1->name << " ";
                }
                if (intercode_copy[j]->arg2 != NULL)
                {
                    if (intercode_copy[j]->arg2->name[0] == '<') cout << intercode_copy[j]->arg2->intVal << " ";
                    else cout << intercode_copy[j]->arg2->name << " ";
                }
                if (intercode_copy[j]->fun != NULL) cout << intercode_copy[j]->fun->name << " ";
                cout << endl;
            }
        }
    }
    if (outOpt == 1) {
        cout.rdbuf(coutbackup);
    }
}
