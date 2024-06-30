; **************************************************************************
; * *
; * Written by Mr. YanJingcun *
; * *
; * [Oct 09, 2021]
; * *
; * Function: 从键盘输入一个十进制数字 0-9，查表求键入数字的七段代码，存入 DL 中，并在键入 
; *           数字之前，显示提示信息“Please input a number:”。*
; * *
; **************************************************************************

DATA    SEGMENT                          ;数据段
  TIPS  DB 'Please input a number(0 - 9):',0DH,0AH,'$' ; 提示输入数字
  ; 数字 0-9 的七段代码表
  TABLE DB  40H, 79H, 24H, 30H, 19H, 12H, 02H, 78, 00H, 18H

DATA    ENDS

STACK   SEGMENT PARA STACK 'STACK'       ;堆栈段
STACK   ENDS

CODE    SEGMENT                          ;代码段
        ASSUME CS:CODE,DS:DATA,SS:STACK  ;3个段寄存器分别与哪些段有关
START:  MOV   AX,DATA
        MOV   DS,AX                      ;设置数据段

        ;输出提示信息
        MOV  DX, OFFSET TIPS
        MOV  AH, 9H
        INT  21H

        ; 用户输入数字
        MOV  AH, 01
        INT  21H    ;AL 是输入的数字的ASCII码
        AND  AL,0FH   ; 得到输入的数字的数字值，也就是数组的下index

        ; 查表求值
        MOV  BX, OFFSET TABLE ; BX 指向表头
        MOV  AH, 0  ; AX高字节清0
        ADD  BX, AX 
        MOV  DL,[BX] ;存入DL中

        ; 返回DOS
        MOV AX,4C00H
        INT 21H

CODE    ENDS                              ;代码段结束
        END START                         ;源代码结束