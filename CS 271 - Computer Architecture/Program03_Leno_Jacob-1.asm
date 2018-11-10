TITLE Program Template     (Program03_Leno_Jacob.asm)

; Author: Jacob Leno
; Course / Project ID 271-400 (Program 3): Integer Accumulator   Date: 10/27/17
; Description: This program will ask the user for integer inputs between -100 and -1 and
; will continue to ask for input until a non-negative number is entered. It then sums up 
; all the numbers entered and displays the sum and the average rounded to the nearest integer
;This program fulfills extra credit option 1.

INCLUDE Irvine32.inc

	TRUE = 1
	FALSE = 0
	UPPERLIMIT = -100
	LOWERLIMIT = -1

.data

;define strings to be used in the program
	nameTitle				BYTE		"Welcome to the Integer Accumulator by Jacob Leno", 0
	getUserName				BYTE		"What is your name? ", 0
	extraCred				BYTE		"**EC: Fulfilled EC 1: Number the lines during user input.", 0
	termsRange				BYTE		"Please enter numbers in [-100, -1].", 0
	howToExit				BYTE		"Enter a non-negative number when you are finished to see results.", 0
	enterNum				BYTE		"Enter number ", 0
	colon					BYTE		": ", 0
	youEntered				BYTE		"You entered ", 0
	validNum				BYTE		" valid numbers.", 0
	sumTotal				BYTE		"The sum of your valid numbers is ", 0
	roundedAverage			BYTE		"The rounded average is ", 0
	hello					BYTE		"Hello, ", 0
	goodbye					BYTE		"Thank you for playing Integer Accumulator!", 0Dh, 0Ah, "It's been a pleasure to meet you, ", 0
	nameBuffer				BYTE		100 DUP(?)
	invalidNum				BYTE		"Please enter a valid integer", 0
	noNumbers				BYTE		"No numbers entered!", 0


	lineNum					DWORD		1
	remainder				DWORD		?
	posNum					SDWORD		?
	sum						SDWORD		0
	roundedAve				SDWORD		?
	numberBuffer			BYTE		10 DUP(?)
	numLength				BYTE		?


.code
main PROC

;--------------------------------------------------------
;Introductions
;--------------------------------------------------------

	mov				edx, OFFSET nameTitle				;Move the greeting into edx
	call			WriteString
	call			CrLf
	call			CrLf
	mov				edx, OFFSET extraCred
	call			WriteString
	call			CrLf
	mov				edx, OFFSET getUserName				;Move the request for a name into edx
	call			WriteString
	mov				edx, OFFSET nameBuffer				;Point to buffer
	mov				ecx, SIZEOF nameBuffer				;Specify the max characters the buffer can hold
	call			ReadString
	mov				edx, OFFSET hello					;Move "Hello, " into edx
	call			WriteString
	mov				edx, OFFSET nameBuffer
	call			WriteString
	call			CrLf
	call			CrLf

;--------------------------------------------------------
;User instructions
;--------------------------------------------------------

	mov				edx, OFFSET termsRange			;Display instructions on what to enter
	call			WriteString						;and how to use the program
	call			CrLf
	mov				edx, OFFSET howToExit
	call			WriteString
	call			CrLf

;--------------------------------------------------------
;Get user data
;--------------------------------------------------------

	DoWhile:
	mov				edx, OFFSET enterNum			;Get the user's number
	call			WriteString
	mov				eax, lineNum					;Display the current number requested
	call			WriteDec
	mov				edx, OFFSET colon
	call			WriteString
	mov				edx, OFFSET	numberBuffer
	mov				ecx, SIZEOF	numberBuffer
	call			ReadString						;Get the user input in the form of a string
	call			checkInt
	cmp				eax, FALSE						;If checkNum returns false jump BadNum
	je				BadNum

	cmp				edx, 0
	jge				EndofLoop						;If user decides to quit jump to the end

	mov				eax, FALSE
	add				sum, edx						;Add the valid number to edx
	inc				lineNum		
	jmp				EndofLoop						;Jump over BadNum since the number is good

	BadNum:
	mov				edx, OFFSET invalidNum			;Ask the user to input a valid number
	call			WriteString
	call			CrLf
	EndofLoop:
	cmp				eax, FALSE						;Should the loop stop? (FALSE - Continue)
	je				DoWhile

	cmp				lineNum, 1						;Did they quit on the first entry? If so jump to the end
	je				First


	;Get the rounded average of the sum
	sub				lineNum, 1
	mov				eax, sum
	cdq
	idiv			lineNum
	mov				roundedAve, eax
	cmp				edx, 0
	je				noSub
	mov				eax, lineNum
	mov				ecx, -2
	mov				remainder, edx
	cdq
	idiv			ecx
	cmp				remainder, eax
	jg				noSub
	sub				roundedAve, 1
	noSub:

	;Output the number of valid numbers that the user input
	mov				edx, OFFSET youEntered
	call			WriteString
	mov				eax, lineNum
	call			WriteDec
	mov				edx, OFFSET validNum
	call			WriteString
	call			CrLf

	;Output the sum of the numbers the user input
	mov				edx, OFFSET sumTotal
	call			WriteString
	mov				eax, sum
	call			WriteInt
	call			CrLf

	;Output the rounded average of the numbers the user input
	mov				edx, OFFSET roundedAverage
	call			WriteString
	mov				eax, roundedAve
	call			WriteInt
	call			CrLf

	jmp				EndMessage

	First:												;If the user exited on the first input 
	mov				edx, OFFSET noNumbers				;Display a message saying that they entered no numbers
	call			WriteString
	call			CrLf
	
	EndMessage:
	mov				edx, OFFSET goodbye					;Display the end message
	call			WriteString
	mov				edx, OFFSET nameBuffer
	call			WriteString
	call			CrLf

	exit	; exit to operating system
main ENDP

;-----------------------------------------------------------------------------
;Procedure: checkInt
;Description: Checks a number to see if its a valid integer returns good integer
;in EDX
;Recieves: A buffer to be checked in EDX, The length of the buffer in EAX
;
;Returns:  If the number is good it will be returned in EDX, EAX will contain
;the value of TRUE/FALSE
;-----------------------------------------------------------------------------
	checkInt	PROC	USES	ecx ebx esi
	mov			ebx, eax						;Move the length into ebx	
	mov			esi, 0							
	mov			ecx, -1							
	
	Do:
	inc			esi
	mov			al, numberBuffer[esi -1]		;Subtract 1 to account for the increment
	cmp			al, 2Dh							;Is AL the negative sign
	je			L1
	call		IsDigit
	jnz			NotANumber						;IsDigit has encountered a non-number, jump to the
	L1:											;end of the prodecure!
	cmp			esi, ebx
	jl			Do


	mov			edx, OFFSET numberBuffer
	mov			ecx, SIZEOF numberBuffer
	call		ParseInteger32					;Extract a number from the buffer
	mov			edx, eax						;Move the number extracted from numberBuffer to edx
	
	mov			ecx, 0
	cmp			edx, 0
	jnl			NotNeg							;If the number is negative add one account for the 
	inc			ecx								;negative sign in the buffer
	NotNeg:

	push		ebx								;Push the length in ebx onto the stack
	push		edx								;Push the user number onto the stack
	mov			ebx, 10

	
	WhileNotZero:								;Find out how many digits in the number extracted from the buffer
	cdq											;Sign extend eax into edx
	idiv		ebx
	inc			ecx
	cmp			eax, 0
	jne			WhileNotZero
	pop			edx								;Pop edx off the stack
	pop			ebx								;Pop the length off the stack into ebx


;*****Alter the comparisons in this part to change what is returned as true in future code****
	NotANumber:
	mov			eax, FALSE						;eax starts off as false
	cmp			ebx, ecx						;	If the length extracted and the length of the buffer 
	jne			EndFunction						;	are not the same end with false
	cmp			edx, -100						;If the number is less than -100
	jl			EndFunction						;end with false
	mov			eax, TRUE						;Otherwise the number is good

	EndFunction:
	ret
	checkInt	ENDP



END main
