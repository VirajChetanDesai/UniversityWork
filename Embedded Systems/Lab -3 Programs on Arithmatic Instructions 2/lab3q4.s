	AREA RESET,DATA, READONLY
	EXPORT __Vectors
__Vectors
	DCD 0X10001000
	DCD Reset_Handler
	ALIGN
	AREA mycode,CODE,READONLY
ENTRY
	EXPORT Reset_Handler
Reset_Handler
	LDR R0,=NUM1
	LDR R1,[R0]; LOAD THE NUMBER
	
	AND R2,R1,#0X0F ;LOAD LOWER BIT TO R2
	MOV R3,R1,LSR #4 ; LOAD HIGHER BIT TO R3
	CMP R2,#0X09 ; COMPARE LOWER BIT WITH 09
	BLS DOWN
	ADD R2,R2,#0X07

DOWN ADD R2,R2,#0X30
	
SECOND CMP R3,#0X09
	BLS DOWN2
	ADD R3,R3,#0X07
	
DOWN2 ADD R3,R3,#0X30

STORE LDR R4,=DEST0
	STR R2,[R4]
	LDR R5,=DEST10
	STR R3,[R5]
STOP B STOP
NUM1 DCD 0X3A
	AREA data, DATA, READWRITE
DEST0 DCD 0
DEST10 DCD 0
	END
