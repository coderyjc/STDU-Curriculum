; **************************************************************************
; * *
; * Written by Mr. YanJingcun *
; * *
; * [Nov 21, 2021]
; * *
; * Function: *
; *           某班有7个同学成绩低于80分，分数存在ARRAY数组中，编程完成以下题目：
; *           1. 给每个人+5分，结果存在NEW数组中
; *           2. 总分存到 SUM 中
; * * 
; **************************************************************************

DATA    SEGMENT                          ;数据段
ARRAY   DB  74, 54, 21, 65, 55, 15, 23
NEW     DB  7 DUP(0)
SUM     DW  0
DATA    ENDS

CODE    SEGMENT                          ;代码段
        ASSUME CS:CODE,DS:DATA  ;3个段寄存器分别与哪些段有关
START:  MOV   AX,DATA
        MOV   DS,AX                      ;设置数据段

;========================= +5分 核心代码===============================

        LEA   SI, ARRAY
        LEA   DI, NEW
        MOV   CX, 7
NEXT:   MOV   AL, [SI]
        ADD   AL, 5
        MOV   [DI],AL
        INC   SI
        INC   DI
        LOOP  NEXT

;========================= +5分 核心代码===============================

;========================= 总分 核心代码===============================

        LEA   SI, ARRAY
        CLC
        MOV   CX, 7
NEXT1:  MOV   AL, [SI]
        MOV   AH, 0
        ADC   SUM, AX
        INC   SI
        LOOP  NEXT1

;========================= 总分 核心代码===============================

        MOV  AX,4C00H
        INT  21H
CODE    ENDS                              ;代码段结束
        END START                         ;源代码结束