	AREA RESET, DATA, READONLY
	EXPORT __Vectors
__Vectors 
	DCD 0x10001000
	DCD Reset_Handler
	ALIGN
	AREA mycode, CODE, READONLY
ENTRY
	EXPORT Reset_Handler
Reset_Handler
	LDR R0,=NUM1
	LDRB R1,[R0]
	LDR R0,=NUM2
	LDRB R2,[R0]
	
	CMP R1,R2
	BHI MSC
	MOV R3,R1
	MOV R1,R2
	MOV R2,R3

MSC MOV R3,R2

FIX	MOV R4,R1
	MOV R5,R2

DIV SUBS R4,R4,R3
	CMP R4,#0X0
	BMI RES
	BHI DIV
	BEQ DIV2
RES	SUB R3,R3,#1
	BAL FIX
	
DIV2 SUBS R5,R5,R3
	CMP R5,#0X0
	BMI RES2
	BHI DIV2
	BEQ FIN
RES2	SUB R3,R3,#1
	BAL FIX
	
FIN LDR R5,=GCD
	STR R3,[R5]
	MUL R6,R1,R2
	MOV R7,#0X0
	
DI SUB R6,R6,R3
	CMP R6,#0X0
	ADD R7,R7,#1
	BEQ FINLCM
	BHI DI
	
FINLCM LDR R8,=LCM
	STR R7,[R8]
	
STOP B STOP
NUM1 DCD 0X4
NUM2 DCD 0X2
	AREA data, DATA, READWRITE
GCD DCD 0
LCM DCD 0
	END