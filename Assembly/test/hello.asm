; **************************************************************************
; * *
; * Written by Mr. YanJingcun *
; * *
; * [Oct 09, 2021]
; * *
; * Function: *
; *           program_function*
; * *
; **************************************************************************

DATA    SEGMENT                          ;数据段

DATA    ENDS

STACK   SEGMENT PARA STACK 'STACK'       ;堆栈段

STACK   ENDS

CODE    SEGMENT                          ;代码段
				ASSUME CS:CODE,DS:DATA,SS:STACK  ;3个段寄存器分别与哪些段有关
START:  
				MOV DL, 'o'
				MOV AH, 02H
				INT 21H
				MOV  AX, 4C00H
				INT  21H
CODE    ENDS                               ;代码段结束
				END START                          ;源代码结束