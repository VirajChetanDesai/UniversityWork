	AREA Reset,DATA, READONLY
	EXPORT __Vectors
__Vectors
	DCD 0x10001000
	DCD Reset_Handler
	ALIGN
	
	AREA mycode,CODE, READONLY
	ENTRY
	EXPORT Reset_Handler
Reset_Handler
	LDR R0,=NUM1 ; TAKING INPUT
	LDR R1,[R0]
	MOV R3,#0 ; CARRYOVER
	MOV R10,#0 ; FINAL OUTPUT
	MOV R4,#1 ; MULTIPLIER
	MOV R5,#2 ; CONSTANT
LOOP AND R2,R1,#0X0F ; TO SELECT LSB
	CMP R2,#9 ; COMPARE WITH 9
	BHI MINI ; IF GREATER GO TO MINI
BACK MUL R2,R2,R4 ; MULTIPLE FOR ITS PLACE LIKE ONES,TENS,THOUSANDS
	ADD R10,R10,R2 ; ADD FIN LSB INTO OUTPUT
	MUL R4,R4,R5 ; UPDATING MULTIPLIER * 2
	LSR R1,#4 
	MUL R3,R4 ; MULTIPLIER * 2 * CARRYOVER FORM LINE 23
	ADD R10,R10,R3
	MOV R3,#0 ; RESET CARRYOVER
	CMP R2,#0 ; EXIT CONDITION
	BNE LOOP ; IF FAIL RESTART 
	BEQ FINAL ; ELSE OUTPUT

MINI SUB R2,R2,#10 ; A-10 = 0 FIN LSB = 0
	ADD R3,R3,#1 ; CARRYOVER = 1
	B BACK
	
FINAL LDR R7,=DEST
	STR R10,[R7]
STOP B STOP
NUM1 DCD 0xABCD
	AREA data,DATA, READWRITE
DEST DCD 0
	END