DATA SEGMENT
CS8251D  EQU    30H ; 数据
CS8251C  EQU     32H ; 控制
STR1  DB    'SHIJIAZHUANG RAILWAY UNIVERSITY            $'
DATA ENDS

CODE    SEGMENT PUBLIC 'CODE'
        ASSUME CS:CODE,DS:DATA
START:
        MOV  AX,DATA
	      MOV  DS,AX
INIT: 
        XOR  AL,AL ; 清0.占用1个时钟周期
        MOV CX,03 ; 
        MOV DX,CS8251C ; 
OUT1:
       OUT DX,AL
       LOOP  OUT1 ; 3个0
       MOV  AL,40H
       OUT  DX,AL ; 复位
       MOV  DX,CS8251C
       MOV  AL,01001101B ; 1个停止位、 无奇偶校验、 字符长度8位、 异步方式 x 1
       OUT  DX,AL ; 控制口写入方式字
       MOV  AL,00010101B ; 使错误标志复位、正常工作、允许接受、允许发送
       OUT  DX,AL ; 控制口写入命令字
 RE:
       LEA  DI,STR1 ; 取地址
SEND:
	MOV  DX,CS8251C
	MOV  AL,00010101B 
	OUT  DX,AL  ; 状态字

WTXD:
   IN  AL,DX ; 读入状态
	 TEST  AL,1 ; TxRDY 有效吗
	 JZ  WTXD ; 无效，等待
	 MOV  AL,[DI]  
	 MOV  AH,'$'; 下一个字符是终止符吗
	 CMP  AL,AH
	 JE RE ; 是，重发
	 MOV  DX,CS8251D ; 下一个字符不是终止符
	 OUT  DX,AL ; 控制口地址送到DX，自动写入
	 MOV  CX,3000H
	 LOOP  $ ; 延时
	 INC  DI
	 LOOP  SEND

ENDLESS:
        JMP ENDLESS
CODE    ENDS
END START