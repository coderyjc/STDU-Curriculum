#pragma once
#ifndef OPERATOR_H_INCLUDED
#define OPERATOR_H_INCLUDED
#include<string>
using namespace std;
static string OperatorArray[] = {
    "op_nop",
    "op_dec",
    "op_entry","op_exit",
    "op_as",
    "op_add","op_sub","op_mul","op_div","op_mod",
    "op_neg",
    "op_gt","op_ge","op_lt","op_le","op_equ","op_ne",
    "op_not",
    "op_and","op_or",
    "op_lea","op_set","op_get","op_jmp","op_jt","op_jf","op_jne","op_arg",
    "op_proc","op_call","op_ret","op_retv",
    "op_printf","op_read","op_write","op_asp"
};
enum Operator
{
    OP_NOP,
    OP_DEC,
    OP_ENTRY, OP_EXIT,
    OP_AS,
    OP_ADD, OP_SUB, OP_MUL, OP_DIV, OP_MOD,
    OP_NEG,
    OP_GT, OP_GE, OP_LT, OP_LE, OP_EQU, OP_NE,
    OP_NOT,
    OP_AND, OP_OR,
    OP_LEA,
    OP_SET,
    OP_GET,
    OP_JMP,
    OP_JT,
    OP_JF,
    OP_JNE,
    OP_ARG,
    OP_PROC,
    OP_CALL,
    OP_RET,
    OP_RETV,
    OP_PRINTF,
    OP_READ,
    OP_WRITE,
    OP_ASP
};

#endif // OPERATOR_H_INCLUDED
