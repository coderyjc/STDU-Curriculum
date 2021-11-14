#include"InterInst.h"
#include<string>
#include"global.h"
using namespace std;

void InterInst::_clear()
{
    this->arg1 = NULL;
    this->arg2 = NULL;
    this->fun = NULL;
    this->label = "";
    this->result = NULL;
    this->target = NULL;
}
InterInst::InterInst(Operator op, Var* result, Var* arg1, Var* arg2, Fun* fun, InterInst* target)
{
    _clear();
    this->op = op;
    this->target = target;
    this->arg1 = arg1;
    this->arg2 = arg2;
    this->fun = fun;
    this->result = result;
}
InterInst::InterInst(Operator op, InterInst* target, Var* arg1, Var* arg2)
{
    _clear();
    this->op = op;
    this->target = target;
    this->arg1 = arg1;
    this->arg2 = arg2;
}
InterInst::InterInst(Operator op, InterInst* target)
{
    _clear();
    this->op = op;
    this->target = target;
}
InterInst::InterInst(Operator op, Var* result, Var* arg1)
{
    _clear();
    this->op = op;
    this->result = result;
    this->arg1 = arg1;
}
InterInst::InterInst(Operator op, Var* result, Var* arg1, Var* arg2)
{
    _clear();
    this->op = op;
    this->result = result;
    this->arg1 = arg1;
    this->arg2 = arg2;
}
InterInst::InterInst(Operator op, Fun* func, Var* result)
{
    _clear();
    this->op = op;
    this->fun = func;
    this->result = result;
}
InterInst::InterInst(Operator op, InterInst* target, Var* result)
{
    _clear();
    this->op = op;
    this->target = target;
    this->arg1 = result;
}
InterInst::InterInst(Operator op, Fun* func)
{
    _clear();
    this->op = op;
    this->fun = func;
}
InterInst::InterInst()
{
    _clear();
    this->label = GenIR::genLb();
}
InterInst::InterInst(Operator op, Var* arg)
{
    _clear();
    this->op = op;
    arg1 = arg;
}
void InterInst::loadVar(string reg32, string reg8, Var* var)
{
    if (!var) return;
    const char* reg;
    if (var->type == _CHAR && var->isBase()) reg = reg8.c_str();
    else reg = reg32.c_str();
    char* type;
    if (var->type == _CHAR && var->isBase()) type = "BYTE";
    else type = "DWORD";
    if (var->type == _CHAR) emit("mov %s,0", reg32.c_str());
    const char* name = var->name.c_str();
    int offset = var->offset;
    if (!var->literal)
    {
        if (!offset)
        {
            emit("mov %s,OFFSET FLAT:_%s", reg, name);
        }
        else
        {
            if (!var->isArray) emit("mov %s,%s PTR [ebp%+d]", reg, type, offset);
            else emit("lea %s,[ebp%+d]", reg, offset);
        }
    }
    else
    {
        if (var->isBase()) emit("mov %s,%d", reg, var->intVal);
        else emit("lea %s,[ebp%+d]", reg, offset);//error
    }
}
void InterInst::leaVar(string reg32, Var* var)
{
    if (!var) return;
    const char* type;
    if (var->type == _CHAR && var->isBase()) type = "BYTE";
    else type = "DWORD";
    const char* reg = reg32.c_str();
    const char* name = var->name.c_str();
    int off = var->offset;
    if (!off) emit("mov %s,OFFSET FLAT:_%S", reg, name);
    else emit("lea %s,[ebp%+d]", reg, off);
}
void InterInst::storeVar(string reg32, string reg8, Var* var)
{
    if (!var) return;
    const char* type;
    if (var->type == _CHAR && var->isBase()) type = "BYTE";
    else type = "DWORD";
    const char* reg;
    if (var->type == _CHAR && var->isBase()) reg = reg8.c_str();
    else reg = reg32.c_str();
    const char* name = var->name.c_str();
    int off = var->offset;
    if (!off) emit("mov OFFSET:FLAT:_%s,%s", name, reg);
    else emit("mov %s PTR[ebp%+d],%s", type, off, reg);
}
void InterInst::initVar(Var* var)
{
    if (!var) return;
    const char* type;
    if (var->type == _CHAR && var->isBase()) type = "BYTE";
    else type = "DWORD";
    if (var->inited)
    {
        if (var->isBase()) emit("mov eax,%d", var->intVal);
        else if (!var->initdata->isBase())    emit("mov eax,OFFSET FLAT:_%s", var->initdata->name.c_str());
        else if (var->initdata->isBase())   emit("mov eax,%s PTR [ebp%+d]", type, var->initdata->offset);
        storeVar("eax", "al", var);
    }
}
void InterInst::toX86()
{
    if (label != "")
    {
        fprintf(file, "%s:\n", label.c_str());
        return;
    }
    switch (op)
    {
    case OP_NOP:
        emit("nop");
    case OP_DEC:
        initVar(arg1);
        break;
    case OP_ENTRY:
        emit("push ebp");
        emit("mov ebp,esp");
        if (this->fun->name == "main") {
            emit("and esp, -16");
            emit("sub esp,%d", this->fun->maxDepth + 16);
        }
        else emit("sub esp,%d", this->fun->maxDepth);
        if (this->fun->name == "main") { emit("call	___main"); }
        break;
    case OP_EXIT:
        emit("mov esp,ebp");
        emit("pop ebp");
        emit("ret");
        break;
    case OP_AS:
        loadVar("eax", "al", arg1);
        storeVar("eax", "al", result);
        break;
    case OP_ADD:
        loadVar("eax", "al", arg1);
        loadVar("ebx", "bl", arg2);
        emit("add eax,ebx");
        storeVar("eax", "al", result);
        break;
    case OP_SUB:
        loadVar("eax", "al", arg1);
        loadVar("ebx", "bl", arg2);
        emit("sub eax,ebx");
        storeVar("eax", "al", result);
        break;
    case OP_MUL:
        loadVar("eax", "al", arg1);
        loadVar("ebx", "bl", arg2);
        emit("imul ebx");
        storeVar("eax", "al", result);
        break;
    case OP_DIV:
        loadVar("eax", "al", arg1);
        loadVar("ebx", "bl", arg2);
        emit("idiv ebx");
        storeVar("eax", "al", result);
        break;
    case OP_MOD:
        loadVar("eax", "al", arg1);
        loadVar("ebx", "bl", arg2);
        emit("idiv eax,ebx");
        storeVar("edx", "dl", result);
        break;
    case OP_NEG:
        loadVar("eax", "al", arg1);
        emit("neg eax");
        storeVar("eax", "al", result);
    case OP_GT:
        loadVar("eax", "al", arg1);
        loadVar("ebx", "bl", arg2);
        emit("mov ecx,0");
        emit("cmp eax,ebx");
        emit("setg cl");
        storeVar("ecx", "cl", result);
        break;
    case OP_GE:
        loadVar("eax", "al", arg1);
        loadVar("ebx", "bl", arg2);
        emit("mov ecx,0");
        emit("cmp eax,ebx");
        emit("setge cl");
        storeVar("ecx", "cl", result);
        break;
    case OP_LT:
        loadVar("eax", "al", arg1);
        loadVar("ebx", "bl", arg2);
        emit("mov ecx,0");
        emit("cmp eax,ebx");
        emit("setl cl");
        storeVar("ecx", "cl", result);
        break;
    case OP_LE:
        loadVar("eax", "al", arg1);
        loadVar("ebx", "bl", arg2);
        emit("mov ecx,0");
        emit("cmp eax,ebx");
        emit("setle cl");
        storeVar("ecx", "cl", result);
        break;
    case OP_EQU:
        loadVar("eax", "al", arg1);
        loadVar("ebx", "bl", arg2);
        emit("mov ecx,0");
        emit("cmp eax,ebx");
        emit("sete cl");
        storeVar("ecx", "cl", result);
        break;
    case OP_NE:
        loadVar("eax", "al", arg1);
        loadVar("ebx", "bl", arg2);
        emit("mov ecx,0");
        emit("cmp eax,ebx");
        emit("setne cl");
        storeVar("ecx", "cl", result);
        break;
    case OP_NOT:
        loadVar("eax", "al", arg1);
        emit("mov ebx,0");
        emit("cmp eax,0");
        emit("sete bl");
        storeVar("ebx", "bl", result);
        break;
    case OP_AND:
        loadVar("eax", "al", arg1);
        emit("cmp eax,0");
        emit("setne al");
        loadVar("ebx", "bl", arg2);
        emit("cmp ebx,0");
        emit("setne bl");
        emit("and eax,ebx");
        storeVar("eax", "al", result);
        break;
    case OP_OR:
        loadVar("eax", "al", arg1);
        emit("cmp eax,0");
        emit("setne al");
        loadVar("ebx", "bl", arg2);
        emit("cmp ebx,0");
        emit("setne bl");
        emit("or eax,ebx");
        storeVar("eax", "al", result);
        break;
    case OP_JMP:
        emit("jmp %s", target->label.c_str());
        break;
    case OP_JT:
        loadVar("eax", "al", arg1);
        emit("cmp eax,0");
        emit("jne %s", target->label.c_str());
        break;
    case OP_JF:
        loadVar("eax", "al", arg1);
        emit("cmp eax,0");
        emit("je %s", target->label.c_str());
        break;
    case OP_JNE:
        loadVar("eax", "al", arg1);
        loadVar("ebx", "bl", arg2);
        emit("cmp eax,ebx");
        emit("jne %s", target->label.c_str());
        break;
    case OP_ARG:
        loadVar("eax", "al", arg1);
        emit("push eax");
        break;
    case OP_PROC:
        emit("call _%s", fun->name.c_str());
        emit("add esp,%d", fun->paraVar.size() * 4);
        break;
    case OP_RET:
        emit("jmp %s", target->label.c_str());
        break;
    case OP_RETV:
        loadVar("eax", "al", arg1);
        emit("jmp %s", target->label.c_str());
        break;
    case OP_LEA:
        leaVar("eax", arg1);
        storeVar("eax", "al", result);
        break;
    case OP_SET:
        loadVar("eax", "al", result);
        loadVar("edx", "bl", arg1);
        if (result->type == _CHAR)
            emit("mov BYTE PTR[eax],edx");
        else emit("mov DWORD PTR[eax],edx");
        break;
    case OP_ASP:
        loadVar("eax", "al", arg1);
        if (arg1->type == _CHAR) { emit("mov edx,0"); emit("mov dl, BYTE PTR [eax]"); }
        else emit("mov edx, DWORD PTR [eax]");
        loadVar("eax", "al", result);
        if (result->type == _CHAR)
            emit("mov BYTE PTR[eax],edx");
        else emit("mov DWORD PTR[eax],edx");
        break;
    case OP_GET:
        loadVar("eax", "al", arg1);
        if (arg1->type == _CHAR)
            emit("mov eax,BYTE PTR [eax]");
        else emit("mov eax,DWORD PTR [eax]");
        if (result != NULL)
            storeVar("eax", "al", result);
        break;
    case OP_CALL:
        emit("call _%s", fun->name.c_str());
        emit("add esp,%d", fun->paraVar.size() * 4);
        storeVar("eax", "al", result);
        break;
    case OP_PRINTF:
        if (arg1->arraySize == 1) break;
        else if (arg1->arraySize == 2) {
            emit("mov	DWORD PTR [esp], %d\n", arg1->strVal[0]);
            emit("call  _putchar\n");
            break;
        }
        else {
            emit("mov	DWORD PTR [esp], OFFSET FLAT:_%s\n", arg1->name.c_str());
            if (arg1->strVal[arg1->strVal.size() - 1] == '\n')
                emit("call	_puts");
            else emit("call	_printf");
        }
        break;
    case OP_WRITE:
        if (arg1->type == _INT && arg1->isPara == false) {
            loadVar("eax", "al", arg1);
            emit("mov	DWORD PTR [esp+4], eax");
            emit("mov	DWORD PTR [esp], OFFSET FLAT:_%s\n", arg2->name.c_str());
            emit("call  _printf");
        }
        else if (arg1->type == _CHAR && arg1->isPara == false) {
            emit("movzx	eax, BYTE PTR [ebp%+d]", arg1->offset);
            emit("movsx	eax, al");
            emit("mov	DWORD PTR [esp], eax");
            emit("call	_putchar");
        }
        else if (arg1->type == _INT && arg1->isPara)
        {
            loadVar("eax", "al", arg1);
            emit("mov	eax, DWORD PTR [eax]");
            emit("mov	DWORD PTR [esp+4], eax");
            emit("mov	DWORD PTR [esp], OFFSET FLAT:_%s\n", arg2->name.c_str());
            emit("call  _printf");
        }
        else if (arg1->type == _CHAR && arg1->isPara)
        {
            emit("movzx	eax, BYTE PTR [ebp%+d]", arg1->offset);
            emit("movsx	eax, al");
            emit("mov	eax, DWORD PTR [eax]");
            emit("mov	DWORD PTR [esp], eax");
            emit("call	_putchar");
        }
        break;
    case OP_READ:
        if (result->isBase() && !result->isPara)
        {
            emit("lea	eax, [ebp%+d]", result->offset);
            emit("mov	DWORD PTR [esp+4], eax");
            emit("mov	DWORD PTR [esp], OFFSET FLAT:_%s", arg1->name.c_str());
            emit("call	_scanf");
        }
        else if (!result->isBase() && !result->isPara) {
            emit("mov	eax, DWORD PTR [ebp%+d]", result->offset);
            emit("mov	DWORD PTR [esp+4], eax");
            emit("mov	DWORD PTR [esp], OFFSET FLAT:_%s", arg1->name.c_str());
            emit("call	_scanf");
        }
        else if (result->isBase() && result->isPara)
        {
            emit("lea	eax, [ebp%+d]", result->offset);
            if (result->type == _INT) emit("mov	eax, DWORD PTR [eax]");
            else if (result->type == _CHAR) emit("mov	eax, BYTE PTR [eax]");
            emit("mov	DWORD PTR [esp+4], eax");
            emit("mov	DWORD PTR [esp], OFFSET FLAT:_%s", arg1->name.c_str());
            emit("call	_scanf");
        }
        else if (!result->isBase() && result->isPara)
        {
            emit("mov	eax, DWORD PTR [ebp%+d]", result->offset);
            if (result->type == _INT) emit("mov	eax, DWORD PTR [eax]");
            else if (result->type == _CHAR) emit("mov	eax, BYTE PTR [eax]");
            emit("mov	DWORD PTR [esp+4], eax");
            emit("mov	DWORD PTR [esp], OFFSET FLAT:_%s", arg1->name.c_str());
            emit("call	_scanf");
        }
        break;
    }
}
