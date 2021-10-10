; ; **************************************************************************
; ; * *
; ; * Written by Mr. YanJingcun *
; ; * *
; ; * [Oct 09, 2021]
; ; * *
; ; * Function: *
; ; *           program_function*
; ; * *
; ; **************************************************************************
DATAS SEGMENT
BUF   DB 20
      DB ?
      DB 20 DUP(24H)
CRLF  DB 0AH,0DH,'$'
  DATAS ENDS
CODES SEGMENT
    ASSUME CS:CODES,DS:DATAS
START:
    MOV AX,DATAS
    MOV DS,AX
    ; 输入字符串到内存缓冲区
    LEA DX,BUF
    MOV AH,0AH
    INT 21H

    ; 回车换行
    LEA DX,CRLF
    MOV AH,09H
    INT 21H
    ; 输出数据
    LEA DX,BUF+2
    MOV AH,09H
    INT 21H
    
    ; 退出DOS
    MOV AH,4CH
    INT 21H
CODES ENDS
    END START