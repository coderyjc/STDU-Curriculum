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
	MEM DB 12H,91H,73H,64H,20H,0A5H,0D1H,91H,0A2H,00H
	PLUS DB 00H
	ZERO DB 00H
	NEGO DB 00H
DATA ENDS
 
CODE SEGMENT
			ASSUME CS:CODE,DS:DATA
START:
MOV AX,DATA
MOV DS,AX
 
MOV CX,10 ; 初始化CX用来进行 loop 的计数
LEA BX,MEM ; BX 指向 MEM数组的基地址
DEC BX ; BX 指向 MEM 数组的基地址的前一位置
 
SIGN:
		INC BX ; BX 后移
		MOV DX,[BX] ; BX 指向的数值赋值给 DX
		TEST DX,0FFH ; 和 0 相比
		JZ ZERO_NUM 
		TEST DX,80H ; 和 1 相比
		JZ PLUS_NUM
		INC NEGO

NEXT:
		; 进行循环
		LOOP SIGN
		; 循环结束
		
		; 打印正数个数
		MOV DL,PLUS
		ADD DL,30H
		MOV AH,02H
		INT 21H
		
		; 打印 0 个数
		MOV DL,ZERO
		ADD DL,30H
		INT 21H
		
		; 打印复数个数
		MOV DL,NEGO
		ADD DL,30H
		INT 21H
		
		; 返回DOS
		MOV AH,4CH
		INT 21H
		
ZERO_NUM:
		INC ZERO
		JMP NEXT
		
PLUS_NUM:
		INC PLUS
		JMP NEXT
		
 
 
CODE ENDS
END START