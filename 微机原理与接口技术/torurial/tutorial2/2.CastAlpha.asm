; **************************************************************************
; * *
; * Written by Mr. YanJingcun *
; * *
; * [Oct 09, 2021]
; * *
; * Function: *
; *           编程将后跟$符的字符串“Go to School.”中的小写字母都改成大写字母。
; *          （提示：小写 字母比大写字母 的 ASCII 大 20H）小写转换成大写过程要
; *           求用子程序完成
; * *
; **************************************************************************

DATA     SEGMENT                          ;数据段
STRING   DB 'Go To School.$'
COUNT    EQU $-STRING ;count是字符总个数
DATA     ENDS

CODE     SEGMENT                          ;代码段
         ASSUME CS:CODE,DS:DATA  ;2个段寄存器分别与哪些段有关
START:   MOV   AX,DATA
         MOV   DS,AX                      ;设置数据段
         MOV   CH,COUNT ;CH数组长度
         MOV   BX,0 ;基址指针清0

         ; 输出原字符串
         MOV  DX,OFFSET STRING ; 显示转换完的字符串
         MOV  AH,09H
         INT  21H

         ; 输出回车和换行
         CALL CRLF

LOOP1:   MOV  AH,STRING[BX]
         CMP  AH,61H ; 61h是 a
         JL   NEXT
         CMP  AH,7AH ; 7a是 z
         JG   NEXT 
         CALL CAST ; 小写字母，直接调用转换

NEXT:      ;当前字符不是小写字母，或者已经循环完毕

         INC  BX
         DEC  CH
         JNZ  LOOP1 ;未完，继续下一个
 
         MOV  DX,OFFSET STRING ; 显示转换完的字符串
         MOV  AH,09H
         INT  21H

         ; 退出DOS
         MOV  AX,4C00H
         INT  21H

CAST     PROC NEAR ; 将小写字母转化为大写字母的子程序
         SUB  AH,20H ;减去20h，转化为大写字母
         MOV  STRING[BX],AH ; 挪回去
         RET
CAST     ENDP


; 输出回车和换行的子程序
CRLF     PROC NEAR
         MOV DL,0DH
         MOV AL,2
         INT 21H
         MOV DL,0AH
         MOV AH,2
         INT 21H
         RET 
CRLF     ENDP

CODE     ENDS                              ;代码段结束
         END START                         ;源代码结束