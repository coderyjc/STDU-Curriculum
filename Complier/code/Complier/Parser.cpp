#include "Parser.h"
#include"Num.h"
#include"Id.h"
#include<iostream>
#include<iomanip>
#include<fstream>
#include<string>
#include"global.h"
#include"Str.h"
using namespace std;

Parser::Parser(char* filename)
{
    lex = new Lex(filename);
    drawCol.push_back(0);/** 控制语法树空格的数目 */
   // symtab->curFun = new Fun();
    //symtab->curFun->name = "global";/**< 负责记录全局变量 */
}

void Parser::analyze()
{
    mov();
    program();
}


void Parser::mov()
{
    pre = look;
    look = lex->tokenize();
    while (look->type == ERR)
    {
        look = lex->tokenize();
    }
    if (pre != NULL)
    {
        string str = pre->toString();
        str = getRawString(str);
        char* temp = new char[30];
        strcpy(temp, str.c_str());
        data.push_back(new DrawTreeData(drawCol, -1, temp));
    }
    //cout<<setw(80)<<setiosflags(ios::right)<<setfill('-')<<"cur_lex:"+look->toString()<<endl;
}

bool Parser::match(_TokenType need)
{
    if (look->type == need)
    {
        //for(int i=0; i<depth+4; i++) cout<<"  ";
        //cout<<look->toString()+" matching success"<<endl;
        mov();
        return true;
    }
    else return false;
}

void Parser::recovery(bool cond, SynError lost, SynError wrong)
{
    if (cond) SYNERROR(lost, look);
    else
    {
        SYNERROR(wrong, look);
        mov();
    }
}

/**
** <program> -><segment><program>|ε
*follow(program)
*/

void Parser::program()
{
    depth++;
    if (depth != 1) data.push_back(new DrawTreeData(drawCol, depth, (char*)__FUNCTION__));
    if (look->type == END) { depth--; return; }
    else
    {
        data.push_back(new DrawTreeData(drawCol, depth, (char*)__FUNCTION__));
        drawCol.push_back(depth);
        segment();
        drawCol.pop_back();
        program();
    }
    depth--;
}


/**
*<segment> ->_EXTERN <type><def> | <type><def>
*/
void Parser::segment()
{
    depth++;
    data.push_back(new DrawTreeData(drawCol, depth, (char*)__FUNCTION__));
    if (match(_EXTERN))
    {
        _TokenType temp = type();
        def(true, temp);
    }
    else
    {
        _TokenType temp = type();
        def(false, temp);
    }
    depth--;
}
/**
*<type> ->_INT|_CHAR|_VOID
*follow(type) :`<def> <paradata>         recovery
*/
_TokenType Parser::type()
{
    depth++;
    data.push_back(new DrawTreeData(drawCol, depth, (char*)__FUNCTION__));
    if (F(_INT)_(_CHAR)_(_VOID))
    {
        //for(int i=0; i<depth+4; i++) cout<<"  ";
        //cout<<look->toString()+" matching success"<<endl;
        _TokenType temp = look->type;
        mov();
        depth--;
        return temp;
    }
    else recovery(F(ID)_(TIMES), TYPE_LOST, TYPE_WRONG);
    depth--;
}


/**
* <defdata> ->ID <varrdef>|TIMES ID <init>
*first( init)
*/

Var* Parser::defdata(bool ext, _TokenType _type)
{
    depth++;
    data.push_back(new DrawTreeData(drawCol, depth, (char*)__FUNCTION__));
    string name = "";
    if (F(ID))
    {
        //for(int i=0; i<depth+4; i++) cout<<"  ";
        //cout<<look->toString()+" matching success"<<endl;
        name = ((Id*)look)->name;
        mov();
        Var* result = varrdef(ext, _type, false, name);
        symtab->addVar(result);
        depth--;
        return result;
    }
    else if (match(TIMES))
    {
        if (F(ID))
        {
            //for(int i=0; i<depth+4; i++) cout<<"  ";
            //cout<<look->toString()+" matching success"<<endl;
            name = ((Id*)look)->name;
            mov();
        }
        else recovery(F(SEMICON)_(COMMA)_(ASSIGN), ID_LOST, ID_WRONG);
        Var* result = init(ext, _type, true, name);
        symtab->addVar(result);
        depth--;
        return result;
    }
    else
    {
        recovery(F(SEMICON)_(COMMA)_(ASSIGN)_(LBRACK), ID_LOST, ID_WRONG);
        Var* result = varrdef(ext, _type, false, name);
        symtab->addVar(result);
        depth--;
        return result;
    }
}

/**
* <varrdef>->[num]|<init>
*follow(varrdef)
*/

Var* Parser::varrdef(bool ext, _TokenType _type, bool ptr, string name)
{
    depth++;
    data.push_back(new DrawTreeData(drawCol, depth, (char*)__FUNCTION__));
    Var* temp = NULL;
    if (match(LBRACK))
    {
        int len = 0;
        if (F(NUM))
        {
            //for(int i=0; i<depth+4; i++) cout<<"  ";
            //cout<<look->toString()+" matching success"<<endl;
            len = ((Num*)look)->val;
            mov();
        }
        else recovery(F(RBRACK), NUM_LOST, NUM_WRONG);
        if (!match(RBRACK)) recovery(F(SEMICON)_(COMMA), RBRACK_LOST, RBRACK_WRONG);
        temp = new Var(symtab->getScopePath(), ext, _type, name, false, true, len, false, NULL, false);
        //symtab->addVar(temp);
        depth--;
        return temp;
    }
    else {
        Var* temp = init(ext, _type, ptr, name);
        depth--;
        return temp;
    }
}

/**
** <init-> ASSIGN<expr>|ε
*follow(init)
*/
Var* Parser::init(bool ext, _TokenType _type, bool ptr, string name)
{
    depth++;
    data.push_back(new DrawTreeData(drawCol, depth, (char*)__FUNCTION__));
    Var* initVal = NULL;
    if (match(ASSIGN))
    {
        //cout<<look->toString()<<endl;
        initVal = expr();
    }
    bool inited;
    if (initVal == NULL) inited = false;
    else inited = true;
    Var* temp = new Var(symtab->getScopePath(), ext, _type, name, ptr, false, 0, true, initVal, inited);
    if (ptr == true && initVal != NULL && initVal->isPtr) {
        Var* cur = initVal;
        while (cur->pointTo != NULL)
            cur = cur->pointTo;
        temp->pointTo = cur;
        cur->ptr = temp;
    }
    else if (ptr == true && initVal != NULL && !initVal->isPtr) temp->pointTo = initVal;
    //symtab->addVar(temp);
    //symtab->ShowVarTab();
    depth--;
    return temp;
}


/**
** <deflist> ->COMMA <defdata><deflist>|SEMICON
*first (type) first (statement)
*/
void Parser::deflist(bool ext, _TokenType _type)
{
    depth++;
    data.push_back(new DrawTreeData(drawCol, depth, (char*)__FUNCTION__));
    if (match(COMMA))
    {
        drawCol.push_back(depth);
        defdata(ext, _type);
        drawCol.pop_back();
        deflist(ext, _type);
    }
    else if (!match(SEMICON)) recovery(F(_INT)_(_VOID)_(_CHAR)_(_WHILE)_(_FOR)_(_FOR)_(_DO)_(_IF)_(_SWITCH)_(_BREAK)_(_CONTINUE)_(_RETURN)_(RBRACE), SEMICON_LOST, SEMICON_WRONG);
    depth--;
}

/**
** <def> ->ID <idtail> |MUL ID <init><deflist>
* first(init) first(idtail&& init)
*/
void Parser::def(bool ext, _TokenType _type)
{
    depth++;
    data.push_back(new DrawTreeData(drawCol, depth, (char*)__FUNCTION__));
    string name = "";
    if (F(ID))
    {
        //for(int i=0; i<depth+4; i++) cout<<"  ";
       // cout<<look->toString()+" matching success"<<endl;
        name = ((Id*)look)->name;
        //**< for debug */cout<<name<<endl;
        mov();
        idtail(ext, _type, false, name);
    }
    else if (match(TIMES))
    {
        if (F(ID))
        {
            //for(int i=0; i<depth+4; i++) cout<<"  ";
            //cout<<look->toString()+" matching success"<<endl;
            name = ((Id*)look)->name;
            mov();
        }
        else recovery(F(SEMICON)_(COMMA)_(ASSIGN), ID_LOST, ID_WRONG);
        symtab->addVar(init(ext, _type, true, name));
        deflist(ext, _type);

    }
    else recovery(F(SEMICON)_(COMMA)_(ASSIGN)_(LBRACK)_(LPAREN), ID_LOST, ID_WRONG);
    depth--;
}
/**
** <idtail> -><varrdef><deflist> |LPAREN <para> RPAREN <funtail>
* first(funtail)
*/

void Parser::idtail(bool ext, _TokenType _type, bool ptr, string name)
{
    depth++;
    data.push_back(new DrawTreeData(drawCol, depth, (char*)__FUNCTION__));
    if (match(LPAREN))
    {
        symtab->enter();
        vector<Var*> paraList;
        drawCol.push_back(depth);
        para(paraList);
        if (!match(RPAREN)) recovery(F(SEMICON)_(LBRACE), RPAREN_LOST, RPAREN_WRONG);
        Fun* fun = new Fun(ext, _type, name, paraList);
        //symtab->curFun = fun;
        drawCol.pop_back();
        funtail(fun);
        symtab->leave();

    }
    else
    {
        symtab->addVar(varrdef(ext, _type, false, name));
        deflist(ext, _type);
    }
    depth--;
}

/**
** <funtail>-> SEMICON|<block>
*
*/
void Parser::funtail(Fun* fun)
{
    depth++;
    data.push_back(new DrawTreeData(drawCol, depth, (char*)__FUNCTION__));
    if (match(SEMICON))
    {
        symtab->decFun(fun);
    }
    else
    {
        symtab->defFun(fun);
        block();
        symtab->endDefFun();
    }
    depth--;
}

/**
** <paradata> ->TIMES ID|ID <paradatatail>
* follow(paradata)
*/
Var* Parser::paradata(_TokenType _type)
{
    depth++;
    data.push_back(new DrawTreeData(drawCol, depth, (char*)__FUNCTION__));
    string name = "";
    if (F(ID))
    {
        name = ((Id*)look)->name;
        Var* result = paradatatail(_type, name);
        result->isPara = true;
        symtab->addVar(result);
        mov();
        depth--;
        return result;
    }
    else if (match(TIMES))
    {
        if (F(ID)) {
            name = ((Id*)look)->name;
            Var* result = new Var(symtab->scopePath, false, _type, name, true, false, 0, true, NULL, false);
            result->isPara = true;
            symtab->addVar(result);
            mov();
            depth--;
            return result;
        }
        else recovery(F(RPAREN)_(COMMA), ID_LOST, ID_WRONG);
    }
    else recovery(F(RPAREN)_(COMMA), ID_LOST, ID_WRONG);
    depth--;
}

/**
** <paradatatail> -> [NUM]|空
* follow(paradatatail) 不需要考虑空,后续程序会发现错误？
*/
Var* Parser::paradatatail(_TokenType _type, string name)
{
    depth++;
    data.push_back(new DrawTreeData(drawCol, depth, (char*)__FUNCTION__));
    if (match(LBRACK))
    {
        //if(!match(NUM))recovery(F(RBRACK),NUM_LOST,NUM_WRONG);
        if (F(NUM)) mov();
        else if (!match(RBRACK)) recovery(F(RPAREN)_(COMMA), RBRACK_LOST, RBRACK_WRONG);
        depth--;
        Var* temp = new Var(symtab->scopePath, false, _type, name, false, true, 1, false, NULL, false);
        temp->isPara = true;
        return temp;
    }
    depth--;
    Var* temp = new Var(symtab->scopePath, false, _type, name, false, false, 0, true, NULL, false);
    temp->isPara = true;
    return temp;
}

/**
** <paralist> ->COMMA <type><paradata><paralist>|kong
*
*/
void Parser::paralist(vector<Var*>& result)
{
    depth++;
    data.push_back(new DrawTreeData(drawCol, depth, (char*)__FUNCTION__));
    if (match(COMMA))
    {
        drawCol.push_back(depth);
        _TokenType temp = type();
        Var* val = paradata(temp);
        result.push_back(val);
        drawCol.pop_back();
        paralist(result);
    }
    depth--;
}

/**
** <para> -><type><paradata><paralist>|kong
*
*/
void Parser::para(vector<Var*>& paraList)
{
    depth++;
    data.push_back(new DrawTreeData(drawCol, depth, (char*)__FUNCTION__));
    if (look->type == RPAREN) { depth--; return; }
    drawCol.push_back(depth);
    _TokenType tmp = type();
    Var* rel = paradata(tmp);
    //cout<<rel->name<<" "<<rel->offset<<endl;
    paraList.push_back(rel);
    drawCol.pop_back();
    paralist(paraList);
    depth--;
}

/**
** <block> ->{ <subprogram>}
* first(subprogram) follow(block)
*/
void Parser::block()
{
    depth++;
    data.push_back(new DrawTreeData(drawCol, depth, (char*)__FUNCTION__));
    if (!match(LBRACE)) recovery(F(_INT)_(_VOID)_(_CHAR)_(_WHILE)_(_FOR)_(_FOR)_(_DO)_(_IF)_(_SWITCH)_(_BREAK)_(_CONTINUE)_(_RETURN)_(RBRACE), LBRACE_LOST, LBRACE_WRONG);
    subprogram();
    if (!match(RBRACE)) recovery(F(_INT)_(_VOID)_(_CHAR)_(_WHILE)_(_FOR)_(_FOR)_(_DO)_(_IF)_(_SWITCH)_(_BREAK)_(_CONTINUE)_(_RETURN)_(END), RBRACE_LOST, RBRACE_WRONG);
    depth--;
}


/**
** <subprogram> -><localdef><subprogram>
                    |<statement><subprogram>
                    |kong
*
*/
void Parser::subprogram()
{
    depth++;
    data.push_back(new DrawTreeData(drawCol, depth, (char*)__FUNCTION__));
    if (F(RBRACE)) { depth--; return; }
    else if (F(_INT)_(_VOID)_(_CHAR))
    {
        drawCol.push_back(depth);
        localdef(false, look->type);
        drawCol.pop_back();
        subprogram();
    }
    else if (F(_WHILE)_(_FOR)_(_FOR)_(_DO)_(_IF)_(_SWITCH)_(_BREAK)_(_CONTINUE)_(_RETURN)_(ID)_(_PRINTF)_(_WRITE)_(_READ)_(TIMES)_(BIT_AND)_(INC)_(DEC)_(LPAREN)_(NUM)_(CH)_(STR))
    {
        drawCol.push_back(depth);
        statement();
        drawCol.pop_back();
        subprogram();
    }
    depth--;
}

/**
** <localdef> -><type><defdata><deflist>
*
*/
void Parser::localdef(bool ext, _TokenType _type)
{
    depth++;
    data.push_back(new DrawTreeData(drawCol, depth, (char*)__FUNCTION__));
    drawCol.push_back(depth);
    type();
    defdata(ext, _type);
    drawCol.pop_back();
    deflist(ext, _type);
    depth--;
}
/**
**<assexpr> -><orexpr><asstail>
*
*/

Var* Parser::assexpr()
{
    depth++;
    data.push_back(new DrawTreeData(drawCol, depth, (char*)__FUNCTION__));
    drawCol.push_back(depth);
    Var* lval = orexpr();
    drawCol.pop_back();
    Var* temp = asstail(lval);
    depth--;
    return temp;
}

/**
**<asstail> -> ASSIGN<<orexpr><asstail>>|kong
*
*/
Var* Parser::asstail(Var*& lval)
{
    depth++;
    data.push_back(new DrawTreeData(drawCol, depth, (char*)__FUNCTION__));
    if (F(ASSIGN)_(PLUS_ASSIGN)_(MINUS_ASSIGN)_(DIV_ASSIGN)_(TIMES_ASSIGN))
    {
        drawCol.push_back(depth);
        _TokenType op = ass();
        Var* val = orexpr();
        drawCol.pop_back();
        Var* rval = asstail(val);
        if (lval != NULL && lval->literal && lval->type == STR)
        {
            SEMWARN(PTR_SEG_FAULT, lval->name);
        }
        Var* result = NULL;
        if (op == ASSIGN) result = ir->genTwoOp(lval, ASSIGN, rval);
        else if (op == PLUS_ASSIGN)  result = ir->genAdd(lval, lval, rval);
        else if (op == MINUS_ASSIGN) result = ir->genSub(lval, lval, rval);
        else if (op == TIMES_ASSIGN)  result = ir->genMul(lval, lval, rval);
        else if (op == DIV_ASSIGN)  result = ir->genDiv(lval, lval, rval);
        depth--;
        return result;
    }
    depth--;
    return lval;
}

_TokenType Parser::ass()
{
    depth++;
    data.push_back(new DrawTreeData(drawCol, depth, (char*)__FUNCTION__));
    if (F(ASSIGN)_(PLUS_ASSIGN)_(MINUS_ASSIGN)_(DIV_ASSIGN)_(TIMES_ASSIGN))
    {
        _TokenType temp = look->type;
        mov();
        depth--;
        return temp;
    }
    depth--;
}
/**
** <orexpr>-><andexpr><ortail>
*
*/
Var* Parser::orexpr()
{
    depth++;
    data.push_back(new DrawTreeData(drawCol, depth, (char*)__FUNCTION__));
    drawCol.push_back(depth);
    Var* lval = andexpr();
    drawCol.pop_back();
    Var* temp = ortail(lval);
    depth--;
    return temp;
}
/**
**
*
*/
Var* Parser::ortail(Var*& lval)
{
    depth++;
    data.push_back(new DrawTreeData(drawCol, depth, (char*)__FUNCTION__));
    if (match(LOGICAL_OR))
    {
        drawCol.push_back(depth);
        Var* val = andexpr();
        Var* result = ir->genTwoOp(lval, LOGICAL_OR, val);
        drawCol.pop_back();
        Var* rval = ortail(result);
        depth--;
        return rval;
    }
    depth--;
    return lval;
}
/**
**
*
*/
Var* Parser::andexpr()
{
    depth++;
    data.push_back(new DrawTreeData(drawCol, depth, (char*)__FUNCTION__));
    drawCol.push_back(depth);
    Var* lval = cmpexpr();
    drawCol.pop_back();
    Var* temp = andtail(lval);
    depth--;
    return temp;
}
Var* Parser::andtail(Var*& lval)
{
    depth++;
    data.push_back(new DrawTreeData(drawCol, depth, (char*)__FUNCTION__));
    if (match(LOGICAL_AND))
    {
        drawCol.push_back(depth);

        Var* val = cmpexpr();
        Var* result = ir->genTwoOp(lval, LOGICAL_AND, val);
        drawCol.pop_back();
        Var* rval = andtail(result);
        depth--;
        return rval;
    }
    depth--;
    return lval;
}
/**
**
*
*/
Var* Parser::cmpexpr()
{
    depth++;
    data.push_back(new DrawTreeData(drawCol, depth, (char*)__FUNCTION__));
    drawCol.push_back(depth);
    Var* lval = aloexpr();
    drawCol.pop_back();
    Var* temp = cmptail(lval);
    depth--;
    return temp;
}
/**
**
*
*/
Var* Parser::cmptail(Var*& lval)
{
    depth++;
    data.push_back(new DrawTreeData(drawCol, depth, (char*)__FUNCTION__));
    if (F(GT)_(GE)_(LT)_(LE)_(EQU)_(NEQU))
    {
        drawCol.push_back(depth);
        _TokenType op = cmps();
        Var* val = aloexpr();
        Var* result = ir->genTwoOp(lval, op, val);
        drawCol.pop_back();
        Var* rval = cmptail(result);
        //cout<<lval->name<<lval->type<<lval->isBase()<<endl;
        //cout<<rval->name<<rval->type<<rval->isBase()<<endl;

        depth--;
        return rval;
    }
    depth--;
    return lval;

}
/**
**
*
*/
_TokenType Parser::cmps()
{
    depth++;
    data.push_back(new DrawTreeData(drawCol, depth, (char*)__FUNCTION__));
    if (F(GT)_(GE)_(LT)_(LE)_(EQU)_(NEQU))
    {
        //for(int i=0; i<depth+4; i++) cout<<"  ";
       // cout<<look->toString()+" matching success"<<endl;
        _TokenType temp = look->type;
        mov();
        depth--;
        return temp;
    }
    depth--;
}
/**
**
*
*/
Var* Parser::aloexpr()
{
    depth++;
    data.push_back(new DrawTreeData(drawCol, depth, (char*)__FUNCTION__));
    drawCol.push_back(depth);
    Var* lval = item();
    drawCol.pop_back();
    Var* temp = alotail(lval);
    depth--;
    return  temp;
}
/**
**
*
*/
Var* Parser::alotail(Var*& lval)
{
    depth++;
    data.push_back(new DrawTreeData(drawCol, depth, (char*)__FUNCTION__));
    //if(F(LOGICAL_AND)_(LOGICAL_OR)_(ASSIGN)_(GT)_(GE)_(LT)_(LE)_(EQU)_(NEQU)_(RPAREN)_(RBRACK)_(SEMICON)) return;
    if (F(PLUS)_(MINUS))
    {
        drawCol.push_back(depth);
        _TokenType type = adds();
        Var* val = item();
        Var* result = ir->genTwoOp(lval, type, val);
        drawCol.pop_back();
        Var* rval = alotail(result);
        depth--;
        return rval;
    }
    depth--;
    return lval;
}
/**
**
*
*/
_TokenType Parser::adds()
{
    depth++;
    data.push_back(new DrawTreeData(drawCol, depth, (char*)__FUNCTION__));
    if (F(PLUS)_(MINUS))
    {
        // for(int i=0; i<depth+4; i++) cout<<"  ";
         //cout<<look->toString()+" matching success"<<endl;
        _TokenType temp = look->type;
        mov();
        depth--;
        return temp;
    }
    depth--;
}
/**
**
*
*/
Var* Parser::item()
{
    depth++;
    data.push_back(new DrawTreeData(drawCol, depth, (char*)__FUNCTION__));
    drawCol.push_back(depth);
    Var* lval = factor();
    drawCol.pop_back();
    Var* temp = itemtail(lval);
    depth--;
    return temp;
}
/**
**
*
*/
Var* Parser::itemtail(Var*& lval)
{
    depth++;
    data.push_back(new DrawTreeData(drawCol, depth, (char*)__FUNCTION__));
    // if(F(LOGICAL_AND)_(LOGICAL_OR)_(ASSIGN)_(GT)_(GE)_(LT)_(LE)_(EQU)_(NEQU)_(PLUS)_(MINUS)_(RPAREN)_(RBRACK)_(SEMICON)) return;
    if (F(TIMES)_(DIV)_(MOD))
    {
        drawCol.push_back(depth);
        _TokenType type = muls();
        Var* val = factor();
        Var* result = ir->genTwoOp(lval, type, val);
        drawCol.pop_back();
        Var* rval = itemtail(result);
        depth--;
        return rval;
    }
    depth--;
    return lval;

}
/**
**
*
*/
_TokenType Parser::muls()
{
    depth++;
    data.push_back(new DrawTreeData(drawCol, depth, (char*)__FUNCTION__));
    if (F(TIMES)_(DIV)_(MOD))
    {
        _TokenType temp = look->type;
        mov();
        depth--;
        return temp;
    }
    depth--;

}
/**
**
*
*/
Var* Parser::factor()
{
    depth++;
    data.push_back(new DrawTreeData(drawCol, depth, (char*)__FUNCTION__));
    if (F(BIT_NOT)_(MINUS)_(BIT_AND)_(TIMES)_(INC)_(DEC))
    {
        drawCol.push_back(depth);
        _TokenType type = lop();
        drawCol.pop_back();
        Var* val = factor();
        Var* result = ir->genOneOpLeft(type, val);
        depth--;
        return result;
    }
    else
    {
        Var* temp = val();
        depth--;
        return temp;
    }

}
/**
**
*
*/
_TokenType Parser::lop()
{
    depth++;
    data.push_back(new DrawTreeData(drawCol, depth, (char*)__FUNCTION__));
    if (F(BIT_NOT)_(MINUS)_(BIT_AND)_(TIMES)_(INC)_(DEC))
    {
        //for(int i=0; i<depth+4; i++) cout<<"  ";
        //cout<<look->toString()+" matching success"<<endl;
        _TokenType temp = look->type;
        mov();
        depth--;
        return temp;
    }
    depth--;
}
/**
**
*
*/
Var* Parser::val()
{
    depth++;
    data.push_back(new DrawTreeData(drawCol, depth, (char*)__FUNCTION__));
    drawCol.push_back(depth);
    Var* val = elem();
    drawCol.pop_back();
    _TokenType tmp = rop();
    if (tmp == INC || tmp == DEC)
    {
        Var* result = ir->genOneOpRight(val, tmp);
        depth--;
        return result;
    }

    else
    {
        depth--;
        return val;
    }
}
/**
**
*
*/
_TokenType Parser::rop()
{
    depth++;
    data.push_back(new DrawTreeData(drawCol, depth, (char*)__FUNCTION__));
    if (F(INC)_(DEC))
    {
        //for(int i=0; i<depth+4; i++) cout<<"  ";
       // cout<<look->toString()+" matching success"<<endl;
        _TokenType temp = look->type;
        mov();
        depth--;
        return temp;
    }
    depth--;
    return (_TokenType)NULL;
}
/**
**
*
*/
Var* Parser::elem()
{
    depth++;
    data.push_back(new DrawTreeData(drawCol, depth, (char*)__FUNCTION__));
    if (F(ID))
    {
        //for(int i=0; i<depth+4; i++) cout<<"  ";
        //cout<<look->toString()+" matching success"<<endl;
        string name = ((Id*)look)->name;
        mov();
        Var* temp = idexpr(name);
        depth--;
        return temp;
    }
    else if (match(LPAREN))
    {
        Var* result = expr();

        if (!match(RPAREN)) recovery(F(INC)_(DEC), RPAREN_LOST, RPAREN_WRONG);
        depth--;
        return result;
    }
    else
    {
        Var* temp = literal();
        depth--;
        return temp;
    }
}
/**
**
*
*/
Var* Parser::idexpr(string name)
{
    depth++;
    data.push_back(new DrawTreeData(drawCol, depth, (char*)__FUNCTION__));
    if (match(LBRACK))
    {
        Var* val = symtab->getVar(name);
        Var* index = expr();
        if (!match(RBRACK)) recovery(F(INC)_(DEC)_(ASSIGN), RBRACK_LOST, RBRACK_WRONG);
        Var* result = ir->genArray(val, index);
        depth--;
        return result;
    }
    else if (match(LPAREN))
    {
        //symtab->ShowFunTab();
        vector<Var*> args = realarg();
        Fun* fun = symtab->getFun(name, args);

        if (!match(RPAREN)) recovery(F(INC)_(DEC)_(ID)_(LPAREN)_(PLUS)_(MINUS)_(TIMES)_(DIV)_(PLUS_ASSIGN)_(MINUS_ASSIGN)_(TIMES_ASSIGN)_(DIV_ASSIGN)_(LOGICAL_AND)_(LOGICAL_OR)_(ASSIGN)_(SEMICON)_(GE)_(GT)_(LE)_(LT)_(EQU)_(NEQU)
            , RPAREN_LOST, RPAREN_WRONG);
        /**< 解决赋值问题 */
        Var* result = ir->genCall(fun, args);
        //        for(int i=0;i<args.size();i++)
        //        {
        //            Var* temp = symtab->getVar(fun->paraVar[i]->name);
        //           // cout<<fun->paraVar[i]->name<<endl;
        //            temp->pointTo = args[args.size()-1-i]->pointTo;
        //            temp->ptr = args[args.size()-1-i]->ptr;
        //        }
        depth--;
        return result;
    }
    else
    {
        Var* val = symtab->getVar(name);
        depth--;
        return val;
    }
}
/**
**
*
*/
vector<Var*> Parser::realarg()
{
    depth++;
    data.push_back(new DrawTreeData(drawCol, depth, (char*)__FUNCTION__));

    vector<Var*> result;
    if (F(RPAREN))
    {
        depth--;
        return result;
    }
    drawCol.push_back(depth);
    Var* val = arg();
    drawCol.pop_back();
    arglist(result);
    result.push_back(val);/**< 实参倒序入栈 */
    depth--;
    return result;
}
/**
**
*
*/
void Parser::arglist(vector<Var*>& result)
{
    depth++;
    data.push_back(new DrawTreeData(drawCol, depth, (char*)__FUNCTION__));
    if (match(COMMA))
    {
        drawCol.push_back(depth);
        Var* val = arg();
        drawCol.pop_back();
        arglist(result);
        result.push_back(val);
    }
    depth--;
}
/**
**
*
*/
Var* Parser::arg()
{
    depth++;
    data.push_back(new DrawTreeData(drawCol, depth, (char*)__FUNCTION__));
    Var* val = expr();
    depth--;
    return val;
}
/**
**
*
*/
Var* Parser::literal()
{
    depth++;
    data.push_back(new DrawTreeData(drawCol, depth, (char*)__FUNCTION__));
    Var* v = NULL;
    if (F(NUM)_(CH)_(STR))
    {
        // for(int i=0; i<depth+4; i++) cout<<"  ";
         //cout<<look->toString()+" matching success"<<endl;
        v = new Var(look);
        if (F(STR)) symtab->addStr(v);
        else symtab->addVar(v);
        mov();
    }
    else recovery(F(ASSIGN)_(LOGICAL_AND)_(LOGICAL_OR)_(GE)_(GT)_(LE)_(EQU)_(NEQU)_(PLUS)_(MINUS)_(TIMES)_(DIV)_(MOD)_(INC)_(DEC)_(COMMA)_(SEMICON), LITERAL_LOST, LITERAL_WRONG);
    depth--;
    return v;
}
/**
**
*
*/
//void Parser::expr()
//{
//    cout<<"call <expr> "<<endl;
//    assexpr();
//}
Var* Parser::expr()
{
    depth++;
    data.push_back(new DrawTreeData(drawCol, depth, (char*)__FUNCTION__));
    Var* temp = assexpr();
    depth--;
    return  temp;
}



Var* Parser::altexpr()
{
    depth++;
    data.push_back(new DrawTreeData(drawCol, depth, (char*)__FUNCTION__));
    if (F(SEMICON)_(RPAREN))
    {
        depth--;
        return Var::getVoid();
    }
    Var* val = expr();
    depth--;
    return val;
}



/****
*<statement> -><altexpr> SEMICON
*               |<whilestat>|<forstat>|<dowhilestat>
                |<ifstat><switchstat>
                |_BREAK SEMICON
                |CONTINUE SEMICON
                |RETURN <altexpr> SEMICON
*/
void Parser::statement()
{
    depth++;
    data.push_back(new DrawTreeData(drawCol, depth, (char*)__FUNCTION__));
    switch (look->type)
    {
    case _WHILE:
        whilestat();
        break;
    case _FOR:
        forstat();
        break;
    case _DO:
        dowhilestat();
        break;
    case _IF:
        ifstat();
        break;
    case _SWITCH:
        switchstat();
        break;
    case _BREAK:
        // for(int i=0; i<depth+4; i++) cout<<"  ";
         //cout<<look->toString()+" matching success"<<endl;
        mov();
        if (!match(SEMICON)) recovery(F(_INT)_(_VOID)_(_CHAR)_(_WHILE)_(_FOR)_(_FOR)_(_DO)_(_IF)_(_SWITCH)_(_BREAK)_(_CONTINUE)_(_RETURN)_(RBRACE), SEMICON_LOST, SEMICON_WRONG);
        ir->genBreak();
        break;
    case _CONTINUE:
        //for(int i=0; i<depth+4; i++) cout<<"  ";
        //cout<<look->toString()+" matching success"<<endl;
        mov();
        if (!match(SEMICON)) recovery(F(_INT)_(_VOID)_(_CHAR)_(_WHILE)_(_FOR)_(_FOR)_(_DO)_(_IF)_(_SWITCH)_(_BREAK)_(_CONTINUE)_(_RETURN)_(RBRACE), SEMICON_LOST, SEMICON_WRONG);
        ir->genContinue();
        break;
    case _RETURN:
        // for(int i=0; i<depth+4; i++) cout<<"  ";
         //cout<<look->toString()+" matching success"<<endl;
        mov();
        ir->genReturn(altexpr());
        if (!match(SEMICON)) recovery(F(_INT)_(_VOID)_(_CHAR)_(_WHILE)_(_FOR)_(_FOR)_(_DO)_(_IF)_(_SWITCH)_(_BREAK)_(_CONTINUE)_(_RETURN)_(RBRACE), SEMICON_LOST, SEMICON_WRONG);
        break;
    case _PRINTF:
        printfstat();
        break;
    case _WRITE:
        writestat();
        break;
    case _READ:
        readstat();
        break;
    default:
        altexpr();
        if (!match(SEMICON)) recovery(F(_INT)_(_VOID)_(_CHAR)_(_WHILE)_(_FOR)_(_FOR)_(_DO)_(_IF)_(_SWITCH)_(_BREAK)_(_CONTINUE)_(_RETURN)_(RBRACE), SEMICON_LOST, SEMICON_WRONG);

    }
    depth--;
}

/**
*<whilestat> -> _WHILE LPAREN <altexpr> RPAREN <block>
*/
void Parser::whilestat()
{
    depth++;
    data.push_back(new DrawTreeData(drawCol, depth, (char*)__FUNCTION__));
    symtab->enter();
    InterInst* _while, * _exit;
    ir->genWhileHead(_while, _exit);
    match(_WHILE);
    if (!match(LPAREN)) recovery(F(RPAREN)_(ID)_(BIT_NOT)_(MINUS)_(BIT_AND)_(TIMES)_(INC)_(DEC)_(LPAREN)_(NUM)_(_CHAR)_(STR), LPAREN_LOST, LPAREN_WRONG);//ÈçºÎÅÐ¶Ï<altexpr>µÄfirst¼¯
    drawCol.push_back(depth);
    Var* cond = altexpr();
    ir->genWhileCond(cond, _exit);

    if (!match(RPAREN)) recovery(F(LBRACE), RPAREN_LOST, RPAREN_WRONG);//<block> first is {LBRACE}
    drawCol.pop_back();
    block();
    ir->genWhileTail(_while, _exit);
    symtab->leave();
    depth--;
}

void Parser::dowhilestat()
{
    depth++;
    data.push_back(new DrawTreeData(drawCol, depth, (char*)__FUNCTION__));
    symtab->enter();
    InterInst* _do, * _exit;
    ir->genDoWhileHead(_do, _exit);
    match(_DO);
    drawCol.push_back(depth);
    block();
    if (!match(_WHILE)) recovery(F(LPAREN), WHILE_LOST, WHILE_WRONG);
    if (!match(LPAREN)) recovery(F(ID)_(BIT_NOT)_(MINUS)_(BIT_AND)_(TIMES)_(INC)_(DEC)_(LPAREN)_(NUM)_(_CHAR)_(STR)_(SEMICON), LPAREN_LOST, LPAREN_WRONG);//not sure

    symtab->leave();
    drawCol.push_back(depth);
    Var* cond = altexpr();
    if (!match(RPAREN)) recovery(F(SEMICON), RPAREN_LOST, RPAREN_WRONG);
    if (!match(SEMICON)) recovery(F(_INT)_(_VOID)_(_CHAR)_(_WHILE)_(_FOR)_(_FOR)_(_DO)_(_IF)_(_SWITCH)_(_BREAK)_(_CONTINUE)_(_RETURN)_(RBRACE), SEMICON_LOST, SEMICON_WRONG);
    ir->genDoWhileTail(cond, _do, _exit);
    depth--;

}

void Parser::forstat()
{
    depth++;
    data.push_back(new DrawTreeData(drawCol, depth, (char*)__FUNCTION__));
    symtab->enter();
    InterInst* _for, * _exit, * _step, * _block;
    match(_FOR);
    if (!match(LPAREN)) recovery(F(ID)_(BIT_NOT)_(MINUS)_(BIT_AND)_(TIMES)_(INC)_(DEC)_(LPAREN)_(NUM)_(_CHAR)_(STR)_(SEMICON)_(_INT)_(_VOID)_(_CHAR), LPAREN_LOST, LPAREN_WRONG);
    drawCol.push_back(depth);
    forinit();
    ir->genForHead(_for, _exit);
    Var* cond = altexpr();
    ir->genForCondBegin(cond, _step, _block, _exit);
    if (!match(SEMICON)) recovery(F(ID)_(BIT_NOT)_(MINUS)_(BIT_AND)_(TIMES)_(INC)_(DEC)_(LPAREN)_(NUM)_(_CHAR)_(STR)_(SEMICON), SEMICON_LOST, SEMICON_WRONG);
    altexpr();
    if (!match(RPAREN)) recovery(F(LBRACE), RPAREN_LOST, RPAREN_WRONG);
    ir->genForCondEnd(_for, _block);
    drawCol.pop_back();
    block();
    ir->genForTail(_step, _exit);
    symtab->leave();
    depth--;
}
/**
**
*
*/
void Parser::forinit()
{
    depth++;
    data.push_back(new DrawTreeData(drawCol, depth, (char*)__FUNCTION__));
    if (F(_INT)_(_VOID)_(_CHAR)) localdef(false, look->type);
    else
    {
        altexpr();
        if (!match(SEMICON)) recovery(F(ID), SEMICON_LOST, SEMICON_WRONG);
    }
    depth--;
}

void Parser::ifstat()
{
    depth++;
    data.push_back(new DrawTreeData(drawCol, depth, (char*)__FUNCTION__));
    symtab->enter();
    InterInst* _else, * _exit;
    match(_IF);
    if (!match(LPAREN)) recovery(F(ID)_(BIT_NOT)_(MINUS)_(BIT_AND)_(TIMES)_(INC)_(DEC)_(LPAREN)_(NUM)_(_CHAR)_(STR), LPAREN_LOST, LPAREN_WRONG);
    drawCol.push_back(depth);
    Var* cond = expr();
    ir->genIFHead(cond, _else);
    if (!match(RPAREN)) recovery(F(LBRACE), RPAREN_LOST, RPAREN_WRONG);
    block();
    symtab->leave();
    if (F(_ELSE))
    {
        ir->genElseHead(_else, _exit);
        drawCol.pop_back();
        elsestat();
        ir->genElseTail(_exit);
    }
    else ir->genIFTail(_else);

    depth--;
}

void Parser::elsestat()
{
    depth++;
    data.push_back(new DrawTreeData(drawCol, depth, (char*)__FUNCTION__));
    if (match(_ELSE))
    {
        symtab->enter();
        block();
        symtab->enter();
    }
    depth--;
}

void Parser::switchstat()
{
    depth++;
    data.push_back(new DrawTreeData(drawCol, depth, (char*)__FUNCTION__));
    symtab->enter();
    InterInst* _exit;
    ir->genSwitchHead(_exit);
    match(_SWITCH);
    if (!match(LPAREN)) recovery(F(ID)_(BIT_NOT)_(MINUS)_(BIT_AND)_(TIMES)_(INC)_(DEC)_(LPAREN)_(NUM)_(_CHAR)_(STR), LPAREN_LOST, LPAREN_WRONG);
    drawCol.push_back(depth);
    Var* cond = expr();
    if (cond->isPtr) cond = ir->genAssign(cond);
    if (!match(RPAREN)) recovery(F(LBRACE), RPAREN_LOST, RPAREN_WRONG);
    if (!match(LBRACE)) recovery(F(_CASE)_(_DEFAULT), LBRACE_LOST, LBRACE_WRONG);
    drawCol.pop_back();
    casestat(cond);

    if (!match(RBRACE)) recovery(F(_INT)_(_VOID)_(_CHAR)_(_WHILE)_(_FOR)_(_FOR)_(_DO)_(_IF)_(_SWITCH)_(_BREAK)_(_CONTINUE)_(_RETURN)_(RBRACE), RBRACE_LOST, RBRACE_WRONG);
    ir->genSwitchTail(_exit);
    symtab->leave();
    depth--;
}

void Parser::casestat(Var* cond)
{
    depth++;
    data.push_back(new DrawTreeData(drawCol, depth, (char*)__FUNCTION__));

    if (match(_CASE))
    {
        InterInst* _case_exit;
        drawCol.push_back(depth);
        Var* lb = caselabel();
        ir->genCaseHead(cond, lb, _case_exit);
        if (!match(COLON)) recovery(F(_INT)_(_VOID)_(_CHAR)_(_WHILE)_(_FOR)_(_FOR)_(_DO)_(_IF)_(_SWITCH)_(_BREAK)_(_CONTINUE)_(_RETURN)_(RBRACE), COLON_LOST, COLON_WRONG);
        symtab->enter();
        subprogram();
        symtab->leave();
        ir->genCaseTail(_case_exit);
        drawCol.pop_back();
        casestat(cond);
    }
    else if (match(_DEFAULT))
    {
        if (!match(COLON)) recovery(F(_INT)_(_VOID)_(_CHAR)_(_WHILE)_(_FOR)_(_FOR)_(_DO)_(_IF)_(_SWITCH)_(_BREAK)_(_CONTINUE)_(_RETURN)_(RBRACE), COLON_LOST, COLON_WRONG);
        symtab->enter();
        subprogram();
        symtab->leave();
    }
    depth--;
}
Var* Parser::caselabel()
{
    depth++;
    data.push_back(new DrawTreeData(drawCol, depth, (char*)__FUNCTION__));
    //data.push_back(new DrawTreeData(drawCol,depth,(char*)__FUNCTION__));
    Var* temp = literal();
    depth--;
    return temp;
}
void Parser::DrawTree(bool outOpt)
{
    streambuf* coutbackup;
    ofstream fout(parseFile);
    if (outOpt == 1)
        coutbackup = cout.rdbuf(fout.rdbuf());
    for (int i = 0; i < data.size(); i++)
    {
        if (data[i]->depth == -1) {
            cout << "---->\"" << data[i]->funName << "\" ";
            if (i < data.size() - 1 && data[i + 1]->depth != -1) cout << endl;
            continue;
        }
        vector<int>& temp = data[i]->drawCol;
        //cout<<data[i]->depth<<endl;
        int number = temp.back();/**< 如果size()==1 则number为0 */
        if (temp.size() == 1) {
            while (number < data[i]->depth - 1) {
                cout << " "; number++;
            }
        }
        else {
            for (int j = 1; j < temp.size(); j++)/**< 数组元素中间的空格以及竖线 */
            {
                //cout<<temp[j-1]<<endl;
                int a = temp[j - 1];/**< 画空格 */
                while (a < temp[j]) {
                    cout << " "; a++;
                }
                cout << "|";/**< 画竖线 */
            }
            while (number < data[i]->depth - 1) {/**< 数组元素之外的空格 */
                cout << " "; number++;
            }
        }
        if (temp.back() + 1 == data[i]->depth)cout << "_";
        else cout << "|_";
        cout << "<" << data[i]->funName << ">";
        if (i < data.size() - 1 && data[i + 1]->depth != -1) cout << endl;
    }
    if (outOpt == 1) {
        cout.rdbuf(coutbackup);
    }
}

/**< <printf>->(STR);  //全部产生终结符 */
void Parser::printfstat()/**< printf */
{
    depth++;
    data.push_back(new DrawTreeData(drawCol, depth, (char*)__FUNCTION__));
    match(_PRINTF);
    if (!match(LPAREN))
        recovery(F(RPAREN)_(ID)_(BIT_NOT)_(MINUS)_(BIT_AND)_(TIMES)_(INC)_(DEC)_(LPAREN)_(NUM)_(_CHAR)_(STR), LPAREN_LOST, LPAREN_WRONG);
    Var* v = NULL;
    if (F(STR))
    {
        v = new Var(look);
        if (look->toString().size() > 1)
            symtab->addStr(v);
        mov();
    }
    else
        recovery(F(RPAREN), LITERAL_LOST, LITERAL_WRONG);
    if (!match(RPAREN))
        recovery(F(SEMICON), RPAREN_LOST, RPAREN_WRONG);
    if (!match(SEMICON))
        recovery(F(_INT)_(_VOID)_(_CHAR)_(_WHILE)_(_FOR)_(_FOR)_(_DO)_(_IF)_(_SWITCH)_(_BREAK)_(_CONTINUE)_(_RETURN)_(END), SEMICON_LOST, SEMICON_WRONG);
    if (v != NULL && v->strVal.size() == 1) IOflag.push_back(1);
    else if (v != NULL && v->strVal.size() > 1 && v->strVal[v->strVal.size() - 1] == '\n') IOflag.push_back(2);
    else if (v != NULL && v->strVal.size() > 1 && v->strVal[v->strVal.size() - 1] != '\n') IOflag.push_back(3);
    ir->genPrintf(v);
    if (!symtab->curFun->IODepthflag) {
        symtab->curFun->IODepthflag = true;
    }
    depth--;
}
/**< <write>->(<arg>); */
void Parser::writestat()/**< 输出单个变量 */
{
    depth++;
    data.push_back(new DrawTreeData(drawCol, depth, (char*)__FUNCTION__));
    match(_WRITE);
    if (!match(LPAREN))
        recovery(F(RPAREN)_(ID)_(BIT_NOT)_(MINUS)_(BIT_AND)_(TIMES)_(INC)_(DEC)_(LPAREN)_(NUM)_(_CHAR)_(STR), LPAREN_LOST, LPAREN_WRONG);
    Var* v = arg();
    if (!match(RPAREN))
        recovery(F(SEMICON), RPAREN_LOST, RPAREN_WRONG);
    if (!match(SEMICON))
        recovery(F(_INT)_(_VOID)_(_CHAR)_(_WHILE)_(_FOR)_(_FOR)_(_DO)_(_IF)_(_SWITCH)_(_BREAK)_(_CONTINUE)_(_RETURN)_(END), SEMICON_LOST, SEMICON_WRONG);
    Var* Vtemp = NULL;
    if (v->type == _INT)
    {
        Str* ss = new Str("%d");
        Vtemp = new Var((Token*)ss);
        symtab->addStr(Vtemp);
        IOflag.push_back(3);
    }
    else if (v->type == _CHAR)
        IOflag.push_back(1);
    ir->genWrite(v, Vtemp);
    if (!symtab->curFun->IODepthflag) {
        symtab->curFun->IODepthflag = true;
    }
    depth--;
}
/**< <read> -> read(ID);|read(ID[NUM]);|read(*ID);*/
void Parser::readstat()/**< 输入单个变量 */
{
    depth++;
    data.push_back(new DrawTreeData(drawCol, depth, (char*)__FUNCTION__));
    match(_READ);
    if (!match(LPAREN))
        recovery(F(RPAREN)_(ID)_(TIMES), LPAREN_LOST, LPAREN_WRONG);
    Var* result = NULL;
    string name = "";
    Var* Vtemp = NULL;
    if (F(ID))
    {
        name = ((Id*)look)->name;
        mov();
        if (match(LBRACK))
        {
            Var* val = symtab->getVar(name);
            Var* index = expr();
            if (!match(RBRACK)) recovery(F(RPAREN), RBRACK_LOST, RBRACK_WRONG);
            result = ir->genArray(val, index);
        }
        else result = symtab->getVar(name);
        Var* val = symtab->getVar(name);
        if (val->type == _INT) {
            Str* ss = new Str("%d");
            Vtemp = new Var((Token*)ss);
            symtab->addStr(Vtemp);
        }
        else if (val->type == _CHAR && !val->isBase())
        {
            Str* ss = new Str("%s");
            Vtemp = new Var((Token*)ss);
            symtab->addStr(Vtemp);
        }
        else if (val->type == _CHAR && val->isBase())
        {
            Str* ss = new Str("%c");
            Vtemp = new Var((Token*)ss);
            symtab->addStr(Vtemp);
        }
    }
    else if (match(TIMES))
    {
        if (!F(ID)) recovery(F(RPAREN)_(SEMICON), ID_LOST, ID_WRONG);
        else {
            name = ((Id*)look)->name;
            Var* val = symtab->getVar(name);
            mov();
            result = ir->genPtr(val);
        }
        Var* val = symtab->getVar(name);
        if (val->type == _INT) {
            Str* ss = new Str("%d");
            Vtemp = new Var((Token*)ss);
            symtab->addStr(Vtemp);
        }
        else if (val->type == _CHAR)
        {
            Str* ss = new Str("%c");
            Vtemp = new Var((Token*)ss);
            symtab->addStr(Vtemp);
        }
    }
    else recovery(F(RPAREN)_(COMMA), ID_LOST, ID_WRONG);
    if (!match(RPAREN))
        recovery(F(SEMICON), RPAREN_LOST, RPAREN_WRONG);
    if (!match(SEMICON))
        recovery(F(_INT)_(_VOID)_(_CHAR)_(_WHILE)_(_FOR)_(_FOR)_(_DO)_(_IF)_(_SWITCH)_(_BREAK)_(_CONTINUE)_(_RETURN)_(END), SEMICON_LOST, SEMICON_WRONG);
    IOflag.push_back(4);
    ir->genRead(result, Vtemp);
    if (!symtab->curFun->IODepthflag) {
        symtab->curFun->IODepthflag = true;
    }
    depth--;
}
