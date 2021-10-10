; **************************************************************************
; * *
; * Written by Mr. YanJingcun *
; * *
; * [Oct 09, 2021]
; * *
; * Function: *
; *          在 TABLE 开始的内存字节单元中，存入了 10 个带符号数，
; *          试编写完整的汇编语言程序 统计其中的正数、负数和零的个数。*
; * *
; **************************************************************************

DATA SEGMENT
    TABLE DB 0A2H,51H,63H,21H,25H,0C5H,0D1H,98H,08H,00H
    PLUS  DB 00H
    ZERO  DB 00H
    NEGE  DB 00H
    TIPS  DB 'The number of positive, negetive and 0 is : $'
DATA ENDS

CODE SEGMENT
			ASSUME CS:CODE,DS:DATA
START:
MOV AX,DATA
MOV DS,AX

MOV CX,10 ; 初始化CX用来进行 loop 的计数
LEA BX,TABLE ; BX 指向 MEM数组的基地址
DEC BX ; BX 指向 MEM 数组的基地址的前一位置

JUDGE:
		INC BX ; BX 后移
		MOV DX,[BX] ; BX 指向的数值赋值给 DX
		TEST DX,0FFH ; 和 0 相比
		JZ NUM_0 
		TEST DX,80H ; 和 1 相比 
		JZ PLUS_NUM
		INC NEGE

MAIN:
		; 进行循环
		LOOP JUDGE
		
    ; 输出提示信息
    MOV  DX, OFFSET TIPS
    MOV  AH, 9H
    INT  21H
      
		; 打印正数个数
		MOV DL,PLUS
		ADD DL,30H
		MOV AH,02H
		INT 21H

    ; 分隔符
    MOV  DL, '-'
    MOV  AH, 02H
    INT  21H

		; 打印负数个数
		MOV DL,NEGE
		ADD DL,30H
		INT 21H

		; 分隔符
    MOV  DL, '-'
    MOV  AH, 02H
    INT  21H
		
    ; 打印 0 个数
		MOV DL,ZERO
		ADD DL,30H
		INT 21H
		
		; 返回DOS
		MOV AH,4CH
		INT 21H

NUM_0:
		INC ZERO
		JMP MAIN

PLUS_NUM:
		INC PLUS
		JMP MAIN

CODE ENDS
END START