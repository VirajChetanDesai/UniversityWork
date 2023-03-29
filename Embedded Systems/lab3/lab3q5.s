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
	LDR R0,=NUM1; given two unpacked values convert into one packed value
	LDR R1,[R0] ;take value of NUM1 into r1
	LDR R0,=NUM2
	;two convert unpacked to packed bcd we must LSL one of the numbers by 4 bits and add to another
	LDR R2,[R0]; take value of NUM2 into r2
	MOV R3,R2,LSL #4
	ADDS R4,R1,R3
	
	LDR R5,=DEST
	STR R4,
STOP B STOP
NUM1 DCD 0X1
NUM2 DCD 0X2
	AREA data,DATA,READWRITE
DEST DCD 0
	END