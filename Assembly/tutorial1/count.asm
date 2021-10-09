; **************************************************************************
; * *
; * Written by Mr. YanJingcun *
; * *
; * [Oct 09, 2021]
; * *
; * Function: 
; *           在 TABLE 开始的内存字节单元中，存入了 10 个带符号数，
; *           试编写完整的汇编语言程序 统计其中的正数、负数和零的个数。
; * *
; **************************************************************************

DATA    SEGMENT                          ;数据段

DATA    ENDS

STACK   SEGMENT PARA STACK 'STACK'       ;堆栈段

STACK   ENDS

CODE    SEGMENT                          ;代码段
        ASSUME CS:CODE,DS:DATA,SS:STACK  ;3个段寄存器分别与哪些段有关
START:  
        
        MOV  AX,4C00H
        INT  21H
CODE    ENDS                               ;代码段结束
        END START                          ;源代码结束