; **************************************************************************
; * *
; * Written by Mr. YanJingcun 
; * *
; * [Oct 09, 2021]
; * *
; * Function: 
; *           某班有 20 个同学的微机原理成绩存放在 LIST 开始的单元中，要求编程先
; *           按从高到低 的次序排列好，再求出总分，并将其存放到 SUM 开始的单元中。
; *           其中排序和求合用子程序完成。
; * *
; **************************************************************************

DATA    SEGMENT                          ;数据段
  LIST DW 64,44,61,43,5,57,50,54,9,45,34,94,21,42,52,7,50,54,9,45
  SUM  DW 00H ;总分
  COUNT EQU ($-LIST)/2 ; 数组的长度
DATA    ENDS

CODE    SEGMENT                          ;代码段
        ASSUME CS:CODE,DS:DATA  ;2个段寄存器分别与哪些段有关

START:  MOV   AX,DATA
        MOV   DS,AX                      ;设置数据段

        CALL SORT_SCORE

        CALL SUM_SCORE

        MOV AX,4C00H
        INT 21H

;  成绩排序子程序
SORT_SCORE PROC NEAR
        
           MOV  CX,COUNT ; CX比较轮数

    LOOP1: MOV  DX,CX ; dx是大循环次数
           MOV  BX,0  ; 地址指针 i
           
           ; 每次循环归位一个最小的数

    LOOP2: MOV  AX,LIST[BX] ; i指向的数字
           CMP  AX,LIST[BX+2] ; num[i]  num[i+1]  相比
           JAE  NO_CHANGE ;  num[i] >= num[i+1]，无变化

           ; if(num[i] < num[i+1])
           ; ax = num[i]; num[i] = num[i + 1]; num[i + 1] = ax
           XCHG AX,LIST[BX+2] 
           ; 此时，ax存放的是较小的数，list[bx+2] 存放的是较大的数

           ; ax 存放的是较小的数，移动到list[bx]中，完成交换
           MOV  LIST[BX],AX; 

    NO_CHANGE:
           ; 因为DW，所以+ 2
           ADD  BX,2
           LOOP LOOP2
           ; 小循环结束
           MOV  CX,DX 
           LOOP LOOP1
           
           RET
SORT_SCORE ENDP

;  成绩求和子程序
SUM_SCORE  PROC NEAR

        MOV  CX,COUNT ; CX循环的次数
        MOV  AX,0 ;使用AX作为sum临时存放位置
        MOV  BX,0 ; 初始化BX

    LOOP_SUM: 
        ADD  AX,LIST[BX]
        ADD  BX,2H

    LOOP LOOP_SUM
        ; 循环结束
        MOV  SUM,AX
        RET
SUM_SCORE  ENDP

CODE    ENDS                              ;代码段结束
        END START                         ;源代码结束
