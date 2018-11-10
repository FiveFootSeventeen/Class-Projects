TITLE Recursive Combinations    (Program06_B_Leno_Jacob.asm)

; Author: Jacob Leno
; Course / Project ID   CS271 - 400 / Program 6b.       Date: 11/28/17
; Description: The program will ask the user to calculate the number of combinations
; of r items taken from a set of n items. First the program generates random problems with n 
; in [3 .. 12] and r in [1 .. n]. The user then enters his/her answer, and the program reports
; the correct answer and an evaluation of the student's answer. The program repeats until the 
; user chooses to quit.

INCLUDE Irvine32.inc

	MIN = 1
	MAX = 9999
	LO = 3
	HI = 12
	TRUE = 1
	FALSE = 0

;writeText macro: Writes the contents of a buffer to the console
;Recieves: The offset of a buffer in edx
;**Code borrowed from lecture 26 slide 6.**

	mWriteText	MACRO	buffer
	push		edx
	mov			edx, OFFSET buffer
	call		WriteString
	pop			edx
	ENDM

.data

	intro			BYTE			"Welcome to the Combinations Calculator", 0dh, 0ah, 9h, "Implemented by Jacob Leno", 0
	problemExp		BYTE			"I'll give you a combinations problem. You enter your answer,", 0dh, 0ah,
									"and I'll let you know if you're right.", 0
	problem			BYTE			"Problem:", 0
	noElementSet	BYTE			"Number of elements in the set: ", 0
	noElementChoose	BYTE			"Number of elements to choose from the set: ", 0
	waysToChoose	BYTE			"How many ways can you choose? ", 0
	thereAre		BYTE			"There are ", 0
	combOf			BYTE			" combinations of ", 0
	itemsFrom		BYTE			" items from a set of ", 0
	period			BYTE			".", 0
	wrong			BYTE			"You need more practice.", 0
	correct			BYTE			"You are correct!", 0
	invalid			BYTE			"Invalid response.", 0
	another			BYTE			"Another problem? (y/n): ", 0
	goodbye			BYTE			"OK ... goodbye.", 0
	validNum		BYTE			"Please enter a valid number between 1 and 9999: ", 0
	
	result			DWORD			?
	nValue			DWORD			?
	rValue			DWORD			?
	answer			DWORD			?
	buffer			BYTE			10 DUP(?)

.code
main PROC

	showProblem	PROTO, nVar: PTR DWORD, rVar: PTR DWORD
	getData	PROTO, answer: PTR DWORD
	combinations PROTO, nVal: DWORD, rVal: DWORD, finalRes: PTR DWORD
	showResults PROTO, n: DWORD, r: DWORD, userAns: DWORD, correctAns: DWORD

	call			randomize
	call			introduction
	Again:
	invoke			showProblem, ADDR nValue, ADDR rValue
	invoke			getData, ADDR answer
	invoke			combinations, nValue, rValue, ADDR result
	invoke			showResults, nValue, rValue, answer, result
	call			tryAgain
	cmp				eax, TRUE
	je				Again


	exit	
main ENDP

;-----------------------------------------------------------------------------
;introduction: displays title, programmer name, and instructions.
;Recieves: none
;
;Returns:  none
;-----------------------------------------------------------------------------
	introduction	PROC

	mWriteText		intro
	call			CrLf
	call			CrLf
	mWriteText		problemExp
	call			CrLf
	call			CrLf

	ret
	introduction	ENDP

;-----------------------------------------------------------------------------
;showProblem: generates the random numbers and displays the problem
;Recieves: The variable to store n by reference, the variable to store r by 
; reference
;
;Returns:  None
;-----------------------------------------------------------------------------

	showProblem		PROC USES eax esi,
		nVar: PTR DWORD, rVar: PTR DWORD

	mov				eax, HI				
	sub				eax, LO
	inc				eax
	call			randomRange				;Get a value in the range of HI - LO
	add				eax, LO					;Add LO to eax to put the value in the range of 3-12
	mov				esi, nVar				;Move the address of nVar into esi
	mov				[esi], eax				;Dereference nVar and move the new random value into it
	
	sub				eax, MIN
	inc				eax
	call			randomRange				;Get a value in the range of nVar - MIN
	add				eax, MIN				;Add MIN to eax to put the value in the range of 1-nVar
	mov				esi, rVar				;Move the address of rVar into esi
	mov				[esi], eax				;Dereference rVar and move the new random value into it

	mWriteText		problem
	call			CrLf
	mWriteText		noElementSet
	mov				esi, nVar
	mov				eax, [esi]				;Move the n variable into eax and write to the console
	call			WriteDec
	call			CrLf
	mWriteText		noElementChoose
	mov				esi, rVar				;Move the address of rVar into esi
	mov				eax, [esi]				;Move the r variable into eax and write to the console
	call			WriteDec
	call			CrLf

	ret
	showProblem		ENDP

;-----------------------------------------------------------------------------
;getData: prompt and get the user’s answer
;Recieves: The address of a variable to store the user's answer in
;
;Returns:  A valid number in edx
;-----------------------------------------------------------------------------

	getData	PROC USES eax edx ecx,
		answerVar: PTR DWORD

	checkInt PROTO, lower: DWORD, upper: DWORD, numberBuffer: PTR BYTE, inputLength: DWORD

	mWriteText		waysToChoose
	BadNum:
	mov				edx, OFFSET buffer
	mov				ecx, SIZEOF buffer
	call			ReadString									
	invoke			checkInt, MIN, MAX, OFFSET buffer, eax		;Check the user's entry to see if its a valid number
	cmp				eax, TRUE									;If checkInt returned true jump to GoodNum
	je				GoodNum
	mWriteText		validNum									;Otherwise output a message asking for a valid number and 
	jmp				BadNum										;jump back to the top
	GoodNum:
	mov				esi, answerVar								;Move the address of answerVar into esi
	mov				[esi], edx									;Move the correct answer returned by checkInt into answerVar

	ret
	getData ENDP


;-----------------------------------------------------------------------------
;combinations: calculates n!/((r!(n-r)!) and stores the value in result
;Recieves: The value of n, the value of r, the address of the variable the result
; will be stored in
;
;Returns: The result of n!/((r!(n-r)!) stored in the address passed to the procedure 
;-----------------------------------------------------------------------------

	combinations PROC USES eax ebx edx,
		nVal: DWORD, rVal: DWORD, finalRes: PTR DWORD 

	mov				eax, nVal
	sub				eax, rVal			;Subtract r from n to get (n-r)
	cmp				eax, 0
	jne				NotZero				;If (n-r) is 0 find the factorial of 1
	mov				eax, 1
	NotZero:
	push			eax
	call			factorial			;Find the factorial of (n-r) to get (n-r)!
	mov				ebx, eax			;Save the value returned by factorial
	push			rVal				
	call			factorial			;Find the factorial of r to get r!
	mul				ebx					;Multiply what was returned from factorial by ebx to get (r!(n-r)!)
	mov				ebx, eax			;Save the result in ebx
	push			nVal				
	call			factorial			;Find the factorial of n to get n!
	mov				edx, 0	
	cdq									;Sign extend into edx
	div				ebx					;Divide eax (n!) by ebx (r!(n-r)!)
	mov				esi, finalRes		;Move the address in finalRes into esi
	mov				[esi], eax			;Dereference esi and store the result

	ret
	combinations ENDP

;-----------------------------------------------------------------------------
;factorial: calculates the factorial of the number it is sent by recursion
;Recieves: DWORD value on the stack
;
;Returns: Factorial of the value sent in eax
;-----------------------------------------------------------------------------

	factorial PROC 
	push			ebp
	mov				ebp, esp

	mov				eax, [ebp + 8]				;Get the value to check off the stack
	cmp				eax, 1						;If the value is one, quit the recursion
	je				quit
	dec				eax							;Decrement the value
	push			eax							;Push it onto the stack
	call			factorial					;Recursively call factorial
	mul				DWORD PTR [ebp + 8]			;Multiply the value in eax by the previous value
	jmp				quit
	quit:

	pop				ebp
	ret				4
	factorial ENDP

;-----------------------------------------------------------------------------
;showResults: display the user’s answer, the calculated result, and a brief 
;statement about the student’s performance
;Recieves: The value of n, the value of r, the value of the user's answer, and
; the value of the result
;
;Returns:  Nothing
;-----------------------------------------------------------------------------

	showResults PROC USES eax, 
		n: DWORD, r: DWORD, userAns: DWORD, correctAns: DWORD

	mWriteText		thereAre
	mov				eax, correctAns			;Move the correct answer into eax and write to console
	call			WriteDec
	mWriteText		combOf
	mov				eax, r					;Move r into eax and write to console
	call			WriteDec
	mWriteText		itemsFrom
	mov				eax, n					;Move n into eax and write to console
	call			WriteDec
	mWriteText		period
	call			CrLf

	mov				eax, userAns			;Move the user's answer into eax and compare to the correct answer
	cmp				eax, correctAns
	je				RightAns				;If the user was right display the right answer message
	mWriteText		wrong
	jmp				Quit
	RightAns:
	mWriteText		correct					;If the user was wrong display the wrong answer message
	Quit:
	call			CrLf
	call			CrLf

	ret
	showResults ENDP

;-----------------------------------------------------------------------------
;tryAgain: Asks the user if they want to try again and gets their response
;Recieves: Nothing
;
;Returns: The user's response as either TRUE or FALSE in eax
;-----------------------------------------------------------------------------

	tryAgain PROC

	repeatQ:
	mWriteText		another
	call			ReadChar			;Read the user's response
	call			CrLf
	cmp				al, 90				;If its greater than 90 add 32
	jg				NoAdd
	add				al, 32
	NoAdd:
	cmp				al, 121				;If its equal to 121 they want to try again
	je				KeepGoing
	cmp				al, 110				;If its equal to 110 they want to quit
	je				Stop
	mWriteText		invalid				;If its not equal to either they have entered an invalid letter/number
	jmp				repeatQ				;Repeat the question
	Stop:
	mov				eax, FALSE			;Stop asking and move FALSE into eax
	call			CrLf
	mWriteText		goodbye
	call			CrLf
	jmp				Quit
	KeepGoing:
	mov				eax, TRUE			;Stop asking and move TRUE into eax
	call			CrLf
	Quit:

	ret
	tryAgain ENDP

;-----------------------------------------------------------------------------
;Description: Checks a number to see if its a valid integer returns good integer
;in EDX
;Recieves: lower limit, upper limit, pointer to the buffer the number is in, and
; the length of the buffer.
;
;Returns:  If the number is good it will be returned in EDX, EAX will contain
;the value of TRUE/FALSE
;-----------------------------------------------------------------------------

	checkInt PROC USES ecx ebx esi,
		lower: DWORD,
		upper: DWORD,
		numberBuffer: PTR BYTE,
		inputLength: DWORD

	mov			ebx, 0
	mov			ecx, 0
	mov			ecx, inputLength				;Move the length into ecx	
	mov			esi, numberBuffer							
				
	Do:
	mov			al, [esi]						;Move value to check into al
	inc			esi	
	cmp			al, 2Dh							;Is AL the negative sign
	je			L1
	call		IsDigit
	jnz			NotANumber						;IsDigit has encountered a non-number, jump to the
	L1:											;end of the prodecure!
	loop		Do


	mov			edx, numberBuffer
	mov			ecx, 0
	mov			ecx, inputLength
	call		ParseInteger32					;Extract a number from the buffer
	mov			edx, eax						;Move the number extracted from numberBuffer to edx
	
	mov			ecx, 0
	cmp			edx, 0
	jnl			NotNeg							;If the number is negative add one account for the 
	inc			ecx								;negative sign in the buffer
	NotNeg:

	push		edx								;Push the user number onto the stack
	mov			ebx, 10

	
	WhileNotZero:								;Find out how many digits in the number extracted from the buffer
	cdq											;Sign extend eax into edx
	idiv		ebx
	inc			ecx
	cmp			eax, 0
	jne			WhileNotZero
	pop			edx								;Pop edx off the stack

	NotANumber:
	mov			eax, 0							;eax starts off as false
	cmp			inputLength, ecx				;	If the length extracted and the length of the buffer 
	jne			EndFunction						;	are not the same end with false
	cmp			edx, lower						;If the number is less than lower end with false
	jl			EndFunction
	cmp			edx, upper						;If the number is greater than upper
	jg			EndFunction						;end with false
	mov			eax, 1							;Otherwise the number is good

	EndFunction:
	ret
	checkInt	ENDP


END main
