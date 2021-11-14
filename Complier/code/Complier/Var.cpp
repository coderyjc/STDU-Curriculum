#include"Var.h"
#include"Num.h"
#include"Char.h"
#include"Str.h"
#include"GenIR.h"
#include"Error.h"


Var::Var(vector<int> scopepath, Var* val)
{
    _clear();
    this->literal = val->literal;
    this->externed = val->externed;
    this->type = val->type;
    this->name = GenIR::genLb();
    this->isPtr = false;
    this->isArray = false;
    this->arraySize = val->arraySize;
    this->isLeft = val->isLeft;
    this->initdata = val->initdata;
    this->inited = val->inited;
    this->intVal = val->intVal;
    this->strVal = val->strVal;
    this->ptrVal = val->ptrVal;
    this->ptr = val->ptr;
    this->pointTo = val->pointTo;
    this->_size = val->_size;
    this->offset = val->offset;
    this->scopepath = scopepath;
}
Var::Var(vector<int> scopepath, bool ext, _TokenType _type, string name, bool isPtr, bool isArray, int arraySize, bool isLeft, Var* initdata, bool inited)
{
    _clear();
    setType(_type);
    this->scopepath = scopepath;
    this->externed = ext;
    this->name = name;
    this->isPtr = isPtr;
    this->isArray = isArray;
    this->isLeft = isLeft;
    this->initdata = initdata;
    this->inited = inited;
    if (isArray) setArray(arraySize);
}
Var* Var::getTrue()
{
    Var* temp = new Var();
    temp->literal = true;
    temp->setType(_INT);
    temp->intVal = 1;
    temp->literal = true;
    return temp;
}
Var* Var::getVoid()
{
    Var* result = new Var();
    result->literal = true;
    result->type = _VOID;
    return result;
}
Var::Var(vector<int> scopepath, _TokenType _type, bool isPtr)
{
    _clear();
    setType(_type);
    this->name = GenIR::genLb();
    this->scopepath = scopepath;
    this->isPtr = isPtr;
}

Var::Var(Token* token)
{
    _clear();
    literal = true;
    isLeft = false;
    switch (token->type)
    {
    case NUM:
        setType(_INT);
        name = "<int>";
        intVal = ((Num*)token)->val;
        break;
    case CH:
        setType(_CHAR);
        name = "<char>";
        charVal = ((Char*)token)->ch;
        break;
    case STR:
        setType(_CHAR);
        name = GenIR::genLb();
        strVal = ((Str*)token)->str;
        setArray(strVal.size() + 1);
        break;
    }
}
void Var::_clear()/**< really??????????????? */
{
    this->isPara = false;
    this->pointTo = NULL;
    this->literal = false;
    this->scopepath.clear();
    this->externed = false;
    this->isArray = false;
    this->isLeft = false;
    this->isPtr = false;
    this->inited = false;
    this->ptr = NULL;
    this->type = _INT;
    this->initdata = NULL;
    this->_size = 0;
    this->offset = 0;
    this->intVal = 0;
    this->arraySize = 0;
}
bool Var::isBase()
{
    if (isArray || isPtr) return false;
    else if (type == _INT || type == _CHAR) return true;
    //else return false;
}
Var::Var()
{
    _clear();
    setType(_INT);
}
void Var::setType(_TokenType type)
{
    this->type = type;
    if (type == _VOID)
    {
        SEMERROR(VOID_VAR, "");
        type = _INT;
    }
    if (!externed && type == _INT) _size = 4;
    else if (!externed && type == _CHAR) _size = 1;
}
void Var::setArray(int len)
{
    if (len <= 0) {
        SEMERROR(ARRAY_LEN_INVALID, name);
        return;
    }
    else {
        isArray = true;
        isLeft = false;
        arraySize = len;
        if (!externed) _size *= len;
    }
}
bool Var::setInit()
{
    Var* init = initdata;
    if (!init) return false;
    inited = false;
    if (externed) SEMERROR(DEC_INIT_DENY, name);
    else if (!GenIR::typeCheck(this, init)) SEMERROR(VAR_INIT_ERR, name);
    else if (init->literal) {
        inited = true;
        if (init->isArray) ptrVal = init->name;
        else intVal = init->intVal;
    }
    else {
        if (scopepath.size() == 1) SEMERROR(GLB_INIT_ERR, name);
        else return true;
    }
    return false;
}

bool Var::isVoid()
{
    if (this->type == _VOID) return true;
    else return false;
}
Var* Var::getStep(Var* val)/**< help!!!!!!!!!!!!!!!!!!!!!!!!!!1 */
{
    Var* temp = new Var();
    temp->type = _INT;
    temp->literal = true;
    if (val->isBase()) { temp->intVal = 1; return temp; }
    else if (val->type == _CHAR) { temp->intVal = 1; return temp; }
    else if (val->type == _INT) { temp->intVal = 4; return temp; }
    else return NULL;
}
string Var::getRawStr()
{
    stringstream ss;
    int len = strVal.size();
    for (int i = 0; i < len; i++)
    {
        if (i != len - 1 && strVal[i] == '\n')
        {
            ss << "\\12"; continue;
        }
        else if (i == len - 1 && strVal[i] == '\n')
        {
            ss << ""; continue;
        }
        if (strVal[i] == '\t') ss << "\\11";
        else if (strVal[i] == '\"') ss << "\\\"";
        else if (strVal[i] == '\\') ss << "\\\\";
        else ss << strVal[i];
    }
    ss << "\\0";
    return ss.str();
}
