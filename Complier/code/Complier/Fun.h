#pragma once
#ifndef FUN_H
#define FUN_H
#include"InterInst.h"
#include"Lex.h"
#include"global.h"
class Fun
{
public:
    Fun(bool ext, _TokenType type, string n, vector<Var*>& paraList);
    Fun();

    bool externed;
    bool IODepthflag;
    _TokenType type;
    string name;
    vector<Var*> paraVar;/**< 形参变量列表 */
    int maxDepth;/**< 栈的最大深度，不累计 */
    int curEsp;/**< 当前栈指针位置esp */
    vector<int> ScopeEsp;/**<动态记录每个作用域的大小  */
    vector<InterInst*> interCode;/**<   目标代码*/
    InterInst* returnPoint;/**< 返回点位置 */
    void enterScope();
    void leaveScope();
    void locate(Var* var);
    bool match(Fun* fun);
    bool match(vector<Var*>& args);
    void define(Fun* def);
protected:

private:
};

#endif // FUN_H
